#include "stdafx.h"
#include "..\Headers\Armor.h"


USING(MyGame)
CArmor::CArmor(PDIRECT3DDEVICE9 _pGrahic_Device)
	:CEquipment(_pGrahic_Device)
{
}

CArmor::CArmor(CArmor & _rhs)
	: CEquipment(_rhs)
{
}

HRESULT CArmor::Initialize(void * _param)
{
	CEquipment::Initialize(_param);

	if (FAILED(Set_Module(L"cloth", SCENE_STAGE, (CModule**)&m_pTexture)))
		return E_FAIL;

	m_pTextureTag = L"cloth";
	m_eBodyPart = BODY_TORSO;
	return S_OK;
}

CArmor * CArmor::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath)
{
	CArmor* pInstance = new CArmor(_pGrahic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
	{
		MSG_BOX("Fail to create CArmor");
		Safe_Release(pInstance);

	}
	return pInstance;
}



CGameObject * CArmor::Clone(void * _param)
{
	CArmor* pInstance = new CArmor(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create CArmor");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CArmor::Free()
{
	CEquipment::Free();
}

