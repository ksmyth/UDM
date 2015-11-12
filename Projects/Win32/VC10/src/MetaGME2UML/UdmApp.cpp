/*
Copyright (c) Vanderbilt University, 2000-2001
ALL RIGHTS RESERVED
Vanderbilt University disclaims all warranties with regard to this
software, including all implied warranties of merchantability
and fitness.  In no event shall Vanderbilt University be liable for
any special, indirect or consequential damages or any damages
whatsoever resulting from loss of use, data or profits, whether
in an action of contract, negligence or other tortious action,
arising out of or in connection with the use or performance of
this software.
*/


// UdmApp.cpp: implementation of the CUdmApp class.
// This file was automatically generated as UdmApp.cpp
// by UDM Interpreter Wizard on Monday, May 13, 2002 13:45:42

// Tihamér Levendovszky 05-13-02

#include "stdafx.h"
#include <afxdlgs.h> // For CFileDialog

//#include <iostream.h>
#include <atlbase.h>
#include <comdef.h>

#include <time.h>
#include "UdmStatic.h"
#include "UdmDom.h"
#include "UdmGME.h"
#include "UmlExt.h"
#include "UdmUtil.h"

#include "UdmApp.h"
#include "UdmConfig.h"

#include "MetaGME.h"
#include "UmlGME.h"
#include "MetaGME2UML.h"

#include "Mga.h"

using namespace std;

extern void dummy(void); // Dummy function for UDM meta initialization

/*********************************************************************************/
/* Initialization function. The framework calls it before preparing the backend. */
/* Initialize here the settings in the config static object.					 */
/* Return 0 if successful.														 */
/*********************************************************************************/
int CUdmApp::Initialize()
{
	// TODO: Your initialization code comes here...
	return 0;
}

bool AskUserForConstraint(long param)
{	
	if(param != GME_SILENT_MODE)
	{	if(IDYES == AfxMessageBox("The metamodel contains constrains.\nConstraints in MetaGME use a different syntax than those in UML.\nIf you choose to copy the constraints you will need to edit them by hand.\n\nDo you wish to copy the constraints?",MB_YESNO|MB_ICONINFORMATION))
			return true;
		return false;
	}
	else
	{	return false;
	}
}

/* 
Remarks to CUdmApp::UdmMain(...):
0.	The p_backend points to an already open backend, and the framework 
	closes it automatically. DO NOT OPEN OR CLOSE IT!
	To commit changes use p_backend->CommitEditSequence().
	To abort changes use p_backend->AbortEditSequence().
	To save changes to a different file use p_backend->SaveAs() or p_backend->CloseAs().

1.	Focus is the currently open model.

2.	The possible values for param (from GME DecoratorLib.h component_startmode_enum):
	GME_MAIN_START			=   0,
	GME_BROWSER_START		=   1,
	GME_CONTEXT_START		=   2,
	GME_EMBEDDED_START		=   3,
	GME_MENU_START			=  16,
	GME_BGCONTEXT_START		=  18,
	GME_ICON_START			=  32,
	METAMODEL_CHECK_SYNTAX	= 101

 3. The framework catches all the exceptions and reports the error in a message box,
	clean up and close the transactions aborting the changes. You can override this 
	behavior by catching udm_exception. Use udm_exception::what() to form an error 
	message.
*/

/***********************************************/
/* Main entry point for Udm-based Interpreter  */
/***********************************************/
using namespace std;

string CUdmApp::mgaDir;

