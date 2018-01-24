// Para5.cpp : implementation file
//

#include "stdafx.h"
#include "3D Printer.h"
//#include "Para5.h"
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
// CPara5 dialog


CPara5::CPara5(CWnd* pParent /*=NULL*/)
	: CDialog(CPara5::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPara5)
	m_StrUpgrateFullName = _T("PDC01.bin");
	//}}AFX_DATA_INIT
}


void CPara5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPara5)
	DDX_Control(pDX, IDC_EDIT_UPGRATE_FULLNAME, m_Edit_FullName);
	DDX_Text(pDX, IDC_EDIT_UPGRATE_FULLNAME, m_StrUpgrateFullName);
	DDV_MaxChars(pDX, m_StrUpgrateFullName, 248);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPara5, CDialog)
	//{{AFX_MSG_MAP(CPara5)
	ON_BN_CLICKED(IDC_UART, OnUart)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_UPGRATE, OnUpgrate)
	ON_EN_CHANGE(IDC_EDIT_UPGRATE_FULLNAME, OnChangeEditUpgrateFullname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPara5 message handlers

//static double float DoTime;

//DWORD dwBeginTime = ::GetTickCount() // OR timeGetTime();
//DWORD dwEndTime = ::GetTickCount();
//DWORD dwSpaceTime = dwEndTime - dwBeginTime;

extern CString ReadIniString(CString Section,CString Key);
extern void WriteIniString(CString Section,CString Key,CString Value);

static BOOL f_first=TRUE;

BOOL CPara5::OnInitDialog() 
{
	CString String;
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	IsExit=FALSE;
	IsStop=FALSE;
	pThread=NULL;
	if(f_first)
	{
		m_StrUpgrateFullName=ReadIniString("system","FirmWareName");
		if(m_StrUpgrateFullName=="")
		{
			m_StrUpgrateFullName="PDC01.bin";
			WriteIniString("system","FirmWareName",m_StrUpgrateFullName);
		}
		UpdateData(FALSE);
	}
	if(UART_Port)
		SetDlgItemText(IDC_UART,_CS("Uart.Close"));
	else
		SetDlgItemText(IDC_UART,_CS("Uart.Open"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPara5::OnUart() 
{
	// TODO: Add your control notification handler code here
	CMy3DPrinterApp* pApp;
	pApp=(CMy3DPrinterApp*)AfxGetApp();
	CPara5* pDlg=&((CMy3DPrinterDlg*)pApp->m_pMainWnd)->m_para5;
	
	CheckUart(pDlg);
}

void CPara5::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(pThread!=NULL)
	{
		IsExit=TRUE;
	}
	else 
	{
		CDialog::OnClose();
	}
}

#define UPGRADE_NO_DISK 1
#define UPGRADE_NO_FILE 2
#define UPGRADE_INVALID_FILE 3
#define UPGRADE_FAIL 4
#define UPGRADE_SUCCESS 0


UINT WINAPI Upgrate_Thread(LPVOID pParam)
{
	U8 buffer[10];
	U32 i;
	U8 f_TimeOut=1;

	CMy3DPrinterApp* pApp;
	pApp=(CMy3DPrinterApp*)AfxGetApp();
	CPara5* pDlg=&((CMy3DPrinterDlg*)pApp->m_pMainWnd)->m_para5;
	
	HWND   hwndUpGrate=GetDlgItem(pDlg->GetSafeHwnd(),IDC_UPGRATE);
	HWND   hwndUart=GetDlgItem(pDlg->GetSafeHwnd(),IDC_UART);
	
    EnableWindow(hwndUpGrate,FALSE);
	EnableWindow(hwndUart,FALSE);

	for(i=0;i<(10000/20);i++)
	{
		if(PackageReceive(buffer,1))
		{
			if(buffer[0]==UPGRADE_SUCCESS)
			{
				pDlg->MessageBox(_CS("WarningSystem.FirmWareUpgrateSuccess"),_CS("WarningSystem.Title"),MB_OK);
				f_TimeOut=0;
				break;
			}
			if(buffer[0]==UPGRADE_FAIL)
			{
				pDlg->MessageBox(_CS("WarningSystem.FirmWareUpgrateFail"),_CS("WarningSystem.Title"),MB_OK);
				f_TimeOut=0;
				break;
			}
			if(buffer[0]==UPGRADE_NO_DISK)
			{
				pDlg->MessageBox(_CS("WarningSystem.NotFindDisk"),_CS("WarningSystem.Title"),MB_OK);
				f_TimeOut=0;
				break;
			}
			if(buffer[0]==UPGRADE_NO_FILE)
			{
				pDlg->MessageBox(_CS("WarningSystem.NotFindFile"),_CS("WarningSystem.Title"),MB_OK);
				f_TimeOut=0;
				break;
			}
			if(buffer[0]==UPGRADE_INVALID_FILE)
			{
				pDlg->MessageBox(_CS("WarningSystem.InvalidFirmWare"),_CS("WarningSystem.Title"),MB_OK);
				f_TimeOut=0;
				break;
			}
		}
		Sleep(20);
	}
	if(f_TimeOut)
	     pDlg->MessageBox(_CS("WarningSystem.UpgrateTimeOut"),_CS("WarningSystem.Title"),MB_OK);

    EnableWindow(hwndUpGrate,TRUE);
	EnableWindow(hwndUart,TRUE);
	pDlg->pThread=NULL;
	return 1;
}

#define PC_CMD_UPGRATE  14

void CPara5::OnUpgrate() 
{
	// TODO: Add your control notification handler code here
	/*
	if(UART_Port)
	{
		FirmWareUpGrate();
	}
	else
	{
		MessageBox(_CS("WarningUart.NotOpen"),_CS("WarningUart.Title"),MB_OK);
	}
	*/

	U8 buffer[250];
	U8 Length;
	int Result;
    UpdateData(TRUE);
    if(m_StrUpgrateFullName!="")
	WriteIniString("system","FirmWareName",m_StrUpgrateFullName);

	if(UART_Port==0)
	{
		MessageBox(_CS("WarningUart.NotOpen"),_CS("WarningUart.Title"),MB_OK);
		return;
	}
	if(m_StrUpgrateFullName=="")
	{
		MessageBox(_CS("WarningSystem.InvalidFileName"),_CS("WarningSystem.Title"),MB_OK);
		return;
	}
	Length=m_StrUpgrateFullName.GetLength();
	
	memcpy(buffer,m_StrUpgrateFullName.GetBuffer(Length),Length);
	buffer[Length]=0;

	Result=FirmWareUpGrate(buffer,Length+1);

	if(Result)
		pThread=AfxBeginThread((AFX_THREADPROC)Upgrate_Thread,NULL);
	else if(Result<0)
		MessageBox(_CS("WarningSystem.FirmWareUpgrateFail"),_CS("WarningSystem.Title"),MB_OK);
}

void CPara5::OnChangeEditUpgrateFullname() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//UpdateData(FALSE);
}

BOOL CPara5::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) 
		return TRUE; 
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN) 
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}
