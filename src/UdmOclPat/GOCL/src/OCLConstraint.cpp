//###############################################################################################################################################
//
//	Object Constraint Language Generic Manager
//	OCLConstraint.h
//
//###############################################################################################################################################

#include "OCLConstraint.h"

#include "OCLObjectExBasic.h"
#include "OCLTokens.h"
#include "OCLParser.h"

	bool OCLParser::m_bProcessingPat;
namespace Ocl
{
	Constraint::Stereotype StringToStereotype( const GOCL_STL_NS()string& str )
	{
		if ( str == "inv" )
			return Constraint::CS_INVARIANT;
		if ( str == "pre" )
			return Constraint::CS_PRECONDITION;
		if ( str == "post" )
			return Constraint::CS_POSTCONDITION;
		if ( str == "defattribute" )
			return Constraint::CS_ATTRIBUTEDEF;
		return Constraint::CS_METHODDEF;
	}

//##############################################################################################################################################
//
//	C L A S S : Ocl::Constraint
//
//##############################################################################################################################################

	Constraint::Constraint()
		:  m_pManager( NULL ), m_pCtxConstraint( NULL ), m_pConstraint( NULL ), m_strName( "" ), m_strText( "" ), m_eState( CS_UNREGISTERED ), m_bContextSucceeded( false )
	{
	}

	Constraint::Constraint( OclTree::TreeManager* pManager )
		: m_pManager( pManager ), m_pCtxConstraint( NULL ), m_pConstraint( NULL ), m_strName( "" ), m_strText( "" ), m_eState( CS_UNREGISTERED ), m_bContextSucceeded( false )
	{
		if ( pManager )
			m_eState = CS_REGISTERED;
	}

	Constraint::Constraint( OclTree::TreeManager* pManager, const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strText, bool bDynamic )
		: m_pManager( pManager ), m_pCtxConstraint( NULL ), m_pConstraint( NULL ), m_strText( strText ), m_strName( strName ), m_eState( CS_UNREGISTERED ), m_bDynamic( bDynamic ), m_bContextSucceeded( false )
	{
		if ( pManager ) {
			m_eState = CS_REGISTERED;
			if ( ! m_strName.empty() && ! m_strText.empty() )
				m_eState = CS_DEFINED;
		}
	}

	Constraint::~Constraint()
	{
		if ( m_pCtxConstraint )
			delete m_pCtxConstraint;
		if ( m_pConstraint )
			delete m_pConstraint;
	}

	Constraint::State Constraint::Register( OclTree::TreeManager* pManager )
	{
		if ( pManager && m_eState == CS_UNREGISTERED ) {
			m_eState = ( ! m_strName.empty() && ! m_strText.empty() ) ? CS_DEFINED : CS_REGISTERED;
			m_pManager = pManager;
			//if( ! m_strName.empty() && ! m_strText.empty() ) printf("Registered....");
		}
		return m_eState;
	}

	Constraint::State Constraint::Define( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strText, bool bDynamic )
	{
		if ( ! strName.empty() || ! strText.empty() && m_eState <= CS_DEFINED ) {
			m_bDynamic = bDynamic;
			if ( ! strName.empty() )
				m_strName = strName;
			if ( ! strText.empty() )
				m_strText = strText;
			if ( m_eState == CS_REGISTERED && ! m_strName.empty() && ! m_strText.empty() )
			{
				//printf("constraint defined.");
				m_eState = CS_DEFINED;
			}
		}
		return m_eState;
	}

	GOCL_STL_NS()string Constraint::GetDefinedName() const
	{
		return m_strName;
	}

	Constraint::State Constraint::GetState() const
	{
		return m_eState;
	}

	bool Constraint::IsValid() const
	{
		return ! ( m_eState == CS_CTX_PARSE_FAILED || m_eState == CS_CTX_CHECK_FAILED || m_eState == CS_PARSE_FAILED || m_eState == CS_CHECK_FAILED || m_eState == CS_CHECK_DEPENDENCY_FAILED );
	}

	bool Constraint::IsDefined() const
	{
		return m_eState >= CS_DEFINED;
	}

	GOCL_STL_NS()string Constraint::GetText() const
	{
		return m_strText;
	}

	bool Constraint::IsDynamic() const
	{
		return m_bDynamic;
	}

