#pragma once



// CControlView �� ���Դϴ�.

class CControlView : public CFormView
{
	DECLARE_DYNCREATE(CControlView)

private:
	enum OPERATION { PLUS, MINUS, MULTI, DIV, END};
protected:
	CControlView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CControlView();

private:
	int			m_iResult = 0;
	OPERATION	m_eLastOperation = END;
	TCHAR		m_pinput[MAX_PATH];
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTROLVIEW };
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
	int StringToInt(TCHAR* _pCharArr);
public:
	afx_msg void OnBnClicked7btn();
	afx_msg void OnBnClickedPlusbtn();
	afx_msg void OnBnClickedMinusbtn();
	afx_msg void OnBnClickedMultibtn();
	afx_msg void OnBnClickedDivbtn();
	afx_msg void OnBnClicked8btn();
	afx_msg void OnBnClicked9btn();
	afx_msg void OnBnClicked4btn();
	afx_msg void OnBnClicked5btn();
	afx_msg void OnBnClicked6btn();
	afx_msg void OnBnClicked1btn();
	afx_msg void OnBnClicked2btn();
	afx_msg void OnBnClicked3btn();
	afx_msg void OnBnClicked0btn();

	afx_msg void OnBnClickedResultbtn();
	afx_msg void OnEnChangeEdit1();
};


