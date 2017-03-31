///////////////////////////////////////////////////////////////////////////
// RawComponent.cpp, the main RAW COM component implementation file
// This is the file (along with its header RawComponent.h)
// that the component implementor is expected to modify in the first place
//
///////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "ComHelp.h"
#include "GMECOM.h"
#include "ComponentConfig.h"
#include "UdmConfig.h"
#include "RawComponent.h"

// Udm includes
#include "UdmBase.h"
#include "Uml.h"
#include "UmlExt.h"

#include "UdmGme.h"
#include "UdmStatic.h"
#include "UdmUtil.h"

#include "UdmApp.h"

#include "Gme.h"
#include "UdmConsole.h"

// #include "MetaGME.cpp"
// #include "UmlGME.cpp"

// Global config object
_config config;


// this method is called after all the generic initialization is done
// this should be empty, unless application-specific initialization is needed
STDMETHODIMP RawComponent::Initialize(struct IMgaProject *) {
	return S_OK;
}

// this is the obsolete component interface
// this present implementation either tries to call InvokeEx, or returns an error;
STDMETHODIMP RawComponent::Invoke(IMgaProject* gme, IMgaFCOs *models, long param) {
#ifdef SUPPORT_OLD_INVOKE
	CComPtr<IMgaFCO> focus;
	CComVariant parval = param;
	return InvokeEx(gme, focus, selected, parvar);
#else
	if(interactive) {
		AfxMessageBox("This component does not support the obsolete invoke mechanism");
	}
	return E_MGA_NOT_SUPPORTED;
#endif
}

#ifdef _DYNAMIC_META
			void dummy(void) {; } // Dummy function for UDM meta initialization
#endif

// This is the main component method for interpereters and plugins. 
// May als be used in case of invokeable addons
STDMETHODIMP RawComponent::InvokeEx( IMgaProject *project,  IMgaFCO *currentobj,  
									IMgaFCOs *selectedobjs,  long param) 
{
	// Calling the user's initialization function
	if(CUdmApp::Initialize())
	{
		return S_FALSE;
	}

	CComPtr<IMgaProject>ccpProject(project);
	try
	{
		CComBSTR projname;
		CComBSTR focusname = "<nothing>";
		CComPtr<IMgaTerritory> terr;
		COMTHROW(ccpProject->CreateTerritory(NULL, &terr));

		CComPtr<IMgaProject> mgaProject = project;
		CComBSTR    connString;
		COMTHROW(mgaProject->get_ProjectConnStr(&connString));

		CString mgaFilePath = connString;
		int e = mgaFilePath.ReverseFind('\\');
		if(e != -1)
		{	
			CUdmApp::mgaDir = mgaFilePath.Mid(4, e-3);
		}

		// Setting up Udm	
		using namespace META_NAMESPACE;
		
		// Loading the project			
		UdmGme::GmeDataNetwork dngBackend(META_NAMESPACE::diagram);				
					
		try
		{
			COMTHROW(ccpProject->BeginTransactionInNewTerr(TRANSACTION_NON_NESTED, &terr));
			try {
			// Opening backend
			dngBackend.OpenExisting(ccpProject, Udm::CHANGES_LOST_DEFAULT, true);
			

			CComPtr<IMgaFCO> ccpFocus(currentobj);
			Udm::Object currentObject;
			if(ccpFocus)
			{
				currentObject=dngBackend.Gme2Udm(ccpFocus);
			}

			std::set<Udm::Object> selectedObjects;

			if (selectedobjs) {
				CComPtr<IMgaFCOs> ccpSelObject(selectedobjs);

				MGACOLL_ITERATE(IMgaFCO,ccpSelObject){		 
					Udm::Object currObj;
					if(MGACOLL_ITER)
					{
						currObj=dngBackend.Gme2Udm(MGACOLL_ITER);
					}
				 selectedObjects.insert(currObj);
				}MGACOLL_ITERATE_END;
			}

			// Calling the main entry point
			CUdmApp::UdmMain(&dngBackend,currentObject,selectedObjects,param);
			// Closing backend
			dngBackend.CloseWithUpdate();
			} catch (...) {
				ccpProject->AbortTransaction();
				throw;
			}
			COMTHROW(ccpProject->CommitTransaction());

		}
		catch(udm_exception &exc) 
		{
#ifdef _META_ACCESS_MEMORY
			dnCacheBackend.CloseNoUpdate();
#endif
			// Close GME Backend (we may close it twice, but GmeDataNetwork handles it)
			dngBackend.CloseNoUpdate();			

			if (interactive)
				AfxMessageBox(exc.what());
			GMEConsole::Console::Error::writeLine(exc.what());
			return E_FAIL;
		}
	}
	catch(udm_exception &exc) 
	{	
		if (interactive)
			AfxMessageBox(exc.what());
		GMEConsole::Console::Error::writeLine(exc.what());
		return E_FAIL;
	}			 
	catch(...) 
	{
		ccpProject->AbortTransaction();
		if (interactive)
			AfxMessageBox("An unexpected error has occured during the interpretation process.");
		GMEConsole::Console::Error::writeLine("An unexpected error has occured during the interpretation process.");
		return E_UNEXPECTED;
	}
	return S_OK;
}

// GME currently does not use this function
// you only need to implement it if other invokation mechanisms are used
STDMETHODIMP RawComponent::ObjectsInvokeEx( IMgaProject *project,  IMgaObject *currentobj,  IMgaObjects *selectedobjs,  long param) {
	if(interactive) {
		AfxMessageBox("The ObjectsInvoke method is not implemented");
	}
	return E_MGA_NOT_SUPPORTED;
}


// implement application specific parameter-mechanism in these functions:
STDMETHODIMP RawComponent::get_ComponentParameter(BSTR name, VARIANT *pVal) {
	return S_OK;
}

STDMETHODIMP RawComponent::put_ComponentParameter(BSTR name, VARIANT newVal) {
	return S_OK;
}


#ifdef GME_ADDON

// these two functions are the main 
STDMETHODIMP RawComponent::GlobalEvent(globalevent_enum event) { 
	if(event == GLOBALEVENT_UNDO) {
		AfxMessageBox("UNDO!!");
	}
	return S_OK; 
}

STDMETHODIMP RawComponent::ObjectEvent(IMgaObject * obj, unsigned long eventmask, VARIANT v) {
	if(eventmask & OBJEVENT_CREATED) {
		CComBSTR objID;
		COMTHROW(obj->get_ID(&objID));
		AfxMessageBox( "Object created! ObjID: " + CString(objID)); 
	}		
	return S_OK;
}

#endif
