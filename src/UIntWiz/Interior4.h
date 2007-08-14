#if !defined(AFX_INTERIOR4_H__0AA81507_A4DB_4EBE_A55A_45642BECD0C1__INCLUDED_)
#define AFX_INTERIOR4_H__0AA81507_A4DB_4EBE_A55A_45642BECD0C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Interior4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInterior4 dialog

class CInterior4 : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CInterior4)

// Construction
public:
	CInterior4();
	~CInterior4();

// Dialog Data
	//{{AFX_DATA(CInterior4)
	enum { IDD = IDD_INTERIOR4_NEW };
	CString	m_strDestPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CInterior4)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CInterior4)
	afx_msg void OnBrowseDestination();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERIOR4_H__0AA81507_A4DB_4EBE_A55A_45642BECD0C1__INCLUDED_)
