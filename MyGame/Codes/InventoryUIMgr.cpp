#include "stdafx.h"
#include "..\Headers\InventoryUIMgr.h"
#include "Inventory.h"
#include "ItemSlot.h"
#include "ItemInfoPanel.h"
#include "ObjMgr.h"
#include "Transform.h"


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
	m_pItemInfoPanel = dynamic_cast<CItemInfoPanel*>(pObjMgr->Add_GO_To_Layer(L"Inventory", SCENE_STAGE, m_pItemInfoPanel));
	RETURN_FAIL_IF_NULL(m_pItemInfoPanel);
	Safe_AddRef(m_pItemInfoPanel);

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


vector<RECT> CInventoryUIMgr::GetUIRect()
{
	vector<RECT> rc;
	
	//�κ��丮�� Ȱ��ȭ ���¸�
	if (m_pInventory->Get_Active())
	{
		//RECT�� ���� �Ѱ��ش�.
		CTransform* pInvenTransform = (CTransform*)m_pInventory->Get_Module(L"Transform");
		if (nullptr == pInvenTransform)
			return rc;
		rc.push_back(pInvenTransform->Get_RECT());

	}
	if (m_pItemInfoPanel->Get_Active())
	{
		CTransform* pItemInfoPanelTransform = (CTransform*)m_pItemInfoPanel->Get_Module(L"Transform");
		if (nullptr == pItemInfoPanelTransform)
			return rc;
		rc.push_back(pItemInfoPanelTransform->Get_RECT());

	}

	return rc;
}

void CInventoryUIMgr::Active_Inventory()
{
	m_pInventory->Set_Active(!m_pInventory->Get_Active());
}

void CInventoryUIMgr::Free()
{
	Safe_Release(m_pItemInfoPanel);
	Safe_Release(m_pInventory);

}
