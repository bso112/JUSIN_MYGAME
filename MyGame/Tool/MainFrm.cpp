
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "Tool.h"
#include "ToolView.h"
#include "SideView.h"
#include "MainFrm.h"
#include "ControlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
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

	if (FALSE == m_Splitter.CreateView(0, 0, RUNTIME_CLASS(CToolView), CSize(400, 600), pContext))
		AfxMessageBox(L"Fail to create view");

	if (FALSE == m_Splitter.CreateView(0, 1, RUNTIME_CLASS(CControlView), CSize(400, 600), pContext))
		AfxMessageBox(L"Fail to create view");


	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
