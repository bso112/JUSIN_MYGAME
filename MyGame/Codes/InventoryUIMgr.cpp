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

	//��������
	pObjMgr->Add_Prototype(L"Inventory", SCENE_STAGE, m_pInventory);

	//���纻����
	m_pInventory = dynamic_cast<CInventory*>(pObjMgr->Add_GO_To_Layer(L"Inventory", SCENE_STAGE, L"UI", SCENE_STAGE));
	RETURN_FAIL_IF_NULL(m_pInventory);
	Safe_AddRef(m_pInventory);

	//CItemInfoPanel::Set_Item�� ù��°���ڷ� m_pItemInfoPanel�� ���ε��Ѵ�.
	function<void(CItem*)> setItemFunc = std::bind(&CItemInfoPanel::Set_Item, m_pItemInfoPanel, std::placeholders::_1);

	//������ Ŭ���ϸ� InfoPanel�� ������ ������ �����Ѵ�.
	m_pInventory->Set_SlotListener(setItemFunc);
	//������ Ŭ���ϸ� InfoPanel�� �Ҵ�.
	m_pInventory->Add_SlotListener([&] {m_pItemInfoPanel->Set_Active(true);});
	//������ ���� �ǳ��� ��ư�� Ŭ���ϸ� �κ��丮�� �ݴ´�. (������ �ǳڵ� ������)
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
