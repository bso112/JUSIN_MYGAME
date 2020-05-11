#include "stdafx.h"
#include "Inventory.h"
#include "Item.h"
#include "ObjMgr.h"
#include "Hero.h"
USING(MyGame)

IMPLEMENT_SINGLETON(CInventory)

CInventory::CInventory()
	
{
	m_pHero = dynamic_cast<CHero*>(CObjMgr::Get_Instance()->Get_Player(SCENE_STAGE));
	if (nullptr == m_pHero)
		MSG_BOX("플레이어를 찾지 못하였습니다.");
}
HRESULT CInventory::Put_Item(CItem * _pItem)
{
	if (nullptr == _pItem)
		return E_FAIL;

	m_vecItem.push_back(_pItem);
	return S_OK;
}

CItem * CInventory::Get_Item(size_t _iIndex)
{
	if (_iIndex >= m_vecItem.size())
		return nullptr;

	return m_vecItem[_iIndex];
}

HRESULT CInventory::Use_item(size_t _iIndex, const _tchar* _pAction)
{
	if (_iIndex >= m_vecItem.size())
		return E_FAIL;

	m_vecItem[_iIndex]->Use(m_pHero, _pAction);
	return S_OK;
}

void CInventory::Free()
{
}
