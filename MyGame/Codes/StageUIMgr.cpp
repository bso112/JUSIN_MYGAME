#include "stdafx.h"
#include "..\Headers\StageUIMgr.h"
#include "ObjMgr.h"
#include "Image.h"
#include "MyButton.h"
#include "Hero.h"
#include "InventoryUIMgr.h"
#include "DialogMgr.h"
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
	Safe_AddRef(_pHero);

	vector<CGameObject*>  vecUI;
	m_pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(_pGraphic_Device, Vector4(float(g_iWinCX>>1), 50.f, 0.f, 1.f), Vector2((float)g_iWinCX, 100.f), L"status_pane", SCENE_STAGE));
	
	int iBtnCX = 60;
	int iBtnCY = 70;
	CMyButton* pBtn = nullptr;

	//인벤토리버튼
	pBtn = CMyButton::Create(_pGraphic_Device, Vector4((g_iWinCX >> 1) + float(iBtnCX >> 1), g_iWinCY - float(iBtnCY >> 1), 0.f, 1.f), Vector2((float)iBtnCX, (float)iBtnCY), L"inventoryBtn", SCENE_STAGE);
	//누르면 인벤토리 켜기
	pBtn->Add_Listener([&] {m_pInventoryUIMgr->Active_Inventory();});
	m_pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, pBtn);
	vecUI.push_back(pBtn);
	

	pBtn = CMyButton::Create(_pGraphic_Device, Vector4((g_iWinCX >> 1) + float(iBtnCX >> 1) + iBtnCX * 1, g_iWinCY - float(iBtnCY >> 1), 0.f, 1.f), Vector2((float)iBtnCX, (float)iBtnCY), L"searchBtn", SCENE_STAGE);
	m_pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, pBtn);
	vecUI.push_back(pBtn);
	pBtn = CMyButton::Create(_pGraphic_Device, Vector4((g_iWinCX >> 1) + float(iBtnCX >> 1) + iBtnCX * 2, g_iWinCY - float(iBtnCY >> 1), 0.f, 1.f), Vector2((float)iBtnCX, (float)iBtnCY), L"checkBtn", SCENE_STAGE);
	m_pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, pBtn);
	vecUI.push_back(pBtn);
	pBtn = CMyButton::Create(_pGraphic_Device, Vector4((g_iWinCX >> 1) + float(iBtnCX >> 1) + iBtnCX * 3, g_iWinCY - float(iBtnCY >> 1), 0.f, 1.f), Vector2((float)iBtnCX, (float)iBtnCY), L"waitBtn", SCENE_STAGE);
	m_pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, pBtn);
	vecUI.push_back(pBtn);
	
	//퀵슬롯
	pBtn = CMyButton::Create(_pGraphic_Device, Vector4((g_iWinCX >> 1) - float(iBtnCX >> 1), g_iWinCY - float(iBtnCY >> 1), 0.f, 1.f), Vector2((float)iBtnCX, (float)iBtnCY), L"quickSlotBtn", SCENE_STAGE);
	m_pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, pBtn);
	vecUI.push_back(pBtn);
	pBtn = CMyButton::Create(_pGraphic_Device, Vector4((g_iWinCX >> 1) - float(iBtnCX >> 1) - iBtnCX * 1, g_iWinCY - float(iBtnCY >> 1), 0.f, 1.f), Vector2((float)iBtnCX, (float)iBtnCY), L"quickSlotBtn", SCENE_STAGE);
	m_pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, pBtn);
	vecUI.push_back(pBtn);
	pBtn = CMyButton::Create(_pGraphic_Device, Vector4((g_iWinCX >> 1) - float(iBtnCX >> 1) - iBtnCX * 2, g_iWinCY - float(iBtnCY >> 1), 0.f, 1.f), Vector2((float)iBtnCX, (float)iBtnCY), L"quickSlotBtn", SCENE_STAGE);
	m_pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, pBtn);
	vecUI.push_back(pBtn);

	
	
	//스크롤 표시
	//pBtn = CMyButton::Create(_pGraphic_Device, Vector4((float)(g_iWinCX >> 1), (float)(g_iWinCY >> 1), 0.f, 1.f), Vector2(g_iWinCX - 100.f, 200.f), L"scroll", SCENE_STAGE);
	//m_pObjMgr->Add_GO_To_Layer(CObjMgr::LAYER_UI, SCENE_STAGE, pBtn);

	for (auto& ui : vecUI)
	{
		CTransform* pTransform = (CTransform*)ui->Get_Module(L"Transform");
		if (nullptr != pTransform)
			m_vecUIRect.push_back(pTransform->Get_RECT());
	}


	Safe_Release(_pHero);
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

	m_pInventoryUIMgr = CInventoryUIMgr::Get_Instance();
	if (nullptr == m_pInventoryUIMgr)
		return E_FAIL;
	
	m_pInventoryUIMgr->Initialize(_pGraphic_Device);
	Safe_AddRef(m_pInventoryUIMgr);

	CDialogMgr* pDialogMgr = CDialogMgr::Get_Instance();
	if (nullptr == pDialogMgr)
		return E_FAIL;

	pDialogMgr->Initialize(_pGraphic_Device);


	Safe_Release(_pGraphic_Device);
	return S_OK;
}

vector<RECT> CStageUIMgr::GetUIRect()
{
	vector<RECT> rc = m_pInventoryUIMgr->GetUIRect();
	for (auto& uiRect : m_vecUIRect)
	{
		rc.push_back(uiRect);
	}
	return rc;
}

void CStageUIMgr::Free()
{
	Safe_Release(m_pObjMgr);
	Safe_Release(m_pInventoryUIMgr);

	//다른 씬에서도 쓰려나?
	if (0 != CInventoryUIMgr::Destroy_Instance())
	{
		m_pInventoryUIMgr = nullptr;
		MSG_BOX("Fail to release InventoryUIMgr");
	}

	if (0 != CDialogMgr::Destroy_Instance())
		MSG_BOX("Fail to release CDialogMgr");

		
}
