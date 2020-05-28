#include "stdafx.h"
#include "..\Headers\Scene_Loading.h"
#include "Loading.h"
#include "ObjMgr.h"
#include "Image.h"
USING(MyGame)

CScene_Loading::CScene_Loading(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CScene(_pGraphic_Device)
{
}

HRESULT CScene_Loading::Initialize()
{
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	RETURN_FAIL_IF_NULL(pObjMgr);
	pObjMgr->Add_GO_To_Layer(L"Loading", SCENE_STATIC, CImage::Create(m_pGraphic_Device, Vector2(g_iWinCX >> 1, g_iWinCY >> 1), Vector2(g_iWinCX, g_iWinCY), L"loading", SCENE_STATIC));

	return S_OK;
}

_int CScene_Loading::Update(_double _timeDelta)
{
	return _int();
}

HRESULT CScene_Loading::Render()
{
	return S_OK;
}

HRESULT CScene_Loading::Initialize_Scene(SCENEID _SceneID, _uint _iLevel)
{
	m_pLoading->Load_Scene(_SceneID);

	return S_OK;
}


CScene_Loading * CScene_Loading::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CScene_Loading* pInstance = new CScene_Loading(_pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail to Create Loading Scene");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CScene_Loading::Free()
{
	Safe_Release(m_pLoading);
	CScene::Free();
}
