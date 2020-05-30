#include "stdafx.h"
#include "..\Headers\FirePotion.h"

USING(MyGame)

void CFirePotion::OnDrink(CHero * _pHero)
{
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"포션을 마시자, 몸에 불이 붙었다."));
}

void CFirePotion::OnShatter()
{
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"포션이 깨지자, 불이 뿜어져나왔다."));

}
