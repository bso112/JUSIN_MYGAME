//#pragma once
//#include "Base.h"
//
//BEGIN(MyGame)
//class CClock;
//class CClockMgr final: public CBase
//{
//	DECLARE_SINGLETON(CClockMgr)
//
//public:
//	enum CLOCK { CLOCK_TRIGGER, CLOCK_DELAY, CLOCK_SINGLE, CLOCK_REVERSAL, CLOCK_END};
//
//private:
//	explicit CClockMgr();
//	virtual ~CClockMgr() = default;
//
//private:
//	map<const _tchar*, CClock*> m_mapClock;
//public:
//	CClock* Get_Clock(const _tchar* _pKey, CLOCK _eType);
//
//
//public:
//	// CBase을(를) 통해 상속됨
//	virtual void Free() override;
//
//};
//END