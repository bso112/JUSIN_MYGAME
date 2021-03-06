#include "stdafx.h"
#include "..\Headers\AIState.h"
#include "Character.h"
#include "ObjMgr.h"
#include "Image.h"
#include "Goo.h"
#include "Tengu.h"
#include "ItemFactory.h"
#include "Spawner.h"
#include "Item.h"
USING(MyGame)

CAIState::STATE CAIIdle::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	if (_isAlerted)
	{
		CTransform* pTransform = dynamic_cast<CTransform*>(m_pActor->Get_Module(L"Transform"));
		if (nullptr == pTransform)
			return STATE_END;

		CCharacter* pFocus = m_pActor->Get_Focus();
		if (nullptr == pFocus)
			return STATE_END;

		CTransform* pTargetTransform = dynamic_cast<CTransform*>(pFocus->Get_Module(L"Transform"));
		if (nullptr == pTargetTransform)
			return STATE_END;

		return STATE_HUNTING;
	}

	m_pActor->SetTurnState(true);
	return STATE_IDLE;
}

CAIState::STATE CAIIdle::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	m_pActor->SetTurnState(true);
	return STATE_IDLE;
}

void CAIIdle::Free()
{
}



CAIState::STATE CAISleeping::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	if (nullptr == m_pActor)
		return STATE_END;

	CMonster* pMonster = dynamic_cast<CMonster*>(m_pActor);
	if (nullptr == pMonster)
		return STATE_END;
	if ( pMonster->IsAwake())
	{
		//CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
		//m_pActor->ShowStateIcon(SCENE_STAGE, L"icon", 2, BASEDESC(Vector2(pTransform->Get_Position().x - 10.f, pTransform->Get_Position().y - 15.f), Vector2(10.f, 15.f)));
		m_pActor->SetTurnState(true);
		return STATE_HUNTING;
	}


	m_pActor->SetTurnState(true);

	return STATE_END;
}

CAIState::STATE CAISleeping::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	m_pActor->SetTurnState(true);

	return STATE_END;
}

void CAISleeping::OnStateEnter(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
	if (nullptr == pAnimator)
		return;

	pAnimator->Play(L"idle");

	//CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
	////1턴만 되서 안나오는것처럼 보임
	//m_pActor->ShowStateIcon(SCENE_STAGE, L"icon", 1, BASEDESC(Vector2(pTransform->Get_Position().x, pTransform->Get_Position().y - 10.f), Vector2(10.f, 10.f)));

}

void CAISleeping::Free()
{
}

CAIState::STATE CAIHunting::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{

	if (nullptr == m_pActor)
		return STATE_END;

	CTransform* pTransform = dynamic_cast<CTransform*>(m_pActor->Get_Module(L"Transform"));
	if (nullptr == pTransform)
		return STATE_END;

	//공격 모션
	CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
	if (nullptr == pAnimator)
		return STATE_END;

	//만약 이동력만큼 다 움직였으면
	if (pTransform->Is_TurnEnd())
	{
		//턴종료
		m_pActor->SetTurnState(true);
		//트랜스폼도 턴종료
		pTransform->NextTurn();
	}
	//공격애니메이션 끝나면
	else if (m_bAttack && pAnimator->IsEndAnim(L"attack"))
	{
		CCharacter* pFocus = m_pActor->Get_Focus();
		if (nullptr == pFocus)
			return STATE_END;

		//공격
		m_pActor->Attack(pFocus);

		//턴종료
		m_pActor->SetTurnState(true);
		m_bAttack = false;
	}
	//그외에는 턴 진행중
	else
		//요거 때문에 턴 안넘어감
		m_pActor->SetTurnState(true);

	return STATE_END;
}

CAIState::STATE CAIHunting::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{

	if (nullptr == m_pActor)
		return STATE_END;


	CTransform* pTransform = dynamic_cast<CTransform*>(m_pActor->Get_Module(L"Transform"));
	if (nullptr == pTransform)
		return STATE_END;

	//만약 인식범위에 플레이어가 없으면 IDLE로 돌아감.
	if (!_isAlerted)
		return STATE_IDLE;


	//공격할 수 있으면
	if (_canAttack)
	{
		//공격 모션
		CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
		if (nullptr == pAnimator)
			return STATE_END;

		pAnimator->Play(L"attack");
		m_bAttack = true;

	}
	//인식했으면
	else if (_isAlerted)
	{
		CTransform* pTransform = dynamic_cast<CTransform*>(m_pActor->Get_Module(L"Transform"));
		if (nullptr == pTransform)
			return STATE_END;

		CCharacter* pFocus = m_pActor->Get_Focus();
		if (nullptr == pFocus)
			return STATE_END;

		CTransform* pTargetTransform = dynamic_cast<CTransform*>(pFocus->Get_Module(L"Transform"));
		if (nullptr == pTargetTransform)
			return STATE_END;

		//점프 모션
		CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
		if (nullptr == pAnimator)
			return STATE_END;
		pAnimator->Play(L"walk");

		//타깃을 향해 간다.
		pTransform->Go_Target(pTargetTransform, 1.f);
	}

	return STATE_END;
}

