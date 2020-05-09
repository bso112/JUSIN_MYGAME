#pragma once
#include "GameObject.h"

BEGIN(MyGame)
class CStateCon;
class CCharacter;
class CActor abstract : public CGameObject
{
protected:
	explicit CActor(PDIRECT3DDEVICE9 _pGraphic_Device) :CGameObject(_pGraphic_Device) {};
	explicit CActor(CActor& _actor);
	virtual ~CActor() = default;

protected:
	CStateCon* m_pStateCon = nullptr;
	//포커스하고 있는 대상
	CCharacter*	m_pFocus = nullptr;
	//공격범위
	_uint	m_iAttackRange = 0;
public:
	CCharacter*	Get_Focus() { return m_pFocus; }
	//타겟이 이 객체를 중심으로 해당 범위에 있는가?
	bool	IsTargetInRange(CCharacter* pTarget, _int _iRange);
	//어느 지형을 밟고있는지 인덱스를 리턴한다.
	HRESULT	Get_TerrainIndex(pair<_int, _int>& _out);
public:
	virtual _int	Start();
	virtual _int	Update();
public:
	virtual HRESULT Act() = 0;
};
END
