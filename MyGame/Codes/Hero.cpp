#include "stdafx.h"
#include "..\Headers\Hero.h"
#include "KeyMgr.h"
#include "World.h"
#include "Transform.h"
#include "TurnMgr.h"
#include "Terrain.h"
USING(MyGame)



CHero::CHero(PDIRECT3DDEVICE9 _pGraphic_Device)
	: CCharacter(_pGraphic_Device), m_pKeyMgr(CKeyMgr::Get_Instance())
{
	ZeroMemory(m_pAnimator, sizeof(m_pAnimator));
	Safe_AddRef(m_pKeyMgr);
}

CHero::CHero(CHero & _hero)
	: CCharacter(_hero),
	m_pKeyMgr(_hero.m_pKeyMgr)
{

}

HRESULT CHero::KeyCheck(_double _timeDelta)
{
	if (m_pKeyMgr == nullptr)
		return E_FAIL;


	if (m_pKeyMgr->Key_Down(VK_LBUTTON))
	{
		if (nullptr == m_pTransform)
			return E_FAIL;

		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		vector<CTerrain*> route;
		CWorld::Get_Instance()->Get_Route(m_pTransform->Get_Position(), Vector2((float)pt.x, (float)pt.y), route, m_pTransform);

		//해당 루트를 따라가기 위해 필요한 턴수를 계산
		_int iTurnCnt = (_int)route.size() / m_pTransform->Get_Desc().movePerTurn;

		m_pTransform->Go_Route(route, 1.f);

		//플레이어가 움직인만큼 턴 이동
		CTurnMgr::Get_Instance()->MoveTurn(iTurnCnt, _timeDelta);
	}

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
	Safe_Release(m_pKeyMgr);
	CCharacter::Free();
}


