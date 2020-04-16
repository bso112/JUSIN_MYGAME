#pragma once
#include "Base.h"

BEGIN(MyGame)
class CHero;
class CHeroMgr :	public CBase
{
	DECLARE_SINGLETON(CHeroMgr)
private:
	explicit CHeroMgr();
	virtual ~CHeroMgr() = default;


public:
	static CHero* m_pHero;
	
public:
	static CHero*	Get_Hero() { return m_pHero; }
	static void		Set_Hero(CHero* _pHero) { m_pHero = _pHero; }
};

END