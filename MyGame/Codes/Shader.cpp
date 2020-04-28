#include "stdafx.h"
#include "..\Headers\Shader.h"

USING(MyGame)

CShader::CShader(LPDIRECT3DDEVICE9 _pGraphic_Device)
	:CModule(_pGraphic_Device)
{

}

CShader::CShader(CShader & _module)
	:CModule(_module),
	m_pEffect(_module.m_pEffect)
{
	Safe_AddRef(m_pEffect);
}

HRESULT CShader::Initialize_Prototype(_tchar* pFilePath)
{
	if (FAILED(D3DXCreateEffectFromFile(m_pGraphic_Device, pFilePath, nullptr, nullptr, 0, nullptr, &m_pEffect, nullptr)))
		return E_FAIL;

	return S_OK;
}

HRESULT CShader::Initialize(void * _pArg)
{
	return S_OK;
}

HRESULT CShader::Set_Texture(D3DXHANDLE hParameter, LPDIRECT3DTEXTURE9 pTexture)
{
	if (nullptr == m_pEffect)
		return E_FAIL;
	return m_pEffect->SetTexture(hParameter, pTexture);
}

HRESULT CShader::Set_Value(D3DXHANDLE hParameter, void * _pValue, _uint _iSize)
{
	if (nullptr == m_pEffect)
		return E_FAIL;
	return m_pEffect->SetValue(hParameter, _pValue, _iSize);
}

HRESULT CShader::Begin()
{
	if (nullptr == m_pEffect)
		return E_FAIL;
	return m_pEffect->Begin(nullptr, 0);
}

HRESULT CShader::End()
{
	if (nullptr == m_pEffect)
		return E_FAIL;
	return m_pEffect->End();
}

HRESULT CShader::Begin_Pass(_uint _iIndex)
{
	if (nullptr == m_pEffect)
		return E_FAIL;
	return m_pEffect->BeginPass(_iIndex);
}

HRESULT CShader::End_Pass()
{
	if (nullptr == m_pEffect)
		return E_FAIL;
	return m_pEffect->EndPass();
}

CShader * CShader::Create(LPDIRECT3DDEVICE9 _pGraphic_Device, _tchar* pFilePath)
{
	CShader* pInstance = new CShader(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(pFilePath)))
	{
		MSG_BOX("Fail to create Shader");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CModule * CShader::Clone(void * _pArg)
{
	CShader* pInstance = new CShader(*this);
	if (FAILED(pInstance->Initialize(_pArg)))
	{
		MSG_BOX("Fail to create Shader");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CShader::Free()
{
	Safe_Release(m_pEffect);
	CModule::Free();
}
