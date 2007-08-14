//###############################################################################################################################################
//
//	Object Constraint Language Implementation For UDM
//	UDMOCLObject.cpp
//
//###############################################################################################################################################

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

#include "UdmOclObject.h"
#include "UdmBase.h"
#include "Uml.h"

#ifndef _WIN32
char *_ltoa( long value, char *string, int radix )
{
	sprintf(string, "%ld", value);
};
#endif


namespace UmlOcl
{

//##############################################################################################################################################
//
//	C L A S S : OclGmeCM::Object <<< + Any
//
//##############################################################################################################################################

	Object::Object( OclMeta::TypeManager* pManager, Udm::Object value )
		: Any( pManager, "udm::Object" ), m_Value( value )
	{
		// WARNING : m_Value not null
		if ( (bool) m_Value )
			m_strTypeName = "meta::" + (GOCL_STL_NS()string) m_Value.type().name();
	}

	Any* Object::Clone() const
	{
		Object* pObject = new Object( GetTypeManager(), m_Value );
		pObject->m_strTypeName = m_strTypeName;
		return pObject;
	}

	void Object::GetValue( Udm::Object& value ) const
	{
		value =  m_Value;
	}

	void Object::SetValue( const Udm::Object& value )
	{
		m_Value = value;
		// WARNING : m_Value not null
		if ( (bool) m_Value )
			m_strTypeName = "meta::" + (GOCL_STL_NS()string) m_Value.type().name();
	}

	bool Object::Equals( const Any& object ) const
	{
		return m_Value == ( ( Object* ) &object )->m_Value;
	}

	bool Object::operator==( const Object& object ) const
	{
		return Equals( object );
	}
	bool Object::operator!=( const Object& object ) const
	{
		return ! ( *this == object );
	}

	GOCL_STL_NS()string Object::Print() const
	{
		/* WARNING: m_Value is NULL */
		if ( ! m_Value )
			return "null";
		char chBuffer[ 300 ];
		_ltoa( m_Value.uniqueId(), chBuffer, 10 );
		return "meta::" + (GOCL_STL_NS()string) m_Value.type().name() + " { id : " + GOCL_STL_NS()string( chBuffer ) + " }";
	}

//##############################################################################################################################################
//
//	C L A S S : UmlOcl::DataNetwork <<< + Any
//
//##############################################################################################################################################

	DataNetwork::DataNetwork( OclMeta::TypeManager* pManager, Udm::DataNetwork* value )
		: Any( pManager, "udm::DataNetwork" ), m_Value( value )
	{
	}

	Any* DataNetwork::Clone() const
	{
		return new DataNetwork( GetTypeManager(), m_Value );
	}

	void DataNetwork::GetValue( Udm::DataNetwork*& value ) const
	{
		value = m_Value;
	}

	void DataNetwork::SetValue( Udm::DataNetwork* value )
	{
		m_Value = value;
	}


	bool DataNetwork::Equals( const Any& object ) const
	{
		return m_Value == ( ( DataNetwork* ) &object )->m_Value;
	}

	bool DataNetwork::operator==( const DataNetwork& object ) const
	{
		return Equals( object );
	}

	bool DataNetwork::operator!=( const DataNetwork& object ) const
	{
		return ! ( *this == object );
	}

	GOCL_STL_NS()string DataNetwork::Print() const
	{
		return "udm::DataNetwork";
	}

}; // namespace UmlOcl