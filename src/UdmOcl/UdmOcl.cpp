//###############################################################################################################################################
//
//	Object Constraint Language Implementation For UDM
//	UDMOCL.cpp
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

//###############################################################################################################################################
  
#ifndef _WIN32
#include <stdio.h>
char *_itoa( int value, char *string, int radix )
{
	sprintf(string, "%d", value);
};
#endif

#include "UdmOcl.h"
#include "UmlExt.h" 

#include "OCLObjectExBasic.h"
#include "OCLRefCount.h"
#include "OCLConstraint.h"
#include "OCLTree.h"

#include "UdmOclObject.h"
#include "UdmOclType.h"


#define LINE_END std::string( "\r\n" )
#define LARGE_DELIMITER std::string( "##############################################################" ) + LINE_END
#define SMALL_DELIMITER std::string( "--------------------------------------------------------------" ) + LINE_END


namespace Ocl
{

	class ConstraintBase;
	class ConstraintEx;
	class ConstraintDefEx;
	class ConstraintDefinitionFactory;
	class Facade;

	typedef OclCommon::RCSmart<Facade> SpFacade;
	typedef std::vector< OclMeta::DependencySet > DependencySetVector;

	typedef std::map< ::Uml::Constraint, ConstraintEx* > ConstraintMap;
	typedef std::vector< ConstraintDefEx* > ConstraintDefVector;
	typedef std::map< ::Uml::Diagram , SpFacade > FacadeMap;

	FacadeMap globalFacadeMap;

//###############################################################################################################################################
//
// FUNCTIONS
//
//###############################################################################################################################################

void inReplace( std::string& str, const std::string& str1, const std::string& str2 )
{
	int iPos = 0;
	int iPosFrom = 0;
	while ( ( iPos = str.find( str1, iPosFrom ) ) != std::string::npos ) {
		str = str.substr( iPosFrom, iPos ) + str2 + str.substr( iPos + str1.length() );
		iPosFrom = iPos + str1.length();
	}
}

//###############################################################################################################################################
//
// CLASS : ConstraintBase
//
//###############################################################################################################################################

	class ConstraintBase
		: public Constraint
	{
		protected :
			Facade*		m_pFacade;

		protected :
			ConstraintBase( Facade* pFacade );

		public :
			virtual ~ConstraintBase() {}

			std::string				PrintCompilationErrors( bool bWithSelf = true ) const;
			std::string 				PrintEvaluationViolations( bool bWithSelf = true ) const;
			virtual std::string		Print( bool bOnlyIdentity = false ) const = 0;
	};

//###############################################################################################################################################
//
// CLASS : ConstraintEx
//
//###############################################################################################################################################

	class ConstraintEx
		: public ConstraintBase
	{
		private :
			::Uml::Constraint m_objConstraint;
			bool b_PatProcessing;

		public :
			ConstraintEx( Facade* pFacade, const ::Uml::Constraint& objConstraint );
			ConstraintEx( Facade* pFacade, const std::string& _strContext, const std::string& _strExpression );

			bool				Compile( const SErrorNotification& sEN );
			EEvaluationResult	Evaluate( const Udm::Object& context, const SEvaluationOptions& sEO );
			virtual std::string		Print( bool bOnlyIdentity = false ) const;
	};

//###############################################################################################################################################
//
// CLASS : ConstraintDefEx
//
//###############################################################################################################################################

	class ConstraintDefEx
		: public ConstraintBase
	{
		private :
			::Uml::ConstraintDefinition m_objDefinition;
			bool m_bIsMethod;

		public :
			ConstraintDefEx( Facade* pFacade, const ::Uml::ConstraintDefinition& objDefinition );

			virtual std::string		Print( bool bOnlyIdentity = false ) const;
			bool				IsMethod() const;
	};

//###############################################################################################################################################
//
// CLASS : Facade
//
//###############################################################################################################################################

	class Facade
		: public OclCommon::ReferenceCountable< Facade >
	{
		private :
			::Uml::Diagram 					m_objDiagram;
			OclMeta::TypeManager* 		m_pTypeManager;
			OclTree::TreeManager* 		m_pTreeManager;
			ConstraintMap					m_mapConstraints;
			ConstraintDefVector			m_vecConstraintDefs;

		public :
			Facade( const ::Uml::Diagram& objDiagram );
			~Facade();

			bool Initialize( const SErrorNotification& sEN );

			EEvaluationResult CheckAll( Udm::Object objObject, const set< ::Uml::Constraint>& setConstraints, const SEvaluationOptions& options );

		private :
			bool LoadConstraintDefinitions( const SErrorNotification& sEN );
			bool CompileConstraintDefinitions( const SErrorNotification& sEN );
			bool CompileConstraints( const SErrorNotification& sEN );
			std::string GetSignature( ConstraintDefEx* pDefinition );

			set<ConstraintEx*> GetAll( const ::Uml::Class& objClass );
			set<ConstraintEx*> GetAll( const set< ::Uml::Constraint>& setConstraints );

			EEvaluationResult CheckAll( Udm::Object objObject, const set<ConstraintEx*>& vecConstraints, const SEvaluationOptions& options );
			EEvaluationResult CheckAll( Udm::Object inObject, const set<ConstraintEx*>& vecConstraints, const SEvaluationOptions& options, int iDepth );

		friend class ConstraintEx;
		friend class ConstraintDefEx;
		friend class ConstraintDefinitionFactory;
	};

//###############################################################################################################################################
//
// CLASS : ConstraintAttribute - IMPLEMENTATION
//
//###############################################################################################################################################

