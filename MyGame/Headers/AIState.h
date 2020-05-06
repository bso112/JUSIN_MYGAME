#pragma once
#include "State.h"

BEGIN(MyGame)


class CAIState abstract : public CState
{
public:
	//AI의 부모상태들이다.
	enum STATE { STATE_IDLE, STATE_SLEEP, STATE_HUNTING, STATE_WADERING, STATE_END};
public:
	explicit CAIState(CCharacter* _pActor) :CState(_pActor) {};

public:
	//변경 된 이후 계속 실행할 루프
	virtual STATE	Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta) = 0;
};


class CAISleeping : public CAIState
{
public:
	explicit CAISleeping(CCharacter* _pActor) :CAIState(_pActor) {};
public:
	virtual STATE	Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta) override;


	// CAIState을(를) 통해 상속됨
	virtual void Free() override;

};

class CAIHunting : public CAIState
{
public:
	explicit CAIHunting(CCharacter* _pActor) :CAIState(_pActor) {};
public:
	virtual STATE	Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta) override;


	// CAIState을(를) 통해 상속됨
	virtual void Free() override;

};

class CAIWandering : public CAIState
{
public:
	explicit CAIWandering(CCharacter* _pActor) :CAIState(_pActor) {};

public:
	virtual STATE	Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta) override;


	// CAIState을(를) 통해 상속됨
	virtual void Free() override;

};

class CAIIdle : public CAIState
{
public:
	explicit CAIIdle(CCharacter* _pActor) :CAIState(_pActor) {};
public:
	virtual STATE	Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta) override;


	// CAIState을(를) 통해 상속됨
	virtual void Free() override;

};



class CAIHunting_Jump : public CAIHunting
{
public:
	explicit CAIHunting_Jump(CCharacter* _pActor) :CAIHunting(_pActor) {};
private:
	Vector3 m_vJumpVelo = Vector3(0.f, -7.f, 0.f);

public:
	virtual STATE	Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta) override;


	// CAIHunting을(를) 통해 상속됨
	virtual void Free() override;

};
END