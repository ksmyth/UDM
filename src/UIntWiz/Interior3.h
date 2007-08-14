#if !defined(AFX_INTERIOR3_H__F011841F_C7C3_4DF7_B7E7_5E364D6E48E8__INCLUDED_)
#define AFX_INTERIOR3_H__F011841F_C7C3_4DF7_B7E7_5E364D6E48E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Interior3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInterior3 dialog

class CInterior3 : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CInterior3)

// Construction
public:
	void RefreshOthers();
	CInterior3();
	~CInterior3();

// Dialog Data
	//{{AFX_DATA(CInterior3)
	enum { IDD = IDD_INTERIOR3_NEW };
	CEdit	m_ParadigmNameCtrl;
	CString	m_strInterfacePath;
	CString	m_strClassName;
	CString	m_strComponentName;
	CString m_strToolTip;
	BOOL	m_bParadigmIndependent;
	CString	m_strParadigmName;
	CString	m_strProgID;
	CString	m_strTypeLibName;
	CString	m_strClassUUID;
	CString	m_strTypeLibUUID;
	BOOL	m_bIconInGME;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CInterior3)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CInterior3)
	virtual BOOL OnInitDialog();
	afx_msg void OnRegen();
	afx_msg void OnBrowseGmeInterfaces();
	afx_msg void OnPardigmIndependent();
	afx_msg void OnChangeComponentName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERIOR3_H__F011841F_C7C3_4DF7_B7E7_5E364D6E48E8__INCLUDED_)
