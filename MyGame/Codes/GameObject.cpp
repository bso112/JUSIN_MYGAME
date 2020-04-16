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


void CGameObject::Update_Rect()
{
	m_tRect.left = (LONG)m_tInfo.vPos.x - (m_tInfo.iCX >>1);
	m_tRect.right = (LONG)m_tInfo.vPos.x + (m_tInfo.iCX >> 1);
	m_tRect.top = (LONG)m_tInfo.vPos.y- (m_tInfo.iCY >> 1);
	m_tRect.bottom = (LONG)m_tInfo.vPos.y + (m_tInfo.iCY >> 1);

}

HRESULT CGameObject::Initialize_Prototype(_tchar * _pFilePath)
{
	return E_NOTIMPL;
}

HRESULT CGameObject::Initialize(void * _param)
{
	return E_NOTIMPL;
}

_int CGameObject::Update(_double _timeDelta)
{
	return _int();
}

_int CGameObject::LateUpate(_double _timeDelta)
{
	return _int();
}

HRESULT CGameObject::Render()
{
	return E_NOTIMPL;
}

HRESULT CGameObject::Render(HDC _DC)
{
	return E_NOTIMPL;
}
