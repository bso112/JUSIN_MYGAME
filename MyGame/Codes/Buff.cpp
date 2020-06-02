#include "stdafx.h"
#include "..\Headers\Buff.h"
#include "Character.h"
USING(MyGame)

HRESULT CBuff::Initialize(void* _pArg)
{
	return S_OK;
}

_int CBuff::Act(CCharacter* _pTarget)
{
	if (m_bBuffStart)
	{
		OnBuffStart(_pTarget);
		m_bBuffStart = false;
	}

	//일단 턴 늘리고
	++m_iTurnCnt;
	
	//끝났으면 남은 턴수는 0, 아무것도 안함.
	if (m_tStateDesc.m_iDuration < m_iTurnCnt)
	{
		OnBuffEnd(_pTarget);
		m_bBuffStart = true;
		return 0;
	}

	//행동
	OnAct(_pTarget);

	return 1;
}

HRESULT CBuff::End_Buff()
{
	m_iTurnCnt = m_tStateDesc.m_iDuration;
	return S_OK;
}

void CBuff::OnBuffStart(CCharacter * _pTarget)
{
}

void CBuff::OnBuffEnd(CCharacter * _pTarget)
{
}



void CBuff::Free()
{
	m_tStateDesc.m_tStats.Free();
}

