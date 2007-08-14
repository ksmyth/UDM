//###############################################################################################################################################
//
//	Object Constraint Language Expression Checker For UML
//	ComponentObj.h
//
//===============================================================================================================================================
//
//	Copyright (c) Vanderbilt University, 2000-2002
//	ALL RIGHTS RESERVED
//
//	Vanderbilt University disclaims all warranties with regard to this
//	software, including all implied warranties of merchantability
//	and fitness.  In no event shall Vanderbilt University be liable for
//	any special, indirect or consequential damages or any damages
//	whatsoever resulting from loss of use, data or profits, whether
//	in an action of contract, negligence or other tortious action,
//	arising out of or in connection with the use or performance of
//	this software.
//
//###############################################################################################################################################

#include "stdafx.h"

#include "GMECOM.h"
#include "ComHelp.h"
#include "ComponentLib.h"
#include "ComponentConfig.h"
#include "ComponentObj.h"
#include "ComponentLib_i.c"
#include "GMESyntacticSemanticDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// --------------------------------------- GmeDllDesc

// Syntax:
//   interpreter,<paradigm>,<description>,<progid>
//   plug-in,*,<description>,<progid>
//   add-on,<paradigm>,<progid>
//
// Examples:
//   L"<GMEDLLDESC> interpreter,SF,SF Code Generator,MGA.Component.SF <END>"
//   L"<GMEDLLDESC> add-on,*,My first general add-on,MGA.GenAddon.MyAddon <END>"

#define WCHAR_L() L
#define WCHAR(PAR) WCHAR_L()PAR

#ifdef PARADIGM_INDEPENDENT
#define EXCETYPE (componenttype_enum)(CETYPE|COMPONENTTYPE_PARADIGM_INDEPENDENT)
#undef PARADIGMS
#define PARADIGMS "*"
#else
#define EXCETYPE CETYPE
#endif


#ifdef GME_PLUGIN
wchar_t GmeDllDesc[] = L"<GMEDLLDESC> plug-in," L"," WCHAR(COMPONENT_NAME) L"," WCHAR(COCLASS_PROGID) L"<END>";
#define CETYPE	COMPONENTTYPE_PLUGIN
#else
#ifdef GME_ADDON
wchar_t GmeDllDesc[] = L"<GMEDLLDESC> add-on,*," WCHAR(COMPONENT_NAME) L"," WCHAR(COCLASS_PROGID) L"<END>";
#define CETYPE	COMPONENTTYPE_ADDON
#else
#ifdef GME_INTERPRETER
wchar_t GmeDllDesc[] = L"<GMEDLLDESC> interpreter," WCHAR(PARADIGMS) L"," WCHAR(COMPONENT_NAME) L"," WCHAR(COCLASS_PROGID) L"<END>";
#define CETYPE	COMPONENTTYPE_INTERPRETER
#else
#error No GME Componenttype (one of GME_PLUGIN, GME_ADDON, GME_INTERPRETER) is defined
#endif
#endif
#endif



#undef WCHAR_L
#undef WCHAR

//##############################################################################################################################################
//
//	C L A S S : CEventSink <<< + CCmdTarget
//
//##############################################################################################################################################

IMPLEMENT_DYNCREATE(CEventSink, CCmdTarget)

CEventSink::CEventSink()
{
	EnableAutomation();
	AfxOleLockApp();
}

CEventSink::~CEventSink()
{
	AfxOleUnlockApp();
}

BEGIN_MESSAGE_MAP(CEventSink, CCmdTarget)
	//{{AFX_MSG_MAP(CEventSink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CEventSink, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CEventSink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CEventSink, CCmdTarget)
	INTERFACE_PART(CEventSink, IID_IMgaEventSink, Component)
END_INTERFACE_MAP()

void CEventSink::OnFinalRelease()
{
	CCmdTarget::OnFinalRelease();
}

#define COMCLASS		CEventSink::XComponent
#define COMPROLOGUE	METHOD_PROLOGUE(CEventSink,Component)

STDMETHODIMP COMCLASS::GlobalEvent(globalevent_enum event)
{
	COMPROLOGUE;
	return pThis->m_pComponentObj->GlobalEvent( event );
}

STDMETHODIMP COMCLASS::ObjectEvent( IMgaObject *obj, unsigned long eventmask, VARIANT v )
{
	COMPROLOGUE;
	return pThis->m_pComponentObj->ObjectEvent( obj, eventmask, v );
}

