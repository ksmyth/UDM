//###############################################################################################################################################
//
//	Object Constraint Language Generic Manager
//	OCLSignature.h
//
//###############################################################################################################################################

#ifndef OCLSignature_h
#define OCLSignature_h

#pragma warning ( disable : 4786 )

#include "OCLCommon.h"
#include "OCLFormalParameter.h"

namespace OclSignature
{
	class Feature;
	class ParametralFeature;
	class TypeableFeature;

	class Attribute;
	class Association;
	class Iterator;
	class Method;
	class Operator;
	class Function;

//##############################################################################################################################################
//
//	C L A S S : OclSignature::Feature
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class Feature
	{
		public :
			enum FeatureKind { FK_OPERATOR = 0, FK_METHOD = 1, FK_FUNCTION = 2, FK_ATTRIBUTE = 3, FK_ASSOCIATION = 4, FK_ITERATOR = 5 };

		private :
			GOCL_STL_NS()string 			m_strName;
			FeatureKind 	m_eKind;

		protected :
									Feature( const GOCL_STL_NS()string& strName, FeatureKind eKind );
		public :
			virtual 					~Feature();

					GOCL_STL_NS()string 			GetName() const;
					FeatureKind 	GetKind() const;
			virtual 	GOCL_STL_NS()string 			Print() const;
		protected :
					bool			IsIdentical( const Feature& object ) const;
	};

//##############################################################################################################################################
//
//	C L A S S : OclSignature::ParametralFeature
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class ParametralFeature
	{
		private :
			OclCommon::FormalParameterVector	m_vecParameters;

		protected :
													ParametralFeature( const OclCommon::FormalParameterVector& vecParameters );
		public :
			virtual 									~ParametralFeature();

					int 								GetParameterCount() const;
					int 								GetMinParameterCount() const;
					const OclCommon::FormalParameter& 		GetParameter( int i ) const;
		protected :
					OclCommon::FormalParameterVector& 	GetParameters();
			virtual 	GOCL_STL_NS()string 							Print() const;
					bool 							IsIdentical( const ParametralFeature& object ) const;
	};

//##############################################################################################################################################
//
//	C L A S S : OclMeta::TypeableFeature
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class TypeableFeature
	{
		private :
			GOCL_STL_NS()string	m_strTypeName;

		protected :
							TypeableFeature( const GOCL_STL_NS()string& strTypeName );
							TypeableFeature();
		public :
			virtual 			~TypeableFeature();

					GOCL_STL_NS()string 	GetTypeName() const;
			virtual 	GOCL_STL_NS()string 	Print() const;
	};

//##############################################################################################################################################
//
//	C L A S S : OclSignature::Attribute <<< + Feature , + TypeableFeature
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
							Attribute( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strTypeName );
		protected :
							Attribute( const GOCL_STL_NS()string& strName );
		public :
			virtual 			~Attribute();

			virtual 	GOCL_STL_NS()string 	Print() const;
					bool	IsIdentical( const Attribute& object ) const;
	};

//##############################################################################################################################################
//
//	C L A S S : OclSignature::Assocation <<< + Feature , + TypeableFeature
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
		private :
			GOCL_STL_NS()string	m_strAcceptable;

		public :
							Association( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strTypeName, const GOCL_STL_NS()string& strAcceptable );
		protected :
							Association( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strAcceptable );
		public :
			virtual 			~Association();

			virtual 	GOCL_STL_NS()string 	Print() const;
					GOCL_STL_NS()string 	GetAcceptableTypeName() const;
					bool	IsIdentical( const Association& object ) const;
	};

//##############################################################################################################################################
//
//	C L A S S : OclSignature::Iterator <<< + Feature , + TypeableFeature, + ParametralFeature
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class Iterator
		:	public Feature,
			public TypeableFeature,
			public ParametralFeature
	{
		public :
							Iterator( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strTypeName, const GOCL_STL_NS()string& strParameterType );
		protected :
							Iterator( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strParameterType );
		public :
			virtual 			~Iterator();

			virtual 	GOCL_STL_NS()string 	Print() const;
					bool	IsIdentical( const Iterator& object ) const;
	};

//##############################################################################################################################################
//
//	C L A S S : OclSignature::Method <<< + Feature , + TypeableFeature, + ParametralFeature
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
							Method( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strTypeName, const StringVector& vecTypes );
		protected :
							Method( const GOCL_STL_NS()string& strName, const OclCommon::FormalParameterVector& vecParameters );
		public :
			virtual 			~Method();

			virtual 	GOCL_STL_NS()string 	Print() const;
					bool	IsIdentical( const Method& object ) const;
	};

//##############################################################################################################################################
//
//	C L A S S : OclSignature::Operator <<< + Feature , + ParametralFeature
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class Operator
		: public Feature, public ParametralFeature
	{
		public :
							Operator( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strOperand1Type );
							Operator( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strOperand1Type, const GOCL_STL_NS()string& strOperand2Type );
		public :
			virtual 			~Operator();

			virtual 	GOCL_STL_NS()string 	Print() const;
					bool	IsIdentical( const Operator& object ) const;
	};

//##############################################################################################################################################
//
//	C L A S S : OclSignature::Function <<< + Feature , + ParametralFeature
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class Function
		: public Feature, public ParametralFeature
	{
		public :
							Function( const GOCL_STL_NS()string& strName, const StringVector& vecTypes );
		protected :
							Function( const GOCL_STL_NS()string& strName, const OclCommon::FormalParameterVector& vecParameters );
		public :
			virtual 			~Function();

			virtual 	GOCL_STL_NS()string 	Print() const;
					bool	IsIdentical( const Function& object ) const;
	};

}; // namespace OclSignature

#endif // OCLSignature_h

