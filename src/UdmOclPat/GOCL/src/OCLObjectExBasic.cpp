//###############################################################################################################################################
//
//	Object Constraint Language Generic Manager
//	OCLObjectExBasic.cpp
//
//###############################################################################################################################################

#include "OCLObjectExBasic.h"
#include "OCLType.h"
#include "algorithm"

namespace OclBasic
{

//##############################################################################################################################################
//
//	F U N C T I O N S
//
//##############################################################################################################################################

	GOCL_STL_NS()string PrintCollection( const GOCL_STL_NS()string& strTypeName, const OclMeta::ObjectVector& vecElements )
	{
		char chBuffer[ 100 ];
		sprintf( chBuffer, "%d", vecElements.size() );
		return strTypeName + " { size: " + GOCL_STL_NS()string( chBuffer ) + "; } ";
		/*
		GOCL_STL_NS()string strObject = strTypeName + " { " + GOCL_STL_NS()string( chBuffer ) + " , [ ";
		for ( int i = 0 ; i < vecElements.size() ; i++ ) {
			strObject = vecElements[ i ].Print();
			if ( i != vecElements.size() - 1 )
				strObject += ", ";
		}
		return strObject + " ] }";
		*/

	}

	int GetObjectCountInVector( OclMeta::ObjectVector& vecObjects, OclMeta::Object& object )
	{
		int i = 0;
		OclMeta::ObjectVector::iterator j = GOCL_STL_NS()find( vecObjects.begin(), vecObjects.end(), object );
		while ( j != vecObjects.end() ) {
			i++;
			vecObjects.erase( j );
			j = GOCL_STL_NS()find( vecObjects.begin(), vecObjects.end(), object );
		}
		return i;
	}

//##############################################################################################################################################
//
//	C L A S S : OclBasic::String <<< + OclBasic::Any
//
//##############################################################################################################################################

	String::String( OclMeta::TypeManager* pManager, const GOCL_STL_NS()string& strTypeName, const GOCL_STL_NS()string& value )
		: Any( pManager, strTypeName ), m_Value( value )
	{
	}


	String::String( OclMeta::TypeManager* pManager, const GOCL_STL_NS()string& value )
		: Any( pManager, "ocl::String" ), m_Value( value )
	{
	}

	void String::GetValue( GOCL_STL_NS()string& value ) const
	{
		value = m_Value;
	}

	void String::SetValue( const GOCL_STL_NS()string& value )
	{
		m_Value = value;
	}

	Any* String::Clone() const
	{
		return new String( GetTypeManager(), m_Value );
	}

	bool String::Equals( const Any& object ) const
	{
		if ( GetTypeManager()->IsTypeA( object.GetTypeName(), "ocl::String" ) >= 0 )
			return m_Value == ( ( String* ) &object )->m_Value;
		else
			return false;
	}

	bool String::operator==( const String& object ) const
	{
		return Equals( object );
	}

	bool String::operator!=( const String& object ) const
	{
		return ! ( *this == object );
	}

	GOCL_STL_NS()string String::Print() const
	{
		return "ocl::String { \"" + m_Value + "\" }";
	}

//##############################################################################################################################################
//
//	C L A S S : OclBasic::Enumeration <<< + OclBasic::Any
//
//##############################################################################################################################################

	Enumeration::Enumeration( OclMeta::TypeManager* pManager, const GOCL_STL_NS()string& strTypeName, const GOCL_STL_NS()string& value )
		: Any( pManager, strTypeName ), m_Value( value )
	{
	}

	Enumeration::Enumeration( OclMeta::TypeManager* pManager, const GOCL_STL_NS()string& value )
		: Any( pManager, "ocl::Enumeration" ), m_Value( value )
	{
	}

	void Enumeration::GetValue( GOCL_STL_NS()string& value ) const
	{
		value = m_Value;
	}

