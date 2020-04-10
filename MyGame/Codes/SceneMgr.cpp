#include "stdafx.h"
#include "..\Headers\SceneMgr.h"
#include "Loading.h"

USING(MyGame)

IMPLEMENT_SINGLETON(CSceneMgr)


HRESULT CSceneMgr::Scene_Change(SCENEID _eID, PDIRECT3DDEVICE9 _pGraphic_Device)
{
	if (0 != Safe_Release(m_pCurrScene))
		goto exception;

	switch (_eID)
	{
	case MyGame::SCENE_STATIC:
		break;
	case MyGame::SCENE_LOADING:
	{
		m_pCurrScene = CLoading::Create(_pGraphic_Device);
		if (m_pCurrScene == nullptr)
			return E_FAIL;
	}
		break;
	case MyGame::SCENE_STAGE:
		break;
	case MyGame::SCENE_END:
		break;
	default:
		break;
	}

	if (nullptr == m_pCurrScene)
		goto exception;

	return S_OK;
exception:
	MSG_BOX("Failed To Replacement Scene");
	return E_FAIL;
}

_int CSceneMgr::Update(_double _timeDelta)
{
	if (nullptr == m_pCurrScene)
		return -1;

	return m_pCurrScene->Update(_timeDelta);
}

HRESULT CSceneMgr::Render()
{
	if (nullptr == m_pCurrScene)
		return E_FAIL;

	m_pCurrScene->Render();
	return S_OK;
}

void CSceneMgr::Free()
{
	if (0 != Safe_Release(m_pCurrScene))
		MSG_BOX("Fail to Release Current Scene");
}
