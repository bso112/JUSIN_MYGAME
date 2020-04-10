#pragma once
#include "Base.h"

BEGIN(MyGame)
class CTimer final: public CBase
{
private:
	CTimer();
	virtual ~CTimer();

private:
	LARGE_INTEGER m_FrameTime;
	LARGE_INTEGER m_FixTime;
	LARGE_INTEGER m_LastTime;
	LARGE_INTEGER m_CpuTick;

	LARGE_INTEGER m_TimeAcc;
	_double	m_TimeDelta;

public:
	HRESULT	Initalize();
	_double Compute_TimeDelta();
	_double Get_TimeDelta() { return m_TimeDelta; }

public:
	static CTimer*	Create();
private:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};

END