	void Enumeration::SetValue( const GOCL_STL_NS()string& value )
	{
		m_Value = value;
	}

	Any* Enumeration::Clone() const
	{
		return new Enumeration( GetTypeManager(), m_Value );
	}

	bool Enumeration::Equals( const Any& object ) const
	{
		if ( GetTypeManager()->IsTypeA( object.GetTypeName(), "ocl::Enumeration" ) >= 0 )
			return m_Value == ( ( Enumeration* ) &object )->m_Value;
		else
			return false;
	}

	bool Enumeration::operator==( const Enumeration& object ) const
	{
		return Equals( object );
	}

	bool Enumeration::operator!=( const Enumeration& object ) const
	{
		return ! ( *this == object );
	}

	GOCL_STL_NS()string Enumeration::Print() const
	{
		return "ocl::Enumeration { #" + m_Value + " }";
	}

//##############################################################################################################################################
//
//	C L A S S : OclBasic::Boolean <<< + OclBasic::Any
//
//##############################################################################################################################################

	Boolean::Boolean( OclMeta::TypeManager* pManager, const GOCL_STL_NS()string& strTypeName, bool value )
		: Any( pManager, strTypeName ), m_Value( value )
	{
	}

	Boolean::Boolean( OclMeta::TypeManager* pManager, bool value )
		: Any( pManager, "ocl::Boolean" ), m_Value( value )
	{
	}

	void Boolean::GetValue( bool& value ) const
	{
		value = m_Value;
	}

	void Boolean::SetValue( bool value )
	{
		m_Value = value;
	}

	Any* Boolean::Clone() const
	{
		return new Boolean( GetTypeManager(), m_Value );
	}

	bool Boolean::Equals( const Any& object ) const
	{
		if ( GetTypeManager()->IsTypeA( object.GetTypeName(), "ocl::Boolean" ) >= 0 )
			return m_Value == ( ( Boolean* ) &object )->m_Value;
		else
			return false;
	}

	bool Boolean::operator==( const Boolean& object ) const
	{
		return Equals( object );
	}

	bool Boolean::operator!=( const Boolean& object ) const
	{
		return ! ( *this == object );
	}

	GOCL_STL_NS()string Boolean::Print() const
	{
		return ( m_Value ) ? "ocl::Boolean { true }" : "ocl::Boolean { false }";
	}

//##############################################################################################################################################
//
//	C L A S S : OclBasic::Real <<< + OclBasic::Any
//
//##############################################################################################################################################

	Real::Real( OclMeta::TypeManager* pManager, const GOCL_STL_NS()string& strTypeName, double value )
		: Any( pManager, strTypeName ), m_Value( value )
	{
	}

	Real::Real( OclMeta::TypeManager* pManager, double value )
		: Any( pManager, "ocl::Real" ), m_Value( value )
	{
	}

	void Real::GetValue( double& value ) const
	{
		value = m_Value;
	}

	void Real::SetValue( double value )
	{
		m_Value = value;
	}

	Any* Real::Clone() const
	{
		return new Real( GetTypeManager(), m_Value );
	}

	bool Real::Equals( const Any& object ) const
	{
		if ( GetTypeManager()->IsTypeA( object.GetTypeName(), "ocl::Real" ) >= 0 ) {
			double v = ( ( Real* ) &object )->m_Value;
			return m_Value == v;
		}
		else
			return false;
	}

	bool Real::operator==( const Real& object ) const
	{
		return Equals( object );
	}

	bool Real::operator!=( const Real& object ) const
	{
		return ! ( *this == object );
	}

	GOCL_STL_NS()string Real::Print() const
	{
		char chBuffer[ 100 ];
		sprintf( chBuffer, "%f", m_Value );
		return "ocl::Real { " + GOCL_STL_NS()string( chBuffer ) + " }";
	}

//##############################################################################################################################################
//
//	C L A S S : OclBasic::Integer <<< + OclBasic::Real
//
//##############################################################################################################################################

