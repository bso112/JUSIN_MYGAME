#include "stdafx.h"
#include "..\Headers\TimerMgr.h"
#include "Timer.h"

USING(MyGame)
IMPLEMENT_SINGLETON(CTimerMgr)

HRESULT CTimerMgr::Add_Timer(const _tchar * _pKey)
{
	
	if (nullptr != Find_Timer(_pKey))
		return E_FAIL;

	CTimer* pTimer = CTimer::Create();
	if (nullptr == pTimer)
		return E_FAIL;

	m_mapTimer.emplace(_pKey, pTimer);

	return S_OK;
}

_double CTimerMgr::Compute_TimeDelta(const _tchar * _pKey)
{
	CTimer* pTimer = Find_Timer(_pKey);
	if (nullptr == pTimer)
		return E_FAIL;

	return pTimer->Compute_TimeDelta();
}

CTimer * CTimerMgr::Find_Timer(const _tchar * _pKey)
{
	auto& iter = find_if(m_mapTimer.begin(), m_mapTimer.end(), CFinder_Tag(_pKey));

	if (iter == m_mapTimer.end())
		return nullptr;

	return iter->second;
}

_double CTimerMgr::Get_TimeDelta(const _tchar * _pKey)
{
	CTimer* timer = Find_Timer(_pKey);
	if (nullptr == timer)
		return E_FAIL;

	return timer->Get_TimeDelta();
}

void CTimerMgr::Free()
{
	for (auto& pair : m_mapTimer)
	{
		Safe_Release(pair.second);
	}

	m_mapTimer.clear();
}

