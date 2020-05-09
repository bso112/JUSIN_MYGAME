#include "stdafx.h"
#include "..\Headers\AIState.h"
#include "Character.h"
#include "ObjMgr.h"

USING(MyGame)

CAIState::STATE CAIIdle::Act(_bool _canAttack, _bool _isAlerted,_double _timeDelta)
{
	if (_isAlerted)
	{
		return STATE_HUNTING;
	}

	return STATE_END;
}

void CAIIdle::Free()
{
}



CAIState::STATE CAISleeping::Act(_bool _canAttack, _bool _isAlerted,  _double _timeDelta)
{

	if (_isAlerted)
	{
		return STATE_HUNTING;
	}

	CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
	if (nullptr == pAnimator)
		return STATE_END;

	pAnimator->Play(L"Sleep");
	return STATE_END;
}

void CAISleeping::Free()
{
}

CAIState::STATE CAIHunting::Act(_bool _canAttack, _bool _isAlerted,  _double _timeDelta)
{
	if (nullptr == m_pActor)
		return STATE_END;

	if (_canAttack)
	{
		CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
		if (nullptr == pTransform)
			return STATE_END;

		CCharacter* pFocus = m_pActor->Get_Focus();
		if (nullptr == pFocus)
			return STATE_END;

		//공격
		pFocus->TakeDamage(m_pActor->Get_Stat().m_fAtt->GetValue());

		//공격 모션
		CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
		if (nullptr == pAnimator)
			return STATE_END;
		pAnimator->Play(L"attack");
	}
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


		//타깃을 향해 간다.
		pTransform->Go_Target(pTargetTransform, 1.f);

		//점프 모션
		CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
		if (nullptr == pAnimator)
			return STATE_END;
		pAnimator->Play(L"walk");
	}
	return STATE_END;
}

void CAIHunting::Free()
{
}

CAIState::STATE CAIWandering::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	return STATE_END;
}

void CAIWandering::Free()
{
}


CAIState::STATE CAIHunting_Jump::LateUpdate(_double _timeDelta)
{
	CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
	if (nullptr == pTransform)
		return STATE_END;

	if (!pTransform->Is_Moving())
		return STATE_IDLE;
	return STATE_END;
}

CAIState::STATE CAIHunting_Jump::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	if (nullptr == m_pActor)
		return STATE_END;

	//공격할 수 있으면
	if (_canAttack)
	{
		CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
		if (nullptr == pTransform)
			return STATE_END;

		CCharacter* pFocus = m_pActor->Get_Focus();
		if (nullptr == pFocus)
			return STATE_END;

		//공격
		pFocus->TakeDamage(m_pActor->Get_Stat().m_fAtt->GetValue());

		//공격 모션
		CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
		if (nullptr == pAnimator)
			return STATE_END;
		pAnimator->Play(L"attack");
	}
	//상대를 인식했으면
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


		//타깃을 향해 간다.
		pTransform->Go_Target(pTargetTransform, 1.f);

		//점프 모션
		CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
		if (nullptr == pAnimator)
			return STATE_END;
		pAnimator->Play(L"jump");
	}

	
	return STATE_END;
}

void CAIHunting_Jump::Free()
{
}

CAIState::STATE CAIState::LateUpdate(_double _timeDelta)
{
	return STATE_END;
}
