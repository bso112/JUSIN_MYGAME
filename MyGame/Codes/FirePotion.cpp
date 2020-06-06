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
	CEffect::STATEDESC desc;
	desc.m_tBuffType = CBuff::TYPE_BURN;
	CEffect* pFire = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Fire", SCENE_STAGE, L"Effect", SCENE_STAGE, &desc));
	pFire->EffectOn(_pHero);

	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"포션을 마시자, 몸에 불이 붙었다."));
}

void CFirePotion::OnShatter()
{
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	RETURN_IF_NULL(pObjMgr);
	CEffect::STATEDESC desc;
	desc.m_tBaseDesc = BASEDESC(m_pTransform->Get_Position(), Vector2(TILECX, TILECY));
	desc.m_tBuffType = CBuff::TYPE_BURN;
	CEffect* pFire = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Fire", SCENE_STAGE, L"Effect", SCENE_STAGE, &desc));
	pFire->Set_CollidableEffect(true);
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"포션이 깨지자, 불이 뿜어져나왔다."));

}
