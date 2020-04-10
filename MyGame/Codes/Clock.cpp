#include "stdafx.h"
#include "Clock.h"
#include "TimerMgr.h"

USING(MyGame)
void CTriggerClock::Free()
{
}

bool CTriggerClock::isThreashHoldReached(_double _time, const _tchar* _pTimerKey)
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


bool CDelayClock::isThreashHoldReached(_double _time, const _tchar* _pTimerKey)
{
	m_bUsing = true;

	if (m_TimeAcc >= _time)
	{
		return true;
	}

	m_TimeAcc += CTimerMgr::Get_Instance()->Get_TimeDelta(_pTimerKey);

	return false;

}

void CDelayClock::Free()
{
}


bool CSingleClock::isThreashHoldReached(_double _time, const _tchar* _pTimerKey)
{
	m_bUsing = true;

	m_TimeAcc += CTimerMgr::Get_Instance()->Get_TimeDelta(_pTimerKey);

	if (m_TimeAcc >= _time)
	{
		return false;
	}

	return true;

}

void CSingleClock::Free()
{
}


bool CReversalClock::isThreashHoldReached(_double _time, const _tchar* _pTimerKey)
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

void CReversalClock::Free()
{
}
