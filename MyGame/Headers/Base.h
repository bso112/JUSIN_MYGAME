#pragma once

BEGIN(MyGame)
class CBase
{
protected:
	explicit CBase();
	virtual ~CBase();

private:
	unsigned long m_RefCnt = 0;

public:
	unsigned long Release();
	unsigned long AddRef();
	virtual void Free() = 0;

public:
	virtual HRESULT	OnKeyDown(_int KeyCode);
	virtual HRESULT OnKeyPressing(_int KeyCode);
	virtual HRESULT	OnKeyUp(_int KeyCode);
	virtual	HRESULT OnMoveTurn();

};


END