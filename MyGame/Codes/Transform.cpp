#include "stdafx.h"
#include "..\Headers\Transform.h"

USING(MyGame)


CTransform::CTransform(LPDIRECT3DDEVICE9 _pGraphic_Device)
	:CModule(_pGraphic_Device)
{
}

CTransform::CTransform(CTransform & _module)
	:CModule(_module)
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
	memcpy(&m_StateMatrix.m[3], Vector4(g_iWinCX>>1, g_iWinCY>>1, 0.f, 1.f), sizeof(Vector4));

	return S_OK;
}

HRESULT CTransform::Set_Position(Vector4 _vPosition)
{
	memcpy(&m_StateMatrix.m[3], _vPosition, sizeof(Vector4));
	return S_OK;
}

CTransform * CTransform::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	CTransform* pInstance = new CTransform(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create VIBuffer");
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
		MSG_BOX("Fail to clone VIBuffer");
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

void CTransform::Free()
{
	CModule::Free();

}

