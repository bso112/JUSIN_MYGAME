#include "stdafx.h"
#include "LevelMgr.h"
#include "Level.h"
USING(MyGame)

IMPLEMENT_SINGLETON(CLevelMgr)

HRESULT CLevelMgr::Initialize(PDIRECT3DDEVICE9 _pGraphic_Device)
{

	m_aLevel[0] = CLevel::Create(_pGraphic_Device, SCENE_STAGE, L"../Bin/Data/level1.dat");
	RETURN_FAIL_IF_NULL(m_aLevel[0]);
	
	return m_aLevel[0]->Load_World(SCENE_STAGE);
}

CLevel*	CLevelMgr::Get_CurrLevel()
{
	if (m_iCurrLevel >= DEPTH)
		return nullptr;

	return m_aLevel[m_iCurrLevel];
}

void CLevelMgr::Free()
{
	for (int i = 0; i < DEPTH; ++i)
	{
		Safe_Release(m_aLevel[i]);
	}
}

CTerrain * CLevelMgr::PickTile(POINT & pt)
{
	CLevel* pLevel = Get_CurrLevel();
	if (nullptr == pLevel)
		return nullptr;
	return pLevel->Pick_Tile(pt);
}
