#pragma once

#include "Base.h"
BEGIN(MyGame)

class CCharacter;


class CState abstract : public CBase
{
public:
	explicit CState(CCharacter* _pActor) :m_pActor(_pActor) {};
protected:
	CCharacter*	m_pActor = nullptr;



};

END