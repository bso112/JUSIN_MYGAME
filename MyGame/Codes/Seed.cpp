#include "stdafx.h"
#include "..\Headers\Seed.h"

USING(MyGame)
CSeed::CSeed(PDIRECT3DDEVICE9 _pGrahic_Device)
	:CItem(_pGrahic_Device)
{
}

CSeed::CSeed(CSeed & _rhs)
	:CItem(_rhs)
{
}

HRESULT CSeed::Initialize(void * _param)
{
	CItem::Initialize();
	

	Set_Module(L"seed", SCENE_STAGE, (CModule**)&m_pTexture);
	m_pTextureTag = L"seed";


	return S_OK;
}

void CSeed::OnThrow()
{
	//������ ���Ѵ�
	++m_iTextureID;
	//�ؽ����� �ѵ��� �Ѿ�� �ʰ�
	if (m_iTextureID >= m_pTexture->Get_TextureSize())
		m_iTextureID = m_pTexture->Get_TextureSize() - 1;
	
	m_bFlower = true;
}

HRESULT CSeed::Render()
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pTexture ||
		nullptr == m_pVIBuffer ||
		nullptr == m_pTransform ||
		nullptr == m_pPipline)
		return E_FAIL;

	_matrix matrix;

	if (m_bDrop)
		matrix = m_pTransform->Get_Matrix() * m_pPipline->Get_ViewMatrix();
	//���Կ� ���������� ī�޶� ��Ʈ���� ����ȹ��� 
	else
	{
		matrix = m_pTransform->Get_Matrix();
	}

	ALPHABLEND;

	if (FAILED(m_pVIBuffer->Set_Transform(matrix)))
		return E_FAIL;

	//�ؽ���ID�� 1���� ����
	if (FAILED(m_pTexture->Set_Texture(m_iTextureID - 1)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;


	ALPHABLEND_END;

#ifdef MYDEBUG

	m_pTransform->Render_Collider();
#endif // MYDEBUG


	return S_OK;
}

Vector3 CSeed::Get_OriginalSize()
{
	return m_vOriginalSize;
}



void CSeed::Free()
{
	CItem::Free();
}