	Integer::Integer( OclMeta::TypeManager* pManager, const GOCL_STL_NS()string& strTypeName, long value )
		: Real( pManager, strTypeName, (double) value )
	{
	}

	Integer::Integer( OclMeta::TypeManager* pManager, long value )
		: Real( pManager, "ocl::Integer", (double) value )
	{
	}

	void Integer::GetValue( long& value ) const
	{
		double dValue;
		Real::GetValue( dValue );
		value = (long) dValue;
	}

	void Integer::SetValue( long value )
	{
		SetValue( (double) value );
	}

	Any* Integer::Clone() const
	{
		long lValue;
		GetValue( lValue );
		return new Integer( GetTypeManager(), lValue );
	}

	bool Integer::operator==( const Integer& object ) const
	{
		return Real::operator==( object );
	}

	bool Integer::operator!=( const Integer& object ) const
	{
		return ! ( *this == object );
	}

	GOCL_STL_NS()string Integer::Print() const
	{
		double lValue;
		Real::GetValue( lValue );
		char chBuffer[ 100 ];
		sprintf( chBuffer, "%d", (long) lValue );
		return "ocl::Integer { " + GOCL_STL_NS()string( chBuffer ) + " }";
	}

//##############################################################################################################################################
//
//	C L A S S : OclBasic::Type <<< + OclBasic::Any
//
//##############################################################################################################################################

	Type::Type( OclMeta::TypeManager* pManager, const GOCL_STL_NS()string& strTypeName, const GOCL_STL_NS()string& value )
		: Any( pManager, strTypeName ), m_Value( value )
	{
	}


	Type::Type( OclMeta::TypeManager* pManager, const GOCL_STL_NS()string& value )
		: Any( pManager, "ocl::Type" ), m_Value( value )
	{
	}

	void Type::GetValue( GOCL_STL_NS()string& value ) const
	{
		value = m_Value;
	}

	void Type::SetValue( const GOCL_STL_NS()string& value )
	{
		m_Value = value;
	}

	Any* Type::Clone() const
	{
		return new Type( GetTypeManager(), m_Value );
	}

	bool Type::Equals( const Any& object ) const
	{
		if ( GetTypeManager()->IsTypeA( object.GetTypeName(), "ocl::Type" ) >= 0 )
			return m_Value == ( ( Type* ) &object )->m_Value;
		else
			return false;
	}

	bool Type::operator==( const Type& object ) const
	{
		return Equals( object );
	}

	bool Type::operator!=( const Type& object ) const
	{
		return ! ( *this == object );
	}

	GOCL_STL_NS()string Type::Print() const
	{
		return "ocl::Type { \"" + m_Value + "\" }";
	}

//##############################################################################################################################################
//
//	C L A S S : OclBasic::ObjectIterator <<< + OclImplementation::ObjectIterator
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class ObjectIterator
		: public OclImplementation::ObjectIterator
	{
		private :
			OclMeta::ObjectVector::iterator m_iteratorPos;
			OclMeta::ObjectVector::iterator m_iteratorEnd;

		public :
			ObjectIterator( OclMeta::ObjectVector::iterator iteratorBegin, OclMeta::ObjectVector::iterator iteratorEnd )
				: OclImplementation::ObjectIterator(), m_iteratorPos( iteratorBegin ), m_iteratorEnd( iteratorEnd )
			{
			}

			virtual ~ObjectIterator()
			{
			}

			virtual bool HasNext()
			{
				return m_iteratorPos != m_iteratorEnd;
			}

			virtual OclMeta::Object GetNext()
			{
				return *( m_iteratorPos++ );
			}
	};

//##############################################################################################################################################
//
//	C L A S S : OclBasic::Set <<< + OclBasic::Collection
//
//##############################################################################################################################################

	Set::Set( OclMeta::TypeManager* pManager, const GOCL_STL_NS()string& strTypeName )
		: Collection( pManager, strTypeName )
	{
	}

