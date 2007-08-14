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


// Interior4.cpp : implementation file
//

#include "stdafx.h"
#include "wizard97.h"
#include "Interior4.h"

#include "FolderDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInterior4 property page

IMPLEMENT_DYNCREATE(CInterior4, CPropertyPageEx)

CInterior4::CInterior4() : CPropertyPageEx(CInterior4::IDD)
{
	//{{AFX_DATA_INIT(CInterior4)
	m_strDestPath = _T("");
	//}}AFX_DATA_INIT

	m_psp.dwFlags |= PSP_HIDEHEADER;
}

CInterior4::~CInterior4()
{
}

void CInterior4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInterior4)
	DDX_Text(pDX, IDC_DESTINATION_PATH, m_strDestPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInterior4, CPropertyPageEx)
	//{{AFX_MSG_MAP(CInterior4)
	ON_BN_CLICKED(IDC_BROWSE_DESTINATION, OnBrowseDestination)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterior4 message handlers

BOOL CInterior4::OnSetActive() 
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	pSheet->GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);
	
	return CPropertyPageEx::OnSetActive();
}

void CInterior4::OnBrowseDestination() 
{
	CFolderDialog dlg(this,"Specify the location for code generation:");
	
	if(dlg.DoModal()==IDOK)
	{
		m_strDestPath=dlg.GetPathName();
		UpdateData(FALSE);
	}
	
}

LRESULT CInterior4::OnWizardNext() 
{
	UpdateData();

	if(m_strDestPath=="")
	{
		MessageBox("Please specify destination folder.","Udm Interpreter Wizard",MB_OK|MB_ICONERROR);
		return -1;
	}
	
	if(m_strDestPath.Right(1)=="\\")
	{
		m_strDestPath=m_strDestPath.Left(m_strDestPath.GetLength()-1);
	}

	Generator.m_strDestinationPath=m_strDestPath;
	
	GetDlgItem(IDC_STATUS)->ShowWindow(SW_SHOW);


	GetDlgItem(IDC_BOLDTITLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DESTINATION_PATH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BROWSE_DESTINATION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);

	RedrawWindow();	

	AfxGetApp()->BeginWaitCursor();
	Generator.Generate();
	AfxGetApp()->EndWaitCursor();

	return CPropertyPageEx::OnWizardNext();
}

BOOL CInterior4::OnInitDialog() 
{
	CPropertyPageEx::OnInitDialog();
	
	GetDlgItem(IDC_STATUS)->ShowWindow(SW_HIDE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
