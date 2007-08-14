// Interior2.h : header file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#if !defined(AFX_INTERIOR2_H__99E7B193_4A5C_11D1_BF2C_00C04FC99F83__INCLUDED_)
#define AFX_INTERIOR2_H__99E7B193_4A5C_11D1_BF2C_00C04FC99F83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// Interior2 dialog

class CInterior2 : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CInterior2)

// Construction
public:
	CInterior2();
	~CInterior2();

// Dialog Data
	//{{AFX_DATA(CInterior2)
	enum { IDD = IDD_INTERIOR2_NEW };
	CEdit	m_UdmPathCtrl;
	CStatic	m_StaticHeaderCtrl;
	CStatic	m_StaticCppCtrl;
	CEdit	m_HeaderPathCtrl;
	CEdit	m_CppPathCtrl;
	CButton	m_BrowseCppCtrl;
	CButton	m_BrowseHeaderCtrl;
	CButton	m_UserSelectCtrl;
	CStatic	m_StaticBackendPathCtrl;
	CEdit	m_BackendPathCtrl;
	CButton	m_StaticNetworkCtrl;
	CButton	m_XMLBackendCtrl;
	CButton	m_BrowseUdmPathCtrl;
	CButton	m_BrowseBackendCtrl;
	CString	m_strBackendPath;
	CString	m_strUdmPath;
	BOOL	m_bIncludeUdm;
	BOOL	m_bUserSelect;
	int		m_nDataNetworkType;
	CString	m_strCppPath;
	CString	m_strHeaderPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CInterior2)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CInterior2)
	virtual BOOL OnInitDialog();
	afx_msg void OnUserSelect();
	afx_msg void OnIncludeUdm();
	afx_msg void OnBrowseHeader();
	afx_msg void OnBrowseCpp();
	afx_msg void OnBrowseUdmPath();
	afx_msg void OnBrowseBackendPath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERIOR2_H__99E7B193_4A5C_11D1_BF2C_00C04FC99F83__INCLUDED_)
