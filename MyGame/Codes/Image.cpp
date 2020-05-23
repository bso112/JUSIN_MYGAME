#include "stdafx.h"
#include "Image.h"
#include "VIBuffer.h"
#include "Texture.h"
#include "Transform.h"
#include "Renderer.h"
#include "Shader.h"
#include "Clock.h"
USING(MyGame)


CImage::CImage(CImage & _rhs)
	:CGameObject(_rhs),
	m_pTextureTag(_rhs.m_pTextureTag)
{
	m_bActive = true;
	m_eSceneID = _rhs.m_eSceneID;
}



HRESULT CImage::Initialize_Prototype(const _tchar* _pTextureTag, Vector4 _vPos, Vector2 _vSize, SCENEID _eTextureSceneID)
{

	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;

	m_pTextureTag = _pTextureTag;
	m_eSceneID = _eTextureSceneID;
	if (FAILED(Set_Module(_pTextureTag, _eTextureSceneID, (CModule**)&m_pTextrue)))
		return E_FAIL;

	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(Set_Module(L"Shader", SCENE_STATIC, (CModule**)&m_pShader)))
		return E_FAIL;

	m_pTransform->Set_Position(Vector4(_vPos.x, _vPos.y, 0, 1));
	m_pTransform->Set_Size(Vector4(_vSize.x, _vSize.y));


	return S_OK;
}

HRESULT CImage::Initialize_Prototype(void* _pArg)
{

	STATEDESC desc;
	if (nullptr == _pArg)
		return E_FAIL;

	desc = *((STATEDESC*)_pArg);

	m_pDeadClock = CClock_Delay::Create();
	m_dLifeTime = desc.m_dLifeTime;

	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;

	m_pTextureTag = desc.m_pTextureTag;
	m_eSceneID = desc.m_eTextureSceneID;

	if (FAILED(Set_Module(m_pTextureTag, m_eSceneID, (CModule**)&m_pTextrue)))
		return E_FAIL;

	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform", &CTransform::STATEDESC(desc.m_fSpeed, 100.f))))
		return E_FAIL;

	if (FAILED(Set_Module(L"Shader", SCENE_STATIC, (CModule**)&m_pShader)))
		return E_FAIL;

	m_pTransform->Set_Position(desc.m_tBaseDesc.vPos);
	m_pTransform->Set_Size(Vector4(desc.m_tBaseDesc.vSize));


	return S_OK;
}


HRESULT CImage::Initialize(void * _pArg)
{
	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;

	if (FAILED(Set_Module(m_pTextureTag, m_eSceneID, (CModule**)&m_pTextrue)))
		return E_FAIL;

	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(Set_Module(L"Shader", SCENE_STATIC, (CModule**)&m_pShader)))
		return E_FAIL;

	if (nullptr != _pArg)
	{
		BASEDESC desc = *((BASEDESC*)_pArg);

		m_pTransform->Set_Position(desc.vPos);
		m_pTransform->Set_Size(desc.vSize);
	}


	return S_OK;
}

_int CImage::Update(_double _timeDelta)
{
	if (m_bDead)
		return -1;

	if (!m_bActive)
		return 0;

	//������Ÿ���� �����Ǿ�����
	if (nullptr != m_pDeadClock && m_dLifeTime != FLT_MAX)
	{
		//������Ÿ���� ������ �ױ�
		if (m_pDeadClock->isThreashHoldReached(m_dLifeTime))
			m_bDead = true;
	}

	m_pTransform->Update_Normal(_timeDelta);
	//�̰� ���� ���� �־�������.. �޴����鶧. ���� ���� �־�ߵ�.
	m_pTransform->Update_Transform();

	return 0;
}

_int CImage::LateUpate(_double _timeDelta)
{
	if (m_bDead)
		return -1;


	if (!m_bActive)
		return 0;

	if (nullptr == m_pRenderer)
		return -1;

	m_pTransform->Update_Transform();

	//������ ȣ����� ����
	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_UI)))
		return -1;

	return 0;
}

