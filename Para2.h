#if !defined(AFX_PARA2_H__97C43500_C49A_4D77_AB3A_C525EAA1A8D4__INCLUDED_)
#define AFX_PARA2_H__97C43500_C49A_4D77_AB3A_C525EAA1A8D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Para2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPara2 dialog

class CPara2 : public CDialog
{
// Construction
public:
	CPara2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPara2)
	enum { IDD = IDD_DIALOG2 };
	CComboBox	m_ComboBox1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPara2)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPara2)
	afx_msg void OnInputSource();
	virtual BOOL OnInitDialog();
	afx_msg void OnUart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARA2_H__97C43500_C49A_4D77_AB3A_C525EAA1A8D4__INCLUDED_)
