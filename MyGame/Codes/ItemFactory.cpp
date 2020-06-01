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
		tDesc.m_pDescription = L"ª�� ���̴�. �����̳� ��Ƹ��� �� �ְڴ�.";
		tDesc.m_pItemName = L"���ҵ�";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 3.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_LONGSWORD:
		tDesc.m_iTextureID = 2;
		tDesc.m_pDescription = L"�� ���̴�. ���԰� �ϳ�����.";
		tDesc.m_pItemName = L"�ռҵ�";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 5.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_DAGGER:
		tDesc.m_iTextureID = 3;
		tDesc.m_pDescription = L"�������̳� �ϻ쿡 ������ �� �ϴ�.";
		tDesc.m_pItemName = L"���";
		tStats.m_fAtt = 2.f;
		tDesc.m_tBaseDesc = _tDesc;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_IRONSWORD:
		tDesc.m_iTextureID = 5;
		tDesc.m_pItemName = L"ö��";
		tDesc.m_pDescription = L"������ �ܴ��� ���̴� ���̴�.";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 6.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_BATTLEAXE:
		tDesc.m_iTextureID = 7;
		tDesc.m_pItemName = L"��������";
		tDesc.m_pDescription = L"�߸����� ����ϴ� ����";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 6.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_GOLDAXE:
		tDesc.m_iTextureID = 8;
		tDesc.m_pItemName = L"Ȳ�ݸ�ġ";
		tDesc.m_pDescription = L"������ �� ��ġ��. ��� ���ڰ� �������.";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 5.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_SPEAR:
		tDesc.m_iTextureID = 9;
		tDesc.m_pItemName = L"â";
		tDesc.m_pDescription = L"����� â�̴�. �� ������ ���� ���� �� ����.";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 5.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_TRIDENT:
		tDesc.m_iTextureID = 10;
		tDesc.m_pItemName = L"����â";
		tDesc.m_pDescription = L"�ϳ� ���ִ�.";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 7.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_MACE:
		tDesc.m_iTextureID = 11;
		tDesc.m_pItemName = L"���̽�";
		tDesc.m_pDescription = L"�׳� ��� ������ �ȴ�.";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fAtt = 4.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"MeleeWeapon", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_LETHERARMOR:
		tDesc.m_iTextureID = 2;
		tDesc.m_pItemName = L"���װ���";
		tDesc.m_pDescription = L"� ������ �����ϱ�?";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fArmor = 2.f;
		tDesc.m_tStats = tStats;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"Armor", SCENE_STAGE,layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_CHAINARMOR:
		tDesc.m_iTextureID = 6;
		tDesc.m_pItemName = L"�罽����";
		tDesc.m_pDescription = L"�����϶����� �Ҹ�������.";
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
		tDesc.m_pItemName = L"ȭ��";
		tDesc.m_pDescription = L"���ϰ� �� �� �ִ� ȭ���̴�.";
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
		tDesc.m_pItemName = L"ȸ������";
		tDesc.m_pDescription = L"������ ü���� ����.";
		tDesc.m_tBaseDesc = _tDesc;
		tStats.m_fHp = 20.f;
		tDesc.m_tStats = tStats;
		tDesc.m_Color = 0xffff0026;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"HealPotion", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_FIREPOTION:
		tDesc.m_iTextureID = 1;
		tDesc.m_pItemName = L"ȭ������";
		tDesc.m_pDescription = L"�߰ſ� ����� ��������.";
		tStats.m_fAtt = 3.f;
		tDesc.m_tBaseDesc = _tDesc;
		tDesc.m_tStats = tStats;
		tDesc.m_Color = 0xffff8c09;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"FirePotion", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_PARALYZEPOTION:
		tDesc.m_iTextureID = 9;
		tDesc.m_pItemName = L"��������";
		tDesc.m_pDescription = L"������ ���񰡽��� ������ִ�.";
		tDesc.m_tBaseDesc = _tDesc;
		tDesc.m_tStats = tStats;
		tDesc.m_Color = 0xffd9ac00;
		pItem = (CItem*)pObjMgr->Add_GO_To_Layer(L"ParalyzePotion", SCENE_STAGE, layerTag, SCENE_STAGE, &tDesc);
		break;
	case MyGame::CItemFactory::ITEM_POSIONPOTION:
		tDesc.m_iTextureID = 5;
		tDesc.m_pItemName = L"������";
		tDesc.m_pDescription = L"�ɻ�ġ ���� ���� ����� ��������.";
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

