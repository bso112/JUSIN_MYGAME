#pragma once
#include "Weapon.h"
BEGIN(MyGame)
class CMeleeWeapon final : public CWeapon
{
protected:
	explicit CMeleeWeapon(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CMeleeWeapon(CMeleeWeapon& _rhs);
	virtual ~CMeleeWeapon() = default;


public:
	virtual HRESULT Initialize(void * _param = nullptr);

public:
	static CMeleeWeapon * Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr);
	CGameObject * Clone(void * _param = nullptr);
	virtual void Free() override;
};

END