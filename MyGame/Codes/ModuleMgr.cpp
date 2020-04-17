#include "stdafx.h"
#include "..\Headers\ModuleMgr.h"
#include "Module.h"

USING(MyGame)
IMPLEMENT_SINGLETON(CModuleMgr)

HRESULT CModuleMgr::Add_Module(MODULE _ePrototypeID, SCENEID _ePrototypeSceneID, CModule * _pModule)
{
	if (MODULE_END <= _ePrototypeID		||
		SCENE_END <= _ePrototypeSceneID ||
		nullptr	== _pModule)
		return E_FAIL;

	CModule* pModule = Find_Module(_ePrototypeID, _ePrototypeSceneID);
	if (nullptr != pModule)
		return E_FAIL;

	m_mapPrototypes[_ePrototypeSceneID].emplace(_ePrototypeID, _pModule);

	return S_OK;
}

CModule * CModuleMgr::Get_Module(MODULE _ePrototypeID, SCENEID _ePrototypeSceneID)
{
	if (MODULE_END <= _ePrototypeID ||
		SCENE_END <= _ePrototypeSceneID)
		return nullptr;

	CModule* pModule = Find_Module(_ePrototypeID, _ePrototypeSceneID);
	if (nullptr == pModule)
		return nullptr;

	return pModule->Clone();
}




CModule * CModuleMgr::Find_Module(MODULE _ePrototypeID, SCENEID _ePrototypeSceneID)
{
	if (MODULE_END <= _ePrototypeID ||
		SCENE_END <= _ePrototypeSceneID)
		return nullptr;

	auto& iter = m_mapPrototypes[_ePrototypeSceneID].find(_ePrototypeID);
	if (iter == m_mapPrototypes[_ePrototypeSceneID].end())
		return nullptr;

	return iter->second;
}

void CModuleMgr::Free()
{
	for (auto& map : m_mapPrototypes)
		for (auto& pair : map)
			Safe_Release(pair.second);
}
