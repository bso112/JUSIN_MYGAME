#include "stdafx.h"
#include "..\Headers\Hero.h"
#include "LevelMgr.h"
#include "Transform.h"
#include "TurnMgr.h"
#include "Terrain.h"
#include "ObjMgr.h"
#include "Layer.h"
#include "StageUIMgr.h"
#include "Monster.h"
#include "ParticleSystem.h"
#include "Item.h"
#include "Equipment.h"
#include "InventoryUIMgr.h"
#include "Laser.h"
#include "wand.h"
USING(MyGame)



CHero::CHero(PDIRECT3DDEVICE9 _pGraphic_Device)
	: CCharacter(_pGraphic_Device)
{
	ZeroMemory(m_pAnimator, sizeof(m_pAnimator));
	ZeroMemory(m_pEquipments, sizeof(m_pEquipments));
	m_pName = L"당신";
}

CHero::CHero(CHero & _hero)
	: CCharacter(_hero)
{
	ZeroMemory(m_pAnimator, sizeof(m_pAnimator));
	ZeroMemory(m_pEquipments, sizeof(m_pEquipments));
	m_pName = L"당신";
}


HRESULT CHero::OnKeyDown(_int KeyCode)
{
	if (KeyCode == VK_LBUTTON)
	{
		if (nullptr == m_pTransform)
			return E_FAIL;


		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

#pragma region 예외처리

		vector<RECT> UIRect = CStageUIMgr::Get_Instance()->GetUIRect();
		for (auto& rc : UIRect)
		{
			//만약 마우스 포인트가 UI위에 있으면 무시
			if (PtInRect(&rc, pt))
			{
				return E_FAIL;
			}
		}
#pragma endregion


#pragma region 발사모드일때, 레이저모드일때
		//발사모드고, 발사할 아이템이 있으면
		if (m_bThrowMode && m_pItemToThrow)
		{
			if (nullptr == m_pItemToThrow)
			{
				m_bThrowMode = false;
				return E_FAIL;
			}
			//아이템을 던진다.
			m_pItemToThrow->Throw(pt);
			m_bThrowMode = false;
			m_pItemToThrow = nullptr;
			//끝낸다.
			return S_OK;
		}
		else if (m_bZapMode)
		{
			if (nullptr == m_pWandToZap)
			{
				m_bZapMode = false;
				return E_FAIL;
			}
			m_pWandToZap->Zap(m_pTransform->Get_Position(), pt);
			m_bZapMode = false;
			return S_OK;
		}
#pragma endregion


		CLevelMgr* pLevelMgr = CLevelMgr::Get_Instance();

#pragma region 이동

		vector<CTerrain*> route;
		CLevel* pLevel = pLevelMgr->Get_CurrLevel();
		RETURN_FAIL_IF_NULL(pLevel);
		pLevel->Get_Route(m_pTransform->Get_Position(), pt, route, m_pTransform);

		//해당 루트를 따라가기 위해 필요한 턴수를 계산
		_int iTurnCnt = (_int)route.size() / m_pTransform->Get_Desc().movePerTurn;
		//최소 1턴
		if (iTurnCnt == 0) iTurnCnt = 1;

		if (!m_bParalyze)
			m_pTransform->Go_Route(route, 1.f, iTurnCnt);


#pragma endregion


		//플레이어가 움직일 턴 이동
		CTurnMgr::Get_Instance()->MoveTurn_Simultaneously(iTurnCnt);

		if (!m_bParalyze)
		{
			//턴 이동 후 인터렉트.
			//타일피킹
			CTerrain* pTerrain = pLevel->Pick_Tile(pt);
			//인터렉트한다.
			if (nullptr != pTerrain)
				pTerrain->Interact(this);

			//그외 오브젝트 피킹
			CGameObject* pObj = pLevelMgr->PickObject(pt);
			if (nullptr != pObj)
			{
				//인터렉트한다.
				Interact(pObj);
				//인터렉트 당한다. (몬스터는 제외. 몬스터와의 인터렉트는 턴으로 제어한다)
				CMonster* pMonster = dynamic_cast<CMonster*>(pObj);
				//NPC이거나 몬스터가 아니면 인터렉트
				if ((pMonster != nullptr && pMonster->Is_NPC()) || nullptr == pMonster)
					pObj->Interact(this);
			}

		}

	}

	return S_OK;
}

