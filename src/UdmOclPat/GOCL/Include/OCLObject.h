//###############################################################################################################################################
//
//	Object Constraint Language Generic Manager
//	OCLObject.h
//
//###############################################################################################################################################

#ifndef OCLObject_h
#define OCLObject_h

#pragma warning ( disable : 4786 )

#include "OCLCommon.h"
#include "OCLRefCount.h"

namespace OclMeta {
	class Object;
};

namespace  OclImplementation {
	class Object;
	class CompoundObject;
	class ObjectIterator;
}

namespace OclMeta
{
	class TypeManager;

	typedef GOCL_STL_NS()vector< Object > ObjectVector;

//##############################################################################################################################################
//
//	C L A S S : OclMeta::Object <<< + OclCommon::RCSmart< OclImplementation::Object >
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class Object
		: protected OclCommon::RCSmart< OclImplementation::Object >
	{
		public :
			static const Object UNDEFINED;

		private :
			GOCL_STL_NS()string m_strStaticTypeName;

		public :
											Object();
											Object( OclImplementation::Object* pImplementation );
											Object( const Object& object );
			Object& 						operator=( const Object& object );
			Object 							Clone() const;

			bool	 						Equals( const Object& object ) const;
			bool 							operator==( const Object& object ) const;
			bool 							operator!=( const Object& object ) const;

			GOCL_STL_NS()string 							GetTypeName() const;
			GOCL_STL_NS()string 							GetStaticTypeName() const;
			void 							SetStaticTypeName( const GOCL_STL_NS()string& strStaticTypeName );
			bool 							IsCompound() const;
			bool 							IsUndefined() const;
			OclImplementation::Object* 	GetImplementation() const;
			GOCL_STL_NS()string			Print() const;
	};

}; // namespace OclMeta

namespace OclImplementation
{

//##############################################################################################################################################
//
//	A B S T R A C T   C L A S S : OclImplementation::Object <<< + OclCommon::ReferenceCountable< OclImplementation::Object >
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class Object
		: public OclCommon::ReferenceCountable< Object >
	{
		protected :
			GOCL_STL_NS()string m_strTypeName;
			OclMeta::TypeManager*	m_pTypeManager;

		protected :
			Object( OclMeta::TypeManager* pManager, const GOCL_STL_NS()string& strTypeName )
				: OclCommon::ReferenceCountable<Object>(), m_pTypeManager( pManager ), m_strTypeName( strTypeName )
			{
			}

		public :
			virtual ~Object()
			{
			}

			GOCL_STL_NS()string GetTypeName() const
			{
				return m_strTypeName;
			}

			OclMeta::TypeManager* GetTypeManager() const
			{
				return m_pTypeManager;
			}

			virtual bool IsCompound() const
			{
				return false;
			}

			virtual Object* Clone() const
			{
				return NULL;
			}

			virtual bool Equals( const Object& object ) const
			{
				return this == &object;
			}

			virtual GOCL_STL_NS()string Print() const = 0;

			virtual bool IsUndefined() const
			{
				return false;
			}
	};

//##############################################################################################################################################
//
//	A B S T R A C T   C L A S S : OclImplementation::CompoundObject <<< + OclImplementation::Object
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class CompoundObject
		: public Object
	{
		protected :
			CompoundObject( OclMeta::TypeManager* pManager, const GOCL_STL_NS()string& strTypeName )
				: Object( pManager, strTypeName )
			{
			}

		public :
			virtual ~CompoundObject()
			{
			}

			bool IsCompound() const
			{
				return true;
			}

			virtual void AddObject( const OclMeta::Object& object ) = 0;

			virtual ObjectIterator* GetIterator() = 0;
	};

//##############################################################################################################################################
//
//	P U R E   A B S T R A C T   C L A S S : OclImplementation::ObjectIterator
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class ObjectIterator
	{
		public :
			ObjectIterator()
			{
			}

			virtual ~ObjectIterator()
			{
			}

			virtual bool HasNext() = 0;

			virtual OclMeta::Object GetNext() = 0;
	};

}; // namespace OclImplementation

#endif // OCLObject_h