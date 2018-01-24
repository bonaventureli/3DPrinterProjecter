// Para1.cpp : implementation file
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
// CPara1 dialog


CPara1::CPara1(CWnd* pParent /*=NULL*/)
	: CDialog(CPara1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPara1)
	m_LedValue = 0;
	//}}AFX_DATA_INIT
}


void CPara1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPara1)
	DDX_Control(pDX, IDC_COMBO_LIGHT, m_ComboBox1);
	DDX_Control(pDX, IDC_EDIT_LED, m_Edit_Led);
	DDX_Control(pDX, IDC_SLIDER_LED, m_Slider_Led);
	DDX_Text(pDX, IDC_EDIT_LED, m_LedValue);
	DDV_MinMaxUInt(pDX, m_LedValue, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPara1, CDialog)
	//{{AFX_MSG_MAP(CPara1)
	ON_BN_CLICKED(IDC_LED_CTRL, OnLedCtrl)
	ON_BN_CLICKED(IDC_BUTTON_LED_SET, OnButtonLedSet)
	ON_BN_CLICKED(IDC_BUTTON_LED_GET, OnButtonLedGet)
	ON_EN_CHANGE(IDC_EDIT_LED, OnChangeEditLed)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_LED, OnCustomdrawSliderLed)
	ON_BN_CLICKED(IDC_UART, OnUart)
	ON_BN_CLICKED(IDC_RADIO_G, OnRadioG)
	ON_BN_CLICKED(IDC_RADIO_R, OnRadioR)
	ON_BN_CLICKED(IDC_RADIO_B, OnRadioB)
	ON_BN_CLICKED(IDC_LIGHT_CTL, OnLightCtl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPara1 message handlers

void CPara1::OnLedCtrl() 
{
	// TODO: Add your control notification handler code here
	HWND   hwnd;
	int i=0;
	Bool flag;
	//U16 red,green,blue;
	
	if(f_LedOff)
	{
		GetDlgItem(IDC_SLIDER_LED,&hwnd);
        ::EnableWindow(hwnd,TRUE);
		GetDlgItem(IDC_EDIT_LED,&hwnd);
        ::EnableWindow(hwnd,TRUE);
		GetDlgItem(IDC_BUTTON_LED_SET,&hwnd);
        ::EnableWindow(hwnd,TRUE);
		GetDlgItem(IDC_BUTTON_LED_GET,&hwnd);
        ::EnableWindow(hwnd,TRUE);
		if(UART_Port)
		{
			//Set_RGB_Current(RED_VAL,SliderPos,BLUE_VAL);
			for(i=0;i<4;i++)
			{
				flag=LedOnOff(1);
				if(flag)
					break;
				Sleep(50);
			}
			
			f_LedOff=FALSE;
			SetDlgItemText(IDC_LED_CTRL,_CS("Led.Off"));
		}
		else
			MessageBox(_CS("WarningUart.NotOpen"),_CS("WarningUart.Title"),MB_OK);
	}
	else
	{
		if(UART_Port==0)
		{
			MessageBox(_CS("WarningUart.NotOpen"),_CS("WarningUart.Title"),MB_OK);
			return ;
		}
		GetDlgItem(IDC_SLIDER_LED,&hwnd);
        ::EnableWindow(hwnd,FALSE);
		GetDlgItem(IDC_EDIT_LED,&hwnd);
        ::EnableWindow(hwnd,FALSE);
		GetDlgItem(IDC_BUTTON_LED_SET,&hwnd);
        ::EnableWindow(hwnd,FALSE);
		GetDlgItem(IDC_BUTTON_LED_GET,&hwnd);
        ::EnableWindow(hwnd,FALSE);
		
		//Set_RGB_Current(RED_VAL,0,BLUE_VAL);
		for(i=0;i<4;i++)
		{
			flag=LedOnOff(0);
			if(flag)
				break;
			Sleep(50);
		}
		f_LedOff=TRUE;
		SetDlgItemText(IDC_LED_CTRL,_CS("Led.On"));
	}
}

static BOOL f_first=TRUE;
static BOOL f_DlgFirst=TRUE;

typedef struct tagKeyAndValue{
	CString Key;
	CString Value;
}KeyAndValue;

extern int GetKeyAndValue(CString Section,KeyAndValue* pKeyAndValue);

BOOL CPara1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	CString gsliderstr;
	KeyAndValue   s_KeyAndValue[255];
	int Cnt,i=0;
	unsigned char f_led=0;
	Cnt=GetKeyAndValue("led",s_KeyAndValue);

	if(f_DlgFirst)
	{
		GetDlgItem(IDC_LIGHT_GROUP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_LIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LIGHT_CTL)->ShowWindow(SW_HIDE);
		UpdateData(FALSE);
		m_ComboBox1.SetCurSel(-1);
		m_ComboBox1.AddString(_CS("Led.Red"));//Red
		m_ComboBox1.AddString(_CS("Led.Green"));//Green
		m_ComboBox1.AddString(_CS("Led.Blue"));//Blue
		m_ComboBox1.AddString(_CS("Led.White"));//White
		m_ComboBox1.SetCurSel(3);
		UpdateData(TRUE);

		m_Slider_Led.SetRange(0,255);
		m_Slider_Led.SetTicFreq(1);
		SliderPos=m_Slider_Led.GetPos();
		gsliderstr.Format("%d",m_Slider_Led.GetPos());
		SetDlgItemText(IDC_EDIT_LED,gsliderstr);
		
		//GetDlgItem(IDC_RADIO_W)
		//第一个参数为该组的第一个单选按钮的ID 
		//第二个参数为该组的最后一个单选按钮的ID
		//第三个参数为该组中被选中的单选按钮的ID
		for(i=0;i<Cnt;i++)
		{
			if(s_KeyAndValue[i].Key=="r" && s_KeyAndValue[i].Value=="true")
			{
				CheckRadioButton(IDC_RADIO_R,IDC_RADIO_W,IDC_RADIO_R);
				GetDlgItem(IDC_RADIO_R)->EnableWindow(TRUE);
				f_led=f_led|0x01;
			}
			if(s_KeyAndValue[i].Key=="g" && s_KeyAndValue[i].Value=="true")
			{
				CheckRadioButton(IDC_RADIO_R,IDC_RADIO_W,IDC_RADIO_G);
				GetDlgItem(IDC_RADIO_G)->EnableWindow(TRUE);
				f_led=f_led|0x02;
			}
			if(s_KeyAndValue[i].Key=="b" && s_KeyAndValue[i].Value=="true")
			{
				CheckRadioButton(IDC_RADIO_R,IDC_RADIO_W,IDC_RADIO_B);
				GetDlgItem(IDC_RADIO_B)->EnableWindow(TRUE);
				f_led=f_led|0x04;
			}
		}

        if(Cnt)
		{
			if(f_led == 7)
			{
				GetDlgItem(IDC_LIGHT_GROUP)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATIC_LIGHT)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_COMBO_LIGHT)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_LIGHT_CTL)->ShowWindow(SW_SHOW);
			}

			if(f_led==0x01 || f_led==0x02 || f_led==0x04 || f_led==0)
			{
				GetDlgItem(IDC_RADIO_R)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO_G)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO_B)->EnableWindow(FALSE);
			}
			if(f_led==0 || f_led==7)
				CheckRadioButton(IDC_RADIO_R,IDC_RADIO_W,IDC_RADIO_G);
		}
        else
			CheckRadioButton(IDC_RADIO_R,IDC_RADIO_W,IDC_RADIO_G); 
		f_LedOff=FALSE;
		f_DlgFirst=FALSE;
	}


	if(UART_Port)
	{
		if(f_first)
		{
			OnButtonLedGet();
			f_first=FALSE;
		}
		
		SetDlgItemText(IDC_UART,_CS("Uart.Close"));
	}
	else
		SetDlgItemText(IDC_UART,_CS("Uart.Open"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPara1::OnButtonLedSet() 
{
	// TODO: Add your control notification handler code here
	CString StrVal;
	//U16 greenval;
	U16 red,green,blue,Value;
	int   iRadioButton;   
    
	iRadioButton=GetCheckedRadioButton(IDC_RADIO_R,IDC_RADIO_W); 
	if(UART_Port)
	{
		GetCurrent(&red,&green,&blue);
		GetDlgItemText(IDC_EDIT_LED,StrVal);
		Value=atoi((const char*)StrVal);
		m_Slider_Led.SetPos(Value);
		SliderPos=Value;
		if(iRadioButton==IDC_RADIO_R)   
			SetCurrent(Value,green,blue);
		else if(iRadioButton==IDC_RADIO_G)   
			SetCurrent(red,Value,blue);
		else if(iRadioButton==IDC_RADIO_B)   
		{
			SetCurrent(red,green,Value);
		}
		else if(iRadioButton==IDC_RADIO_W)
			SetCurrent(red,Value,blue);
		
	}
	else
	{
		MessageBox(_CS("WarningUart.NotOpen"),_CS("WarningUart.Title"),MB_OK);
	}
}

void CPara1::OnButtonLedGet() 
{
	// TODO: Add your control notification handler code here
	U16 red=0,green=0,blue=0,Value=0;
	CString StrVal;
	int   iRadioButton;   
    
	iRadioButton=GetCheckedRadioButton(IDC_RADIO_R,IDC_RADIO_W);   
	
	if(UART_Port)
	{
		GetCurrent(&red,&green,&blue);

		if(red>255 || green >255 || blue>255)
		{
			MessageBox(_CS("WarningUart.ReadFail"),_CS("WarningUart.Title"),MB_OK);
			return ;
		}

		if(iRadioButton==IDC_RADIO_R)   
			Value=red;
		else if(iRadioButton==IDC_RADIO_G)   
			Value=green;
		else if(iRadioButton==IDC_RADIO_B)   
		{
			Value=blue;
		}
		else if(iRadioButton==IDC_RADIO_W)
			Value=green;
		StrVal.Format("%d",Value);
		m_Slider_Led.SetPos(Value);
		SliderPos=Value;
		SetDlgItemText(IDC_EDIT_LED,StrVal);
	}
	else
		MessageBox(_CS("WarningUart.NotOpen"),_CS("WarningUart.Title"),MB_OK);
}

void CPara1::OnChangeEditLed() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	UpdateData(FALSE);
}

void CPara1::OnCustomdrawSliderLed(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CString setgreenstr;
	U16 SliderPosNew;
	
	UpdateData(TRUE);
	SliderPosNew=m_Slider_Led.GetPos();
	if(SliderPos!=SliderPosNew)
	{
		setgreenstr.Format("%d",SliderPosNew);
		SetDlgItemText(IDC_EDIT_LED,setgreenstr);
		//	AdjRGBEx(red,(U16)m_Slider_Led.GetPos(),blue);
		SliderPos=SliderPosNew;
		//if (MST_Port)
		//{
		//GetRGB_PC(&red,&green,&blue);
		//AdjRGBEx(RED_VAL,(U16)SliderPosNew,BLUE_VAL);
		//}
		//Sleep(100);
	}
	UpdateData(FALSE);
	*pResult = 0;
}

BOOL CPara1::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) 
		return TRUE; 
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN) 
		return TRUE;
	if ((pMsg->message==WM_LBUTTONDOWN) && (pMsg->hwnd == m_Edit_Led.m_hWnd ))
	{
		CString g;
		//U16 red,green,blue;
		U16 gval;
		int   iRadioButton;   
		iRadioButton=GetCheckedRadioButton(IDC_RADIO_R,IDC_RADIO_W); 
		
		
		GetDlgItemText(IDC_EDIT_LED,g);
		gval=atoi((const char *)g);
		if(gval>=0 && gval<256)
		{
			m_Slider_Led.SetPos(gval);
			/*
			if (UART_Port)
			{
				GetCurrent(&red,&green,&blue);
				if(iRadioButton==IDC_RADIO_R)   
					SetCurrent(gval,green,blue);
				else if(iRadioButton==IDC_RADIO_G)   
					SetCurrent(red,gval,blue);
				else if(iRadioButton==IDC_RADIO_B)   
				{
					SetCurrent(red,green,gval);
				}
				else if(iRadioButton==IDC_RADIO_W)
				SetCurrent(red,gval,blue);
			}
			*/
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CPara1::OnUart() 
{
	// TODO: Add your control notification handler code here

	//short int r=-100,g=-100,b=-100;
	//CString str_r,str_g,str_b;
	CString StrVal;
	U16 red,green,blue,Value;
	int   iRadioButton;   

	CMy3DPrinterApp* pApp;
	pApp=(CMy3DPrinterApp*)AfxGetApp();
	CPara1* pDlg=&((CMy3DPrinterDlg*)pApp->m_pMainWnd)->m_para1;

	iRadioButton=GetCheckedRadioButton(IDC_RADIO_R,IDC_RADIO_W); 
	
	if(UART_Port)
	{
        CheckUart(pDlg);
		return ;
	}
	
	if(CheckUart(pDlg)==1)
	{
		GetCurrent(&red,&green,&blue);
		if(iRadioButton==IDC_RADIO_R)   
			Value=red;
		else if(iRadioButton==IDC_RADIO_G)   
			Value=green;
		else if(iRadioButton==IDC_RADIO_B)   
		{
			Value=blue;
		}
		else if(iRadioButton==IDC_RADIO_W)
		Value=green;
		StrVal.Format("%d",Value);
		SliderPos=Value;
		SetDlgItemText(IDC_EDIT_LED,StrVal);
		m_Slider_Led.SetPos(Value);
	}

	return ;
}

void CPara1::OnRadioG() 
{
	// TODO: Add your control notification handler code here
	if(UART_Port)
		OnButtonLedGet();
}

void CPara1::OnRadioR() 
{
	// TODO: Add your control notification handler code here
	if(UART_Port)
		OnButtonLedGet();
}

void CPara1::OnRadioB() 
{
	// TODO: Add your control notification handler code here
	if(UART_Port)
		OnButtonLedGet();
}

void CPara1::OnLightCtl() 
{
	// TODO: Add your control notification handler code here
	unsigned char buffer[3];
	unsigned char Index;
	if(UART_Port==0)
	{
		MessageBox(_CS("WarningUart.NotOpen"),_CS("WarningUart.Title"),MB_OK);
		return;
	}
	Index=m_ComboBox1.GetCurSel();

	if(Index<3)
		buffer[0]=1<<Index;
	else
		buffer[0]=7;
	LightControl(buffer[0]);
}
