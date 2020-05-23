#include "stdafx.h"
#include "..\Headers\Ring.h"


USING(MyGame)
CRing::CRing(PDIRECT3DDEVICE9 _pGrahic_Device)
	:CEquipment(_pGrahic_Device)
{
}

CRing::CRing(CRing & _rhs)
	: CEquipment(_rhs)
{
}

HRESULT CRing::Initialize(void * _param)
{
	CEquipment::Initialize(_param);

	if (FAILED(Set_Module(L"ring", SCENE_STAGE, (CModule**)&m_pTexture)))
		return E_FAIL;
}

CRing * CRing::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath)
{
	CRing* pInstance = new CRing(_pGrahic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
	{
		MSG_BOX("Fail to create CRing");
		Safe_Release(pInstance);

	}
	return pInstance;
}



CGameObject * CRing::Clone(void * _param)
{
	CRing* pInstance = new CRing(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create CRing");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CRing::Free()
{
	CEquipment::Free();
}

