#include "stdafx.h"
#include "..\Headers\Transform.h"
#include "Terrain.h"
#include "TurnMgr.h"
#include "LevelMgr.h"
#include "Texture.h"
#include "ModuleMgr.h"
#include "Pipline.h"
#include "Spawner.h"
USING(MyGame)

_int CTransform::m_iTurnCnt = 0;
CTransform::CTransform(LPDIRECT3DDEVICE9 _pGraphic_Device)
	:CModule(_pGraphic_Device)
{
	m_tStateDesc.movePerTurn = 1;
	m_tStateDesc.radianPerSec = 1;
	m_tStateDesc.speedPerSec = 1;
}

CTransform::CTransform(CTransform & _module)
	: CModule(_module)
{

}

HRESULT CTransform::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CTransform::Initialize(void * _pArg)
{
	if (nullptr != _pArg)
		memcpy(&m_tStateDesc, _pArg, sizeof(STATEDESC));


	m_vSize = Vector3(1.f, 1.f, 1.f);
	m_vRotation = Vector3(0.f, 0.f, 0.f);
	m_vPosition = Vector3(0.f, 0.f, 0.f, 1.f);
	m_vDir = Vector3();
	m_vLook = Vector3(1.f, 0.f, 0.f);
	m_vColliderSize = Vector3(1.f, 1.f, 1.f);
	D3DXMatrixIdentity(&m_StateMatrix);

	//�ݶ��̴��� ���� VIBuffer
	m_pVIBuffer = dynamic_cast<CVIBuffer*>(CModuleMgr::Get_Instance()->Get_Module(L"VIBuffer", SCENE_STATIC));
	if (nullptr == m_pVIBuffer)
		return E_FAIL;
	//�ݶ��̴��� ���� �ؽ���
	m_pTexture = dynamic_cast<CTexture*>(CModuleMgr::Get_Instance()->Get_Module(L"empty_bound", SCENE_STATIC));
	if (nullptr == m_pTexture)
		return E_FAIL;

	return S_OK;
}