	class ConstraintAttribute
		: public OclImplementation::Attribute
	{
		private :
			ConstraintDefEx*					m_pConstraintDef;

		public :
			ConstraintAttribute( ConstraintDefEx* pConstraintDef )
				: m_pConstraintDef( pConstraintDef )
			{
			}

			void operator()()
			{
				if ( ! m_pConstraintDef || m_pConstraintDef->GetState() < Ocl::Constraint::CS_CHECK_DEPENDENCY_SUCCEEDED )
					ThrowException( "Constraint attribute definition cannot be evaluated." );
				DECL_UDMOBJECT( objThis, GetThis() );
				if ( ! objThis )
					ThrowException( "Object is null." );
				OclTree::ObjectContextStack context;
				context.AddVariable( "dn", CREATE_UDMDATANETWORK( GetTypeManager(), objThis.__impl()->__getdn() ) );
				context.AddVariable( "self", GetThis() );
				SetResult( m_pConstraintDef->Evaluate( context ) );
			}
	};

//###############################################################################################################################################
//
// CLASS : ConstraintMethod - IMPLEMENTATION
//
//###############################################################################################################################################

	class ConstraintMethod
		: public OclImplementation::Method
	{
		private :
			ConstraintDefEx*					m_pConstraintDef;

		public :
			ConstraintMethod( ConstraintDefEx* pConstraintDef )
				: m_pConstraintDef( pConstraintDef )
			{
			}

			void operator()()
			{
				if ( ! m_pConstraintDef || m_pConstraintDef->GetState() < Ocl::Constraint::CS_CHECK_DEPENDENCY_SUCCEEDED )
					ThrowException( "Constraint method definition cannot be evaluated." );
				DECL_UDMOBJECT( objThis, GetThis() );
				if ( ! objThis )
					ThrowException( "Object is null." );
				OclTree::ObjectContextStack context;
				context.AddVariable( "dn", CREATE_UDMDATANETWORK( GetTypeManager(), objThis.__impl()->__getdn() ) );
				context.AddVariable( "self", GetThis() );
				OclCommon::FormalParameterVector vecParameters = m_pConstraintDef->GetFormalParameters();
				for ( int i = 0 ; i < vecParameters.size() ; i++ )
					context.AddVariable( vecParameters[ i ].GetName(), ( i >= GetArgumentCount() ) ? OclMeta::Object::UNDEFINED : GetArgument( i ) );
				SetResult( m_pConstraintDef->Evaluate( context ) );
			}
	};

//###############################################################################################################################################
//
// CLASS : ConstraintDefinitionFactory - IMPLEMENTATION
//
//###############################################################################################################################################

	class ConstraintDefinitionFactory
		: public OclImplementation::ConstraintDefinitionFactory
	{
		public :
			Facade* m_pFacade;

			virtual void GetFeatures( const OclSignature::Attribute& signature, OclMeta::AttributeVector& vecFeatures )
			{
				ConstraintDefVector& vecDefs = m_pFacade->m_vecConstraintDefs;
				for ( int i = 0 ; i < vecDefs.size() ; i++ ) {
					if ( vecDefs[ i ]->IsValid() && m_pFacade->m_pTreeManager->GetTypeManager()->IsTypeA( signature.GetTypeName(), vecDefs[ i ]->GetContextType() ) >= 0 )
						if ( vecDefs[ i ]->GetName() == signature.GetName() && ! vecDefs[ i ]->IsMethod() )
						{
							vecFeatures.push_back( new OclMeta::Attribute( signature.GetName(), CreateReturnType( vecDefs[ i ]->GetReturnType() ), new ConstraintAttribute( vecDefs[ i ] ), true, true ) );

						}
				}
			}

			virtual void GetFeatures( const OclSignature::Method& signature, OclMeta::MethodVector& vecFeatures )
			{
				ConstraintDefVector& vecDefs = m_pFacade->m_vecConstraintDefs;
				for ( int i = 0 ; i < vecDefs.size() ; i++ ) {
					if ( vecDefs[ i ]->IsValid() && m_pFacade->m_pTreeManager->GetTypeManager()->IsTypeA( signature.GetTypeName(), vecDefs[ i ]->GetContextType() ) >= 0 )
						if ( vecDefs[ i ]->GetName() == signature.GetName() && vecDefs[ i ]->IsMethod() && vecDefs[ i ]->GetFormalParameters().size() == signature.GetParameterCount() )
							const std::string name = signature.GetName();
							const  OclCommon::FormalParameterVector fpv  = CreateFormalParameters( vecDefs[ i ]->GetFormalParameters() );
							TypeSeq ts = CreateReturnType( vecDefs[ i ]->GetReturnType() );
							vecFeatures.push_back( new OclMeta::Method(signature.GetName(), fpv , ts , new ConstraintMethod( vecDefs[ i ] ), true, true ) );
				}
			}

		private :
			TypeSeq CreateReturnType( const std::string& strType )
			{
				TypeSeq vecType;
				OclCommon::Convert( strType, vecType );
				return vecType;
			}

			OclCommon::FormalParameterVector CreateFormalParameters( const OclCommon::FormalParameterVector& vecParamsIn ) const
			{
				OclCommon::FormalParameterVector vecParams;
				for ( int j = 0 ; j < vecParamsIn.size() ; j++ ) {
					TypeSeq vecType;
					OclCommon::Convert( vecParamsIn[ j ].GetTypeName(), vecType );
					vecParams.push_back( OclCommon::FormalParameter( vecParamsIn[ j ].GetName(), vecType[ 0 ], true ) );
				}
				return vecParams;
			}
	};

//###############################################################################################################################################
//
// CLASS : ConstraintBase - IMPLEMENTATION
//
//###############################################################################################################################################

