#include "stdafx.h"
#include "..\Headers\QuestMgr.h"
#include "InventoryUIMgr.h"

USING(MyGame)
IMPLEMENT_SINGLETON(CQuestMgr)
HRESULT CQuestMgr::Reward(vector<CItem*>* _pItem)
{
	CInventoryUIMgr* pInvenMgr = CInventoryUIMgr::Get_Instance();
	RETURN_FAIL_IF_NULL(pInvenMgr);
	CInventory* pInven = pInvenMgr->GetInventory();
	RETURN_FAIL_IF_NULL(pInven);
	
	while (!_pItem->empty())
	{
		pInven->Put_Item(_pItem->back(), true);
		_pItem->pop_back();
	}

	return S_OK;
}

void CQuestMgr::Free()
{
}
