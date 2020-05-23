#pragma once
#include "Equipment.h"
BEGIN(MyGame)
class CRing final : public CEquipment
{
protected:
	explicit CRing(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CRing(CRing& _rhs);
	virtual ~CRing() = default;


public:
	virtual HRESULT Initialize(void * _param = nullptr);

public:
	static CRing * Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr);
	CGameObject * Clone(void * _param = nullptr);
	virtual void Free() override;
};

END