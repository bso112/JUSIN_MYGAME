#pragma once
#include "Base.h"

BEGIN(MyGame)
class CLayer;
class CTurnMgr : public CBase
{
	DECLARE_SINGLETON(CTurnMgr)
private:
	explicit CTurnMgr();
	explicit CTurnMgr(CTurnMgr& _rhs);
	virtual ~CTurnMgr() = default;

private:
	_uint	m_iCurrTurn = 0;
	size_t	m_iLayerIndex = 0;
	vector<CLayer*> m_vecLayer;
public:
	int		MoveTurn(_int _iTurnCnt, _double _timeDelta);
	
private:
	void	OnNextTurn(_double _timeDelta);
public:
	virtual void Free() override;
};
END
