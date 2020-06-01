#include "stdafx.h"
#include "..\Headers\FirePotion.h"
#include "ObjMgr.h"
#include "Effect.h"
#include "Hero.h"
USING(MyGame)

void CFirePotion::OnDrink(CHero * _pHero)
{
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	RETURN_IF_NULL(pObjMgr);
	CEffect* pFire = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Fire", SCENE_STAGE, L"Effect", SCENE_STAGE));
	pFire->EffectOn(_pHero);

	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"������ ������, ���� ���� �پ���."));
}

void CFirePotion::OnShatter()
{
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	RETURN_IF_NULL(pObjMgr);
	
	BASEDESC desc = BASEDESC(m_pTransform->Get_Position(), Vector2(TILECX, TILECY));
	CEffect* pFire = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Fire", SCENE_STAGE, L"Effect", SCENE_STAGE, &desc));
	pFire->Set_Collidable(true);
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"������ ������, ���� �վ������Դ�."));

}
