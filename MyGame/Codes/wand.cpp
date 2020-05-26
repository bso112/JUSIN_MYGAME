#include "stdafx.h"
#include "wand.h"


USING(MyGame)
CWand::CWand(PDIRECT3DDEVICE9 _pGrahic_Device)
	:CWeapon(_pGrahic_Device)
{
}

CWand::CWand(CWand & _rhs)
	: CWeapon(_rhs)
{
}

HRESULT CWand::Initialize(void * _param)
{
	CWeapon::Initialize(_param);
	m_vecActions.push_back(AC_ZAP);

	if (FAILED(Set_Module(L"wand", SCENE_STAGE, (CModule**)&m_pTexture)))
		return E_FAIL;

	m_pTextureTag = L"wand";

	return S_OK;
}

CWand * CWand::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath)
{
	CWand* pInstance = new CWand(_pGrahic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
	{
		MSG_BOX("Fail to create wand");
		Safe_Release(pInstance);

	}
	return pInstance;
}



CGameObject * CWand::Clone(void * _param)
{
	CWand* pInstance = new CWand(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create wand");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CWand::Free()
{
	CWeapon::Free();
}

