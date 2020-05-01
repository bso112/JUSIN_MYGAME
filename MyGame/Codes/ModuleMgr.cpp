#include "stdafx.h"
#include "..\Headers\ModuleMgr.h"
#include "Module.h"

USING(MyGame)
IMPLEMENT_SINGLETON(CModuleMgr)

HRESULT CModuleMgr::Add_Module(const _tchar* _pTag, SCENEID _ePrototypeSceneID, CModule * _pModule)
{
	if (SCENE_END <= _ePrototypeSceneID ||
		nullptr	== _pModule)
		return E_FAIL;

	//문자열 깊은복사 (맵의 키는 문자열의 포인터이기 때문에 원본이 바뀌면 key도 바뀌어버림)
	_tchar* szTag = new _tchar[MAX_PATH];
	ZeroMemory(szTag, sizeof(_tchar)*MAX_PATH);
	StringCchCat(szTag, MAX_PATH, _pTag);

	CModule* pModule = Find_Module(szTag, _ePrototypeSceneID);
	if (nullptr != pModule)
		return E_FAIL;
	
	m_mapPrototypes[_ePrototypeSceneID].emplace(szTag, _pModule);

	return S_OK;
}

CModule * CModuleMgr::Get_Module(const _tchar* _pTag, SCENEID _ePrototypeSceneID, void* _pArg)
{
	if (SCENE_END <= _ePrototypeSceneID)
		return nullptr;

	CModule* pModule = Find_Module(_pTag, _ePrototypeSceneID);
	if (nullptr == pModule)
		return nullptr;

	return pModule->Clone(_pArg);
}

HRESULT CModuleMgr::Clear_Scene(SCENEID _eSceneID)
{
	if (SCENE_END <= _eSceneID)
		return E_FAIL;
	
	for (auto& pair : m_mapPrototypes[_eSceneID])
		Safe_Release(pair.second);

	m_mapPrototypes[_eSceneID].clear();

	return S_OK;
}


CModule * CModuleMgr::Find_Module(const _tchar* _pTag, SCENEID _ePrototypeSceneID)
{
	if (SCENE_END <= _ePrototypeSceneID)
		return nullptr;

	auto& iter = find_if(m_mapPrototypes[_ePrototypeSceneID].begin(), m_mapPrototypes[_ePrototypeSceneID].end(), CFinder_Tag(_pTag));
	if (iter == m_mapPrototypes[_ePrototypeSceneID].end())
		return nullptr;

	return iter->second;
}

void CModuleMgr::Free()
{
	for (auto& map : m_mapPrototypes)
		for (auto& pair : map)
		{
			Safe_Delete_Array(pair.first);
			Safe_Release(pair.second);
		}
}
