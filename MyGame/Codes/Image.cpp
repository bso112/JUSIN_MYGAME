#include "stdafx.h"
#include "Image.h"
#include "VIBuffer.h"
#include "Texture.h"
#include "Transform.h"
#include "Renderer.h"
#include "Shader.h"

USING(MyGame)


CImage::CImage(CImage & _rhs)
	:CGameObject(_rhs)
{

}



HRESULT CImage::Initialize(_tchar* _pTextureTag, Vector4 _vPos, Vector2 _vSize, SCENEID _eTextureSceneID)
{

	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;

	if (FAILED(Set_Module(_pTextureTag, _eTextureSceneID, (CModule**)&m_pTextrue)))
		return E_FAIL;

	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(Set_Module(L"Shader_Default", SCENE_STATIC, (CModule**)&m_pShader)))
		return E_FAIL;

	m_pTransform->Set_Position(Vector4(_vPos.x, _vPos.y, 0, 1));
	m_pTransform->Set_Size(Vector4(_vSize.x, _vSize.y));



	return S_OK;
}

_int CImage::Update(_double _timeDelta)
{
	m_pTransform->Update();
	return 0;
}

_int CImage::LateUpate(_double _timeDelta)
{
	if (nullptr == m_pRenderer)
		return -1;

	//여러번 호출되지 않음
	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_UI)))
		return -1;

	return 0;
}

HRESULT CImage::Render()
{
	if (nullptr == m_pVIBuffer ||
		nullptr == m_pTextrue ||
		nullptr == m_pTransform)
		return E_FAIL;


	ALPHABLEND;

	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix())))
		return E_FAIL;

	if (FAILED(m_pTextrue->Set_TextureOnShader(m_pShader, "g_BaseTexture", 0)))
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



	return S_OK;
}

CGameObject* CImage::Clone(void* _param)
{

	return nullptr;
}

CImage * CImage::Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID)
{
	CImage* pInstance = new CImage(_pGraphic_Device);
	if (FAILED(pInstance->Initialize(_pTextureTag, _vPos, _vSize, _eTextureSceneID)))
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

	CGameObject::Free();
}

