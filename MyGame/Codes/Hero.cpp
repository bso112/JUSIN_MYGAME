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