STDMETHODIMP_(ULONG) COMCLASS::AddRef()
{
	COMPROLOGUE;
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) COMCLASS::Release()
{
	COMPROLOGUE;
	return pThis->ExternalRelease();
}

STDMETHODIMP COMCLASS::QueryInterface( REFIID riid, void** ppv )
{
	COMPROLOGUE;
	return pThis->ExternalQueryInterface( &riid, ppv );
}

#undef COMCLASS
#undef COMPROLOGUE

//##############################################################################################################################################
//
//	C L A S S : CComponentObj <<< + CCmdTarget
//
//##############################################################################################################################################

IMPLEMENT_DYNCREATE( CComponentObj, CCmdTarget )

CComponentObj::CComponentObj()
{
	EnableAutomation();
	AfxOleLockApp();

	registeractiveobjectret = 0;
}

void CComponentObj::RegisterActiveObject()
{
	ASSERT( registeractiveobjectret == 0 );
	COMVERIFY( ::RegisterActiveObject( GetInterface(), CLSID_MgaComponent, ACTIVEOBJECT_STRONG, &registeractiveobjectret) );
	ASSERT( registeractiveobjectret );
}

CComponentObj::~CComponentObj()
{
	ASSERT( registeractiveobjectret == 0 );
	AfxOleUnlockApp();
}

void CComponentObj::UnregisterActiveObject()
{
	ASSERT( registeractiveobjectret );
	COMVERIFY( ::RevokeActiveObject( registeractiveobjectret, NULL ) );
	registeractiveobjectret = 0;
}

void CComponentObj::OnFinalRelease()
{
	CCmdTarget::OnFinalRelease();
}

STDMETHODIMP CComponentObj::GlobalEvent( globalevent_enum event )
{
	return S_OK;
}

STDMETHODIMP CComponentObj::ObjectEvent( IMgaObject * obj, unsigned long eventmask, VARIANT v )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	if ( ! m_Facade.m_bEnabled )
		return S_OK;

	CWnd* pMainWindow = AfxGetApp()->m_pActiveWnd;

	COMTRY {

		if( ( eventmask & OBJEVENT_ATTR ) || ( eventmask & OBJEVENT_CONNECTED ) ) {

			CComQIPtr<IMgaFCO> spFCO = obj;
			if( spFCO ) {
				GOCL_STL_NS()string strKind = GME::GetObjectKind( spFCO.p );
				if ( strKind == "Constraint" ) {
					CWaitCursor crsrWait;
					OCLUML::ConstraintVector vecConstraints;
					m_Facade.CheckConstraint( spFCO.p, vecConstraints, false );
					if ( ! vecConstraints.empty() ) {
						CSyntacticSemanticDialog dlgErrors( pMainWindow );
						for ( int i = 0 ; i < vecConstraints.size() ; i++ )
							dlgErrors.AddItem( vecConstraints[ i ] );
						crsrWait.Restore();
						dlgErrors.DoModal();
					}
					else
						crsrWait.Restore();
				}
				if ( strKind == "ConstraintDefinition" ) {
					CWaitCursor crsrWait;
					OCLUML::ConstraintDefVector vecConstraintDefinitions;
					m_Facade.CheckConstraintDefinition( spFCO.p, vecConstraintDefinitions, false );
					if ( ! vecConstraintDefinitions.empty() ) {
						CSyntacticSemanticDialog dlgErrors( pMainWindow );
						for ( int i = 0 ; i < vecConstraintDefinitions.size() ; i++ )
							dlgErrors.AddItem( vecConstraintDefinitions[ i ] );
						crsrWait.Restore();
						dlgErrors.DoModal();
					}
					else
						crsrWait.Restore();
				}
				m_Facade.Finalize();
			}
		}

	} COMCATCH( ASSERT( 0 ); )

	return S_OK;
}

BEGIN_MESSAGE_MAP(CComponentObj, CCmdTarget)
	//{{AFX_MSG_MAP(CComponentObj)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CComponentObj, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CComponentObj)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: We get the type and name of the embedded class
// "XComponent" and "m_xComponent" from the "Component" parameter

BEGIN_INTERFACE_MAP(CComponentObj, CCmdTarget)
	INTERFACE_PART(CComponentObj, IID_IMgaComponentEx, Component)
	INTERFACE_PART(CComponentObj, IID_IMgaComponent, Component)
	INTERFACE_PART(CComponentObj, IID_IMgaVersionInfo, VersionInfo)
