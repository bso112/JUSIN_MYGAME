#pragma once

BEGIN(MyGame)
class CBase
{
public:
	CBase();
	virtual ~CBase();

private:
	unsigned long m_RefCnt = 0;

public:
	unsigned long Release();
	unsigned long AddRef();
	virtual void Free() = 0;
};

END