#include "stdafx.h"
#include "..\Headers\ParalyzePotion.h"

USING(MyGame)

void CParalyzePotion::OnDrink(CHero * _pHero)
{
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"������ ������, ���� ������ ����� ������ �����ߴ�."));
}

void CParalyzePotion::OnShatter()
{
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"������ ������, ������ �Ȱ��� �վ������Դ�."));

}
