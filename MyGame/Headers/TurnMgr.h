#pragma once
#include "Base.h"

BEGIN(MyGame)
#define	MAX_LAYER_CNT 3
class CLayer;
class CCharacter;
/*
���� �����Ѵٴ� ����� State�� �����Ѵٴ� ������ �и��ߴ�.
���ʿ� �װ� ��Ʈ�� �����ϴ°� �߸��̾���.
*/
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

	_bool	m_bActLock = false;

private:
	CLayer*	m_pActorLayers[MAX_LAYER_CNT];

	

private:
	CCharacter*				m_pCurrActor = nullptr;

	_bool			m_bTurnStart = false;
public:
	HRESULT		Initialize();
	_int		Update_sequentially();
	_int		Update_sequentially2();
	_int		Update_Simultaneously();
	_int		Get_TurnCnt() {return m_iMaxTurn;}

public:
	HRESULT	MoveTurn_sequentially(_int _iTurnCnt);
	HRESULT	MoveTurn_sequentially2(_int _iTurnCnt);
	HRESULT	MoveTurn_Simultaneously(_int _iTurnCnt);




	

private:
	_int	Get_NextActor(CCharacter** _pOutCharacter);
public:
	virtual void Free() override;
};
END
