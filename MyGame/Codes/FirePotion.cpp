#include "stdafx.h"
#include "..\Headers\FirePotion.h"

USING(MyGame)

void CFirePotion::OnDrink(CHero * _pHero)
{
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"������ ������, ���� ���� �پ���."));
}

void CFirePotion::OnShatter()
{
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"������ ������, ���� �վ������Դ�."));

}
