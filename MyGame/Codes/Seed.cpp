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
	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform", &CTransform::STATEDESC(300.0, 300.0));
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);

	m_vOriginalSize = Vector2(30.f, 25.f);
	m_pTransform->Set_Size(m_vOriginalSize);
	m_pTransform->Set_ColliderSize(COLLIDER_SIZE);

	return S_OK;
}

void CSeed::OnThrowEnd()
{
	//꽃으로 변한다
	++m_iTextureID;
	//텍스쳐의 한도를 넘어가지 않게
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
	//슬롯에 들어가있을때는 카메라 매트릭스 적용안받음 
	else
	{
		matrix = m_pTransform->Get_Matrix();
	}

	ALPHABLEND;

	if (FAILED(m_pVIBuffer->Set_Transform(matrix)))
		return E_FAIL;

	//텍스쳐ID는 1부터 시작
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
