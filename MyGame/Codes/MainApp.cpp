#include "stdafx.h"
#include "MainApp.h"
#include "SceneMgr.h"
#include "Graphic_Device.h"
#include "TimerMgr.h"
#include "Renderer.h"
#include "ObjMgr.h"
#include "Clock.h"
#include "ModuleMgr.h"

USING(MyGame)

CMainApp::CMainApp()
	:m_pSceneMgr(CSceneMgr::Get_Instance())
{

	Safe_AddRef(m_pSceneMgr);
}

HRESULT CMainApp::Initalize()
{

	if (FAILED(Initalize_Default_Setting()))
		return E_FAIL;

	if (FAILED(Initalize_Module()))
		return E_FAIL;

	if (FAILED(Initalize_Scene()))
		return E_FAIL;

	return S_OK;
}

_int CMainApp::Update(_double _timeDelta)
{
#if _DEBUG
	m_dwTimeAcc += _timeDelta;
#endif



	m_pSceneMgr->Update(_timeDelta);


	if (nullptr == m_pSceneMgr)
		return -1;
	return 0;
}



HRESULT CMainApp::Render()
{
#if _DEBUG
	++m_iRenderCnt;
	if (m_dwTimeAcc >= 1.0)
	{
		wsprintf(m_szFPS, L"FPS : %d", m_iRenderCnt);
		SetWindowText(g_hWnd, m_szFPS);
		m_dwTimeAcc = 0.0;
		m_iRenderCnt = 0;
	}
#endif
	if (nullptr == m_pGraphic_Device ||
		nullptr == m_pSceneMgr)
		return E_FAIL;

	m_pGraphic_Device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DXCOLOR(0.f, 0.f, 1.f, 1.f), 1.f, 0);
	m_pGraphic_Device->BeginScene();
	//�׸��� �׸���.

	if (FAILED(m_pSceneMgr->Render()))
		return E_FAIL;


	m_pGraphic_Device->EndScene();
	m_pGraphic_Device->Present(nullptr, nullptr, g_hWnd, nullptr);
	return S_OK;
}

HRESULT CMainApp::Initalize_Default_Setting()
{
	CGraphic_Device* pGraphic_Device = CGraphic_Device::Get_Instance();
	if (nullptr == pGraphic_Device)
		return E_FAIL;

	Safe_AddRef(pGraphic_Device);

	if (FAILED(pGraphic_Device->Ready_Graphic_Device(CGraphic_Device::TYPE_WIN, &m_pGraphic_Device)))
		return E_FAIL;

	Safe_Release(pGraphic_Device);
	return S_OK;
}

HRESULT CMainApp::Initalize_Scene()
{
	if (m_pSceneMgr == nullptr)
		return E_FAIL;

	if (FAILED(m_pSceneMgr->Scene_Change(SCENE_LOADING, m_pGraphic_Device)))
		return E_FAIL;

	return S_OK;
}

HRESULT CMainApp::Initalize_Module()
{
	CModuleMgr* pModuleMgr = CModuleMgr::Get_Instance();
	if (nullptr == pModuleMgr)
		return E_FAIL;

	Safe_AddRef(pModuleMgr);

	if (FAILED(pModuleMgr->Add_Module(MODULE_VIBUFFER, SCENE_STATIC, CVIBuffer::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(pModuleMgr->Add_Module(MODULE_TRANSFORM, SCENE_STATIC, CTransform::Create(m_pGraphic_Device))))
		return E_FAIL;

	Initalize_Texture();

	Safe_Release(pModuleMgr);

	return S_OK;
}

HRESULT CMainApp::Initalize_Texture()
{
	CModuleMgr* pModuleMgr = CModuleMgr::Get_Instance();
	if (nullptr == pModuleMgr)
		return E_FAIL;

	Safe_AddRef(pModuleMgr);


	if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_DEFUALT, SCENE_STATIC, 
		CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Loading.jpg"))))
		return E_FAIL;

	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_BOOKSHELF, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/bookshelf%d", 6))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_FLOOR, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/bookshelf_broken%d", 1))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_FLOOR_MASKE, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/door_locked%d", 2))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_FLOOR_GRASS, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/floor_burend%d", 2))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_FLOOR_MOSSY, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/floor_mask%d", 15))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_FLOOR_WOOD, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/floor_grass%d", 2))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_GRASS_GREEN, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/floor_mossy%d", 2))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_GRASS_GREEN_MASKE, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/floor_wood%d", 2))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_GRASS_ASH, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/floor%d", 2))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_GRASS_ASH_MASKE, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/grass_ash_mask%d", 4))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_SING, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/grass_ash%d", 4))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_STAIR_UP, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/grass_green_mask%d", 6))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_STAIR_DOWN, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/grass_green%d", 4))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_STATUE_WITH_FLOOR, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/stair_up%d", 1))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_STATUE_WITH_WOOD, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/stair_down%d", 1))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_WALL, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/statue_with_floor%d", 1))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_WALL_SEWERS, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/statue_with_wood%d", 1))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_WELL, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/wall_sewers%d", 10))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_WELL, SCENE_STATIC,
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/wall%d", 17))))
	//	return E_FAIL;
	//if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE_BLACK, SCENE_STATIC, 
	//	CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Terrain/sewers/well%d", 1))))
	//	return E_FAIL;
	//





	Safe_Release(pModuleMgr);
	return S_OK;
}


CMainApp * CMainApp::Create()
{
	CMainApp* instance = new CMainApp;
	if (FAILED(instance->Initalize()))
	{
		MSG_BOX("Fail To Create MainApp");
		Safe_Release(instance);
	}
	return instance;
}

void CMainApp::Free()
{
	Safe_Release(m_pGraphic_Device);
	Safe_Release(m_pSceneMgr);


	if (FAILED(CRenderer::Get_Instance()->Clear_RenderGroup()))
		return;


	if (0 != CSceneMgr::Destroy_Instance())
		MSG_BOX("Fail to Release CScneeMgr");

	if (0 != CObjMgr::Destroy_Instance())
		MSG_BOX("Fail to Release CObjMgr");

	if (0 != CModuleMgr::Destroy_Instance())
		MSG_BOX("Fail to Relese CModuleMgr");

	if (0 != CRenderer::Destroy_Instance())
		MSG_BOX("Fail to Release CRenderer");

	if (0 != CTimerMgr::Destroy_Instance())
		MSG_BOX("Fail to Release CTimerMgr");

	if (0 != CGraphic_Device::Destroy_Instance())
		MSG_BOX("Fail to Relese CGraphic_Device");



}
