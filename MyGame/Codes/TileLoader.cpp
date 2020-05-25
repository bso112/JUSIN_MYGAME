#include "stdafx.h"
#include "..\Headers\TileLoader.h"
#include "ObjMgr.h"
#include "Terrain.h"
#include "Door.h"
#include "Trap.h"
#include "Stair.h"

USING(MyGame)
CTileLoader::CTileLoader()
{
}


CTileLoader::~CTileLoader()
{
}

HRESULT CTileLoader::CreateTilePrototype(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID, vector<CTerrain*>* container)
{
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;

	//팔레트에 쓸 타일(프로토타입)을 만든다.
	CTerrain* pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_bookshelf", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_bookshelf", _eSceneID, pTerrain); if(container)container->push_back(pTerrain); 

	pTerrain = CDoor::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_door", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_door", _eSceneID, pTerrain); if(container)container->push_back(pTerrain);

	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_floor", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_floor", _eSceneID, pTerrain); if(container)container->push_back(pTerrain);


	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_floor_mask", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask", _eSceneID, pTerrain); if (container)container->push_back(pTerrain);

	//10개 넘어가면 인식못함..
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_floor_mask_ex", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_ex", _eSceneID, pTerrain); if (container)container->push_back(pTerrain);

	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_sign", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_sign", _eSceneID, pTerrain); if(container)container->push_back(pTerrain); 

	pTerrain = CStair::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_stair", _eSceneID, L"stair");
	pObjMgr->Add_Prototype(L"lv_One_stair", _eSceneID, pTerrain); if(container)container->push_back(pTerrain);

	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_statue", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_statue", _eSceneID, pTerrain); if(container)container->push_back(pTerrain); 

	pTerrain = CTrap::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_trap", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_trap", _eSceneID, pTerrain); if(container)container->push_back(pTerrain); 

	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_wall", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_wall", _eSceneID, pTerrain); if(container)container->push_back(pTerrain); 

	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_water", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_water", _eSceneID, pTerrain); if (container)container->push_back(pTerrain);
	pTerrain->Set_Maskable();

	return S_OK;
}


