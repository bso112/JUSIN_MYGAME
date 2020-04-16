#pragma once
#include "Base.h"

#define VK_MAX 0xff

BEGIN(MyGame)

class CKeyMgr final: public CBase
{
	DECLARE_SINGLETON(CKeyMgr)

private:
	CKeyMgr() { ZeroMemory(m_bKeyState, sizeof(m_bKeyState)); }
	virtual ~CKeyMgr() = default;

public:
	bool Key_Pressing(int _Key);
	bool Key_Down(int _Key);
	bool Key_Up(int _Key);
	void Key_Update();

private:
	bool				m_bKeyState[VK_MAX];


	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};
END
