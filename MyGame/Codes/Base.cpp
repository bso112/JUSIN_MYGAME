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
	//만약 지워졌으면 항상 0을 반환한다.
	if (m_RefCnt == 0)
	{
		Free();
		delete this;
		return 0;
	}
	else
		//후위를 쓰는 이유는 지워짐(0)과 안지워짐(1이상) 을 구분하기 위해
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

HRESULT CBase::OnMoveTurn()
{
	return S_OK;
}
