#pragma once
#include "Equipment.h"
BEGIN(MyGame)
class CArmor final : public CEquipment
{
protected:
	explicit CArmor(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CArmor(CArmor& _rhs);
	virtual ~CArmor() = default;


public:
	virtual HRESULT Initialize(void * _param = nullptr);

public:
	static CArmor * Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr);
	CGameObject * Clone(void * _param = nullptr);
	virtual void Free() override;
};

END