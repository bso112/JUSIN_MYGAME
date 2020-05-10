#pragma once
#include "Base.h"

BEGIN(MyGame)
class CModule abstract : public CBase
{
protected:
	explicit CModule(LPDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CModule(CModule& _module);
	virtual ~CModule() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* _pArg);
	
protected:
	LPDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;

public:
	virtual CModule* Clone(void* _pArg = nullptr) = 0;
	virtual void Free() override;

};
END
