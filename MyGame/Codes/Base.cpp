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


HRESULT CBase::OnKeyDown(_int KeyCode)
{
	return S_OK;
}

HRESULT CBase::OnKeyPressing(_int KeyCode)
{
	return S_OK;
}

HRESULT CBase::OnKeyUp(_int KeyCode)
{
	return S_OK;
}
