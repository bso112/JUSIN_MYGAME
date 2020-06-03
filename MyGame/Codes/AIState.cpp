#include "stdafx.h"
#include "..\Headers\AIState.h"
#include "Character.h"
#include "ObjMgr.h"

USING(MyGame)

CAIState::STATE CAIIdle::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	if (_isAlerted)
	{
		CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
		if (nullptr == pTransform)
			return STATE_END;

		CCharacter* pFocus = m_pActor->Get_Focus();
		if (nullptr == pFocus)
			return STATE_END;

		CTransform* pTargetTransform = (CTransform*)pFocus->Get_Module(L"Transform");
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
	if (_isAlerted)
	{
		return STATE_HUNTING;
	}
	return STATE_END;
}

CAIState::STATE CAISleeping::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{

	CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
	if (nullptr == pAnimator)
		return STATE_END;

	pAnimator->Play(L"Sleep");


	return STATE_END;
}

void CAISleeping::Free()
{
}

CAIState::STATE CAIHunting::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{

	if (nullptr == m_pActor)
		return STATE_END;

	CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
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
		m_pActor->Interact(pFocus);

		//턴종료
		m_pActor->SetTurnState(true);
		m_bAttack = false;
	}
	//그외에는 턴 진행중
	else
		m_pActor->SetTurnState(false);

	return STATE_END;
}

CAIState::STATE CAIHunting::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{

	if (nullptr == m_pActor)
		return STATE_END;

	
	CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
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
		CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
		if (nullptr == pTransform)
			return STATE_END;

		CCharacter* pFocus = m_pActor->Get_Focus();
		if (nullptr == pFocus)
			return STATE_END;

		CTransform* pTargetTransform = (CTransform*)pFocus->Get_Module(L"Transform");
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

	return STATE_END;
}

CAIState::STATE CAIWandering::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	//랜덤하게 움직이기
	return STATE_END;
}

void CAIWandering::Free()
{
}


CAIState::STATE CAIHunting_Jump::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	return CAIHunting::LateUpdate(_canAttack, _isAlerted, _timeDelta);
}

CAIState::STATE CAIHunting_Jump::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	return CAIHunting::Act(_canAttack, _isAlerted, _timeDelta);
}

void CAIHunting_Jump::Free()
{
}

