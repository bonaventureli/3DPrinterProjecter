#if !defined(AFX_PARA6_H__9D2D1239_41C2_4C23_91D6_49A4A83CD2FE__INCLUDED_)
#define AFX_PARA6_H__9D2D1239_41C2_4C23_91D6_49A4A83CD2FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Para6.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPara6 dialog

class CPara6 : public CDialog
{
// Construction
public:
	CPara6(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPara6)
	enum { IDD = IDD_DIALOG6 };
	BOOL	m_check_x;
	BOOL	m_check_y;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPara6)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPara6)
	virtual BOOL OnInitDialog();
	afx_msg void OnUart();
	afx_msg void OnFlipDo();
	afx_msg void OnCheckX();
	afx_msg void OnCheckY();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARA6_H__9D2D1239_41C2_4C23_91D6_49A4A83CD2FE__INCLUDED_)
