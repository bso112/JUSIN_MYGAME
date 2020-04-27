#include "stdafx.h"
#include "..\Headers\StageUIMgr.h"
#include "ObjMgr.h"
#include "Image.h"
#include "MyButton.h"
USING(MyGame)

IMPLEMENT_SINGLETON(CStageUIMgr)

CStageUIMgr::CStageUIMgr()
	:m_pObjMgr(CObjMgr::Get_Instance())
{
	Safe_AddRef(m_pObjMgr);
}

HRESULT CStageUIMgr::Initialize_Prototype(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	Safe_AddRef(_pGraphic_Device);

	m_pObjMgr->Add_GO_To_Layer(CObjMgr::LAYER_UI, SCENE_STAGE, CImage::Create(_pGraphic_Device, Vector4(0, 0, 0, 1), Vector2(g_iWinCX, 200), L"status_pane", SCENE_STAGE));

	Safe_Release(_pGraphic_Device);
	return S_OK;
}

HRESULT CStageUIMgr::Initialize(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	Safe_AddRef(_pGraphic_Device);

	if (FAILED(Initialize_Prototype(_pGraphic_Device)))
	{
		Safe_Release(_pGraphic_Device);
		return E_FAIL;
	}

	Safe_Release(_pGraphic_Device);
	return S_OK;
}

HRESULT CStageUIMgr::Update()
{
	return S_OK;
}

HRESULT CStageUIMgr::Render()
{
	return S_OK;
}

void CStageUIMgr::Free()
{
	Safe_Release(m_pObjMgr);
}
