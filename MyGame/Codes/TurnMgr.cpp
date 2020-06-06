#include "stdafx.h"
#include "..\Headers\TurnMgr.h"
#include "Layer.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "GameObject.h"
#include "TimerMgr.h"
#include "Character.h"
#include "Spawner.h"

USING(MyGame)
IMPLEMENT_SINGLETON(CTurnMgr)

CTurnMgr::CTurnMgr()
{
	ZeroMemory(m_pActorLayers, sizeof(m_pActorLayers));
}

CTurnMgr::CTurnMgr(CTurnMgr & _rhs)
{
}


HRESULT CTurnMgr::Initialize()
{
	m_eCurrScene = CSceneMgr::Get_Instance()->Get_CurrScene();

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	RETURN_FAIL_IF_NULL(pObjMgr);

	pObjMgr->Make_Layer(L"Effect", SCENE_STAGE);

	CLayer* pLayer = pObjMgr->Find_Layer(L"Effect", SCENE_STAGE);
	if (nullptr == pLayer)
		MSG_BOX("����Ʈ ���̾ �����ϴ�.");

	m_pActorLayers[0] = pLayer;
	Safe_AddRef(m_pActorLayers[0]);

	pLayer = pObjMgr->Find_Layer(L"Player", SCENE_STAGE);
	if (nullptr == pLayer)
		MSG_BOX("�÷��̾� ���̾ �����ϴ�.");

	m_pActorLayers[1] = pLayer;
	Safe_AddRef(m_pActorLayers[1]);

	pLayer = pObjMgr->Find_Layer(L"Monster", SCENE_STAGE);
	if (nullptr == pLayer)
		MSG_BOX("���� ���̾ �����ϴ�.");

	m_pActorLayers[2] = pLayer;
	Safe_AddRef(m_pActorLayers[2]);


	return S_OK;
}




_int CTurnMgr::Update_Simultaneously()
{

	/*
	1. ���� �����δ�.
	2. �������� ���� ����� ��� ����� �������� ���������� ����Ѵ�.
	3. ��� ����� �������� ������ ������ ������.
	4. ���� ������ ���� �Ѱ��� �������� �ö����� ����ϰ� �ΰ� �̻��̸� 1���� ����.

	*/

	//���� ������Ʈ�� ��
	_uint iEndGOCnt = 0;
	//�˻��� ������Ʈ�� ��
	_uint iGOCnt = 0;




	//��� ������Ʈ�� Update�� �θ���.
	for (auto& layer : m_pActorLayers)
	{
		if (nullptr == layer)
			MSG_BOX("���̾ null�Դϴ�");

		for (auto& GO : layer->Get_List())
		{
			if (!GO->Get_Active())
				continue;

			//�ൿ�� ������ �� ����
			++iGOCnt;
			GO->UpdateAct();
			//���� �������� ���� ���� ������ �� ����
			if (GO->IsTurnEnd())
				++iEndGOCnt;
		}
	}
	//��� ������Ʈ�� ���� ��������
	if (iGOCnt == iEndGOCnt)
	{
		//���� ��� �������� �˻�
		if (m_iCurrTurn >= m_iMaxTurn)
		{
			m_bTurnEnd = true;
			m_iCurrTurn = 1;
			m_iMaxTurn = 1;
			m_iLayerIndex = 0;
			m_iObjIndex = 0;
			//���� �������� �ƹ��͵� ����.
			return TURN_END;
		}
		//�ƴϸ� ���� �ø��� ��� ���� �Ҹ�ɶ����� �ٽ� ����
		else
		{
			++m_iCurrTurn;

			for (auto& layer : m_pActorLayers)
			{
				if (nullptr == layer)
					MSG_BOX("���̾ null�Դϴ�");

				for (auto& GO : layer->Get_List())
				{
					if (!GO->Get_Active())
						continue;

					if (GO->IsParalyzed())
						continue;
					//���� ������
					GO->SetTurnState(false);
					GO->StartAct();
				}
			}

		}
	}


	return S_OK;
}


