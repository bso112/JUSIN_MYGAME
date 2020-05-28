#include "stdafx.h"
#include "..\Headers\TileLoader.h"
#include "ObjMgr.h"
#include "Terrain.h"
#include "Door.h"
#include "Trap.h"
#include "Stair.h"
#include "TextureLoader.h"

USING(MyGame)
CTileLoader::CTileLoader()
{
}


CTileLoader::~CTileLoader()
{
}

HRESULT CTileLoader::CreateTilePrototype(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID, vector<CTerrain*>* container)
{
	//텍스쳐 로드
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder_Anim(_pGraphic_Device, _eSceneID, L"../Bin/Resources/Textures/Terrain/level_one/");
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder_Anim(_pGraphic_Device, _eSceneID, L"../Bin/Resources/Textures/Terrain/level_two/");


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

	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_water", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_water", _eSceneID, pTerrain); if (container)container->push_back(pTerrain);
	pTerrain->Set_Maskable();



	//팔레트에 쓸 타일(프로토타입)을 만든다.
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_Two_bookshelf", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_Two_bookshelf", _eSceneID, pTerrain); if (container)container->push_back(pTerrain);

	pTerrain = CDoor::Create(_pGraphic_Device, TERRAIN(false), L"lv_Two_door", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_Two_door", _eSceneID, pTerrain); if (container)container->push_back(pTerrain);

	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_Two_floor", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_Two_floor", _eSceneID, pTerrain); if (container)container->push_back(pTerrain);


	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_Two_floor_mask", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_Two_floor_mask", _eSceneID, pTerrain); if (container)container->push_back(pTerrain);

	//10개 넘어가면 인식못함..
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_Two_floor_mask_ex", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_Two_floor_mask_ex", _eSceneID, pTerrain); if (container)container->push_back(pTerrain);

	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_Two_sign", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_Two_sign", _eSceneID, pTerrain); if (container)container->push_back(pTerrain);

	pTerrain = CStair::Create(_pGraphic_Device, TERRAIN(true), L"lv_Two_stair", _eSceneID, L"stair");
	pObjMgr->Add_Prototype(L"lv_Two_stair", _eSceneID, pTerrain); if (container)container->push_back(pTerrain);

	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_Two_statue", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_Two_statue", _eSceneID, pTerrain); if (container)container->push_back(pTerrain);

	pTerrain = CTrap::Create(_pGraphic_Device, TERRAIN(true), L"lv_Two_trap", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_Two_trap", _eSceneID, pTerrain); if (container)container->push_back(pTerrain);

	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_Two_wall", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_Two_wall", _eSceneID, pTerrain); if (container)container->push_back(pTerrain);

	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_Two_water", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_Two_water", _eSceneID, pTerrain); if (container)container->push_back(pTerrain);
	pTerrain->Set_Maskable();

	return S_OK;
}


