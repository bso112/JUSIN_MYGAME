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
	//끝났으면 남은 턴수는 0, 아무것도 안함.
	if (m_tStateDesc.m_iDuration < m_iTurnCnt)
		return 0;

	//행동
	OnAct(_pTarget);

	++m_iTurnCnt;
	return m_tStateDesc.m_iDuration - m_iTurnCnt;
}

HRESULT CBuff::End_Buff()
{
	m_iTurnCnt = m_tStateDesc.m_iDuration;
	return S_OK;
}



void CBuff::Free()
{
	m_tStateDesc.m_tStats.Free();
}

