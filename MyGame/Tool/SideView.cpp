// SideView.cpp : 구현 파일입니다.
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


// CSideView 그리기입니다.

void CSideView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CSideView 진단입니다.

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


// CSideView 메시지 처리기입니다.