	ConstraintBase::ConstraintBase( Facade* pFacade )
		: m_pFacade( pFacade )
	{
	}

	std::string ConstraintBase::PrintCompilationErrors( bool bWithSelf ) const
	{
		std::string strResult = Print( ! bWithSelf ) + SMALL_DELIMITER;
		OclCommon::ExceptionPool poolExceptions = (( ConstraintBase* const ) this )->GetExceptions();
		for ( int i = 0 ; i < poolExceptions.Size() ; i++ ) {
			OclCommon::Exception ex = poolExceptions.GetAt( i );
			if ( ex.GetLine() < 0 )
				strResult += "Line: ? ";
			else {
				char chBuffer[ 300 ];
				_itoa( ex.GetLine(), chBuffer, 10 );
				strResult += "Line: " + std::string( chBuffer );
			}
			if ( ex.GetCode() == -1 )
				strResult += " Code: ? ";
			else {
				char chBuffer[ 300 ];
				_itoa( ex.GetCode(), chBuffer, 10 );
				strResult += " Code: " + std::string( chBuffer );
			}
			strResult += " Message: " + ex.GGetMessage() + LINE_END;
		}
		strResult += LARGE_DELIMITER;
		return strResult;
	}

	std::string ConstraintBase::PrintEvaluationViolations( bool bWithSelf ) const
	{
		std::string strResult = Print( ! bWithSelf ) + SMALL_DELIMITER;
		OclTree::ViolationVector vecViolations = (( ConstraintBase* const ) this )->GetViolations();
		for ( int i = 0 ; i < vecViolations.size() ; i++ ) {
			OclTree::Violation vi = vecViolations[ i ];
			if ( vi.position.iLine < 0 )
				strResult += "Line: ? ";
			else {
				char chBuffer[ 300 ];
				_itoa( vi.position.iLine, chBuffer, 10 );
				strResult += "Line: " + std::string( chBuffer );
			}
			strResult += " Message: " + vi.strMessage + "[ " + vi.strSignature + " ]" + LINE_END;
			for ( int j = 0 ; j < vi.vecVariables.size() ; j++ )
				strResult += "\t " + vi.vecVariables[ j ] + ": " + vi.vecObjects[ j ] + LINE_END;
		}
		strResult += LARGE_DELIMITER;
		return strResult;
	}

//###############################################################################################################################################
//
// CLASS : ConstraintEx - IMPLEMENTATION
//
//###############################################################################################################################################

	static long lCounter = 0;

	ConstraintEx::ConstraintEx( Facade* pFacade, const ::Uml::Constraint& objConstraint )
		: ConstraintBase( pFacade ), m_objConstraint( objConstraint )
	{
		::Uml::Class context = objConstraint.parent();
		std::string strType = (std::string) ((::Uml::Namespace)context.parent()).name() + "::" + (std::string) context.name();
		std::string strName = objConstraint.name();
		std::string strExpression = objConstraint.expression();

		Define( strType + "::" + strName, "context " + strType + " inv " + strName + " : " + LINE_END + LINE_END + strExpression, true );
		//printf( ("context " + strType + " inv " + strName + " : " + strExpression + "\n").c_str());
		Register( m_pFacade->m_pTreeManager );
		b_PatProcessing = false;
	}

	ConstraintEx::ConstraintEx( Facade* pFacade, const std::string& _strContext, const std::string& _strExpression )
		: ConstraintBase( pFacade )
	{
		char chBuffer[ 30 ];
		sprintf( chBuffer, "UdmPatConstraint%d", lCounter++ );
		std::string strType = /*"meta::" + */_strContext;	//strContext should be fullt qualified!
		std::string strName = chBuffer;
		std::string strExpression = _strExpression;
		Define( strType + "::" + strName, "context " + strType + " inv " + strName + " : " + LINE_END + LINE_END + strExpression, true );
		//printf( ("context " + strType + " inv " + strName + " : " + strExpression + "\n").c_str());
		Register( m_pFacade->m_pTreeManager );
		b_PatProcessing = true;
	}

	bool ConstraintEx::Compile( const SErrorNotification& sEN )
	{
		// Parse the Constraint

		Constraint::State eState = Parse();
		if ( eState != Ocl::Constraint::CS_PARSE_SUCCEEDED ) {

			std::string strErr = LARGE_DELIMITER + "SYNTAX ERROR >> " + PrintCompilationErrors();
			if ( sEN.bStdOutEnabled )
				cout << strErr << endl;
			if ( sEN.eExceptionKind != ENT_NONE )
				throw udm_exception( strErr );
			return false;
		}

		// Check the Constraint

		OclTree::TypeContextStack context;
		context.AddVariable( "dn", TypeSeq( 1, "udm::DataNetwork" ) );
		eState = Check( context );
		if ( eState != Ocl::Constraint::CS_CHECK_SUCCEEDED ) {
			std::string strErr = LARGE_DELIMITER + "SEMANTICAL ERROR >> " + PrintCompilationErrors();
			if ( sEN.bStdOutEnabled )
				cout << strErr << endl;
			if ( sEN.eExceptionKind != ENT_NONE )
				throw udm_exception( strErr );
			return false;
		}

		// Check Dependencies

		OclMeta::DependencySet setDependencies = GetDependencySet();
		eState = SetDependencyResult( setDependencies );
		if ( eState != Ocl::Constraint::CS_CHECK_DEPENDENCY_SUCCEEDED ) {
			std::string strErr = LARGE_DELIMITER + "DEPENDENCY ERROR >> " + PrintCompilationErrors();
			if ( sEN.bStdOutEnabled )
				cout << strErr << endl;
			if ( sEN.eExceptionKind != ENT_NONE )
				throw udm_exception( strErr );
			return false;
		}
		return true;
	}

