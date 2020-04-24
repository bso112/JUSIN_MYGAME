#pragma once
#include "Module.h"

BEGIN(MyGame)
class CText final: public CModule
{
protected:
	explicit CText(LPDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CText(CText& _module);
	virtual ~CText() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* _pArg);

protected:
	LPDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;

public:
	virtual CModule* Clone(void* _pArg = nullptr);
	virtual void Free() override;

};

END