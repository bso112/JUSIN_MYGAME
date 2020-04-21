#include "stdafx.h"
#include "Menu.h"
#include "Image.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "TextureLoader.h"
#include "ModuleMgr.h"

USING(MyGame)

CMenu * CMenu::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CMenu* pInstance = new CMenu(_pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail to Create Loading Scene");
		Safe_Release(pInstance);
	}
	return pInstance;
}


CMenu::CMenu(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CScene(_pGraphic_Device)
{
	ZeroMemory(m_pImgArc1, sizeof(m_pImgArc1));
	ZeroMemory(m_pImgArc2, sizeof(m_pImgArc2));

}


HRESULT CMenu::Initialize()
{
	//�ؽ��� �ε�
	if (FAILED(Load_Textures()))
		return E_FAIL;


#pragma region ��׶����غ�

	for (int i = 0; i < ARC1X; ++i)
	{
		for (int j = 0; j < ARC1Y; ++j)
		{
			m_pImgArc1[i][j] = CImage::Create(m_pGraphic_Device, Vector4((float)(ARC1CX >> 1) + ARC1CX * j, (float)(ARC1CY >> 1) + ARC1CY * i), Vector2(ARC1CX, ARC1CY), L"arcs1", SCENE_MENU);
		}
	}

	for (int i = 0; i < ARC2X; ++i)
	{
		for (int j = 0; j < ARC2Y; ++j)
		{
			m_pImgArc2[i][j] = CImage::Create(m_pGraphic_Device, Vector4((float)(ARC2CX >> 1) + ARC2CX * j, (float)(ARC2CY >> 1) + ARC2CY * i), Vector2(ARC2CX, ARC2CY), L"arcs2", SCENE_MENU);
		}
	}

#pragma endregion

#pragma region �����׷� 1 �غ�
	//�ΰ����
	m_pImgLogo = CImage::Create(m_pGraphic_Device, Vector4((float)(g_iWinCX >> 1), 190.f, 0.f, 1.f), Vector2(370.f, 200.f), L"logo", SCENE_MENU);
	//��ư����
	float padding = 30;
	m_vecMenuBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding - 50.f, 350.f, 0.f, 1.f), Vector2(100.f, 100.f), CMyButton::BTN_CHARACTER_SELECT, L"character_select", SCENE_MENU));
	m_vecMenuBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding + 50.f, 350.f, 0.f, 1.f), Vector2(100.f, 100.f), CMyButton::BTN_END, L"Ranking", SCENE_MENU));
	m_vecMenuBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding - 50.f, 510.f, 0.f, 1.f), Vector2(100.f, 100.f), CMyButton::BTN_EDITOR, L"Badges", SCENE_MENU));
	m_vecMenuBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding + 50.f, 510.f, 0.f, 1.f), Vector2(100.f, 100.f), CMyButton::BTN_QUIT, L"About", SCENE_MENU));


#pragma endregion

#pragma region �����׷�2 �غ�

	//�ΰ����
	m_pImgCharSelectBanner = CImage::Create(m_pGraphic_Device, Vector4((float)(g_iWinCX >> 1), 80.f, 0.f, 1.f), Vector2(450.f, 80.f), L"select_yout_hero", SCENE_MENU);
	//��ư����

	//�߾����� x��ǥ�� ������ ����
	float padding2 = 100;
	m_vecCharSelectBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding2, 250.f, 0.f, 1.f), Vector2(120.f, 180.f), CMyButton::BTN_CHARACTER_SELECT, L"avatars_warrior", SCENE_MENU));
	m_vecCharSelectBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding2, 250.f, 0.f, 1.f), Vector2(120.f, 180.f), CMyButton::BTN_END, L"avatars_mage", SCENE_MENU));
	m_vecCharSelectBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding2, 480.f, 0.f, 1.f), Vector2(120.f, 180.f), CMyButton::BTN_QUIT, L"avatars_huntress", SCENE_MENU));
	m_vecCharSelectBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding2, 480.f, 0.f, 1.f), Vector2(120.f, 180.f), CMyButton::BTN_EDITOR, L"avatars_rogue", SCENE_MENU));
	m_vecCharSelectBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - 10 - 100.f, 660.f, 0.f, 1.f), Vector2(200.f, 80.f), CMyButton::BTN_CHARACTER_SELECT, L"RedButton", SCENE_MENU));
	m_vecCharSelectBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + 10 + 100.f, 660.f, 0.f, 1.f), Vector2(200.f, 80.f), CMyButton::BTN_CHARACTER_SELECT, L"RedButton", SCENE_MENU));

