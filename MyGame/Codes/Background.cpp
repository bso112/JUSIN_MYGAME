#include "stdafx.h"
#include "..\Headers\Background.h"
#include "VIBuffer.h"

USING(MyGame)


CBackground::CBackground(CBackground & _rhs)
	:CGameObject(_rhs)
{

}

HRESULT CBackground::Initialize_Prototype(_tchar* _pFilePath)
{
	return S_OK;
}

HRESULT CBackground::Initialize(void * _param)
{
	if (FAILED(Initalize_Module()))
		return E_FAIL;

	m_pTransform->Set_Position(Vector4(300.f, 300.f, 0.f, 1.f));
	
	return S_OK;
}

_int CBackground::Update(_double _timeDelta)
{
	return _int();
}

_int CBackground::LateUpate(_double _timeDelta)
{
	if (nullptr == m_pRenderer)
		return -1;

	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_PRIOR)))
		return -1;

	return 0;
}

HRESULT CBackground::Render()
{
	if (nullptr == m_pVIBuffer	||
		nullptr == m_pTextrue	||
		nullptr == m_pTransform)
		return E_FAIL;

	if (FAILED(m_pTextrue->Set_Textrue(0)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix())))
		return E_FAIL;

	if(FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

	return S_OK;
}

CGameObject* CBackground::Clone(void* _param)
{
	CBackground* pInstance = new CBackground(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create Background");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CBackground * CBackground::Create(PDIRECT3DDEVICE9 _pGraphic_Device, _tchar* _pFilePath)
{
	CBackground* pInstance = new CBackground(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
	{
		MSG_BOX("Fail to create Background");
		Safe_Release(pInstance);

	}
	return pInstance;
}


void CBackground::Free()
{
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTextrue);
	Safe_Release(m_pTransform);

	CGameObject::Free();
}

HRESULT CBackground::Initalize_Module()
{
	if (FAILED(Set_Module(MODULE_VIBUFFER, SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;

	if (FAILED(Set_Module(MODULE_DEFUALT_TEXTURE, SCENE_STATIC, (CModule**)&m_pTextrue)))
		return E_FAIL;

	if (FAILED(Set_Module(MODULE_TRANSFORM, SCENE_STATIC, (CModule**)&m_pTransform)))
		return E_FAIL;

	return S_OK;
}

