// CalculatorView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "CalculatorView.h"


// CCalculatorView

IMPLEMENT_DYNCREATE(CCalculatorView, CFormView)

CCalculatorView::CCalculatorView()
	: CFormView(IDD_CALCULATORVIEW)
	//, m_iOperand(0)
{

}

CCalculatorView::~CCalculatorView()
{
}

void CCalculatorView::DoDataExchange(CDataExchange* pDX)
{
	//DDX_Text(pDX, IDC_EDIT1, m_iOperand);
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCalculatorView, CFormView)
	ON_EN_CHANGE(IDC_EDIT1, &CCalculatorView::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON_7, &CCalculatorView::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CCalculatorView::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CCalculatorView::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_4, &CCalculatorView::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CCalculatorView::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CCalculatorView::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_1, &CCalculatorView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CCalculatorView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CCalculatorView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_0, &CCalculatorView::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CCalculatorView::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CCalculatorView::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_MULTI, &CCalculatorView::OnBnClickedButtonMulti)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CCalculatorView::OnBnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_EQUL, &CCalculatorView::OnBnClickedButtonEqul)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCalculatorView::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CCalculatorView �����Դϴ�.

#ifdef _DEBUG
void CCalculatorView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCalculatorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCalculatorView �޽��� ó�����Դϴ�.


void CCalculatorView::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CFormView::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CCalculatorView::OnBnClickedButton7()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str);

	if (str == L"0")
		str = L"";
	SetDlgItemText(IDC_EDIT1, str + L"7");

}


void CCalculatorView::OnBnClickedButton8()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str);

	if (str == L"0")
		str = L"";
	SetDlgItemText(IDC_EDIT1, str + L"8");
}


void CCalculatorView::OnBnClickedButton9()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str);

	if (str == L"0")
		str = L"";
	SetDlgItemText(IDC_EDIT1, str + L"9");
}


void CCalculatorView::OnBnClickedButton4()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str);

	if (str == L"0")
		str = L"";
	SetDlgItemText(IDC_EDIT1, str + L"4");
}


void CCalculatorView::OnBnClickedButton5()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str);

	if (str == L"0")
		str = L"";
	SetDlgItemText(IDC_EDIT1, str + L"5");
}


void CCalculatorView::OnBnClickedButton6()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str);

	if (str == L"0")
		str = L"";
	SetDlgItemText(IDC_EDIT1, str + L"6");
}


void CCalculatorView::OnBnClickedButton1()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str);

	if (str == L"0")
		str = L"";
	SetDlgItemText(IDC_EDIT1, str + L"1");
}


void CCalculatorView::OnBnClickedButton2()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str);

	if (str == L"0")
		str = L"";
	SetDlgItemText(IDC_EDIT1, str + L"2");
}


void CCalculatorView::OnBnClickedButton3()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str);

	if (str == L"0")
		str = L"";
	SetDlgItemText(IDC_EDIT1, str + L"3");
}


void CCalculatorView::OnBnClickedButton0()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str);

	if (str == L"0")
		str = L"";
	SetDlgItemText(IDC_EDIT1, str + L"0");
}


void CCalculatorView::OnBnClickedButtonPlus()
{
	m_iOperand = GetDlgItemInt(IDC_EDIT1);
	SetDlgItemText(IDC_EDIT1, L"0");
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_eOperation = OP_PLUS;
}


void CCalculatorView::OnBnClickedButtonMinus()
{
	m_iOperand = GetDlgItemInt(IDC_EDIT1);
	SetDlgItemText(IDC_EDIT1, L"0");
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_eOperation = OP_MINUS;
}


void CCalculatorView::OnBnClickedButtonMulti()
{
	m_iOperand = GetDlgItemInt(IDC_EDIT1);
	SetDlgItemText(IDC_EDIT1, L"0");
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_eOperation = OP_MUL;
}


void CCalculatorView::OnBnClickedButtonDiv()
{
	m_iOperand = GetDlgItemInt(IDC_EDIT1);
	SetDlgItemText(IDC_EDIT1, L"0");
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_eOperation = OP_DIV;
}


void CCalculatorView::OnBnClickedButtonEqul()
{
	int operand2 = GetDlgItemInt(IDC_EDIT1);
	int iResult = 0;
	switch (m_eOperation)
	{
	case CCalculatorView::OP_PLUS:
		iResult = m_iOperand + operand2;
		break;
	case CCalculatorView::OP_MINUS:
		iResult = m_iOperand - operand2;
		break;
	case CCalculatorView::OP_MUL:
		iResult = m_iOperand * operand2;
		break;
	case CCalculatorView::OP_DIV:
		if (m_iOperand != 0)
			iResult = m_iOperand / operand2;
		else
			iResult = 0;
		break;
	case CCalculatorView::OP_END:
		break;
	default:
		break;
	}

	CString str;
	str.Format(L"%d", iResult);

	SetDlgItemText(IDC_EDIT1, str);
	m_eOperation = OP_END;

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CCalculatorView::OnBnClickedButtonClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

int CCalculatorView::StringToInt(TCHAR * _pCharArr)
{
	TCHAR* tmp = _pCharArr;
	int num = 0;
	int figure = 0;
	while (*tmp != '\0')
	{
		num += (*tmp - '0') * (int)pow(10, figure);
		++tmp;
		++figure;
	}

	return num;
}
