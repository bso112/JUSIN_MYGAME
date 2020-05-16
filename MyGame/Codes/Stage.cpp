#include "stdafx.h"
#include "..\Headers\Stage.h"
#include "LevelMgr.h"
#include "TextureLoader.h"
#include "StageUIMgr.h"
#include "Transform.h"
#include "TurnMgr.h"
#include "MyButton.h"
#include "KeyMgr.h"


USING(MyGame)

CStage::CStage(PDIRECT3DDEVICE9 _pGraphic_Device)
	: CScene(_pGraphic_Device),
	m_pLevelMgr(CLevelMgr::Get_Instance()),
	m_pStageUIMgr(CStageUIMgr::Get_Instance()),
	m_pTurnMgr(CTurnMgr::Get_Instance())
{
	Safe_AddRef(m_pLevelMgr);
	Safe_AddRef(m_pStageUIMgr);
	Safe_AddRef(m_pTurnMgr);

};

HRESULT CStage::Initialize()
{
	
	if (FAILED(Initalize_Prototypes()))
		return E_FAIL;

	if (FAILED(Initalize_Layers()))
		return E_FAIL;
	
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	m_pStageUIMgr->Initialize(m_pGraphic_Device, (CHero*)m_pObjMgr->Get_Player(SCENE_STAGE));
	m_pTurnMgr->Initialize();

	return S_OK;
}

_int CStage::Update(_double _timeDelta)
{
	m_pTurnMgr->Update_Simultaneously();
	CScene::Update(_timeDelta);

	return 0;
}

HRESULT CStage::Render()
{
	CScene::Render();

	return S_OK;
}



HRESULT CStage::Initalize_Prototypes()
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	CTextureLoader* pLoader = CTextureLoader::Get_Instance();
	if (nullptr == pLoader)
		return E_FAIL;

	Safe_AddRef(pLoader);

	pLoader->Create_Textrues_From_Folder(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/UI/Stage/");
	pLoader->Create_Textrues_From_Folder(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/UI/icon/");
	pLoader->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Terrain/level_one/");

	Safe_Release(pLoader);


	if (FAILED(m_pLevelMgr->Initialize_Prototypes(m_pGraphic_Device)))
		return E_FAIL;

	return S_OK;
}

HRESULT CStage::Initalize_Layers()
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;


	if (FAILED(m_pLevelMgr->Initialize()))
		return E_FAIL;


	return S_OK;
}

CStage * CStage::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CStage* pInstance = new CStage(_pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail to Create CStage Scene");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CStage::Free()
{

	Safe_Release(m_pLevelMgr);
	Safe_Release(m_pStageUIMgr);
	Safe_Release(m_pTurnMgr);


	if (0 != CStageUIMgr::Destroy_Instance())
		MSG_BOX("Fail to release m_pStageUIMgr");

	if(0 != CLevelMgr::Destroy_Instance())
		MSG_BOX("Fail to release CLevelMgr");

	if (0 != CTurnMgr::Destroy_Instance())
		MSG_BOX("Fail to release CTurnMgr");

	if (FAILED(CObjMgr::Get_Instance()->Clear_Scene(SCENEID::SCENE_STAGE)))
		MSG_BOX("Fail to Clear GameObject Prototypes");

	//모듈 프로토타입 지우기
	if (FAILED(CModuleMgr::Get_Instance()->Clear_Scene(SCENEID::SCENE_STAGE)))
		MSG_BOX("Fail to Clear Module Prototypes");

	//게임 오브젝트 인스턴스 지우기
	if (FAILED(CRenderer::Get_Instance()->Clear_RenderGroup()))
		MSG_BOX("Fail to Clear Module Prototypes");

	if (FAILED(CKeyMgr::Get_Instance()->ClearObservers(SCENEID::SCENE_STAGE)))
		MSG_BOX("Fail to Clear Module Prototypes");

	CScene::Free();
}



