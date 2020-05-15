#include "stdafx.h"
#include "..\Headers\Hero.h"
#include "KeyMgr.h"
#include "LevelMgr.h"
#include "Transform.h"
#include "TurnMgr.h"
#include "Terrain.h"
#include "ObjMgr.h"
#include "Layer.h"
USING(MyGame)



CHero::CHero(PDIRECT3DDEVICE9 _pGraphic_Device)
	: CCharacter(_pGraphic_Device)
{
	ZeroMemory(m_pAnimator, sizeof(m_pAnimator));
}

CHero::CHero(CHero & _hero)
	: CCharacter(_hero)
{

}

HRESULT CHero::KeyCheck(_double _timeDelta)
{
	//if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	//{
	//	if (nullptr == m_pTransform)
	//		return E_FAIL;

	//	POINT pt;
	//	GetCursorPos(&pt);
	//	ScreenToClient(g_hWnd, &pt);

	//	vector<CTerrain*> route;
	//	CLevel* pLevel = CLevelMgr::Get_Instance()->Get_CurrLevel();
	//	RETURN_FAIL_IF_NULL(pLevel);
	//	pLevel->Get_Route(m_pTransform->Get_Position(), Vector2((float)pt.x, (float)pt.y), route, m_pTransform);

	//	//해당 루트를 따라가기 위해 필요한 턴수를 계산
	//	_int iTurnCnt = (_int)route.size() / m_pTransform->Get_Desc().movePerTurn;

	//	m_pTransform->Go_Route(route, 1.f, iTurnCnt);

	//	//플레이어가 움직일 턴 이동
	//	CTurnMgr::Get_Instance()->MoveTurn_Simultaneously(iTurnCnt);
	//}

	return S_OK;
}

HRESULT CHero::Set_InitialPos()
{
	if (m_pTransform == nullptr)
		return E_FAIL;

	CLevel* pLevel = CLevelMgr::Get_Instance()->Get_CurrLevel();

	if (nullptr == pLevel)
		return E_FAIL;

	m_pTransform->Set_Position(pLevel->Get_PlayerSpawnPos());

	

	return S_OK;

	
}

HRESULT CHero::PlayAnimation(const _tchar * _pTag)
{
	return m_pAnimator[m_eCurrCloth]->Play(_pTag);
}

bool CHero::Has_Key(TIER _tier)
{


	return true;
}

void CHero::Free()
{

	CCharacter::Free();
}


