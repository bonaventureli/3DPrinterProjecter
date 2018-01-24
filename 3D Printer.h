// 3D Printer.h : main header file for the 3D PRINTER application
//

#if !defined(AFX_3DPRINTER_H__53AEE728_C784_446D_A1C7_96313EE5408F__INCLUDED_)
#define AFX_3DPRINTER_H__53AEE728_C784_446D_A1C7_96313EE5408F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy3DPrinterApp:
// See 3D Printer.cpp for the implementation of this class
//

struct ModuleFileInfomations
{
	CString		strFullPath;
	CString		strPath;
	CString		strDrive;
	CString		strDir;
	CString		strName;
	CString		strExt;
};

const ModuleFileInfomations&    GetModuleFileInformations();

#define GET_MODULE_FILE_INFO    (GetModuleFileInformations())

class CMy3DPrinterApp : public CWinApp
{
public:
	CMy3DPrinterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3DPrinterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy3DPrinterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DPRINTER_H__53AEE728_C784_446D_A1C7_96313EE5408F__INCLUDED_)
