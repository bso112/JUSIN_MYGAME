#include "stdafx.h"
#include "..\Headers\InventoryUIMgr.h"
#include "Inventory.h"
#include "ItemSlot.h"
#include "ItemInfoPanel.h"
#include "ObjMgr.h"


USING(MyGame)
IMPLEMENT_SINGLETON(CInventoryUIMgr)

HRESULT CInventoryUIMgr::Initialize(PDIRECT3DDEVICE9 _pGraphicDevice)
{

	m_pInventory = CInventory::Create(_pGraphicDevice);
	m_pItemInfoPanel = CItemInfoPanel::Create(_pGraphicDevice, Vector3(g_iWinCX >> 1, g_iWinCY >> 1));
	
	//void(MyGame::CItemInfoPanel::*)(MyGame::CItem* _pItem)
	//function<void(CItemInfoPanel&, CItem*)> tmp = &CItemInfoPanel::Set_Item;

	//슬롯을 클릭하면 InfoPanel에 아이템 정보를 연결한다.
	//m_pInventory->Set_SlotListener(&m_pItemInfoPanel->Set_Item, m_pItemInfoPanel);
	//슬롯을 클릭하면 InfoPanel을 켠다.
	m_pInventory->Add_SlotListener([&] {m_pItemInfoPanel->Set_Active(true);});
	//아이템 정보 판넬의 버튼을 클릭하면 인벤토리를 닫는다. (아이템 판넬도 닫힌다)
	m_pItemInfoPanel->Add_ButtonListener([&] { m_pInventory->Set_Active(false);});

	
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;
	pObjMgr->Add_Prototype(L"Inventory", SCENE_STAGE, m_pInventory);
	pObjMgr->Add_Prototype(L"ItemInfoPanel", SCENE_STAGE, m_pItemInfoPanel);

	m_pInventory = dynamic_cast<CInventory*>(pObjMgr->Add_GO_To_Layer(L"Inventory", SCENE_STAGE, L"UI", SCENE_STAGE));
	Safe_AddRef(m_pInventory);
	pObjMgr->Add_GO_To_Layer(L"ItemInfoPanel", SCENE_STAGE, L"UI", SCENE_STAGE);


	
	return S_OK;
}


void CInventoryUIMgr::Active_Inventory()
{
	static _bool bActive = false;
	m_pInventory->Set_Active(!bActive);
}

void CInventoryUIMgr::Free()
{
	Safe_Release(m_pInventory);
}