void CAIHunting::Free()
{
}

CAIState::STATE CAIWandering::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	//CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
	//if (nullptr == pTransform)
	//	return STATE_END;
	////만약 이동력만큼 다 움직였으면
	//if (pTransform->Is_TurnEnd())
	//{
	//	//턴종료
	//	m_pActor->SetTurnState(true);
	//	//트랜스폼도 턴종료
	//	pTransform->NextTurn();
	//}

	m_pActor->SetTurnState(true);

	return STATE_END;
}

CAIState::STATE CAIWandering::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	////랜덤하게 움직이기
	//CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
	//if (nullptr == pTransform)
	//	return STATE_END;

	//CCharacter* pFocus = m_pActor->Get_Focus();
	//if (nullptr == pFocus)
	//	return STATE_END;

	//CTransform* pTargetTransform = (CTransform*)pFocus->Get_Module(L"Transform");
	//if (nullptr == pTargetTransform)
	//	return STATE_END;

	////타깃을 향해 간다.
	//pTransform->Go_Target(pTargetTransform, 1.f);
	return STATE_END;
}

void CAIWandering::Free()
{
}


void CAIState::OnStateEnter(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
}

CAIState::STATE CAITengu::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	if (nullptr == m_pActor)
		return STATE_END;


	//공격 모션
	CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
	if (nullptr == pAnimator)
		return STATE_END;


	//공격애니메이션 끝나면
	if (m_bAttack && pAnimator->IsEndAnim(L"attack"))
	{
		CCharacter* pFocus = m_pActor->Get_Focus();
		if (nullptr == pFocus)
			return STATE_END;

		//공격
		m_pActor->Attack(pFocus);

		//턴종료
		m_pActor->SetTurnState(true);
		m_bAttack = false;
	}
	//그외에는 턴 진행중
	else
		//요거 때문에 턴 안넘어감
		m_pActor->SetTurnState(true);

	return STATE_END;
}

CAIState::STATE CAITengu::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	if (nullptr == m_pActor)
		return STATE_END;


	CTransform* pTransform = dynamic_cast<CTransform*>(m_pActor->Get_Module(L"Transform"));
	if (nullptr == pTransform)
		return STATE_END;

	//만약 인식범위에 플레이어가 없으면 IDLE로 돌아감.
	if (!_isAlerted)
		return STATE_IDLE;


	//공격할 수 있으면
	if (_canAttack)
	{
		_int ranNum = rand() % 100;
		//80프로의 확률로 공격
		if (ranNum > 20)
		{
			//공격 모션
			CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
			if (nullptr == pAnimator)
				return STATE_END;

			//근거리공격
			pAnimator->Play(L"attack");
			m_bAttack = true;
		}
		//20프로의 확률로 순보
		else
		{
			CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
			if (nullptr == pAnimator)
				return STATE_END;

			pAnimator->Play(L"sunbo");
			CTengu* pTengu = dynamic_cast<CTengu*>(m_pActor);
			if (nullptr == pTengu) return STATE_END;
			pTengu->Sunbo();
		}

	}
	//인식했으면
	else if (_isAlerted)
	{
		//원거리공격

		//공격 모션
		CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
		if (nullptr == pAnimator)
			return STATE_END;

		pAnimator->Play(L"attack");

		CTransform* pTransform = dynamic_cast<CTransform*>(m_pActor->Get_Module(L"Transform"));
		if (nullptr == pTransform) return STATE_END;

		vector<CItemFactory::ITEM_ID> vecThrowItem;
		//vecThrowItem.push_back(CItemFactory::ITEM_ARROW);
		vecThrowItem.push_back(CItemFactory::ITEM_SURIKEN);
		//vecThrowItem.push_back(CItemFactory::ITEM_FIRESEED);
		//vecThrowItem.push_back(CItemFactory::ITEM_FIREPOTION);
		//throwItems.push_back(CItemFactory::ITEM_BOMB);
		
		_int toThrow = rand() % (_int)vecThrowItem.size();
		
		CSpawner* pSpawner = CSpawner::Get_Instance();
		CItem* pItem = CItemFactory::Make_Item(BASEDESC(pTransform->Get_Position(), Vector2(20.f, 20.f)), vecThrowItem[toThrow]);
		pSpawner->Add_Interact(pItem, 2);
		((CMonster*)m_pActor)->Throw_Item(pItem);


	}

	return STATE_END;
}

void CAITengu::Free()
{
	CAIHunting::Free();
}
