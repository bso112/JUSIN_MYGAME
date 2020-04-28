#include "stdafx.h"
#include "Menu.h"
#include "Image.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "TextureLoader.h"
#include "ModuleMgr.h"
#include "SceneMgr.h"
#include "Statics.h"


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
	//텍스쳐 로드
	if (FAILED(Load_Textures()))
		return E_FAIL;

	CMyButton* pBtn = nullptr;

#pragma region 백그라운드준비

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

#pragma region 렌더그룹 1 준비	
	//로고생성
	m_pImgLogo = CImage::Create(m_pGraphic_Device, Vector4((float)(g_iWinCX >> 1), 190.f, 0.f, 1.f), Vector2(370.f, 200.f), L"logo", SCENE_MENU);
	//버튼생성
	float padding = 30;
	float text_pitch1 = 70;
	m_vecMenuBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding - 50.f, 350.f, 0.f, 1.f), Vector2(100.f, 100.f), L"character_select", SCENE_MENU));
	m_vecMenuBtn[0]->Add_Listener([=] { m_iCurrCanvas = 1;});
	pBtn = CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding - 50.f, 350.f + text_pitch1, 0.f, 1.f), Vector2(100.f, 100.f), L"empty_bound", SCENE_MENU);
	pBtn->Set_Text(L"Play");
	m_vecMenuBtn.push_back(pBtn);


	pBtn->Set_InstanceID(1);


	m_vecMenuBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding + 50.f, 350.f, 0.f, 1.f), Vector2(100.f, 100.f), L"Ranking", SCENE_MENU));
	pBtn = CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding + 50.f, 350.f + text_pitch1, 0.f, 1.f), Vector2(100.f, 100.f), L"empty_bound", SCENE_MENU);
	pBtn->Set_Text(L"Ranking");
	m_vecMenuBtn.push_back(pBtn);

	m_vecMenuBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding - 50.f, 510.f, 0.f, 1.f), Vector2(100.f, 100.f), L"Badges", SCENE_MENU));

	m_vecMenuBtn[4]->Add_Listener(
		[=]
	{
		CSceneMgr::Get_Instance()->Scene_Change(SCENEID::SCENE_EDITOR, m_pGraphic_Device);
	});


	pBtn = CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding - 50.f, 510.f + text_pitch1, 0.f, 1.f), Vector2(100.f, 100.f), L"empty_bound", SCENE_MENU);
	pBtn->Set_Text(L"Editor");
	m_vecMenuBtn.push_back(pBtn);

	m_vecMenuBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding + 50.f, 510.f, 0.f, 1.f), Vector2(100.f, 100.f), L"About", SCENE_MENU));
	pBtn = CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding + 50.f, 510.f + text_pitch1, 0.f, 1.f), Vector2(100.f, 100.f), L"empty_bound", SCENE_MENU);
	pBtn->Set_Text(L"Exit");
	m_vecMenuBtn.push_back(pBtn);

#pragma endregion

