#include "stdafx.h"
#include "..\Headers\CharacterSelect.h"
#include "TextureLoader.h"
#include "Image.h"
#include "MyButton.h"

USING(MyGame)

HRESULT CCharacterSelect::Initialize()
{
	if (FAILED(Load_Textures()))
		return E_FAIL;

	//肺绊积己
	m_pImgLogo = CImage::Create(m_pGraphic_Device, Vector4((float)(g_iWinCX >> 1), 190.f, 0.f, 1.f), Vector2(370.f, 200.f), L"logo", SCENE_MENU);
	//滚瓢积己
	float padding = 30;
	m_vecBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding - 50.f, 350.f, 0.f, 1.f), Vector2(100.f, 100.f),  L"character_select", SCENE_MENU));
	m_vecBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding + 50.f, 350.f, 0.f, 1.f), Vector2(100.f, 100.f),  L"Ranking", SCENE_MENU));
	m_vecBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding - 50.f, 510.f, 0.f, 1.f), Vector2(100.f, 100.f), CMyButton::BTN_EDITOR, L"Badges", SCENE_MENU));
	m_vecBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding + 50.f, 510.f, 0.f, 1.f), Vector2(100.f, 100.f), CMyButton::BTN_QUIT, L"About", SCENE_MENU));



	return S_OK;
}

_int CCharacterSelect::Update(_double _timeDelta)
{
	return _int();
}

HRESULT CCharacterSelect::Render()
{
	return S_OK;
}

HRESULT CCharacterSelect::Load_Textures()
{
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder(m_pGraphic_Device, SCENEID::SCENE_CHARACTER_SELECT, L"../Bin/Resources/Textures/UI/Character_Select/");
	return S_OK;
}

CCharacterSelect* CCharacterSelect::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CCharacterSelect* pInstance = new CCharacterSelect(_pGraphic_Device);
	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail to create CCharacterSelect");
		Safe_Release(pInstance);

	}
	return pInstance;
}
