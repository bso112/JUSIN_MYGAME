#include "stdafx.h"
#include "..\Headers\PlayerState.h"
#include "Transform.h"
#include "Character.h"
#include "Hero.h"
#include "KeyMgr.h"
#include "World.h"
#include "TurnMgr.h"

USING(MyGame)



CPlayerState::STATE CPlayerIdle::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	if (m_pActor == nullptr)
		return STATE_END;

	CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
	if (nullptr == pTransform)
		return STATE_END;

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		if (nullptr == pTransform)
			return STATE_END;

		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		vector<CTerrain*> route;
		CWorld::Get_Instance()->Get_Route(pTransform->Get_Position(), Vector2((float)pt.x, (float)pt.y), route, pTransform);

		//해당 루트를 따라가기 위해 필요한 턴수를 계산
		_int iTurnCnt = (_int)route.size() / pTransform->Get_Desc().movePerTurn;

		pTransform->Go_Route(route, 1.f);

		//플레이어가 움직인만큼 턴 이동
		CTurnMgr::Get_Instance()->MoveTurn(iTurnCnt);

		return STATE_WALK;
	}


	return STATE_END;
}

CPlayerState::STATE CPlayerIdle::Act(_bool _canAttack, _bool _isAlerted,  _double _timeDelta)
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

	if (!pTransform->Is_Moving())
	{
		return STATE_IDLE;
	}

	return STATE_END;
}

CPlayerState::STATE CPlayerWalk::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	CHero* pHero = dynamic_cast<CHero*>(m_pActor);
	if (nullptr == pHero)
		return STATE_END;

	pHero->PlayAnimation(L"walk");


	return STATE_END;
}

void CPlayerWalk::Free()
{
}

CPlayerState::STATE CPlayerUsing::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	return STATE_END;
}

CPlayerState::STATE CPlayerUsing::Act(_bool _canAttack, _bool _isAlerted,  _double _timeDelta)
{
	return STATE_END;
}

void CPlayerUsing::Free()
{
}
