#include "stdafx.h"
#include "Menu.h"
#include "Image.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "TextureLoader.h"
#include "ModuleMgr.h"
#include "SceneMgr.h"

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

	for (int i = 0; i < ARC1Y; ++i)
	{
		for (int j = 0; j < ARC1X; ++j)
		{
			m_pImgArc1[i][j] = CImage::Create(m_pGraphic_Device, Vector4((float)(ARC1CX >> 1) + ARC1CX * j, (float)(ARC1CY >> 1) + ARC1CY * i), Vector2(ARC1CX, ARC1CY), L"arcs1", SCENE_MENU);
		}
	}

	for (int i = 0; i < ARC2Y; ++i)
	{
		for (int j = 0; j < ARC2X; ++j)
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
	m_vecMenuBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding - 50.f, 350.f, 0.f, 1.f), Vector2(100.f, 100.f), L"character_select", SCENE_MENU));
	m_vecMenuBtn[0]->Add_Listener([=] { m_iCurrCanvas = 1;});
	m_vecMenuBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding + 50.f, 350.f, 0.f, 1.f), Vector2(100.f, 100.f), L"Ranking", SCENE_MENU));
	m_vecMenuBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding - 50.f, 510.f, 0.f, 1.f), Vector2(100.f, 100.f), L"Badges", SCENE_MENU));
	m_vecMenuBtn[2]->Add_Listener(
		[=]
	{
		if (CSceneMgr::Get_Instance()->Scene_Change(SCENEID::SCENE_EDITOR, m_pGraphic_Device) == S_OK)
			m_bDead = true;
	});
	m_vecMenuBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding + 50.f, 510.f, 0.f, 1.f), Vector2(100.f, 100.f), L"About", SCENE_MENU));


#pragma endregion

#pragma region �����׷�2 �غ�

	//�ΰ����
	m_pImgCharSelectBanner = CImage::Create(m_pGraphic_Device, Vector4((float)(g_iWinCX >> 1), 80.f, 0.f, 1.f), Vector2(450.f, 80.f), L"select_yout_hero", SCENE_MENU);

	//��ư����
	//�߾����� x��ǥ�� ������ ����
	float padding2 = 100;
	m_vecCharSelectBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding2, 250.f, 0.f, 1.f), Vector2(120.f, 180.f), L"avatars_warrior", SCENE_MENU));
	m_vecCharSelectBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding2, 250.f, 0.f, 1.f), Vector2(120.f, 180.f), L"avatars_mage", SCENE_MENU));
	m_vecCharSelectBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding2, 480.f, 0.f, 1.f), Vector2(120.f, 180.f), L"avatars_huntress", SCENE_MENU));
	m_vecCharSelectBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding2, 480.f, 0.f, 1.f), Vector2(120.f, 180.f), L"avatars_rogue", SCENE_MENU));

	CMyButton* pBtn = CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - 10 - 100.f, 660.f, 0.f, 1.f), Vector2(200.f, 80.f), L"RedButton", SCENE_MENU);
	pBtn->Set_Text(L"Game Load");
	m_vecCharSelectBtn.push_back(pBtn);
	pBtn = CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + 10 + 100.f, 660.f, 0.f, 1.f), Vector2(200.f, 80.f), L"RedButton", SCENE_MENU);
	pBtn->Set_Text(L"Game Start");
	m_vecCharSelectBtn.push_back(pBtn);


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


	for (int i = 0; i < ARC2Y; ++i)
	{
		for (int j = 0; j < ARC2X; ++j)
		{
			CTransform* pTransform = (CTransform*)(m_pImgArc2[i][j]->Get_Module(L"Transform"));

			if (pTransform == nullptr)
				return -1;


			//���� ���翭�� �ٴ��� õ�忡 ������ �����ϴ� ���� �ٷ� ������ ��ġ�� �����Ѵ�.
			//0���� ���������� ������ �̵��Ѵ�.

			if (pTransform->Get_Position().y + (ARC2CY >> 1) < 0)
			{
				CTransform* pLastArcTransform = nullptr;

				if(i == 0)
					pLastArcTransform = (CTransform*)(m_pImgArc2[ARC2Y-1][j]->Get_Module(L"Transform"));
				else
					pLastArcTransform = (CTransform*)(m_pImgArc2[i-1][j]->Get_Module(L"Transform"));

				if (pLastArcTransform == nullptr)
					return -1;

				Vector3 vLastArcPos = pLastArcTransform->Get_Position();
				pTransform->Set_Position(Vector3(vLastArcPos.x, vLastArcPos.y + ARC2CY));
			}

			pTransform->MoveToDir(Vector3(0, -1), _timeDelta, 30.f);
			m_pImgArc2[i][j]->Update(_timeDelta);

		}
	}


	for (int i = 0; i < ARC1Y; ++i)
	{
		for (int j = 0; j < ARC1X; ++j)
		{
			CTransform* pTransform = (CTransform*)(m_pImgArc1[i][j]->Get_Module(L"Transform"));

			if (pTransform == nullptr)
				return -1;


			//���� ���翭�� �ٴ��� õ�忡 ������ �����ϴ� ���� �ٷ� ������ ��ġ�� �����Ѵ�.
			//0���� ���������� ������ �̵��Ѵ�.

			if (pTransform->Get_Position().y + (ARC1CY >> 1) < 0)
			{
				CTransform* pLastArcTransform = nullptr;

				if (i == 0)
					pLastArcTransform = (CTransform*)(m_pImgArc1[ARC1Y-1][j]->Get_Module(L"Transform"));
				else
					pLastArcTransform = (CTransform*)(m_pImgArc1[i - 1][j]->Get_Module(L"Transform"));

				if (pLastArcTransform == nullptr)
					return -1;

				Vector3 vLastArcPos = pLastArcTransform->Get_Position();
				pTransform->Set_Position(Vector3(vLastArcPos.x, vLastArcPos.y + ARC1CY));
			}

			pTransform->MoveToDir(Vector3(0, -1), _timeDelta, 100.f);
			m_pImgArc1[i][j]->Update(_timeDelta);
		}
	}

	for (auto& obj : m_vecCanvas[m_iCurrCanvas])
	{
		obj->Update(_timeDelta);
		if (m_bDead)
			return -1;
	}

	CScene::Update(_timeDelta);
	return 0;
}

HRESULT CMenu::Render()
{
	CScene::Render();

	for (int i = 0; i < ARC2Y; ++i)
	{
		for (int j = 0; j < ARC2X; ++j)
		{
			m_pImgArc2[i][j]->Render();
		}
	}

	for (int i = 0; i < ARC1Y; ++i)
	{
		for (int j = 0; j < ARC1X; ++j)
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

	for (int i = 0; i < ARC1Y; ++i)
	{
		for (int j = 0; j < ARC1X; ++j)
		{
			if (0 != Safe_Release(m_pImgArc1[i][j]))
				MSG_BOX("Fail to Release Arc1");
		}
	}

	for (int i = 0; i < ARC2Y; ++i)
	{
		for (int j = 0; j < ARC2X; ++j)
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