	Constraint::State Constraint::ParseContext()
	{
		if ( m_eState < CS_DEFINED )
			throw m_eState;
		if ( m_pCtxConstraint )
			return CS_CTX_PARSE_SUCCEEDED;
		m_pCtxConstraint = OCLParser::ParseConstraint( m_pManager, m_strText, true, m_poolCtxExceptions );
		if ( m_poolCtxExceptions.IsEmpty() && m_pCtxConstraint ) {
			if ( ! m_pConstraint )
				m_eState = CS_CTX_PARSE_SUCCEEDED;
			return CS_CTX_PARSE_SUCCEEDED;
		}
		if ( m_pCtxConstraint ) {
			delete m_pCtxConstraint;
			m_pCtxConstraint = NULL;
		}
		return m_eState = CS_CTX_PARSE_FAILED;
	}

	GOCL_STL_NS()string Constraint::GetName() const
	{
		if ( m_pCtxConstraint )
			return m_pCtxConstraint->m_strName;
		if ( m_pConstraint )
			return m_pConstraint->m_strName;
		throw m_eState;
	}

	Constraint::Stereotype Constraint::GetStereotype() const
	{
		if ( m_pCtxConstraint )
			return StringToStereotype( m_pCtxConstraint->m_pContext->m_strStereotype );
		if ( m_pConstraint )
			return StringToStereotype( m_pConstraint->m_pContext->m_strStereotype );
		throw m_eState;
	}

	Constraint::State Constraint::CheckContext()
	{
		if ( m_eState == CS_CTX_CHECK_FAILED )
			return m_eState;
		if ( m_bContextSucceeded || m_eState > CS_CHECK_SUCCEEDED || m_eState == CS_CTX_CHECK_SUCCEEDED )
			return CS_CTX_CHECK_SUCCEEDED;
		if ( ! m_pCtxConstraint )
			throw CS_CTX_CHECK_FAILED;
		OclTree::TypeContext context;
		m_bContextSucceeded = m_pCtxConstraint->Check( context );
		m_poolCtxExceptions = context.m_poolExceptions;
		Constraint::State eState = ( m_bContextSucceeded ) ? CS_CTX_CHECK_SUCCEEDED : CS_CTX_CHECK_FAILED;
		if ( m_eState == CS_CTX_PARSE_SUCCEEDED )
			m_eState = eState;
		return eState;
	}

	GOCL_STL_NS()string Constraint::GetContextType() const
	{
		if ( m_bContextSucceeded )
			return m_pCtxConstraint->m_pContext->m_strType;
		if ( m_eState >= CS_CHECK_SUCCEEDED )
			return m_pConstraint->m_pContext->m_strType;
		throw m_eState;
	}

	GOCL_STL_NS()string Constraint::GetFullName() const
	{
		return GetContextType() + "::" + GetName();
	}

	GOCL_STL_NS()string Constraint::GetReturnType() const
	{
		if ( m_bContextSucceeded || m_eState >= CS_CHECK_SUCCEEDED ) {
			if ( GetStereotype() == CS_INVARIANT )
				throw CS_INVARIANT;
			if ( m_bContextSucceeded )
				return m_pCtxConstraint->m_pContext->m_strReturnType;
			return m_pConstraint->m_pContext->m_strReturnType;
		}
		throw m_eState;
	}

	OclCommon::FormalParameterVector Constraint::GetFormalParameters() const
	{
		if ( m_bContextSucceeded || m_eState >= CS_CHECK_SUCCEEDED ) {
			if ( GetStereotype() == CS_INVARIANT )
				throw CS_INVARIANT;
			if ( m_bContextSucceeded )
				return m_pCtxConstraint->m_pContext->m_vecParameters;
			return m_pConstraint->m_pContext->m_vecParameters;
		}
		throw m_eState;
	}

	Constraint::State Constraint::Parse()
	{
		if ( m_eState < CS_DEFINED )
			throw m_eState;
		if ( m_eState == CS_PARSE_FAILED )
			return m_eState;
		if ( m_eState >= CS_PARSE_SUCCEEDED )
			return CS_PARSE_SUCCEEDED;
		m_pConstraint = OCLParser::ParseConstraint( m_pManager, m_strText, false, m_poolExceptions );
		if ( m_poolExceptions.IsEmpty() && m_pConstraint )
			return m_eState = CS_PARSE_SUCCEEDED;
		if ( m_pConstraint ) {
			delete m_pConstraint;
			m_pConstraint = NULL;
		}
		return m_eState = CS_PARSE_FAILED;
	}

