#pragma once
#include "MyButton.h"
BEGIN(MyGame)
class CItem;
class CTransform;
class CVIBuffer;
class CItemInfoPanel;

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
public:
	_bool	IsEmpty(){ return m_listItem.empty(); }
	size_t	Get_ItemCnt() { return m_listItem.size(); }
	CItem*	Get_Item() { return m_listItem.back(); }

protected:
	virtual HRESULT	OnKeyDown(_int KeyCode) override;
	

public:
	static CItemSlot*	Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID);
	virtual void Free() override;
};
END
