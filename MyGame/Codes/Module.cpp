#include "stdafx.h"
#include "..\Headers\Module.h"

USING(MyGame)

CModule::CModule(LPDIRECT3DDEVICE9 _pGraphic_Device)
	:m_pGraphic_Device(_pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}
CModule::CModule(CModule & _module)
	:m_pGraphic_Device(_module.m_pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}
HRESULT CModule::Initialize_Prototype()
{
	return S_OK;
}
HRESULT CModule::Initialize(void * _pArg)
{
	return S_OK;
}
void CModule::Free()
{
	Safe_Release(m_pGraphic_Device);
}
