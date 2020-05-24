#pragma once
#include "MyButton.h"
BEGIN(MyGame)
class CItem;
class CTransform;
class CVIBuffer;
class CItemInfoPanel;

//내용물 크기
#define CONTENTX 100.f
#define CONTENTY 100.f
class CItemSlot final: public CMyButton
{
private:
	explicit CItemSlot(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CItemSlot(CItemSlot& _rhs);
	virtual ~CItemSlot() = default;


private:
	function<void(CItem*)> m_pSlotListener = nullptr;
	list<CItem*>	m_listItem;

	
	
public:
	virtual HRESULT Initialize(Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID);
	virtual _int	Update(_double _timeDelta)	override;
	virtual _int	LateUpate(_double _timeDelta)override;
	virtual HRESULT	Render() override;
	


public:
	HRESULT	Add_Item(CItem* _pItem);
	virtual HRESULT	Set_Listener(function<void(CItem*)> _listener);
	//슬롯이 가지고 있는 아이템이 사용되면 아이템을 지운다.
	HRESULT	Remove_Item();
	//슬롯이 가지고 있는 아이템을 오브젝트 매니저에 등록하고, 슬롯의 아이템 리스트에서 제거함.
	HRESULT	Drop_Item();
	//장비 슬롯은 하나의 아이템만을 가진다.
	void	Equip(CItem* _pItem);
	CItem*	UnEquip();
public:
	_bool	IsEmpty(){ return m_listItem.empty(); }
	_bool	Has_Item(CItem* _pItem);
	size_t	Get_ItemCnt() { return m_listItem.size(); }
	CItem*	Get_Item() { return m_listItem.back(); }
	void	Clear();
protected:
	virtual	void OnSetActive(_bool _bActive);

protected:
	virtual HRESULT	OnKeyDown(_int KeyCode) override;
	

public:
	static CItemSlot*	Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID);
	virtual void Free() override;
};
END
