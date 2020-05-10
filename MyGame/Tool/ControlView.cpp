// ControlView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "ControlView.h"
#include "ObjMgr.h"
#include "Terrain.h"
#include "Transform.h"
#include "MainFrm.h"
#include "Texture.h"

// CControlView

USING(MyGame)
IMPLEMENT_DYNCREATE(CControlView, CFormView)

CControlView::CControlView()
	: CFormView(IDD_CONTROLVIEW1)
	, m_iTileNumX(0)
	, m_iTileNumY(0)
{
}

CControlView::~CControlView()
{
}

void CControlView::DoDataExchange(CDataExchange* pDX)
{
	DDX_Text(pDX, IDC_EDIT1, m_iTileNumX);
	DDX_Text(pDX, IDC_EDIT2, m_iTileNumY);
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
}

HRESULT CControlView::Initialize_Tile()
{
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	

	for (int i = 0; i < m_iTileNumY; ++i)
	{
		for (int j = 0; j < m_iTileNumX; ++j)
		{
			CGameObject* pTile = pObjMgr->Add_GO_To_Layer(L"Tile", SCENE_STATIC, L"Tile", SCENE_STATIC);
			
			((CTerrain*)pTile)->Set_Texture(m_Combo.GetCurSel());

			CModule* pModule = pTile->Get_Module(L"Transform");
			if (!pModule)
				return E_FAIL;

			((CTransform*)pModule)->Set_Position(Vector3((TILECX >> 1) + TILECX * j, (TILECY >> 1) + i * TILECY));
			
			
			
		}
	}

	return S_OK;

}

void CControlView::CreateTile()
{	
	//현재 연결된 변수를 가져온다.
	UpdateData(TRUE);

	//가져온 변수를 이용해 타일을 그린다.
	if (FAILED(Initialize_Tile()))
		return;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if (nullptr == pMainFrame)
		return;
	//화면을 다시그린다.(메시지 발생시키기)
	pMainFrame->Invaildate(0, 0);

	//화면을 지우고 다시그린다.
	Invalidate(FALSE);

	
	




}

BEGIN_MESSAGE_MAP(CControlView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CControlView::CreateTile)
END_MESSAGE_MAP()


// CControlView 진단입니다.

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


// CControlView 메시지 처리기입니다.






void CControlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	TCHAR	szString[MAX_PATH] = L"";
	for (size_t i = 1; i < 41; ++i)
	{
		wsprintf(szString, L"Tile%d", i);
		m_Combo.AddString(szString);
	}
	m_Combo.SetCurSel(0);
	m_Combo.GetCurSel();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
