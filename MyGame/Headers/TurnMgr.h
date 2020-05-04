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
	map<const _tchar*, CLayer*>*	m_mapLayer;

public:
	//_iCnt만큼 턴을 넘긴다.
	HRESULT	MoveTurn(_int _iCnt);

public:
	virtual void Free() override;
};
END
