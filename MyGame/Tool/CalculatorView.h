#pragma once



// CCalculatorView 폼 뷰입니다.

class CCalculatorView : public CFormView
{
	DECLARE_DYNCREATE(CCalculatorView)

private:
	enum OPERATION { OP_PLUS, OP_MINUS, OP_MUL, OP_DIV, OP_END};
protected:
	CCalculatorView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CCalculatorView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATORVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEnChangeEdit1();

public:
	int StringToInt(TCHAR * _pCharArr);
private:
	int		m_iOperand = 0;
	OPERATION	m_eOperation = OP_END;

public:
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonMulti();
	afx_msg void OnBnClickedButtonDiv();
	afx_msg void OnBnClickedButtonEqul();
	afx_msg void OnBnClickedButtonClear();
};


