#include "stdafx.h"
#include "MainApp.h"
#include "SceneMgr.h"
#include "Graphic_Device.h"
#include "TimerMgr.h"
#include "Renderer.h"
#include "ObjMgr.h"
#include "ModuleMgr.h"
#include "KeyMgr.h"
#include "TextureLoader.h"
#include "Shader.h"
#include "Animator.h"
#include "AIStateCon.h"
#include "PlayerStateCon.h"
#include "KeyMgr.h"
#include "Pipline.h"
#include "ParticleSystem.h"
#include "DialogMgr.h"
#include "TargetMgr.h"

USING(MyGame)

ID3DXFont* g_pFont = nullptr;
//사이즈 2배
ID3DXFont* g_pFontX2 = nullptr;

CMainApp::CMainApp()
	:m_pSceneMgr(CSceneMgr::Get_Instance())
{

	Safe_AddRef(m_pSceneMgr);
	//랜덤시드 정해주기
	srand(_uint(time(NULL)));

}

HRESULT CMainApp::Initalize()
{


	if (FAILED(Initalize_Default_Setting()))
		return E_FAIL;

	if (FAILED(Initialize_Prototypes()))
		return E_FAIL;

	if (FAILED(Initalize_Module()))
		return E_FAIL;

	if (FAILED(Initalize_Texture()))
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

	if (nullptr == m_pSceneMgr)
		return -1;


	CKeyMgr* pKeyMgr = CKeyMgr::Get_Instance();
	if (nullptr == pKeyMgr)
		return -1;

	CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON);
	CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON);
	CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON);
	CKeyMgr::Get_Instance()->Key_Update();

	m_pSceneMgr->Update(_timeDelta);

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
	//그림을 그린다.

	if (FAILED(m_pSceneMgr->Render()))
		return E_FAIL;


	m_pGraphic_Device->EndScene();
	m_pGraphic_Device->Present(nullptr, nullptr, g_hWnd, nullptr);

	//죽은 게임 오브젝트를 클리어한다.
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	pObjMgr->Clear_DeadObjects();
	//만약 씬이 바뀌었으면 이전씬을 지운다.
	if (FAILED(m_pSceneMgr->Clear_PrvScene()))
		return E_FAIL;


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

	//그래픽 디바이스 셋팅
	ALPHATEST;
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphic_Device->SetRenderState(D3DRS_ZENABLE, FALSE);

	//폰트셋팅
	D3DXCreateFont(m_pGraphic_Device, 0, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"pixel", &g_pFont);
	D3DXCreateFont(m_pGraphic_Device, 35, 13, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"pixel", &g_pFontX2);


	return S_OK;
}

HRESULT CMainApp::Initialize_Prototypes()
{
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	RETURN_FAIL_IF_NULL(pObjMgr);

	//파티클 시스템 프로토타입 생성
	pObjMgr->Add_Prototype(L"ParticleSystem", SCENE_STATIC, CParticleSystem::Create(m_pGraphic_Device));

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

	if (FAILED(pModuleMgr->Add_Module(L"VIBuffer", SCENE_STATIC, CVIBuffer::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(pModuleMgr->Add_Module(L"Transform", SCENE_STATIC, CTransform::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(pModuleMgr->Add_Module(L"Shader", SCENE_STATIC, CShader::Create(m_pGraphic_Device, L"../Bin/ShaderFiles/Shader_Default.fx"))))
		return E_FAIL;

	if (FAILED(pModuleMgr->Add_Module(L"Animator", SCENE_STATIC, CAnimator::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(pModuleMgr->Add_Module(L"AIStateCon", SCENE_STATIC, CAIStateCon::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(pModuleMgr->Add_Module(L"PlayerStateCon", SCENE_STATIC, CPlayerStateCon::Create(m_pGraphic_Device))))
		return E_FAIL;


	Safe_Release(pModuleMgr);

	return S_OK;
}

HRESULT CMainApp::Initalize_Texture()
{

	CTextureLoader* pLoader = CTextureLoader::Get_Instance();

	if (nullptr == pLoader)
		return E_FAIL;

	Safe_AddRef(pLoader);

	pLoader->Create_Textrues_From_Folder(m_pGraphic_Device, SCENEID::SCENE_STATIC, L"../Bin/Resources/Textures/Static/");

	Safe_Release(pLoader);

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

	Safe_Release(g_pFont);
	Safe_Release(g_pFontX2);
	Safe_Release(m_pGraphic_Device);
	Safe_Release(m_pSceneMgr);

	//별 의미 없다.
	if (FAILED(CRenderer::Get_Instance()->Clear_RenderGroup()))
		return;

	if (0 != CDialogMgr::Destroy_Instance())
		MSG_BOX("Fail to Release DIalogMgr");

	if (0 != CTargetMgr::Destroy_Instance())
		MSG_BOX("Fail to Release CTargetMgr");


	//스태틱 씬의 오브젝트가 오브젝트 매니저를 참조해서 오브젝트 매니저의 refcnt가 0 이 아니게됨.
	//따라서 클리어 해줘야함
	CObjMgr::Get_Instance()->Clear_Scene(SCENE_STATIC);


	if (0 != CTextureLoader::Destroy_Instance())
		MSG_BOX("Fail to Release CTextureLoader");

	if (0 != CSceneMgr::Destroy_Instance())
		MSG_BOX("Fail to Release CScneeMgr");

	if (0 != CObjMgr::Destroy_Instance())
		MSG_BOX("Fail to Release CObjMgr");

	if (0 != CModuleMgr::Destroy_Instance())
		MSG_BOX("Fail to Relese CModuleMgr");

	CRenderer::Destroy_Instance();
	CPipline::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CTimerMgr::Destroy_Instance();
	CGraphic_Device::Destroy_Instance();

	/*if (0 != CRenderer::Destroy_Instance())
		MSG_BOX("Fail to Release CRenderer");

	if (0 != CPipline::Destroy_Instance())
		MSG_BOX("Fail to Relese CPipline");

	if (0 != CKeyMgr::Destroy_Instance())
		MSG_BOX("Fail to Release KeyMgr");

	if (0 != CGraphic_Device::Destroy_Instance())
		MSG_BOX("Fail to Relese CGraphic_Device");*/




}
