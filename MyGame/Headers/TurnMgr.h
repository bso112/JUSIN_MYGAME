#pragma once
#include "Base.h"

BEGIN(MyGame)
class CLayer;
class CCharacter;
class CTurnMgr : public CBase
{
	DECLARE_SINGLETON(CTurnMgr)
private:
	explicit CTurnMgr();
	explicit CTurnMgr(CTurnMgr& _rhs);
	virtual ~CTurnMgr() = default;

private:
	SCENEID	m_eCurrScene = SCENE_END;
	size_t	m_iLayerIndex = 0;
	size_t	m_iObjIndex = 0;
	int		m_iCurrTurn = 0;

private:
	int		m_iMaxTurn = 0;

private:
	CCharacter*				m_pCurrActor = nullptr;

public:
	int		Update();

public:
	HRESULT	MoveTurn(_int _iTurnCnt);

private:
	_int	Get_NextActor(CCharacter** _pOutCharacter);
public:
	virtual void Free() override;
};
END
