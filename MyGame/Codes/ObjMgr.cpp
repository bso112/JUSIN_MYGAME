#include "stdafx.h"
#include "..\Headers\ObjMgr.h"
#include "Layer.h"
#include "GameObject.h"

USING(MyGame)

IMPLEMENT_SINGLETON(CObjMgr)
CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
}

_int CObjMgr::Update(_double _timeDelta)
{
	for (int i = 0; i < SCENE_END; ++i)
	{
		for (auto& pair : m_mapLayer[i])
		{
			if (nullptr != pair.second)
			{
				if (0x80000000 & pair.second->Update(_timeDelta))
					return -1;
			}

		}
	}

	for (int i = 0; i < SCENE_END; ++i)
	{
		for (auto& pair : m_mapLayer[i])
		{
			if (nullptr != pair.second)
			{
				if (0x80000000 & pair.second->Late_Update(_timeDelta))
					return -1;
			}

		}
	}
	return 0;
}

HRESULT CObjMgr::Add_Prototype(const _tchar* _ePrototypeID, SCENEID _ePrototypeSceneID, CGameObject* _pGO)
{
	if (SCENE_END <= _ePrototypeSceneID ||
		nullptr == _pGO ||
		nullptr != Find_Prototype(_ePrototypeID, _ePrototypeSceneID))
		return E_FAIL;

	m_mapPrototype[_ePrototypeSceneID].emplace(_ePrototypeID, _pGO);

	return S_OK;
}

CGameObject* CObjMgr::Add_GO_To_Layer(const _tchar* _ePrototypeID, SCENEID _ePrototypeSceneID, const _tchar* _eLayerID, SCENEID _eLayerSceneID, void* _pArg)
{
	if (SCENE_END <= _ePrototypeSceneID ||
		SCENE_END <= _eLayerSceneID)
		return nullptr;

	CGameObject* pPrototype = Find_Prototype(_ePrototypeID, _ePrototypeSceneID);
	if (nullptr == pPrototype)
		return nullptr;

	//프로토타입에서 객체를 복사해 생성한다.
	CGameObject* pGo = pPrototype->Clone(_pArg);
	if (nullptr == pGo)
		return nullptr;

	CLayer* layer = Find_Layer(_eLayerID, _eLayerSceneID);
	if (nullptr == layer)
	{
		layer = CLayer::Create();
		if (nullptr == layer)
			goto exception;

		if (FAILED(layer->Add_GameObject(pGo)))
			goto exception;

		m_mapLayer[_eLayerSceneID].emplace(_eLayerID, layer);

	}
	else
	{
		if(FAILED(layer->Add_GameObject(pGo)))
			goto exception;
	}

	return pGo;
exception:
	Safe_Release(pGo);
	return nullptr;
}

HRESULT CObjMgr::Add_GO_To_Layer(const _tchar* _eLayerID, SCENEID _eLayerSceneID, CGameObject * _pObj)
{
	if (SCENE_END <= _eLayerSceneID	||
		nullptr	== _pObj)
		return E_FAIL;

	//레이어를 찾아 넣는다. 레이어가 없으면 새로 만든다.
	CLayer* layer = Find_Layer(_eLayerID, _eLayerSceneID);
	if (nullptr == layer)
	{
		layer = CLayer::Create();
		if (nullptr == layer)
			return E_FAIL;

		if (FAILED(layer->Add_GameObject(_pObj)))
			return E_FAIL;

		m_mapLayer[_eLayerSceneID].emplace(_eLayerID, layer);

	}
	else
	{
		if (FAILED(layer->Add_GameObject(_pObj)))
			return E_FAIL;
	}

	return S_OK;

}

CGameObject * CObjMgr::Find_Prototype(const _tchar* _ePrototypeID, SCENEID _ePrototypeSceneID)
{
	if (SCENE_END <= _ePrototypeSceneID)
		return nullptr;

	auto& iter = find_if(m_mapPrototype[_ePrototypeSceneID].begin(), m_mapPrototype[_ePrototypeSceneID].end(), CFinder_Tag(_ePrototypeID));
	
	if (iter == m_mapPrototype[_ePrototypeSceneID].end())
		return nullptr;

	return iter->second;
}

CLayer * CObjMgr::Find_Layer(const _tchar* _eLayerID, SCENEID _eLayerSceneID)
{
	if (SCENE_END <= _eLayerSceneID)
		return nullptr;

	auto& iter = find_if(m_mapLayer[_eLayerSceneID].begin(), m_mapLayer[_eLayerSceneID].end(), CFinder_Tag(_eLayerID));

	if (iter == m_mapLayer[_eLayerSceneID].end())
		return nullptr;
	
	return iter->second;
}

CGameObject * CObjMgr::Get_Player(SCENEID _eLayerSceneID)
{
	CLayer* pPlayerLayer = Find_Layer(L"Player", _eLayerSceneID);
	if (nullptr == pPlayerLayer)
		return nullptr;
	return pPlayerLayer->Get_Front();
}

HRESULT CObjMgr::Clear_Scene(SCENEID _eSceneID)
{
	if (SCENEID::SCENE_END <= _eSceneID)
		return E_FAIL;

	for (auto& pair : m_mapLayer[_eSceneID])
		Safe_Release(pair.second);

	m_mapLayer[_eSceneID].clear();

	for (auto& pair : m_mapPrototype[_eSceneID])
		Safe_Release(pair.second);

	m_mapPrototype[_eSceneID].clear();

	return S_OK;
}

void CObjMgr::Free()
{
	for (auto& map : m_mapLayer)
	{
		for (auto& pair : map)
		{
			Safe_Release(pair.second);
		}

		map.clear();
	}

	for (auto& map : m_mapPrototype)
	{
		for (auto& pair : map)
		{
			Safe_Release(pair.second);
		}

		map.clear();
	}

}