#pragma region 렌더그룹2 준비

	//로고생성
	m_pImgCharSelectBanner = CImage::Create(m_pGraphic_Device, Vector4((float)(g_iWinCX >> 1), 80.f, 0.f, 1.f), Vector2(450.f, 80.f), L"select_your_hero", SCENE_MENU);

	//버튼생성
	//중앙으로 x좌표가 떨어진 정도
	float padding2 = 100.f;
	//텍스트가 y좌표로 떨어진 정도
	float text_pitch = 100.f;
	m_vecCharSelectBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding2, 250.f, 0.f, 1.f), Vector2(120.f, 180.f), L"avatars_warrior", SCENE_MENU));
	pBtn = CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding2, 250.f + text_pitch, 0.f, 1.f), Vector2(120.f, 180.f), L"empty", SCENE_MENU);
	pBtn->Set_Text(L"WARRIOR");
	m_vecCanvas[1].push_back(pBtn);

	m_vecCharSelectBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding2, 250.f, 0.f, 1.f), Vector2(120.f, 180.f), L"avatars_mage", SCENE_MENU));
	pBtn = CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding2, 250.f + text_pitch, 0.f, 1.f), Vector2(120.f, 180.f), L"empty", SCENE_MENU);
	pBtn->Set_Text(L"MAGE");
	m_vecCanvas[1].push_back(pBtn);

	m_vecCharSelectBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding2, 480.f, 0.f, 1.f), Vector2(120.f, 180.f), L"avatars_huntress", SCENE_MENU));
	pBtn = CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + padding2, 480.f + text_pitch, 0.f, 1.f), Vector2(120.f, 180.f), L"empty", SCENE_MENU);
	pBtn->Set_Text(L"HUNTRESS");
	m_vecCanvas[1].push_back(pBtn);

	m_vecCharSelectBtn.push_back(CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding2, 480.f, 0.f, 1.f), Vector2(120.f, 180.f), L"avatars_rogue", SCENE_MENU));
	pBtn = CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - padding2, 480.f + text_pitch, 0.f, 1.f), Vector2(120.f, 180.f), L"empty", SCENE_MENU);
	pBtn->Set_Text(L"ROUGUE");
	m_vecCanvas[1].push_back(pBtn);


	pBtn = CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) - 10 - 100.f, 660.f, 0.f, 1.f), Vector2(200.f, 80.f), L"RedButton", SCENE_MENU);
	pBtn->Set_Text(L"Game Load");
	m_vecCanvas[1].push_back(pBtn);
	pBtn = CMyButton::Create(m_pGraphic_Device, Vector4((g_iWinCX >> 1) + 10 + 100.f, 660.f, 0.f, 1.f), Vector2(200.f, 80.f), L"RedButton", SCENE_MENU);
	pBtn->Set_Text(L"Game Start");
	pBtn->Add_Listener([&] {CSceneMgr::Get_Instance()->Scene_Change(SCENEID::SCENE_STAGE, m_pGraphic_Device);});
	m_vecCanvas[1].push_back(pBtn);

#pragma endregion

	m_vecCanvas[0].push_back(m_pImgLogo);

	for (auto& btn : m_vecMenuBtn)
		m_vecCanvas[0].push_back(btn);

	m_vecCanvas[1].push_back(m_pImgCharSelectBanner);

	//for (auto& btn : m_vecCharSelectBtn)
	//	m_vecCanvas[1].push_back(btn);



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


			//만약 현재열의 바닥이 천장에 닿으면 선행하는 열의 바로 밑으로 위치를 변경한다.
			//0열만 마지막열의 밑으로 이동한다.

			if (pTransform->Get_Position().y + (ARC2CY >> 1) < 0)
			{
				CTransform* pLastArcTransform = nullptr;

				if (i == 0)
					pLastArcTransform = (CTransform*)(m_pImgArc2[ARC2Y - 1][j]->Get_Module(L"Transform"));
				else
					pLastArcTransform = (CTransform*)(m_pImgArc2[i - 1][j]->Get_Module(L"Transform"));

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


			//만약 현재열의 바닥이 천장에 닿으면 선행하는 열의 바로 밑으로 위치를 변경한다.
			//0열만 마지막열의 밑으로 이동한다.

			if (pTransform->Get_Position().y + (ARC1CY >> 1) < 0)
			{
				CTransform* pLastArcTransform = nullptr;

				if (i == 0)
					pLastArcTransform = (CTransform*)(m_pImgArc1[ARC1Y - 1][j]->Get_Module(L"Transform"));
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
	}

	if (m_iCurrCanvas == 1)
	{
		static CMyButton* pPrvBtn = nullptr;


		for (size_t i = 0; i < m_vecCharSelectBtn.size(); ++i)
		{
			//만약 선택된 버튼이 아니면 비활성화
			if (pPrvBtn != m_vecCharSelectBtn[i])
				m_vecCharSelectBtn[i]->Set_RenderState(CMyButton::STATE_DISABLE);

			//선택됬으면
			if (OBJ_CLICKED == m_vecCharSelectBtn[i]->Update(_timeDelta))
			{
				//활성화
				m_vecCharSelectBtn[i]->Set_RenderState(CMyButton::STATE_ENABLE);
				pPrvBtn = m_vecCharSelectBtn[i];
				//선택된 캐릭터 저장
				CStatics::m_eSelectedHero = (CStatics::SELECTED_HERO)i;
			}
		}

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

	if (m_iCurrCanvas == 1)
	{
		for (auto& btn : m_vecCharSelectBtn)
		{
			btn->Render();
		}
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

	for (auto& btn : m_vecCharSelectBtn)
	{
		if (0 != Safe_Release(btn))
			MSG_BOX("Fail to release Btn");

	}
	m_vecCharSelectBtn.clear();

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


