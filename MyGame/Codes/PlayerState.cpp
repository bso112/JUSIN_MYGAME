#include "stdafx.h"
#include "..\Headers\PlayerState.h"
#include "Transform.h"
#include "Character.h"
#include "Hero.h"
#include "KeyMgr.h"
#include "LevelMgr.h"
#include "TurnMgr.h"
#include "SoundMgr.h"

USING(MyGame)



CPlayerState::STATE CPlayerIdle::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	return STATE_END;
}

CPlayerState::STATE CPlayerIdle::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	//상태를 체크하고, 움직이는 중이면 WALK로 상태를 바꿈.

	if (m_pActor == nullptr)
		return STATE_END;

	CHero* pHero = dynamic_cast<CHero*>(m_pActor);
	if (nullptr == pHero)
		return STATE_END;
	else
		pHero->PlayAnimation(L"idle");

	CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
	if (nullptr == pTransform)
		return STATE_END;

	if (pTransform->Is_Moving())
	{
		pHero->PlayAnimation(L"walk");
		return STATE_WALK;
	}

	//바로 턴 종료
	m_pActor->SetTurnState(true);

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

	//이동력만큼 움직였으면
	if (pTransform->Is_TurnEnd())
	{
		//턴종료
		m_pActor->SetTurnState(true);
		pTransform->NextTurn();
	}

	//모든 루트를 움직였으면
	if (!pTransform->Is_Moving())
	{
		return STATE_IDLE;
	}
	else
		CSoundMgr::Get_Instance()->PlaySound(L"snd_step.mp3", CSoundMgr::CHANNELID::PLAYER_LOOP);

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
		//pHero->PlayAnimation(L"walk");

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
