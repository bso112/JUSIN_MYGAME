#include "stdafx.h"
#include "..\Headers\Light.h"
#include "Transform.h"
#include "VIBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "TargetMgr.h"
USING(MyGame)

CLight::CLight(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CGameObject(_pGraphic_Device)
{
}

CLight::CLight(CGameObject & _rhs)
	:CGameObject(_rhs)
{
}

HRESULT CLight::Initialize_Prototype(_tchar * _pFilePath)
{
	return S_OK;
}

HRESULT CLight::Initialize(void * _pArg)
{
	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform)))
		return E_FAIL;
	if (FAILED(Set_Module(L"Shader", SCENE_STATIC, (CModule**)&m_pShader)))
		return E_FAIL;
	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;
	if (FAILED(Set_Module(L"light", SCENE_STAGE, (CModule**)&m_pTexture)))
		return E_FAIL;
	m_pTransform->Set_Position(Vector4(0.f, 0.f, 0.f, 1.f));
	m_pTransform->Set_Size(Vector2(100.f, 100.f));
	return S_OK;
}

_int CLight::Update(_double _timeDelta)
{
	return 0;
}

_int CLight::LateUpate(_double _timeDelta)
{
//	if (!m_bActive)
//		return 0;
//
//	if (nullptr == m_pRenderer)
//		return -1;
//
//	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_PRIOR)))
//		return -1;
//
	return 0;
}

HRESULT CLight::Render()
{
	/*if (!m_bActive)
		return 0;

	if (nullptr == m_pVIBuffer ||
		nullptr == m_pTransform	||
		nullptr == m_pPipline)
		return E_FAIL;


	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix() * m_pPipline->Get_ViewMatrix())))
		return E_FAIL;

	CTargetMgr* pTargetMgr = CTargetMgr::Get_Instance();
	RETURN_FAIL_IF_NULL(pTargetMgr);
	pTargetMgr->Set_RenderTarget(L"Fog", 1);

	ALPHABLEND;

	if (FAILED(m_pTexture->Set_TextureOnShader(m_pShader, "g_BaseTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pShader->Begin()))
		return E_FAIL;
	if (FAILED(m_pShader->Begin_Pass(9)))
		return E_FAIL;


	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;


	if (FAILED(m_pShader->End_Pass()))
		return E_FAIL;

	if (FAILED(m_pShader->End()))
		return E_FAIL;


	ALPHABLEND_END;

	pTargetMgr->Release_RenderTarget(L"Fog");*/
	
	return S_OK;
}

HRESULT CLight::Set_Parent(CTransform * _pTransform)
{
	m_pTransform->Set_Parent(_pTransform);
	_pTransform->Set_Position(Vector4(0.f, 0.f, 0.f, 1.f));
	return S_OK;
}


CLight * CLight::Create(PDIRECT3DDEVICE9 _pGraphic_Device, _tchar * _pFilePath)
{
	CLight* pInstance = new CLight(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
	{
		MSG_BOX("Fail to create CLight");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CLight::Clone(void * _param)
{
	CLight* pInstance = new CLight(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create CLight");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CLight::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pShader);
	Safe_Release(m_pVIBuffer);
	CGameObject::Free();
}
