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
	//���� ����� ������ �����´�.
	UpdateData(TRUE);

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

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}
