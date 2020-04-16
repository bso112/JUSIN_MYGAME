#include "stdafx.h"
#include "..\Headers\VIBuffer.h"

USING(MyGame)


CVIBuffer * CVIBuffer::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CVIBuffer* pInstance = new CVIBuffer(_pGraphic_Device);
	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail to create VIBuffer");
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT CVIBuffer::Initialize()
{
	if (m_pGraphic_Device == nullptr)
		return E_FAIL;

	m_pGraphic_Device->CreateVertexBuffer(sizeof(VTXTEX) * 6, 0, D3DFVF_XYZRHW | D3DFVF_TEX1, D3DPOOL_MANAGED, &m_pVBuffer, nullptr);

	return S_OK;
}

void CVIBuffer::Free()
{
	CModule::Free();
}