	Set::Set( OclMeta::TypeManager* pManager, const GOCL_STL_NS()string& strTypeName, const OclMeta::ObjectVector& vecObjects )
		: Collection( pManager, strTypeName )
	{
		for ( int i = 0 ; i < vecObjects.size() ; i++ )
			AddObject( vecObjects[ i ] );
	}

	Set::Set( OclMeta::TypeManager* pManager )
		: Collection( pManager, "ocl::Set" )
	{
	}

	Set::Set( OclMeta::TypeManager* pManager, const OclMeta::ObjectVector& vecObjects )
		: Collection( pManager, "ocl::Set" )
	{
		for ( int i = 0 ; i < vecObjects.size() ; i++ )
			AddObject( vecObjects[ i ] );
	}

	Any* Set::Clone() const
	{
		return new Set( GetTypeManager(), m_vecObjects );
	}

	void Set::GetValue( OclMeta::ObjectVector& value ) const
	{
		value = m_vecObjects;
	}

	void Set::SetValue( const OclMeta::ObjectVector& value )
	{
		for ( int i = 0 ; i < value.size() ; i++ )
			AddObject( value[ i ] );
	}

	bool Set::Equals( const Any& object ) const
	{
		if ( GetTypeManager()->IsTypeA( object.GetTypeName(), "ocl::Set" ) >= 0 ) {
			OclMeta::ObjectVector vecObjects = ( ( Set* ) &object )->m_vecObjects;
			if ( m_vecObjects.size() != vecObjects.size() )
				return false;
			for ( int i = 0 ; i < m_vecObjects.size() ; i++ )
				if ( GOCL_STL_NS()find( vecObjects.begin(), vecObjects.end(), m_vecObjects[ i ] ) == vecObjects.end() )
					return false;
			return true;
		}
		else
			return false;
	}

	bool Set::operator==( const Set& object ) const
	{
		return Equals( object );
	}

	bool Set::operator!=( const Set& object ) const
	{
		return ! ( *this == object );
	}

	void Set::AddObject( const OclMeta::Object& object )
	{
		OclMeta::ObjectVector::iterator i = GOCL_STL_NS()find( m_vecObjects.begin(), m_vecObjects.end(), object );
			if ( i == m_vecObjects.end() )
				m_vecObjects.push_back( object );
	}

	OclImplementation::ObjectIterator* Set::GetIterator()
	{
		return new ObjectIterator( m_vecObjects.begin(), m_vecObjects.end() );
	}

	GOCL_STL_NS()string Set::Print() const
	{
		return PrintCollection( GetTypeName(), m_vecObjects );
	}

//##############################################################################################################################################
//
//	C L A S S : OclBasic::Bag <<< + OclBasic::Collection
//
//##############################################################################################################################################

	Bag::Bag( OclMeta::TypeManager* pManager, const GOCL_STL_NS()string& strTypeName )
		: Collection( pManager, strTypeName )
	{
	}

	Bag::Bag( OclMeta::TypeManager* pManager, const GOCL_STL_NS()string& strTypeName, const OclMeta::ObjectVector& vecObjects )
		: Collection( pManager, strTypeName )
	{
		m_vecObjects = vecObjects;
	}

	Bag::Bag( OclMeta::TypeManager* pManager )
		: Collection( pManager, "ocl::Bag" )
	{
	}

	Bag::Bag( OclMeta::TypeManager* pManager, const OclMeta::ObjectVector& vecObjects )
		: Collection( pManager, "ocl::Bag" )
	{
		m_vecObjects = vecObjects;
	}

	Any* Bag::Clone() const
	{
		return new Bag( GetTypeManager(), m_vecObjects );
	}

	void Bag::GetValue( OclMeta::ObjectVector& value ) const
	{
		value = m_vecObjects;
	}

