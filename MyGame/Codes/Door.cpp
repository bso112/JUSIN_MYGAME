#include "stdafx.h"
#include "..\Headers\Door.h"
#include "Hero.h"

USING(MyGame)
CDoor::CDoor(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CTerrain(_pGraphic_Device)
{

}

CDoor::CDoor(CDoor & _rhs)
	:CTerrain(_rhs)
{
}

HRESULT CDoor::Interact(CGameObject* _pInteractor)
{
	CHero* pHero = dynamic_cast<CHero*>(_pInteractor);
	if (nullptr == pHero)
		return E_FAIL;

	if (m_bLocked)
	{
		if (pHero->Has_Key(TIER_RARE))
		{
			UnLock();
		}

	}
	return S_OK;
}

HRESULT CDoor::OnMoveFrame()
{
	switch (m_iCurFrame)
	{
	case STATE_UNLOCKED:
		UnLock();
	case STATE_LOCKED:
		Lock();
	default:
		break;
	}
	return S_OK;
}

HRESULT CDoor::OnLoadData()
{
	OnMoveFrame();
	return S_OK;
}

void CDoor::UnLock()
{
	m_bLocked = false; 
	m_tInfo.m_bMovable = true;
	m_iCurFrame = 0;
	m_eState = STATE::STATE_UNLOCKED;
}

void CDoor::Lock()
{
	m_bLocked = true;
	m_tInfo.m_bMovable = false;
	m_iCurFrame = 1;
	m_eState = STATE::STATE_LOCKED;
}




