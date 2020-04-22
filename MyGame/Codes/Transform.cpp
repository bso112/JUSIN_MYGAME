#include "stdafx.h"
#include "..\Headers\Transform.h"

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
	m_vPosition = Vector3(0.f, 0.f, 0.f);

	D3DXMatrixIdentity(&m_StateMatrix);
	
	return S_OK;
}

_int CTransform::Update()
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
	return S_OK;
}

HRESULT CTransform::Set_Size(Vector3 _vSize)
{
	m_vSize = _vSize;
	return S_OK;
}

HRESULT CTransform::Set_Roation(Vector3 _vRotation)
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

HRESULT CTransform::MoveToTarget(CTransform * _pTransform, _double _timeDelta, _double _fStopDistance)
{
	Vector3 vDir = _pTransform->Get_Position() - m_vPosition;
	
	if (vDir.magnitude() <= _fStopDistance)
	{
		m_vPosition += vDir.nomalize() * m_tStateDesc.speedPerSec * _timeDelta;
	}
	return S_OK;
}

HRESULT CTransform::MoveToTarget(CTransform * _pTransform, _double _timeDelta, _double _fStopDistance, _double _speed)
{
	Vector3 vDir = _pTransform->Get_Position() - m_vPosition;

	if (vDir.magnitude() <= _fStopDistance)
	{
		m_vPosition += vDir.nomalize() *_speed * _timeDelta;
	}
	return S_OK;
}

HRESULT CTransform::MoveToDir(Vector3 _vDir, _double _timeDelta)
{
	m_vPosition += _vDir.nomalize() * m_tStateDesc.speedPerSec * _timeDelta;
	return S_OK;
}

HRESULT CTransform::MoveToDir(Vector3 _vDir, _double _timeDelta, _double _speed)
{
	m_vPosition += _vDir.nomalize() * _speed * _timeDelta;
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

