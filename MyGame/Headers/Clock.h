#pragma once
#include "Base.h"

BEGIN(MyGame)
class CClock abstract : public CBase
{
protected:
	explicit CClock() {};
	virtual ~CClock() = default;

protected:
	_double m_TimeAcc = 0.0;
	_bool	m_bUsing = false;
public:
	virtual bool isThreashHoldReached(_double _time, const _tchar* _pTimerKey = L"Timer_100") = 0;
	_bool isUsing() { return m_bUsing; }
	virtual	void Reset() { m_TimeAcc = 0.0; m_bUsing = false; }
};

//주어진 시간간격으로 true를 반환하는 시계
class CClock_Trigger final : public CClock
{
private:
	explicit CClock_Trigger() {};
	virtual  ~CClock_Trigger() = default;
public:
	static CClock_Trigger* Create() { return new CClock_Trigger; }
	virtual bool isThreashHoldReached(_double _time, const _tchar* _pTimerKey = L"Timer_100") override;
	virtual void Free() override;
};

//주어진 시간이 지나면 계속 true를 반환하는 시계
class CClock_Delay final : public CClock
{
private:
	explicit CClock_Delay() {};
	virtual  ~CClock_Delay() = default;
public:

	static CClock_Delay* Create() { return new CClock_Delay; }
	virtual bool isThreashHoldReached(_double _time,  const _tchar* _pTimerKey = L"Timer_100") override;
	virtual void Free() override;
};

//주어진 시간이 지나면 계속 false가 되는 시계
class CClock_Single final : public CClock
{
private:
	explicit CClock_Single() {};
	virtual  ~CClock_Single() = default;
public:
	static CClock_Single* Create() { return new CClock_Single; }
	virtual bool isThreashHoldReached(_double _time,  const _tchar* _pTimerKey = L"Timer_100") override;
	virtual void Free() override;
};

//주어진 시간 간격으로 false, true, false.. 뒤바뀌며 반환하는 시계
class CClock_Reversal final : public CClock
{
private:
	explicit CClock_Reversal() {};
	virtual  ~CClock_Reversal() = default;

private:
	_bool m_bState = false;
public:
	static CClock_Reversal* Create() { return new CClock_Reversal; }
	virtual bool isThreashHoldReached(_double _time,  const _tchar* _pTimerKey = L"Timer_100") override;
	virtual void Free() override;
};
END
