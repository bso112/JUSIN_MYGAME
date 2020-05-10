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
	//정점들의 초기 위치(상수)
	Vector4	m_vBasePos[4];
private:
	PDIRECT3DVERTEXBUFFER9	m_pVBuffer = nullptr;
	PDIRECT3DINDEXBUFFER9	m_pIBuffer = nullptr;
public:
	HRESULT Set_Transform(_matrix _matrix);
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
