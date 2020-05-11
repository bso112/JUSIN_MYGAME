#include "stdafx.h"
#include "ObjMgr.h"
#include "Layer.h"
#include "GameObject.h"
#include "Transform.h"


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

	//������Ÿ�Կ��� ��ü�� ������ �����Ѵ�.
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
		if (FAILED(layer->Add_GameObject(pGo)))
			goto exception;
	}

	return pGo;
exception:
	Safe_Release(pGo);
	return nullptr;
}

HRESULT CObjMgr::Add_GO_To_Layer(const _tchar* _eLayerID, SCENEID _eLayerSceneID, CGameObject * _pObj)
{
	if (SCENE_END <= _eLayerSceneID ||
		nullptr == _pObj)
		return E_FAIL;

	//���̾ ã�� �ִ´�. ���̾ ������ ���� �����.
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

CGameObject * CObjMgr::Picking_Tile(POINT _pt, _int _iTileX)
{
	int x = _pt.x / TILECX;
	int y = _pt.y / TILECY;

	CLayer* pLayer = Find_Layer(L"Tile", SCENE_STATIC);
	if (nullptr == pLayer)
		return nullptr;

	return pLayer->Get_GO(_iTileX * y + x);
}

CGameObject * CObjMgr::Picking_Tile(POINT _pt)
{
	CLayer* pLayer = Find_Layer(L"Tile_Homework", SCENE_STATIC);
	if (nullptr == pLayer)
		return nullptr;

	for (auto& pTile : pLayer->Get_List())
	{

		//pt�� �����ʿ� �ִٰ� �Ǵ��� ������ ��
		int cnt = 0;

		CTransform* pTransform = dynamic_cast<CTransform*>(pTile->Get_Module(L"Transform"));

		//��ġ����
		Vector3 vPos = pTransform->Get_Position();

		//������ �� ������ ���ϱ�
		Vector2 vTopPt = Vector2	(vPos.x					, vPos.y - (TILECY >> 1));
		Vector2 vBottomPt = Vector2	(vPos.x					, vPos.y + (TILECY >> 1));
		Vector2 vRightPt = Vector2	(vPos.x + (TILECX >> 1)	, vPos.y);
		Vector2 vLeftPt = Vector2	(vPos.x - (TILECX >> 1)	, vPos.y);

		Vector2 vPt[4] = { vTopPt, vRightPt, vBottomPt, vLeftPt };
		//������ �� �� ���ϱ� (�ð����)
		Vector2 vTop = vRightPt - vTopPt;
		Vector2 vRight = vBottomPt - vRightPt;
		Vector2 vBottom = vLeftPt - vBottomPt;
		Vector2 vLeft = vTopPt - vLeftPt;

		Vector2 vLine[4] = { vTop, vRight, vBottom, vLeft };

		for (int i = 0; i < 4; ++i)
		{
			//�������� ���ϱ�
			Vector2 vNomalVec = Vector2(-vLine[i].y, vLine[i].x);
			//���⺤���� ���������� �ٶ� ���콺������ ��ġ���� ���ϱ�
			Vector2 vPos = Vector2(_pt.x, _pt.y) - vPt[i];
			//���̰� ���ϱ�
			float cosTheata = D3DXVec4Dot(&vPos.Nomalize(), &vNomalVec.Nomalize());

			//costTheata�� ����� �����ʿ� �ִٰ� �Ǵ�(y���� �ݴ�� ����� �Ǵ��ؾ���)
			if (cosTheata > 0)
				++cnt;
		}


		//���� ���콺����Ʈ�� ��� ���� �����ʿ� ������ �ش� Ÿ���� ����
		if (cnt >= 4)
		{
			return pTile;
		}
	}

	return nullptr;
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
