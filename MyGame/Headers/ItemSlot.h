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
	function<void(CItemInfoPanel&, CItem*)> m_pSlotListener = nullptr;
	//아이템의 정보를 보여줄 판넬
	CItemInfoPanel* m_pInfoPanel = nullptr;
	list<CItem*>	m_listItem;
	
public:
	HRESULT	Add_Item(CItem* _pItem);
	virtual HRESULT	Set_Listener(function<void(CItemInfoPanel&, CItem*)> _listener, CItemInfoPanel* _pPanel);
	HRESULT	Remove_Item();
	virtual _int	Update(_double _timeDelta)	override;

public:
	_bool	IsEmpty(){ return m_listItem.empty(); }
	size_t	Get_ItemCnt() { return m_listItem.size(); }
	CItem*	Get_Item() { return m_listItem.back(); }
	

public:
	static CItemSlot*	Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID);
	virtual void Free() override;
};
END
