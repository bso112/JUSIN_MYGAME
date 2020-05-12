
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "Tool.h"
#include "ToolView.h"
#include "SideView.h"
#include "MainFrm.h"
#include "ControlView.h"
#include "VIBuffer.h"
#include "Transform.h"
#include "ModuleMgr.h"
#include "ObjMgr.h"
#include "Renderer.h"
#include "Graphic_Device.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
USING(MyGame)
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::Get_ClientRect(int _iRow, int _iCol, RECT & _outRC)
{
	CWnd* pWnd = m_Splitter.GetPane(_iRow, _iCol);
	
	if (nullptr == pWnd)
		return FALSE;

	pWnd->GetClientRect(&_outRC);

	return TRUE;
}

CWnd* CMainFrame::Get_Client(int _iRow, int _iCol)
{
	return m_Splitter.GetPane(_iRow, _iCol);
}

void CMainFrame::Invaildate(int _iRow, int _iCol)
{
	CWnd* pWnd = m_Splitter.GetPane(_iRow, _iCol);

	if (nullptr == pWnd)
		return;

	//화면을 지우고 다시그린다.
	pWnd->Invalidate(FALSE);

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;



	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (FALSE == m_Splitter.CreateStatic(this, 1, 2))
		AfxMessageBox(L"Fail to split MainFrame");

	/*
	ToolView(오브젝트를 띄우는 뷰)의 사이즈는
	백버퍼의 사이즈와 동일해야한다. 

	ToolView의 	왼쪽위를 백버퍼 좌표상으로 (0,0),
			오른쪽 아래를 (g_iWinCX, g_iWinCY)로 치기때문이다.

	만약 백버퍼사이즈보다 ToolView 사이즈가 작으면 좌표가 찌그려져서
	띄우는 그림도 찌그러지고, 마우스 좌표도 백버퍼의 좌표랑 일치하지 않아서
	마우스 클릭 좌표가 의도한대로 나오지 않을것이다.
	*/
	if (FALSE == m_Splitter.CreateView(0, 0, RUNTIME_CLASS(CToolView), CSize(g_iWinCX, g_iWinCY), pContext))
		AfxMessageBox(L"Fail to create view");

	if (FALSE == m_Splitter.CreateView(0, 1, RUNTIME_CLASS(CControlView), CSize(g_iFormViewCX, g_iFormViewCY), pContext))
		AfxMessageBox(L"Fail to create view");


	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}


void CMainFrame::OnDestroy()
{
	CFrameWnd::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_Splitter.DestroyWindow();

	if (0 != CObjMgr::Destroy_Instance())
		AfxMessageBox(L"Failed To Destroy CObjMgr");
	if (0 != CRenderer::Destroy_Instance())
		AfxMessageBox(L"Failed To Destroy CRenderer");
	if (0 != CModuleMgr::Destroy_Instance())
		AfxMessageBox(L"Failed To Destroy CModuleMgr");
	if (0 != CGraphic_Device::Destroy_Instance())
		AfxMessageBox(L"Failed To Destroy CGraphic_Device");
}
