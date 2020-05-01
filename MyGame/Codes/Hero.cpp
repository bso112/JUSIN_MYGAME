#include "stdafx.h"
#include "..\Headers\Hero.h"
#include "KeyMgr.h"
#include "World.h"
#include "Transform.h"
USING(MyGame)



CHero::CHero(PDIRECT3DDEVICE9 _pGraphic_Device)
	: CCharacter(_pGraphic_Device), m_pKeyMgr(CKeyMgr::Get_Instance())
{
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

		//CWorld::Get_Instance()->Get_TerrainPos(pt, m_vDst);
		//m_pTransform->MoveToDst_Auto(m_vDst, 1.f);
		vector<Vector3> route;
		CWorld::Get_Instance()->Get_Route(m_pTransform->Get_Position(), pt, route);
		m_pTransform->Go_Route(route, 1.f);
	}

	return S_OK;
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


