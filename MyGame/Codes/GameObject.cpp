#include "stdafx.h"
#include "..\Headers\GameObject.h"
#include "Renderer.h"

USING(MyGame)
void CGameObject::Free()
{
	Safe_Release(m_pRenderer);
	Safe_Release(m_pGraphic_Device);
}

CGameObject::CGameObject(PDIRECT3DDEVICE9 _pGrahic_Device)
	:m_pGraphic_Device(_pGrahic_Device), m_pRenderer(CRenderer::Get_Instance())
{
	Safe_AddRef(m_pRenderer);
	Safe_AddRef(m_pGraphic_Device);


};



CGameObject::CGameObject(CGameObject & _rhs)
	:m_pGraphic_Device(_rhs.m_pGraphic_Device), m_pRenderer(CRenderer::Get_Instance())
{
	Safe_AddRef(m_pGraphic_Device);
	Safe_AddRef(m_pRenderer);
}

HRESULT CGameObject::Initialize_Prototype(_tchar* _pFilePath)
{
	return S_OK;
}

HRESULT CGameObject::Initalize(void * _param)
{
	return S_OK;
}

_int CGameObject::Update(_double _timeDelta)
{
	return 0;
}

_int CGameObject::LateUpate(_double _timeDelta)
{	

	return 0;
}

HRESULT CGameObject::Render()
{	

	return S_OK;
}
