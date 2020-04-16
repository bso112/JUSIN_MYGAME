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

HRESULT CObjMgr::Add_Prototype(PrototypeID _ePrototypeID, SCENEID _ePrototypeSceneID, CGameObject* _pGO)
{
	if (SCENE_END <= _ePrototypeSceneID ||
		nullptr == _pGO ||
		nullptr != Find_Prototype(_ePrototypeID, _ePrototypeSceneID))
		return E_FAIL;

	m_mapPrototype[_ePrototypeSceneID].emplace(_ePrototypeID, _pGO);

	return S_OK;
}

HRESULT CObjMgr::Add_GO_To_Layer(PrototypeID _ePrototypeID, SCENEID _ePrototypeSceneID, LayerID _eLayerID, SCENEID _eLayerSceneID)
{
	if (SCENE_END <= _ePrototypeSceneID ||
		SCENE_END <= _eLayerSceneID)
		return E_FAIL;

	CGameObject* pPrototype = Find_Prototype(_ePrototypeID, _ePrototypeSceneID);
	if (nullptr == pPrototype)
		return E_FAIL;

	//프로토타입에서 객체를 복사해 생성한다.
	CGameObject* pGo = pPrototype->Clone();
	if (nullptr == pGo)
		return E_FAIL;

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

	return S_OK;
exception:
	Safe_Release(pGo);
	return E_FAIL;
}

CGameObject * CObjMgr::Find_Prototype(PrototypeID _ePrototypeID, SCENEID _ePrototypeSceneID)
{
	if (SCENE_END <= _ePrototypeSceneID ||
		PROTOTYPE_END <= _ePrototypeID)
		return nullptr;

	auto& iter = m_mapPrototype[_ePrototypeSceneID].find(_ePrototypeID);

	if (iter == m_mapPrototype[_ePrototypeSceneID].end())
		return nullptr;

	return iter->second;
}

CLayer * CObjMgr::Find_Layer(LayerID _eLayerID, SCENEID _eLayerSceneID)
{
	if (SCENE_END <= _eLayerSceneID ||
		LAYER_END <= _eLayerID)
		return nullptr;

	auto& iter = m_mapLayer[_eLayerSceneID].find(_eLayerID);

	if (iter == m_mapLayer[_eLayerSceneID].end())
		return nullptr;
	
	return iter->second;
}

CGameObject * CObjMgr::Get_Player(SCENEID _eLayerSceneID)
{
	CLayer* pPlayerLayer = Find_Layer(LayerID::LAYER_PLAYER, _eLayerSceneID);
	if (nullptr == pPlayerLayer)
		return nullptr;
	return pPlayerLayer->Get_Front();
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
