#include "stdafx.h"
#include "..\Headers\Spawner.h"
#include "World.h"
#include "ObjMgr.h"
#include "Rat.h"
#include "Gnoll.h"
#include "Crab.h"
#include "Food.h"
#include "Texture.h"
#include "ModuleMgr.h"

USING(MyGame)
CSpawner::CSpawner()
{
}

HRESULT CSpawner::Ready_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eScene)
{
	if (SCENE_END <= _eScene)
		return E_FAIL;

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;
	Safe_AddRef(pObjMgr);

	CModuleMgr* pModuleMgr = CModuleMgr::Get_Instance();
	if (nullptr == pModuleMgr)
		return E_FAIL;
	Safe_AddRef(pModuleMgr);
	pObjMgr->Add_Prototype(L"Rat", _eScene, CRat::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"Gnoll", _eScene, CGnoll::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"Crab", _eScene, CCrab::Create(_pGraphic_Device));

	if(FAILED(pModuleMgr->Add_Module(L"Texture_Food", _eScene, CTexture::Create(_pGraphic_Device, L"../Bin/Resources/Textures/Item/Food/%d.png", 1))))
		return E_FAIL;
	pObjMgr->Add_Prototype(L"Food", _eScene, CFood::Create(_pGraphic_Device));


	Safe_Release(pObjMgr);
	Safe_Release(pModuleMgr);
	return S_OK;
}

HRESULT CSpawner::Spawn(SCENEID _eScene)
{
	if (SCENE_END <= _eScene)
		return E_FAIL;

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;

	CWorld* pWorld = CWorld::Get_Instance();
	if (nullptr == pWorld)
		return E_FAIL;
	
	
	switch (_eScene)
	{
	case MyGame::SCENE_STAGE:
	{
		Vector3 ranPos = pWorld->Get_RandomPos();
		pObjMgr->Add_GO_To_Layer(L"Rat", _eScene, L"Monster", _eScene, &ranPos);
		ranPos = pWorld->Get_RandomPos();
		pObjMgr->Add_GO_To_Layer(L"Gnoll", _eScene, L"Monster", _eScene, &ranPos);
		ranPos = pWorld->Get_RandomPos();
		pObjMgr->Add_GO_To_Layer(L"Crab", _eScene, L"Monster", _eScene, &ranPos);
		ranPos = pWorld->Get_RandomPos();
		pObjMgr->Add_GO_To_Layer(L"Food", _eScene, L"Cheese", _eScene, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(25.f,20.f)), 10.f, 1));

		break;

	}
	default:
		break;
	}

	return S_OK;
}



void CSpawner::Free()
{
}
