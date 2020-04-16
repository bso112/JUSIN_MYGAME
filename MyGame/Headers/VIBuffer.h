#pragma once

#include "Module.h"

BEGIN(MyGame)
class CVIBuffer final : public CModule
{
protected:
	explicit CVIBuffer(PDIRECT3DDEVICE9 _pGraphic_Device) : CModule(_pGraphic_Device) {};
	virtual ~CVIBuffer() = default;

private:
	PDIRECT3DVERTEXBUFFER9 m_pVBuffer = nullptr;
public:
	static CVIBuffer* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	HRESULT Initialize();
	virtual void Free();

};
END
