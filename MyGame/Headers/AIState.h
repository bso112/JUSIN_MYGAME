#pragma once
#include "State.h"

BEGIN(MyGame)

class CAIState abstract : public CState
{
public:
	explicit CAIState(CCharacter* _pActor) :CState(_pActor) {};
};


class CAISleeping : public CAIState
{
public:
	explicit CAISleeping(CCharacter* _pActor) :CAIState(_pActor) {};
public:
	virtual CState*	Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta) override;


	// CAIState을(를) 통해 상속됨
	virtual void Free() override;

};

class CAIHunting : public CAIState
{
public:
	explicit CAIHunting(CCharacter* _pActor) :CAIState(_pActor) {};
public:
	virtual CState*	Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta) override;


	// CAIState을(를) 통해 상속됨
	virtual void Free() override;

};

class CAIWandering : public CAIState
{
public:
	explicit CAIWandering(CCharacter* _pActor) :CAIState(_pActor) {};

public:
	virtual CState*	Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta) override;


	// CAIState을(를) 통해 상속됨
	virtual void Free() override;

};

class CAIIdle : public CAIState
{
public:
	explicit CAIIdle(CCharacter* _pActor) :CAIState(_pActor) {};
public:
	virtual CState*	Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta) override;


	// CAIState을(를) 통해 상속됨
	virtual void Free() override;

};

class CAIIdle_Rat : public CAIIdle
{
public:
	explicit CAIIdle_Rat(CCharacter* _pActor) :CAIIdle(_pActor) {};
public:
	virtual CState*	Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta) override;


	// CAIState을(를) 통해 상속됨
	virtual void Free() override;

};

class CAIHunting_Rat : public CAIHunting
{
public:
	explicit CAIHunting_Rat(CCharacter* _pActor) :CAIHunting(_pActor) {};
private:
	Vector3 m_vJumpVelo = Vector3(0.f, -7.f, 0.f);

public:
	virtual CState*	Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta) override;


	// CAIHunting을(를) 통해 상속됨
	virtual void Free() override;

};
END