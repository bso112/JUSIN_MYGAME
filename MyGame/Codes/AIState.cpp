#include "stdafx.h"
#include "..\Headers\AIState.h"
#include "Character.h"
#include "ObjMgr.h"
#include "Image.h"
#include "Goo.h"
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
		CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
		m_pActor->ShowStateIcon(SCENE_STAGE, L"icon", 2, BASEDESC(Vector2(pTransform->Get_Position().x, pTransform->Get_Position().y - 10.f), Vector2(10.f, 15.f)));
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

	CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
	m_pActor->ShowStateIcon(SCENE_STAGE, L"icon", 1, BASEDESC(Vector2(pTransform->Get_Position().x, pTransform->Get_Position().y - 10.f), Vector2(10.f, 10.f)));

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

	//���� ���
	CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
	if (nullptr == pAnimator)
		return STATE_END;

	//���� �̵��¸�ŭ �� ����������
	if (pTransform->Is_TurnEnd())
	{
		//������
		m_pActor->SetTurnState(true);
		//Ʈ�������� ������
		pTransform->NextTurn();
	}
	//���ݾִϸ��̼� ������
	else if (m_bAttack && pAnimator->IsEndAnim(L"attack"))
	{
		CCharacter* pFocus = m_pActor->Get_Focus();
		if (nullptr == pFocus)
			return STATE_END;

		//����
		m_pActor->Attack(pFocus);
		
		//������
		m_pActor->SetTurnState(true);
		m_bAttack = false;
	}
	//�׿ܿ��� �� ������
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

	//���� �νĹ����� �÷��̾ ������ IDLE�� ���ư�.
	if (!_isAlerted)
		return STATE_IDLE;


	//������ �� ������
	if (_canAttack)
	{
		//���� ���
		CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
		if (nullptr == pAnimator)
			return STATE_END;

		pAnimator->Play(L"attack");
		m_bAttack = true;

	}
	//�ν�������
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

		//���� ���
		CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
		if (nullptr == pAnimator)
			return STATE_END;
		pAnimator->Play(L"walk");

		//Ÿ���� ���� ����.
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
	////���� �̵��¸�ŭ �� ����������
	//if (pTransform->Is_TurnEnd())
	//{
	//	//������
	//	m_pActor->SetTurnState(true);
	//	//Ʈ�������� ������
	//	pTransform->NextTurn();
	//}

	m_pActor->SetTurnState(true);

	return STATE_END;
}

CAIState::STATE CAIWandering::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	////�����ϰ� �����̱�
	//CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
	//if (nullptr == pTransform)
	//	return STATE_END;

	//CCharacter* pFocus = m_pActor->Get_Focus();
	//if (nullptr == pFocus)
	//	return STATE_END;

	//CTransform* pTargetTransform = (CTransform*)pFocus->Get_Module(L"Transform");
	//if (nullptr == pTargetTransform)
	//	return STATE_END;

	////Ÿ���� ���� ����.
	//pTransform->Go_Target(pTargetTransform, 1.f);
	return STATE_END;
}

void CAIWandering::Free()
{
}


void CAIState::OnStateEnter(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
}