HRESULT CTransform::Update_Route(_double _timeDelta)
{
	if (m_bStop)
		return E_FAIL;


	//��� ��Ʈ�� �̵��ϸ� ����.
	//���⼭ ��ī��Ʈ�� ���ؼ� ������. ���ʹ� �̵� �߰��� ���ݵ��ϴϱ� ��ī��Ʈ�� �״�ξ��� �ȵ�.
	if ((_int)m_iCurrRouteIndex >= m_Route.size() ||
		(m_iTotalMoveCnt >= (_int)m_tStateDesc.movePerTurn * m_iTurnCnt))
	{
		//�ʱ�ȭ
		m_bStop = true;
		m_iCurrRouteIndex = 0;
		m_iTotalMoveCnt = 0;
		m_iCntForTurn = 0;
		m_Route.swap(vector<CTerrain*>());
		m_pTarget = nullptr;
		// isTurnEnd�� false���� �Ѵ�. true�� ��� ���� �Ѿ�� ���Ͱ� GO_Route��Ӻθ�.
		return TURN_END;
	}

	CTransform* pTileTransform = (CTransform*)m_Route[m_iCurrRouteIndex]->Get_Module(L"Transform");
	if (nullptr == pTileTransform)
		return E_FAIL;

	_float fSpeed = (_float)m_tStateDesc.speedPerSec;

	m_vDir = pTileTransform->Get_Position() - m_vPosition;
	if (m_vDir.magnitude() > 5.f)
	{
		//�ƹ��� ������ ���� Ÿ���ΰ�. �ڱ��ڽ��� ���ִٰ� �Ǵ°ǰ�?
		_bool	bEmptyTile = (nullptr == CSpawner::Get_Instance()->PickCharacter(pTileTransform->Get_Position(), CLevelMgr::Get_Instance()->Get_CurrDepth(), this));
		//������ ��θ� �ٽ� üũ�ؼ� �� �� �ִ� ���̸�
		if (bEmptyTile)
		{
			m_vPosition += m_vDir.nomalize() * float(fSpeed * _timeDelta);
		}
		//�� �� ������ ��Ʈ����
		else
		{
			//��Ʈ ����
			m_Route.swap(vector<CTerrain*>());

			CLevel* pLevel = CLevelMgr::Get_Instance()->Get_CurrLevel();
			RETURN_FAIL_IF_NULL(pLevel);

			if (m_pTarget != nullptr)
			{
				pLevel->Get_Route(m_vPosition, m_pTarget->Get_Position(), m_Route, this);
			}
			else
			{

				pLevel->Get_Route(m_vPosition, m_vDst, m_Route, this);
			}

			//��Ʈ �ε��� �ʱ�ȭ
			m_iCurrRouteIndex = 0;
		}

		FaceDir(m_vDir);
	}
	//Ÿ�Ͽ� ����������
	else
	{
		//������ Ÿ�� �� ����
		++m_iCntForTurn;
		//�Ͽ� ������� ���ݱ��� �̵��� Ÿ�� ��
		++m_iTotalMoveCnt;
		//�� Ÿ�������� �ε��� ���ϱ�
		++m_iCurrRouteIndex;

		////Ÿ���� �i�� ���¶�� (�ַ� ����)
		//if (nullptr != m_pTarget)
		//{
		//	//Ÿ���� ��ġ�� ���ϱ� ������ ��Ʈ�� �Ź� ����������Ѵ�.(��ĭ ��������)
		//	m_Route.swap(vector<CTerrain*>());
		//	CLevel* pLevel = CLevelMgr::Get_Instance()->Get_CurrLevel();
		//	RETURN_FAIL_IF_NULL(pLevel);
		//	pLevel->Get_Route(m_vPosition, m_pTarget->Get_Position(), m_Route, this);

		//	//���Žÿ��� ��Ʈ �ε����� �ʱ�ȭ
		//	m_iCurrRouteIndex = 0;
		//}
	}

	//�ൿ�¸�ŭ �̵��ߴ��� üũ
	//m_iCntForTurn�� ���Ͽ� �̵��� Ÿ�� ���� �ǹ���.
	//���͵�, �÷��̾�� �̵��¸�ŭ �����̸� ������ �ѱ��.
	if ((m_iCntForTurn >= (_int)m_tStateDesc.movePerTurn))
	{
		m_bTurnEnd = true;
		m_iCntForTurn = 0;
	}

	return S_OK;
}

//Auto ������ Update_Nomal�̶� Update_Transform�̶� �Ѵٽ�ߵǴ� �ų� ������
HRESULT CTransform::Update_Normal(_double _timeDelta)
{
	
	m_vPosition += m_vDir_Normal * float(m_tStateDesc.speedPerSec * _timeDelta);

	m_vSize -= m_dShrinkSpeed * _timeDelta;
	m_vSize += m_dExpandSpeed * _timeDelta;
	m_vRotation.z += m_tStateDesc.radianPerSec * _timeDelta;

	return S_OK;
}