	Constraint::State Constraint::Check( OclTree::TypeContextStack& ctxTypes )
	{
		if ( m_eState < CS_PARSE_SUCCEEDED )
			throw m_eState;
		if ( m_eState == CS_CHECK_FAILED )
			return m_eState;
		if ( m_eState >= CS_CHECK_SUCCEEDED )
			return CS_CHECK_SUCCEEDED;
		OclTree::TypeContext context;
		context.m_ctxTypes = ctxTypes;
		bool bResult = m_pConstraint->Check( context );
		m_poolExceptions = context.m_poolExceptions;
		return m_eState = ( bResult ) ? CS_CHECK_SUCCEEDED : CS_CHECK_FAILED;
	}

	OclMeta::DependencySet Constraint::GetDependencySet() const
	{
		if ( m_eState < CS_CHECK_SUCCEEDED )
			throw m_eState;
		return m_pConstraint->m_pContext->m_setDependencies;
	}

	Constraint::State Constraint::SetDependencyResult( const OclMeta::DependencySet& setDependencies )
	{
		if ( m_eState != CS_CHECK_SUCCEEDED )
			throw m_eState;
		bool bWasError = false;
		for ( OclMeta::DependencySet::const_iterator i = setDependencies.begin() ; i != setDependencies.end() ; i++ ) {
			if ( (*i).m_bFailed ) {
				bWasError = true;
				m_poolExceptions.Add( OclCommon::Exception( OclCommon::Exception::ET_SEMANTIC, EX_CONSTRAINT_DEF_FAILED, (*i).m_strSignature, (*i).m_position.iLine, (*i).m_position.iColumn ) );
			}
		}
		return m_eState = ( bWasError ) ? CS_CHECK_DEPENDENCY_FAILED : CS_CHECK_DEPENDENCY_SUCCEEDED;
	}

	GOCL_STL_NS()string Constraint::Print() const
	{
		if ( m_eState >= CS_CHECK_SUCCEEDED )
			return m_pConstraint->Print( "" );
		throw m_eState;
	}

	GOCL_STL_NS()string Constraint::PrintTree() const
	{
		if ( m_eState >= CS_PARSE_SUCCEEDED )
			return m_pConstraint->Print( "" );
		throw m_eState;
	}

	OclMeta::Object Constraint::Evaluate( OclTree::ObjectContextStack& ctxObjects, bool bEnableLogicalShortCircuit, bool bEnableIteratorShortCircuit, bool bEnableTracking )
	{
		if ( m_eState < CS_CHECK_DEPENDENCY_SUCCEEDED )
			throw m_eState;
		OclTree::ObjectContext context;
		context.oCtx = ctxObjects;
		context.bDoSnapshot = true;
		context.iViolationCount = 0;
		context.m_bHasException = false;
		context.m_bShortCircuitLogical = bEnableLogicalShortCircuit;
		context.m_bShortCircuitIterator = bEnableIteratorShortCircuit;
		context.m_bEnableTracking = bEnableTracking;

		OclMeta::Object spResult = m_pConstraint->Evaluate( context );
		m_vecViolations = context.vecViolations;
		if ( spResult.IsUndefined() ) {
			//printf("CS_EVAL_FAILED|");
			m_eState = CS_EVAL_FAILED;
		}
		else
			m_eState = CS_EVAL_SUCCEEDED;
		return spResult;
	}

	OclCommon::ExceptionPool Constraint::GetExceptions()
	{
		if ( m_eState <= CS_DEFINED )
			throw m_eState;
		return ( m_eState > CS_CTX_PARSE_FAILED && m_eState <= CS_CTX_CHECK_SUCCEEDED ) ? m_poolCtxExceptions : m_poolExceptions;
	}

	OclCommon::ExceptionPool Constraint::GetExceptions( bool bContext )
	{
		if ( m_eState <= CS_DEFINED )
			throw m_eState;
		return ( bContext ) ? m_poolCtxExceptions : m_poolExceptions;
	}

	OclTree::ViolationVector Constraint::GetViolations()
	{
		if ( m_eState < CS_EVAL_FAILED )
			throw m_eState;
		return m_vecViolations;
	}

	void Constraint::setPatProcessFlag(bool bflag)
	{
		OCLParser::m_bProcessingPat = bflag;
	}

}; // namespace Ocl