#include "stdafx.h"
#include "..\Headers\Fog.h"
#include "ObjMgr.h"
#include "Transform.h"
#include "VIBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "TargetMgr.h"

USING(MyGame)

CFog::CFog(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CGameObject(_pGraphic_Device)
{
}

CFog::CFog(CFog & _rhs)
	:CGameObject(_rhs)
{
}

HRESULT CFog::Initialize(void * _pArg)
{
	if(FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform)))
		return E_FAIL;
	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;
	if (FAILED(Set_Module(L"fog", SCENE_STATIC, (CModule**)&m_pTexture)))
		return E_FAIL;
	if (FAILED(Set_Module(L"Shader", SCENE_STATIC, (CModule**)&m_pShader)))
		return E_FAIL;


	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	RETURN_FAIL_IF_NULL(pObjMgr);
	CGameObject* pPalyer = pObjMgr->Get_Player(SCENE_STAGE);
	RETURN_FAIL_IF_NULL(pPalyer);
	m_pHeroTransform = (CTransform*)pPalyer->Get_Module(L"Transform");
	RETURN_FAIL_IF_NULL(m_pHeroTransform);
	Safe_AddRef(m_pHeroTransform);

	m_pTransform->Set_Size(Vector2(30.f, 30.f));

	return S_OK;
}

_int CFog::Update(_double _timeDelta)
{
	if (!m_bActive)
		return 0;


	if (nullptr == m_pTransform ||
		nullptr == m_pHeroTransform)
		return -1;

	m_pTransform->Set_Position(m_pHeroTransform->Get_Position());

	return 0;
}

_int CFog::LateUpate(_double _timeDelta)
{
	m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_FOG);
	return 0;
}

HRESULT CFog::Initialize_Prototype(_tchar * _pFilePath)
{
	return S_OK;
}

HRESULT CFog::Render()
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pVIBuffer ||
		nullptr == m_pTransform	||
		nullptr == m_pPipline)
		return E_FAIL;


	CTargetMgr* pTargetMgr =  CTargetMgr::Get_Instance();
	RETURN_FAIL_IF_NULL(pTargetMgr);
	Safe_AddRef(pTargetMgr);

	pTargetMgr->Set_RenderTarget(L"fog", 2);

	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix() * m_pPipline->Get_ViewMatrix())))
		return E_FAIL;

	ALPHABLEND;

	if (FAILED(m_pTexture->Set_TextureOnShader(m_pShader, "g_BaseTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pShader->Begin()))
		return E_FAIL;
	if (FAILED(m_pShader->Begin_Pass(0)))
		return E_FAIL;


	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;



	if (FAILED(m_pShader->End_Pass()))
		return E_FAIL;

	if (FAILED(m_pShader->End()))
		return E_FAIL;

	ALPHABLEND_END;

	pTargetMgr->Release_RenderTarget(L"fog");

	Safe_Release(pTargetMgr);

	return S_OK;
}

CFog * CFog::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CFog* pInstance = new CFog(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CFog");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CFog::Clone(void * _pArg)
{
	CFog* pInstance = new CFog(*this);
	if (FAILED(pInstance->Initialize(_pArg)))
	{
		MSG_BOX("Fail to clone CFog");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CFog::Free()
{
	Safe_Release(m_pHeroTransform);
	Safe_Release(m_pShader);
	Safe_Release(m_pTexture);
	Safe_Release(m_pTransform);
	Safe_Release(m_pVIBuffer);

	CGameObject::Free();

}