#pragma endregion

	m_vecCanvas[0].push_back(m_pImgLogo);

	for (auto& btn : m_vecMenuBtn)
		m_vecCanvas[0].push_back(btn);
	
	m_vecCanvas[1].push_back(m_pImgCharSelectBanner);

	for (auto& btn : m_vecCharSelectBtn)
		m_vecCanvas[1].push_back(btn);



	return S_OK;
}

_int CMenu::Update(_double _timeDelta)
{
	for (auto& obj : m_vecCanvas[m_iCurrCanvas])
	{
		_short msg = obj->Update(_timeDelta);
		//���� ��ư���� ��ü���� �ϸ�, �� ���ο��� ���� �������� ������ ����
		if (msg & 0x8000)
			return -1;

		//���� ��ư�� ĳ���� ����Ʈ��ư�̸�
		if (msg == CMyButton::BTN_CHARACTER_SELECT)
		{
			m_iCurrCanvas = 1;
		}
	}

	CScene::Update(_timeDelta);
	return 0;
}

HRESULT CMenu::Render()
{
	CScene::Render();

	for (int i = 0; i < ARC2X; ++i)
	{
		for (int j = 0; j < ARC2Y; ++j)
		{
			m_pImgArc2[i][j]->Render();
		}
	}

	for (int i = 0; i < ARC1X; ++i)
	{
		for (int j = 0; j < ARC1Y; ++j)
		{
			m_pImgArc1[i][j]->Render();
		}
	}

	for (auto& obj : m_vecCanvas[m_iCurrCanvas])
	{
		obj->Render();
	}

	return 0;
}

HRESULT CMenu::Load_Textures()
{
	CTextureLoader* pLoader = CTextureLoader::Get_Instance();

	if (nullptr == pLoader)
		return E_FAIL;

	Safe_AddRef(pLoader);

	pLoader->Create_Textrues_From_Folder(m_pGraphic_Device, SCENEID::SCENE_MENU, L"../Bin/Resources/Textures/UI/Menu/");

	Safe_Release(pLoader);
	return S_OK;
}



void CMenu::Free()
{

	for (int i = 0; i < ARC1X; ++i)
	{
		for (int j = 0; j < ARC1Y; ++j)
		{
			if (0 != Safe_Release(m_pImgArc1[i][j]))
				MSG_BOX("Fail to Release Arc1");
		}
	}

	for (int i = 0; i < ARC2X; ++i)
	{
		for (int j = 0; j < ARC2Y; ++j)
		{
			if (0 != Safe_Release(m_pImgArc2[i][j]))
				MSG_BOX("Fail to Release Arc2");
		}
	}

	for (auto& canvas : m_vecCanvas)
	{
		for (auto& obj : canvas)
		{
			if (0 != Safe_Release(obj))
				MSG_BOX("Fail to release canvas");
		}
		canvas.clear();
	}

	if (FAILED(CObjMgr::Get_Instance()->Clear_Scene(SCENEID::SCENE_MENU)))
		MSG_BOX("Fail to Clear GameObject Prototypes");

	if (FAILED(CModuleMgr::Get_Instance()->Clear_Scene(SCENEID::SCENE_MENU)))
		MSG_BOX("Fail to Clear Module Prototypes");

	CScene::Free();
}


