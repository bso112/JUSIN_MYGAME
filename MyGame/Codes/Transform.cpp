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
	memcpy(&m_StateMatrix.m[0], Vector4(1.f, 0.f, 0.f, 0.f), sizeof(Vector4));
	memcpy(&m_StateMatrix.m[1], Vector4(0.f, 1.f, 0.f, 0.f), sizeof(Vector4));
	memcpy(&m_StateMatrix.m[2], Vector4(0.f, 0.f, 1.f, 0.f), sizeof(Vector4));
	memcpy(&m_StateMatrix.m[3], Vector4(0.f, 0.f, 0.f, 1.f), sizeof(Vector4));

	m_BaseMatrix = m_StateMatrix;
	return S_OK;
}

HRESULT CTransform::Set_Position(Vector4 _vPosition)
{
	memcpy(&m_StateMatrix.m[3], _vPosition, sizeof(Vector4));
	return S_OK;
}

HRESULT CTransform::Set_Size(Vector4 _vSize)
{
	m_StateMatrix.m[0][0] = m_BaseMatrix.m[0][0] * _vSize.x;
	m_StateMatrix.m[0][1] = m_BaseMatrix.m[0][1] * _vSize.x;
	m_StateMatrix.m[0][2] = m_BaseMatrix.m[0][2] * _vSize.x;

	m_StateMatrix.m[1][0] = m_BaseMatrix.m[1][0] * _vSize.y;
	m_StateMatrix.m[1][1] = m_BaseMatrix.m[1][1] * _vSize.y;
	m_StateMatrix.m[1][2] = m_BaseMatrix.m[1][2] * _vSize.y;

	m_StateMatrix.m[2][0] = m_BaseMatrix.m[2][0] * _vSize.z;
	m_StateMatrix.m[2][1] = m_BaseMatrix.m[2][1] * _vSize.z;
	m_StateMatrix.m[2][2] = m_BaseMatrix.m[2][2] * _vSize.z;

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

