#include "stdafx.h"
#include "..\Headers\FirePotion.h"
#include "ObjMgr.h"
#include "Effect.h"
#include "Hero.h"
#include "LevelMgr.h"
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

	if (nullptr == m_pTransform) return;

	CLevelMgr* pLevelMgr = CLevelMgr::Get_Instance();
	if (nullptr == pLevelMgr) return;
	for (auto& vPos : pLevelMgr->Get_Area(m_pTransform->Get_Position(), 1))
	{
		CEffect::STATEDESC desc;
		desc.m_tBaseDesc = BASEDESC(vPos, Vector2(TILECX, TILECY));
		desc.m_tBuffType = CBuff::TYPE_BURN;

		CEffect* pFire = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Fire", SCENE_STAGE, L"Effect", SCENE_STAGE, &desc));
		pFire->Set_CollidableEffect(true);
		pFire->Play();

	}
		CDialogMgr::Get_Instance()->Log_Main(new wstring(L"포션이 깨지자, 불이 뿜어져나왔다."));

}
