#include "stdafx.h"
#include "..\Headers\PlayerState.h"
#include "Transform.h"
#include "Character.h"
#include "Hero.h"
#include "KeyMgr.h"
#include "LevelMgr.h"
#include "TurnMgr.h"

USING(MyGame)



CPlayerState::STATE CPlayerIdle::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	if (m_pActor == nullptr)
		return STATE_END;

	CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
	if (nullptr == pTransform)
		return STATE_END;

	if (pTransform->Is_Moving())
		return STATE_WALK;


	return STATE_END;
}

CPlayerState::STATE CPlayerIdle::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	if (m_pActor == nullptr)
		return STATE_END;

	CHero* pHero = dynamic_cast<CHero*>(m_pActor);
	if (nullptr == pHero)
		return STATE_END;
	else
		pHero->PlayAnimation(L"idle");

	return STATE_END;
}

void CPlayerIdle::Free()
{
}

CPlayerState::STATE CPlayerWalk::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
	if (nullptr == pTransform)
		return STATE_END;

	//��Ʈ�� ��� �̵������� ���� ������.
	if (!pTransform->Is_Moving())
	{
		return STATE_IDLE;
	}
	//�̵��¸�ŭ �̵������� ���� ������.
	if (pTransform->Is_TurnEnd())
	{
		return STATE_WALK;
	}

	return STATE_END;
}

CPlayerState::STATE CPlayerWalk::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
	if (nullptr == pTransform)
		return STATE_END;

	CHero* pHero = dynamic_cast<CHero*>(m_pActor);
	if (nullptr == pHero)
		return STATE_END;
	else
		pHero->PlayAnimation(L"walk");

	//���� �ʱ�ȭ�ؼ� �����Ͽ� Act�� �Ҹ�����.
	pTransform->NextTurn();


	return STATE_END;
}

void CPlayerWalk::Free()
{
}

CPlayerState::STATE CPlayerUsing::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	return STATE_END;
}

CPlayerState::STATE CPlayerUsing::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	return STATE_END;
}

void CPlayerUsing::Free()
{
}
