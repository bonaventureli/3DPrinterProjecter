#if !defined(AFX_PARA3_H__C1DD8155_6FF8_4621_A493_E15D2C96936D__INCLUDED_)
#define AFX_PARA3_H__C1DD8155_6FF8_4621_A493_E15D2C96936D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Para3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPara3 dialog

class CPara3 : public CDialog
{
// Construction
public:
	CPara3(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPara3)
	enum { IDD = IDD_DIALOG3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPara3)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
    void UpgrateTemp(void);
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPara3)
	afx_msg void OnCtrlTemp();
	virtual BOOL OnInitDialog();
	afx_msg void OnUart();
	afx_msg void OnTempRead();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARA3_H__C1DD8155_6FF8_4621_A493_E15D2C96936D__INCLUDED_)
