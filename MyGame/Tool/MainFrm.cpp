
// MainFrm.cpp : CMainFrame Ŭ������ ����
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

CWnd* CMainFrame::Get_Client(int _iRow, int _iCol)
{
	return m_Splitter.GetPane(_iRow, _iCol);
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

	/*
	ToolView(������Ʈ�� ���� ��)�� �������
	������� ������� �����ؾ��Ѵ�. 

	ToolView�� 	�������� ����� ��ǥ������ (0,0),
			������ �Ʒ��� (g_iWinCX, g_iWinCY)�� ġ�⶧���̴�.

	���� ����ۻ������ ToolView ����� ������ ��ǥ�� ��׷�����
	���� �׸��� ��׷�����, ���콺 ��ǥ�� ������� ��ǥ�� ��ġ���� �ʾƼ�
	���콺 Ŭ�� ��ǥ�� �ǵ��Ѵ�� ������ �������̴�.
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
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
