// 3D PrinterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "3D Printer.h"
#include "3D PrinterDlg.h"

#include "typedef.h"
#include "uart.h"
#include "Delay.h"
#include "Command.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UCHAR UART_Port=0;
UCHAR u_Serial[10]={0};
unsigned long BaudRate[]={9600,115200};

#define MAIN_DIALOG_TITLE1 "3D Printer"
U32 FirmwareVersion=0x0001000B;//1.0.11

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3DPrinterDlg dialog

CMy3DPrinterDlg::CMy3DPrinterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy3DPrinterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy3DPrinterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy3DPrinterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy3DPrinterDlg)
	DDX_Control(pDX, IDC_TAB1, m_tab);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy3DPrinterDlg, CDialog)
	//{{AFX_MSG_MAP(CMy3DPrinterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CString ReadIniString(CString Section,CString Key)
{
	//GetPrivateProfileSectionNames
	//GetPrivateProfileSection
	CString  inipath;
    CString  Value;
	char pathtemp[MAX_PATH];
	Value="";
	GetCurrentDirectory(MAX_PATH,pathtemp);
	inipath=pathtemp;
	inipath = inipath + "\\3D.ini";
	GetPrivateProfileString((LPCTSTR)Section,(LPCTSTR)Key,(LPCTSTR)Value,Value.GetBuffer(MAX_PATH),MAX_PATH,(LPCTSTR)inipath);
	return Value;
}

void WriteIniString(CString Section,CString Key,CString Value)
{
	CString  inipath;
    //CString  Value;
	char pathtemp[MAX_PATH];
	//Value="";
	GetCurrentDirectory(MAX_PATH,pathtemp);
	inipath=pathtemp;
	inipath = inipath + "\\3D.ini";
	WritePrivateProfileString((LPCTSTR)Section,(LPCTSTR)Key,(LPCTSTR)Value,(LPCTSTR)inipath);
}

typedef struct tagKeyAndValue{
	CString Key;
	CString Value;
}KeyAndValue;

int GetKeyAndValue(CString Section,KeyAndValue* pKeyAndValue)
{
	//GetPrivateProfileSectionNames
	//GetPrivateProfileSection
	CString strtemp;
	int posit,i;
	i=0;
	CString  inipath;
	char pathtemp[MAX_PATH];
	char KeyAndValueBuffer[10*MAX_PATH];
	char *str=KeyAndValueBuffer;
	
	GetCurrentDirectory(MAX_PATH,pathtemp);
	inipath=pathtemp;
	inipath = inipath + "\\3D.ini";
	GetPrivateProfileSection((LPCTSTR)Section,KeyAndValueBuffer,MAX_PATH,(LPCTSTR)inipath);
	
	while(*str!=0) //str为lpReturnedString返回的字符串
	{        
		strtemp = str;
		posit=strtemp.Find('=',0);
		pKeyAndValue[i].Key=strtemp.Left(posit);
		pKeyAndValue[i].Value=strtemp.Right(strtemp.GetLength()-posit-1);
		i++;
		str += strtemp.GetLength()+1;
	}
	return i;
}

/////////////////////////////////////////////////////////////////////////////
// CMy3DPrinterDlg message handlers

