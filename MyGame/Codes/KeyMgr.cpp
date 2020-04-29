#include "stdafx.h"
#include "..\Headers\KeyMgr.h"

USING(MyGame)

IMPLEMENT_SINGLETON(CKeyMgr)

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}


bool CKeyMgr::Key_Pressing(int _Key)
{
	if ((GetAsyncKeyState(_Key) & 0x8000))
		return true;
	return false;
}

bool CKeyMgr::Key_Down(int _Key)
{
	if (!m_bKeyState[_Key] && (GetAsyncKeyState(_Key) & 0x8000))
	{
		m_bKeyState[_Key] = !m_bKeyState[_Key];
		return true;
	}
	return false;
}

bool CKeyMgr::Key_Up(int _Key)
{
	if (m_bKeyState[_Key] && !(GetAsyncKeyState(_Key) & 0x8000))
	{
		m_bKeyState[_Key] = !m_bKeyState[_Key];
		return true;
	}
	return false;
}

void CKeyMgr::Key_Update()
{
	// Key ���� ���� �Լ�
	for (int i = 0; i < VK_MAX; ++i)
	{
		if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];

		if (!m_bKeyState[i] && (GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}
}

void CKeyMgr::Free()
{
}
