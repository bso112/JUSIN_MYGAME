#include "stdafx.h"
#include "..\Headers\StageUIMgr.h"
#include "ObjMgr.h"
#include "Image.h"
#include "MyButton.h"
#include "Hero.h"
USING(MyGame)

IMPLEMENT_SINGLETON(CStageUIMgr)

CStageUIMgr::CStageUIMgr()
	:m_pObjMgr(CObjMgr::Get_Instance())
{
	Safe_AddRef(m_pObjMgr);
}

HRESULT CStageUIMgr::Initialize_Prototype(LPDIRECT3DDEVICE9 _pGraphic_Device, CHero* _pHero)
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	Safe_AddRef(_pGraphic_Device);
	m_pObjMgr->Add_GO_To_Layer(CObjMgr::LAYER_UI, SCENE_STAGE, CImage::Create(_pGraphic_Device, Vector4(0.f, 0.f, 0.f, 1.f), Vector2((float)g_iWinCX, 200), L"status_pane", SCENE_STAGE));
	
	int iBtnCX = 60;
	int iBtnCY = 70;
	CMyButton* pBtn = nullptr;
	pBtn = CMyButton::Create(_pGraphic_Device, Vector4(float(iBtnCX >> 1), g_iWinCY - float(iBtnCY >> 1), 0.f, 1.f), Vector2(iBtnCX, iBtnCY), L"waitBtn", SCENE_STAGE);
	//pBtn->Add_Listener([&] { _pHero-> })
	m_pObjMgr->Add_GO_To_Layer(CObjMgr::LAYER_UI, SCENE_STAGE, pBtn);
	pBtn = CMyButton::Create(_pGraphic_Device, Vector4(float(iBtnCX >> 1) + iBtnCX * 1, g_iWinCY - float(iBtnCY >> 1), 0.f, 1.f), Vector2(iBtnCX, iBtnCY), L"searchBtn", SCENE_STAGE);
	m_pObjMgr->Add_GO_To_Layer(CObjMgr::LAYER_UI, SCENE_STAGE, pBtn);
	pBtn = CMyButton::Create(_pGraphic_Device, Vector4(float(iBtnCX >> 1) + iBtnCX * 2, g_iWinCY - float(iBtnCY >> 1), 0.f, 1.f), Vector2(iBtnCX, iBtnCY), L"checkBtn", SCENE_STAGE);
	m_pObjMgr->Add_GO_To_Layer(CObjMgr::LAYER_UI, SCENE_STAGE, pBtn);
	pBtn = CMyButton::Create(_pGraphic_Device, Vector4(g_iWinCX - float(iBtnCX >> 1), g_iWinCY - float(iBtnCY >> 1), 0.f, 1.f), Vector2(iBtnCX, iBtnCY), L"quickSlotBtn", SCENE_STAGE);
	m_pObjMgr->Add_GO_To_Layer(CObjMgr::LAYER_UI, SCENE_STAGE, pBtn);
	pBtn = CMyButton::Create(_pGraphic_Device, Vector4(g_iWinCX - float(iBtnCX >> 1) - iBtnCX, g_iWinCY - float(iBtnCY >> 1), 0.f, 1.f), Vector2(iBtnCX, iBtnCY), L"inventoryBtn", SCENE_STAGE);
	m_pObjMgr->Add_GO_To_Layer(CObjMgr::LAYER_UI, SCENE_STAGE, pBtn);
	pBtn = CMyButton::Create(_pGraphic_Device, Vector4((float)(g_iWinCX >> 1), (float)(g_iWinCY >> 1), 0.f, 1.f), Vector2(g_iWinCX - 100.f, 200.f), L"scroll", SCENE_STAGE);
	m_pObjMgr->Add_GO_To_Layer(CObjMgr::LAYER_UI, SCENE_STAGE, pBtn);




	Safe_Release(_pGraphic_Device);
	return S_OK;
}

HRESULT CStageUIMgr::Initialize(LPDIRECT3DDEVICE9 _pGraphic_Device, CHero* _pHero)
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	Safe_AddRef(_pGraphic_Device);

	if (FAILED(Initialize_Prototype(_pGraphic_Device, _pHero)))
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