	EEvaluationResult ConstraintEx::Evaluate( const Udm::Object& object, const SEvaluationOptions& options )
	{
		// Fill the Context of the Constraint

		OclTree::ObjectContextStack context;
		context.AddVariable( "dn", CREATE_UDMDATANETWORK( m_pFacade->m_pTypeManager, object.__impl()->__getdn() ) );
		context.AddVariable( "self", CREATE_UDMOBJECT( m_pFacade->m_pTypeManager, object ) );

		// Evaluate the Constraint
		OclMeta::Object spResult = Constraint::Evaluate( context, options.bLogicalShortCircuit, options.bIteratorShortCircuit, options.bTrackingEnabled );

		if ( spResult.IsUndefined() ) {
			std::string strErr = LARGE_DELIMITER + "CONSTRAINT FAILURE >> " + PrintEvaluationViolations();
			if ( options.sErrorNotification.bStdOutEnabled )
				cout << strErr << endl;
			if ( options.sErrorNotification.eExceptionKind != ENT_NONE )
				throw udm_exception( strErr );
			return CER_UNDEFINED;
		}

		DECL_BOOLEAN( bResult, spResult );
		EEvaluationResult eResult = CER_TRUE;
		if ( ! bResult ) {
			eResult = CER_FALSE;
			std::string strErr = LARGE_DELIMITER + "CONSTRAINT VIOLATION >> " + PrintEvaluationViolations();
			if ( options.sErrorNotification.bStdOutEnabled )
				cout << strErr << endl;
			if ( options.sErrorNotification.eExceptionKind != ENT_NONE )
				throw udm_exception( strErr );
		}

		return eResult;
	}

	std::string ConstraintEx::Print( bool bOnlyIdentity ) const
	{
		std::string strType = "";
		std::string strName = "";
		::Uml::Class context;
		if(!b_PatProcessing) {
			context = m_objConstraint.parent();
			strType = (std::string) ((::Uml::Namespace)context.parent()).name() + "::" + (std::string) context.name();
			strName = (std::string) m_objConstraint.name();
		} else {
			strType = "Failure in pattern file";
			strName = "";
		}
		std::string strResult = strType + "::" + strName + LINE_END;
		if ( ! bOnlyIdentity ) {
			strResult += SMALL_DELIMITER;
			if(!b_PatProcessing)
				strResult += "==> Description : " + LINE_END + (std::string) m_objConstraint.description() + LINE_END;
			else
				strResult += "==> Description : Some constraint in the pat.";
			strResult += "==> Expression : " + LINE_END;
			strResult += strType + "::" + strName + " context " + strType + " inv " + strName + " : " + LINE_END + LINE_END;
			if(!b_PatProcessing)
				strResult += (std::string) m_objConstraint.expression() + LINE_END;
			else
				strResult += " The Expression. ";
		}
		return strResult;
	}

//###############################################################################################################################################
//
// CLASS : ConstraintEx - IMPLEMENTATION
//
//###############################################################################################################################################

	ConstraintDefEx::ConstraintDefEx( Facade* pFacade, const ::Uml::ConstraintDefinition& objDefinition )
		: ConstraintBase( pFacade ), m_objDefinition( objDefinition )
	{
		::Uml::Class context = objDefinition.parent();
		std::string strType = (std::string) ((::Uml::Namespace)context.parent()).name() + "::" + (std::string) context.name();
		std::string strName = objDefinition.name();
		std::string strExpression = objDefinition.expression();
		std::string strParameterList = objDefinition.parameterList();
		m_bIsMethod = (std::string) objDefinition.stereotype() == "method";
		std::string strReturnType = objDefinition.returnType();
		std::string strStereotype = ( m_bIsMethod ) ? " defmethod " : " defattribute ";

		Define( strType + "::" + strName, "context " + strType + "::" + strName + "( " + strParameterList + " ) : " + strReturnType + strStereotype + strName + " : " + LINE_END + LINE_END+ strExpression, true );
		Register( m_pFacade->m_pTreeManager );
	}

	std::string ConstraintDefEx::Print( bool bOnlyIdentity ) const
	{
		::Uml::Class context = m_objDefinition.parent();
		std::string strType = (std::string) ((::Uml::Namespace)context.parent()).name() + "::" + (std::string) context.name();
		std::string strName = (std::string) m_objDefinition.name();
		std::string strParameterList = m_objDefinition.parameterList();
		std::string strReturnType = m_objDefinition.returnType();
		std::string strStereotype = ( m_bIsMethod ) ? " defmethod " : " defattribute ";
		std::string strResult = strType + "::" + strName;
		if ( m_bIsMethod )
			strResult += "( " + strParameterList + " )";
		strResult += " : " + strType + LINE_END;
		if ( ! bOnlyIdentity ) {
			strResult += SMALL_DELIMITER;
			strResult += "==> Expression : " + LINE_END;
			strResult += strType + "::" + strName + "context " + strType + "::" + strName + "( " + strParameterList + " ) : " + strReturnType + strStereotype + strName + " : " + LINE_END + LINE_END;
			strResult += (std::string) m_objDefinition.expression() + LINE_END;
		}
		return strResult;
	}

