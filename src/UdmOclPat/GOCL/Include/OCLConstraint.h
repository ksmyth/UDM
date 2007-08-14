//###############################################################################################################################################
//
//	Object Constraint Language Generic Manager
//	OCLConstraint.h
//
//###############################################################################################################################################

#ifndef OCLConstraint_h
#define OCLConstraint_h

#pragma warning ( disable : 4786 )

#include "OCLTree.h"

namespace Ocl
{
	class Constraint;

//##############################################################################################################################################
//
//	C L A S S : Ocl::Constraint
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class Constraint
	{
		public :
			typedef enum State
				{
					CS_UNREGISTERED = 0,
					CS_REGISTERED = 1,
					CS_DEFINED = 2,
					CS_CTX_PARSE_FAILED = 3,
					CS_CTX_PARSE_SUCCEEDED = 4,
					CS_CTX_CHECK_FAILED = 5,
					CS_CTX_CHECK_SUCCEEDED = 6,
					CS_PARSE_FAILED = 7,
					CS_PARSE_SUCCEEDED = 8,
					CS_CHECK_FAILED = 9,
					CS_CHECK_SUCCEEDED = 10,
					CS_CHECK_DEPENDENCY_FAILED = 11,
					CS_CHECK_DEPENDENCY_SUCCEEDED = 12,
					CS_EVAL_FAILED = 13,
					CS_EVAL_SUCCEEDED = 14
				};

			typedef enum Stereotype
				{
					CS_INVARIANT = 20,
					CS_PRECONDITION = 21,
					CS_POSTCONDITION = 22,
					CS_ATTRIBUTEDEF = 23,
					CS_METHODDEF = 24
				};

		private :
			OclTree::TreeManager* 					m_pManager;
			OclTree::Constraint*						m_pCtxConstraint;
			OclTree::Constraint*						m_pConstraint;

			GOCL_STL_NS()string 										m_strText;
			GOCL_STL_NS()string 										m_strName;
			State 										m_eState;
			bool 										m_bDynamic;
			bool										m_bContextSucceeded;

			OclCommon::ExceptionPool 				m_poolCtxExceptions;
			OclCommon::ExceptionPool 				m_poolExceptions;
			OclTree::ViolationVector					m_vecViolations;

		public :
																Constraint();
																Constraint( OclTree::TreeManager* pManager );
																Constraint( OclTree::TreeManager* pManager, const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strText, bool bDynamic = false );
			virtual 												~Constraint();

					State 										Register( OclTree::TreeManager* pManager );
					State 										Define( const GOCL_STL_NS()string& strName, const GOCL_STL_NS()string& strText = "", bool bDynamic = false );

					GOCL_STL_NS()string 										GetDefinedName() const;
					State 										GetState() const;
					bool										IsValid() const;
					bool										IsDefined() const;
					GOCL_STL_NS()string 										GetText() const;
					bool 										IsDynamic() const;

					State 										ParseContext();

					GOCL_STL_NS()string 										GetName() const;
					Stereotype 								GetStereotype() const;

					State 										CheckContext();

					GOCL_STL_NS()string 										GetContextType() const;
					GOCL_STL_NS()string 										GetReturnType() const;
					OclCommon::FormalParameterVector 	GetFormalParameters() const;
					virtual GOCL_STL_NS()string							GetFullName() const;

					State Parse();

					State 										Check( OclTree::TypeContextStack& ctxTypes );

					OclMeta::DependencySet 					GetDependencySet() const;
					GOCL_STL_NS()string 										PrintTree() const;
					GOCL_STL_NS()string 										Print() const;

					State										SetDependencyResult( const OclMeta::DependencySet& setDependenies = OclMeta::DependencySet() );
					OclCommon::ExceptionPool 				GetExceptions();
					OclCommon::ExceptionPool 				GetExceptions( bool bContext );


					OclMeta::Object 							Evaluate( OclTree::ObjectContextStack& ctxObjects, bool bEnableLogicalShortCircuit = false, bool bEnableIteratorShortCircuit = false, bool bEnableTracking = true );

					OclTree::ViolationVector 					GetViolations();
					static void setPatProcessFlag(bool bFlag);
					//static void setPatOutputFile(std::string str) { OclTree::PatHelper::f_pat_output.open(str.c_str()); };
					//static void closePatOutputFile() { OclTree::PatHelper::f_pat_output.close(); };
	};
}; // namespace Ocl

#endif // OCLConstraint_h