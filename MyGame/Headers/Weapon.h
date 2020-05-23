#pragma once
#include "Equipment.h"
BEGIN(MyGame)
class CWeapon : public CEquipment
{
protected:
	explicit CWeapon(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CWeapon(CWeapon& _rhs);
	virtual ~CWeapon() = default;
};

END