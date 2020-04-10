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
	return _int();
}

HRESULT CObjMgr::Add_Prototype(const wchar_t * _pPrototypeKey, SCENEID _ePrototypeSceneID, CGameObject * _pGO)
{
	if (SCENE_END <= _ePrototypeSceneID ||
		nullptr == _pGO ||
		nullptr != Find_Prototype(_pPrototypeKey, _ePrototypeSceneID))
		return E_FAIL;

	m_mapPrototype[_ePrototypeSceneID].emplace(_pPrototypeKey, _pGO);

	return S_OK;
}

HRESULT CObjMgr::Add_GO_To_Layer(const wchar_t * _pPrototypeKey, SCENEID _ePrototypeSceneID, const wchar_t * _pLayerKey, SCENEID _eLayerSceneID)
{
	if (SCENE_END <= _ePrototypeSceneID ||
		SCENE_END <= _eLayerSceneID)
		return E_FAIL;

	CGameObject* pPrototype = Find_Prototype(_pPrototypeKey, _ePrototypeSceneID);
	if (nullptr == pPrototype)
		return E_FAIL;

	//프로토타입에서 객체를 복사해 생성한다.
	CGameObject* pGo = pPrototype->Clone();
	if (nullptr == pGo)
		return E_FAIL;

	CLayer* layer = Find_Layer(_pLayerKey, _eLayerSceneID);
	if (nullptr == layer)
	{
		layer = CLayer::Create();
		if (nullptr == layer)
			goto exception;

		if (FAILED(layer->Add_GameObject(pGo)))
			goto exception;

		m_mapLayer[_eLayerSceneID].emplace(_pLayerKey, layer);

	}
	else
	{
		if(FAILED(layer->Add_GameObject(pGo)))
			goto exception;
	}

	return S_OK;
exception:
	Safe_Release(pGo);
	return E_FAIL;
}

CGameObject * CObjMgr::Find_Prototype(const wchar_t* _pPrototypeKey, SCENEID _ePrototypeSceneID)
{
	if (SCENE_END <= _ePrototypeSceneID)
		return nullptr;

	auto& iter = find_if(m_mapPrototype[_ePrototypeSceneID].begin(), m_mapPrototype[_ePrototypeSceneID].end(), CFinder_Tag(_pPrototypeKey));

	if (iter == m_mapPrototype[_ePrototypeSceneID].end())
		return nullptr;


	return iter->second;
}

CLayer * CObjMgr::Find_Layer(const wchar_t* _pLayerKey, SCENEID _eLayerSceneID)
{
	if (SCENE_END <= _eLayerSceneID)
		return nullptr;

	auto& iter = find_if(m_mapLayer[_eLayerSceneID].begin(), m_mapLayer[_eLayerSceneID].end(), CFinder_Tag(_pLayerKey));

	if (iter == m_mapLayer[_eLayerSceneID].end())
		return nullptr;

	return iter->second;
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
