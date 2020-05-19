#include "stdafx.h"
#include "Particle.h"
#include "VIBuffer.h"
#include "Texture.h"
#include "Transform.h"
#include "Renderer.h"
#include "Shader.h"


USING(MyGame)


CParticle::CParticle(CParticle & _rhs)
	:CGameObject(_rhs)
{
	m_bActive = true;
	ZeroMemory(&m_tDesc, sizeof(STATEDESC));
}




HRESULT CParticle::Initialize_Prototype()
{
	return S_OK;

}


HRESULT CParticle::Initialize(void * _pArg)
{
	if (nullptr != _pArg)
		memcpy(&m_tDesc, _pArg, sizeof(STATEDESC));

	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;

	if (FAILED(Set_Module(m_tDesc.m_pTextureTag, m_tDesc.m_eTextureSceneID, (CModule**)&m_pTextrue)))
		return E_FAIL;

	CTransform::STATEDESC transformDesc;
	transformDesc.speedPerSec = m_tDesc.m_fSpeed;

	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform", &transformDesc)))
		return E_FAIL;

	if (FAILED(Set_Module(L"Shader", SCENE_STATIC, (CModule**)&m_pShader)))
		return E_FAIL;

	m_pTransform->Set_Position(m_tDesc.m_tBaseDesc.vPos);
	m_pTransform->Set_Size(m_tDesc.m_tBaseDesc.vSize);


	return S_OK;
}

_int CParticle::Update(_double _timeDelta)
{
	if (m_bDead)
		return -1;

	if (!m_bActive)
		return 0;

	m_pTransform->Update_Normal(_timeDelta);

	return 0;
}

_int CParticle::LateUpate(_double _timeDelta)
{
	if (m_bDead)
		return -1;


	if (!m_bActive)
		return 0;

	if (nullptr == m_pRenderer)
		return -1;

	m_pTransform->Update_Transform();

	//여러번 호출되지 않음
	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_UI)))
		return -1;

	return 0;
}

HRESULT CParticle::Render()
{


	if (!m_bActive)
		return 0;

	if (nullptr == m_pVIBuffer ||
		nullptr == m_pTextrue ||
		nullptr == m_pTransform)
		return E_FAIL;


	ALPHABLEND;

	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix() * m_pPipline->Get_ViewMatrix())))
		return E_FAIL;

	if (FAILED(m_pTextrue->Set_TextureOnShader(m_pShader, "g_BaseTexture", m_tDesc.m_iTextureID - 1)))
		return E_FAIL;
	if (FAILED(m_pShader->Begin()))
		return E_FAIL;
	if (FAILED(m_pShader->Begin_Pass(0)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

	m_tFont.m_tRC = m_pTransform->Get_RECT();
	g_pFont->DrawText(NULL, m_tFont.m_pText, -1, &m_tFont.m_tRC, m_tFont.m_dwFormat, m_tFont.m_Color);
	//하위클래스의 렌더
	OnRender();

	if (FAILED(m_pShader->End_Pass()))
		return E_FAIL;
	if (FAILED(m_pShader->End()))
		return E_FAIL;

	ALPHABLEND_END;



	return S_OK;
}

HRESULT CParticle::OnRender()
{
	return S_OK;
}


void CParticle::Replace_Texture(const _tchar * pTextureTag, _int _iTextureID, SCENEID _eTextureSceneID)
{
	if (nullptr == pTextureTag)
		return;

	Safe_Release(m_pTextrue);
	m_tDesc.m_pTextureTag = pTextureTag;
	m_tDesc.m_eTextureSceneID = _eTextureSceneID;
	m_tDesc.m_iTextureID = _iTextureID;
	Set_Module(pTextureTag, _eTextureSceneID, (CModule**)&m_pTextrue);
}


CParticle * CParticle::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CParticle* pInstance = new CParticle(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CParicle");
		Safe_Release(pInstance);

	}
	return pInstance;
}



CGameObject* CParticle::Clone(void* _param)
{
	CParticle* pInstance = new CParticle(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create CParicle");
		Safe_Release(pInstance);

	}

	return pInstance;
}

void CParticle::Free()
{
	Safe_Release(m_pShader);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTextrue);
	Safe_Release(m_pTransform);

	CGameObject::Free();
}

