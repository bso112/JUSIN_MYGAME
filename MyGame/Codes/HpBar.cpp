#include "stdafx.h"
#include "..\Headers\HpBar.h"
#include "Transform.h"
#include "VIBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Character.h"
#include "Stat.h"

USING(MyGame)

CHpBar::CHpBar(PDIRECT3DDEVICE9 _pGraphic_Device)
	: CImage(_pGraphic_Device)
{

};

CHpBar::CHpBar(CHpBar & _rhs)
	: CImage(_rhs)
{

};

HRESULT CHpBar::Initialize_Prototype(const _tchar * _pTextureTag, Vector4 _vPos, Vector2 _vSize, SCENEID _eTextureSceneID)
{
	CImage::Initialize_Prototype(_pTextureTag, _vPos, _vSize, _eTextureSceneID);
	if (0 == lstrcmp(_pTextureTag, L"hp_bar"))
	{
		m_eRenderGroup = CRenderer::RENDER_UI;
		m_iDepth = 10;
	}
	return S_OK;
}

HRESULT CHpBar::Render()
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pVIBuffer ||
		nullptr == m_pTextrue ||
		nullptr == m_pTransform ||
		nullptr == m_pPipline)
		return E_FAIL;


	ALPHABLEND;
	_matrix matrix;
	if (m_bUI)
		matrix = m_pTransform->Get_Matrix();
	else
		matrix = m_pTransform->Get_Matrix() * m_pPipline->Get_ViewMatrix();

	if (FAILED(m_pVIBuffer->Set_Transform(matrix)))
		return E_FAIL;

	if (FAILED(m_pTextrue->Set_TextureOnShader(m_pShader, "g_BaseTexture", m_iTextureID - 1)))
		return E_FAIL;



	if (FAILED(m_pShader->Set_Value("g_fCurrHp", &m_fHp, sizeof(float))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_Value("g_fMaxHp", &m_fMaxHp, sizeof(float))))
		return E_FAIL;

	if (FAILED(m_pShader->Begin()))
		return E_FAIL;
	if (FAILED(m_pShader->Begin_Pass(5)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;


	//하위클래스의 렌더
	OnRender();


	if (FAILED(m_pShader->End_Pass()))
		return E_FAIL;
	if (FAILED(m_pShader->End()))
		return E_FAIL;

	//원래대로 돌려놓기
	float tmp = 1.f;
	if (FAILED(m_pShader->Set_Value("g_fCurrHp", &tmp, sizeof(float))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_Value("g_fMaxHp", &tmp, sizeof(float))))
		return E_FAIL;

	ALPHABLEND_END;



	return S_OK;
}

CHpBar* CHpBar::Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, const _tchar* _pTextureTag, SCENEID _eTextureSceneID)
{
	CHpBar* pInstance = new CHpBar(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pTextureTag, _vPos, _vSize, _eTextureSceneID)))
	{
		MSG_BOX("Fail to create CHpBar");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CHpBar* CHpBar::Create(PDIRECT3DDEVICE9 _pGraphic_Device, void* _desc)
{
	CHpBar* pInstance = new CHpBar(_pGraphic_Device);
	if (FAILED(pInstance->CImage::Initialize_Prototype(_desc)))
	{
		MSG_BOX("Fail to create CHpBar");
		Safe_Release(pInstance);

	}
	return pInstance;
}



CGameObject* CHpBar::Clone(void* _param)
{
	CHpBar* pInstance = new CHpBar(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create CHpBar");
		Safe_Release(pInstance);

	}

	return pInstance;
}

void CHpBar::Free()
{
	CImage::Free();
}
