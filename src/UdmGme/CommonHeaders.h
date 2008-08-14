#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
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

#import "Meta.dll" no_implementation
#import "Mga.dll" no_implementation
#import "Gme.exe" no_implementation

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
