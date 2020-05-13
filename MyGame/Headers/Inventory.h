#pragma once
#include "GameObject.h"
BEGIN(MyGame)
class CItem;
class CHero;
class CTransform;
class CTexture;
class VIBuffer;
class CItemSlot;
class CItemInfoPanel;
#define INVENX 4
#define INVENY 6
#define INVENCX 500
#define INVENCY 600
#define INVEN_MARGIN_H 50
#define INVEN_MARGIN_V 50 
#define SLOTCX 60
#define SLOTCY 60

class CInventory final : public CGameObject
{
private:
	explicit CInventory(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CInventory(CInventory& _rhs);
	virtual ~CInventory() = default;

private:
	CTransform*			m_pTransform = nullptr;
	CVIBuffer*			m_pVIBuffer = nullptr;
	CTexture*			m_pTexture = nullptr;
	
private:
	vector<CItemSlot*>	m_vecSlot;
	CHero*	m_pHero;
public:
	HRESULT	Initialize_Prototype();
	HRESULT	Initialize(void* _pArg);
	_int	Update(_double _timeDelta);
	HRESULT Remove_Item(size_t _iIndex);
	HRESULT	Put_Item(CItem* _pItem);
	HRESULT	Use_item(size_t _iIndex, const _tchar* _pAction);

public:
	HRESULT	Add_SlotListenr(function<void(CItemInfoPanel&)> _func);


public:
	static CInventory*	Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CGameObject * Clone(void * _param = nullptr) override;
	virtual void Free() override;

};

END