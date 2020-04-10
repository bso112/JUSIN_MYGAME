#pragma once
#include "E:\myClient\MyGame\Headers\Base.h"

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
};

class CTriggerClock final : public CClock
{
private:
	explicit CTriggerClock() {};
	virtual  ~CTriggerClock() = default;
public:
	static CTriggerClock* Create() { return new CTriggerClock; }
	virtual bool isThreashHoldReached(_double _time, const _tchar* _pTimerKey = L"Timer_100") override;
	virtual void Free() override;
};

class CDelayClock final : public CClock
{
private:
	explicit CDelayClock() {};
	virtual  ~CDelayClock() = default;
public:

	static CDelayClock* Create() { return new CDelayClock; }
	virtual bool isThreashHoldReached(_double _time,  const _tchar* _pTimerKey = L"Timer_100") override;
	virtual void Free() override;
};

class CSingleClock final : public CClock
{
private:
	explicit CSingleClock() {};
	virtual  ~CSingleClock() = default;
public:
	static CSingleClock* Create() { return new CSingleClock; }
	virtual bool isThreashHoldReached(_double _time,  const _tchar* _pTimerKey = L"Timer_100") override;
	virtual void Free() override;
};

class CReversalClock final : public CClock
{
private:
	explicit CReversalClock() {};
	virtual  ~CReversalClock() = default;

private:
	_bool m_bState = false;
public:
	static CReversalClock* Create() { return new CReversalClock; }
	virtual bool isThreashHoldReached(_double _time,  const _tchar* _pTimerKey = L"Timer_100") override;
	virtual void Free() override;
};
END
