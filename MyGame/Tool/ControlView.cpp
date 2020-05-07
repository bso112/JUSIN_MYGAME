// ControlView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "ControlView.h"


// CControlView

IMPLEMENT_DYNCREATE(CControlView, CFormView)

CControlView::CControlView()
	: CFormView(IDD_CONTROLVIEW)
{
	ZeroMemory(m_pinput, sizeof(m_pinput));
}

CControlView::~CControlView()
{
}

void CControlView::DoDataExchange(CDataExchange* pDX)
{
	DDX_Text(pDX, IDC_RESULT_TEXT, m_iResult);
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CControlView, CFormView)
	ON_BN_CLICKED(IDC_7BTN, &CControlView::OnBnClicked7btn)
	ON_BN_CLICKED(IDC_PLUSBTN, &CControlView::OnBnClickedPlusbtn)
	ON_BN_CLICKED(IDC_MINUSBTN, &CControlView::OnBnClickedMinusbtn)
	ON_BN_CLICKED(IDC_MULTIBTN, &CControlView::OnBnClickedMultibtn)
	ON_BN_CLICKED(IDC_DIVBTN, &CControlView::OnBnClickedDivbtn)
	ON_BN_CLICKED(IDC_8BTN, &CControlView::OnBnClicked8btn)
	ON_BN_CLICKED(IDC_9BTN, &CControlView::OnBnClicked9btn)
	ON_BN_CLICKED(IDC_4BTN, &CControlView::OnBnClicked4btn)
	ON_BN_CLICKED(IDC_5BTN, &CControlView::OnBnClicked5btn)
	ON_BN_CLICKED(IDC_6BTN, &CControlView::OnBnClicked6btn)
	ON_BN_CLICKED(IDC_1BTN, &CControlView::OnBnClicked1btn)
	ON_BN_CLICKED(IDC_2BTN, &CControlView::OnBnClicked2btn)
	ON_BN_CLICKED(IDC_3BTN, &CControlView::OnBnClicked3btn)
	ON_BN_CLICKED(IDC_0BTN, &CControlView::OnBnClicked0btn)
	ON_BN_CLICKED(IDC_RESULTBTN, &CControlView::OnBnClickedResultbtn)

	ON_EN_CHANGE(IDC_RESULT_TEXT, &CControlView::OnEnChangeEdit1)
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



int CControlView::StringToInt(TCHAR * _pCharArr)
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

void CControlView::OnBnClicked7btn()
{
	lstrcat(m_pinput, L"7");
	SetDlgItemText(IDC_RESULT_TEXT,m_pinput);
}


void CControlView::OnBnClickedPlusbtn()
{
	m_iResult += StringToInt(m_pinput);
	ZeroMemory(m_pinput, sizeof(m_pinput));
	m_eLastOperation = PLUS;
}


void CControlView::OnBnClickedMinusbtn()
{
	if(m_iResult == 0)
		m_iResult = StringToInt(m_pinput);
	else
		m_iResult -= StringToInt(m_pinput);

	ZeroMemory(m_pinput, sizeof(m_pinput));
	m_eLastOperation = MINUS;
}


void CControlView::OnBnClickedMultibtn()
{
	if (m_iResult == 0)
		m_iResult = StringToInt(m_pinput);
	else
		m_iResult *= StringToInt(m_pinput);

	ZeroMemory(m_pinput, sizeof(m_pinput));
	m_eLastOperation = MULTI;
}


void CControlView::OnBnClickedDivbtn()
{
	if (m_iResult == 0)
		return;
	m_iResult /= StringToInt(m_pinput);
	ZeroMemory(m_pinput, sizeof(m_pinput));
	m_eLastOperation = DIV;
}



void CControlView::OnBnClicked8btn()
{
	lstrcat(m_pinput, L"8");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
}


void CControlView::OnBnClicked9btn()
{

	lstrcat(m_pinput, L"9");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
}


void CControlView::OnBnClicked4btn()
{

	lstrcat(m_pinput, L"4");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
}


void CControlView::OnBnClicked5btn()
{

	lstrcat(m_pinput, L"5");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
}


void CControlView::OnBnClicked6btn()
{

	lstrcat(m_pinput, L"6");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
}


void CControlView::OnBnClicked1btn()
{

	lstrcat(m_pinput, L"1");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
}


void CControlView::OnBnClicked2btn()
{

	lstrcat(m_pinput, L"2");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
}


void CControlView::OnBnClicked3btn()
{

	lstrcat(m_pinput, L"3");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
}


void CControlView::OnBnClicked0btn()
{

	lstrcat(m_pinput, L"0");
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
}




void CControlView::OnBnClickedResultbtn()
{
	switch (m_eLastOperation)
	{
	case CControlView::PLUS:
		OnBnClickedPlusbtn();
		break;
	case CControlView::MINUS:
		OnBnClickedMinusbtn();
		break;
	case CControlView::MULTI:
		OnBnClickedMultibtn();
		break;
	case CControlView::DIV:
		OnBnClickedDivbtn();
		break;
	case CControlView::END:
		break;
	default:
		break;
	}
	wsprintf(m_pinput, L"%d", m_iResult);
	SetDlgItemText(IDC_RESULT_TEXT, m_pinput);
	m_eLastOperation = END;
	ZeroMemory(m_pinput, sizeof(m_pinput));
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CControlView::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CFormView::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int tmp = 1;
}
