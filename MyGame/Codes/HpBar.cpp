#include "stdafx.h"
#include "..\Headers\HpBar.h"
#include "Transform.h"
#include "VIBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Character.h"
#include "Stat.h"

USING(MyGame)

HRESULT CHpBar::Render()
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pVIBuffer ||
		nullptr == m_pTextrue ||
		nullptr == m_pTransform ||
		nullptr == m_pPipline	||
		nullptr == m_pOwner)
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

	//쉐이더에 Hp 셋팅하기
	CCharacter::STATS tStats = m_pOwner->Get_Stat();
	float fMaxHp = tStats.m_fMaxHp->GetValue();
	float fCurrHp = tStats.m_fHP;

	if (FAILED(m_pShader->Set_Value("g_fCurrHp", &fCurrHp, sizeof(float))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_Value("g_fMaxHp", &fMaxHp, sizeof(float))))
		return E_FAIL;

	if (FAILED(m_pShader->Begin()))
		return E_FAIL;
	if (FAILED(m_pShader->Begin_Pass(5)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

	if (m_bUI)
		m_tFont.m_tRC = m_pTransform->Get_RECT();
	else
		//매트릭스 곱한 위치를 써야함
		m_tFont.m_tRC = m_pTransform->Make_Rect(Vector3(matrix.m[3][0], matrix.m[3][1]), m_pTransform->Get_Size());


	//텍스트는 _tchar 배열일수도, 상수문자열 일수도 있다. 상수문자열이 지정안되어있으면 _tchar 배열을 사용하도록하자.
	const _tchar* szBuff = (m_tFont.m_pText == nullptr) ? m_tFont.m_pTextArr : m_tFont.m_pText;

	//따로 지정한 폰트가 있으면 그 폰트로 그린다.
	if (nullptr != m_tFont.m_pFont)
		m_tFont.m_pFont->DrawText(NULL, szBuff, -1, &m_tFont.m_tRC, m_tFont.m_dwFormat, m_tFont.m_Color);
	else
		g_pFont->DrawText(NULL, szBuff, -1, &m_tFont.m_tRC, m_tFont.m_dwFormat, m_tFont.m_Color);


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
	if (FAILED(pInstance->Initialize_Prototype(_desc)))
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
	Safe_Release(m_pOwner);
	CImage::Free();
}
