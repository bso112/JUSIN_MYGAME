#pragma once
#include "Character.h"
#include "State.h"
BEGIN(MyGame)

class CAnimator;
class CMonster abstract : public CCharacter
{

protected:
	explicit CMonster(PDIRECT3DDEVICE9 _pGraphic_Device) :CCharacter(_pGraphic_Device) {};
	explicit CMonster(CMonster& _rhs);
	virtual ~CMonster() = default;

protected:
	CAnimator*		m_pAnimator = nullptr;

public:
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render();

protected:
	//플레이어와 턴수를 비교해서 자신이 가져야할 속도를 계산한다.
	_float		CalulateSpeed(_int movePerturn);

protected:
	virtual	HRESULT	OnRender();
	virtual void OnDead();
	virtual	void OnAttack(CGameObject * _pOther);


public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;









};
END
