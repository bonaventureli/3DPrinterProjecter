#if !defined(AFX_PARA5_H__2C8C2BC9_7DD5_4E45_BD97_73BC0593EF96__INCLUDED_)
#define AFX_PARA5_H__2C8C2BC9_7DD5_4E45_BD97_73BC0593EF96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Para5.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPara5 dialog

class CPara5 : public CDialog
{
// Construction
public:
	CPara5(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPara5)
	enum { IDD = IDD_DIALOG5 };
	CEdit	m_Edit_FullName;
	CString	m_StrUpgrateFullName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPara5)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
	BOOL IsExit;
	CWinThread *pThread;
	BOOL IsStop;
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPara5)
	virtual BOOL OnInitDialog();
	afx_msg void OnUart();
	afx_msg void OnClose();
	afx_msg void OnUpgrate();
	afx_msg void OnChangeEditUpgrateFullname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARA5_H__2C8C2BC9_7DD5_4E45_BD97_73BC0593EF96__INCLUDED_)
