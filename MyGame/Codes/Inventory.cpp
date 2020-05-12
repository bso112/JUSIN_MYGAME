#include "stdafx.h"
#include "Inventory.h"
#include "Item.h"
#include "ObjMgr.h"
#include "Hero.h"
#include "ItemSlot.h"
#include "ItemInfoPanel.h"
USING(MyGame)


CInventory::CInventory(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CGameObject(_pGraphic_Device)
{

}

CInventory::CInventory(CInventory & _rhs)
	: CGameObject(_rhs)
{
}

HRESULT CInventory::Initialize(void * _pArg)
{
	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform)))
		return E_FAIL;
	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;
	if (FAILED(Set_Module(L"Texture_Inven", SCENE_STAGE, (CModule**)&m_pTexture)))
		return E_FAIL;


	if (nullptr != _pArg)
	{
		BASEDESC* desc = static_cast<BASEDESC*>(_pArg);
		if (nullptr == desc)
		{
			MSG_BOX("void*를 BASEDESC*로 변환할 수 없습니다.");
			return E_FAIL;
		}
		m_pTransform->Set_Position(desc->vPos);

	}

	m_pTransform->Set_Size(Vector2(INVENCX, INVENCY));
	m_pHero = dynamic_cast<CHero*>(CObjMgr::Get_Instance()->Get_Player(SCENE_STAGE));
	if (nullptr == m_pHero)
		MSG_BOX("플레이어를 찾지 못하였습니다.");


	Vector3 vPos = m_pTransform->Get_Position();

	for (int i = 0; i < INVENY; ++i)
	{
		for (int j = 0; j < INVENX; ++j)
		{
			Vector2 vPos = Vector2(INVEN_MARGIN_H + (SLOTCX>>1) + SLOTCX * j, INVEN_MARGIN_V + (SLOTCY >>1) + SLOTCY * i);
			m_vecSlot.push_back(CItemSlot::Create(m_pGraphic_Device, vPos, Vector2(SLOTCX, SLOTCY), L"Texture_Inven", SCENE_STAGE));

		}
	}

	m_pInfoPanel = CItemInfoPanel::Create(m_pGraphic_Device, m_pTransform->Get_Position());
	

	return S_OK;
}

_int CInventory::Update(_double _timeDelta)
{
	for (auto& slot : m_vecSlot)
	{
		slot->Update();
	}
	return _int();
}

HRESULT CInventory::Initialize_Prototype()
{
	m_vecSlot.reserve(INVENX * INVENY);

	return S_OK;
}
HRESULT CInventory::Put_Item(CItem * _pItem)
{
	if (nullptr == _pItem)
		return E_FAIL;

	for (auto& pSlot : m_vecSlot)
	{
		if (pSlot->IsEmpty())
		{
			pSlot->Add_Item(_pItem);
			break;
		}
	}
	return S_OK;
}

HRESULT CInventory::Remove_Item(size_t _iIndex)
{
	return S_OK;
}


HRESULT CInventory::Use_item(size_t _iIndex, const _tchar* _pAction)
{
	if (_iIndex >= m_vecSlot.size())
		return E_FAIL;

	m_vecSlot[_iIndex]->Get_Item()->Use(m_pHero, _pAction);
	
return S_OK;
}

void CInventory::Free()
{
}

CInventory * CInventory::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CInventory* pInstance = new CInventory(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CMyButton");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CInventory::Clone(void * _param = nullptr)
{
	CInventory* pInstance = new CInventory(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to clone CMyButton");
		Safe_Release(pInstance);

	}
	return pInstance;

	return nullptr;
}
