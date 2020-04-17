#include "stdafx.h"
#include "..\Headers\VIBuffer.h"

USING(MyGame)


CVIBuffer::CVIBuffer(CVIBuffer& _rhs)
	:CModule(_rhs),
	m_pVBuffer(_rhs.m_pVBuffer)
{
	Safe_AddRef(m_pVBuffer);
}

HRESULT CVIBuffer::Render()
{
	if (nullptr == m_pGraphic_Device ||
		nullptr == m_pVBuffer)
		return E_FAIL;

	m_pGraphic_Device->SetStreamSource(0, m_pVBuffer, 0, sizeof(VTXTEX));
	m_pGraphic_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
	m_pGraphic_Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	return S_OK;
}

CVIBuffer * CVIBuffer::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CVIBuffer* pInstance = new CVIBuffer(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create VIBuffer");
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}


HRESULT CVIBuffer::Initialize_Prototype()
{
	if (m_pGraphic_Device == nullptr)
		return E_FAIL;

	//버텍스 버퍼를 생성
	if (FAILED(m_pGraphic_Device->CreateVertexBuffer(sizeof(VTXTEX) * 6, 0, D3DFVF_XYZRHW | D3DFVF_TEX1, D3DPOOL_MANAGED, &m_pVBuffer, nullptr)))
		return E_FAIL;

	VTXTEX* pVertices = nullptr;
	//다른 스레드가 접근하지 못하도록 락을 걸고, 락이 걸린 공간에 접근할 수 있는 포인터를 인자로 넘겨줌
	m_pVBuffer->Lock(0, 0, (void**)&pVertices, 0);

	//버텍스 버퍼에 있는 버텍스 값 셋팅
	pVertices[0].vPosition = D3DXVECTOR4(-0.5f * 100, -0.5f * 100, 0.f, 1.f);
	pVertices[0].vTexUV = D3DXVECTOR2(0.f, 0.f);

	pVertices[1].vPosition = D3DXVECTOR4(0.5f * 100, -0.5f * 100, 0.f, 1.f);
	pVertices[1].vTexUV = D3DXVECTOR2(1.f, 0.f);

	pVertices[2].vPosition = D3DXVECTOR4(0.5f * 100, 0.5f * 100, 0.f, 1.f);
	pVertices[2].vTexUV = D3DXVECTOR2(1.f, 1.f);

	pVertices[3].vPosition = D3DXVECTOR4(-0.5f * 100, -0.5f * 100, 0.f, 1.f);
	pVertices[3].vTexUV = D3DXVECTOR2(0.f, 0.f);

	pVertices[4].vPosition = D3DXVECTOR4(0.5f * 100, 0.5f * 100, 0.f, 1.f);
	pVertices[4].vTexUV = D3DXVECTOR2(1.f, 1.f);

	pVertices[5].vPosition = D3DXVECTOR4(-0.5f * 100, 0.5f * 100, 0.f, 1.f);
	pVertices[5].vTexUV = D3DXVECTOR2(0.f, 1.f);

	m_pVBuffer->Unlock();



	return S_OK;
}

HRESULT CVIBuffer::Initialize(void * _pArg)
{
	return S_OK;
}

void CVIBuffer::Free()
{
	Safe_Release(m_pVBuffer);
	CModule::Free();
}

CModule * CVIBuffer::Clone(void * _pArg)
{
	CVIBuffer* pInstance = new CVIBuffer(*this);

	if (FAILED(pInstance->Initialize(_pArg)))
	{
		MSG_BOX("Fail to clone VIBuffer");
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}
