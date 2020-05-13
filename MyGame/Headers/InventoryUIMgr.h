#pragma once
#include "Base.h"
BEGIN(MyGame)
class CInventory;
class CItemInfoPanel;
class InventoryUIMgr : public CBase
{
	DECLARE_SINGLETON(InventoryUIMgr);
public:
	explicit InventoryUIMgr() {};
	virtual ~InventoryUIMgr() = default;

private:
	CInventory*		m_pInventory = nullptr;
	CItemInfoPanel*	m_pItemInfoPanel = nullptr;
public:
	HRESULT	Initialize(PDIRECT3DDEVICE9 _pGraphicDevice);
	_int	Update();
	HRESULT	Render();
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};
END
