#pragma once
#include "E:\myClient\MyGame\Headers\Base.h"

BEGIN(MyGame)
class CClock abstract : public CBase
{
public:
	explicit CClock() {};
	virtual ~CClock() = default;

protected:
	_double m_TimeAcc = 0.0;

public:
	virtual bool isThreashHoldReached(_double _time, const _tchar* _pTimerKey = L"Timer_100") = 0;
};

class CTriggerClock final : public CClock
{
public:
	explicit CTriggerClock() {};
	virtual  ~CTriggerClock() = default;
	
	virtual bool isThreashHoldReached(_double _time, const _tchar* _pTimerKey = L"Timer_100") override;
	virtual void Free() override;
};

class CDelayClock final : public CClock
{
public:
	explicit CDelayClock() {};
	virtual  ~CDelayClock() = default;

	virtual bool isThreashHoldReached(_double _time,  const _tchar* _pTimerKey = L"Timer_100") override;
	virtual void Free() override;
};

class CSingleClock final : public CClock
{
public:
	explicit CSingleClock() {};
	virtual  ~CSingleClock() = default;

	virtual bool isThreashHoldReached(_double _time,  const _tchar* _pTimerKey = L"Timer_100") override;
	virtual void Free() override;
};

class CReversalClock final : public CClock
{
public:
	explicit CReversalClock() {};
	virtual  ~CReversalClock() = default;

private:
	_bool m_bState = false;
public:
	virtual bool isThreashHoldReached(_double _time,  const _tchar* _pTimerKey = L"Timer_100") override;
	virtual void Free() override;
};
END
