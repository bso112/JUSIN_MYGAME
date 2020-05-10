// ControlView.cpp : 구현 파일입니다.
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


// CControlView 진단입니다.

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


// CControlView 메시지 처리기입니다.



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
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CCalculatorView::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int tmp = 1;
}
