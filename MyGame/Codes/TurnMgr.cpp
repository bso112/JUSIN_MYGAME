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

	CLayer* pLayer = CObjMgr::Get_Instance()->Find_Layer(L"Player", SCENE_STAGE);
	if (nullptr == pLayer)
		MSG_BOX("플레이어 레이어가 없습니다.");

	m_pActorLayers[0] = pLayer;

	pLayer = CObjMgr::Get_Instance()->Find_Layer(L"Monster", SCENE_STAGE);
	if (nullptr == pLayer)
		MSG_BOX("몬스터 레이어가 없습니다.");

	m_pActorLayers[1] = pLayer;

	MoveTurn_sequentially(1);
	return S_OK;
}

/*
0. MoveTurn이 불리고, 소비할 턴수가 셋팅된다.
1. 액터를 하나하나 체크한다.
2. 한 액터의 행동이 끝나야 다른 액터가 행동할 수 있다.
3. 한 액터의 턴이 끝나는 시점은 UpdateAct의 메세지로 판단한다.
4. 한 액터의 턴이 끝났으면 다음 액터로 바꾸고, 바뀐 액터의 StartAct를 부른다.
5. 3번으로
6. 만약 모든 턴을 소비하면 루프는 다음에 MoveTurn이 불릴때까지 멤버변수를 초기화하고 TURN_END를 리턴한다.

UpdateAct는 턴의 종료시점을 판단하는 '루프'다.
StartAct는 실제 Actor의 행동이다. 이 턴종료가 StartAct종료 즉시 이루어질 경우, StartAct안에서도 턴을 종료할 수 있다.

주의할 점은 턴의 종료가 곧 모든행동의 종료는 아니라는 것이다.
예를들어, 이동의 경우 턴의 종료는 Actor의 이동력만큼 이동한 시점이다.
그러나 턴이 종료됬다고 해서 Actor는 멈추지 않는다. Actor는 이동력 * 소비할 턴수 만큼 움직인다.
그러는 동시에 UpdateAct에서 매 턴마다 return을 통해 StartAct를 다시부르도록 한다.
즉, 행동은 소비할 턴수만큼 하는 것이다.
이동의 경우에는 턴 종료시 멈추게하면 다음턴이 돌아올때까지 멈춰있어야한다.
그건 완전턴제게임에는 맞는 로직이지만, 픽셀던전에 맞지 않는다.
*/

_int CTurnMgr::Update_sequentially()
{

	if (m_iCurrTurn >= m_iMaxTurn)
	{
		m_iLayerIndex = 0;
		m_iObjIndex = 0;
		m_pCurrActor = nullptr;
		return TURN_END;
	}

	//현재 액터를 행동시킨다.
	_int msg = m_pCurrActor->UpdateAct();

	//만약 액터가 행동을 마치면
	if (TURN_END == msg)
	{
		//다음 액터로 교체한다.
		_int msg = Get_NextActor(&m_pCurrActor);

		//만약 턴이 종료됬다면 턴을 1 넘긴다.
		if (TURN_END == msg)
		{
			++m_iCurrTurn;
			//다시 몬스터레이어의 첫번째 몬스터를 셋팅
			Get_NextActor(&m_pCurrActor);
		}
		m_pCurrActor->StartAct();
	}

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
			m_pCurrActor = nullptr;
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

HRESULT CTurnMgr::MoveTurn_sequentially(_int _iTurnCnt)
{
	//소모할 턴을 셋팅함
	m_iMaxTurn = _iTurnCnt;
	m_iCurrTurn = 0;

	if (FAILED(Get_NextActor(&m_pCurrActor)))
		return E_FAIL;

	if (nullptr == m_pCurrActor)
		return E_FAIL;

	m_pCurrActor->StartAct();

	return S_OK;

}

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
			((CCharacter*)GO)->StartAct();
		}
	}
	return S_OK;
}



_int CTurnMgr::Get_NextActor(CCharacter** _pOutCharacter)
{
	if (m_eCurrScene >= SCENE_END)
		return E_FAIL;

	//모든 레이어 턴 종료
	if (2 <= m_iLayerIndex)
	{
		m_iLayerIndex = 0;
		m_iObjIndex = 0;
		return TURN_END;
	}

	//게임오브젝트를 찾는다.
	list<CGameObject*> listGO = m_pActorLayers[m_iLayerIndex]->Get_List();
	if (m_iObjIndex >= listGO.size())
	{
		//레이어 턴 종료
		++m_iLayerIndex;
		m_iObjIndex = 0;
	}

	auto& listIter = listGO.begin();
	std::advance(listIter, m_iObjIndex);

	//다음 오브젝트 바라보기
	++m_iObjIndex;

	*_pOutCharacter = dynamic_cast<CCharacter*>(*listIter);

	return TURN_NOEVENT;

}

void CTurnMgr::Free()
{
}
