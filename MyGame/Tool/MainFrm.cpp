
// MainFrm.cpp : CMainFrame Ŭ������ ����
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
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
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

	//ȭ���� ����� �ٽñ׸���.
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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return TRUE;
}

// CMainFrame ����

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


// CMainFrame �޽��� ó����



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	if (FALSE == m_Splitter.CreateStatic(this, 1, 2))
		AfxMessageBox(L"Fail to split MainFrame");

	if (FALSE == m_Splitter.CreateView(0, 0, RUNTIME_CLASS(CToolView), CSize(400, 600), pContext))
		AfxMessageBox(L"Fail to create view");

	if (FALSE == m_Splitter.CreateView(0, 1, RUNTIME_CLASS(CControlView), CSize(400, 600), pContext))
		AfxMessageBox(L"Fail to create view");


	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
