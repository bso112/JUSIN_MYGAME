#include "stdafx.h"
#include "..\Headers\ParalyzePotion.h"

USING(MyGame)

void CParalyzePotion::OnDrink(CHero * _pHero)
{
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"포션을 마시자, 몸에 마비의 기운이 퍼지기 시작했다."));
}

void CParalyzePotion::OnShatter()
{
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"포션이 깨지고, 마비의 안개가 뿜어져나왔다."));

}
