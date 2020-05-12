#include "stdafx.h"
#include "Transform.h"
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

HRESULT CTransform::Add_Force(Vector3 _vDir, _float _fForce, _double _timeDelta)
{
	m_vPosition += _vDir * _fForce * float(_timeDelta);
	return S_OK;
}

HRESULT CTransform::Add_Force(Vector2 _vForce)
{
	m_vPosition.x += _vForce.x;
	m_vPosition.y += _vForce.y;
	return E_NOTIMPL;
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

