// ControlView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "ControlView.h"
#include "ObjMgr.h"
#include "Terrain.h"
#include "Transform.h"
#include "MainFrm.h"
#include "Texture.h"
#include "MyGame_Constant.h"
#include "ModuleMgr.h"
#include "VIBuffer.h"
#include "Transform.h"
#include "Graphic_Device.h"
#include "Texture.h"
#include "ObjMgr.h"
#include "Layer.h"
#include "Terrain.h"

// CControlView

USING(MyGame)
IMPLEMENT_DYNCREATE(CControlView, CFormView)

BEGIN(MyGame)
int g_iTileX = 0;
CGameObject* g_pSelected;
int g_TextureIndex = 0;
END

CControlView::CControlView()
	: CFormView(IDD_CONTROLVIEW1)
	, m_iTileNumX(0)
	, m_iTileNumY(0)
	, m_pGraphic_DeviceMgr(CGraphic_Device::Get_Instance())
{
	Safe_AddRef(m_pGraphic_DeviceMgr);
}

CControlView::~CControlView()
{
}

void CControlView::DoDataExchange(CDataExchange* pDX)
{
	DDX_Text(pDX, IDC_EDIT1, m_iTileNumX);
	DDX_Text(pDX, IDC_EDIT2, m_iTileNumY);
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
	DDX_Control(pDX, IDCLOSE, m_Picture);
	CFormView::DoDataExchange(pDX);
}

HRESULT CControlView::Initialize_Tile()
{
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();


	//for (int i = 0; i < m_iTileNumY; ++i)
	//{
	//	for (int j = 0; j < m_iTileNumX; ++j)
	//	{
	//		CGameObject* pTile = pObjMgr->Add_GO_To_Layer(L"Tile", SCENE_STATIC, L"Tile", SCENE_STATIC);

	//		((CTerrain*)pTile)->Set_Texture(m_Combo.GetCurSel());

	//		CModule* pModule = pTile->Get_Module(L"Transform");
	//		if (!pModule)
	//			return E_FAIL;

	//		((CTransform*)pModule)->Set_Position(Vector3((TILECX >> 1) + TILECX * j, (TILECY >> 1) + i * TILECY));
	//		((CTransform*)pModule)->Set_Size(Vector3(TILECX, TILECY, 1.f));


	//	}
	//}

	for (size_t i = 0; i < m_iTileNumY; ++i)
	{
		for (size_t j = 0; j < m_iTileNumX; ++j)
		{
			CGameObject* pTile = pObjMgr->Add_GO_To_Layer(L"Tile_Homework", SCENE_STATIC, L"Tile_Homework", SCENE_STATIC);

			((CTerrain*)pTile)->Set_Texture(m_Combo.GetCurSel());

			CModule* pModule = pTile->Get_Module(L"Transform");
			if (!pModule)
				return E_FAIL;


			((CTerrain*)pTile)->Set_InitialPos(Vector3((i % 2) * (TILECX * 0.5f) + j * TILECX, i * (TILECY * 0.5f), 0.f));
			((CTransform*)pModule)->Set_Position(Vector3((i % 2) * (TILECX * 0.5f) + j * TILECX, i * (TILECY * 0.5f), 0.f));
			((CTransform*)pModule)->Set_Size(Vector3(TILECX, TILECY, 1.f));

			((CTransform*)pModule)->Late_Update();
		}
	}

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	pMainFrame->Set_ScrollSize(0, 0, CSize(TILECX * m_iTileNumX, TILECY * m_iTileNumY * 0.5f));


	return S_OK;

}

