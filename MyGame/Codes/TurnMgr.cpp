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
	MoveTurn_sequentially(1);
	return S_OK;
}

/*
0. MoveTurn�� �Ҹ���, �Һ��� �ϼ��� ���õȴ�.
1. ���͸� �ϳ��ϳ� üũ�Ѵ�.
2. �� ������ �ൿ�� ������ �ٸ� ���Ͱ� �ൿ�� �� �ִ�.
3. �� ������ ���� ������ ������ UpdateAct�� �޼����� �Ǵ��Ѵ�.
4. �� ������ ���� �������� ���� ���ͷ� �ٲٰ�, �ٲ� ������ StartAct�� �θ���.
5. 3������
6. ���� ��� ���� �Һ��ϸ� ������ ������ MoveTurn�� �Ҹ������� ��������� �ʱ�ȭ�ϰ� TURN_END�� �����Ѵ�.

UpdateAct�� ���� ��������� �Ǵ��ϴ� '����'��.
StartAct�� ���� Actor�� �ൿ�̴�. �� �����ᰡ StartAct���� ��� �̷���� ���, StartAct�ȿ����� ���� ������ �� �ִ�.

������ ���� ���� ���ᰡ �� ����ൿ�� ����� �ƴ϶�� ���̴�.
�������, �̵��� ��� ���� ����� Actor�� �̵��¸�ŭ �̵��� �����̴�.
�׷��� ���� �����ٰ� �ؼ� Actor�� ������ �ʴ´�. Actor�� �̵��� * �Һ��� �ϼ� ��ŭ �����δ�.
�׷��� ���ÿ� UpdateAct���� �� �ϸ��� return�� ���� StartAct�� �ٽúθ����� �Ѵ�.
��, �ൿ�� �Һ��� �ϼ���ŭ �ϴ� ���̴�.
�̵��� ��쿡�� �� ����� ���߰��ϸ� �������� ���ƿö����� �����־���Ѵ�.
�װ� �����������ӿ��� �´� ����������, �ȼ������� ���� �ʴ´�.
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
			//�ٽ� ���ͷ��̾��� ù��° ���͸� ����
			Get_NextActor(&m_pCurrActor);
		}
		m_pCurrActor->StartAct();
	}

	return S_OK;
}

_int CTurnMgr::Update_Simultaneously()
{
	if (m_iCurrTurn >= m_iMaxTurn)
	{
		m_iLayerIndex = 0;
		m_iObjIndex = 0;
		m_pCurrActor = nullptr;
		return TURN_END;
	}

	_bool bTurnEnd = false;
	//���� ������Ʈ�� ��
	_uint iEndGOCnt = 0;
	//�˻��� ������Ʈ�� ��
	_uint iGOCnt = 0;

	//��� ������Ʈ�� Update�� �θ���.
	for (auto& layer : m_pActorLayers)
	{
		for (auto& GO : layer->Get_List())
		{
			++iGOCnt;
			_int msg = ((CCharacter*)GO)->UpdateAct();
			if (TURN_END == msg)
			{
				++iEndGOCnt;
			}
		}
	}

	//��� ������Ʈ�� ���� ��������
	if (iGOCnt == iEndGOCnt)
	{
		//��� ������Ʈ�� Start�� �ٽ� �θ�
		for (auto& layer : m_pActorLayers)
		{
			for (auto& GO : layer->Get_List())
			{
				((CCharacter*)GO)->StartAct();
			}
		}
		++m_iCurrTurn;
	}

	return S_OK;
}

HRESULT CTurnMgr::MoveTurn_sequentially(_int _iTurnCnt)
{
	m_iMaxTurn += _iTurnCnt;
	m_iTurnToSpend = _iTurnCnt;

	if (FAILED(Get_NextActor(&m_pCurrActor)))
		return E_FAIL;

	if (nullptr == m_pCurrActor)
		return E_FAIL;

	m_pCurrActor->StartAct();

	return S_OK;

}

HRESULT CTurnMgr::MoveTurn_Simultaneously(_int _iTurnCnt)
{
	m_iMaxTurn += _iTurnCnt;
	m_iTurnToSpend = _iTurnCnt;

	//��� ������Ʈ�� Start�� �θ�
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

	//��� ���̾� �� ����
	if (2 <= m_iLayerIndex)
	{
		m_iLayerIndex = 0;
		m_iObjIndex = 0;
		return TURN_END;
	}

	//���ӿ�����Ʈ�� ã�´�.
	list<CGameObject*> listGO = m_pActorLayers[m_iLayerIndex]->Get_List();
	if (m_iObjIndex >= listGO.size())
	{
		//���̾� �� ����
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
