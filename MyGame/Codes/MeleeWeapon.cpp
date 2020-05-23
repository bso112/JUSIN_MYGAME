#include "stdafx.h"
#include "..\Headers\MeleeWeapon.h"


USING(MyGame)
CMeleeWeapon::CMeleeWeapon(PDIRECT3DDEVICE9 _pGrahic_Device)
	:CWeapon(_pGrahic_Device)
{
}

CMeleeWeapon::CMeleeWeapon(CMeleeWeapon & _rhs)
	:CWeapon(_rhs)
{
}

HRESULT CMeleeWeapon::Initialize(void * _param)
{
	CWeapon::Initialize(_param);

	if (FAILED(Set_Module(L"meleeWeapon", SCENE_STAGE, (CModule**)&m_pTexture)))
		return E_FAIL;


	return S_OK;
}

CMeleeWeapon * CMeleeWeapon::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath)
{
	CMeleeWeapon* pInstance = new CMeleeWeapon(_pGrahic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
	{
		MSG_BOX("Fail to create CMeleeWeapon");
		Safe_Release(pInstance);

	}
	return pInstance;
}



CGameObject * CMeleeWeapon::Clone(void * _param)
{
	CMeleeWeapon* pInstance = new CMeleeWeapon(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create CMeleeWeapon");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CMeleeWeapon::Free()
{
	CWeapon::Free();
}

