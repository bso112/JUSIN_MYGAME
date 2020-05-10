#pragma once
#include "afxwin.h"
#include "Base.h"
// CControlView �� ���Դϴ�.
BEGIN(MyGame)
class CGameObject;
END


class CControlView : public CFormView
{
	DECLARE_DYNCREATE(CControlView)

protected:
	CControlView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CControlView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTROLVIEW1 };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
private:
	int m_iTileNumX = 0;
	int m_iTileNumY = 0;
	MyGame::CGameObject* m_pSelected = nullptr;

public:
	int Get_TileNumX() { UpdateData(TRUE); return m_iTileNumX; }
	void Set_Selected(MyGame::CGameObject* pSelected) { m_pSelected = pSelected; }
public:
	afx_msg	void CreateTile();
private:
	HRESULT Initialize_Tile();


	CComboBox m_Combo;
	virtual void OnInitialUpdate();
public:
	afx_msg void OnCbnSelchangeCombo1();
};


