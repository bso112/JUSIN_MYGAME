#include "stdafx.h"
#include "..\Headers\ItemFactory.h"
#include "Item.h"
#include "MeleeWeapon.h"
#include "wand.h"
#include "Ring.h"
#include "Armor.h"
#include "ObjMgr.h"
#include "Arrow.h"
#include "HealPotion.h"
#include "PoisionPotion.h"
#include "ParalyzePotion.h"
#include "FirePotion.h"
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
	pObjMgr->Add_Prototype(L"Arrow", SCENE_STAGE, CArrow::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"HealPotion", SCENE_STAGE, CHealPotion::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"ParalyzePotion", SCENE_STAGE, CParalyzePotion::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"FirePotion", SCENE_STAGE, CFirePotion::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"PosionPotion", SCENE_STAGE, CPoisionPotion::Create(_pGraphic_Device));




	return S_OK;
}



CItem* CItemFactory::Make_Item( BASEDESC _tDesc, ITEM_ID _eID, _int _level)
{
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return nullptr;



	CItem* pItem = nullptr;

	CItem::STATEDESC tDesc;
	CItem::STATS tStats;
	const _tchar* layerTag = L"Item";
	switch (_level)
	{
	case 1:
		layerTag = L"Item";
	case 2:
		layerTag = L"Item_lv2";
	case 3:
		layerTag = L"Item_lv3";
	default:
		break;
	}

	switch (_eID)
	{
	case MyGame::CItemFactory::ITEM_SHORTSWORD:
		tDesc.m_iTextureID = 4;
		tDesc.m_pDescription = L"짧은 검이다. 과일이나 깎아먹을 수 있겠다.";
		tDesc.m_pItemName = L"숏소드";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 3.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_LONGSWORD:
		tDesc.m_iTextureID = 2;
		tDesc.m_pDescription = L"긴 검이다. 무게가 꽤나간다.";
		tDesc.m_pItemName = L"롱소드";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 5.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_DAGGER:
		tDesc.m_iTextureID = 3;
		tDesc.m_pDescription = L"근접전이나 암살에 적당할 듯 하다.";
		tDesc.m_pItemName = L"대거";
		tStats.m_fAtt = 2.f;
		tDesc.m_tBaseDesc = _tDesc;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_IRONSWORD:
		tDesc.m_iTextureID = 5;
		tDesc.m_pItemName = L"철검";
		tDesc.m_pDescription = L"굉장히 단단해 보이는 검이다.";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 6.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_BATTLEAXE:
		tDesc.m_iTextureID = 7;
		tDesc.m_pItemName = L"전투도끼";
		tDesc.m_pDescription = L"야만족이 사용하는 도끼";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 6.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_GOLDAXE:
		tDesc.m_iTextureID = 8;
		tDesc.m_pItemName = L"황금망치";
		tDesc.m_pDescription = L"금으로 된 망치다. 어느 부자가 만들었다.";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 5.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_SPEAR:
		tDesc.m_iTextureID = 9;
		tDesc.m_pItemName = L"창";
		tDesc.m_pDescription = L"평범한 창이다. 쥐 정도는 쉽게 잡을 것 같다.";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 5.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_TRIDENT:
		tDesc.m_iTextureID = 10;
		tDesc.m_pItemName = L"삼지창";
		tDesc.m_pDescription = L"꽤나 멋있다.";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 7.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_MACE:
		tDesc.m_iTextureID = 11;
		tDesc.m_pItemName = L"메이스";
		tDesc.m_pDescription = L"그냥 들고 때리면 된다.";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 4.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_LETHERARMOR:
		tDesc.m_iTextureID = 2;
		tDesc.m_pItemName = L"가죽갑옷";
		tDesc.m_pDescription = L"어떤 동물의 가죽일까?";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fArmor = 2.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"Armor", SCENE_STAGE,layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_CHAINARMOR:
		tDesc.m_iTextureID = 6;
		tDesc.m_pItemName = L"사슬갑옷";
		tDesc.m_pDescription = L"움직일때마다 소리가난다.";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fArmor = 3.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"Armor", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_PLATEARMOR:
		break;
	case MyGame::CItemFactory::ITEM_IRONARMOR:
		break;
	case MyGame::CItemFactory::ITEM_DRAGONARMOR:
		break;
	case MyGame::CItemFactory::ITEM_ARROW:
		tDesc.m_iTextureID = 1;
		tDesc.m_pItemName = L"화살";
		tDesc.m_pDescription = L"흔하게 볼 수 있는 화살이다.";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 3.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"Arrow", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
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
	case MyGame::CItemFactory::ITEM_HEALPOTION:
		tDesc.m_iTextureID = 7;
		tDesc.m_pItemName = L"회복포션";
		tDesc.m_pDescription = L"먹으면 체력이 찬다.";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fHp = 20.f;
		tDesc.m_tStats = tStats;
		tDesc.m_Color = 0xffff0026;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"HealPotion", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_FIREPOTION:
		tDesc.m_iTextureID = 1;
		tDesc.m_pItemName = L"화염포션";
		tDesc.m_pDescription = L"뜨거운 기운이 느껴진다.";
		tStats.m_fAtt = 3.f;
		tDesc.m_tBaseDesc = _tDesc;
		tDesc.m_tStats = tStats;
		tDesc.m_Color = 0xffff8c09;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"FirePotion", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_PARALYZEPOTION:
		tDesc.m_iTextureID = 9;
		tDesc.m_pItemName = L"마비포션";
		tDesc.m_pDescription = L"유독한 마비가스가 담겨져있다.";
		tDesc.m_tBaseDesc = _tDesc;
		tDesc.m_tStats = tStats;
		tDesc.m_Color = 0xffd9ac00;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"ParalyzePotion", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_POSIONPOTION:
		tDesc.m_iTextureID = 5;
		tDesc.m_pItemName = L"독포션";
		tDesc.m_pDescription = L"심상치 않은 독의 기운이 느껴진다.";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 3.f;
		tDesc.m_tStats = tStats;
		tDesc.m_Color = 0xff00b43e;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"PosionPotion", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	default:
		break;
	}

	return pItem;
}

