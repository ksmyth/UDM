//###############################################################################################################################################
//
//	Object Constraint Language Generic Manager
//	OCLObject.cpp
//
//###############################################################################################################################################

#include "OCLObject.h"

#define UNDEFINED_TYPENAME ""

namespace OclMeta
{
	typedef OclCommon::RCSmart<OclImplementation::Object> RCObject;

//##############################################################################################################################################
//
//	C L A S S : OclMetat::Object <<< # OclCommon::RCSmart< OclImplementation::Object >
//
//##############################################################################################################################################

	const Object Object::UNDEFINED = Object();

	Object::Object()
		: RCObject(), m_strStaticTypeName( UNDEFINED_TYPENAME )
	{
	}

	Object::Object( OclImplementation::Object* pImplementation )
		: RCObject( pImplementation ), m_strStaticTypeName( pImplementation->GetTypeName() )
	{
	}

	Object::Object( const Object& object )
		: RCObject( object ), m_strStaticTypeName( object.m_strStaticTypeName )
	{
	}

	Object& Object::operator=( const Object& object )
	{
		if ( this != &object ) {
			m_strStaticTypeName = object.m_strStaticTypeName;
		}
		RCObject::operator=( object );
		return *this;
	}

	bool Object::Equals( const Object& object ) const
	{
		if ( IsUndefined() )
			if ( object.IsUndefined() )
				return true;
			else
				return false;
		else
			if ( object.IsUndefined() )
				return false;
			else
				return Ptr()->Equals( *object.Ptr() );
	}

	bool Object::operator==( const Object& object ) const
	{
		return Equals( object );
	}

	bool Object::operator!=( const Object& object ) const
	{
		return ! Equals( object );
	}

	GOCL_STL_NS()string Object::GetTypeName() const
	{
		return ( IsUndefined() ) ? UNDEFINED_TYPENAME : Ptr()->GetTypeName();
	}

	GOCL_STL_NS()string Object::GetStaticTypeName() const
	{
		return m_strStaticTypeName;
	}

	void Object::SetStaticTypeName( const GOCL_STL_NS()string& strStaticTypeName )
	{
		m_strStaticTypeName = strStaticTypeName;
	}

	bool Object::IsCompound() const
	{
		if ( IsUndefined() )
			return false;
		return Ptr()->IsCompound();
	}

	bool Object::IsUndefined() const
	{
		//if(IsNull()) { printf("Object is null|"); }
		//else if(Ptr()->IsUndefined()) { printf("Ptr Undefined|"); }
		return IsNull() || Ptr()->IsUndefined();
	}

	OclImplementation::Object* Object::GetImplementation() const
	{
		return ( IsUndefined() ) ? NULL : Ptr();
	}

	Object Object::Clone() const
	{
		return ( IsUndefined() ) ? UNDEFINED : Object( Ptr()->Clone() );
	}

	GOCL_STL_NS()string Object::Print() const
	{
		return ( IsUndefined() ) ? "undefined" : Ptr()->Print();
	}

}; // namespace OclMeta

