//###############################################################################################################################################
//
//	Object Constraint Language Generic Manager
//	OCLCommon.cpp
//
//###############################################################################################################################################

#include "OCLCommon.h"

	GOCL_STL_NS()string& TrimLeft( GOCL_STL_NS()string& strIn )
	{
		while ( ! strIn.empty() && ( strIn[ 0 ] < 20 || strIn[ 0 ] == ' ' || strIn[ 0 ] == '\t' ) )
			strIn.erase( 0, 1 );
		return strIn;
	}

	GOCL_STL_NS()string& TrimRight( GOCL_STL_NS()string& strIn )
	{
		while ( ! strIn.empty() && ( strIn[ strIn.length() - 1 ] < 20 || strIn[ strIn.length() - 1 ] == ' ' || strIn[ strIn.length() - 1 ] == '\t' ) )
			strIn.erase( strIn.length() - 1, 1 );
		return strIn;
	}

	GOCL_STL_NS()string& Trim( GOCL_STL_NS()string& strIn )
	{
		return TrimRight( TrimLeft( strIn ) );
	}

	//bool operator!=( const GOCL_STL_NS()string& str1, const GOCL_STL_NS()string& str2 )
	//{
	//	return ! ( str1 == str2 );
	//}

namespace OclCommon {

	void convertR( const TypeSeq& si, int i, GOCL_STL_NS()string& s )
	{
		s += si[ i ];
		if ( si.size() >  i + 1 ) {
			s += "(";
			convertR( si, i + 1, s );
			s += ")";
		}
	}

	void Convert( const TypeSeq& si, GOCL_STL_NS()string& s )
	{
		s = "";
		if ( si.size() > 0 )
			convertR( si, 0, s );
	}

	int convertR( GOCL_STL_NS()string& s, TypeSeq& si, int i )
	{
		int p = s.find( '(' );
		if ( p == GOCL_STL_NS()string::npos ) {
			si.push_back( s );
			return 0;
		}
		if ( s[ s.length() - 1 ] != ')' )
			return i + s.length();
		GOCL_STL_NS()string strTemp = s.substr( 0, p );
		TrimRight( strTemp );
		if ( strTemp.empty() )
			return i;
		si.push_back( strTemp );
		strTemp = s.substr( p + 1, s.length() - 1 - p - 1 );
		TrimLeft( strTemp );
		i += s.length() - strTemp.length();
		TrimRight( strTemp );
		return convertR( strTemp, si, i );
	}

	int Convert( const GOCL_STL_NS()string& s, TypeSeq& si )
	{
		si.clear();
		GOCL_STL_NS()string ss( s );
		TrimLeft( ss );
		int i = s.length() - ss.length();
		TrimRight( ss );
		return convertR( ss, si, i );
	}

}; // namespace OclCommon


