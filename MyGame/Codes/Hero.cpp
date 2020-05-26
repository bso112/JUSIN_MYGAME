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
USING(MyGame)



CHero::CHero(PDIRECT3DDEVICE9 _pGraphic_Device)
	: CCharacter(_pGraphic_Device)
{
	ZeroMemory(m_pAnimator, sizeof(m_pAnimator));
	ZeroMemory(m_pEquipments, sizeof(m_pEquipments));
	m_pName = L"���";
}

CHero::CHero(CHero & _hero)
	: CCharacter(_hero)
{
	ZeroMemory(m_pAnimator, sizeof(m_pAnimator));
	ZeroMemory(m_pEquipments, sizeof(m_pEquipments));
	m_pName = L"���";
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

#pragma region ����ó��

		vector<RECT> UIRect = CStageUIMgr::Get_Instance()->GetUIRect();
		for (auto& rc : UIRect)
		{
			//���� ���콺 ����Ʈ�� UI���� ������ ����
			if (PtInRect(&rc, pt))
			{
				return E_FAIL;
			}
		}
#pragma endregion


#pragma region �߻����϶�
	
		//�߻����, �߻��� �������� ������
		if (m_bThrowMode && m_pItemToThrow)
		{
			//�������� ������.
			m_pItemToThrow->Throw(pt);
			m_bThrowMode = false;
			m_pItemToThrow = nullptr;
			//������.
			return S_OK;
		}
#pragma endregion

		CLevelMgr* pLevelMgr = CLevelMgr::Get_Instance();

#pragma region �̵�

		vector<CTerrain*> route;
		CLevel* pLevel = pLevelMgr->Get_CurrLevel();
		RETURN_FAIL_IF_NULL(pLevel);
		pLevel->Get_Route(m_pTransform->Get_Position(), pt, route, m_pTransform);

		//�ش� ��Ʈ�� ���󰡱� ���� �ʿ��� �ϼ��� ���
		_int iTurnCnt = (_int)route.size() / m_pTransform->Get_Desc().movePerTurn;
		//�ּ� 1��
		if (iTurnCnt == 0) iTurnCnt = 1;
		m_pTransform->Go_Route(route, 1.f, iTurnCnt);
#pragma endregion


		//�÷��̾ ������ �� �̵�
		CTurnMgr::Get_Instance()->MoveTurn_Simultaneously(iTurnCnt);

		//�� �̵� �� ���ͷ�Ʈ.
		//Ÿ����ŷ
		CTerrain* pTerrain = pLevel->Pick_Tile(pt);
		//���ͷ�Ʈ�Ѵ�.
		if (nullptr != pTerrain)
			pTerrain->Interact(this);

		//�׿� ������Ʈ ��ŷ
		CGameObject* pObj = pLevelMgr->PickObject(pt);
		if (nullptr != pObj)
		{
			//���ͷ�Ʈ�Ѵ�.
			Interact(pObj);
			////���ͷ�Ʈ ���Ѵ�.
			pObj->Interact(this);
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

	//�̹� ���� ������ ����.
	if (nullptr != m_pEquipments[_eBodyPart])
		UnEquip(_eBodyPart);

	m_pEquipments[_eBodyPart] = _pItem;
	Safe_AddRef(_pItem);

	CEquipment::STATS itemStats = _pItem->Get_Stats();
	m_tStat.m_fArmor->AddModifier(itemStats.m_fArmor);
	m_tStat.m_fAtt->AddModifier(itemStats.m_fAtt);
	m_tStat.m_fMaxHp->AddModifier(itemStats.m_fMaxHP);

	//�κ��丮 ����
	CInventory* pInventory = CInventoryUIMgr::Get_Instance()->GetInventory();
	pInventory->Equip(_pItem, _eBodyPart);

	return S_OK;
}

HRESULT CHero::UnEquip(BODYPART _eBodyPart)
{
	if (_eBodyPart >= BODY_END	||
		nullptr == m_pEquipments[_eBodyPart])
		return E_FAIL;


	CEquipment::STATS itemStats = m_pEquipments[_eBodyPart]->Get_Stats();
	m_tStat.m_fArmor->RemoveModifire(itemStats.m_fArmor);
	m_tStat.m_fAtt->RemoveModifire(itemStats.m_fAtt);
	m_tStat.m_fMaxHp->RemoveModifire(itemStats.m_fMaxHP);

	Safe_Release(m_pEquipments[_eBodyPart]);

	//�κ��丮 ����
	CInventory* pInventory = CInventoryUIMgr::Get_Instance()->GetInventory();
	pInventory->UnEquip(_eBodyPart);

	return S_OK;
}

void CHero::Free()
{
	for (int i = 0; i < BODY_END; ++i)
		Safe_Release(m_pEquipments[i]);

	for (int i = 0; i < CLOTH_END; ++i)
		Safe_Release(m_pAnimator[i]);

	CCharacter::Free();
}


