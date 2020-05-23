#include "stdafx.h"
#include "..\Headers\Equipment.h"


USING(MyGame)

CEquipment::CEquipment(PDIRECT3DDEVICE9 _pGrahic_Device)
	: CItem(_pGrahic_Device) 
{
};

CEquipment::CEquipment(CEquipment & _rhs)
	:CItem(_rhs)
{
}

HRESULT CEquipment::Initialize(void * _param)
{
	CItem::Initialize(_param);
	m_vecActions.push_back(AC_EQUIP);
	
	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform)))
		return E_FAIL;
	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;

	if (nullptr != _param)
		memcpy(&m_tDesc, _param, sizeof(STATEDESC));

	m_pTransform->Set_Position(m_tDesc.m_tBaseDesc.vPos);
	m_pTransform->Set_Size(m_tDesc.m_tBaseDesc.vSize);
	m_pTransform->Set_ColliderSize(m_tDesc.m_tBaseDesc.vSize);

	m_pDescription = m_tDesc.m_pDescription;
	m_iTextureID = m_tDesc.m_iTextureID;
	m_pItemName = m_tDesc.m_pItemName;


	return S_OK;
}


Vector3 CEquipment::Get_OriginalSize()
{
	return m_tDesc.m_tBaseDesc.vSize;
}

void CEquipment::Free()
{
	CItem::Free();
}