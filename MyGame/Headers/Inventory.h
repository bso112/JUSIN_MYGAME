#pragma once
#include "Base.h"
BEGIN(MyGame)
class CItem;
class CHero;

#define INVENX 4
#define INVENY 6
class CInventory final : public CBase
{
	DECLARE_SINGLETON(CInventory)
protected:
	explicit CInventory();
	virtual ~CInventory() = default;

private:
	typedef vector<CItem*> slot;
	slot	m_vecItem[INVENX][INVENY];
	CHero*	m_pHero;
public:
	HRESULT	Put_Item(CItem* _pItem);
	HRESULT	Remove_Item(CItem* _pItem);
	CItem*	Get_Item(size_t _iIndex);
	HRESULT	Use_item(size_t _iIndex, const _tchar* _pAction);


	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};

END