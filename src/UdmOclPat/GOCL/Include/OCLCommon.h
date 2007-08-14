//###############################################################################################################################################
//
//	Object Constraint Language Generic Manager
//	OCLCommon.h
//
//###############################################################################################################################################

#ifndef OCLCommon_h
#define OCLCommon_h

/*
in case of VC 7.x we use MSVC's own STL

*/
#ifdef _WIN32
#if (_MSC_VER == 1200)
#include <stl_user_config.h>
#endif
#endif

#pragma warning ( disable : 4786 )

#include "vector"
#include "map"
#include "set"
#include "string"
#include "stdio.h"

#include "OCLConfig.h"

#define TABSTR "    "

typedef GOCL_STL_NS()vector< GOCL_STL_NS()string >	StringVector;
typedef StringVector			TypeSeq;

// bool operator!=( const GOCL_STL_NS()string& str1, const GOCL_STL_NS()string& str2 );

struct Position
{
	int iLine;
	int iColumn;
};

GOCL_STL_NS()string& Trim( GOCL_STL_NS()string& strIn );

typedef GOCL_STL_NS()map< int , Position > PositionMap;

namespace OclCommon {

	void Convert( const TypeSeq& ts, GOCL_STL_NS()string& s );
	int Convert( const GOCL_STL_NS()string& s, TypeSeq& ts );

}; // namespace OclCommon

#endif OCLCommon_h