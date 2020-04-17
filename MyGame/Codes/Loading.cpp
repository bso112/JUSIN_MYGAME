#include "stdafx.h"
#include "..\Headers\Loading.h"
#include "Background.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "Textrue.h"

USING(MyGame)

CLoading * CLoading::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CLoading* pInstance = new CLoading(_pGraphic_Device);

	if (FAILED(pInstance->Initalize()))
	{
		MSG_BOX("Fail to Create Loading Scene");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoading::Free()
{
	CScene::Free();
}

HRESULT CLoading::Initalize()
{
	//텍스쳐를 먼저 로드해야함. 오브젝트들 이니셜라이즈 하는데 쓰임
	if (FAILED(Initalize_Textures()))
		return E_FAIL;

	if (FAILED(Initalize_Prototypes()))
		return E_FAIL;

	if (FAILED(Initalize_Layers()))
		return E_FAIL;




	return S_OK;
}

_int CLoading::Update(_double _timeDelta)
{
	CScene::Update(_timeDelta);
	return 0;
}

HRESULT CLoading::Render()
{
	CScene::Render();
	return 0;
}


HRESULT CLoading::Initalize_Prototypes()
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	if (FAILED(m_pObjMgr->Add_Prototype(CObjMgr::PROTOTYPE_BACKGROUND, SCENE_LOADING, CBackground::Create(m_pGraphic_Device))))
		return E_FAIL;
	return S_OK;
}

HRESULT CLoading::Initalize_Layers()
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	if (FAILED(m_pObjMgr->Add_GO_To_Layer(CObjMgr::PROTOTYPE_BACKGROUND, SCENE_LOADING, CObjMgr::LAYER_BACKGROUND, SCENE_LOADING)))
		return E_FAIL;
	return S_OK;
}

HRESULT CLoading::Initalize_Textures()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	CModuleMgr* pModuleMgr = CModuleMgr::Get_Instance();
	if (nullptr == pModuleMgr)
		return E_FAIL;

	Safe_AddRef(pModuleMgr);

	if (FAILED(pModuleMgr->Add_Module(MODULE_TEXTURE, SCENEID::SCENE_LOADING, CTextrue::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Loading.jpg"))))
		return E_FAIL;

	Safe_Release(pModuleMgr);
	return S_OK;
}


