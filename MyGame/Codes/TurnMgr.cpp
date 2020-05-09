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
	m_eCurrScene = CSceneMgr::Get_Instance()->Get_CurrScene();
}

CTurnMgr::CTurnMgr(CTurnMgr & _rhs)
{
}


_int CTurnMgr::Update()
{
	if (nullptr == m_pCurrActor)
	{
		return E_FAIL;
	}

	if (m_iCurrTurn >= m_iMaxTurn)
	{
		m_iLayerIndex = 0;
		m_iObjIndex = 0;
		m_pCurrActor = nullptr;
		return TURN_END;
	}

	//���� ���͸� �ൿ��Ų��.
	_int msg = m_pCurrActor->UpdateAct();

	//���� ���Ͱ� �ൿ�� ��ġ��
	if (TURN_END == msg)
	{
		//���� ���ͷ� ��ü�Ѵ�.
		_int msg = Get_NextActor(&m_pCurrActor);

		//���� ���� �����ٸ� ���� 1 �ѱ��.
		if (TURN_END == msg)
		{
			++m_iCurrTurn;
		}

		if (nullptr != m_pCurrActor)
			_int msg = m_pCurrActor->StartAct();
	}

	return S_OK;
}

HRESULT CTurnMgr::MoveTurn(_int _iTurnCnt)
{
	m_iMaxTurn += _iTurnCnt;

	if(FAILED(Get_NextActor(&m_pCurrActor)))
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

	//���̾ ã�´�.
	map<const _tchar*, CLayer*>* pMapLayer = CObjMgr::Get_Instance()->Get_Layers();
	if (m_iLayerIndex >= pMapLayer[m_eCurrScene].size())
	{
		//������
		m_iLayerIndex = 0;
		m_iObjIndex = 0;
		*_pOutCharacter = nullptr;
		return TURN_END;
	}

	auto& mapIter = pMapLayer[m_eCurrScene].begin();
	std::advance(mapIter, m_iLayerIndex);

	//���ӿ�����Ʈ�� ã�´�.
	list<CGameObject*> listGO = mapIter->second->Get_List();
	if (m_iObjIndex >= listGO.size())
	{
		//���� ���̾��
		++m_iLayerIndex;
		m_iObjIndex = 0;
	}

	auto& listIter = listGO.begin();
	std::advance(listIter, m_iObjIndex);

	//���� ������Ʈ �ٶ󺸱�
	++m_iObjIndex;

	*_pOutCharacter = dynamic_cast<CCharacter*>(*listIter);

	return TURN_NOEVENT;

}

void CTurnMgr::Free()
{
}
