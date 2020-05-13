#include "stdafx.h"
#include "ItemSlot.h"
#include "Item.h"
USING(MyGame)

CItemSlot::CItemSlot(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CMyButton(_pGraphic_Device)
{
}

CItemSlot::CItemSlot(CItemSlot & _rhs)
	:CMyButton(_rhs)
{
}

HRESULT CItemSlot::Add_Item(CItem * _pItem)
{
	if (nullptr == _pItem)
		return E_FAIL;
	m_listItem.push_back(_pItem);
	return S_OK;
}

HRESULT CItemSlot::Add_Listener(function<void(CItemInfoPanel&, CItem*)> _listener)
{
	m_pSlotListener = _listener;
	return S_OK;
}

HRESULT CItemSlot::Remove_Item()
{
	if (m_listItem.empty())
		return E_FAIL;

	m_listItem.pop_back();

	return S_OK;
}

_int CItemSlot::Update(_double _timeDelta)
{
	CMyButton::Update(_timeDelta);
	
	if (m_listItem.back()->Get_Dead())
	{
		Remove_Item();
	}

	return 0;
}

CItemSlot * CItemSlot::Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID)
{
	CItemSlot* pInstance = new CItemSlot(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_vPos, _vSize, _pTextureTag, _eTextureSceneID)))
	{
		MSG_BOX("Fail to create CMyButton");
		Safe_Release(pInstance);

	}
	return pInstance;
}



void CItemSlot::Free()
{
}
