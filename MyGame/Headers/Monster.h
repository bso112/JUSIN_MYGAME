#pragma once
#include "Character.h"
#include "State.h"
BEGIN(MyGame)

class CAnimator;
class CHpBar;
class CItem;
class CMonster abstract : public CCharacter
{

protected:
	explicit CMonster(PDIRECT3DDEVICE9 _pGraphic_Device) :CCharacter(_pGraphic_Device) {};
	explicit CMonster(CMonster& _rhs);
	virtual ~CMonster() = default;

protected:
	CAnimator*		m_pAnimator = nullptr;
	CHpBar*			m_pHpBar = nullptr;
	//얼마나 가까워지면 잠에서 깨는가
	_int			m_iAwakeRange = 0;
public:
	virtual HRESULT	Initialize(void * _param);
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render();
	
public:
	//잠에서 깼는가
	_bool	IsAwake();

protected:
	//플레이어와 턴수를 비교해서 자신이 가져야할 속도를 계산한다.
	_float		CalulateSpeed(_int movePerturn);

public:
	HRESULT	Throw_Item(CItem* pItem);

protected:
	virtual	HRESULT	OnRender();
	virtual void OnDead();
	virtual	void OnAttack(CGameObject * _pOther);
	virtual void OnTakeDamage(float _fDamage) override;


public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;









};
END
