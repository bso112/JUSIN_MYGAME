#include "stdafx.h"
#include "..\Headers\HealPotion.h"
#include "Hero.h"
USING(MyGame)

void CHealPotion::OnDrink(CHero * _pHero)
{
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"������ ������, ü���� ȸ���Ǵ� ���� ��������."));
	_pHero->Heal(m_tDesc.m_tStats.m_fHp);
}

