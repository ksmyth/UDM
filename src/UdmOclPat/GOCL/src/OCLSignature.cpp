//###############################################################################################################################################
//
//	Object Constraint Language Generic Manager
//	OCLSignature.cpp
//
//###############################################################################################################################################

#include "OCLSignature.h"

namespace OclSignature
{

//##############################################################################################################################################
//
//	A B S T R A C T   C L A S S : OclSignature::Feature
//
//##############################################################################################################################################

	Feature::Feature( const GOCL_STL_NS()string& strName, FeatureKind eKind )
		: m_strName( strName ), m_eKind( eKind )
	{
	}

	Feature::~Feature()
	{
	}

	GOCL_STL_NS()string Feature::GetName() const
	{
		return m_strName;
	}

	Feature::FeatureKind Feature::GetKind() const
	{
		return m_eKind;
	}

	GOCL_STL_NS()string Feature::Print() const
	{
		return m_strName;
	}

	bool Feature::IsIdentical( const Feature& object ) const
	{
		return m_strName == object.m_strName;
	}

//##############################################################################################################################################
//
//	C L A S S : OclSignature::ParametralFeature
//
//##############################################################################################################################################

	ParametralFeature::ParametralFeature( const OclCommon::FormalParameterVector& vecParameters )
		: m_vecParameters( vecParameters )
	{
	}

	ParametralFeature::~ParametralFeature()
	{
	}

	int ParametralFeature::GetParameterCount() const
	{
		return m_vecParameters.size();
	}

	int ParametralFeature::GetMinParameterCount() const
	{
		for ( int i = m_vecParameters.size()-1 ; i >= 0 ; i-- )
			if ( m_vecParameters[ i ].IsRequired() )
				return i+1;
		return 0;
	}

	const OclCommon::FormalParameter& ParametralFeature::GetParameter( int i ) const
	{
		return m_vecParameters[ i ];
	}

	OclCommon::FormalParameterVector& ParametralFeature::GetParameters()
	{
		return m_vecParameters;
	}

	GOCL_STL_NS()string ParametralFeature::Print() const
	{
		GOCL_STL_NS()string strSignature = "( ";
		for ( int i = 0 ; i < GetParameterCount() ; i++ ) {
			OclCommon::FormalParameter parameter = GetParameter( i );
			if ( ! parameter.IsRequired() )
				strSignature += " { ";
			if ( i != 0 )
				strSignature += ", ";
			strSignature += parameter.GetTypeName();
			if ( i == GetParameterCount() - 1 && ! parameter.IsRequired() )
				strSignature += "} ";
		}
		return strSignature + " )";
	}

	bool ParametralFeature::IsIdentical( const ParametralFeature& object ) const
	{
		return m_vecParameters == object.m_vecParameters;
	}

//##############################################################################################################################################
//
//	C L A S S : OclSignature::TypeableFeature
//
//##############################################################################################################################################

	TypeableFeature::TypeableFeature( const GOCL_STL_NS()string& strTypeName )
		: m_strTypeName( strTypeName )
	{
	}

	TypeableFeature::TypeableFeature()
		: m_strTypeName( "" )
	{
	}

	TypeableFeature::~TypeableFeature()
	{
	}

	GOCL_STL_NS()string TypeableFeature::GetTypeName() const
	{
		return m_strTypeName;
	}

	GOCL_STL_NS()string TypeableFeature::Print() const
	{
		if ( m_strTypeName.empty() )
			return "";
		return m_strTypeName + "::";
	}

//##############################################################################################################################################
//
//	C L A S S : OclSignature::Attribute <<< + Feature , + TypeableFeature
//
//##############################################################################################################################################

	Attribute::Attribute( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strTypeName )
		: Feature( strName, Feature::FK_ATTRIBUTE ), TypeableFeature( strTypeName )
	{
	}

	Attribute::Attribute( const GOCL_STL_NS()string& strName )
		: Feature( strName, Feature::FK_ATTRIBUTE ), TypeableFeature()
	{
	}

	Attribute::~Attribute()
	{
	}

	GOCL_STL_NS()string Attribute::Print() const
	{
		return TypeableFeature::Print() + Feature::Print();
	}

	bool Attribute::IsIdentical( const Attribute& object ) const
	{
		return Feature::IsIdentical( object );
	}

//##############################################################################################################################################
//
//	C L A S S : OclSignature::Assocation <<< + Feature , + TypeableFeature
//
//##############################################################################################################################################

	Association::Association( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strTypeName, const GOCL_STL_NS()string& strAcceptable )
		: Feature( strName, Feature::FK_ASSOCIATION ), TypeableFeature( strTypeName ), m_strAcceptable( strAcceptable )
	{
	}

	Association::Association( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strAcceptable )
		: Feature( strName, Feature::FK_ASSOCIATION ), TypeableFeature(), m_strAcceptable( strAcceptable )
	{
	}

	Association::~Association()
	{
	}

	GOCL_STL_NS()string Association::Print() const
	{
		if ( m_strAcceptable.empty() )
			return TypeableFeature::Print() + Feature::Print();
		return TypeableFeature::Print() + m_strAcceptable + "[ " + Feature::Print() + " ]";
	}

