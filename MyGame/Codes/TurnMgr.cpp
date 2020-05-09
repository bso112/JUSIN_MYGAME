#include "stdafx.h"
#include "..\Headers\TurnMgr.h"
#include "Layer.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "GameObject.h"
#include "TimerMgr.h"

USING(MyGame)
IMPLEMENT_SINGLETON(CTurnMgr)

CTurnMgr::CTurnMgr()
{

}

CTurnMgr::CTurnMgr(CTurnMgr & _rhs)
{
}





_int CTurnMgr::MoveTurn(_int _iTurnCnt, _double _timeDelta)
{



	return S_OK;
}

void CTurnMgr::OnNextTurn(_double _timeDelta)
{


	

}

void CTurnMgr::Free()
{
	for (auto& layer : m_vecLayer)
	{
		Safe_Release(layer);
	}
	m_vecLayer.clear();
}
