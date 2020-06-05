#pragma once
#include "State.h"

BEGIN(MyGame)


class CAIState abstract : public CState
{
public:
	//AI의 부모상태들이다.
	enum STATE { STATE_IDLE, STATE_SLEEP, STATE_HUNTING, STATE_WADERING, STATE_RAGE, STATE_END};
public:
	explicit CAIState(CCharacter* _pActor) :CState(_pActor) {};

public:
	//리턴을 통해 턴의 종료시점을 알려준다. Actor의 상태를 반환된 State로 변경한다.
	virtual STATE	LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta) = 0;
	//변경 된 이후 계속 실행할 루프.. STATE를 반환할 필요 없을듯
	virtual STATE	Act(_bool _canAttack, _bool _isAlerted,_double _timeDelta) = 0;
	virtual	void	OnStateEnter(_bool _canAttack, _bool _isAlerted, _double _timeDelta);
};



class CAISleeping : public CAIState
{
public:
	explicit CAISleeping(CCharacter* _pActor) :CAIState(_pActor) {};
public:
	virtual STATE	LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta) override;
	virtual STATE	Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta) override;
	virtual	void	OnStateEnter(_bool _canAttack, _bool _isAlerted, _double _timeDelta);


	// CAIState을(를) 통해 상속됨
	virtual void Free() override;

};

class CAIHunting : public CAIState
{
public:
	explicit CAIHunting(CCharacter* _pActor) :CAIState(_pActor) {};

private:
	_bool	m_bAttack = false;
public:
	virtual STATE	LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta) override;
	virtual STATE	Act(_bool _canAttack, _bool _isAlerted,  _double _timeDelta) override;


	// CAIState을(를) 통해 상속됨
	virtual void Free() override;

};



class CAIWandering : public CAIState
{
public:
	explicit CAIWandering(CCharacter* _pActor) :CAIState(_pActor) {};

public:
	virtual STATE	LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta) override;
	virtual STATE	Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta) override;

	// CAIState을(를) 통해 상속됨
	virtual void Free() override;

};

class CAIIdle : public CAIState
{
public:
	explicit CAIIdle(CCharacter* _pActor) :CAIState(_pActor) {};


public:
	virtual STATE	LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta) override;
	virtual STATE	Act(_bool _canAttack, _bool _isAlerted,  _double _timeDelta) override;


	// CAIState을(를) 통해 상속됨
	virtual void Free() override;

};




END