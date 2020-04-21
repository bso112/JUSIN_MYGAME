#include "stdafx.h"
#include "..\Headers\Stage.h"
#include "World.h"
#include "MyButton.h"
#include "Warrior.h"


USING(MyGame)

HRESULT CStage::Initalize()
{
	CScene::Initialize();
	
	if (FAILED(Initalize_Prototypes()))
		return E_FAIL;

	if (FAILED(Initalize_Layers()))
		return E_FAIL;
	
	if (FAILED(Initalize_Tile()))
		return E_FAIL;


	return S_OK;
}

_int CStage::Update(_double _timeDelta)
{


	return 0;
}

HRESULT CStage::Render()
{
	CScene::Render();
	return S_OK;
}



HRESULT CStage::Initalize_Tile()
{


	return S_OK;
}




HRESULT CStage::Initalize_Prototypes()
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

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

void CStage::Free()
{
	CScene::Free();

	Safe_Release(m_pBtn);
	Safe_Release(m_pTileMgr);

	if (0 != m_pTileMgr->Destroy_Instance())
		MSG_BOX("Fail to release TileMgr");

}



