#pragma once
#include "MyButton.h"
BEGIN(MyGame)
class CItem;
class CTransform;
class CVIBuffer;

class CItemSlot final: public CMyButton
{
private:
	explicit CItemSlot(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CItemSlot(CItemSlot& _rhs);
	virtual ~CItemSlot() = default;


private:
	CItem*	m_pItem = nullptr;
	_uint	m_iItemCnt = 0;
	
public:
	HRESULT	Add_Item(CItem* _pItem);
	HRESULT	Remove_Item(CItem* _pItem);

public:
	_bool	IsEmpty(){ return m_pItem == nullptr; }
	_uint	Get_ItemCnt() { return m_iItemCnt; }
	CItem*	Get_Item() { return m_pItem; }
	

public:
	static CItemSlot*	Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID);
	virtual void Free() override;
};
END
