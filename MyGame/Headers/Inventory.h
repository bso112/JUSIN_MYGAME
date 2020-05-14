#pragma once
#include "GameObject.h"


BEGIN(MyGame)
class CItem;
class CHero;
class CTransform;
class CTexture;
class CVIBuffer;
class CItemSlot;
class CItemInfoPanel;
#define INVENCX 730 // 670
#define INVENCY 500 // 380
#define INVEN_MARGIN_H 30
#define INVEN_MARGIN_V 70
#define SLOTX 6
#define SLOTY 4

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
	_int	Update(_double _timeDelta) override;
	virtual _int	LateUpate(_double _timeDelta) override;
	virtual HRESULT	Render() override;
	HRESULT Remove_Item(size_t _iIndex);
	HRESULT	Put_Item(CItem* _pItem);

public:
	HRESULT	Set_SlotListener(function<void(CItem*)> _func);
	HRESULT	Add_SlotListener(function<void()> _func);



public:
	static CInventory*	Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CGameObject * Clone(void * _param = nullptr) override;
	virtual void Free() override;

};

END