void CHero::OnAttack(CGameObject * _pOther)
{
	if (_pOther == nullptr ||
		m_pAnimator[m_eCurrCloth] == nullptr)
		return;

	m_pAnimator[m_eCurrCloth]->Play(L"attack");
}

HRESULT CHero::Set_InitialPos()
{
	if (m_pTransform == nullptr)
		return E_FAIL;

	CLevel* pLevel = CLevelMgr::Get_Instance()->Get_CurrLevel();

	if (nullptr == pLevel)
		return E_FAIL;

	m_pTransform->Set_Position(pLevel->Get_PlayerSpawnPos());
	return S_OK;


}

HRESULT CHero::Set_LastPos()
{
	if (m_pTransform == nullptr)
		return E_FAIL;

	CLevel* pLevel = CLevelMgr::Get_Instance()->Get_CurrLevel();

	if (nullptr == pLevel)
		return E_FAIL;

	m_pTransform->Set_Position(pLevel->Get_PlayerLastPos());
	return S_OK;

	return S_OK;
}


HRESULT CHero::PlayAnimation(const _tchar * _pTag)
{
	return m_pAnimator[m_eCurrCloth]->Play(_pTag);
}

bool CHero::Has_Key()
{
	CInventory* pInventory = CInventoryUIMgr::Get_Instance()->GetInventory();
	return pInventory->Use_Key();
}

HRESULT CHero::ThrowItem(CItem * _pItem)
{
	m_bThrowMode = true;
	m_pItemToThrow = _pItem;
	return S_OK;
}


HRESULT CHero::Equip(CEquipment * _pItem, BODYPART _eBodyPart)
{
	if (_eBodyPart >= BODY_END ||
		nullptr == _pItem)
		return E_FAIL;

	//이미 끼고 있으면 뺀다.
	if (nullptr != m_pEquipments[_eBodyPart])
		UnEquip(_eBodyPart);

	m_pEquipments[_eBodyPart] = _pItem;
	Safe_AddRef(_pItem);

	CEquipment::STATS itemStats = _pItem->Get_Stats();
	m_tStat.m_fArmor->AddModifier(itemStats.m_fArmor);
	m_tStat.m_fAtt->AddModifier(itemStats.m_fAtt);
	m_tStat.m_fMaxHp->AddModifier(itemStats.m_fMaxHP);

	//인벤토리 갱신
	CInventory* pInventory = CInventoryUIMgr::Get_Instance()->GetInventory();
	pInventory->Equip(_pItem, _eBodyPart);

	return S_OK;
}

HRESULT CHero::UnEquip(BODYPART _eBodyPart)
{
	if (_eBodyPart >= BODY_END ||
		nullptr == m_pEquipments[_eBodyPart])
		return E_FAIL;


	CEquipment::STATS itemStats = m_pEquipments[_eBodyPart]->Get_Stats();
	m_tStat.m_fArmor->RemoveModifire(itemStats.m_fArmor);
	m_tStat.m_fAtt->RemoveModifire(itemStats.m_fAtt);
	m_tStat.m_fMaxHp->RemoveModifire(itemStats.m_fMaxHP);

	Safe_Release(m_pEquipments[_eBodyPart]);

	//인벤토리 갱신
	CInventory* pInventory = CInventoryUIMgr::Get_Instance()->GetInventory();
	pInventory->UnEquip(_eBodyPart);

	return S_OK;
}

HRESULT CHero::Zap(CWand * _pWand)
{
	//레퍼런스카운트 안셌네.. 귀찮아서
	m_bZapMode = true;
	m_pWandToZap = _pWand;
	return S_OK;
}

void CHero::Set_Cloth(CLOTH _eCloth)
{
	if (CLOTH_END <= _eCloth)
		return;
	m_eCurrCloth = _eCloth;
	m_pAnimator[m_eCurrCloth]->Play(L"idle");
}

HRESULT CHero::Explore()
{
	CLevelMgr* pLevelMgr = CLevelMgr::Get_Instance();
	RETURN_FAIL_IF_NULL(pLevelMgr);
	ShowText(L"탐사", 0xffffffff);
	return pLevelMgr->Explore(m_pTransform->Get_Position());
}

void CHero::Free()
{
	for (int i = 0; i < BODY_END; ++i)
		Safe_Release(m_pEquipments[i]);

	for (int i = 0; i < CLOTH_END; ++i)
		Safe_Release(m_pAnimator[i]);

	CCharacter::Free();
}


