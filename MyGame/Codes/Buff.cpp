#include "stdafx.h"
#include "..\Headers\Buff.h"
#include "Character.h"
USING(MyGame)

void CBuff::AttachTo(CCharacter * _pCharacter)
{
	m_pTarget = _pCharacter;
}

void CBuff::Detach()
{
}

void CBuff::Act()
{
	m_pTarget->SetInvisible(true);
}
