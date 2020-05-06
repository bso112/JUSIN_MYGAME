#include "stdafx.h"
#include "..\Headers\AIState.h"
#include "Character.h"
#include "ObjMgr.h"

USING(MyGame)

CState * CAIIdle::Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta)
{
	return nullptr;
}

void CAIIdle::Free()
{
}



CState * CAISleeping::Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta)
{
	return nullptr;
}

void CAISleeping::Free()
{
}

CState * CAIHunting::Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta)
{
	return nullptr;
}

void CAIHunting::Free()
{
}

CState * CAIWandering::Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta)
{
	return nullptr;
}

void CAIWandering::Free()
{
}

CState * CAIIdle_Rat::Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta)
{
	if (_isAlerted)
	{
		return new CAIHunting_Rat(m_pActor);
	}

	return nullptr;
}

void CAIIdle_Rat::Free()
{
}

CState * CAIHunting_Rat::Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta)
{
	if (nullptr == m_pActor)
		return nullptr;

	//공격할 수 있으면
	if (_canAttack)
	{
		CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
		if (nullptr == pTransform)
			return nullptr;

		CCharacter* pFocus = m_pActor->Get_Focus();
		if (nullptr == pFocus)
			return nullptr;

		//공격
		pFocus->TakeDamage(m_pActor->Get_Stat().m_fAtt->GetValue());

		//공격 모션
		CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
		if (nullptr == pAnimator)
			return nullptr;
		pAnimator->Play(L"attack");
	}
	//상대를 인식했으면
	else if (_isAlerted)
	{
		CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
		if (nullptr == pTransform)
			return nullptr;

		CCharacter* pFocus = m_pActor->Get_Focus();
		if (nullptr == pFocus)
			return nullptr;

		CTransform* pTargetTransform = (CTransform*)pFocus->Get_Module(L"Transform");
		if (nullptr == pTargetTransform)
			return nullptr;


		//타깃을 향해 간다.
		pTransform->Go_Target(pTargetTransform, 1.f, _iTurnCnt);

		//점프 모션
		CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
		if (nullptr == pAnimator)
			return nullptr;
		pAnimator->Play(L"jump");
	}

	
	return nullptr;
}

void CAIHunting_Rat::Free()
{
}

