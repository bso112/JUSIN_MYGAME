#include "stdafx.h"
#include "..\Headers\Timer.h"

USING(MyGame)

CTimer::CTimer()
{
}


CTimer::~CTimer()
{
}

HRESULT CTimer::Initalize()
{	
	QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceCounter(&m_LastTime);
	QueryPerformanceFrequency(&m_CpuTick);

	return S_OK;
}

_double CTimer::Compute_TimeDelta()
{
	QueryPerformanceCounter(&m_FrameTime);

	if (m_FrameTime.QuadPart - m_FixTime.QuadPart >= m_CpuTick.QuadPart)
	{
		m_FixTime = m_FixTime;
		QueryPerformanceFrequency(&m_CpuTick);
	}

	 m_TimeDelta = (_double)(m_FrameTime.QuadPart - m_LastTime.QuadPart) / m_CpuTick.QuadPart;
	
	m_LastTime = m_FrameTime;

	return _double(m_TimeDelta);
}

CTimer * CTimer::Create()
{
	CTimer* pInstance = new CTimer;
	if (FAILED(pInstance->Initalize()))
	{
		MSG_BOX("Fail to create timer");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTimer::Free()
{
}