	bool ConstraintDefEx::IsMethod() const
	{
		return m_bIsMethod;
	}

//###############################################################################################################################################
//
// CLASS : Facade - IMPLEMENTATION
//
//###############################################################################################################################################

	Facade::Facade( const ::Uml::Diagram& objDiagram )
		: m_objDiagram( objDiagram )
	{
		 //printf("creating facade.");
		ConstraintDefinitionFactory* pCDFactory = new ConstraintDefinitionFactory();
		pCDFactory->m_pFacade = this;
		m_pTypeManager = new OclMeta::TypeManager( new UmlOcl::TypeFactory( m_objDiagram ), new OclBasic::OperatorFactory(), new OclBasic::FunctionFactory(), pCDFactory );
		m_pTreeManager = new OclTree::TreeManager( m_pTypeManager, new OclTree::ObjectNodeAdaptor(), new OclTree::CollectionNodeAdaptor() );
	}

	Facade::~Facade()
	{
		delete m_pTreeManager;
		for ( ConstraintMap::iterator it = m_mapConstraints.begin() ; it != m_mapConstraints.end() ; it++ )
			delete (*it).second;
		for ( int i = 0 ; i < m_vecConstraintDefs.size() ; i++ )
			delete m_vecConstraintDefs[ i ];
	}

	bool Facade::LoadConstraintDefinitions( const SErrorNotification& sEN )
	{
			//printf("UDMOCL: LoadConstraintDefinitions\t");
		std::string strErrAll( "" );
		bool bResult = true;

		set< ::Uml::Namespace> setNamespaces = m_objDiagram.namespaces();
		for(set< ::Uml::Namespace>::iterator itNamespace = setNamespaces.begin(); itNamespace != setNamespaces.end(); itNamespace++)
		{
			set< ::Uml::Class> setClasses = itNamespace->classes();
			for ( set< ::Uml::Class>::iterator itClass = setClasses.begin() ; itClass != setClasses.end() ; itClass++ ) 
			{
				set< ::Uml::ConstraintDefinition> setConstraintDefs = (*itClass).definitions();
				for ( set< ::Uml::ConstraintDefinition>::iterator itDefinition = setConstraintDefs.begin() ; itDefinition != setConstraintDefs.end() ; itDefinition++ ) {

					ConstraintDefEx* pDefinition = new ConstraintDefEx( this, *itDefinition );

					// Parse Context of the ConstraintDef

					Constraint::State eState = pDefinition->Parse();
					if ( eState != Constraint::CS_PARSE_SUCCEEDED ) {

						std::string strErr = LARGE_DELIMITER + "SYNTAX ERROR >> " + pDefinition->PrintCompilationErrors();
						if ( sEN.bStdOutEnabled )
							cout << strErr << endl;
						delete pDefinition;
						switch ( sEN.eExceptionKind ) {
							case ENT_FIRST :
								throw udm_exception( strErr );
								break;
							case ENT_ALL :
								strErrAll += LINE_END + strErr;
								break;
						}
						bResult = false;

					}
					else {

						// Check Context of the ConstraintDef

						pDefinition->ParseContext();
						eState = pDefinition->CheckContext();
						if ( eState != Constraint::CS_CTX_CHECK_SUCCEEDED ) {

							std::string strErr = LARGE_DELIMITER + "SEMANTICAL ERROR >> " + pDefinition->PrintCompilationErrors();
							if ( sEN.bStdOutEnabled )
								cout << strErr << endl;
							delete pDefinition;
							switch ( sEN.eExceptionKind ) {
								case ENT_FIRST :
									throw udm_exception( strErr );
									break;
								case ENT_ALL :
									strErrAll += LINE_END + strErr;
									break;
							}
							bResult = false;
						}
						else
							m_vecConstraintDefs.push_back( pDefinition );
					}
				}
			}

		}
		if ( ! strErrAll.empty() && sEN.eExceptionKind != ENT_NONE )
			throw udm_exception( strErrAll );
		return bResult;
	}

