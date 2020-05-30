#include "stdafx.h"
#include "..\Headers\HealPotion.h"
#include "Hero.h"
USING(MyGame)

void CHealPotion::OnDrink(CHero * _pHero)
{
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"포션을 마시자, 체력이 회복되는 것이 느껴졌다."));
	_pHero->Heal(m_tDesc.m_tStats.m_fHp);
}

