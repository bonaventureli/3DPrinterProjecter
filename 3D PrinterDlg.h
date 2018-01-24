// 3D PrinterDlg.h : header file
//

#if !defined(AFX_3DPRINTERDLG_H__14638931_15DE_4EB1_9956_E16A6D594801__INCLUDED_)
#define AFX_3DPRINTERDLG_H__14638931_15DE_4EB1_9956_E16A6D594801__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Para1.h"
#include "Para2.h"
#include "Para3.h"
#include "Para5.h"
#include "Para6.h"

/////////////////////////////////////////////////////////////////////////////
// CMy3DPrinterDlg dialog

class CMy3DPrinterDlg : public CDialog
{
// Construction
public:
	CMy3DPrinterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy3DPrinterDlg)
	enum { IDD = IDD_MY3DPRINTER_DIALOG };
	CTabCtrl	m_tab;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3DPrinterDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
public:
    CPara1 m_para1;
	CPara2 m_para2;
	CPara3 m_para3;
	CPara5 m_para5;
	CPara6 m_para6;
	int m_CurSelTab;
	CDialog *pDialog[5];
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy3DPrinterDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DPRINTERDLG_H__14638931_15DE_4EB1_9956_E16A6D594801__INCLUDED_)
