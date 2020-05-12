#include "stdafx.h"
#include "..\Headers\ItemSlot.h"

USING(MyGame)

CItemSlot::CItemSlot(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CMyButton(_pGraphic_Device), m_pItem(nullptr)
{
}

CItemSlot::CItemSlot(CItemSlot & _rhs)
	:CMyButton(_rhs)
{
}

HRESULT CItemSlot::Add_Item(CItem * _pItem)
{
	return E_NOTIMPL;
}

HRESULT CItemSlot::Remove_Item(CItem * _pItem)
{
	return E_NOTIMPL;
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
