#include "stdafx.h"
#include "..\Headers\InventoryUIMgr.h"
#include "Inventory.h"
#include "ItemSlot.h"
#include "ItemInfoPanel.h"
USING(MyGame)
IMPLEMENT_SINGLETON(InventoryUIMgr)

HRESULT InventoryUIMgr::Initialize(PDIRECT3DDEVICE9 _pGraphicDevice)
{

	m_pInventory = CInventory::Create(_pGraphicDevice);
	m_pItemInfoPanel = CItemInfoPanel::Create(_pGraphicDevice, Vector3(g_iWinCX >> 1, g_iWinCY >> 1));
	
	m_pInventory->
	return S_OK;
}

_int InventoryUIMgr::Update()
{

	return _int();
}

HRESULT InventoryUIMgr::Render()
{
	return E_NOTIMPL;
}

void InventoryUIMgr::Free()
{
}
