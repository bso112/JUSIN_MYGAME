// ControlView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "CalculatorView.h"


// CControlView

IMPLEMENT_DYNCREATE(CCalculatorView, CFormView)

CCalculatorView::CCalculatorView()
	: CFormView(IDD_CONTROLVIEW)
{
	ZeroMemory(m_pinput, sizeof(m_pinput));
}

CCalculatorView::~CCalculatorView()
{
}

void CCalculatorView::DoDataExchange(CDataExchange* pDX)
{
	DDX_Text(pDX, IDC_RESULT_TEXT, m_iResult);
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCalculatorView, CFormView)
	ON_BN_CLICKED(IDC_7BTN, &CCalculatorView::OnBnClicked7btn)
	ON_BN_CLICKED(IDC_PLUSBTN, &CCalculatorView::OnBnClickedPlusbtn)
	ON_BN_CLICKED(IDC_MINUSBTN, &CCalculatorView::OnBnClickedMinusbtn)
	ON_BN_CLICKED(IDC_MULTIBTN, &CCalculatorView::OnBnClickedMultibtn)
	ON_BN_CLICKED(IDC_DIVBTN, &CCalculatorView::OnBnClickedDivbtn)
	ON_BN_CLICKED(IDC_8BTN, &CCalculatorView::OnBnClicked8btn)
	ON_BN_CLICKED(IDC_9BTN, &CCalculatorView::OnBnClicked9btn)
	ON_BN_CLICKED(IDC_4BTN, &CCalculatorView::OnBnClicked4btn)
	ON_BN_CLICKED(IDC_5BTN, &CCalculatorView::OnBnClicked5btn)
	ON_BN_CLICKED(IDC_6BTN, &CCalculatorView::OnBnClicked6btn)
	ON_BN_CLICKED(IDC_1BTN, &CCalculatorView::OnBnClicked1btn)
	ON_BN_CLICKED(IDC_2BTN, &CCalculatorView::OnBnClicked2btn)
	ON_BN_CLICKED(IDC_3BTN, &CCalculatorView::OnBnClicked3btn)
	ON_BN_CLICKED(IDC_0BTN, &CCalculatorView::OnBnClicked0btn)
	ON_BN_CLICKED(IDC_RESULTBTN, &CCalculatorView::OnBnClickedResultbtn)

	ON_EN_CHANGE(IDC_RESULT_TEXT, &CCalculatorView::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CControlView �����Դϴ�.

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


// CControlView �޽��� ó�����Դϴ�.



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



void CCalculatorView::OnBnClickedPlusbtn()
{
	m_iResult += StringToInt(m_pinput);
	ZeroMemory(m_pinput, sizeof(m_pinput));
	m_eLastOperation = OP_PLUS;
}


void CCalculatorView::OnBnClickedMinusbtn()
{
	if(m_iResult == 0)
		m_iResult = StringToInt(m_pinput);
	else
		m_iResult -= StringToInt(m_pinput);

	ZeroMemory(m_pinput, sizeof(m_pinput));
	m_eLastOperation = OP_MINUS;
}


void CCalculatorView::OnBnClickedMultibtn()
{
	if (m_iResult == 0)
		m_iResult = StringToInt(m_pinput);
	else
		m_iResult *= StringToInt(m_pinput);

	ZeroMemory(m_pinput, sizeof(m_pinput));
	m_eLastOperation = OP_MULTI;
}


void CCalculatorView::OnBnClickedDivbtn()
{
	int operand = StringToInt(m_pinput);
	
	if (operand == 0)
		return;
	
	if (m_iResult == 0)
		m_iResult = operand;
	else
		m_iResult /= operand;
	
	ZeroMemory(m_pinput, sizeof(m_pinput));
	m_eLastOperation = OP_DIV;
}



void CCalculatorView::OnBnClicked7btn()
{
	lstrcat(m_pinput, L"7");
	SetDlgItemText(IDC_RESULT_TEXT,m_pinput);
}
void CCalculatorView::OnBnClicked8btn()
{
	lstrcat(m_pinput, L"8");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);

}


void CCalculatorView::OnBnClicked9btn()
{

	lstrcat(m_pinput, L"9");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
}


void CCalculatorView::OnBnClicked4btn()
{

	lstrcat(m_pinput, L"4");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
}


void CCalculatorView::OnBnClicked5btn()
{

	lstrcat(m_pinput, L"5");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
}


void CCalculatorView::OnBnClicked6btn()
{

	lstrcat(m_pinput, L"6");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
}


void CCalculatorView::OnBnClicked1btn()
{

	lstrcat(m_pinput, L"1");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
}


void CCalculatorView::OnBnClicked2btn()
{

	lstrcat(m_pinput, L"2");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
}


void CCalculatorView::OnBnClicked3btn()
{

	lstrcat(m_pinput, L"3");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
}


void CCalculatorView::OnBnClicked0btn()
{

	lstrcat(m_pinput, L"0");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
}




void CCalculatorView::OnBnClickedResultbtn()
{
	switch (m_eLastOperation)
	{
	case CCalculatorView::OP_PLUS:
		OnBnClickedPlusbtn();
		break;
	case CCalculatorView::OP_MINUS:
		OnBnClickedMinusbtn();
		break;
	case CCalculatorView::OP_MULTI:
		OnBnClickedMultibtn();
		break;
	case CCalculatorView::OP_DIV:
		OnBnClickedDivbtn();
		break;
	case CCalculatorView::OP_END:
		break;
	default:
		break;
	}
	wsprintf(m_pinput, L"%d", m_iResult);
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
	m_eLastOperation = OP_END;
	ZeroMemory(m_pinput, sizeof(m_pinput));
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CCalculatorView::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CFormView::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int tmp = 1;
}
