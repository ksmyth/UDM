#define STRICT
#ifndef _WIN32_WINNT
#if _MSC_VER >= 1500
#define _WIN32_WINNT 0x0500		// Windows 2000 is the minimal version supported by VS 2008
#else
#define _WIN32_WINNT 0x0400
#endif
#endif
#include <windows.h>
#include <cstdio>
#include <tchar.h>
//#include <objbase.h>
//#include <atlbase.h>
//extern CComModule _Module;
//#include <atlcom.h>
//CComModule _Module;

/*
24/09/04	-	endre

			- removed  the UdmGme.h #include directive, and added the only function which is needed from that namespace
*/

#import "progid:Mga.MgaMetaFolder" version("1.0") no_implementation
#import "progid:Mga.MgaFolders" version("1.0") no_implementation
#import "progid:Mga.CoreBinFile" version("1.0") no_implementation
// GMELib
#import "libid:0ADEEC71-D83A-11D3-B36B-005004CC8592" no_implementation


//only this is needed from the UdmGme namespace.
namespace UdmGme
{
	void com_exception(HRESULT a, IUnknown *b, REFIID c);
};



#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif


#include "Uml.h"
#include "UmlExt.h"

#define _com_issue_errorex(a, b, c) UdmGme::com_exception(a, b, c)
