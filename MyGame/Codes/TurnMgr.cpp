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

	pLayer = pObjMgr->Find_Layer(L"Monster_lv2", SCENE_STAGE);
	if (nullptr == pLayer)
		MSG_BOX("���� ���̾ �����ϴ�.");

	m_pActorLayers[3] = pLayer;
	Safe_AddRef(m_pActorLayers[3]);






	return S_OK;
}



_int CTurnMgr::Update_sequentially()
{
	if (!m_bTurnStart)
		return 0;


	//��� ���͸� ������� �ൿ��Ų��.
	static int layerIndex = 0;
	static int objIndex = 0;

	//�ʱ�ȭ
	m_pCurrActor = nullptr;
	if (m_iCurrTurn < m_iMaxTurn)
	{
		if (layerIndex < MAX_LAYER_CNT)
		{
			list<CGameObject*> actorList = m_pActorLayers[layerIndex]->Get_List();

			auto& iter = actorList.begin();
			if (actorList.size() > objIndex)
			{

				//�ε�����ŭ ���ͷ��� �̵�
				for (int i = 0; i < objIndex; ++i)
					++iter;

				m_pCurrActor = *iter;
				if (nullptr == m_pCurrActor)
					return -1;

				//������Ͱ� ���� �����ϸ�, Ȥ�� ��Ȱ��ȭ ����, Ȥ�� ������¸�
				if (nullptr == m_pCurrActor || m_pCurrActor->Get_Dead() ||
					m_pCurrActor->IsTurnEnd() || !m_pCurrActor->Get_Active() || m_pCurrActor->IsParalyzed())
				{
					//���� ���͸� ����
					++objIndex;
					m_bActLock = false;
					//�ѹ� ���� ���� ���ʹ� �������� ���� �� ���� �ʱ�ȭ
					m_pCurrActor->SetTurnState(false);
				}
				else
				{
					//���� ���͸� �ѹ��� ���۽�Ű�� ���� ��
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
			//��� ������ ���� ��� ����. 
			layerIndex = 0;
			objIndex = 0;
			//�� ����
			++m_iCurrTurn;
		}

	}
	else
	{
		//��� �� ����
		layerIndex = 0;
		objIndex = 0;
		m_iCurrTurn = 0;
		m_bTurnStart = false;
	}
	

	//������Ʈ�� �� ������ ����������� �Ǵ��Ѵ�.
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
//	//���� ���͸� �ൿ��Ų��.
//	_int msg = m_pCurrActor->UpdateAct();
//
//	//���� ���Ͱ� �ൿ�� ��ġ��
//	if (TURN_END == msg)
//	{
//		//���� ���ͷ� ��ü�Ѵ�.
//		_int msg = Get_NextActor(&m_pCurrActor);
//
//		//���� ���� �����ٸ� ���� 1 �ѱ��.
//		if (TURN_END == msg)
//		{
//			++m_iCurrTurn;
//			//�ٽ� ���ͷ��̾��� ù��° ���͸� ����
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
			//�ൿ�� ������ �� ����
			++iGOCnt;
			((CCharacter*)GO)->UpdateAct();
			//���� �������� ���� ���� ������ �� ����
			if (((CCharacter*)GO)->IsTurnEnd())
				++iEndGOCnt;
		}
	}
	//��� ������Ʈ�� ���� ��������
	if (iGOCnt == iEndGOCnt)
	{
		//���� ��� �������� �˻�
		if (m_iCurrTurn >= m_iMaxTurn)
		{
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
					//���� ������
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
//	//�Ҹ��� ���� ������
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
	//�Ҹ��� ���� ������
	m_iMaxTurn = _iTurnCnt;
	m_iCurrTurn = 1;

	//��� ������Ʈ�� Start�� �θ�
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
//	//��� ���̾� �� ����
//	if (2 <= m_iLayerIndex)
//	{
//		m_iLayerIndex = 0;
//		m_iObjIndex = 0;
//		return TURN_END;
//	}
//
//	//���ӿ�����Ʈ�� ã�´�.
//	list<CGameObject*> listGO = m_pActorLayers[m_iLayerIndex]->Get_List();
//	if (m_iObjIndex >= listGO.size())
//	{
//		//���̾� �� ����
//		++m_iLayerIndex;
//		m_iObjIndex = 0;
//	}
//
//	auto& listIter = listGO.begin();
//	std::advance(listIter, m_iObjIndex);
//
//	//���� ������Ʈ �ٶ󺸱�
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
