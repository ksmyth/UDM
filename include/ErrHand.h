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

#ifndef MOBIES_ERRHAND_H
#define MOBIES_ERRHAND_H

#ifndef UDM_DYNAMIC_LINKING
#define UDM_DLL 
#else
#ifdef UDM_DLL_EXPORT
#define UDM_DLL __declspec(dllexport)
#else
#define UDM_DLL __declspec(dllimport)
#endif
#endif

#define UDM_ASSERT(x) assert(x)
#ifndef UDM_NO_DEFINE_ASSERT
#ifndef ASSERT
#define ASSERT assert
#endif
#endif

#include <exception>
#include <string>



#ifdef _WIN32
#if (_MSC_VER == 1600) /* VS2010 */
#define UDM_NAMESPACE Udm_VS10
namespace UDM_NAMESPACE {};
namespace Udm = UDM_NAMESPACE;
#if defined(_M_AMD64)
#ifdef _DEBUG
#define UDM_DLL_LIB "UdmDll_v100_x64D.lib"
#else
#define UDM_DLL_LIB "UdmDll_v100_x64.lib"
#endif
#elif defined(_M_IX86)
#ifdef _DEBUG
#define UDM_DLL_LIB "UdmDll_VS10D.lib"
#else
#define UDM_DLL_LIB "UdmDll_VS10.lib"
#endif
#endif
#define UDM_RVALUE
#else
#define UDM_NAMESPACE Udm
#ifdef _DEBUG
#define UDM_DLL_LIB "UdmDllD.lib"
#else
#define UDM_DLL_LIB "UdmDll.lib"
#endif
#endif /* _MSC_VER == 1600 */

#if defined(UDM_DYNAMIC_LINKING) && !defined(UDM_DLL_EXPORT) && defined(UDM_DLL_LIB)
#pragma comment(lib, UDM_DLL_LIB)
#endif
#else
#define UDM_NAMESPACE Udm
#endif /* _WIN32 */

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#define UDM_RVALUE
#endif

namespace UdmUtil {
	UDM_DLL std::string stacktrace();
}

class udm_exception : public std::exception
{
	std::string get_stacktrace()
	{
#ifdef UDM_EXCEPTION_USES_STACKTRACE
		return UdmUtil::stacktrace();
#else
		return "";
#endif
	}
public:
	udm_exception() throw() : stacktrace(get_stacktrace()) { _init(); }
	udm_exception(const udm_exception &a) throw() : description(a.description), stacktrace(get_stacktrace()) { _init(); }
	udm_exception(const std::string &d) throw() : description(d), stacktrace(get_stacktrace()) { _init(); }
	udm_exception(const char *d) throw() : description(d), stacktrace(get_stacktrace()) { _init(); }
	const udm_exception &operator =(const udm_exception &a) throw()
		{ description = a.description; stacktrace = get_stacktrace(); _init(); return *this; }
	virtual ~udm_exception() throw() { }
	virtual const char *what() const throw() { return descr_wstack.c_str(); }
	virtual const char *where() const throw() { return stacktrace.c_str(); }


protected:
	std::string description;
	std::string descr_wstack;
	std::string stacktrace;

	void _init() {
		descr_wstack = description;
		if (stacktrace != "") {
			descr_wstack += "\n";
			descr_wstack += stacktrace;
		}
	}

};
// int64

#ifndef _WIN32
#include <cstdio>
typedef long long __int64;
#define __int64() long long()
long long _atoi64(const char *x);
#endif

// --------------------------- STL

#define _NOTHREADS

//USE STLPort when using VC6.x

#if (_MSC_VER == 1200)
#include <stl_user_config.h>
#define UDM_OBJECT Object
#else
#define UDM_OBJECT Udm::Object
#endif

#ifndef UDM_NO_USING_STD
using namespace std;
#endif

#include <cassert>
#include <string>
#include <iostream>

#undef __SGI_STL_NO_ARROW_OPERATOR
#define __SGI_STL_INTERNAL_RELOPS


#endif//MOBIES_ERRHAND_H
