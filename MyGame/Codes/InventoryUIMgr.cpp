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
	m_pItemInfoPanel = CItemInfoPanel::Create(_pGraphicDevice);
	
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;

	//원형생성
	pObjMgr->Add_Prototype(L"Inventory", SCENE_STAGE, m_pInventory);

	//복사본생성
	m_pInventory = dynamic_cast<CInventory*>(pObjMgr->Add_GO_To_Layer(L"Inventory", SCENE_STAGE, L"UI", SCENE_STAGE));
	RETURN_FAIL_IF_NULL(m_pInventory);
	Safe_AddRef(m_pInventory);

	//CItemInfoPanel::Set_Item의 첫번째인자로 m_pItemInfoPanel를 바인딩한다.
	function<void(CItem*)> setItemFunc = std::bind(&CItemInfoPanel::Set_Item, m_pItemInfoPanel, std::placeholders::_1);

	//슬롯을 클릭하면 InfoPanel에 아이템 정보를 연결한다.
	m_pInventory->Set_SlotListener(setItemFunc);
	//슬롯을 클릭하면 InfoPanel을 켠다.
	m_pInventory->Add_SlotListener([&] {m_pItemInfoPanel->Set_Active(true);});
	//아이템 정보 판넬의 버튼을 클릭하면 인벤토리를 닫는다. (아이템 판넬도 닫힌다)
	m_pItemInfoPanel->Add_ButtonListener([&] { m_pInventory->Set_Active(false);});

	



	
	return S_OK;
}


void CInventoryUIMgr::Active_Inventory()
{
	static _bool bActive = false;
	bActive = !bActive;
	m_pInventory->Set_Active(bActive);
}

void CInventoryUIMgr::Free()
{
	Safe_Release(m_pInventory);

}