HRESULT CImage::Render()
{


	if (!m_bActive)
		return 0;

	if (nullptr == m_pVIBuffer ||
		nullptr == m_pTextrue ||
		nullptr == m_pTransform ||
		nullptr == m_pPipline)
		return E_FAIL;


	ALPHABLEND;
	_matrix matrix;
	if (m_bUI)
		matrix = m_pTransform->Get_Matrix();
	else
		matrix = m_pTransform->Get_Matrix() * m_pPipline->Get_ViewMatrix();

	if (FAILED(m_pVIBuffer->Set_Transform(matrix)))
		return E_FAIL;

	if (FAILED(m_pTextrue->Set_TextureOnShader(m_pShader, "g_BaseTexture", m_iTextureID - 1)))
		return E_FAIL;
	if (FAILED(m_pShader->Begin()))
		return E_FAIL;
	if (FAILED(m_pShader->Begin_Pass(0)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

	if (m_bUI)
		m_tFont.m_tRC = m_pTransform->Get_RECT();
	else
		//��Ʈ���� ���� ��ġ�� �����
		m_tFont.m_tRC = m_pTransform->Make_Rect(Vector3(matrix.m[3][0], matrix.m[3][1]), m_pTransform->Get_Size());


	//�ؽ�Ʈ�� _tchar �迭�ϼ���, ������ڿ� �ϼ��� �ִ�. ������ڿ��� �����ȵǾ������� _tchar �迭�� ����ϵ�������.
	const _tchar* szBuff = (m_tFont.m_pText == nullptr) ? m_tFont.m_pTextArr : m_tFont.m_pText;

	//���� ������ ��Ʈ�� ������ �� ��Ʈ�� �׸���.
	if (nullptr != m_tFont.m_pFont)
		m_tFont.m_pFont->DrawText(NULL, szBuff, -1, &m_tFont.m_tRC, m_tFont.m_dwFormat, m_tFont.m_Color);
	else
		g_pFont->DrawText(NULL, szBuff, -1, &m_tFont.m_tRC, m_tFont.m_dwFormat, m_tFont.m_Color);


	//����Ŭ������ ����
	OnRender();


	if (FAILED(m_pShader->End_Pass()))
		return E_FAIL;
	if (FAILED(m_pShader->End()))
		return E_FAIL;

	ALPHABLEND_END;



	return S_OK;
}

HRESULT CImage::OnRender()
{
	return S_OK;
}


void CImage::Replace_Texture(const _tchar * pTextureTag, _int _iTextureID, SCENEID _eTextureSceneID)
{
	if (nullptr == pTextureTag)
		return;

	Replace_Module(m_pTextureTag, pTextureTag, _eTextureSceneID, (CModule**)&m_pTextrue);
	m_iTextureID = _iTextureID;
	m_pTextureTag = pTextureTag;

}

CImage * CImage::Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, const _tchar* _pTextureTag, SCENEID _eTextureSceneID)
{
	CImage* pInstance = new CImage(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pTextureTag, _vPos, _vSize, _eTextureSceneID)))
	{
		MSG_BOX("Fail to create CImage");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CImage * CImage::Create(PDIRECT3DDEVICE9 _pGraphic_Device, void* _desc)
{
	CImage* pInstance = new CImage(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_desc)))
	{
		MSG_BOX("Fail to create CImage");
		Safe_Release(pInstance);

	}
	return pInstance;
}



CGameObject* CImage::Clone(void* _param)
{
	CImage* pInstance = new CImage(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create CImage");
		Safe_Release(pInstance);

	}

	return pInstance;
}

void CImage::Free()
{
	Safe_Release(m_pShader);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTextrue);
	Safe_Release(m_pTransform);
	Safe_Release(m_pDeadClock);

	CGameObject::Free();
}