BOOL CMy3DPrinterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	_CWndCS(this);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CRect rc,rect,Rect,ScreenRect;
	KeyAndValue   s_KeyAndValue[255];
	int DlgCnt,i,j=0;
    CString DlgName[5];

	DlgName[0]=_CS("Tab.Led");//"LED控制";
	DlgName[1]=_CS("Tab.InputSource");//"输入源";
	DlgName[2]=_CS("Tab.Temperature");//"温度";
	DlgName[3]=_CS("Tab.Flip");//"图像镜像";
	DlgName[4]=_CS("Tab.System");//"系统";

	DlgCnt=GetKeyAndValue("dialog",s_KeyAndValue);

	//设置IDC_TAB1为父窗口
	m_para1.Create(IDD_DIALOG1,GetDlgItem(IDC_TAB1));
	m_para2.Create(IDD_DIALOG2,GetDlgItem(IDC_TAB1));
	m_para3.Create(IDD_DIALOG3,GetDlgItem(IDC_TAB1));
	m_para5.Create(IDD_DIALOG5,GetDlgItem(IDC_TAB1));
	m_para6.Create(IDD_DIALOG6,GetDlgItem(IDC_TAB1));

	//添加选项卡名称
	for(i=0;i<DlgCnt;i++)
	{
		if(s_KeyAndValue[i].Key=="dlg1" && s_KeyAndValue[i].Value=="true")
		{
			pDialog[j] = &m_para1;
			m_tab.InsertItem(j,DlgName[0]);
		}
		else if(s_KeyAndValue[i].Key=="dlg2" && s_KeyAndValue[i].Value=="true")
		{
			pDialog[j] = &m_para2;
			m_tab.InsertItem(j,DlgName[1]);
		}
		else if(s_KeyAndValue[i].Key=="dlg3" && s_KeyAndValue[i].Value=="true")
		{
			pDialog[j] = &m_para3;
			m_tab.InsertItem(j,DlgName[2]);
		}
		else if(s_KeyAndValue[i].Key=="dlg4" && s_KeyAndValue[i].Value=="true")
		{
			pDialog[j] = &m_para6;
			m_tab.InsertItem(j,DlgName[3]);
		}		
		else if(s_KeyAndValue[i].Key=="dlg5" && s_KeyAndValue[i].Value=="true")
		{
			pDialog[j] = &m_para5;
			m_tab.InsertItem(j,DlgName[4]);
		}
		else
			continue;
		j++;
	}

	if(m_tab.GetItemCount()<=0)
	{
		m_tab.InsertItem(0,DlgName[0]);
		m_tab.InsertItem(1,DlgName[1]);
		m_tab.InsertItem(2,DlgName[2]);
		m_tab.InsertItem(3,DlgName[3]);
		m_tab.InsertItem(4,DlgName[4]);
		
		//把对话框对象指针保存起来
		pDialog[0] = &m_para1;
		pDialog[1] = &m_para2;
		pDialog[2] = &m_para3;
		pDialog[3] = &m_para6;
		pDialog[4] = &m_para5;
	}

	CString String;
	 GetWindowText(String);

	//保存当前选择
	String=MAIN_DIALOG_TITLE1;
	SetWindowText(String);
    m_CurSelTab = 0;
//---------------------------------------------
	 //m_CurSelTab = m_tab.GetCurSel();
	 pDialog[m_CurSelTab]->GetClientRect(&rc);
	 
	 GetWindowRect(&ScreenRect);
	 
	 rc.top += 25;
	 rc.left +=8;
	 rc.bottom +=25;
	 rc.right +=8;
	 m_tab.GetClientRect(&rect);
	 
	 //rect.top +=5;
	 rect.bottom=rect.top+rc.bottom+8;
	 rect.right=rect.left+rc.right+8;
	 
	 pDialog[m_CurSelTab]->MoveWindow(&rc);
	 m_tab.MoveWindow(&rect);
	 
	 GetClientRect(&Rect);
	 
	 Rect.left=ScreenRect.left;
	 Rect.top=ScreenRect.top;
	 
	 Rect.bottom=Rect.top+rect.bottom+35;
	 Rect.right=Rect.left+rect.right+8;
	 
	MoveWindow(&Rect);
//------------------------------------------
	//设置默认的选项卡
     m_tab.SetCurSel(m_CurSelTab);

	 for(i=0;i<m_tab.GetItemCount();i++)
		pDialog[i]->ShowWindow(SW_HIDE);
     //显示初始页面
	pDialog[0]->ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy3DPrinterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy3DPrinterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy3DPrinterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMy3DPrinterDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CRect rc,rect,Rect,ScreenRect;
	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	m_CurSelTab = m_tab.GetCurSel();
	pDialog[m_CurSelTab]->GetClientRect(&rc);

	GetWindowRect(&ScreenRect);

	rc.top += 25;
	rc.left +=8;
	rc.bottom +=25;
	rc.right +=8;
	m_tab.GetClientRect(&rect);

	//rect.top +=5;
	rect.bottom=rect.top+rc.bottom+8;
	rect.right=rect.left+rc.right+8;

    pDialog[m_CurSelTab]->MoveWindow(&rc);
	m_tab.MoveWindow(&rect);

	GetClientRect(&Rect);

	Rect.left=ScreenRect.left;
	Rect.top=ScreenRect.top;

	Rect.bottom=Rect.top+rect.bottom+35;
	Rect.right=Rect.left+rect.right+8;

	MoveWindow(&Rect);
	
    pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);
	pDialog[m_CurSelTab]->OnInitDialog();
	
	*pResult = 0;
}

