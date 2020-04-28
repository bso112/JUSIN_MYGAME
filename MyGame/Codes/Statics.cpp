#include "stdafx.h"
#include "..\Headers\Statics.h"

USING(MyGame)
IMPLEMENT_SINGLETON(CStatics)

CStatics::SELECTED_HERO CStatics::m_eSelectedHero = CStatics::HERO_END;

void CStatics::Free()
{
}