_int CTransform::Update_Transform()
{
	_matrix scalingMatrix, rotationXMatrix, rotationYMatrix, rotationZMatrix, translationMatrix,
		revolveXMatrix, revolveYMatrix, revolveZMatrix, parentMatrix, pivotMatrix;

	D3DXMatrixScaling(&scalingMatrix, m_vSize.x, m_vSize.y, m_vSize.z);
	D3DXMatrixRotationX(&rotationXMatrix, m_vRotation.x);
	D3DXMatrixRotationY(&rotationYMatrix, m_vRotation.y);
	D3DXMatrixRotationZ(&rotationZMatrix, m_vRotation.z);
	D3DXMatrixTranslation(&translationMatrix, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	D3DXMatrixRotationX(&revolveXMatrix, m_vRevolveAngle.x);
	D3DXMatrixRotationY(&revolveYMatrix, m_vRevolveAngle.y);
	D3DXMatrixRotationZ(&revolveZMatrix, m_vRevolveAngle.z);
	D3DXMatrixTranslation(&pivotMatrix, m_vPivot.x, m_vPivot.y, m_vPivot.z);


	//�θ� ��ļ���
	if (nullptr != m_pParent)
	{
		_matrix parent = m_pParent->Get_Matrix();
		D3DXMatrixTranslation(&parentMatrix, parent.m[3][0], parent.m[3][1], parent.m[3][2]);
	}
	else
		D3DXMatrixIdentity(&parentMatrix);


	m_StateMatrix = scalingMatrix * pivotMatrix * rotationXMatrix * rotationYMatrix * rotationZMatrix * translationMatrix
		* parentMatrix;

	return 0;
}

HRESULT CTransform::Render_Collider()
{
	if (nullptr == m_pTexture ||
		nullptr == m_pVIBuffer)
		return E_FAIL;

	ALPHATEST;
	m_pTexture->Set_Texture(0);

	//����� ��� �÷��� ����
	Vector3 originSize = m_vSize;
	m_vSize = m_vColliderSize;
	Update_Transform();
	m_pVIBuffer->Set_Transform(m_StateMatrix * CPipline::Get_Instance()->Get_ViewMatrix());
	m_vSize = originSize;
	Update_Transform();

	m_pVIBuffer->Render();

	ALPHATEST_END;
	return S_OK;

}

HRESULT CTransform::Set_Position(Vector3 _vPosition)
{
	m_vPosition = _vPosition;
	m_vPosition.w = 1;
	return S_OK;
}

HRESULT CTransform::Set_Pivot(Vector3 _vPivot)
{
	m_vPivot = _vPivot;
	return S_OK;
}

HRESULT CTransform::Set_Size(Vector3 _vSize)
{
	m_vSize = _vSize;
	return S_OK;
}

HRESULT CTransform::Set_Rotation(Vector3 _vRotation)
{
	m_vRotation = _vRotation;
	return S_OK;
}



Vector3 CTransform::Get_WorldPos()
{
	//�θ� ������ �׳� ������ ����
	if (nullptr == m_pParent)
		return m_vPosition;

	Vector3 result = m_vPosition + m_pParent->Get_WorldPos();
	result.z = 0.f;
	result.w = 1.f;

	//�θ� ������ �θ��� ���������ǿ� �ڽ��� ������������ ���� ���� ����
	return result;
}

RECT CTransform::Get_Collider()
{
	RECT rc = {};
	float fX = m_vPosition.x;
	float fY = m_vPosition.y;
	int iCX = (int)m_vColliderSize.x;
	int iCY = (int)m_vColliderSize.y;

	rc.left = (LONG)fX - (iCX >> 1);
	rc.right = (LONG)fX + (iCX >> 1);
	rc.top = (LONG)fY - (iCY >> 1);
	rc.bottom = (LONG)fY + (iCY >> 1);
	return rc;
}

RECT CTransform::Get_RECT()
{
	RECT rc = {};
	float fX = m_vPosition.x;
	float fY = m_vPosition.y;
	int iCX = (int)m_vSize.x;
	int iCY = (int)m_vSize.y;

	rc.left = (LONG)fX - (iCX >> 1);
	rc.right = (LONG)fX + (iCX >> 1);
	rc.top = (LONG)fY - (iCY >> 1);
	rc.bottom = (LONG)fY + (iCY >> 1);
	return rc;
}


void CTransform::FaceDir(Vector2 _vDir)
{
	float sizeX = abs(m_vSize.x);

	//����� ������ ����, ����� �������� �ٶ󺻴�.
	if (_vDir.x < 0)
		m_vSize.x = -1 * sizeX;
	else
		m_vSize.x = sizeX;
}

HRESULT CTransform::LookAt(CTransform * pTargetTransform)
{
	Vector3		vDirection = pTargetTransform->m_vPosition - m_vPosition;

	_float		fCosTheta = D3DXVec4Dot(&m_vLook.Nomalize(), &vDirection.Nomalize());

	if (pTargetTransform->m_vPosition.y >= m_vPosition.y)
		m_vRotation.z = acosf(fCosTheta);
	else
		m_vRotation.z = D3DXToRadian(360.0f) - acosf(fCosTheta);

	return S_OK;
}

HRESULT CTransform::LookAt(Vector3 _vPos)
{
	Vector3		vDirection = _vPos - m_vPosition;

	_float		fCosTheta = D3DXVec4Dot(&m_vLook.Nomalize(), &vDirection.Nomalize());

	if (_vPos.y >= m_vPosition.y)
		m_vRotation.z = acosf(fCosTheta);
	else
		m_vRotation.z = D3DXToRadian(360.0f) - acosf(fCosTheta);

	return S_OK;
}


void CTransform::Set_Parent(CTransform * pParent)
{
	if (nullptr == pParent)
		return;

	//������ǥ ��ȯ
	m_vPosition = Get_WorldPos() - pParent->Get_WorldPos();
	m_vPosition.z = 0.f;
	m_vPosition.w = 1.f;
	//�θ� ��Ʈ����
	m_pParent = pParent;
}

HRESULT CTransform::MoveToTarget(CTransform * _pTransform, _double _timeDelta, _double _StopDistance)
{

	Vector3 vDir = _pTransform->Get_Position() - m_vPosition;

	if (vDir.magnitude() >= _StopDistance)
	{
		m_vPosition += vDir.nomalize() * float(m_tStateDesc.speedPerSec * _timeDelta);
	}
	return S_OK;

}

HRESULT CTransform::MoveToTarget(CTransform * _pTransform, _double _timeDelta, _double _StopDistance, _double _Speed)
{

	Vector3 vDir = _pTransform->Get_Position() - m_vPosition;

	if (vDir.magnitude() >= _StopDistance)
	{
		m_vPosition += vDir.nomalize() * float(_Speed * _timeDelta);
	}
	return S_OK;
}

HRESULT CTransform::MoveToDirAuto(Vector3 _vDir)
{

	m_vDir_Normal = _vDir;

	return S_OK;
}

HRESULT CTransform::MoveToDirAuto(Vector3 _vDir, _double _timeDelta, _double _Speed)
{

	m_vDir_Normal = _vDir;
	m_tStateDesc.speedPerSec = _Speed;

	return S_OK;
}

HRESULT CTransform::Shrink_Auto(Vector2 _vShrink)
{
	m_dShrinkSpeed = _vShrink;
	return S_OK;
}

HRESULT CTransform::Expand_Auto(Vector2 _vExpand)
{
	m_dExpandSpeed = _vExpand;
	return S_OK;
}

HRESULT CTransform::Rotate_Auto(_double	radianPerSec)
{
	m_tStateDesc.radianPerSec = radianPerSec;
	return S_OK;
}

HRESULT CTransform::MoveToDir(Vector3 _vDir, _double _timeDelta)
{
	m_vPosition += _vDir.nomalize() * float(m_tStateDesc.speedPerSec * _timeDelta);

	return S_OK;
}

HRESULT CTransform::MoveToDir(Vector3 _vDir, _double _timeDelta, _double _Speed)
{
	m_vPosition += _vDir.nomalize() * float(_Speed * _timeDelta);
	return S_OK;
}

_bool CTransform::MoveToDst(Vector3 _vDst, _double _timeDelta, _double _fStopDistance)
{
	Vector3 vDir = _vDst - m_vPosition;

	//�������� �������� �ʾҴٸ� �̵�
	if (vDir.magnitude() >= _fStopDistance)
	{
		Vector3 nextPos = m_vPosition + vDir.nomalize() * float(m_tStateDesc.speedPerSec * _timeDelta);

		//���� ��ġ�� Rect�� ���Ѵ�.
		RECT rc = Make_Rect(nextPos, m_vColliderSize);
		//���� ��ġ�� �� �𼭸��� ���Ѵ�.
		Vector2 pt[4] = { Vector2(rc.left, rc.top), Vector2(rc.right, rc.top), Vector2(rc.left, rc.bottom), Vector2(rc.right, rc.bottom) };

		//�� �𼭸��� �˻��Ѵ�.
		for (int i = 0; i < 4; ++i)
		{
			//���� ������ ���� �ִٸ� �����̶�� ģ��.a
			if (!CLevelMgr::Get_Instance()->IsMovable(pt[i]))
				return true;
		}

		//����ϸ� ����.
		m_vPosition = nextPos;
	}
	else
		//�������� �����ߴٸ� ����
		return true;

	return false;
}

HRESULT CTransform::MoveToDst(Vector3 _vDst, _double _timeDelta, _double _fStopDistance, _double _Speed)
{

	Vector3 vDir = _vDst - m_vPosition;

	if (vDir.magnitude() >= _fStopDistance)
	{
		m_vPosition += vDir.nomalize() * float(_Speed * _timeDelta);
	}
	return S_OK;
}

HRESULT CTransform::Add_Froce(Vector3 _vDir, _float _fForce, _double _timeDelta)
{
	m_vPosition += _vDir * _fForce * float(_timeDelta);
	return S_OK;
}



HRESULT CTransform::Go_Route(vector<CTerrain*> _route, _double _StopDistance, _int _iTurnCnt)
{

	if (_route.empty())
		return E_FAIL;

	m_iTurnCnt = _iTurnCnt;
	m_iCurrRouteIndex = 0;
	m_Route.swap(vector<CTerrain*>());
	m_bTurnEnd = false;
	m_bStop = false;
	m_Route = _route;
	m_StopDistance = _StopDistance;
	CTransform* pTransform = (CTransform*)m_Route.back()->Get_Module(L"Transform");
	if (nullptr == pTransform)
		return E_FAIL;
	m_vDst = pTransform->Get_Position();


	return S_OK;
}

HRESULT CTransform::Go_Target(CTransform * _pTarget, _double _StopDistance)
{
	if (nullptr == _pTarget)
		return E_FAIL;

	m_iCurrRouteIndex = 0;
	m_Route.swap(vector<CTerrain*>());
	m_bTurnEnd = false;
	m_bStop = false;
	m_pTarget = _pTarget;
	m_StopDistance = _StopDistance;
	//��Ʈ ����
	CLevel* pLevel = CLevelMgr::Get_Instance()->Get_CurrLevel();
	RETURN_FAIL_IF_NULL(pLevel);
	pLevel->Get_Route(m_vPosition, m_pTarget->Get_Position(), m_Route, this);

	return S_OK;
}

RECT CTransform::Make_Rect(Vector3 _vPos, Vector2 _vSize)
{

	//���� ��ġ�� Rect�� ���Ѵ�.
	RECT rc = {};
	float fX = _vPos.x;
	float fY = _vPos.y;
	int iCX = (int)_vSize.x;
	int iCY = (int)_vSize.y;

	rc.left = (LONG)fX - (iCX >> 1);
	rc.right = (LONG)fX + (iCX >> 1);
	rc.top = (LONG)fY - (iCY >> 1);
	rc.bottom = (LONG)fY + (iCY >> 1);
	return rc;
}




CTransform * CTransform::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CTransform* pInstance = new CTransform(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CTransform");
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CModule* CTransform::Clone(void * _pArg)
{
	CTransform* pInstance = new CTransform(*this);

	if (FAILED(pInstance->Initialize(_pArg)))
	{
		MSG_BOX("Fail to clone CTransform");
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

void CTransform::Free()
{
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTexture);
	CModule::Free();

}

