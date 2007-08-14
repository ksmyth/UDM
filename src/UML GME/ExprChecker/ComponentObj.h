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

#if !defined(AFX_INTERPRETEROBJ_H__1DBDD345_023D_11D2_BBB3_0040051F7117__INCLUDED_)
#define AFX_INTERPRETEROBJ_H__1DBDD345_023D_11D2_BBB3_0040051F7117__INCLUDED_


#include "ComHelp.h"
#include "GMECOM.h"
#include "ComponentConfig.h"
#include "UMLFacade.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CComponentObj;

//##############################################################################################################################################
//
//	C L A S S : CEventSink <<< + CCmdTarget
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

class CEventSink
	: public CCmdTarget
{

		DECLARE_DYNCREATE(CEventSink)
		CEventSink();

	public:
		CComponentObj* m_pComponentObj;

		IMgaEventSink* GetInterface() { return &m_xComponent; }

	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CComponentObj)
	public:
		virtual void OnFinalRelease();
		//}}AFX_VIRTUAL

	// Implementation

	protected:
		virtual ~CEventSink();

		DECLARE_MESSAGE_MAP()
		DECLARE_OLECREATE(CEventSink)

		// Generated OLE dispatch map functions
		//{{AFX_DISPATCH(CComponentObj)
			// NOTE - the ClassWizard will add and remove member functions here.
		//}}AFX_DISPATCH
		DECLARE_DISPATCH_MAP()

		DECLARE_INTERFACE_MAP()
	public:
		BEGIN_INTERFACE_PART( Component, IMgaEventSink )
			STDMETHODIMP GlobalEvent( globalevent_enum event );
			STDMETHODIMP ObjectEvent( IMgaObject * obj, unsigned long eventmask, VARIANT v );
		END_INTERFACE_PART( Component )
};

//##############################################################################################################################################
//
//	C L A S S : CCComponentObj <<< + CCmdTarget
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

class CComponentObj
	: public CCmdTarget
{

		DECLARE_DYNCREATE(CComponentObj)

		CComponentObj();           // protected constructor used by dynamic creation
		void RegisterActiveObject();
		unsigned long registeractiveobjectret;
		CComPtr<IMgaEventSink> 	m_spEventSink;
		CComPtr<IMgaProject> 		m_spProject;
		CComPtr<IMgaAddOn>		m_spAddOn;
		OCLUML::Facade				m_Facade;

	// Operations
	public:
		IMgaComponentEx* GetInterface() { return &m_xComponent; }

		STDMETHODIMP GlobalEvent( globalevent_enum event );
		STDMETHODIMP ObjectEvent( IMgaObject * obj, unsigned long eventmask, VARIANT v );

	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CComponentObj)
		public:
		virtual void OnFinalRelease();
		//}}AFX_VIRTUAL

	// Implementation
	protected:
		virtual ~CComponentObj();
		void UnregisterActiveObject();

		// Generated message map functions
		//{{AFX_MSG(CComponentObj)
			// NOTE - the ClassWizard will add and remove member functions here.
		//}}AFX_MSG

		DECLARE_MESSAGE_MAP()
		DECLARE_OLECREATE(CComponentObj)

		// Generated OLE dispatch map functions
		//{{AFX_DISPATCH(CComponentObj)
			// NOTE - the ClassWizard will add and remove member functions here.
		//}}AFX_DISPATCH
		DECLARE_DISPATCH_MAP()

		DECLARE_INTERFACE_MAP()
		BEGIN_INTERFACE_PART( Component, IMgaComponentEx )
			STDMETHODIMP InvokeEx( IMgaProject *project,  IMgaFCO *currentobj,  IMgaFCOs *selectedobjs, long param );
			STDMETHODIMP ObjectsInvokeEx( IMgaProject *project,  IMgaObject *currentobj,  IMgaObjects *selectedobjs,  long param );
			STDMETHODIMP Invoke( IMgaProject* gme, IMgaFCOs *models, long param );
			STDMETHODIMP Initialize( struct IMgaProject * );
			STDMETHODIMP Enable( VARIANT_BOOL newVal );
			STDMETHODIMP get_ComponentParameter( BSTR name, VARIANT *pVal );
			STDMETHODIMP put_ComponentParameter( BSTR name, VARIANT newVal );
			STDMETHODIMP get_InteractiveMode( VARIANT_BOOL *enabled );
			STDMETHODIMP put_InteractiveMode( VARIANT_BOOL enabled );
			STDMETHODIMP get_ComponentType( componenttype_enum *t );
			STDMETHODIMP get_ComponentProgID( BSTR *pVal );
			STDMETHODIMP get_ComponentName( BSTR *pVal );
			STDMETHODIMP get_Paradigm( BSTR *pVal);
		END_INTERFACE_PART(Component)

		BEGIN_INTERFACE_PART( VersionInfo, IMgaVersionInfo )
			STDMETHODIMP get_version( enum MgaInterfaceVersion *pVal );
		END_INTERFACE_PART(VersionInfo)
};

//##############################################################################################################################################
//
//	C L A S S : CPushRoutingFrame
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

class CPushRoutingFrame
{
	protected:
		CFrameWnd* pOldRoutingFrame;
		_AFX_THREAD_STATE* pThreadState;

	public:
		CPushRoutingFrame(CFrameWnd* pNewRoutingFrame)
		{
			pThreadState = AfxGetThreadState();
			pOldRoutingFrame = pThreadState->m_pRoutingFrame;
			pThreadState->m_pRoutingFrame = pNewRoutingFrame;
		}

		~CPushRoutingFrame()
		{
			pThreadState->m_pRoutingFrame = pOldRoutingFrame;
		}
};

//##############################################################################################################################################
//
//	C L A S S : CComponentReg
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

class CComponentReg
{
	public :
		CStringList paradigms;

	public:
					CComponentReg();
		HRESULT 	RegisterParadigms( regaccessmode_enum loc = REGACCESS_SYSTEM );
		HRESULT 	UnregisterParadigms( regaccessmode_enum loc = REGACCESS_SYSTEM );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERPRETEROBJ_H__1DBDD345_023D_11D2_BBB3_0040051F7117__INCLUDED_)