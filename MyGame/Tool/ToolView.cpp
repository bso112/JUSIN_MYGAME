
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "ToolDoc.h"
#include "ToolView.h"
#include "MainFrm.h"
#include "Graphic_Device.h"
#include "ModuleMgr.h"
#include "ObjMgr.h"
#include "Transform.h"
#include "VIBuffer.h"
#include "Texture.h"
#include "Terrain.h"
#include "Renderer.h"
#include "KeyMgr.h"
#include "ControlView.h"
#include "Layer.h"


USING(MyGame)
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CView)

BEGIN_MESSAGE_MAP(CToolView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
	:m_pRenderer(CRenderer::Get_Instance())
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	Safe_AddRef(m_pRenderer);
}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CToolView �׸���

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	pObjMgr->Update(0.0);


	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	if (nullptr == m_pGraphic_Device ||
		nullptr == m_pRenderer)
		return;

	ALPHATEST;

	m_pGraphic_Device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DXCOLOR(0.f, 0.f, 1.f, 1.f), 1.f, 0);
	m_pGraphic_Device->BeginScene();

	m_pRenderer->Render();

	m_pGraphic_Device->EndScene();
	m_pGraphic_Device->Present(nullptr, nullptr, 0, nullptr);

	ALPHATEST_END;
}


// CToolView �μ�

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����


void CToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	SetScrollSizes(MM_TEXT, CSize(0, 0));

	if (FAILED(Ready_WindowSize()))
		return;
	if (FAILED(Ready_GraphicDevice()))
		return;
	if (FAILED(Ready_PrototypeModule()))
		return;
	if (FAILED(Ready_PrototypeGameObject()))
		return;
}


void CToolView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.


	Safe_Release(m_pGraphic_Device);
	m_pRenderer->Clear_RenderGroup();
	Safe_Release(m_pRenderer);



}

HRESULT CToolView::Ready_WindowSize()
{
	//������������ ���´�. 
	CMainFrame*	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if (nullptr == pMainFrame)
		return E_FAIL;

	//������������ RECT�� ���´�.
	RECT	mainFrameRc;
	pMainFrame->GetWindowRect(&mainFrameRc);

	RECT toolViewRC = {};
	GetClientRect(&toolViewRC);

	RECT sideViewRC = {};
	pMainFrame->Get_ClientRect(0, 1, sideViewRC);


	int iFrameWidth = (mainFrameRc.right - mainFrameRc.left) - (toolViewRC.right + sideViewRC.right);
	int iFrameHeight = (mainFrameRc.bottom - mainFrameRc.top) - (toolViewRC.bottom);

	pMainFrame->SetWindowPos(nullptr, 0, 0, 800 + g_iFormViewCX + iFrameWidth, g_iFormViewCY + iFrameHeight, SWP_NOMOVE);


	return S_OK;
}

HRESULT CToolView::Ready_GraphicDevice()
{

	CGraphic_Device* pGraphic_DeviceMgr = CGraphic_Device::Get_Instance();
	if (nullptr == pGraphic_DeviceMgr)
		return E_FAIL;
	Safe_AddRef(pGraphic_DeviceMgr);

	pGraphic_DeviceMgr->Ready_Graphic_Device(m_hWnd, CGraphic_Device::TYPE_WIN, &m_pGraphic_Device);

	Safe_Release(pGraphic_DeviceMgr);
	return S_OK;
}

HRESULT CToolView::Ready_PrototypeModule()
{
	CModuleMgr* pModuleMgr = CModuleMgr::Get_Instance();
	if (nullptr == pModuleMgr)
		return E_FAIL;

	if (FAILED(pModuleMgr->Add_Module(L"Transform", SCENE_STATIC, CTransform::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(pModuleMgr->Add_Module(L"VIBuffer", SCENE_STATIC, CVIBuffer::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(pModuleMgr->Add_Module(L"Texture_Tile", SCENE_STATIC, CTexture::Create(m_pGraphic_Device, L"Resources/Textures/Terrain/%d.png", 39))))
		return E_FAIL;


	if (FAILED(pModuleMgr->Add_Module(L"Texture_Tile_Homework", SCENE_STATIC, CTexture::Create(m_pGraphic_Device, L"Resources/Textures/Tile_Homework/Tile%d.png", 35))))
		return E_FAIL;


	return S_OK;
}

HRESULT CToolView::Ready_PrototypeGameObject()
{
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;

	if (FAILED(pObjMgr->Add_Prototype(L"Tile", SCENE_STATIC, CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"Texture_Tile", SCENE_STATIC))))
		return E_FAIL;

	if (FAILED(pObjMgr->Add_Prototype(L"Tile_Homework", SCENE_STATIC, CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"Texture_Tile_Homework", SCENE_STATIC))))
		return E_FAIL;


	return S_OK;
}

void CToolView::Set_ScrollSize(CSize _size)
{
	SetScrollSizes(MM_TEXT, _size);
}




void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();

	CGameObject* pObject = pObjMgr->Picking_Tile(point);
	if (nullptr == pObject)
		return;

	int textureIndex = g_TextureIndex;

	CTerrain* pTerrain = dynamic_cast<CTerrain*> (pObject);
	if (nullptr == pTerrain)
		return;
	pTerrain->Set_Texture(g_TextureIndex);

	Invalidate(FALSE);

	g_pSelected = pObject;

	CView::OnLButtonDown(nFlags, point);
}


void CToolView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return;
	CLayer* pLayer = pObjMgr->Find_Layer(L"Tile_Homework", SCENE_STATIC);
	if (nullptr == pLayer)
		return;
	for (auto& obj : pLayer->Get_List())
	{
		if (nullptr != obj)
		{
			dynamic_cast<CTerrain*>(obj)->Set_ScrollY(GetScrollPos(1));
		}
	}
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CToolView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return;
	CLayer* pLayer = pObjMgr->Find_Layer(L"Tile_Homework", SCENE_STATIC);
	if (nullptr == pLayer)
		return;
	for (auto& obj : pLayer->Get_List())
	{
		if (nullptr != obj)
		{
			dynamic_cast<CTerrain*>(obj)->Set_ScrollX(GetScrollPos(0));
		}
	}

	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL CToolView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return FALSE;
}
