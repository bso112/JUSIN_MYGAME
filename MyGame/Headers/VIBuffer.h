#pragma once

#include "Module.h"

BEGIN(MyGame)
class CVIBuffer final : public CModule
{
protected:
	explicit CVIBuffer(PDIRECT3DDEVICE9 _pGraphic_Device) : CModule(_pGraphic_Device) {};
	explicit CVIBuffer(CVIBuffer& _rhs);
	virtual ~CVIBuffer() = default;

private:
	PDIRECT3DVERTEXBUFFER9 m_pVBuffer = nullptr;
public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* _pArg);
	
public:
	HRESULT	Render();
public:
	static CVIBuffer* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CModule * Clone(void * _pArg = nullptr) override;
	virtual void Free();



};
END
