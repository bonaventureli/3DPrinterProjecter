// Para6.cpp : implementation file
//

#include "stdafx.h"
#include "3D Printer.h"
//#include "Para6.h"

#include "3D PrinterDlg.h"

#include "typedef.h"
#include "uart.h"
#include "Delay.h"
#include "Command.h"
#include <math.h>

extern UCHAR UART_Port;
extern unsigned char CheckUart(CDialog *pDlg) ;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPara6 dialog


CPara6::CPara6(CWnd* pParent /*=NULL*/)
	: CDialog(CPara6::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPara6)
	m_check_x = FALSE;
	m_check_y = FALSE;
	//}}AFX_DATA_INIT
}


void CPara6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPara6)
	DDX_Check(pDX, IDC_CHECK_X, m_check_x);
	DDX_Check(pDX, IDC_CHECK_Y, m_check_y);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPara6, CDialog)
	//{{AFX_MSG_MAP(CPara6)
	ON_BN_CLICKED(IDC_UART, OnUart)
	ON_BN_CLICKED(IDC_FLIP_DO, OnFlipDo)
	ON_BN_CLICKED(IDC_CHECK_X, OnCheckX)
	ON_BN_CLICKED(IDC_CHECK_Y, OnCheckY)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPara6 message handlers

BOOL CPara6::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	if(UART_Port)
		SetDlgItemText(IDC_UART,_CS("Uart.Close"));
	else
		SetDlgItemText(IDC_UART,_CS("Uart.Open"));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPara6::OnUart() 
{
	// TODO: Add your control notification handler code here
	CMy3DPrinterApp* pApp;
	pApp=(CMy3DPrinterApp*)AfxGetApp();
	CPara6* pDlg=&((CMy3DPrinterDlg*)pApp->m_pMainWnd)->m_para6;
	
	CheckUart(pDlg);
}

BOOL CPara6::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) 
		return TRUE; 
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN) 
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CPara6::OnFlipDo() 
{
	// TODO: Add your control notification handler code here
	unsigned char buffer[2];

	if(m_check_x)
		buffer[0]=1;
	else
		buffer[0]=0;

	if(m_check_y)
		buffer[1]=1;
	else
		buffer[1]=0;

	Flip(buffer[0],buffer[1]);
}

void CPara6::OnCheckX() 
{
	// TODO: Add your control notification handler code here
	CButton  *pButton=(CButton *)GetDlgItem(IDC_CHECK_X);
	m_check_x=pButton->GetCheck();
}

void CPara6::OnCheckY() 
{
	// TODO: Add your control notification handler code here
	CButton  *pButton=(CButton *)GetDlgItem(IDC_CHECK_Y);
	m_check_y=pButton->GetCheck();
}

void CPara6::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}
