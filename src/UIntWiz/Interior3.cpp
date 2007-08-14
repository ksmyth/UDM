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


// Interior3.cpp : implementation file
//

#include "stdafx.h"
#include "Wizard97.h"
#include "Interior3.h"
#include "FolderDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInterior3 property page

IMPLEMENT_DYNCREATE(CInterior3, CPropertyPageEx)

CInterior3::CInterior3() : CPropertyPageEx(CInterior3::IDD, 0, IDS_HEADERTITLE, IDS_HEADERSUBTITLE3)
{
	//{{AFX_DATA_INIT(CInterior3)
	m_strInterfacePath = _T("");
	m_strClassName = _T("");
	m_strComponentName = _T("");
	m_bParadigmIndependent = FALSE;
	m_strParadigmName = _T("");
	m_strProgID = _T("");
	m_strTypeLibName = _T("");
	m_strClassUUID = _T("");
	m_strTypeLibUUID = _T("");
	m_bIconInGME = FALSE;
	//}}AFX_DATA_INIT
}

CInterior3::~CInterior3()
{
}

void CInterior3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInterior3)
	DDX_Control(pDX, IDC_PARNAME, m_ParadigmNameCtrl);
	DDX_Text(pDX, IDC_IFPATH, m_strInterfacePath);
	DDX_Text(pDX, IDC_CLASSNAME, m_strClassName);
	DDX_Text(pDX, IDC_COMPNAME, m_strComponentName);
	DDX_Check(pDX, IDC_PARINDEP, m_bParadigmIndependent);
	DDX_Text(pDX, IDC_PARNAME, m_strParadigmName);
	DDX_Text(pDX, IDC_PROGID, m_strProgID);
	DDX_Text(pDX, IDC_TLBNAME, m_strTypeLibName);
	DDX_Text(pDX, IDC_CLASSUUID, m_strClassUUID);
	DDX_Text(pDX, IDC_TLBUUID, m_strTypeLibUUID);
	DDX_Check(pDX, IDC_TBICON, m_bIconInGME);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInterior3, CPropertyPageEx)
	//{{AFX_MSG_MAP(CInterior3)
	ON_BN_CLICKED(IDC_REGEN, OnRegen)
	ON_BN_CLICKED(IDC_BROWSE_GME_INTERFACES, OnBrowseGmeInterfaces)
	ON_BN_CLICKED(IDC_PARINDEP, OnPardigmIndependent)
	ON_EN_CHANGE(IDC_COMPNAME, OnChangeComponentName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterior3 message handlers



BOOL CInterior3::OnSetActive() 
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	pSheet->GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);
	
	return CPropertyPageEx::OnSetActive();
}

BOOL CInterior3::OnInitDialog() 
{
	CPropertyPageEx::OnInitDialog();
	

	/***** Getting GME Path from Windows Registry *****/
	DWORD type;
	static char name[_MAX_PATH+1];
	DWORD namelen = sizeof(name)-1;
	HKEY hn;

	LONG lRet =::RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion", 0, KEY_READ, &hn);
	if(lRet == ERROR_SUCCESS)
	{
		lRet = RegQueryValueEx(hn,"ProgramFilesDir", NULL, &type, (LPBYTE)name, &namelen);
	}
	::RegCloseKey(hn);


	if(lRet != ERROR_SUCCESS) 
	{
		strcpy(name,  "c:\\Program Files\\GME\\Interfaces");
	}
	else 
	{
		strncat(name, "\\GME\\Interfaces", sizeof(name)-1 - namelen);
	}

	m_strInterfacePath = name;


	RefreshOthers(); // Calls UpdateData

	/***** Generating UUIDs for the component interfaces *****/
	OnRegen();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInterior3::OnRegen() 
{
	GUID uid;
	OLECHAR buf[60];

	UpdateData(TRUE);

	#define DIM(x) (sizeof(x)/sizeof((x)[0]))

	if(CoCreateGuid(&uid) != S_OK || !StringFromGUID2(uid, buf, DIM(buf))) {
		m_strClassUUID = "<UUIDgen failure, enter manually!>";
	}
	else { 
		buf[wcslen(buf)-1] = OLECHAR(0);
		m_strClassUUID = buf+1;
	}

	if(CoCreateGuid(&uid) != S_OK || !StringFromGUID2(uid, buf, DIM(buf))) {
		m_strTypeLibUUID = "<UUIDgen failure, enter manually!>";
	}
	else { 
		buf[wcslen(buf)-1] = OLECHAR(0);
		m_strTypeLibUUID = buf+1;
	}
	UpdateData(FALSE);	
}

void CInterior3::OnBrowseGmeInterfaces() 
{
	CFolderDialog dlg(this,"Specify the location of GME interfaces:");
	
	if(dlg.DoModal()==IDOK)
	{
		m_strInterfacePath=dlg.GetPathName();
		UpdateData(FALSE);
	}	
}

void CInterior3::RefreshOthers()
{
	m_strProgID="MGA.Interpreter." + m_strComponentName;
	m_strClassName=CString("MGA Interpreter")+" CoClass (" + m_strComponentName + ")";
	m_strTypeLibName="MGA Interpreter TypeLibrary (" + m_strComponentName + ")";

	UpdateData(FALSE);
}

void CInterior3::OnPardigmIndependent() 
{
	UpdateData();

	if(m_bParadigmIndependent)
	{
		m_strParadigmName="*";
		m_ParadigmNameCtrl.EnableWindow(FALSE);
	}
	else
	{		
		m_strParadigmName="";
		m_ParadigmNameCtrl.EnableWindow(TRUE);
	}
	UpdateData(FALSE);
	
}

void CInterior3::OnChangeComponentName() 
{
	UpdateData();
	RefreshOthers();
}

LRESULT CInterior3::OnWizardNext() 
{
	UpdateData();

	if(m_strComponentName=="")
	{
		MessageBox("Please specify component name.","Udm Interpreter Wizard",MB_OK|MB_ICONERROR);
		return -1;
	}
	
	if(!m_bParadigmIndependent && m_strParadigmName=="")
	{
		MessageBox("Please specify paradigm name.","Udm Interpreter Wizard",MB_OK|MB_ICONERROR);
		return -1;
	}
		
	Generator.m_ComponentData.m_strInterfacePath=m_strInterfacePath;
	Generator.m_ComponentData.m_strClassName=m_strClassName;
	Generator.m_ComponentData.m_strComponentName=m_strComponentName;
	Generator.m_ComponentData.m_bParadigmIndependent=m_bParadigmIndependent;
	Generator.m_ComponentData.m_strParadigmName=m_strParadigmName;
	Generator.m_ComponentData.m_strProgID=m_strProgID;
	Generator.m_ComponentData.m_strTypeLibName=m_strTypeLibName;
	Generator.m_ComponentData.m_strClassUUID=m_strClassUUID;
	Generator.m_ComponentData.m_strTypeLibUUID=m_strTypeLibUUID;
	Generator.m_ComponentData.m_bIconInGME=m_bIconInGME;
	
	return CPropertyPageEx::OnWizardNext();
}
