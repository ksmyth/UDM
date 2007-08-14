/*
 *	Copyright (c) Vanderbilt University, 2000-2001
 *	ALL RIGHTS RESERVED
 *
 *	Vanderbilt University disclaims all warranties with regard to this
 *	software, including all implied warranties of merchantability
 *	and fitness.  In no event shall Vanderbilt University be liable for
 *	any special, indirect or consequential damages or any damages
 *	whatsoever resulting from loss of use, data or profits, whether
 *	in an action of contract, negligence or other tortious action,
 *	arising out of or in connection with the use or performance of
 *	this software.
 */

// Complete.cpp : implementation file
//

#include "stdafx.h"
#include "Wizard97.h"
#include "Complete.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompletion property page

IMPLEMENT_DYNCREATE(CCompletion, CPropertyPageEx)

CCompletion::CCompletion() : CPropertyPageEx(CCompletion::IDD)
{
	//{{AFX_DATA_INIT(CCompletion)
	//}}AFX_DATA_INIT
	m_psp.dwFlags |= PSP_HIDEHEADER;
}

CCompletion::~CCompletion()
{
}

void CCompletion::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCompletion)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCompletion, CPropertyPageEx)
	//{{AFX_MSG_MAP(CCompletion)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompletion message handlers

BOOL CCompletion::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->SetWizardButtons(PSWIZB_FINISH);
	pSheet->GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
	pSheet->GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);
	return CPropertyPageEx::OnSetActive();
}


BOOL CCompletion::OnWizardFinish() 
{


	return CPropertyPageEx::OnWizardFinish();
}

void CCompletion::OnAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();
}