//_int CTurnMgr::Update_Simultaneously()
//{
//
//	/*
//	1. ���� �����δ�.
//	2. �������� ���� ����� ��� ����� �������� ���������� ����Ѵ�.
//	3. ��� ����� �������� ������ ������ ������.
//	4. ���� ������ ���� �Ѱ��� �������� �ö����� ����ϰ� �ΰ� �̻��̸� 1���� ����.
//
//	*/
//
//
//
//	//��� ������Ʈ�� Update�� �θ���.
//	set<CGameObject*> endActor;
//	list<CGameObject*>* pListActor = CSpawner::Get_Instance()->Get_Actors();
//	for (auto& GO : *pListActor)
//	{
//		if (!GO->Get_Active())
//			continue;
//
//		GO->UpdateAct();
//		//���� ������ ���� ���Ͱ� �ִٸ� ����
//		if (!GO->IsTurnEnd())
//			return E_FAIL;
//	}
//
//	//���� ��� �������� �˻�
//	if (m_iCurrTurn >= m_iMaxTurn)
//	{
//		m_bTurnEnd = true;
//		m_iCurrTurn = 1;
//		m_iMaxTurn = 1;
//		m_iLayerIndex = 0;
//		m_iObjIndex = 0;
//		//���� �������� �ƹ��͵� ����.
//		return TURN_END;
//	}
//	//�ƴϸ� ���� �ø��� ��� ���� �Ҹ�ɶ����� �ٽ� ����
//	else
//	{
//		++m_iCurrTurn;
//
//		for (auto& GO : *pListActor)
//		{
//			if (!GO->Get_Active())
//				continue;
//
//			if (GO->IsParalyzed())
//				continue;
//			//���� ������
//			GO->SetTurnState(false);
//			GO->StartAct();
//		}
//	}
//
//
//	return S_OK;
//}
//




HRESULT CTurnMgr::MoveTurn_Simultaneously(_int _iTurnCnt)
{
	//�Ҹ��� ���� ������
	m_iMaxTurn = _iTurnCnt;
	m_iCurrTurn = 1;
	m_bTurnEnd = false;

	//��� ������Ʈ�� Start�� �θ�
	for (auto& layer : m_pActorLayers)
	{
		for (auto& GO : layer->Get_List())
		{
			if (!GO->Get_Active())
				continue;

			GO->SetTurnState(false);
			GO->StartAct();
		}
	}

	for (auto& observer : m_listObservers)
		observer->OnMoveTurn();

	return S_OK;
}

//HRESULT CTurnMgr::MoveTurn_Simultaneously(_int _iTurnCnt)
//{
//	//�Ҹ��� ���� ������
//	m_iMaxTurn = _iTurnCnt;
//	m_iCurrTurn = 1;
//	m_bTurnEnd = false;
//
//	//��� ������Ʈ�� Start�� �θ�
//
//	list<CGameObject*>* pListActor = CSpawner::Get_Instance()->Get_Actors();
//
//	for (auto& GO : *pListActor)
//	{
//		if (!GO->Get_Active())
//			continue;
//
//		GO->SetTurnState(false);
//		GO->StartAct();
//	}
//
//	for (auto& observer : m_listObservers)
//		observer->OnMoveTurn();
//
//	return S_OK;
//}

HRESULT CTurnMgr::RegisterObserver(CBase * _pObserver)
{
	if (nullptr == _pObserver)
		return E_FAIL;

	m_listObservers.push_back(_pObserver);
	return S_OK;
}

HRESULT CTurnMgr::UnRegisterObserver(CBase * _pObserver)
{
	if (nullptr == _pObserver)
		return E_FAIL;

	auto& iter = m_listObservers.begin();
	for (;iter != m_listObservers.end(); ++iter)
	{
		if (*iter == _pObserver)
		{
			m_listObservers.erase(iter);
			return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT CTurnMgr::ClearObservers()
{

	m_listObservers.clear();
	return S_OK;
}


void CTurnMgr::Free()
{
	m_listObservers.clear();

	for (auto& layer : m_pActorLayers)
	{
		Safe_Release(layer);
	}
}
