#include "stdafx.h"
#include "Texture.h"

USING(MyGame)

CTexture::CTexture(CTexture & _rhs)
	:CModule(_rhs),
	m_vecTexture(_rhs.m_vecTexture)
{
	for (auto& texture : m_vecTexture)
	{
		Safe_AddRef(texture);
	}
}

HRESULT CTexture::Initialize_Prototype(const _tchar* _pFilePath, _uint _iCnt)
{
	m_vecTexture.reserve(_iCnt);
	for (_uint i = 0; i < _iCnt; ++i)
	{
		_tchar szBuff[MAX_PATH] = L"";
		wsprintf(szBuff, _pFilePath, i);
		LPDIRECT3DTEXTURE9 pTexture = nullptr;
		if(FAILED(D3DXCreateTextureFromFile(m_pGraphic_Device, szBuff, &pTexture)))
			return E_FAIL;

		m_vecTexture.push_back(pTexture);
	}
	return S_OK;
}

HRESULT CTexture::Initialize(void * _pArg)
{
	return S_OK;
}

HRESULT CTexture::Set_Texture(_uint _iIndex)
{
	if (m_vecTexture.size() <= _iIndex ||
		nullptr == m_pGraphic_Device)
		return E_FAIL;

	if(FAILED(m_pGraphic_Device->SetTexture(0, m_vecTexture[_iIndex])))
		return E_FAIL;

	return S_OK;
}


CTexture * CTexture::Create(PDIRECT3DDEVICE9 _pGraphic_Device, _tchar* _pFilePath, _uint _iCnt)
{
	CTexture* pInstance = new CTexture(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pFilePath, _iCnt)))
	{
		MSG_BOX("Fail to create CTexture");
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CModule * CTexture::Clone(void * _pArg)
{
	CTexture* pInstance = new CTexture(*this);

	if (FAILED(pInstance->Initialize(_pArg)))
	{
		MSG_BOX("Fail to clone CTexture");
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

void CTexture::Free()
{
	for (auto texture : m_vecTexture)
	{
		Safe_Release(texture);
	}

	m_vecTexture.clear();

	CModule::Free();
}
