#pragma once
#include "Base.h"
#include "Level.h"
BEGIN(MyGame)
#define DEPTH 3
class CLevelMgr final: public CBase
{
	DECLARE_SINGLETON(CLevelMgr)
private:
	explicit CLevelMgr() { ZeroMemory(m_aLevel, sizeof(m_aLevel)); }
	virtual ~CLevelMgr() = default;

private:
	CLevel* m_aLevel[DEPTH];
	_uint	m_iCurrLevel = 0;

public:
	CLevel*	Get_CurrLevel();
	
public:
	HRESULT Initialize(PDIRECT3DDEVICE9 _pGraphic_Device);
	CTerrain*	PickTile(POINT& pt);
public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};
END
