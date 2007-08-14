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
// Wizard97.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Wizard97.h"
#include "WizSheet.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizard97App

BEGIN_MESSAGE_MAP(CWizard97App, CWinApp)
	//{{AFX_MSG_MAP(CWizard97App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizard97App construction

CWizard97App::CWizard97App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWizard97App object

CWizard97App theApp;

static BOOL Is256ColorSupported()
{
	BOOL bRetval = FALSE;

	// return TRUE if screen deivce supports 256 colors or better

	HDC hdc = GetDC(NULL);
	if (hdc != NULL)
	{
		if(GetDeviceCaps(hdc, BITSPIXEL) >= 8)
			bRetval = TRUE;
		ReleaseDC(NULL, hdc);
	}

	return bRetval;
}


/////////////////////////////////////////////////////////////////////////////
// CWizard97App initialization

BOOL CWizard97App::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();         // Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();   // Call this when linking to MFC statically
#endif

	CBitmap bmpWatermark;
	CBitmap bmpHeader;	



	VERIFY(bmpWatermark.LoadBitmap(IDB_WATERMARK));
	VERIFY(bmpHeader.LoadBitmap(IDB_HEADER));


	CWizard97Sheet dlg(IDS_SAMPLEWIZARD, NULL, 0, bmpWatermark, NULL, bmpHeader);
	dlg.m_psh.hInstance = ::GetModuleHandle(NULL);
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	if (nResponse == IDCANCEL) // Cancel
	{

	}
	else // Finish 
	{
	
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
