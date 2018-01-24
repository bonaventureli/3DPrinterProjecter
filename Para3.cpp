// Para3.cpp : implementation file
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
// CPara3 dialog


CPara3::CPara3(CWnd* pParent /*=NULL*/)
	: CDialog(CPara3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPara3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPara3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPara3)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPara3, CDialog)
	//{{AFX_MSG_MAP(CPara3)
	ON_BN_CLICKED(IDC_CTRL_TEMP, OnCtrlTemp)
	ON_BN_CLICKED(IDC_UART, OnUart)
	ON_BN_CLICKED(IDC_TEMP_READ, OnTempRead)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
void CPara3::UpgrateTemp(void)
{
	short int r,g,b,board;
	CString str_r,str_g,str_b,str_board;
	if(UART_Port)
	{
		GetTemperature(&r,&g,&b,&board);
		
		if(r==-100)
			str_r="----";
		else
			str_r.Format("%d",r);
		
		if(g==-100)
			str_g="----";
		else
			str_g.Format("%d",g);
		
		if(b==-100)
			str_b="----";
		else
			str_b.Format("%d",b);

		if(board==-100)
			str_board="----";
		else
			str_board.Format("%d",board);
		
		SetDlgItemText(IDC_STATIC_R,str_r);
		SetDlgItemText(IDC_STATIC_G,str_g);
		SetDlgItemText(IDC_STATIC_B,str_b);
		SetDlgItemText(IDC_STATIC_W,str_board);
		if(g==-100)
			SetDlgItemText(IDC_STATIC_TEMP,str_board);
		else
			SetDlgItemText(IDC_STATIC_TEMP,str_g);
	}
	else
	{
		MessageBox(_CS("WarningUart.NotOpen"),_CS("WarningUart.Title"),MB_OK);
	}
}
// CPara3 message handlers
void CPara3::OnCtrlTemp() 
{
	// TODO: Add your control notification handler code here
    UpgrateTemp();
}

static BOOL f_first=TRUE;
static BOOL f_DlgFirst=TRUE;

typedef struct tagKeyAndValue{
	CString Key;
	CString Value;
}KeyAndValue;

extern int GetKeyAndValue(CString Section,KeyAndValue* pKeyAndValue);

BOOL CPara3::OnInitDialog() 
{

	CDialog::OnInitDialog();
    _CWndCS(this);
	KeyAndValue   s_KeyAndValue[255];
	int Cnt,i,j=0;
	unsigned char f_led=0;
	Cnt=GetKeyAndValue("led",s_KeyAndValue);
	
	// TODO: Add extra initialization here
    if(f_DlgFirst)
	{

		for(i=0;i<(IDC_STATIC_3-IDC_STATIC_TEMP+1);i++)
			GetDlgItem(IDC_STATIC_TEMP+i)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_CTRL_TEMP)->ShowWindow(SW_HIDE);

		SetDlgItemText(IDC_STATIC_R,"----");
		SetDlgItemText(IDC_STATIC_G,"----");
		SetDlgItemText(IDC_STATIC_B,"----");
		SetDlgItemText(IDC_STATIC_W,"----");
		SetDlgItemText(IDC_STATIC_TEMP,"----");

		for(i=0;i<Cnt;i++)
		{
			if(s_KeyAndValue[i].Key=="r" && s_KeyAndValue[i].Value=="true")
			{
				f_led=f_led|0x01;
			}
			if(s_KeyAndValue[i].Key=="g" && s_KeyAndValue[i].Value=="true")
			{
				f_led=f_led|0x02;
			}
			if(s_KeyAndValue[i].Key=="b" && s_KeyAndValue[i].Value=="true")
			{
				f_led=f_led|0x04;
			}
		}

		if(Cnt)
		{
			if(f_led!=0x01 && f_led!=0x02 && f_led!=0x04 && f_led!=0)
			{
				for(i=0;i<(IDC_STATIC13-IDC_STATIC1+1);i++)
				GetDlgItem(IDC_STATIC1+i)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_CTRL_TEMP)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATIC_R)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATIC_G)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATIC_B)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATIC_W)->ShowWindow(SW_SHOW);
				//SW_SHOW  SW_HIDE
			}
			else
			{
				GetDlgItem(IDC_STATIC_1)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATIC_2)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATIC_TEMP)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_TEMP_READ)->ShowWindow(SW_SHOW);	
			}
		}
		else
		{
			GetDlgItem(IDC_STATIC_1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_TEMP)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_TEMP_READ)->ShowWindow(SW_SHOW);	
		}
		f_DlgFirst=FALSE;
	}

	if(UART_Port)
	{
		SetDlgItemText(IDC_UART,_CS("Uart.Close"));
		if(f_first)
		{
        UpgrateTemp();
		f_first=FALSE;
		}
	}
	else
		SetDlgItemText(IDC_UART,_CS("Uart.Open"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPara3::OnUart() 
{
	// TODO: Add your control notification handler code here
	short int r=-100,g=-100,b=-100;
	CString str_r,str_g,str_b;
	//CString StrVal;
	//U16 red,green,blue,Value;
	//int   iRadioButton;   

	CMy3DPrinterApp* pApp;
	pApp=(CMy3DPrinterApp*)AfxGetApp();
	CPara3* pDlg=&((CMy3DPrinterDlg*)pApp->m_pMainWnd)->m_para3;

	//iRadioButton=GetCheckedRadioButton(IDC_RADIO_R,IDC_RADIO_W); 
	
	if(UART_Port)
	{
        CheckUart(pDlg);
		return ;
	}
	
	if(CheckUart(pDlg)==1)
	{
		/*	
		//-------------------------------------
		GetTemperature(&r,&g,&b);
		if(r==-100)
			str_r="----";
		else
			str_r.Format("%d",r);
			
		if(g==-100)
			str_g="----";
		else
			str_g.Format("%d",g);
			
		if(b==-100)
			str_b="----";
		else
			str_b.Format("%d",b);
			
		SetDlgItemText(IDC_STATIC_R,str_r);
		SetDlgItemText(IDC_STATIC_G,str_g);
		SetDlgItemText(IDC_STATIC_B,str_b);
		SetDlgItemText(IDC_STATIC_W,str_g);
		//-------------------------------------	
		*/
		UpgrateTemp();
	}
}

void CPara3::OnTempRead() 
{
	// TODO: Add your control notification handler code here
	UpgrateTemp();
}

BOOL CPara3::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) 
		return TRUE; 
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN) 
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}
