//###############################################################################################################################################
//
//	Object Constraint Language Expression Checker For UML
//	UMLConstraint.h
//
//===============================================================================================================================================
//
//	Copyright (c) Vanderbilt University, 2000-2002
//	ALL RIGHTS RESERVED
//
//	Vanderbilt University disclaims all warranties with regard to this
//	software, including all implied warranties of merchantability
//	and fitness.  In no event shall Vanderbilt University be liable for
//	any special, indirect or consequential damages or any damages
//	whatsoever resulting from loss of use, data or profits, whether
//	in an action of contract, negligence or other tortious action,
//	arising out of or in connection with the use or performance of
//	this software.
//
//###############################################################################################################################################

#ifndef UMLConstraint_h
#define UMLConstraint_h

#include "GMECommon.h"
#include "OCLConstraint.h"
#include "OCLRefCount.h"

// Predeclarations

namespace OCLUML
{
	class Constraint;

	typedef OclCommon::RCSmart<Constraint> 	SpConstraint;
	typedef GOCL_STL_NS()vector<SpConstraint>				ConstraintVector;

	class ConstraintDef;

	typedef OclCommon::RCSmart<ConstraintDef> 	SpConstraintDef;
	typedef GOCL_STL_NS()vector<SpConstraintDef>				ConstraintDefVector;


// Declarations

//##############################################################################################################################################
//
//	C L A S S : OCLUML::Constraint <<< + Ocl::Constraint, OclCommon::ReferenceCountable< Constraint >
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class Constraint
		: public Ocl::Constraint, public OclCommon::ReferenceCountable< Constraint >
	{
		private :
			GOCL_STL_NS()string	m_strExpression;

		public :
										Constraint( const GOCL_STL_NS()string& strContextType, CComPtr<IMgaFCO> spFCO );
				virtual					~Constraint();
						GOCL_STL_NS()string			GetExpression() const;
	};

//##############################################################################################################################################
//
//	C L A S S : OCLUML::ConstraintDef <<< + Ocl::Constraint, OclCommon::ReferenceCountable< ConstraintDef >
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class ConstraintDef
		: public Ocl::Constraint, public OclCommon::ReferenceCountable< ConstraintDef >
	{
		private :
			GOCL_STL_NS()string	m_strExpression;
			GOCL_STL_NS()string	m_strParameterList;
			GOCL_STL_NS()string	m_strStereotype;

		public :
										ConstraintDef( const GOCL_STL_NS()string& strContextType, CComPtr<IMgaFCO> spFCO );
				virtual					~ConstraintDef();
						GOCL_STL_NS()string			GetExpression() const;
						GOCL_STL_NS()string 			GetParameterList() const;
						GOCL_STL_NS()string			GetStereotype() const;
	};


}; // namespace OCLUML

#endif // UMLConstraint_h