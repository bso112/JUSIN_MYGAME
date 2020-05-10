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
	m_pActorLayers[0] = CObjMgr::Get_Instance()->Find_Layer(L"Player", SCENE_STAGE);
	m_pActorLayers[1] = CObjMgr::Get_Instance()->Find_Layer(L"Monster", SCENE_STAGE);
	MoveTurn(1);
	return S_OK;
}

_int CTurnMgr::Update()
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

HRESULT CTurnMgr::MoveTurn(_int _iTurnCnt)
{
	m_iMaxTurn += _iTurnCnt;

	if (FAILED(Get_NextActor(&m_pCurrActor)))
		return E_FAIL;

	if (nullptr == m_pCurrActor)
		return E_FAIL;

	m_pCurrActor->StartAct();

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
