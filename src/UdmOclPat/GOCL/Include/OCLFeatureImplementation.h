//###############################################################################################################################################
//
//	Object Constraint Language Generic Manager
//	OCLFeatureImplementation.h
//
//###############################################################################################################################################

#ifndef OCLFeatureImplementation_h
#define OCLFeatureImplementation_h

#pragma warning ( disable : 4786 )

#include "OCLCommon.h"
#include "OCLObject.h"
#include "OCLException.h"

#define ATTRIBUTE( featureName )		class featureName : public OclImplementation::Attribute
#define ASSOCIATION( featureName )	class featureName : public OclImplementation::Association
#define ITERATOR( featureName )		class featureName : public OclImplementation::Iterator
#define METHOD( featureName )			class featureName : public OclImplementation::Method
#define OPERATOR( featureName )		class featureName : public OclImplementation::Operator
#define FUNCTION( featureName )		class featureName : public OclImplementation::Function

#define TYPE_EXPRESSION_RETURN 					"%ocl::Type_Expression_Return"
#define TYPE_COMPOUNDARGUMENT_SELF_BASE 	"%ocl::Type_CompoundArgument_Self_Base"
#define TYPE_ARGUMENT_SELF_BASE 				"%ocl::Type_Argument_Self_Base"
#define TYPE_AGGREGATED_OBJECT 					"%ocl::Type_Aggregated_Object"

namespace OclMeta
{
	class TypeManager;
}

namespace OclImplementation
{

//##############################################################################################################################################
//
//	A B S T R A C T   C L A S S : OclImplementation::Feature
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class Feature
	{
		private :
			OclMeta::Object m_Result;
			OclMeta::TypeManager* m_pTypeManager;

		protected :
			Feature()
			{
			}

		public :
			virtual 	~Feature()
			{
			}

			virtual 	void Initialize()
			{
			}

			virtual 	void Finalize()
			{
				m_Result = OclMeta::Object::UNDEFINED;
			}

			virtual 	void operator()() = 0;

			void SetResult( const OclMeta::Object& object )
			{
				m_Result = object;
			}

			virtual OclMeta::Object GetResult() const
			{
				return m_Result;
			}

			OclMeta::TypeManager* GetTypeManager() const
			{
				return m_pTypeManager;
			}

			void ThrowException( const GOCL_STL_NS()string& strMessage )
			{
				THROWOCL0( ET_RUNTIME, strMessage );
			}

		friend OclMeta::TypeManager;
	};

//##############################################################################################################################################
//
//	C L A S S : OclImplementation::TypeableFeature
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class TypeableFeature
	{
		private :
			OclMeta::Object m_This;

		protected :
							TypeableFeature() {}
			virtual	void	Finalize() { m_This = OclMeta::Object::UNDEFINED; }
		public :
			virtual 			~TypeableFeature() {}

					void 	SetThis( const OclMeta::Object& object )		{ m_This = object; 	}
					OclMeta::Object 	GetThis() const						{ return m_This;		}
	};

//##############################################################################################################################################
//
//	C L A S S : OclImplementation::ParametralFeature
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class ParametralFeature
	{
		private :
			OclMeta::ObjectVector	m_vecArguments;

		protected :
							ParametralFeature() {}
			virtual	void	Finalize() { m_vecArguments.clear(); }
		public :
			virtual 			~ParametralFeature() {}

					void 	SetArguments( const OclMeta::ObjectVector& vecArguments ) 	{ m_vecArguments = vecArguments; 	}
					OclMeta::Object 	GetArgument( int i ) const								{ return m_vecArguments[ i ]; 			}
					int 		GetArgumentCount() const 								{ return m_vecArguments.size(); 		}
	};

//##############################################################################################################################################
//
//	C L A S S : OclImplementation::Attribute <<< + OclImplementation::Feature , + OclImplementation::TypeableFeature
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class Attribute
		: 	public Feature,
			public TypeableFeature
	{
		public :
			virtual void Finalize() { Feature::Finalize(); TypeableFeature::Finalize(); }
	};

//##############################################################################################################################################
//
//	C L A S S : OclImplementation::Association <<< + OclImplementation::Feature , + OclImplementation::TypeableFeature
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class Association
		: 	public Feature,
			public TypeableFeature
	{
		public :
			virtual void Finalize() { Feature::Finalize(); TypeableFeature::Finalize(); }
	};

//##############################################################################################################################################
//
//	C L A S S : OclImplementation::Iterator <<< + OclImplementation::Feature , + OclImplementation::TypeableFeature
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class Iterator
		: 	public Feature,
			public TypeableFeature,
			public ParametralFeature
	{
		private :
			OclMeta::Object 	m_Next;
			bool 				m_bStopped;
			bool				m_bDoSnapShot;

		public :
			virtual void Initialize()										{ m_bDoSnapShot = false; m_bStopped = false; }
					void SetSubResult( const OclMeta::Object& object ) 	{ m_Next = object; 			}
					OclMeta::Object GetSubResult() const 				{ return m_Next; 				}
					bool DoSnapshot() const								{ return m_bDoSnapShot; 	}
					void SetDoSnapshot( bool bDo ) 						{ m_bDoSnapShot = bDo; 	}
					bool DoStop() const									{ return m_bStopped; 		}
					void SetDoStop( bool bDo ) 							{ m_bStopped = bDo;	 		}
			virtual 	void Finalize() 											{ Feature::Finalize(); TypeableFeature::Finalize(); ParametralFeature::Finalize(); m_Next = OclMeta::Object::UNDEFINED; }
	};

//##############################################################################################################################################
//
//	C L A S S : OclImplementation::Method <<< + OclImplementation::Feature , + OclImplementation::TypeableFeature, + OclImplementation::ParametralFeature
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class Method
		: 	public Feature,
			public TypeableFeature,
			public ParametralFeature
	{
		public :
			virtual 	void Finalize() { Feature::Finalize(); TypeableFeature::Finalize(); ParametralFeature::Finalize(); }
	};

//##############################################################################################################################################
//
//	C L A S S : OclImplementation::Operator <<< + OclImplementation::Feature , + OclImplementation::ParametralFeature
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class Operator
		: 	public Feature,
			public ParametralFeature
	{
		public :
			virtual 	void Finalize() { Feature::Finalize(); ParametralFeature::Finalize(); }
	};

//##############################################################################################################################################
//
//	C L A S S : OclImplementation::Function <<< + OclImplementation::Feature , + OclImplementation::ParametralFeature
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class Function
		: 	public Feature,
			public ParametralFeature
	{
		public :
			virtual 	void Finalize() { Feature::Finalize(); ParametralFeature::Finalize(); }
	};

}; // namespace OclImplementation

#endif // OCLFeatureImplementation_h
