#pragma once



// CControlView �� ���Դϴ�.

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
	int m_iTileNumX;
	int m_iTileNumY;

private:
	HRESULT Initialize_Tile();
public:
	afx_msg	void CreateTile();

};