	bool Facade::CompileConstraintDefinitions( const SErrorNotification& sEN )
	{
			//printf("UDMOCL: CompileConstraintDefinitions\t");
		std::string strErrAll( "" );
		bool bResult = true;

		ConstraintDefVector vecFailed;
		ConstraintDefVector vecSucceeded;

		// Check All
		int i;
		for ( i = 0 ; i < m_vecConstraintDefs.size() ; i ++ ) {
			OclTree::TypeContextStack context;
			context.AddVariable( "dn", TypeSeq( 1, "udm::DataNetwork" ) );
			if ( m_vecConstraintDefs[ i ]->Check( context ) != Constraint::CS_CHECK_SUCCEEDED ) {
				std::string strErr = LARGE_DELIMITER + "SEMANTICAL ERROR >> " + m_vecConstraintDefs[ i ]->PrintCompilationErrors();
				if ( sEN.bStdOutEnabled )
					cout << strErr << endl;
				vecFailed.push_back( m_vecConstraintDefs[ i ] );
				switch ( sEN.eExceptionKind ) {
					case ENT_FIRST :
						throw udm_exception( strErr );
						break;
					case ENT_ALL :
						strErrAll += LINE_END + strErr;
						break;
				}
				bResult = false;
			}
			else
				vecSucceeded.push_back( m_vecConstraintDefs[ i ] );
		}

		// Sort only succeeded so far

		DependencySetVector vecDependencySets;

		for ( i = 0 ; i < vecSucceeded.size() ; i ++ )
			vecDependencySets.push_back( vecSucceeded[ i ]->GetDependencySet() );
		m_vecConstraintDefs = vecSucceeded;
		vecSucceeded.clear();

		// Collect all Error Dependencies

		StringVector vecErrors;
		for ( i = 0 ; i < vecFailed.size() ; i++ ) {
			std::string strSignature;
			try {
				strSignature = GetSignature( vecFailed[ i ] );
			}
			catch ( ... ) {
				strSignature = "#";
			}
			delete vecFailed[ i ];
			vecErrors.push_back( strSignature );
		}

		for ( i = 0 ; i < vecErrors.size() ; i++ ) {
			for ( int j = 0 ; j < vecDependencySets.size() ; j++ ) 
			{
				std::set<OclMeta::Dependency>::iterator dep_i = OclMeta::Dependency::LookUp( vecDependencySets[ j ], vecErrors[ i ] );
				if (dep_i == vecDependencySets[ j ].end()) continue;
				OclMeta::Dependency dep = *dep_i;
				if ( ! ( dep.m_strSignature == "#" ) ) 
				{
					OclMeta::Dependency::SetChecked( vecDependencySets[ j ], dep_i, true );
					std::string strSignature = GetSignature( m_vecConstraintDefs[ j ] );
					/*
						// this find function could not be compiled with VC7.x .NET'w own STL
						// c:\MobiesTransition\Udm.Net\src\UdmOcl\UdmOcl.cpp(701): error C2784: 'bool std::operator ==(const std::list<_Ty,_Alloc> &,const std::list<_Ty,_Alloc> &)' : could not deduce template argument for 'const std::list<_Ty,_Ax> &' from ''unknown-type''

					if ( find( vecErrors.begin(), vecErrors.end(), strSignature ) == vecErrors.end() )
						vecErrors.push_back( strSignature );

						//so I used thw following few line to replace it's functionality
					*/
					StringVector::iterator sv_i = vecErrors.begin();
					while (sv_i != vecErrors.end())
					{
						if (sv_i->compare(strSignature) == 0 ) break;
						sv_i++;
					};
					if (sv_i == vecErrors.end())
						vecErrors.push_back( strSignature );
				}
			}
		}

		// Set result dependencies

		for ( i = 0 ; i < m_vecConstraintDefs.size() ; i++ ) {
			if ( m_vecConstraintDefs[ i ]->SetDependencyResult( vecDependencySets[ i ] ) != Constraint::CS_CHECK_DEPENDENCY_SUCCEEDED ) {
				std::string strErr = LARGE_DELIMITER + "DEPENDENCY ERROR >> " + m_vecConstraintDefs[ i ]->PrintCompilationErrors();
				if ( sEN.bStdOutEnabled )
					cout << strErr << endl;
				delete m_vecConstraintDefs[ i ];
				switch ( sEN.eExceptionKind ) {
					case ENT_FIRST :
						throw udm_exception( strErr );
						break;
					case ENT_ALL :
						strErrAll += LINE_END + strErr;
						break;
				}
				bResult = false;
			}
			else
				vecSucceeded.push_back( m_vecConstraintDefs[ i ] );
		}

		// Sort only succeeded

		m_vecConstraintDefs = vecSucceeded;

		if ( ! strErrAll.empty() && sEN.eExceptionKind != ENT_NONE )
			throw udm_exception( strErrAll );
		return bResult;
	}

	std::string Facade::GetSignature( ConstraintDefEx* pDefinition )
	{
		if ( ! pDefinition->IsMethod() ) {
			OclSignature::Attribute signature( pDefinition->GetName(), pDefinition->GetContextType() );
			return signature.Print();
		}
		else {
			OclCommon::FormalParameterVector vecParameters = pDefinition->GetFormalParameters();
			StringVector vecTypes;
			for ( int i = 0 ; i < vecParameters.size() ; i++ ) {
				TypeSeq vecType;
				OclCommon::Convert( vecParameters[ i ].GetTypeName(), vecType );
				vecTypes.push_back( vecType[ 0 ] );
			}
			OclSignature::Method signature( pDefinition->GetName(), pDefinition->GetContextType(), vecTypes );
			return signature.Print();
		}
	}

