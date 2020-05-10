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
	_int	m_iCurrTurn = 0;
	_int	m_iMaxTurn = 0;

private:
	_int	m_iTurnToSpend = 0;

private:
	CLayer*	m_pActorLayers[2];

	

private:
	CCharacter*				m_pCurrActor = nullptr;

public:
	HRESULT	Initialize();
	_int		Update_sequentially();
	_int		Update_Simultaneously();

public:
	HRESULT	MoveTurn_sequentially(_int _iTurnCnt);
	HRESULT	MoveTurn_Simultaneously(_int _iTurnCnt);


public:
	_int	Get_TurnCnt() { return m_iTurnToSpend; }
	

private:
	_int	Get_NextActor(CCharacter** _pOutCharacter);
public:
	virtual void Free() override;
};
END