END_INTERFACE_MAP()

// We register the ComponentClass
// CLSID_MGAComponentClass

IMPLEMENT_OLECREATE(CComponentObj, COCLASS_PROGID,
COCLASS_UUID_EXPLODED1,
COCLASS_UUID_EXPLODED2,
COCLASS_UUID_EXPLODED3,
COCLASS_UUID_EXPLODED4,
COCLASS_UUID_EXPLODED5,
COCLASS_UUID_EXPLODED6,
COCLASS_UUID_EXPLODED7,
COCLASS_UUID_EXPLODED8,
COCLASS_UUID_EXPLODED9,
COCLASS_UUID_EXPLODED10,
COCLASS_UUID_EXPLODED11
)

//##############################################################################################################################################
//
//	I N T E R F A C E  : CComponentObj::XComponent <<< + IMgaComponent
//
//##############################################################################################################################################

#define COMCLASS		CComponentObj::XComponent
#define COMPROLOGUE	METHOD_PROLOGUE( CComponentObj, Component )

STDMETHODIMP_(ULONG) COMCLASS::AddRef()
{
	COMPROLOGUE;
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) COMCLASS::Release()
{
	COMPROLOGUE;
	return pThis->ExternalRelease();
}

STDMETHODIMP COMCLASS::QueryInterface( REFIID riid, void** ppv )
{
	COMPROLOGUE;
	return pThis->ExternalQueryInterface( &riid, ppv );
}

STDMETHODIMP COMCLASS::Invoke( IMgaProject *gme, IMgaFCOs *psa, long param )
{
	COMPROLOGUE;
	return InvokeEx( gme, NULL, psa, param );
}

STDMETHODIMP COMCLASS::InvokeEx( IMgaProject *gme,  IMgaFCO *currentobj,  IMgaFCOs *selectedobjs,  long param )
{
	COMPROLOGUE;
	return S_OK;
}

STDMETHODIMP COMCLASS::ObjectsInvokeEx( IMgaProject *gme,  IMgaObject *currentobj,  IMgaObjects *selectedobjs,  long param )
{
	COMPROLOGUE;

	if ( ! pThis->m_Facade.m_bEnabled )
		return S_OK;

	CPushRoutingFrame temp( NULL );
	{
		AFX_MANAGE_STATE( AfxGetStaticModuleState() );

		COMTRY {

			CWaitCursor crsrWait;

			OCLUML::ConstraintVector vecConstraints;
			pThis->m_Facade.CheckAllConstraints( vecConstraints );

			crsrWait.Restore();

			if ( ! vecConstraints.empty() ) {
				CSyntacticSemanticDialog dlgErrors( AfxGetApp()->m_pActiveWnd );
				for ( int i = 0 ; i < vecConstraints.size() ; i++ )
					dlgErrors.AddItem( vecConstraints[ i ] );
				dlgErrors.DoModal();
			}
			pThis->m_Facade.Finalize();

		} COMCATCH( ASSERT( 0 ); )
	}
	return S_OK;
}

STDMETHODIMP COMCLASS::Initialize( struct IMgaProject *p )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	COMTRY {
		COMPROLOGUE;

		pThis->m_spProject = p;

		CEventSink *pEventSink = new CEventSink;
		pThis->m_spEventSink = &pEventSink->m_xComponent;
		pEventSink->m_pComponentObj = pThis;

		pThis->m_spAddOn = NULL;
		COMTHROW( p->CreateAddOn( pThis->m_spEventSink, &( pThis->m_spAddOn ) ) );
		COMTHROW( pThis->m_spAddOn->put_EventMask( ADDON_EVENTMASK ) );

		pThis->m_Facade.Initialize( p );

	} COMCATCH( ASSERT( 0 ); );

	return S_OK;
};

STDMETHODIMP COMCLASS::Enable( VARIANT_BOOL newVal )
{
	COMPROLOGUE;
	pThis->m_Facade.m_bEnabled = ( newVal ) ? true : false;
	return S_OK;
};

STDMETHODIMP COMCLASS::get_InteractiveMode( VARIANT_BOOL *enabled )
{
	COMPROLOGUE;
	*enabled = ( pThis->m_Facade.m_bEnabledInteractions ) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
};

STDMETHODIMP COMCLASS::put_InteractiveMode( VARIANT_BOOL enabled )
{
	COMPROLOGUE;
	pThis->m_Facade.m_bEnabledInteractions = ( enabled ) ? true : false;
	return S_OK;
};

