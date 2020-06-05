#include "stdafx.h"
#include "Inventory.h"
#include "Item.h"
#include "Key.h"
#include "ObjMgr.h"
#include "Hero.h"
#include "ItemSlot.h"
#include "ItemInfoPanel.h"
#include "ItemFactory.h"
#include "ModuleMgr.h"
#include "Spawner.h"
#include "DialogMgr.h"
USING(MyGame)


CInventory::CInventory(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CGameObject(_pGraphic_Device)
{
}

CInventory::CInventory(CInventory & _rhs)
	: CGameObject(_rhs)
{
	m_vecItemSlot.reserve(SLOTX * SLOTY);
}

HRESULT CInventory::Initialize(void * _pArg)
{

	m_iDepth = 0;
	m_vecEquipSlot.reserve(4);

	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform)))
		return E_FAIL;
	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;
	if (FAILED(Set_Module(L"inventory", SCENE_STAGE, (CModule**)&m_pTexture)))
		return E_FAIL;

	m_bActive = false;

	m_pTransform->Set_Position(Vector2(float(g_iWinCX >> 1), float(g_iWinCY >> 1)));
	m_pTransform->Set_Size(Vector2(INVENCX, INVENCY));



	RECT invenRc = m_pTransform->Get_RECT();
	_float	margin_slot = 3.f;

	//모든 슬롯이 들어갈 RECT의 X크기, Y크기
	_float slotRcX = (INVENCX - (INVEN_MARGIN_H << 1));
	_float slotRcY = (INVENCY - (INVEN_MARGIN_V << 1));

	//슬롯 하나의 크기
	_float slotCX = (slotRcX - (margin_slot * SLOTX - 1)) / SLOTX;
	_float slotCY = (slotRcY - (margin_slot * SLOTY - 1)) / SLOTY;

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;

	CModuleMgr::Get_Instance()->Add_Module(L"Texture_EquipSlot", SCENE_STAGE, CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/UI/Stage/equipSlot%d.png", 4));
		

	for (int i = 0; i < SLOTY; ++i)
	{
		for (int j = 0; j < SLOTX; ++j)
		{
			Vector2 vPos = Vector2(
				invenRc.left + (float)INVEN_MARGIN_H + (slotCX*0.5f) + (slotCX + margin_slot) * j,
				invenRc.top + (float)INVEN_MARGIN_V + (slotCY*0.5f) + (slotCY + margin_slot) * i);


			//슬롯을 오브젝트 매니저에 등록안하고 렌더러에만 등록하면
			//렌더러가 슬롯을 지워버린다. 원래 렌더러는 한프레임 그리고 다 지우니까.
			CItemSlot* pSlot;
			if (i == 0 && j < 4)
			{
				pSlot = CItemSlot::Create(m_pGraphic_Device, vPos, Vector2(slotCX, slotCY), L"Texture_EquipSlot", SCENE_STAGE, j);
				pSlot->Set_Equipmentslot();
			}
			else
				pSlot = CItemSlot::Create(m_pGraphic_Device, vPos, Vector2(slotCX, slotCY), L"slot", SCENE_STAGE);

			if (nullptr == pSlot)
				return E_FAIL;

			pSlot->Set_Depth(m_iDepth + 1);
			pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, pSlot);

			if (i == 0 && j < 4)
				m_vecEquipSlot.push_back(pSlot);
			else
				m_vecItemSlot.push_back(pSlot);
			Safe_AddRef(pSlot);

		}
	}



	RECT rc = m_pTransform->Get_RECT();
	m_tTitlePlaceHolder = Make_Rect(Vector2(rc.left + 50.f + 37.f, rc.top +37.f), Vector2(100.f, 40.f, 1.f));


	return S_OK;
}

_int CInventory::Update(_double _timeDelta)
{
	if (!m_bActive)
		return 0;

	return 0;
}

_int CInventory::LateUpate(_double _timeDelta)
{
	if (!m_bActive)
		return 0;

	m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_UI);

	return 0;
}

HRESULT CInventory::Render()
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pTexture ||
		nullptr == m_pVIBuffer ||
		nullptr == m_pTransform)
		return E_FAIL;

	ALPHABLEND;

	m_pTexture->Set_Texture(0);
	m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix());
	m_pVIBuffer->Render();

	g_pFontX3->DrawText(NULL, L"배낭", -1,&m_tTitlePlaceHolder, DT_LEFT, COLOR_YELLOW);
	ALPHABLEND_END;
	return S_OK;


}