	GOCL_STL_NS()string Association::GetAcceptableTypeName() const
	{
		return m_strAcceptable;
	}

	bool Association::IsIdentical( const Association& object ) const
	{
		return Feature::IsIdentical( object ) && m_strAcceptable == object.m_strAcceptable;
	}

//##############################################################################################################################################
//
//	C L A S S : OclSignature::Iterator <<< + Feature , + TypeableFeature, + ParametralFeature
//
//##############################################################################################################################################

	Iterator::Iterator( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strTypeName, const GOCL_STL_NS()string& strParameterType )
		: Feature( strName, Feature::FK_ITERATOR ), TypeableFeature( strTypeName ), ParametralFeature( OclCommon::FormalParameterVector( 1, OclCommon::FormalParameter( strParameterType, true ) ) )
	{
	}

	Iterator::Iterator( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strParameterType )
		: Feature( strName, Feature::FK_ITERATOR ), TypeableFeature(), ParametralFeature( OclCommon::FormalParameterVector( 1, OclCommon::FormalParameter( strParameterType, true ) ) )
	{
	}

	Iterator::~Iterator()
	{
	}

	GOCL_STL_NS()string Iterator::Print() const
	{
		return TypeableFeature::Print() + Feature::Print() +  "( ... | " + GetParameter( 0 ).GetTypeName() + " )";
	}

	bool Iterator::IsIdentical( const Iterator& object ) const
	{
		return Feature::IsIdentical( object ) && ParametralFeature::IsIdentical( object );
	}

//##############################################################################################################################################
//
//	C L A S S : OclSignature::Method <<< + Feature , + TypeableFeature, + ParametralFeature
//
//##############################################################################################################################################

	Method::Method( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strTypeName, const StringVector& vecTypes )
		: Feature( strName, Feature::FK_METHOD ), TypeableFeature( strTypeName ), ParametralFeature( OclCommon::FormalParameterVector() )
	{
		OclCommon::FormalParameterVector& vecParameters = GetParameters();
		for ( int i = 0 ; i < vecTypes.size() ; i++ )
			vecParameters.push_back( OclCommon::FormalParameter( vecTypes[ i ], true ) );
	}

	Method::Method( const GOCL_STL_NS()string& strName, const OclCommon::FormalParameterVector& vecParameters )
		: Feature( strName, Feature::FK_METHOD ), TypeableFeature(), ParametralFeature( vecParameters )
	{
	}

	Method::~Method()
	{
	}

	GOCL_STL_NS()string Method::Print() const
	{
		return  TypeableFeature::Print() + Feature::Print() + ParametralFeature::Print();
	}

	bool Method::IsIdentical( const Method& object ) const
	{
		return Feature::IsIdentical( object ) && ParametralFeature::IsIdentical( object );
	}

//##############################################################################################################################################
//
//	C L A S S : OclSignature::Operator <<< + Feature , + ParametralFeature
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	Operator::Operator( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strOperand1Type )
		: Feature( strName, Feature::FK_OPERATOR ), ParametralFeature( OclCommon::FormalParameterVector( 1, OclCommon::FormalParameter( strOperand1Type, true ) ) )
	{
	}

	Operator::Operator( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strOperand1Type, const GOCL_STL_NS()string& strOperand2Type )
		: Feature( strName, Feature::FK_OPERATOR ), ParametralFeature( OclCommon::FormalParameterVector() )
	{
		OclCommon::FormalParameterVector& vecParameters = GetParameters();
		vecParameters.push_back( OclCommon::FormalParameter( strOperand1Type, true ) );
		vecParameters.push_back( OclCommon::FormalParameter( strOperand2Type, true ) );
	}

	Operator::~Operator()
	{
	}

	GOCL_STL_NS()string Operator::Print() const
	{
		return "operator[ " + Feature::Print() + " ]" + ParametralFeature::Print();
	}

	bool Operator::IsIdentical( const Operator& object ) const
	{
		return Feature::IsIdentical( object ) && ParametralFeature::IsIdentical( object );
	}

//##############################################################################################################################################
//
//	C L A S S : OclSignature::Function <<< + Feature , + ParametralFeature
//
//##############################################################################################################################################

	Function::Function( const GOCL_STL_NS()string& strName, const StringVector& vecTypes )
		: Feature( strName, Feature::FK_METHOD ), ParametralFeature( OclCommon::FormalParameterVector() )
	{
		OclCommon::FormalParameterVector& vecParameters = GetParameters();
		for ( int i = 0 ; i < vecTypes.size() ; i++ )
			vecParameters.push_back( OclCommon::FormalParameter( vecTypes[ i ], true ) );
	}

	Function::Function( const GOCL_STL_NS()string& strName, const OclCommon::FormalParameterVector& vecParameters )
		: Feature( strName, Feature::FK_METHOD ), ParametralFeature( vecParameters )
	{
	}

	Function::~Function()
	{
	}

	GOCL_STL_NS()string Function::Print() const
	{
		return Feature::Print() + ParametralFeature::Print();
	}

	bool Function::IsIdentical( const Function& object ) const
	{
		return Feature::IsIdentical( object ) && ParametralFeature::IsIdentical( object );
	}


}; // namespace OclSignature