#pragma once

#include "Base.h"
BEGIN(MyGame)

class CCharacter;
class CTransform;
class CAnimator;

class CState abstract : public CBase
{
public:
	explicit CState(CCharacter* _pActor) :m_pActor(_pActor) {};
protected:
	CCharacter*	m_pActor = nullptr;
public:
	//변경 된 이후 계속 실행할 루프
	virtual CState*	Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt, _double _timeDelta) = 0;


};

END