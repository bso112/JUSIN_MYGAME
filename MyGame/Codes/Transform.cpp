#include "stdafx.h"
#include "..\Headers\Transform.h"
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

	D3DXMatrixIdentity(&m_StateMatrix);

	return S_OK;
}

//목표지점으로 간다.
_int CTransform::Update(_double _timeDelta)
{
	if (m_bStop)
		return -1;


	//이동력만큼 이동하고 멈춤
	if ((_int)m_iCurrRouteIndex >= m_Route.size() || m_iCurrRouteIndex >= (_int)m_tStateDesc.movePerTurn * m_iTurnCnt)
	{
		m_bStop = true;
		m_iCurrRouteIndex = 0;
		m_iTurnCnt = 0;
		m_Route.swap(vector<Vector3>());
		m_pTarget = nullptr;
		return -1;
	}

	Vector3 vDir = m_Route[m_iCurrRouteIndex] - m_vPosition;

	if (vDir.magnitude() > m_StopDistance)
	{
		m_vPosition += vDir.nomalize() * float(m_tStateDesc.speedPerSec * _timeDelta);
	}
	//타일에 도달했으면
	else
	{
		//타깃을 쫒는 상태라면
		if (nullptr != m_pTarget)
		{
			//루트 갱신
			m_Route.swap(vector<Vector3>());
			CWorld::Get_Instance()->Get_Route(m_vPosition, m_pTarget->Get_Position(), m_Route);
		}


		//한 타일지나면 인덱스 더하기
		++m_iCurrRouteIndex;
	}
	return 0;
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


RECT CTransform::Get_Rect()
{
	RECT rc = {};
	float fX = Get_Position().x;
	float fY = Get_Position().y;
	int iCX = (int)Get_Size().x;
	int iCY = (int)Get_Size().y;

	rc.left = (LONG)fX - (iCX >> 1);
	rc.right = (LONG)fX + (iCX >> 1);
	rc.top = (LONG)fY - (iCY >> 1);
	rc.bottom = (LONG)fY + (iCY >> 1);
	return rc;
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

HRESULT CTransform::MoveToTarget_Auto(CTransform * _pTransform, _double _fStopDistance)
{
	m_bStop = false;
	m_Route.push_back(_pTransform->Get_Position());
	m_StopDistance = _fStopDistance;
	return S_OK;
}

HRESULT CTransform::MoveToDir_Auto(Vector3 _vDir)
{
	m_bStop = false;
	m_Route.push_back(_vDir * FLT_MAX);
	m_StopDistance = DBL_MAX;
	return S_OK;
}



HRESULT CTransform::MoveToDst_Auto(Vector3 _vDst, _double _StopDistance)
{
	m_bStop = false;
	m_Route.push_back(_vDst);
	m_StopDistance = _StopDistance;
	return S_OK;
}

HRESULT CTransform::Go_Route(vector<Vector3> _route, _double _StopDistance, _int _iTurnCnt)
{
	m_bStop = false;
	m_Route = _route;
	m_StopDistance = _StopDistance;
	m_iTurnCnt = _iTurnCnt;
	return S_OK;
}

HRESULT CTransform::Go_Target(CTransform * _pTarget, _double _StopDistance, _int _iTurnCnt)
{
	if (nullptr == _pTarget)
		return E_FAIL;

	m_bStop = false;
	m_pTarget = _pTarget;
	m_StopDistance = _StopDistance;
	m_iTurnCnt = _iTurnCnt;
	//루트 설정
	CWorld::Get_Instance()->Get_Route(m_vPosition, m_pTarget->Get_Position(), m_Route);

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

