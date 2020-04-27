#include "stdafx.h"
#include "..\Headers\Stage.h"
#include "World.h"
#include "Warrior.h"
#include "TextureLoader.h"
#include "StageUIMgr.h"

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
	
	if (FAILED(Initalize_World()))
		return E_FAIL;

	m_pStageUIMgr->Initialize(m_pGraphic_Device);


	return S_OK;
}

_int CStage::Update(_double _timeDelta)
{
	m_pStageUIMgr->Update();
	CScene::Update(_timeDelta);

	return 0;
}

HRESULT CStage::Render()
{
	m_pStageUIMgr->Render();
	CScene::Render();

	return S_OK;
}



HRESULT CStage::Initalize_World()
{
	m_pWorld->Initialize(m_pGraphic_Device, SCENE_STAGE);

	return S_OK;
}




HRESULT CStage::Initalize_Prototypes()
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/UI/Stage/");


	if (FAILED(m_pObjMgr->Add_Prototype(CObjMgr::PROTOTYPE_PLAYER, SCENE_STAGE, CWarrior::Create(m_pGraphic_Device))))
		return E_FAIL;


	return S_OK;
}

HRESULT CStage::Initalize_Layers()
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	if (FAILED(m_pObjMgr->Add_GO_To_Layer(CObjMgr::PROTOTYPE_PLAYER, SCENE_STAGE, CObjMgr::LAYER_PLAYER, SCENE_STAGE)))
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

	CScene::Free();
}



