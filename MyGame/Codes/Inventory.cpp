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
	if (FAILED(Set_Module(L"inventory", SCENE_STAGE, (CModule**)&m_pTexture)))
		return E_FAIL;

	m_bActive = false;

	m_pTransform->Set_Position(Vector2(float(g_iWinCX >> 1), float(g_iWinCY >> 1)));
	m_pTransform->Set_Size(Vector2(INVENCX, INVENCY));
	m_pHero = dynamic_cast<CHero*>(CObjMgr::Get_Instance()->Get_Player(SCENE_STAGE));
	if (nullptr == m_pHero)
		MSG_BOX("플레이어를 찾지 못하였습니다.");


	Vector3 vPos = m_pTransform->Get_Position();

	for (int i = 0; i < INVENY; ++i)
	{
		for (int j = 0; j < INVENX; ++j)
		{
			Vector2 vPos = Vector2((float)INVEN_MARGIN_H + (SLOTCX>>1) + SLOTCX * j, (float)INVEN_MARGIN_V + (SLOTCY >>1) + SLOTCY * i);
			CItemSlot* pSlot = CItemSlot::Create(m_pGraphic_Device, vPos, Vector2(SLOTCX, SLOTCY), L"slot", SCENE_STAGE);
			if (nullptr == pSlot)
				return E_FAIL;
			m_vecSlot.push_back(pSlot);

		}
	}


	return S_OK;
}

_int CInventory::Update(_double _timeDelta)
{
	if (!m_bActive)
		return 0;

	m_pTransform->Update(_timeDelta);

	for (auto& slot : m_vecSlot)
	{
		slot->Update(_timeDelta);
	}
	return 0;
}

_int CInventory::LateUpate(_double _timeDelta)
{
	if (!m_bActive)
		return 0;

	for (auto& slot : m_vecSlot)
	{
		slot->LateUpate(_timeDelta);
	}

	m_pTransform->Late_Update();
	m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_UI);
	return 0;
}

HRESULT CInventory::Render()
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pTexture ||
		nullptr == m_pVIBuffer ||
		nullptr == m_pTransform )
		return E_FAIL;

	ALPHABLEND;

	m_pTexture->Set_Texture(0);
	m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix());
	m_pVIBuffer->Render();
	
	for (auto& slot : m_vecSlot)
	{
		slot->Render();
	}

	
	ALPHABLEND_END;
	return S_OK;


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



HRESULT CInventory::Set_SlotListener(function<void(CItemInfoPanel&, CItem*)> _func, CItemInfoPanel* _pInfoPanel)
{
	for (auto& slot : m_vecSlot)
	{
		slot->Set_Listener(_func, _pInfoPanel);
	}
	return S_OK;
}

HRESULT CInventory::Add_SlotListener(function<void()> _func)
{
	for (auto& slot : m_vecSlot)
	{
		slot->Add_Listener(_func);
	}
	return S_OK;
}

void CInventory::Free()
{
	Safe_Release(m_pTexture);
	Safe_Release(m_pTransform);
	Safe_Release(m_pVIBuffer);

	for (auto& slot : m_vecSlot)
	{
		Safe_Release(slot);
	}
	CGameObject::Free();
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

CGameObject * CInventory::Clone(void * _param)
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
