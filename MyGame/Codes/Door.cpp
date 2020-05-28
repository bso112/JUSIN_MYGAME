#include "stdafx.h"
#include "..\Headers\Door.h"
#include "Hero.h"
#include "DialogMgr.h"

USING(MyGame)
CDoor::CDoor(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CTerrain(_pGraphic_Device)
{

}

CDoor::CDoor(CDoor & _rhs)
	:CTerrain(_rhs)
{
}


_int CDoor::Interact(CGameObject* _pOther)
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pTransform)
		return -1;

	CHero* pHero = dynamic_cast<CHero*>(_pOther);
	if (nullptr == pHero)
		return -1;

	CTransform* pTransform = dynamic_cast<CTransform*>(pHero->Get_Module(L"Transform"));
	if (nullptr == pTransform)
		return -1;

	if ((pTransform->Get_Position() - m_pTransform->Get_Position()).magnitude() > 40)
		return -1;

	

	if (m_bLocked)
	{
		if (pHero->Has_Key())
		{
			UnLock();
			pHero->PlayAnimation(L"use");
		}
		else
			CDialogMgr::Get_Instance()->Log_Main(new wstring(L"알맞은 열쇠가 없습니다."));

	}
	return 0;
}

void CDoor::OnCollisionEnterTerrain(CGameObject * _pOther)
{

}

HRESULT CDoor::OnMoveFrame()
{
	//프레임이 바뀔때마다 멤버변수를 적합한 상태로 셋팅한다.
	switch (m_iCurFrame)
	{
	case STATE_UNLOCKED:
		UnLock();
		break;
	case STATE_LOCKED:
		Lock();
		break;
	default:
		break;
	}
	return S_OK;
}

HRESULT CDoor::OnLoadData()
{
	//로드될때 받은 상태에따라 멤버변수를 셋팅한다.
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

CDoor * CDoor::Create(PDIRECT3DDEVICE9 _pGraphic_Device, TERRAIN _tData, const _tchar* _pTextureTag, SCENEID _eTextureScene, _tchar* _pFilePath)
{
	CDoor* pInstance = new CDoor(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_tData, _pTextureTag, _eTextureScene, _pTextureTag, _pFilePath)))
	{
		MSG_BOX("Fail to create CDoor");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CDoor * CDoor::Clone(void * _param)
{
	CDoor* pInstance = new CDoor(*this);
	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail to clone CDoor");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CDoor::Free()
{
	CTerrain::Free();
}






