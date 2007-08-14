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


// Int2.cpp : implementation file
//

#include "stdafx.h"
#include "Wizard97.h"
#include "Int2.h"
#include "WizSheet.h"

#include "FolderDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Interior2 property page

IMPLEMENT_DYNCREATE(CInterior2, CPropertyPageEx)

CInterior2::CInterior2()
	: CPropertyPageEx(CInterior2::IDD, 0, IDS_HEADERTITLE, IDS_HEADERSUBTITLE2)
{
	//{{AFX_DATA_INIT(CInterior2)
	m_strBackendPath = _T("");
	m_strUdmPath = _T("");
	m_bIncludeUdm = FALSE;
	m_bUserSelect = FALSE;
	m_nDataNetworkType = -1;
	m_strCppPath = _T("");
	m_strHeaderPath = _T("");
	//}}AFX_DATA_INIT
}

CInterior2::~CInterior2()
{
}

void CInterior2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInterior2)
	DDX_Control(pDX, IDC_UDM_PATH, m_UdmPathCtrl);
	DDX_Control(pDX, IDC_STATIC_HEADER, m_StaticHeaderCtrl);
	DDX_Control(pDX, IDC_STATIC_CPP, m_StaticCppCtrl);
	DDX_Control(pDX, IDC_HEADER_PATH, m_HeaderPathCtrl);
	DDX_Control(pDX, IDC_CPP_PATH, m_CppPathCtrl);
	DDX_Control(pDX, IDC_BROWSE_CPP, m_BrowseCppCtrl);
	DDX_Control(pDX, IDC_BROWSE_HEADER, m_BrowseHeaderCtrl);
	DDX_Control(pDX, IDC_USER_SELECT, m_UserSelectCtrl);
	DDX_Control(pDX, IDC_STATIC_BACKEND_PATH, m_StaticBackendPathCtrl);
	DDX_Control(pDX, IDC_BACKEND_PATH, m_BackendPathCtrl);
	DDX_Control(pDX, IDC_STATIC_NETWORK, m_StaticNetworkCtrl);
	DDX_Control(pDX, IDC_XML_BACKEND, m_XMLBackendCtrl);
	DDX_Control(pDX, IDC_BROWSE_UDM_PATH, m_BrowseUdmPathCtrl);
	DDX_Control(pDX, IDC_BROWSE_BACKEND_PATH, m_BrowseBackendCtrl);
	DDX_Text(pDX, IDC_BACKEND_PATH, m_strBackendPath);
	DDX_Text(pDX, IDC_UDM_PATH, m_strUdmPath);
	DDX_Check(pDX, IDC_INCLUDE_UDM, m_bIncludeUdm);
	DDX_Check(pDX, IDC_USER_SELECT, m_bUserSelect);
	DDX_Radio(pDX, IDC_STATIC_NETWORK, m_nDataNetworkType);
	DDX_Text(pDX, IDC_CPP_PATH, m_strCppPath);
	DDX_Text(pDX, IDC_HEADER_PATH, m_strHeaderPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInterior2, CPropertyPageEx)
	//{{AFX_MSG_MAP(CInterior2)
	ON_BN_CLICKED(IDC_USER_SELECT, OnUserSelect)
	ON_BN_CLICKED(IDC_INCLUDE_UDM, OnIncludeUdm)
	ON_BN_CLICKED(IDC_BROWSE_HEADER, OnBrowseHeader)
	ON_BN_CLICKED(IDC_BROWSE_CPP, OnBrowseCpp)
	ON_BN_CLICKED(IDC_BROWSE_UDM_PATH, OnBrowseUdmPath)
	ON_BN_CLICKED(IDC_BROWSE_BACKEND_PATH, OnBrowseBackendPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterior2 message handlers

BOOL CInterior2::OnSetActive()
{
	CWizard97Sheet* pSheet = (CWizard97Sheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);

	
	
	if(pSheet->m_Interior1.m_nMetaLoading==0)
	{		
		m_StaticNetworkCtrl.ShowWindow(SW_HIDE);
		m_XMLBackendCtrl.ShowWindow(SW_HIDE);
		m_BrowseBackendCtrl.ShowWindow(SW_HIDE);
		m_UserSelectCtrl.ShowWindow(SW_HIDE);
		m_StaticBackendPathCtrl.ShowWindow(SW_HIDE);
		m_BackendPathCtrl.ShowWindow(SW_HIDE);

		m_StaticCppCtrl.ShowWindow(SW_SHOW);
		m_StaticHeaderCtrl.ShowWindow(SW_SHOW);
		m_BrowseHeaderCtrl.ShowWindow(SW_SHOW);
		m_BrowseCppCtrl.ShowWindow(SW_SHOW);
		m_CppPathCtrl.ShowWindow(SW_SHOW);
		m_HeaderPathCtrl.ShowWindow(SW_SHOW);

	}
	else
	{
		m_StaticCppCtrl.ShowWindow(SW_HIDE);
		m_StaticHeaderCtrl.ShowWindow(SW_HIDE);
		m_BrowseHeaderCtrl.ShowWindow(SW_HIDE);
		m_BrowseCppCtrl.ShowWindow(SW_HIDE);
		m_CppPathCtrl.ShowWindow(SW_HIDE);
		m_HeaderPathCtrl.ShowWindow(SW_HIDE);


		m_StaticNetworkCtrl.ShowWindow(SW_SHOW);
		m_XMLBackendCtrl.ShowWindow(SW_SHOW);
		m_BrowseBackendCtrl.ShowWindow(SW_SHOW);
		m_UserSelectCtrl.ShowWindow(SW_SHOW);
		m_StaticBackendPathCtrl.ShowWindow(SW_SHOW);
		m_BackendPathCtrl.ShowWindow(SW_SHOW);

	}

	UpdateData(FALSE);

	return CPropertyPageEx::OnSetActive();
}

BOOL CInterior2::OnInitDialog() 
{
	CPropertyPageEx::OnInitDialog();
	
	m_bIncludeUdm=FALSE;
	//Ananth
	char l_strSingleVal[255];
	if(GetEnvironmentVariable("UDM_PATH", l_strSingleVal,255)) {
		m_strUdmPath=l_strSingleVal;
	}
	//end
	m_BrowseUdmPathCtrl.EnableWindow(TRUE);
	m_UdmPathCtrl.EnableWindow(TRUE);
	m_nDataNetworkType=0;


	UpdateData(FALSE);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInterior2::OnUserSelect() 
{
	UpdateData(TRUE);

	if(m_bUserSelect)
	{
		m_BrowseBackendCtrl.EnableWindow(FALSE);
		m_BackendPathCtrl.EnableWindow(FALSE);
	}
	else
	{
		m_BrowseBackendCtrl.EnableWindow(TRUE);
		m_BackendPathCtrl.EnableWindow(TRUE);
	}
	
}

void CInterior2::OnIncludeUdm() 
{
	UpdateData(TRUE);

	if(m_bIncludeUdm)
	{
		m_BrowseUdmPathCtrl.EnableWindow(FALSE);
		m_UdmPathCtrl.EnableWindow(FALSE);
	}
	else
	{
		m_BrowseUdmPathCtrl.EnableWindow(TRUE);
		m_UdmPathCtrl.EnableWindow(TRUE);
	}

}

void CInterior2::OnBrowseHeader() 
{

	static char szFilter[] = "C++ Header Files (*.h;*.hpp)|*.h; *.hpp|All Files (*.*)|*.*||";

	CFileDialog dlg(TRUE,"h",NULL,OFN_FILEMUSTEXIST,szFilter,this);

	if(dlg.DoModal()==IDOK)
	{
		m_HeaderPathCtrl.SetWindowText(dlg.GetPathName());
	}
}

void CInterior2::OnBrowseCpp() 
{
	static char szFilter[] = "C++ Files (*.cpp;*.cxx)|*.cpp; *.cxx|All Files (*.*)|*.*||";

	CFileDialog dlg(TRUE,"cpp",NULL,OFN_FILEMUSTEXIST,szFilter,this);

	if(dlg.DoModal()==IDOK)
	{
		m_CppPathCtrl.SetWindowText(dlg.GetPathName());
	}	
}

void CInterior2::OnBrowseUdmPath() 
{

	CFolderDialog dlg(this,"Specify the name of the UDM root folder:");
	
	if(dlg.DoModal()==IDOK)
	{
		m_strUdmPath=dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CInterior2::OnBrowseBackendPath() 
{
	static char szFilterXML[] = "XML Backend Files (*.xml)|*.xml|All Files (*.*)|*.*||";
	static char szFilterMem[] = "Static Memory Backend Files (*.mem)|*.mem|All Files (*.*)|*.*||";

	UpdateData(TRUE);
	if(m_nDataNetworkType==0)// Static
	{
		CFileDialog dlg(TRUE,"mem",NULL,OFN_FILEMUSTEXIST,szFilterMem,this);

		if(dlg.DoModal()==IDOK)
		{
			m_BackendPathCtrl.SetWindowText(dlg.GetPathName());
		}	
	}
	else
	{
		CFileDialog dlg(TRUE,"xml",NULL,OFN_FILEMUSTEXIST,szFilterXML,this);

		if(dlg.DoModal()==IDOK)
		{
			m_BackendPathCtrl.SetWindowText(dlg.GetPathName());
		}	
	}
	
}

LRESULT CInterior2::OnWizardNext() 
{

	UpdateData();

	CWizard97Sheet* pSheet = (CWizard97Sheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	
	if(!m_bIncludeUdm)
	{
		if(m_strUdmPath=="")
		{
			MessageBox("Please specify UDM path.","Udm Interpreter Wizard",MB_OK|MB_ICONERROR);
			return -1;
		}

	}

		
	if(pSheet->m_Interior1.m_nMetaLoading==0)
	{
		if(m_strHeaderPath=="")
		{
			MessageBox("Please specify UDM header file.","Udm Interpreter Wizard",MB_OK|MB_ICONERROR);
			return -1;
		}
		if(m_strCppPath=="")
		{
			MessageBox("Please specify UDM code file.","Udm Interpreter Wizard",MB_OK|MB_ICONERROR);
			return -1;
		}
	}
	else
	{
		if(!m_bUserSelect)
		{
			if(m_strBackendPath=="")
			{
				MessageBox("Please specify backend file.","Udm Interpreter Wizard",MB_OK|MB_ICONERROR);
				return -1;
			}
		}
	}
	

	Generator.m_UdmData.m_strBackendPath=m_strBackendPath;
	Generator.m_UdmData.m_strUdmPath=m_strUdmPath;
	Generator.m_UdmData.m_bIncludeUdm=m_bIncludeUdm;
	Generator.m_UdmData.m_bUserSelect=m_bUserSelect;
	Generator.m_UdmData.m_nDataNetworkType=m_nDataNetworkType;
	Generator.m_UdmData.m_strCppPath=m_strCppPath;
	Generator.m_UdmData.m_strHeaderPath=m_strHeaderPath;	
	
	return CPropertyPageEx::OnWizardNext();
}
