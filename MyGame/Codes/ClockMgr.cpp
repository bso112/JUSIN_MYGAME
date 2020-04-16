//#include "stdafx.h"
//#include "..\Headers\ClockMgr.h"
//#include "Clock.h"
//USING(MyGame)
//
//
//
//CClock * CClockMgr::Get_Clock(const _tchar* _pKey, CLOCK _eType)
//{
//
//	CClock* pClock = nullptr;
//	
//	auto& iter = find_if(m_mapClock.begin(), m_mapClock.end(), CFinder_Tag(_pKey));
//	
//	if (iter == m_mapClock.end())
//	{
//		switch (_eType)
//		{
//		case MyGame::CClockMgr::CLOCK_TRIGGER:
//			pClock = CTriggerClock::Create();
//		case MyGame::CClockMgr::CLOCK_DELAY:
//			pClock = CDelayClock::Create();
//			break;
//		case MyGame::CClockMgr::CLOCK_SINGLE:
//			pClock = CSingleClock::Create();
//			break;
//		case MyGame::CClockMgr::CLOCK_REVERSAL:
//			pClock = CReversalClock::Create();
//			break;
//		default:
//			break;
//		}
//
//		m_mapClock.emplace(_pKey, pClock);
//	}
//	else
//		pClock = iter->second;
//	
//	//찾는 클락이 nullptr면 지운다.
//	if (iter->second == nullptr)
//	{
//		m_mapClock.erase(iter);
//	}
//
//	return pClock;
//
//}
//
//void CClockMgr::Free()
//{
//	for (auto& pair : m_mapClock)
//	{
//		Safe_Release(pair.second);
//	}
//
//	m_mapClock.clear();
//}
