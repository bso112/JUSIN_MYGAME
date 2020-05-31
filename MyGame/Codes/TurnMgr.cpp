#include "stdafx.h"
#include "..\Headers\TurnMgr.h"
#include "Layer.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "GameObject.h"
#include "TimerMgr.h"
#include "Character.h"

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

	pLayer = pObjMgr->Find_Layer(L"Monster_lv2", SCENE_STAGE);
	if (nullptr == pLayer)
		MSG_BOX("몬스터 레이어가 없습니다.");

	m_pActorLayers[3] = pLayer;
	Safe_AddRef(m_pActorLayers[3]);






	return S_OK;
}



_int CTurnMgr::Update_sequentially()
{
	if (!m_bTurnStart)
		return 0;


	//모든 엑터를 순서대로 행동시킨다.
	static int layerIndex = 0;
	static int objIndex = 0;

	//초기화
	m_pCurrActor = nullptr;
	if (m_iCurrTurn < m_iMaxTurn)
	{
		if (layerIndex < MAX_LAYER_CNT)
		{
			list<CGameObject*> actorList = m_pActorLayers[layerIndex]->Get_List();

			auto& iter = actorList.begin();
			if (actorList.size() > objIndex)
			{

				//인덱스만큼 이터레터 이동
				for (int i = 0; i < objIndex; ++i)
					++iter;

				m_pCurrActor = *iter;
				if (nullptr == m_pCurrActor)
					return -1;

				//현재액터가 턴을 종료하면, 혹은 비활성화 상태, 혹은 마비상태면
				if (nullptr == m_pCurrActor || m_pCurrActor->Get_Dead() ||
					m_pCurrActor->IsTurnEnd() || !m_pCurrActor->Get_Active() || m_pCurrActor->IsParalyzed())
				{
					//다음 액터를 셋팅
					++objIndex;
					m_bActLock = false;
					//한번 턴이 끝난 액터는 다음번을 위해 턴 상태 초기화
					m_pCurrActor->SetTurnState(false);
				}
				else
				{
					//현재 액터를 한번만 동작시키기 위한 락
					if (!m_bActLock)
					{
						m_pCurrActor->StartAct();
						m_bActLock = true;
					}
				}

			}
			else
			{
				++layerIndex;
				objIndex = 0;
			}
		}
		else
		{
			//모든 액터의 턴이 모두 끝남. 
			layerIndex = 0;
			objIndex = 0;
			//턴 종료
			++m_iCurrTurn;
		}

	}
	else
	{
		//모든 턴 종료
		layerIndex = 0;
		objIndex = 0;
		m_iCurrTurn = 0;
		m_bTurnStart = false;
	}
	

	//업데이트로 각 액터의 턴종료시점을 판단한다.
	if (nullptr != m_pCurrActor)
		m_pCurrActor->UpdateAct();



	return 0;
}


HRESULT CTurnMgr::MoveTurn_sequentially(_int _iTurnCnt)
{
	m_iMaxTurn = _iTurnCnt;
	m_bTurnStart = true;
	for (auto& layer : m_pActorLayers)
	{
		if (nullptr == layer)
			continue;

		for (auto& actor : layer->Get_List())
		{
			if (!actor->Get_Active())
				continue;
			actor->SetTurnState(false);
			m_bActLock = false;
		}
	}


	return S_OK;
}

#pragma region legacy
//
//
//_int CTurnMgr::Update_sequentially()
//{
//
//	if (m_iCurrTurn >= m_iMaxTurn)
//	{
//		m_iLayerIndex = 0;
//		m_iObjIndex = 0;
//		m_pCurrActor = nullptr;
//		return TURN_END;
//	}
//
//	//현재 액터를 행동시킨다.
//	_int msg = m_pCurrActor->UpdateAct();
//
//	//만약 액터가 행동을 마치면
//	if (TURN_END == msg)
//	{
//		//다음 액터로 교체한다.
//		_int msg = Get_NextActor(&m_pCurrActor);
//
//		//만약 턴이 종료됬다면 턴을 1 넘긴다.
//		if (TURN_END == msg)
//		{
//			++m_iCurrTurn;
//			//다시 몬스터레이어의 첫번째 몬스터를 셋팅
//			Get_NextActor(&m_pCurrActor);
//		}
//		m_pCurrActor->StartAct();
//	}
//
//	return S_OK;
//}


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
			//행동한 액터의 수 세기
			++iGOCnt;
			((CCharacter*)GO)->UpdateAct();
			//턴이 끝났으면 턴이 끝난 액터의 수 세기
			if (((CCharacter*)GO)->IsTurnEnd())
				++iEndGOCnt;
		}
	}
	//모든 오브젝트의 턴이 끝났으면
	if (iGOCnt == iEndGOCnt)
	{
		//턴이 모두 끝났는지 검사
		if (m_iCurrTurn >= m_iMaxTurn)
		{
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
					//턴을 시작함
					((CCharacter*)GO)->SetTurnState(false);
					((CCharacter*)GO)->StartAct();
				}
			}

		}
	}


	return S_OK;
}

//HRESULT CTurnMgr::MoveTurn_sequentially(_int _iTurnCnt)
//{
//	//소모할 턴을 셋팅함
//	m_iMaxTurn = _iTurnCnt;
//	m_iCurrTurn = 0;
//
//	if (FAILED(Get_NextActor(&m_pCurrActor)))
//		return E_FAIL;
//
//	if (nullptr == m_pCurrActor)
//		return E_FAIL;
//
//	m_pCurrActor->StartAct();
//
//	return S_OK;
//
//}



HRESULT CTurnMgr::MoveTurn_Simultaneously(_int _iTurnCnt)
{
	//소모할 턴을 셋팅함
	m_iMaxTurn = _iTurnCnt;
	m_iCurrTurn = 1;

	//모든 오브젝트의 Start를 부름
	for (auto& layer : m_pActorLayers)
	{
		for (auto& GO : layer->Get_List())
		{
			((CCharacter*)GO)->SetTurnState(false);
			((CCharacter*)GO)->StartAct();
		}
	}
	return S_OK;
}

//
//
//_int CTurnMgr::Get_NextActor(CCharacter** _pOutCharacter)
//{
//	if (m_eCurrScene >= SCENE_END)
//		return E_FAIL;
//
//	//모든 레이어 턴 종료
//	if (2 <= m_iLayerIndex)
//	{
//		m_iLayerIndex = 0;
//		m_iObjIndex = 0;
//		return TURN_END;
//	}
//
//	//게임오브젝트를 찾는다.
//	list<CGameObject*> listGO = m_pActorLayers[m_iLayerIndex]->Get_List();
//	if (m_iObjIndex >= listGO.size())
//	{
//		//레이어 턴 종료
//		++m_iLayerIndex;
//		m_iObjIndex = 0;
//	}
//
//	auto& listIter = listGO.begin();
//	std::advance(listIter, m_iObjIndex);
//
//	//다음 오브젝트 바라보기
//	++m_iObjIndex;
//
//	*_pOutCharacter = dynamic_cast<CCharacter*>(*listIter);
//
//	return TURN_NOEVENT;
//
//}

#pragma endregion


void CTurnMgr::Free()
{
	for (auto& layer : m_pActorLayers)
	{
		Safe_Release(layer);
	}
}
