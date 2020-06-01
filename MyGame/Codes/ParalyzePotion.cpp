#include "stdafx.h"
#include "..\Headers\ParalyzePotion.h"
#include "ObjMgr.h"
#include "Effect.h"
#include "Hero.h"
USING(MyGame)

void CParalyzePotion::OnDrink(CHero * _pHero)
{
	CEffect::STATEDESC desc;
	desc.m_tBaseDesc = BASEDESC(m_pTransform->Get_Position(), Vector2(TILECX, TILECY));
	desc.m_tBuffType = CBuff::TYPE_PARALIZE;
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	RETURN_IF_NULL(pObjMgr);
	CEffect* pSmoke = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Smoke", SCENE_STAGE, L"Effect", SCENE_STAGE, &desc));
	RETURN_IF_NULL(pSmoke);
	pSmoke->EffectOn(_pHero);
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"포션을 마시자, 몸에 마비의 기운이 퍼지기 시작했다."));
}

void CParalyzePotion::OnShatter()
{
	CEffect::STATEDESC desc;
	desc.m_tBaseDesc = BASEDESC(m_pTransform->Get_Position(), Vector2(TILECX, TILECY));
	desc.m_tBuffType = CBuff::TYPE_PARALIZE;
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	RETURN_IF_NULL(pObjMgr);
	CEffect* pSmoke = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Smoke", SCENE_STAGE, L"Effect", SCENE_STAGE, &desc));
	pSmoke->Play();
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"포션이 깨지고, 마비의 안개가 뿜어져나왔다."));

}