STDMETHODIMP COMCLASS::get_ComponentParameter( BSTR name, VARIANT *pVal )
{
	COMPROLOGUE;
	return S_OK;
}

STDMETHODIMP COMCLASS::put_ComponentParameter( BSTR name, VARIANT newVal )
{
	COMPROLOGUE;
	return S_OK;
}

STDMETHODIMP COMCLASS::get_ComponentType( componenttype_enum *t )
{
	COMPROLOGUE;
	*t = EXCETYPE;
	return S_OK;
}

STDMETHODIMP COMCLASS::get_ComponentProgID( BSTR *pVal )
{
	*pVal = CComBSTR( COCLASS_PROGID ).Detach();
	return S_OK;
};

STDMETHODIMP COMCLASS::get_ComponentName( BSTR *pVal )
{
	*pVal = CComBSTR( COMPONENT_NAME ).Detach();
	return S_OK;
};

STDMETHODIMP COMCLASS::get_Paradigm( BSTR *pVal)\
{
	*pVal = CComBSTR( PARADIGMS ).Detach();
	return S_OK;
};

#undef COMCLASS
#undef COMPROLOGUE

//##############################################################################################################################################
//
//	I N T E R F A C E  : CComponentObj::XVersionInfo <<< + IMgaVersionInfo
//
//##############################################################################################################################################

#define COMCLASS		CComponentObj::XVersionInfo
#define COMPROLOGUE	METHOD_PROLOGUE( CComponentObj, VersionInfo )

STDMETHODIMP_(ULONG) COMCLASS::AddRef()
{
	COMPROLOGUE;
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) COMCLASS::Release()
{
	COMPROLOGUE;
	return pThis->ExternalRelease();
}

STDMETHODIMP COMCLASS::QueryInterface( REFIID riid, void** ppv )
{
	COMPROLOGUE;
	return pThis->ExternalQueryInterface( &riid, ppv );
}

STDMETHODIMP COMCLASS::get_version( enum MgaInterfaceVersion *pVal )
{
	COMPROLOGUE;

	if( pVal == NULL )
		return E_POINTER;

	*pVal = MgaInterfaceVersion_Current;
	return S_OK;
}

#undef COMCLASS
#undef COMPROLOGUE

//##############################################################################################################################################
//
//	C L A S S : CComponentReg
//
//##############################################################################################################################################

CComponentReg::CComponentReg()
{

#ifndef GME_PLUGIN
	CString pars = PARADIGMS;
#ifndef PARADIGM_INDEPENDENT
	while( !pars.IsEmpty() )
	{
		CString trash = pars.SpanIncluding(" ,;");
		pars = pars.Mid(trash.GetLength());
		if( pars.IsEmpty() )
			break;
		CString par = pars.SpanExcluding(" ,;");
		pars = pars.Mid(par.GetLength());
		ASSERT(!par.IsEmpty());
		paradigms.AddTail(par);
	}
#endif
#endif
}


#define COMRETURN(hr) { HRESULT res; if((res = (hr)) != S_OK) return res; }

HRESULT CComponentReg::UnregisterParadigms(regaccessmode_enum loc) {
	CComPtr<IMgaRegistrar> registrar;
	COMRETURN(registrar.CoCreateInstance(OLESTR("Mga.MgaRegistrar")));
	COMRETURN(registrar->UnregisterComponent(CComBSTR(COCLASS_PROGID), loc));
	return S_OK;
}

HRESULT CComponentReg::RegisterParadigms(regaccessmode_enum loc) {
	CComPtr<IMgaRegistrar> registrar;
	COMRETURN(registrar.CoCreateInstance(OLESTR("Mga.MgaRegistrar")));
	COMRETURN(registrar->RegisterComponent(CComBSTR(COCLASS_PROGID),EXCETYPE, CComBSTR(COMPONENT_NAME), loc));
#ifdef BON_ICON_SUPPORT
	COMRETURN(registrar->put_ComponentExtraInfo(loc, CComBSTR(COCLASS_PROGID), CComBSTR("Icon"), CComBSTR(",IDI_COMPICON")));
#endif
	POSITION pos = paradigms.GetHeadPosition();
	while(pos)
	{
		CString paradigm = paradigms.GetNext(pos);
		COMRETURN(registrar->Associate(CComBSTR(COCLASS_PROGID), CComBSTR(paradigm), loc));
	}
	return S_OK;
}

