#include "stdafx.h"
#include "Base.h"

USING(MyGame)
CBase::CBase()
{
}


CBase::~CBase()
{
}

unsigned long CBase::Release()
{	
	if (m_RefCnt == 0)
	{
		Free();
		delete this;
		return 0;
	}
	else
		return m_RefCnt--;
}

unsigned long CBase::AddRef()
{
	
	return ++m_RefCnt;
}
