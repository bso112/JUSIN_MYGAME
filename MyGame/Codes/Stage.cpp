#include "stdafx.h"
#include "..\Headers\Stage.h"
#include "World.h"
#include "Warrior.h"
#include "TextureLoader.h"
#include "StageUIMgr.h"
#include "Transform.h"


USING(MyGame)

CStage::CStage(PDIRECT3DDEVICE9 _pGraphic_Device)
	: CScene(_pGraphic_Device),
	m_pWorld(CWorld::Get_Instance()),
	m_pStageUIMgr(CStageUIMgr::Get_Instance())
{
	Safe_AddRef(m_pWorld);
	Safe_AddRef(m_pStageUIMgr);
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


	return S_OK;
}

_int CStage::Update(_double _timeDelta)
{
	m_pStageUIMgr->Update();
	m_pWorld->Update();
	CScene::Update(_timeDelta);

	return 0;
}

HRESULT CStage::Render()
{
	m_pWorld->Render();
	CScene::Render();
	m_pStageUIMgr->Render();

	return S_OK;
}



HRESULT CStage::Initalize_World()
{
	m_pWorld->Initialize(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Data/level1.dat");

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
	pLoader->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Hero/Warrior/");
	pLoader->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Terrain/level_one/");

	if (FAILED(Initalize_World()))
		return E_FAIL;

	Safe_Release(pLoader);

	//이부분 캐릭터 선택 반영하게 변경
	if (FAILED(m_pObjMgr->Add_Prototype(L"Player", SCENE_STAGE, CWarrior::Create(m_pGraphic_Device))))
		return E_FAIL;


	return S_OK;
}

HRESULT CStage::Initalize_Layers()
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	if (nullptr == m_pObjMgr->Add_GO_To_Layer(L"Player", SCENE_STAGE, L"Player", SCENE_STAGE))
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

	Safe_Release(m_pWorld);
	Safe_Release(m_pStageUIMgr);
	
	if (0 != m_pWorld->Destroy_Instance())
		MSG_BOX("Fail to release TileMgr");

	if (0 != m_pStageUIMgr->Destroy_Instance())
		MSG_BOX("Fail to release m_pStageUIMgr");


	//게임 오브젝트 프로토타입 지우기, 게임 오브젝트 인스턴스에 대한 레퍼런스 끊기, 모듈 인스턴스 지우기
	if (FAILED(CObjMgr::Get_Instance()->Clear_Scene(SCENEID::SCENE_STAGE)))
		MSG_BOX("Fail to Clear GameObject Prototypes");

	//모듈 프로토타입 지우기
	if (FAILED(CModuleMgr::Get_Instance()->Clear_Scene(SCENEID::SCENE_STAGE)))
		MSG_BOX("Fail to Clear Module Prototypes");

	//게임 오브젝트 인스턴스 지우기
	if (FAILED(CRenderer::Get_Instance()->Clear_RenderGroup()))
		MSG_BOX("Fail to Clear Module Prototypes");


	CScene::Free();
}



