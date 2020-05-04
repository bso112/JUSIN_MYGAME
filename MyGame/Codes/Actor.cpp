#include "stdafx.h"
#include "..\Headers\Actor.h"

USING(MyGame)



CActor::CActor(CActor & _actor)
	:CGameObject(_actor)
{
}
