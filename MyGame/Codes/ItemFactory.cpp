#include "stdafx.h"
#include "..\Headers\ItemFactory.h"
#include "Item.h"
#include "MeleeWeapon.h"
#include "wand.h"
#include "Ring.h"
#include "Armor.h"
#include "ObjMgr.h"
USING(MyGame)

HRESULT CItemFactory::Make_Prototpyes(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;

	pObjMgr->Add_Prototype(L"MeleeWeapon", SCENE_STAGE, CMeleeWeapon::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"Wand", SCENE_STAGE, CWand::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"Ring", SCENE_STAGE, CRing::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"Armor", SCENE_STAGE, CArmor::Create(_pGraphic_Device));
	return S_OK;
}



CItem* CItemFactory::Make_Item( BASEDESC _tDesc, ITEM_ID _eID)
{
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return nullptr;

	CEquipment::STATEDESC tDesc;
	CEquipment::STATS tStats;

	CItem* pItem = nullptr;

	switch (_eID)
	{
	case MyGame::CItemFactory::ITEM_SHORTSWORD:
		tDesc.m_iTextureID = 4;
		tDesc.m_pDescription = L"짧은 검이다. 과일이나 깎아먹을 수 있겠다.";
		tDesc.m_pItemName = L"숏소드";
		tDesc.m_tBaseDesc = _tDesc;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, L"Item", SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_LONGSWORD:
		tDesc.m_iTextureID = 2;
		tDesc.m_pDescription = L"긴 검이다. 무게가 꽤나간다.";
		tDesc.m_pItemName = L"롱소드";
		tDesc.m_tBaseDesc = _tDesc;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, L"Item", SCENE_STAGE, &tDesc);
		break;
		break;
	case MyGame::CItemFactory::ITEM_DAGGER:
		break;
	case MyGame::CItemFactory::ITEM_IRONSWORD:
		break;
	case MyGame::CItemFactory::ITEM_BATTLEAXE:
		break;
	case MyGame::CItemFactory::ITEM_GOLDAXE:
		break;
	case MyGame::CItemFactory::ITEM_SPEAR:
		break;
	case MyGame::CItemFactory::ITEM_TRIDENT:
		break;
	case MyGame::CItemFactory::ITEM_MACE:
		break;
	case MyGame::CItemFactory::ITEM_LETHERARMOR:
		break;
	case MyGame::CItemFactory::ITEM_CHAINARMOR:
		break;
	case MyGame::CItemFactory::ITEM_PLATEARMOR:
		break;
	case MyGame::CItemFactory::ITEM_IRONARMOR:
		break;
	case MyGame::CItemFactory::ITEM_DRAGONARMOR:
		break;
	case MyGame::CItemFactory::ITEM_ARROW:
		break;
	case MyGame::CItemFactory::ITEM_BOMB:
		break;
	case MyGame::CItemFactory::ITEM_BOTTLE:
		break;
	case MyGame::CItemFactory::ITEM_NUCKLE:
		break;
	case MyGame::CItemFactory::ITEM_REDRING:
		break;
	case MyGame::CItemFactory::ITEM_END:
		break;
	default:
		break;
	}

	return pItem;
}

