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
		MSG_BOX("이펙트 레이어가 없습니다.");

	m_pActorLayers[0] = pLayer;
	Safe_AddRef(m_pActorLayers[0]);

	pLayer = pObjMgr->Find_Layer(L"Player", SCENE_STAGE);
	if (nullptr == pLayer)
		MSG_BOX("플레이어 레이어가 없습니다.");

	m_pActorLayers[1] = pLayer;
	Safe_AddRef(m_pActorLayers[1]);

	pLayer = pObjMgr->Find_Layer(L"Monster", SCENE_STAGE);
	if (nullptr == pLayer)
		MSG_BOX("몬스터 레이어가 없습니다.");

	m_pActorLayers[2] = pLayer;
	Safe_AddRef(m_pActorLayers[2]);


	return S_OK;
}




_int CTurnMgr::Update_Simultaneously()
{

	/*
	1. 전부 움직인다.
	2. 움직임이 끝난 사람은 모든 사람의 움직임이 끝날때까지 대기한다.
	3. 모든 사람이 움직임이 끝나면 한턴이 끝났다.
	4. 만약 움직일 턴이 한개면 다음턴이 올때까지 대기하고 두개 이상이면 1으로 간다.

	*/

	//끝난 오브젝트의 수
	_uint iEndGOCnt = 0;
	//검사한 오브젝트의 수
	_uint iGOCnt = 0;




	//모든 오브젝트의 Update를 부른다.
	for (auto& layer : m_pActorLayers)
	{
		if (nullptr == layer)
			MSG_BOX("레이어가 null입니다");

		for (auto& GO : layer->Get_List())
		{
			if (!GO->Get_Active())
				continue;

			//행동한 액터의 수 세기
			++iGOCnt;
			GO->UpdateAct();
			//턴이 끝났으면 턴이 끝난 액터의 수 세기
			if (GO->IsTurnEnd())
				++iEndGOCnt;
		}
	}
	//모든 오브젝트의 턴이 끝났으면
	if (iGOCnt == iEndGOCnt)
	{
		//턴이 모두 끝났는지 검사
		if (m_iCurrTurn >= m_iMaxTurn)
		{
			m_bTurnEnd = true;
			m_iCurrTurn = 1;
			m_iMaxTurn = 1;
			m_iLayerIndex = 0;
			m_iObjIndex = 0;
			//턴이 끝났으면 아무것도 안함.
			return TURN_END;
		}
		//아니면 턴을 올리고 모든 턴이 소모될때까지 다시 시작
		else
		{
			++m_iCurrTurn;

			for (auto& layer : m_pActorLayers)
			{
				if (nullptr == layer)
					MSG_BOX("레이어가 null입니다");

				for (auto& GO : layer->Get_List())
				{
					if (!GO->Get_Active())
						continue;

					if (GO->IsParalyzed())
						continue;
					//턴을 시작함
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
//	1. 전부 움직인다.
//	2. 움직임이 끝난 사람은 모든 사람의 움직임이 끝날때까지 대기한다.
//	3. 모든 사람이 움직임이 끝나면 한턴이 끝났다.
//	4. 만약 움직일 턴이 한개면 다음턴이 올때까지 대기하고 두개 이상이면 1으로 간다.
//
//	*/
//
//
//
//	//모든 오브젝트의 Update를 부른다.
//	set<CGameObject*> endActor;
//	list<CGameObject*>* pListActor = CSpawner::Get_Instance()->Get_Actors();
//	for (auto& GO : *pListActor)
//	{
//		if (!GO->Get_Active())
//			continue;
//
//		GO->UpdateAct();
//		//턴이 끝나지 않은 액터가 있다면 리턴
//		if (!GO->IsTurnEnd())
//			return E_FAIL;
//	}
//
//	//턴이 모두 끝났는지 검사
//	if (m_iCurrTurn >= m_iMaxTurn)
//	{
//		m_bTurnEnd = true;
//		m_iCurrTurn = 1;
//		m_iMaxTurn = 1;
//		m_iLayerIndex = 0;
//		m_iObjIndex = 0;
//		//턴이 끝났으면 아무것도 안함.
//		return TURN_END;
//	}
//	//아니면 턴을 올리고 모든 턴이 소모될때까지 다시 시작
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
//			//턴을 시작함
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
	//소모할 턴을 셋팅함
	m_iMaxTurn = _iTurnCnt;
	m_iCurrTurn = 1;
	m_bTurnEnd = false;

	//모든 오브젝트의 Start를 부름
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
//	//소모할 턴을 셋팅함
//	m_iMaxTurn = _iTurnCnt;
//	m_iCurrTurn = 1;
//	m_bTurnEnd = false;
//
//	//모든 오브젝트의 Start를 부름
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