	bool Facade::CompileConstraints( const SErrorNotification& sEN )
	{
		std::string strErrAll( "" );
		bool bResult = true;

		set< ::Uml::Namespace> setNamespaces = m_objDiagram.namespaces();
		for(set< ::Uml::Namespace>::iterator itNamespace = setNamespaces.begin(); itNamespace != setNamespaces.end(); itNamespace++)
		{
			set< ::Uml::Class> setClasses = itNamespace->classes();
			for ( set< ::Uml::Class>::iterator itClass = setClasses.begin() ; itClass != setClasses.end() ; itClass++ ) {
			set< ::Uml::Constraint> setConstraints = (*itClass).constraints();
			for ( set< ::Uml::Constraint>::iterator itConstraint = setConstraints.begin() ; itConstraint != setConstraints.end() ; itConstraint++ ) {

				ConstraintEx* pConstraint = new ConstraintEx( this, *itConstraint );
			//printf("UDMOCL: CompileConstraints\t");
				try {
					if ( ! pConstraint->Compile( sEN ) )
						bResult = false;
				}
				catch ( const udm_exception& ex ) {
					if ( sEN.eExceptionKind == ENT_FIRST ) {
						delete pConstraint;
						throw udm_exception( ex.what() );
					}
					bResult = false;
					strErrAll += LINE_END + (std::string) ex.what();
				}

				m_mapConstraints.insert( ConstraintMap::value_type( *itConstraint, pConstraint ) );
			}
		}
		}
		if ( ! strErrAll.empty() && sEN.eExceptionKind == ENT_ALL )
			throw udm_exception( strErrAll );
		return bResult;
	}

	bool Facade::Initialize( const SErrorNotification& sEN )
	{
		std::string strErrAll( "" );
		bool bResult = true;
		try {
			bResult = LoadConstraintDefinitions( sEN );
		}
		catch ( const udm_exception& ex ) {
			if ( sEN.eExceptionKind == ENT_FIRST )
				throw udm_exception( ex.what() );
			bResult = false;
			strErrAll += LINE_END + (std::string) ex.what();
		}

		try {
			bResult &= CompileConstraintDefinitions( sEN );
		}
		catch ( const udm_exception& ex ) {
			if ( sEN.eExceptionKind == ENT_FIRST )
				throw udm_exception( ex.what() );
			bResult = false;
			strErrAll += LINE_END + (std::string) ex.what();
		}

		try {
			bResult &= CompileConstraints( sEN );
		}
		catch ( const udm_exception& ex ) {
			if ( sEN.eExceptionKind == ENT_FIRST )
				throw udm_exception( ex.what() );
			bResult = false;
			strErrAll += LINE_END + (std::string) ex.what();
		}

		if ( ! strErrAll.empty() && sEN.eExceptionKind == ENT_ALL )
			throw udm_exception( strErrAll );
		return bResult;
	}

	set<ConstraintEx*> Facade::GetAll( const ::Uml::Class& objClass )
	{
		set<ConstraintEx*> setResult;
		set< ::Uml::Class> setClasses = Uml::AncestorClasses( objClass );
		for ( set< ::Uml::Class>::iterator itClass = setClasses.begin() ; itClass != setClasses.end() ; itClass++ ) {
			set< ::Uml::Constraint> setConstraints = (*itClass).constraints();
			for ( set< ::Uml::Constraint>::iterator itConstraint = setConstraints.begin() ; itConstraint != setConstraints.end() ; itConstraint++ )
				setResult.insert( (*m_mapConstraints.find( *itConstraint )).second );
		}
		return setResult;
	}

	set<ConstraintEx*> Facade::GetAll( const set< ::Uml::Constraint>& setConstraints )
	{
		set<ConstraintEx*> setResult;
		for ( set< ::Uml::Constraint>::const_iterator itConstraint = setConstraints.begin() ; itConstraint != setConstraints.end() ; itConstraint++ )
			setResult.insert( (*m_mapConstraints.find( *itConstraint )).second );
		return setResult;
	}

	EEvaluationResult Facade::CheckAll( Udm::Object objObject, const set< ::Uml::Constraint>& setConstraints, const SEvaluationOptions& options )
	{
		set<ConstraintEx*> setConstraints2 = GetAll( setConstraints );
		return CheckAll( objObject, setConstraints2, options, 0 );
	}

	EEvaluationResult Facade::CheckAll( Udm::Object objObject, const set<ConstraintEx*>& setConstraints, const SEvaluationOptions& options )
	{
		set<ConstraintEx*> setConstraintsClass = GetAll( objObject.type() );
		EEvaluationResult eResult = CER_TRUE;
		std::string strErrAll( "" );

		for ( set<ConstraintEx*>::iterator it = setConstraintsClass.begin() ; it != setConstraintsClass.end() ; it++ ) {
			if ( setConstraints.empty() || setConstraints.find( *it ) != setConstraints.end() ) {
				if ( ! (*it)->IsValid() ) {
					if ( ! options.bSkipInvalids ) {
						std::string strErr = LARGE_DELIMITER + "CONSTRAINT IS UNCOMPILED >> " + (*it)->PrintCompilationErrors();
						if ( options.sErrorNotification.bStdOutEnabled )
							cout << strErr << endl;
						switch ( options.sErrorNotification.eExceptionKind  ) {
							case ENT_FIRST :
								throw udm_exception( strErr );
								break;
							case ENT_ALL :
								strErrAll += LINE_END + strErr;
								break;
						}
						eResult = CER_UNDEFINED;
					}
				}
				else {
					try {
						switch ( (*it)->Evaluate( objObject, options ) ) {
							case CER_FALSE :
								if ( eResult == CER_TRUE )
									eResult = CER_FALSE;
								break;
							case CER_UNDEFINED :
								eResult = CER_UNDEFINED;
								break;
						}
					}
					catch ( const udm_exception& ex ) {
						switch ( options.sErrorNotification.eExceptionKind ) {
							case ENT_FIRST :
								throw udm_exception( ex.what() );
								break;
							case ENT_ALL :
								strErrAll += LINE_END + (std::string) ex.what();
								break;
						}
					}
				}
			}
		}
		if ( ! strErrAll.empty() && options.sErrorNotification.eExceptionKind != ENT_NONE )
			throw udm_exception( strErrAll );
		return eResult;
	}

