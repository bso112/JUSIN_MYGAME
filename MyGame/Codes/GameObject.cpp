#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ModuleMgr.h"

USING(MyGame)
void CGameObject::Free()
{
	
	for (auto pair : m_mapModule)
	{
		Safe_Release(pair.second);
	}

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
	Safe_AddRef(m_pRenderer);
	Safe_AddRef(m_pGraphic_Device);
}



HRESULT CGameObject::Initialize_Prototype(_tchar * _pFilePath)
{
	return S_OK;
}

HRESULT CGameObject::Initialize(void * _param)
{
	return S_OK;
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
	return S_OK;
}

HRESULT CGameObject::Set_Module(MODULE _eModuleID,SCENEID _eSceneID, CModule** _ppModule)
{
	if (nullptr != Get_Module(_eModuleID))
		return E_FAIL;

	CModuleMgr* pModuleMgr = CModuleMgr::Get_Instance();
	if (nullptr == pModuleMgr)
		return E_FAIL;

	Safe_AddRef(pModuleMgr);

	CModule* pModule = pModuleMgr->Get_Module(_eModuleID, _eSceneID);
	if (nullptr == pModule)
		return E_FAIL;

	*_ppModule = pModule;

	m_mapModule.emplace(_eModuleID, pModule);
	//map에 추가했으니까 AddRef
	Safe_AddRef(*_ppModule);

	Safe_Release(pModuleMgr);

	return S_OK;
}

CModule * CGameObject::Get_Module(MODULE _eModuleID)
{
	if (MODULE_END <= _eModuleID)
		return nullptr;

	auto& iter = m_mapModule.find(_eModuleID);
	if (iter == m_mapModule.end())
		return nullptr;
	
	return iter->second;
}

