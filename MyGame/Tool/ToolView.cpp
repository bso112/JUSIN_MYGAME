
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
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

// CToolView 생성/소멸

CToolView::CToolView()
	:m_pRenderer(CRenderer::Get_Instance())
{
	// TODO: 여기에 생성 코드를 추가합니다.
	Safe_AddRef(m_pRenderer);
}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CToolView 그리기

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	pObjMgr->Update(0.0);


	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

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


// CToolView 인쇄

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기


void CToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.


	Safe_Release(m_pGraphic_Device);
	m_pRenderer->Clear_RenderGroup();
	Safe_Release(m_pRenderer);



}

HRESULT CToolView::Ready_WindowSize()
{
	//메인프레임을 얻어온다. 
	CMainFrame*	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if (nullptr == pMainFrame)
		return E_FAIL;

	//메인프레임의 RECT를 얻어온다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return FALSE;
}
