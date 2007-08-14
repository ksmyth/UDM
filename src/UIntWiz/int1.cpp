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

// Int1.cpp : implementation file
//

#include "stdafx.h"
#include "Wizard97.h"
#include "Int1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInterior1 property page

IMPLEMENT_DYNCREATE(CInterior1, CPropertyPageEx)

CInterior1::CInterior1() : CPropertyPageEx(CInterior1::IDD, 0, IDS_HEADERTITLE, IDS_HEADERSUBTITLE1)
{
	//{{AFX_DATA_INIT(CInterior1)
	m_nMGAAccess = -1;
	m_nMetaLoading = -1;
	//}}AFX_DATA_INIT
}

CInterior1::~CInterior1()
{
}

void CInterior1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInterior1)
	DDX_Radio(pDX, IDC_DMA, m_nMGAAccess);
	DDX_Radio(pDX, IDC_STATIC_META, m_nMetaLoading);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInterior1, CPropertyPageEx)
	//{{AFX_MSG_MAP(CInterior1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterior1 message handlers

BOOL CInterior1::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	pSheet->GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);
	return CPropertyPageEx::OnSetActive();
}

BOOL CInterior1::OnInitDialog() 
{
	CPropertyPageEx::OnInitDialog();
	
	m_nMGAAccess=0;
	m_nMetaLoading=0;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CInterior1::OnWizardNext() 
{
	UpdateData();

	Generator.m_UdmData.m_nMGAAccess=m_nMGAAccess;
	Generator.m_UdmData.m_nMetaLoading=m_nMetaLoading;
	
	return CPropertyPageEx::OnWizardNext();
}
