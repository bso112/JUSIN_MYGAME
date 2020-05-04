#include "stdafx.h"
#include "..\Headers\TurnMgr.h"
#include "Layer.h"
#include "ObjMgr.h"
#include "SceneMgr.h"

USING(MyGame)
IMPLEMENT_SINGLETON(CTurnMgr)

CTurnMgr::CTurnMgr()
{
	m_mapLayer = CObjMgr::Get_Instance()->Get_Layers();
}

CTurnMgr::CTurnMgr(CTurnMgr & _rhs)
{
}

HRESULT CTurnMgr::MoveTurn(_int _iCnt)
{
	SCENEID eSceneID = CSceneMgr::Get_Instance()->Get_CurrScene();
	if (SCENE_END <= eSceneID)
		return E_FAIL;

	for (auto& pair : m_mapLayer[eSceneID])
	{
		if (0 != lstrcmp(pair.first, L"Player"))
		{
			pair.second->Act(_iCnt);
		}
	}

	++m_iCurrTurn;

	return S_OK;
}

void CTurnMgr::Free()
{
}
