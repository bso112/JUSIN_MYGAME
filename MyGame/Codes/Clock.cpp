#include "stdafx.h"
#include "Clock.h"
#include "TimerMgr.h"

USING(MyGame)
void CClock_Trigger::Free()
{
}

bool CClock_Trigger::isThreashHoldReached(_double _time, const _tchar* _pTimerKey)
{
	m_bUsing = true;

	m_TimeAcc += CTimerMgr::Get_Instance()->Get_TimeDelta(_pTimerKey);

	if (m_TimeAcc >= _time)
	{
		m_TimeAcc = 0.0;
		return true;
	}

	return false;
}


bool CClock_Delay::isThreashHoldReached(_double _time, const _tchar* _pTimerKey)
{
	m_bUsing = true;

	if (m_TimeAcc >= _time)
	{
		return true;
	}

	m_TimeAcc += CTimerMgr::Get_Instance()->Get_TimeDelta(_pTimerKey);

	return false;

}

void CClock_Delay::Free()
{
}


bool CClock_Single::isThreashHoldReached(_double _time, const _tchar* _pTimerKey)
{
	m_bUsing = true;

	m_TimeAcc += CTimerMgr::Get_Instance()->Get_TimeDelta(_pTimerKey);

	if (m_TimeAcc >= _time)
	{
		return false;
	}

	return true;

}

void CClock_Single::Free()
{
}


bool CClock_Reversal::isThreashHoldReached(_double _time, const _tchar* _pTimerKey)
{
	m_bUsing = true;

	m_TimeAcc += CTimerMgr::Get_Instance()->Get_TimeDelta(_pTimerKey);

	if (m_TimeAcc >= _time)
	{
		m_bState = !m_bState;
		m_TimeAcc = 0.0;
	}

	return m_bState;
}

void CClock_Reversal::Free()
{
}
