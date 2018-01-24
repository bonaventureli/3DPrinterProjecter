; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPara5
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "3d printer.h"
LastPage=0

ClassCount=12
Class1=CMy3DPrinterApp
Class2=CAboutDlg
Class3=CMy3DPrinterDlg
Class4=CImageMaker
Class5=MyListBox
Class6=CPara1
Class7=CPara2
Class8=CPara3
Class9=CPara4
Class10=CPara5
Class11=CPara6
Class12=CPara7

ResourceCount=7
Resource1=IDD_DIALOG1
Resource2=IDD_DIALOG3
Resource3=IDD_DIALOG5
Resource4=IDD_ABOUTBOX
Resource5=IDD_MY3DPRINTER_DIALOG
Resource6=IDD_DIALOG2
Resource7=IDD_DIALOG6

[CLS:CMy3DPrinterApp]
Type=0
BaseClass=CWinApp
HeaderFile=3D Printer.h
ImplementationFile=3D Printer.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=3D PrinterDlg.cpp
ImplementationFile=3D PrinterDlg.cpp

[CLS:CMy3DPrinterDlg]
Type=0
BaseClass=CDialog
HeaderFile=3D PrinterDlg.h
ImplementationFile=3D PrinterDlg.cpp

[CLS:CImageMaker]
Type=0
BaseClass=CDialog
HeaderFile=ImageMaker.h
ImplementationFile=ImageMaker.cpp

[CLS:MyListBox]
Type=0
BaseClass=CListBox
HeaderFile=MyListBox.h
ImplementationFile=MyListBox.cpp

[CLS:CPara1]
Type=0
BaseClass=CDialog
HeaderFile=Para1.h
ImplementationFile=Para1.cpp

[CLS:CPara2]
Type=0
BaseClass=CDialog
HeaderFile=Para2.h
ImplementationFile=Para2.cpp

[CLS:CPara3]
Type=0
BaseClass=CDialog
HeaderFile=Para3.h
ImplementationFile=Para3.cpp

[CLS:CPara4]
Type=0
BaseClass=CDialog
HeaderFile=Para4.h
ImplementationFile=Para4.cpp
LastObject=IDC_PAT_INDEX1
Filter=D
VirtualFilter=dWC

[CLS:CPara5]
Type=0
BaseClass=CDialog
HeaderFile=Para5.h
ImplementationFile=Para5.cpp
Filter=D
VirtualFilter=dWC
LastObject=CPara5

[CLS:CPara6]
Type=0
BaseClass=CDialog
HeaderFile=Para6.h
ImplementationFile=Para6.cpp
LastObject=IDC_CHECK_Y

[CLS:CPara7]
Type=0
BaseClass=CDialog
HeaderFile=Para7.h
ImplementationFile=Para7.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_EXPOSURE_TIME

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MY3DPRINTER_DIALOG]
Type=1
Class=CMy3DPrinterDlg
ControlCount=1
Control1=IDC_TAB1,SysTabControl32,1342177280

[DLG:IDD_DIALOG1]
Type=1
Class=CPara1
ControlCount=20
Control1=IDC_STATIC,static,1342308352
Control2=IDC_LED_CTRL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_SLIDER_LED,msctls_trackbar32,1350631444
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_LED,edit,1350639745
Control7=IDC_BUTTON_LED_SET,button,1342242816
Control8=IDC_BUTTON_LED_GET,button,1342242816
Control9=IDC_RADIO_R,button,1476395017
Control10=IDC_RADIO_G,button,1476395017
Control11=IDC_RADIO_B,button,1476395017
Control12=IDC_RADIO_W,button,1476395017
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,static,1342308352
Control15=IDC_UART,button,1342242816
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC_LIGHT,static,1342308354
Control18=IDC_COMBO_LIGHT,combobox,1344339971
Control19=IDC_LIGHT_CTL,button,1342242816
Control20=IDC_LIGHT_GROUP,button,1342177287

[DLG:IDD_DIALOG2]
Type=1
Class=CPara2
ControlCount=7
Control1=IDC_STATIC,static,1342308354
Control2=IDC_COMBO1,combobox,1344339971
Control3=IDC_INPUT_SOURCE,button,1342242816
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_UART,button,1342242816
Control7=IDC_STATIC,button,1342177287

[DLG:IDD_DIALOG3]
Type=1
Class=CPara3
ControlCount=26
Control1=IDC_STATIC5,static,1073872896
Control2=IDC_STATIC_R,static,1073872896
Control3=IDC_STATIC9,static,1073872896
Control4=IDC_STATIC1,button,1073741831
Control5=IDC_STATIC6,static,1073872896
Control6=IDC_STATIC_G,static,1073872896
Control7=IDC_STATIC10,static,1073872896
Control8=IDC_STATIC2,button,1073741831
Control9=IDC_STATIC7,static,1073872896
Control10=IDC_STATIC_B,static,1073872896
Control11=IDC_STATIC11,static,1073872896
Control12=IDC_STATIC3,button,1073741831
Control13=IDC_CTRL_TEMP,button,1073807360
Control14=IDC_STATIC13,button,1073741831
Control15=IDC_STATIC8,static,1073872896
Control16=IDC_STATIC_W,static,1073872896
Control17=IDC_STATIC12,static,1073872896
Control18=IDC_STATIC4,button,1073741831
Control19=IDC_STATIC,static,1342308352
Control20=IDC_UART,button,1342242816
Control21=IDC_STATIC,button,1342177287
Control22=IDC_STATIC_TEMP,static,1342308352
Control23=IDC_TEMP_READ,button,1342242816
Control24=IDC_STATIC_3,static,1342308352
Control25=IDC_STATIC_2,static,1342308352
Control26=IDC_STATIC_1,button,1342177287

[DLG:IDD_DIALOG5]
Type=1
Class=CPara5
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_UART,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_UPGRATE,button,1342242816
Control5=IDC_STATIC,static,1342308354
Control6=IDC_EDIT_UPGRATE_FULLNAME,edit,1350631552
Control7=IDC_STATIC,button,1342177287

[DLG:IDD_DIALOG6]
Type=1
Class=CPara6
ControlCount=6
Control1=IDC_CHECK_X,button,1342242851
Control2=IDC_CHECK_Y,button,1342242851
Control3=IDC_FLIP_DO,button,1342242816
Control4=IDC_UART,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,button,1342177287

