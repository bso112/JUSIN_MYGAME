#pragma once
#include "Base.h"

BEGIN(MyGame)
class CTimer;
class CTimerMgr : public CBase
{
	DECLARE_SINGLETON(CTimerMgr)
private:
	explicit CTimerMgr() {};
	virtual ~CTimerMgr() = default;

private:
	map<const _tchar*, CTimer*> m_mapTimer;

public:
	HRESULT	Add_Timer(const _tchar* _pKey);
	_double	Compute_TimeDelta(const _tchar* _pKey);
	CTimer*	Find_Timer(const _tchar* _pKey);
	_double Get_TimeDelta(const _tchar* _pKey= L"Timer_100");

private:
	virtual void Free() override;

};

END