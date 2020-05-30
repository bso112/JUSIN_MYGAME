#include "stdafx.h"
#include "..\Headers\PoisionPotion.h"

USING(MyGame)

void CPoisionPotion::OnDrink(CHero * _pHero)
{
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"포션을 마시자, 몸에 독의 기운이 퍼지기 시작했다."));
}

void CPoisionPotion::OnShatter()
{
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"포션이 깨지고, 독의 안개가 뿜어져나왔다."));

}
