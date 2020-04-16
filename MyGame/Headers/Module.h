#pragma once
#include "Base.h"

BEGIN(MyGame)
class CModule : public CBase
{
protected:
	explicit CModule(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CModule() = default;

public:
	virtual HRESULT Initialize();
protected:
	LPDIRECT3DDEVICE9 m_pGraphic_Device;

public:
	virtual void Free() override;

};
END