void CUdmApp::UdmMain(
					 Udm::DataNetwork* p_backend,		// Backend pointer(already open!)
					 Udm::Object focusObject,			// Focus object
					 set<Udm::Object> selectedObjects,	// Selected objects
					 long param)						// Parameters
{	
	// TODO: Your Code Comes Here...
	try
	{
		unsigned int transconfig = 0;
				
		string rname = MetaGME::RootFolder::Cast(p_backend->GetRootObject()).name();
		string name = MetaGME::RootFolder::Cast(p_backend->GetRootObject()).name();
#ifdef UML_CLASS_DIAGRAM
		name += "_uml";
#else 
		name += "_umt";
#endif
		CString filename;

		CFileDialog getFile(false, ".mga", name.c_str(), OFN_HIDEREADONLY | OFN_NOCHANGEDIR, 
								"(*.xml;*.mga)|*.mga;*.xml|All Files (*.*)|*.*||" );
		if(param != GME_SILENT_MODE)
		{
			OPENFILENAME &ofn = getFile.GetOFN();
			ofn.lpstrInitialDir = CUdmApp::mgaDir.c_str();

			if(getFile.DoModal() != IDOK)
				return;
			filename = getFile.GetPathName();
		}
		else
			filename = (CUdmApp::mgaDir + name + ".mga").c_str();
			
		//AfxMessageBox(filename);
		Udm::Object rf;
		CComPtr<IMgaProject> mgaProject;

#ifdef UML_CLASS_DIAGRAM

		Udm::SmartDataNetwork umlGme(UmlGME::diagram);
		if (filename.Right(4) == ".mga") {
			mgaProject.CoCreateInstance(L"Mga.MgaProject", NULL, CLSCTX_INPROC);
			COMTHROW(mgaProject->Create(_bstr_t(CString(_T("MGA=")) + filename), _bstr_t(L"Uml")));
			CComPtr<IMgaTerritory> terr;
			COMTHROW(mgaProject->BeginTransactionInNewTerr(TRANSACTION_NON_NESTED, &terr));
			umlGme.OpenExisting_([&](const Udm::UdmDiagram &metaroot, Udm::UdmProject* pr) -> Udm::DataNetwork* {
				std::auto_ptr<UdmGme::GmeDataNetwork> dn1(new UdmGme::GmeDataNetwork(metaroot, pr));
				dn1->OpenExisting(mgaProject, Udm::CHANGES_LOST_DEFAULT, true);
				return dn1.release();
			});
		} else {
			umlGme.CreateNew((string)filename,"Uml", UmlGME::RootFolder::meta, Udm::CHANGES_LOST_DEFAULT);
		}
		try {
		UmlGME::RootFolder urf = UmlGME::RootFolder::Cast(umlGme.GetRootObject());
		urf.name() = rname;
		UmlGME::Package pac = UmlGME::Package::Create(urf);
		pac.name() = rname;
		rf = pac;
#else
		Udm::SmartDataNetwork umlGme(UmlGME::diagram);
		UmlGME::RootFolder trf;
		try
		{	
			umlGme.OpenExisting((string)filename,"UMLModelTransformer", Udm::CHANGES_LOST_DEFAULT);
			trf = UmlGME::RootFolder::Cast(umlGme.GetRootObject());
			trf.name() = (string)trf.name()+"_2_"+rname;
		}
		catch(udm_exception &exc)
		{	
			if(_stricmp(exc.what(), "Com exception: File could not be opened\n")!=0)
				throw exc;
			umlGme.CreateNew((string)filename,"UMLModelTransformer", UmlGME::RootFolder::meta, Udm::CHANGES_LOST_DEFAULT);
			trf = UmlGME::RootFolder::Cast(umlGme.GetRootObject());
			trf.name() = rname;
		}
//		vector<UmlGME::Package> pacs = trf.Package_kind_children();
//		for(vector<UmlGME::Package>::iterator i=pacs.begin(); i!=pacs.end(); i++)
//		{	UmlGME::Package pac = *i;
//			char id[30];
//			if((string)pac.name() == rname)
//			{	pac.name() = "old"+rname+ itoa(pac.uniqueId(),id,10);
//			}
//		}
		char id[30];
		UmlGME::Package pac = UmlGME::Package::Create(trf);
		pac.name() = "New"+rname+_itoa(pac.uniqueId(),id,10);
		rf = pac;
		try {
#endif
		{
		MetaGME2UML transformer(*p_backend, umlGme, rf, param);
		transformer.transformMetaGME2UmlGME();
		}

		//AfxMessageBox(((string)urf.name()).c_str());


		umlGme.CloseWithUpdate();
		} catch (...) {
			if (mgaProject)
			{
				mgaProject->AbortTransaction();
				mgaProject->Close(VARIANT_TRUE);
			}
			throw;
		}
		if (mgaProject)
		{
			COMTHROW(mgaProject->CommitTransaction());
			COMTHROW(mgaProject->Save(L"", VARIANT_TRUE));
			COMTHROW(mgaProject->Close(VARIANT_TRUE));
		}
		
		CString fn;
		if(param != GME_SILENT_MODE)
		{
			fn = getFile.GetFileName();
		}
		else
		{
			fn.Format("%s.mga",name.c_str());
		}

		if(param != GME_SILENT_MODE)
		{	AfxMessageBox("1. "+ fn + " has been Created\\Modified.\n2. Changes have been made to this metamodel.\n\nRun MetaGME Interpreter to reflect these changes in the paradigm.", MB_ICONINFORMATION);
		}
		else 
		{	cout << "1. "<< fn << " has been Created\\Modified.\n2. Changes have been made to this metamodel.\n\nRun MetaGME Interpreter to reflect these changes in the paradigm.\n";
		}
	}
	catch(udm_exception &exc) 
	{	if(param != GME_SILENT_MODE)
		{	AfxMessageBox(exc.what());
		}
		else
		{	cerr << exc.what();
		}
	}  
	catch(_com_error ce) 
	{	if(param != GME_SILENT_MODE)
		{	AfxMessageBox(ce.Description());
		}
		else
		{	cerr << (char*)ce.Description();
		}
	}
														
}


