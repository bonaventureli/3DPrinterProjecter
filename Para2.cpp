// Para2.cpp : implementation file
//

#include "stdafx.h"
#include "3D Printer.h"
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
// CPara2 dialog


CPara2::CPara2(CWnd* pParent /*=NULL*/)
	: CDialog(CPara2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPara2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPara2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPara2)
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPara2, CDialog)
	//{{AFX_MSG_MAP(CPara2)
	ON_BN_CLICKED(IDC_INPUT_SOURCE, OnInputSource)
	ON_BN_CLICKED(IDC_UART, OnUart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPara2 message handlers

void CPara2::OnInputSource() 
{
	// TODO: Add your control notification handler code here
	unsigned char Index;
	Index=m_ComboBox1.GetCurSel();
	
	
	if(UART_Port==0)
	{
		MessageBox(_CS("WarningUart.NotOpen"),_CS("WarningUart.Title"),MB_OK);
		return;
	}
	
	InputSource(Index);
}

static BOOL f_first=TRUE;

BOOL CPara2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	if(f_first)
	{
		UpdateData(FALSE);
		m_ComboBox1.SetCurSel(-1);
		m_ComboBox1.AddString(" HDMI");
		m_ComboBox1.AddString(" VGA");
		m_ComboBox1.SetCurSel(0);
		UpdateData(TRUE);
		f_first=FALSE;
	}

	if(UART_Port)
		SetDlgItemText(IDC_UART,_CS("Uart.Close"));
	else
		SetDlgItemText(IDC_UART,_CS("Uart.Open"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPara2::OnUart() 
{
	// TODO: Add your control notification handler code here
  
	CMy3DPrinterApp* pApp;
	pApp=(CMy3DPrinterApp*)AfxGetApp();
	CPara2* pDlg=&((CMy3DPrinterDlg*)pApp->m_pMainWnd)->m_para2;
	
	CheckUart(pDlg);

}

BOOL CPara2::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) 
		return TRUE; 
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN) 
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}
