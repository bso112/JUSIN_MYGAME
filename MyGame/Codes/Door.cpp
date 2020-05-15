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


_int CDoor::Interact(CGameObject* _pOther)
{
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
		if (pHero->Has_Key(TIER_RARE))
		{
			UnLock();
			pHero->PlayAnimation(L"use");
		}

	}
	return 0;
}

void CDoor::OnCollisionEnterTerrain(CGameObject * _pOther)
{

}

HRESULT CDoor::OnMoveFrame()
{
	//�������� �ٲ𶧸��� ��������� ������ ���·� �����Ѵ�.
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
	//�ε�ɶ� ���� ���¿����� ��������� �����Ѵ�.
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






