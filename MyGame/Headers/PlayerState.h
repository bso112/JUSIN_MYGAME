#pragma once
#include "State.h"
BEGIN(MyGame)
class CPlayerState abstract : public CState
{
public:
	//�θ� ���µ�
	enum STATE { STATE_IDLE, STATE_WALK, STATE_USING, STATE_END };
public:
	explicit CPlayerState(CCharacter* _pActor) :CState(_pActor) {};

public:
	virtual STATE	LateUpdate() { return STATE_END; }
	//���� ���� ��ӹٲ�ٸ� ����ü�� ����°� ����غ���.
	virtual STATE	Act(_bool _canAttack, _bool _isAlerted,  _double _timeDelta) = 0;
};

class CPlayerIdle : public CPlayerState
{
public:
	explicit CPlayerIdle(CCharacter* _pActor) :CPlayerState(_pActor) {};

public:
	virtual STATE	Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta);

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Free() override;
};

class CPlayerWalk : public CPlayerState
{
public:
	explicit CPlayerWalk(CCharacter* _pActor) :CPlayerState(_pActor) {};

public:
	virtual STATE	LateUpdate() override;
	virtual STATE	Act(_bool _canAttack, _bool _isAlerted,  _double _timeDelta);

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Free() override;
};

class CPlayerUsing : public CPlayerState
{
public:
	explicit CPlayerUsing(CCharacter* _pActor) :CPlayerState(_pActor) {};

public:
	virtual STATE	Act(_bool _canAttack, _bool _isAlerted,  _double _timeDelta);

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Free() override;
};


END