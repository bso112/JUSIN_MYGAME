#include "stdafx.h"
#include "..\Headers\VIBuffer.h"

USING(MyGame)


//��ü�� �����ϰ� ���� ���빰�� ��������.
CVIBuffer::CVIBuffer(CVIBuffer& _rhs)
	:CModule(_rhs),
	m_pVBuffer(_rhs.m_pVBuffer),
	m_pIBuffer(_rhs.m_pIBuffer)

{
	Safe_AddRef(m_pVBuffer);
	Safe_AddRef(m_pIBuffer);
	memcpy(&m_vBasePos, _rhs.m_vBasePos, sizeof(m_vBasePos));
}

HRESULT CVIBuffer::Render()
{
	if (nullptr == m_pGraphic_Device	||
		nullptr == m_pVBuffer			||
		nullptr == m_pIBuffer)
		return E_FAIL;

	m_pGraphic_Device->SetStreamSource(0, m_pVBuffer, 0, sizeof(VTXTEX));
	m_pGraphic_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
	m_pGraphic_Device->SetIndices(m_pIBuffer);
	m_pGraphic_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

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


HRESULT CVIBuffer::Set_Transform(_matrix _matrix)
{
	if (nullptr == m_pVBuffer)
		return E_FAIL;

	VTXTEX* pVertices = nullptr;
	//�ٸ� �����尡 �������� ���ϵ��� ���� �ɰ�, ���� �ɸ� ������ ������ �� �ִ� �����͸� ���ڷ� �Ѱ���
	m_pVBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec4Transform(&pVertices[i].vPosition, &m_vBasePos[i], &_matrix);

	}

	m_pVBuffer->Unlock();
	return S_OK;

}

HRESULT CVIBuffer::Initialize_Prototype()
{
	if (m_pGraphic_Device == nullptr)
		return E_FAIL;

	//���ؽ� ���۸� ����
	if (FAILED(m_pGraphic_Device->CreateVertexBuffer(sizeof(VTXTEX) * 4, 0, D3DFVF_XYZRHW | D3DFVF_TEX1, D3DPOOL_MANAGED, &m_pVBuffer, nullptr)))
		return E_FAIL;



	VTXTEX* pVertices = nullptr;
	//�ٸ� �����尡 �������� ���ϵ��� ���� �ɰ�, ���� �ɸ� ������ ������ �� �ִ� �����͸� ���ڷ� �Ѱ���
	m_pVBuffer->Lock(0, 0, (void**)&pVertices, 0);

	//���ؽ� ���ۿ� �ִ� ���ؽ� �� ����
	m_vBasePos[0] = pVertices[0].vPosition = D3DXVECTOR4(-0.5f, -0.5f, 0.f, 1.f);
	pVertices[0].vTexUV = D3DXVECTOR2(0.f, 0.f);

	m_vBasePos[1] = pVertices[1].vPosition = D3DXVECTOR4(0.5f, -0.5f, 0.f, 1.f);
	pVertices[1].vTexUV = D3DXVECTOR2(1.f, 0.f);

	m_vBasePos[2] = pVertices[2].vPosition = D3DXVECTOR4(0.5f, 0.5f, 0.f, 1.f);
	pVertices[2].vTexUV = D3DXVECTOR2(1.f, 1.f);

	m_vBasePos[3] = pVertices[3].vPosition = D3DXVECTOR4(-0.5f , 0.5f, 0.f, 1.f);
	pVertices[3].vTexUV = D3DXVECTOR2(0.f, 1.f);

	m_pVBuffer->Unlock();

	//�ε��� ���۸� ����
	if (FAILED(m_pGraphic_Device->CreateIndexBuffer(sizeof(_ushort) * 6, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIBuffer, nullptr)))
		return E_FAIL;

	//��� �ε������ۿ� �����ϱ� ���� ������
	_ushort* pIndices = nullptr;
	m_pIBuffer->Lock(0, 0, (void**)&pIndices, 0);

	pIndices[0] = 0;
	pIndices[1] = 1;
	pIndices[2] = 2;
	pIndices[3] = 0;
	pIndices[4] = 2;
	pIndices[5] = 3;

	m_pIBuffer->Unlock();

	return S_OK;
}

HRESULT CVIBuffer::Initialize(void * _pArg)
{
	return S_OK;
}

void CVIBuffer::Free()
{
	Safe_Release(m_pVBuffer);
	Safe_Release(m_pIBuffer);
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