UCHAR EnumSerialEx(UCHAR *m_Port)
{
	HKEY hKey;
	CString str;
	LPCTSTR data_Set="HARDWARE\\DEVICEMAP\\SERIALCOMM\\";
	long ret0 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_READ, &hKey);
	if(ret0 != ERROR_SUCCESS)
	{
		return -1;
	}
	int i = 1;				//put the port index from 1;
	CHAR Name[50];
	UCHAR szPortName[50];
	LONG Status;
	DWORD dwIndex = 0;
	DWORD dwName;
	DWORD dwSizeofPortName;
	DWORD Type;
	dwName = sizeof(Name);
	dwSizeofPortName = sizeof(szPortName);
	do
	{
		Status = RegEnumValue(hKey, dwIndex++, Name, &dwName, NULL, &Type,
			szPortName, &dwSizeofPortName);
		if((Status == ERROR_SUCCESS)||(Status == ERROR_MORE_DATA))
		{
			str = CString(szPortName).Mid(3);;       // 串口字符串保存
			m_Port[i] = atoi((const char *)str);
			i++;// 串口计数
		}
		dwName = sizeof(Name);
		dwSizeofPortName = sizeof(szPortName);
	} while((Status == ERROR_SUCCESS)||(Status == ERROR_MORE_DATA));
	RegCloseKey(hKey);
	return i;
}

unsigned char CheckUart(CDialog *pDlg) 
{
	// TODO: Add your control notification handler code here
		BYTE i=0;
	UCHAR SerialPortNum=0;
	unsigned char j;
	
	if(UART_Port)
	{
		CloseUart(u_Serial[UART_Port]);
		UART_Port=0;
		pDlg->SetDlgItemText(IDC_UART,_CS("Uart.Open"));
		return 1;
	}

	//DLG_PRINTF("正在连接...........");
	SerialPortNum=EnumSerialEx(u_Serial);
	
	for(i=0;i<COUNTOF(BaudRate);i++)
	{
		if (0< UART_Port && UART_Port < SerialPortNum)
		{
			if(OpenUart(u_Serial[UART_Port],BaudRate[i])==TRUE)
			{
				if(ShakeHands()==FALSE)
				{
					CloseUart(u_Serial[UART_Port]);
				}
				else
				{
					pDlg->MessageBox(_CS("WarningUart.ConnectSuccess"),_CS("WarningUart.Title"),MB_OK);
					
					pDlg->SetDlgItemText(IDC_UART,_CS("Uart.Close"));
					if(CheckVersion(FirmwareVersion)==FALSE)
						pDlg->MessageBox(_CS("WarningGeneral.FirmWareOld"),_CS("WarningUart.Title"),MB_OK);
						
					return 1;
				}
			}
			else
				UART_Port=0;
		}
		else
			UART_Port=0;
	}
	
	UART_Port=0;
	//first connect MST
	if (SerialPortNum)
	{
		if(UART_Port == 0)
		{
			for (i=1; i<SerialPortNum; i++)
			{
				for(j=0;j<COUNTOF(BaudRate);j++)
				{
					if(OpenUart(u_Serial[i],BaudRate[j])==TRUE)
					{
						if(ShakeHands()==TRUE)
						{
							UART_Port=i;

							pDlg->MessageBox(_CS("WarningUart.ConnectSuccess"),_CS("WarningUart.Title"),MB_OK);
								
							pDlg->SetDlgItemText(IDC_UART,_CS("Uart.Close"));
							if(CheckVersion(FirmwareVersion)==FALSE)
							pDlg->MessageBox(_CS("WarningGeneral.FirmWareOld"),_CS("WarningUart.Title"),MB_OK);
							return 1;
						}
						CloseUart(u_Serial[i]);
					}
				}
			}
		}
		if(UART_Port == 0)
		{
			pDlg->MessageBox(_CS("WarningUart.ConnectFail"),_CS("WarningUart.Title"),MB_OK);
			return 0;
		}
	}
	else
	{
		pDlg->MessageBox(_CS("WarningUart.NotFinded"),_CS("WarningUart.Title"),MB_OK);
		return 2;
	}
	return 1;
}

void CMy3DPrinterDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//if(pThread!=NULL)
	//{
	//	IsExit=TRUE;
	//}
	//else 
	{
		CDialog::OnClose();
	}
}

void CMy3DPrinterDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	CloseUart(u_Serial[UART_Port]);
	CDialog::OnCancel();
}

BOOL CMy3DPrinterDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) 
		return TRUE; 
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN) 
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}
