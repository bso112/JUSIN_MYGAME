#include "stdafx.h"
#include "Menu.h"
#include "Image.h"
#include "MyButton.h"
#include "ObjMgr.h"

USING(MyGame)

CMenu * CMenu::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CMenu* pInstance = new CMenu(_pGraphic_Device);

	if (FAILED(pInstance->Initalize()))
	{
		MSG_BOX("Fail to Create Loading Scene");
		Safe_Release(pInstance);
	}
	return pInstance;
}


HRESULT CMenu::Initalize()
{
	if (FAILED(Initalize_Prototypes()))
		return E_FAIL;

	if (FAILED(Initalize_Layers()))
		return E_FAIL;

	//x 마진 60
	//y 마진 60
	float padding = 30;
	m_pImgLogo = CImage::Create(m_pGraphic_Device, Vector4((float)(g_iWinCX >> 1), 190.f, 0.f, 1.f), Vector2(370.f, 200.f), L"logo");
	m_vecBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding - 50.f, 350.f, 0.f, 1.f), Vector2(100.f, 100.f), CMyButton::BTN_CHARACTER_SELECT, L"character_select"));
	m_vecBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding + 50.f, 350.f, 0.f, 1.f), Vector2(100.f, 100.f), CMyButton::BTN_END, L"Ranking"));
	m_vecBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding - 50.f, 510.f, 0.f, 1.f), Vector2(100.f, 100.f), CMyButton::BTN_EDITOR, L"Badges"));
	m_vecBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding + 50.f, 510.f, 0.f, 1.f), Vector2(100.f, 100.f), CMyButton::BTN_QUIT, L"About"));

	return S_OK;
}

_int CMenu::Update(_double _timeDelta)
{
	CScene::Update(_timeDelta);
	return 0;
}

HRESULT CMenu::Render()
{
	CScene::Render();

	for (auto& btn : m_vecBtn)
	{
		btn->Render();
	}

	m_pImgLogo->Render();

	return 0;
}


HRESULT CMenu::Initalize_Prototypes()
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	return S_OK;
}

void CMenu::Free()
{
	for (auto& btn : m_vecBtn)
	{
		if (0 != Safe_Release(btn))
			MSG_BOX("Fail to Release Btn");
	}

	if (0 != Safe_Release(m_pImgLogo))
		MSG_BOX("Fail to release logo");

	CScene::Free();
}
HRESULT CMenu::Initalize_Layers()
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	return S_OK;
}




