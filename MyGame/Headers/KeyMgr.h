#pragma once
#include "Base.h"

BEGIN(MyGame)

#define VK_MAX 0xff

class CKeyMgr : public CBase
{
	DECLARE_SINGLETON(CKeyMgr)

private:
	explicit CKeyMgr();
	virtual	 ~CKeyMgr() = default;

public:
	bool Key_Pressing(int _Key);
	bool Key_Down(int _Key);
	bool Key_Up(int _Key);
	void Key_Update();

public:
	HRESULT RegisterObserver(SCENEID _eSceneID, CBase* _pObserver);
	HRESULT UnRegisterObserver(SCENEID _eSceneID, CBase* _pObserver);
	HRESULT	ClearObservers(SCENEID _eSceneID);
private:
	list<CBase*> m_listObservers[SCENE_END];

private:
	bool				m_bKeyState[VK_MAX];

	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};

END