	void Bag::SetValue( const OclMeta::ObjectVector& value )
	{
		m_vecObjects = value;
	}

	bool Bag::Equals( const Any& object ) const
	{
		if ( GetTypeManager()->IsTypeA( object.GetTypeName(), "ocl::Bag" ) >= 0 ) {
			OclMeta::ObjectVector vecObjects2 = ( ( Bag* ) &object )->m_vecObjects;
			if ( m_vecObjects.size() != vecObjects2.size() )
				return false;

			OclMeta::ObjectVector vecObjects1 = m_vecObjects;

			OclMeta::ObjectVector::iterator i = vecObjects1.begin();
			while ( i != vecObjects1.end() ) {
				OclMeta::Object o = *i;
				vecObjects1.erase( i );
				if ( GetObjectCountInVector( vecObjects1, o ) + 1 != GetObjectCountInVector( vecObjects2, o ) )
					return false;
				i = vecObjects1.begin();
			}
			return true;
		}
		else
			return false;
	}

	bool Bag::operator==( const Bag& object ) const
	{
		return Equals( object );
	}

	bool Bag::operator!=( const Bag& object ) const
	{
		return ! ( *this == object );
	}

	void Bag::AddObject( const OclMeta::Object& object )
	{
		m_vecObjects.push_back( object );
	}

	OclImplementation::ObjectIterator* Bag::GetIterator()
	{
		return new ObjectIterator( m_vecObjects.begin(), m_vecObjects.end() );
	}

	GOCL_STL_NS()string Bag::Print() const
	{
		return PrintCollection( GetTypeName(), m_vecObjects );
	}

//##############################################################################################################################################
//
//	C L A S S : OclBasic::Sequence <<< + OclBasic::Collection
//
//##############################################################################################################################################

	Sequence::Sequence( OclMeta::TypeManager* pManager, const GOCL_STL_NS()string& strTypeName )
		: Collection( pManager, strTypeName )
	{
	}

	Sequence::Sequence( OclMeta::TypeManager* pManager, const GOCL_STL_NS()string& strTypeName, const OclMeta::ObjectVector& vecObjects )
		: Collection( pManager, strTypeName )
	{
		m_vecObjects = vecObjects;
	}

	Sequence::Sequence( OclMeta::TypeManager* pManager )
		: Collection( pManager, "ocl::Sequence" )
	{
	}

	Sequence::Sequence( OclMeta::TypeManager* pManager, const OclMeta::ObjectVector& vecObjects )
		: Collection( pManager, "ocl::Sequence" )
	{
		m_vecObjects = vecObjects;
	}

	Any* Sequence::Clone() const
	{
		return new Sequence( GetTypeManager(), m_vecObjects );
	}

	void Sequence::GetValue( OclMeta::ObjectVector& value ) const
	{
		value = m_vecObjects;
	}

	void Sequence::SetValue( const OclMeta::ObjectVector& value )
	{
		m_vecObjects = value;
	}

	bool Sequence::Equals( const Any& object ) const
	{
		if ( GetTypeManager()->IsTypeA( object.GetTypeName(), "ocl::Sequence" ) >= 0 )
			return m_vecObjects == ( ( Sequence* ) &object )->m_vecObjects;
		else
			return false;
	}

	bool Sequence::operator==( const Sequence& object ) const
	{
		return Equals( object );
	}

	bool Sequence::operator!=( const Sequence& object ) const
	{
		return ! ( *this == object );
	}

	void Sequence::AddObject( const OclMeta::Object& object )
	{
		m_vecObjects.push_back( object );
	}

	OclImplementation::ObjectIterator* Sequence::GetIterator()
	{
		return new ObjectIterator( m_vecObjects.begin(), m_vecObjects.end() );
	}

	GOCL_STL_NS()string Sequence::Print() const
	{
		return PrintCollection( GetTypeName(), m_vecObjects );
	}

}; // namespace OclBasic
