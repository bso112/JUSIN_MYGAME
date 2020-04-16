#include "stdafx.h"
#include "..\Headers\Background.h"


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
	CGameObject::Free();
}
