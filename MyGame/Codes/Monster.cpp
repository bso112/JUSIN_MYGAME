#include "stdafx.h"
#include "..\Headers\Monster.h"

USING(MyGame)

CMonster::CMonster(CMonster & _rhs)
	:CCharacter(_rhs)
{
}

void CMonster::Free()
{
	CCharacter::Free();
}
