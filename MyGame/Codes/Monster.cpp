#include "stdafx.h"
#include "..\Headers\Monster.h"
#include "ObjMgr.h"
#include "SceneMgr.h"

USING(MyGame)

CMonster::CMonster(CMonster & _rhs)
	:CCharacter(_rhs)
{
	SCENEID eSceneID = CSceneMgr::Get_Instance()->Get_CurrScene();
	m_pHero = (CHero*)CObjMgr::Get_Instance()->Get_Player(eSceneID);
}

void CMonster::Free()
{
	CCharacter::Free();
}