	EEvaluationResult Facade::CheckAll( Udm::Object objObject, const set<ConstraintEx*>& setConstraints, const SEvaluationOptions& options, int iDepth )
	{
		EEvaluationResult eResult = CER_TRUE;
		std::string strErrAll( "" );

		try {
			eResult = CheckAll( objObject, setConstraints, options );
		} catch ( const udm_exception& ex ) {
			switch ( options.sErrorNotification.eExceptionKind ) {
				case ENT_FIRST :
					throw udm_exception( ex.what() );
					break;
				case ENT_ALL :
					strErrAll += LINE_END + (std::string) ex.what();
					break;
			}
		}

		if ( options.iContainmentDepth < 0 || iDepth < options.iContainmentDepth ) {
			set<Udm::Object> setChildren = ( ( Udm::Object )objObject ).GetChildObjects();
			for ( set<Udm::Object>::iterator itChild = setChildren.begin() ; itChild != setChildren.end() ; itChild++ ) {
				try {
					switch( CheckAll( *itChild, setConstraints, options, iDepth++ ) ) {
						case CER_FALSE :
							if ( eResult == CER_TRUE )
								eResult = CER_FALSE;
							break;
						case CER_UNDEFINED :
							eResult = CER_UNDEFINED;
							break;
					}
				} catch ( const udm_exception& ex ) {
					switch ( options.sErrorNotification.eExceptionKind ) {
						case ENT_FIRST :
							throw udm_exception( ex.what() );
							break;
						case ENT_ALL :
							strErrAll += LINE_END + (std::string) ex.what();
							break;
					}
				}
			}
		}

		if ( ! strErrAll.empty() && options.sErrorNotification.eExceptionKind != ENT_NONE )
			throw udm_exception( strErrAll );
		return eResult;
	}

//###############################################################################################################################################
//
// CLASS : Evaluator - IMPLEMENTATION
//
//###############################################################################################################################################

	UDM_DLL Evaluator::Evaluator( const Udm::Object& objObject, const set< ::Uml::Constraint>& setConstraints )
		: m_objObject( objObject ), m_setConstraints( setConstraints )
	{
	}

	UDM_DLL Evaluator::Evaluator( const Evaluator& evaluator )
		: m_objObject( evaluator.m_objObject ), m_setConstraints( evaluator.m_setConstraints )
	{
	}

	UDM_DLL Evaluator& Evaluator::operator=( const Evaluator& evaluator )
	{
		if ( this != &evaluator ) {
			m_objObject = evaluator.m_objObject;
			m_setConstraints = evaluator.m_setConstraints;
		}
		return *this;
	}

	UDM_DLL Udm::Object& Evaluator::object() const
	{
		return ( Udm::Object& ) m_objObject;
	}

	UDM_DLL set< ::Uml::Constraint>& Evaluator::constraints() const
	{
		return ( set< ::Uml::Constraint>& ) m_setConstraints;
	}

	UDM_DLL EEvaluationResult Evaluator::Check( const SEvaluationOptions& sOptions ) const
	{
		FacadeMap::iterator it = globalFacadeMap.find( ( (::Uml::Namespace)((::Uml::Class) m_objObject.type() ).parent()).parent() );
		if ( it == globalFacadeMap.end() ) {
			return CER_UNDEFINED;
		}
		return (*it).second->CheckAll( m_objObject, m_setConstraints, sOptions );
	}

//###############################################################################################################################################
//
// FUNCTION : Initialize - IMPLEMENTATION
//
//###############################################################################################################################################

	UDM_DLL bool Initialize( const ::Uml::Diagram& objDiagram, const SErrorNotification& sErrorNotification )
	{
		//printf("Start Initialize");
		SpFacade spFacade( new Facade( objDiagram ) );
		bool bResult = spFacade->Initialize( sErrorNotification );
		globalFacadeMap[ objDiagram ] = spFacade;
		Constraint::setPatProcessFlag(false);
		return bResult;
	}

 	UDM_DLL void UnInitialize()
	{
		globalFacadeMap.clear();
	}

	UDM_DLL bool ProcessPat( const ::Uml::Diagram& metaDiagram, const Udm::Object& objContext, const std::string& strExpression)
	{
		std::string strContext = (string)objContext.type().name();
		SErrorNotification en = SErrorNotification();
		Initialize( metaDiagram, en );
		Constraint::setPatProcessFlag(true);
		//Constraint::setPatOutputFile("testoutput.out");
		ConstraintEx cons = ConstraintEx( globalFacadeMap[ metaDiagram ], strContext, strExpression);
		SEvaluationOptions options = SEvaluationOptions();
		cons.Compile(en);
		EEvaluationResult eResult = cons.Evaluate( objContext, options );
		OclTree::PatHelper::clean();
		Constraint::setPatProcessFlag(false);
		//Constraint::closePatOutputFile();
		return true;
	}

}; // namespace Ocl

namespace UdmPat {

	UDM_DLL bool ProcessPat( const ::Uml::Diagram& metaDiagram, const Udm::Object& dataNetwork , const std::string& strExpression)
	{
		return Ocl::ProcessPat(metaDiagram, dataNetwork, strExpression);
	}


}; // namespace UdmPat
