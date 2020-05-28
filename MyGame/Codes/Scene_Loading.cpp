#include "stdafx.h"
#include "..\Headers\Scene_Loading.h"
#include "Loading.h"
#include "ObjMgr.h"
#include "Image.h"
#include "SceneMgr.h"
USING(MyGame)

CScene_Loading::CScene_Loading(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CScene(_pGraphic_Device)
{
}

HRESULT CScene_Loading::Initialize()
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;
	CImage* pImage = (CImage*)m_pObjMgr->Add_GO_To_Layer(L"Loading", SCENE_LOADING, CImage::Create(m_pGraphic_Device, Vector2((float)(g_iWinCX >> 1), float(g_iWinCY >>1)), Vector2((float)g_iWinCX, (float)g_iWinCY), L"loading", SCENE_STATIC));
	pImage->Set_UI(true);
	m_pLoading = CLoading::Create(m_pGraphic_Device, SCENE_STAGE);
	
	return S_OK;
}

_int CScene_Loading::Update(_double _timeDelta)
{
	CScene::Update(_timeDelta);
	if (m_pLoading->IsFinish())
	{
		CSceneMgr::Get_Instance()->Scene_Change(SCENE_STAGE, m_pGraphic_Device);
	}
	return 0;
}

HRESULT CScene_Loading::Render()
{
	CScene::Render();
	g_pFontX2->DrawText(NULL, L"내려가는중...", -1, &Make_Rect(Vector2(g_iWinCX >> 1, g_iWinCY >>1), Vector2(500.f,100.f)), DT_CENTER | DT_VCENTER, 0xffffffff);
	return S_OK;
}




CScene_Loading * CScene_Loading::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CScene_Loading* pInstance = new CScene_Loading(_pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail to Create Loading Scene");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CScene_Loading::Free()
{
	Safe_Release(m_pLoading);
	//게임 오브젝트 프로토타입 지우기, 게임 오브젝트 인스턴스에 대한 레퍼런스 끊기, 모듈 인스턴스 지우기
	if (FAILED(CObjMgr::Get_Instance()->Clear_Scene(SCENEID::SCENE_LOADING)))
		MSG_BOX("Fail to Clear GameObject Prototypes");

	//모듈 프로토타입 지우기
	if (FAILED(CModuleMgr::Get_Instance()->Clear_Scene(SCENEID::SCENE_LOADING)))
		MSG_BOX("Fail to Clear Module Prototypes");

	//게임 오브젝트 인스턴스 지우기
	if (FAILED(CRenderer::Get_Instance()->Clear_RenderGroup()))
		MSG_BOX("Fail to Clear Module Prototypes");



	CScene::Free();
}
