#include "stdafx.h"
#include "..\Headers\Scene.h"
#include "Renderer.h"
#include "ObjMgr.h"
#include "Image.h"
#include "KeyMgr.h"
#include "Pipline.h"

USING(MyGame)
CScene::CScene(PDIRECT3DDEVICE9 _pGraphic_Device)
	:m_pGraphic_Device(_pGraphic_Device), m_pRenderer(CRenderer::Get_Instance()),
	m_pObjMgr(CObjMgr::Get_Instance()), m_pPipline(CPipline::Get_Instance())
{
	Safe_AddRef(m_pGraphic_Device);
	Safe_AddRef(m_pRenderer);
	Safe_AddRef(m_pObjMgr);
	Safe_AddRef(m_pPipline);
}

HRESULT CScene::Initialize()
{

	return S_OK;
}

_int CScene::Update(_double _timeDelta)
{
	if (nullptr == m_pObjMgr)
		return -1;

	m_pObjMgr->Update(_timeDelta);
	m_pPipline->UpdateViewMatrix();
	return 0;
}

HRESULT CScene::Render()
{
	if (nullptr == m_pRenderer)
		return -1;

	m_pRenderer->Render();

	return S_OK;
}


void CScene::Free()
{
	Safe_Release(m_pPipline);
	Safe_Release(m_pObjMgr);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pGraphic_Device);
}