HRESULT CInventory::Initialize_Prototype()
{
	m_vecItemSlot.reserve(SLOTX * SLOTY);
	return S_OK;
}


HRESULT CInventory::Equip(CItem* _pEquipment, BODYPART _eBodyPart)
{

	if (_eBodyPart >= BODY_END ||
		_eBodyPart >= m_vecEquipSlot.size() ||
		nullptr == _pEquipment)
		return E_FAIL;

	CItem* pItem = nullptr;
	//슬롯을 순회해서 해당 아이템을 가지고 있는 슬롯을 찾는다.
	for (auto& slot : m_vecItemSlot)
	{
		//찾았으면
		if (slot->Has_Item(_pEquipment))
		{
			//찾은 슬롯을 클리어하고
			pItem = slot->UnEquip();
			if (nullptr == pItem)
				return E_FAIL;

		}
	}
	//장비슬롯에도 있을 가능성이 있음.
	for (auto& slot : m_vecEquipSlot)
	{
		//찾았으면
		if (slot->Has_Item(_pEquipment))
		{
			//찾은 슬롯을 클리어하고
			pItem = slot->UnEquip();
			if (nullptr == pItem)
				return E_FAIL;

		}
	}
	//찾은 아이템을 장착한다.
	m_vecEquipSlot[_eBodyPart]->Equip(pItem);
	return S_OK;
}

HRESULT CInventory::UnEquip(BODYPART _eBodyPart)
{
	if (_eBodyPart >= BODY_END ||
		_eBodyPart >= m_vecEquipSlot.size())
		return E_FAIL;


	//장착슬롯에 있는 아이템을 빼서 다시 인벤토리에 넣는다.
	CItem* pUnEquipped = m_vecEquipSlot[_eBodyPart]->UnEquip();
	if (nullptr == pUnEquipped)
		return E_FAIL;
	Put_Item(pUnEquipped);
	return S_OK;
}

HRESULT CInventory::Put_Item(CItem * _pItem, _bool _bReward)
{
	if (nullptr == _pItem)
		return E_FAIL;

	if (m_vecItemSlot.empty())
		return E_FAIL;

	for (auto& pSlot : m_vecItemSlot)
	{
		CItem* pSlotItem = pSlot->Get_Item();

		//슬롯이 완전히 비어있거나, 비어있지 않아도 같은 종류의 아이템이고 스택가능하면
		if (pSlot->IsEmpty() || (pSlotItem != nullptr && pSlotItem->CanStackWith(_pItem)))
		{
			//그 슬롯에 넣는다.
			pSlot->Add_Item(_pItem);
			_pItem->SetDrop(false);
			if(_bReward)
				CDialogMgr::Get_Instance()->Log_Main(MSG_PICK(_pItem->Get_Name()), 0xff00ff1a);
			else
				CDialogMgr::Get_Instance()->Log_Main(MSG_PICK(_pItem->Get_Name()), 0xffffffff);
			break;
		}
	}

	return S_OK;
}

void CInventory::Put_Key(CKey * _pKey)
{
	m_vecKey.push_back(_pKey);
	Safe_AddRef(_pKey);
}

_bool CInventory::Use_Key()
{
	if (m_vecKey.empty())
		return false;

	//키를 소모한다.
	m_vecKey.back()->Use();
	//레퍼런스감소
	Safe_Release(m_vecKey.back());
	//공간 지움
	m_vecKey.pop_back();
	return true;
}




HRESULT CInventory::Set_SlotListener(function<void(CItem*)> _func)
{
	for (auto& slot : m_vecItemSlot)
		slot->Set_Listener(_func);

	for (auto& slot : m_vecEquipSlot)
		slot->Set_Listener(_func);



	return S_OK;
}

HRESULT CInventory::Add_SlotListener(function<void()> _func)
{
	for (auto& slot : m_vecItemSlot)
		slot->Add_Listener(_func);

	for (auto& slot : m_vecEquipSlot)
		slot->Add_Listener(_func);

	return S_OK;
}

void CInventory::OnSetActive(_bool _bActive)
{
	for (auto& slot : m_vecItemSlot)
		slot->Set_Active(_bActive);
	for (auto& slot : m_vecEquipSlot)
		slot->Set_Active(_bActive);

}

void CInventory::Free()
{
	Safe_Release(m_pTexture);
	Safe_Release(m_pTransform);
	Safe_Release(m_pVIBuffer);

	for (auto& key : m_vecKey)
		Safe_Release(key);

	for (auto& slot : m_vecEquipSlot)
		Safe_Release(slot);

	for (auto& slot : m_vecItemSlot)
		Safe_Release(slot);

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
