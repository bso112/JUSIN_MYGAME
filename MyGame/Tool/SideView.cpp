// SideView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "SideView.h"


// CSideView

IMPLEMENT_DYNCREATE(CSideView, CView)

CSideView::CSideView()
{

}

CSideView::~CSideView()
{
}

BEGIN_MESSAGE_MAP(CSideView, CView)
END_MESSAGE_MAP()


// CSideView �׸����Դϴ�.

void CSideView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CSideView �����Դϴ�.

#ifdef _DEBUG
void CSideView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CSideView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSideView �޽��� ó�����Դϴ�.
