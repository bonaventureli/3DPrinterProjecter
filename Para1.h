#if !defined(AFX_PARA1_H__A67E005D_930C_42A0_87DC_EF92FC3F39DE__INCLUDED_)
#define AFX_PARA1_H__A67E005D_930C_42A0_87DC_EF92FC3F39DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Para1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPara1 dialog

class CPara1 : public CDialog
{
// Construction
public:
	CPara1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPara1)
	enum { IDD = IDD_DIALOG1 };
	CComboBox	m_ComboBox1;
	CEdit	m_Edit_Led;
	CSliderCtrl	m_Slider_Led;
	UINT	m_LedValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPara1)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
	BOOL f_LedOff;
	unsigned short SliderPos;
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPara1)
	afx_msg void OnLedCtrl();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonLedSet();
	afx_msg void OnButtonLedGet();
	afx_msg void OnChangeEditLed();
	afx_msg void OnCustomdrawSliderLed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUart();
	afx_msg void OnRadioG();
	afx_msg void OnRadioR();
	afx_msg void OnRadioB();
	afx_msg void OnLightCtl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARA1_H__A67E005D_930C_42A0_87DC_EF92FC3F39DE__INCLUDED_)
