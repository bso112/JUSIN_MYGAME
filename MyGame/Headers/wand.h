#pragma once
#include "Weapon.h"
BEGIN(MyGame)
class CWand final : public CWeapon
{
protected:
	explicit CWand(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CWand(CWand& _rhs);
	virtual ~CWand() = default;


public:
	virtual HRESULT Initialize(void * _param = nullptr);

public:
	static CWand * Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr);
	CGameObject * Clone(void * _param = nullptr);
	virtual void Free() override;
};

END