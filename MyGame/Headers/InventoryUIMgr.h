#pragma once
#include "Base.h"
#include "Inventory.h"
BEGIN(MyGame)
class CItemInfoPanel;
class CInventoryUIMgr : public CBase
{
	DECLARE_SINGLETON(CInventoryUIMgr)
public:
	explicit CInventoryUIMgr() {};
	virtual ~CInventoryUIMgr() = default;

private:
	CInventory*		m_pInventory = nullptr;
	CItemInfoPanel*	m_pItemInfoPanel = nullptr;
public:
	HRESULT	Initialize(PDIRECT3DDEVICE9 _pGraphicDevice);

public:
	CInventory*		GetInventory() { return m_pInventory; }

public:
	void	Active_Inventory();
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};
END
