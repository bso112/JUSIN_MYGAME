#include "stdafx.h"
#include "Weapon.h"

USING(MyGame)

CWeapon::CWeapon(PDIRECT3DDEVICE9 _pGrahic_Device)
	:CEquipment(_pGrahic_Device)
{
}

CWeapon::CWeapon(CWeapon & _rhs)
	:CEquipment(_rhs)
{
}

HRESULT CWeapon::Initialize(void * _param)
{
	CEquipment::Initialize(_param);
	m_eBodyPart = BODY_HAND;
	return S_OK;
}
