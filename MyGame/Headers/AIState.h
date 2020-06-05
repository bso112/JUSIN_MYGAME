#pragma once
#include "State.h"

BEGIN(MyGame)


class CAIState abstract : public CState
{
public:
	//AI�� �θ���µ��̴�.
	enum STATE { STATE_IDLE, STATE_SLEEP, STATE_HUNTING, STATE_WADERING, STATE_RAGE, STATE_END};
public:
	explicit CAIState(CCharacter* _pActor) :CState(_pActor) {};

public:
	//������ ���� ���� ��������� �˷��ش�. Actor�� ���¸� ��ȯ�� State�� �����Ѵ�.
	virtual STATE	LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta) = 0;
	//���� �� ���� ��� ������ ����.. STATE�� ��ȯ�� �ʿ� ������
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


	// CAIState��(��) ���� ��ӵ�
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


	// CAIState��(��) ���� ��ӵ�
	virtual void Free() override;

};



class CAIWandering : public CAIState
{
public:
	explicit CAIWandering(CCharacter* _pActor) :CAIState(_pActor) {};

public:
	virtual STATE	LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta) override;
	virtual STATE	Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta) override;

	// CAIState��(��) ���� ��ӵ�
	virtual void Free() override;

};

class CAIIdle : public CAIState
{
public:
	explicit CAIIdle(CCharacter* _pActor) :CAIState(_pActor) {};


public:
	virtual STATE	LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta) override;
	virtual STATE	Act(_bool _canAttack, _bool _isAlerted,  _double _timeDelta) override;


	// CAIState��(��) ���� ��ӵ�
	virtual void Free() override;

};




END