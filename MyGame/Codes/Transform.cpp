#include "stdafx.h"
#include "..\Headers\Transform.h"
#include "Terrain.h"
#include "World.h"
USING(MyGame)


CTransform::CTransform(LPDIRECT3DDEVICE9 _pGraphic_Device)
	:CModule(_pGraphic_Device)
{
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

	m_vColliderSize = Vector3((float)TILECX - 5, (float)TILECY - 5, 1.f);

	D3DXMatrixIdentity(&m_StateMatrix);

	return S_OK;
}

//목표지점으로 간다.
_int CTransform::Update(_double _timeDelta)
{
	return Update_Route(_timeDelta);
}

_int CTransform::Late_Update()
{
	_matrix scalingMatrix, rotationXMatrix, rotationYMatrix, rotationZMatrix, translationMatrix;

	D3DXMatrixScaling(&scalingMatrix, m_vSize.x, m_vSize.y, m_vSize.z);
	D3DXMatrixRotationX(&rotationXMatrix, m_vRotation.x);
	D3DXMatrixRotationX(&rotationYMatrix, m_vRotation.y);
	D3DXMatrixRotationX(&rotationZMatrix, m_vRotation.z);
	D3DXMatrixTranslation(&translationMatrix, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_StateMatrix = scalingMatrix * rotationXMatrix * rotationYMatrix * rotationZMatrix * translationMatrix;
	return 0;
}

HRESULT CTransform::Set_Position(Vector3 _vPosition)
{
	m_vPosition = _vPosition;
	m_vPosition.w = 1;
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


void CTransform::FaceDir()
{
	float sizeX = abs(m_vSize.x);

	if (m_vDir.x < 0)
		m_vSize.x = -1 * sizeX;
	else
		m_vSize.x = sizeX;
}

HRESULT CTransform::MoveToTarget(CTransform * _pTransform, _double _timeDelta, _double _StopDistance)
{

	Vector3 vDir = _pTransform->Get_Position() - m_vPosition;

	if (vDir.magnitude() >= m_StopDistance)
	{
		m_vPosition += vDir.nomalize() * float(m_tStateDesc.speedPerSec * _timeDelta);
	}
	return S_OK;

}

HRESULT CTransform::MoveToTarget(CTransform * _pTransform, _double _timeDelta, _double _StopDistance, _double _Speed)
{

	Vector3 vDir = _pTransform->Get_Position() - m_vPosition;

	if (vDir.magnitude() >= m_StopDistance)
	{
		m_vPosition += vDir.nomalize() * float(_Speed * _timeDelta);
	}
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

HRESULT CTransform::MoveToDst(Vector3 _vDst, _double _timeDelta, _double _fStopDistance)
{
	Vector3 vDir = _vDst - m_vPosition;

	if (vDir.magnitude() >= m_StopDistance)
	{
		m_vPosition += vDir.nomalize() * float(m_tStateDesc.speedPerSec * _timeDelta);
	}
	return S_OK;
}

HRESULT CTransform::MoveToDst(Vector3 _vDst, _double _timeDelta, _double _fStopDistance, _double _Speed)
{

	Vector3 vDir = _vDst - m_vPosition;

	if (vDir.magnitude() >= m_StopDistance)
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



HRESULT CTransform::Go_Route(vector<CTerrain*> _route, _double _StopDistance)
{

	if (_route.empty())
		return E_FAIL;


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
	//루트 설정
	CWorld::Get_Instance()->Get_Route(m_vPosition, m_pTarget->Get_Position(), m_Route, this);

	return S_OK;
}


HRESULT CTransform::Update_Route(_double _timeDelta)
{
	if (m_bStop)
		return E_FAIL;


	//행동력만큼 이동하고 멈춤
	if ((m_iTotalMoveCnt >= (_int)m_tStateDesc.movePerTurn) || m_bTurnEnd == true)
	{
		m_bTurnEnd = true;
		m_iTotalMoveCnt = 0;
		return TURN_END;
	}

	//모든 루트를 이동하면 멈춤
	if ((_int)m_iCurrRouteIndex >= m_Route.size())
	{	
		//초기화
		m_bStop = true;
		m_iCurrRouteIndex = 0;
		m_iTotalMoveCnt = 0;
		m_Route.swap(vector<CTerrain*>());
		m_pTarget = nullptr;
		m_bTurnEnd = false;
		return TURN_END;
	}

	CTransform* pTransform = (CTransform*)m_Route[m_iCurrRouteIndex]->Get_Module(L"Transform");
	if (nullptr == pTransform)
		return E_FAIL;

	m_vDir = pTransform->Get_Position() - m_vPosition;

	if (m_vDir.magnitude() > 1.f)
	{
		//가려는 경로를 다시 체크해서 갈 수 있는 곳이면
		if (m_Route[m_iCurrRouteIndex]->IsMovable(this))
		{
			m_vPosition += m_vDir.nomalize() * float(m_tStateDesc.speedPerSec * _timeDelta);
		}
		//갈 수 없으면 루트갱신
		else
		{
			//루트 삭제
			m_Route.swap(vector<CTerrain*>());

			//타겟이 있으면 타겟을 따라가고, 아니면 목표위치로 간다.
			if (m_pTarget != nullptr)
				CWorld::Get_Instance()->Get_Route(m_vPosition, m_pTarget->Get_Position(), m_Route, this);
			else
				CWorld::Get_Instance()->Get_Route(m_vPosition, m_vDst, m_Route, this);

			//루트 인덱스 초기화
			m_iCurrRouteIndex = 0;
		}

		FaceDir();
	}
	//타일에 도달했으면
	else
	{
		//지나간 타일 수 세기
		++m_iTotalMoveCnt;
		//한 타일지나면 인덱스 더하기
		++m_iCurrRouteIndex;

		//타깃을 쫒는 상태라면 (주로 몬스터)
		if (nullptr != m_pTarget)
		{
			//타깃의 위치는 변하기 때문에 루트를 매번 갱신해줘야한다.(한칸 갈때마다)
			m_Route.swap(vector<CTerrain*>());
			CWorld::Get_Instance()->Get_Route(m_vPosition, m_pTarget->Get_Position(), m_Route, this);

			//갱신시에는 루트 인덱스도 초기화
			m_iCurrRouteIndex = 0;
		}
	}
	return S_OK;
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
	CModule::Free();

}

