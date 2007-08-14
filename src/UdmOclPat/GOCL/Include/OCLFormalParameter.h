//###############################################################################################################################################
//
//	Object Constraint Language Generic Manager
//	OCLFormalParameter.h
//
//###############################################################################################################################################

#ifndef OCLFormalParameter_h
#define OCLFormalParameter_h

#pragma warning ( disable : 4786 )

#include "OCLCommon.h"

namespace OclCommon
{
	class FormalParameter;
	typedef GOCL_STL_NS()vector< FormalParameter > FormalParameterVector;

//##############################################################################################################################################
//
//	C L A S S : OclMeta::FormalParameter
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class FormalParameter
	{
		private :
			GOCL_STL_NS()string	m_strName;
			GOCL_STL_NS()string	m_strType;
			bool	m_bRequired;

		public :
			FormalParameter( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strType, bool bRequired )
				: m_strName( strName ), m_strType( strType ), m_bRequired( bRequired )
			{
			}

			FormalParameter( const GOCL_STL_NS()string& strType, bool bRequired )
				: m_strName( "" ), m_strType( strType ), m_bRequired( bRequired )
			{
			}

			FormalParameter()
				: m_strName( "" ), m_strType( "" ), m_bRequired( false )
			{
			}

			FormalParameter( const FormalParameter& object )
				: m_strName( object.m_strName ), m_strType( object.m_strType ), m_bRequired( object.m_bRequired )
			{
			}

			FormalParameter& operator=( const FormalParameter& object )
			{
				if ( this != &object ) {
					m_strName = object.m_strName;
					m_strType = object.m_strType;
					m_bRequired = object.m_bRequired;
				}
				return *this;
			}

			bool IsIdentical( const FormalParameter& object ) const
			{
				return m_strType == object.m_strType;
			}

			bool IsIdentical( const GOCL_STL_NS()string& strType ) const
			{
				return m_strType == strType;
			}

			bool operator==( const FormalParameter& object ) const
			{
				return IsIdentical( object ) && m_strName == object.m_strName && m_bRequired == object.m_bRequired;
			}

			bool operator!=( const FormalParameter& object ) const
			{
				return ! ( *this == object );
			}

			bool IsRequired() const
			{
				return m_bRequired;
			}

			GOCL_STL_NS()string GetName() const
			{
				return m_strName;
			}

			GOCL_STL_NS()string GetTypeName() const
			{
				return m_strType;
			}
	};

}; // namespace OclCommon

#endif // OCLFormalParameter_h