HRESULT CControlView::Save_Tile()
{
	
	//���� Ž���⸦ ����. 
	CFileDialog		FileDialog(FALSE, L"dat", nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"MyType Files(*.dat)|*.dat|cpp Files(*.cpp)|*.cpp||");

	CObjMgr*	pObject_Manager = CObjMgr::Get_Instance();
	if (nullptr == pObject_Manager)
		return E_FAIL;

	Safe_AddRef(pObject_Manager);

	CLayer*	pTileLayer = pObject_Manager->Find_Layer(L"Tile_Homework", SCENE_STATIC);
	if (nullptr == pTileLayer)
		return E_FAIL;

	list<CGameObject*> pTileList = pTileLayer->Get_List();

	//���� OK��ư�� ��������
	// (Modal�� �˾�â�� ���� ������ �ٸ� â�� Ȱ��ȭ ��ų �� ���� ���)
	if (FileDialog.DoModal() == IDOK)
	{
		HANDLE		hFile = 0;
		_ulong		dwByte = 0;

		hFile = CreateFile(FileDialog.GetPathName(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		if (0 == hFile)
			return E_FAIL;

		for (auto& pGameObject : pTileList)
		{
			CTerrain* pTile = (CTerrain*)pGameObject;
			CTerrain::SAVE_DATA	TileDesc = pTile->Get_SaveData();

			WriteFile(hFile, &TileDesc, sizeof(CTerrain::SAVE_DATA), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}

	Safe_Release(pObject_Manager);
	return S_OK;
}

HRESULT CControlView::Load_Tile()
{
	//���� Ž���⸦ ����. 
	CFileDialog		FileDialog(TRUE, L"dat", nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"MyType Files(*.dat)|*.dat|cpp Files(*.cpp)|*.cpp||");


	//���� OK��ư�� ��������
	// (Modal�� �˾�â�� ���� ������ �ٸ� â�� Ȱ��ȭ ��ų �� ���� ���)
	if (FileDialog.DoModal() == IDOK)
	{
		HANDLE		hFile = 0;
		_ulong		dwByte = 0;


		hFile = CreateFile(FileDialog.GetPathName(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (0 == hFile)
			return E_FAIL;


		CTerrain::SAVE_DATA	tSaveData;

		while (true)
		{
			ReadFile(hFile, &tSaveData, sizeof(CTerrain::SAVE_DATA), &dwByte, nullptr);
			if (dwByte == 0)
				break;

			
			CTerrain* pTerrain = (CTerrain*)CObjMgr::Get_Instance()->Add_GO_To_Layer(L"Tile_Homework", SCENE_STATIC, L"Terrain", SCENE_STATIC);
			pTerrain->Load_Data(tSaveData);
			
		}

		CloseHandle(hFile);
	}

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if (nullptr == pMainFrame)
		return E_FAIL;
	//ȭ���� �ٽñ׸���.(�޽��� �߻���Ű��)
	pMainFrame->Invaildate(0, 0);



	return S_OK;
}

void CControlView::CreateTile()
{
	//���� ����� ������ �����´�.
	UpdateData(TRUE);
	MyGame::g_iTileX = m_iTileNumX;

	//������ ������ �̿��� Ÿ���� �׸���.
	if (FAILED(Initialize_Tile()))
		return;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if (nullptr == pMainFrame)
		return;
	//ȭ���� �ٽñ׸���.(�޽��� �߻���Ű��)
	pMainFrame->Invaildate(0, 0);

	//ȭ���� ����� �ٽñ׸���.
	Invalidate(FALSE);

}

BEGIN_MESSAGE_MAP(CControlView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CControlView::CreateTile)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CControlView::OnCbnSelchangeCombo1)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON3, &CControlView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CControlView::OnBnClickedButton2)
END_MESSAGE_MAP()


// CControlView �����Դϴ�.

#ifdef _DEBUG
void CControlView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CControlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CControlView �޽��� ó�����Դϴ�.






void CControlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	TCHAR	szString[MAX_PATH] = L"";
	for (size_t i = 1; i < 41; ++i)
	{
		wsprintf(szString, L"Tile%d", i);
		m_Combo.AddString(szString);
	}
	m_Combo.SetCurSel(0);
	m_Combo.GetCurSel();


	CModuleMgr* pModuleMgr = CModuleMgr::Get_Instance();
	if (nullptr == pModuleMgr)
		return;

	m_pVIBuffer = (CVIBuffer*)CModuleMgr::Get_Instance()->Get_Module(L"VIBuffer", SCENE_STATIC);
	if (nullptr == m_pVIBuffer)
		return;
	m_pTransform = (CTransform*)CModuleMgr::Get_Instance()->Get_Module(L"Transform", SCENE_STATIC);
	if (nullptr == m_pTransform)
		return;
	/*m_pTexture = (CTexture*)CModuleMgr::Get_Instance()->Get_Module(L"Texture_Tile", SCENE_STATIC);
	if (nullptr == m_pTexture)
		return;*/
	m_pTexture = (CTexture*)CModuleMgr::Get_Instance()->Get_Module(L"Texture_Tile_Homework", SCENE_STATIC);
	if (nullptr == m_pTexture)
		return;

	m_pTransform->Set_Size(Vector3(g_iWinCX, g_iWinCY, 1.f));
	m_pTransform->Set_Position(Vector2(g_iWinCX >> 1, g_iWinCY >> 1));


}





void CControlView::OnCbnSelchangeCombo1()
{
	g_TextureIndex = m_Combo.GetCurSel();

	//if (nullptr != g_pSelected)
	//{
	//	((CTerrain*)g_pSelected)->Set_Texture(m_Combo.GetCurSel());

	//	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	//	if (nullptr == pMainFrame)
	//		return;
	//	//ȭ���� �ٽñ׸���.(�޽��� �߻���Ű��)
	//	pMainFrame->Invaildate(0, 0);
	//}
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CControlView::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	Safe_Release(m_pTransform);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTexture);
	Safe_Release(m_pGraphic_DeviceMgr);
}


void CControlView::OnDraw(CDC* /*pDC*/)
{
	if (nullptr == m_pGraphic_DeviceMgr)
		return;
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	PDIRECT3DDEVICE9 pGraphicDevice = m_pGraphic_DeviceMgr->Get_GraphicDevice();
	if (nullptr == pGraphicDevice)
		return;


	m_pTransform->Late_Update();


	pGraphicDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DXCOLOR(0.f, 0.f, 1.f, 1.f), 1.f, 0);
	pGraphicDevice->BeginScene();

	pGraphicDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pGraphicDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pGraphicDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pTexture->Set_Texture(m_Combo.GetCurSel());
	m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix());
	m_pVIBuffer->Render();

	pGraphicDevice->EndScene();
	pGraphicDevice->Present(0, 0, m_Picture.m_hWnd, nullptr);

	pGraphicDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}


void CControlView::OnBnClickedButton3()
{

	Load_Tile();
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CControlView::OnBnClickedButton2()
{
	Save_Tile();

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
