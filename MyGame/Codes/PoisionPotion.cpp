#include "stdafx.h"
#include "..\Headers\PoisionPotion.h"

USING(MyGame)

void CPoisionPotion::OnDrink(CHero * _pHero)
{
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"������ ������, ���� ���� ����� ������ �����ߴ�."));
}

void CPoisionPotion::OnShatter()
{
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"������ ������, ���� �Ȱ��� �վ������Դ�."));

}
