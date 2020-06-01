#include "stdafx.h"
#include "..\Headers\PoisionPotion.h"
#include "ObjMgr.h"
#include "Effect.h"
#include "Hero.h"

USING(MyGame)

void CPoisionPotion::OnDrink(CHero * _pHero)
{
	CEffect::STATEDESC desc;
	desc.m_tBaseDesc = BASEDESC(m_pTransform->Get_Position(), Vector2(TILECX, TILECY));
	desc.m_tBuffType = CBuff::TYPE_POISION;
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	RETURN_IF_NULL(pObjMgr);
	CEffect* pSmoke = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Smoke", SCENE_STAGE, L"Effect", SCENE_STAGE, &desc));
	RETURN_IF_NULL(pSmoke);
	pSmoke->EffectOn(_pHero);
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"포션을 마시자, 몸에 독의 기운이 퍼지기 시작했다."));
}

void CPoisionPotion::OnShatter()
{
	if (nullptr == m_pTransform)
		return;

	CEffect::STATEDESC desc;
	desc.m_tBaseDesc = BASEDESC(m_pTransform->Get_Position(), Vector2(TILECX, TILECY));
	desc.m_tBuffType = CBuff::TYPE_POISION;
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	RETURN_IF_NULL(pObjMgr);
	CEffect* pSmoke = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Smoke", SCENE_STAGE, L"Effect", SCENE_STAGE, &desc));
	pSmoke->Play();
	CDialogMgr::Get_Instance()->Log_Main(new wstring(L"포션이 깨지고, 독의 안개가 뿜어져나왔다."));

}
