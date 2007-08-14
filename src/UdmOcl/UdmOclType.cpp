//###############################################################################################################################################
//
//	Object Constraint Language Implementation For UDM
//	UDMOCLType.cpp
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

#include "UdmOclType.h"
#include "OCLObjectExBasic.h"
#include "UdmOclObject.h"





#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#include "Uml.h"
#include "UmlExt.h"
using namespace Uml;

namespace UmlOcl
{
  #ifndef _WIN32 // clash from gocl under linux

char *_strlwr( char *string )
{
	if (string)
	{
		for (int i = 0; i< strlen(string); i++)
			*(string + i) = tolower(*(string+i));
	};
	return string;
};




#endif


	GOCL_STL_NS()string LowerFirst( const GOCL_STL_NS()string& strValue )
	{
		if ( strValue.empty() )
			return strValue;
		return GOCL_STL_NS()string( _strlwr( (char*)strValue.substr( 0, 1 ).c_str() ) ) + strValue.substr( 1 );
	}

//##############################################################################################################################################
//
//	T Y P E   O F   uml::DataNetwork
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class TDataNetworkDerived_Classes
		: public OclImplementation::Association
	{
		private :
			const ::Uml::Uml::Class m_class;

		public :
			TDataNetworkDerived_Classes( const ::Uml::Uml::Class& inClass )
				: m_class( inClass )
			{
			}

			void operator()()
			{
				DECL_UDMDATANETWORK( objThis, GetThis() );
				if ( ! objThis )
					ThrowException( "Object is null." );
				OclMeta::ObjectVector vecOut;
				Collect( vecOut, objThis->GetRootObject() );
				SetResult( CREATE_SET( GetTypeManager(), vecOut ) );
			}

			void Collect( OclMeta::ObjectVector& vecResult, Udm::Object object )
			{
				if ( ::Uml::IsDerivedFrom(object.type(),m_class) )
					vecResult.push_back( CREATE_UDMOBJECT( GetTypeManager(), object ) );
				set<Udm::Object> setChildren = object.GetChildObjects();
				for ( set<Udm::Object>::iterator it = setChildren.begin() ; it != setChildren.end() ; it++ )
					Collect( vecResult, *it );
			}
	};

	class TDataNetwork_AssociationFactory
		: public OclImplementation::AssociationFactory
	{
		private :
			const ::Uml::Uml::Diagram m_diagram;

		 public :
			 TDataNetwork_AssociationFactory( const ::Uml::Uml::Diagram& diagram )
		 		: m_diagram( diagram )
		 	{
		 	}

			virtual void GetFeatures( const OclSignature::Association& signature, OclMeta::AssociationVector& vecFeatures )
			{
				if ( ! signature.GetAcceptableTypeName().empty() )
					return;

				GOCL_STL_NS()vector< ::Uml::Uml::Namespace> vecNamespaces = m_diagram.namespaces();
				for( int j = 0; j < vecNamespaces.size(); j++)
				{

					GOCL_STL_NS()vector< ::Uml::Uml::Class> vecClasses = vecNamespaces[j].classes();
					for ( int i = 0 ; i < vecClasses.size() ; i++ ) 
					{
						GOCL_STL_NS()string strClass = vecClasses[ i ].name();
						GOCL_STL_NS()string strNs = ((::Uml::Uml::Namespace)vecClasses[ i ].parent()).name();
						GOCL_STL_NS()string strRole = LowerFirst( strClass );
						GOCL_STL_NS()string strRole_Ns = LowerFirst( strNs ) +"::" + strClass ;
						GOCL_STL_NS()string strSig = signature.GetName();
						bool bHasNamespace = strSig.find( "::" ) != GOCL_STL_NS()string::npos; // true if qualified type, false if local type
						

						if ((bHasNamespace && ( strRole_Ns == signature.GetName())) || ( (!bHasNamespace) && (strRole == signature.GetName()) ) )
						{
							TypeSeq vecType( 1, "ocl::Set" );
							vecType.push_back( strNs + "::" + strClass );
							vecFeatures.push_back( new OclMeta::Association( strRole, "", vecType, new TDataNetworkDerived_Classes( vecClasses[ i ] ), true ) );
						}
					}
				}
			}
	};

//##############################################################################################################################################
//
//	D E R I V E D   O F   udm::Object
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	class TObjectDerived_Parent
		: public OclImplementation::Association
	{
		private :
			::Uml::Uml::CompositionParentRole m_parentRole;
			const ::Uml::Uml::Class m_class;

		public :
			TObjectDerived_Parent( const ::Uml::Uml::CompositionParentRole& parentRole, const ::Uml::Uml::Class& inClass )
				: m_class( inClass ), m_parentRole( parentRole )
			{
			}

			void operator()()
			{
				DECL_UDMOBJECT( objThis, GetThis() );
				if ( ! objThis )
					ThrowException( "Object is null." );
				if ( m_parentRole )
					SetResult( CREATE_UDMOBJECT( GetTypeManager(), Udm::Object ( objThis.__impl()->getParent( m_parentRole ) ) ) ); // Access by Role
				else {
					Udm::Object objParent = objThis.GetParent();	// Access by Class
					if ( ! objParent || ! ::Uml::IsDerivedFrom( objParent.type(), m_class ) )
						objParent = Udm::Object( NULL );
					SetResult( CREATE_UDMOBJECT( GetTypeManager(), objParent ) );
				}
			}
	};

	class TObjectDerived_Children
		: public OclImplementation::Association
	{
		private :
			Udm::Object::CompositionInfo m_info;
			const ::Uml::Uml::Class m_class;
			bool m_bCompound;

		public :
			TObjectDerived_Children( const Udm::Object::CompositionInfo& info, const ::Uml::Uml::Class& inClass, bool bCompound )
				: m_class( inClass ), m_info( info ), m_bCompound( bCompound )
			{
			}

			void operator()()
			{
				DECL_UDMOBJECT( objThis, GetThis() );
				if ( ! objThis )
					ThrowException( "Object is null." );
				set<Udm::Object> setOut;
				if ( m_info.strParentRoleName.empty() )  								// Access by Class
					setOut = objThis.GetChildObjects( m_class );
				else																		// Access by Role
					setOut = objThis.GetChildObjects( m_info, m_class );
				OclMeta::ObjectVector vecOut;
				for ( set<Udm::Object>::iterator it = setOut.begin() ; it != setOut.end() ; it++ )
					vecOut.push_back( CREATE_UDMOBJECT( GetTypeManager(), *it ) );
				if ( m_bCompound )
					SetResult( CREATE_SET( GetTypeManager(), vecOut ) );
				else
					SetResult( ( vecOut.empty() ) ? CREATE_UDMOBJECT( GetTypeManager(), Udm::Object( NULL ) ) : vecOut[ 0 ] );

			}
	};

	class TObjectDerived_Peers
		: public OclImplementation::Association
	{
		private :
			const ::Uml::Uml::AssociationRole m_assocRole;
			const ::Uml::Uml::Class m_class;
			bool m_bCompound;

		public :
			TObjectDerived_Peers( const ::Uml::Uml::AssociationRole& inAssocRole, const ::Uml::Uml::Class& inClass, bool bCompound )
				: m_class( inClass  ), m_assocRole( inAssocRole ), m_bCompound( bCompound )
			{
			}

			void operator()()
			{
				DECL_UDMOBJECT( objThis, GetThis() );
				if ( ! objThis )
					ThrowException( "Object is null." );
				set<Udm::Object> setOut;
				if ( ! m_class ) {
					GOCL_STL_NS()vector<Udm::ObjectImpl*> vecImpls = objThis.__impl()->getAssociation( m_assocRole, Udm::TARGETFROMPEER );
					for ( int i = 0 ; i < vecImpls.size() ; i++ )
						setOut.insert( Udm::Object( vecImpls[ i ] ) );
				}
				else
					setOut = objThis.GetAdjacentObjects( m_class );
				OclMeta::ObjectVector vecOut;
				for ( set<Udm::Object>::iterator it = setOut.begin() ; it != setOut.end() ; it++ )
					vecOut.push_back( CREATE_UDMOBJECT( GetTypeManager(), *it ) );
				if ( m_bCompound )
					SetResult( CREATE_SET( GetTypeManager(), vecOut ) );
				else
					SetResult( ( vecOut.empty() ) ? CREATE_UDMOBJECT( GetTypeManager(), Udm::Object( NULL ) ) : vecOut[ 0 ] );
			}
	};

	class TObjectDerived_AssocClasses
		: public OclImplementation::Association
	{
		private :
			::Uml::Uml::AssociationRole m_assocRole;
			bool m_bCompound;

		public :
			TObjectDerived_AssocClasses( const ::Uml::Uml::AssociationRole& assocRole, bool bCompound )
				: m_assocRole( assocRole ), m_bCompound( bCompound )
			{
			}

			void operator()()
			{
				DECL_UDMOBJECT( objThis, GetThis() );
				if ( ! objThis )
					ThrowException( "Object is null." );
				GOCL_STL_NS()vector<Udm::ObjectImpl*> vecImpls = objThis.__impl()->getAssociation( m_assocRole, Udm::CLASSFROMTARGET );
				OclMeta::ObjectVector vecOut;
				for ( int i = 0 ; i < vecImpls.size() ; i++ )
					vecOut.push_back( CREATE_UDMOBJECT( GetTypeManager(), Udm::Object( vecImpls[ i ] ) ) );
				if ( m_bCompound )
					SetResult( CREATE_SET( GetTypeManager(), vecOut ) );
				else
					SetResult( ( vecOut.empty() ) ? CREATE_UDMOBJECT( GetTypeManager(), Udm::Object( NULL ) ) : vecOut[ 0 ] );
			}
	};

	class TObjectDerived_Targets
		: public OclImplementation::Association
	{
		private :
			::Uml::Uml::AssociationRole m_assocRole;

		public :
			TObjectDerived_Targets( const ::Uml::Uml::AssociationRole& assocRole )
				: m_assocRole( assocRole )
			{
			}

			void operator()()
			{
				DECL_UDMOBJECT( objThis, GetThis() );
				if ( ! objThis )
					ThrowException( "Object is null." );
				GOCL_STL_NS()vector<Udm::ObjectImpl*> vecImpls = objThis.__impl()->getAssociation( m_assocRole, Udm::TARGETFROMCLASS );
				SetResult( CREATE_UDMOBJECT( GetTypeManager(), Udm::Object( vecImpls[ 0 ] ) ) );
			}
	};

	class TObjectDerived_AssociationFactory
		: public OclImplementation::AssociationFactory
	{
		private :
		 	const ::Uml::Uml::Class m_class;

		 public :
		 	TObjectDerived_AssociationFactory( const ::Uml::Uml::Class& inclass )
		 		: m_class( inclass )
		 	{
		 	}

		 	virtual void GetFeatures( const OclSignature::Association& signature, OclMeta::AssociationVector& vecFeatures )
		 	{
		 		GetParents( signature, vecFeatures );
		 		GetChildren( signature, vecFeatures );
		 		GetAssociationEnds( signature, vecFeatures );
		 		GetAssociationClasses( signature, vecFeatures );
		 		GetAssociationEndsFromClasses( signature, vecFeatures );
		 	}

		 private :
		 	void GetParents( const OclSignature::Association& signature, OclMeta::AssociationVector& vecFeatures )
		 	{
		 		if ( ! signature.GetAcceptableTypeName().empty() )
					return;

				GOCL_STL_NS()string strName = signature.GetName();
				set< ::Uml::Uml::Class> setAncestors = ::Uml::AncestorClasses( m_class );
				bool bClassAccessFound = false;
				for ( set< ::Uml::Uml::Class>::iterator itClass =  setAncestors.begin() ; itClass != setAncestors.end() ; itClass++ ) {
					set< ::Uml::Uml::CompositionChildRole> setChildRoles = (*itClass).childRoles();
					for ( set< ::Uml::Uml::CompositionChildRole>::iterator itChild = setChildRoles.begin() ; itChild != setChildRoles.end() ; itChild++ ) {
						::Uml::Uml::CompositionParentRole parentRole = ( (::Uml::Uml::Composition)(*itChild).parent() ).parentRole();
			 			GOCL_STL_NS()string strRole = parentRole.name();
			 			::Uml::Uml::Class parent = parentRole.target();
			 			GOCL_STL_NS()string strClass = parent.name();
						GOCL_STL_NS()string strNs = ((::Uml::Uml::Namespace)parent.parent()).name();
			 			TypeSeq vecType( 1, strNs + "::" + strClass );
			 			if ( ! strRole.empty() && strRole == strName )
			 				vecFeatures.push_back( new OclMeta::Association( strName, "", vecType, new TObjectDerived_Parent( parentRole, parent ), true ) );
			 			else if ( strName == LowerFirst( strClass ) && ! bClassAccessFound && *itClass == m_class ) {
		 					bClassAccessFound = true;
							vecFeatures.push_back( new OclMeta::Association( strName, "", vecType, new TObjectDerived_Parent( ::Uml::Uml::CompositionParentRole( NULL ), parent ), true ) );
		 				}
			 		}
			 	}
		 	}

		 	void GetChildren( const OclSignature::Association& signature, OclMeta::AssociationVector& vecFeatures )
		 	{
		 		if ( ! signature.GetAcceptableTypeName().empty() )
					return;

				GOCL_STL_NS()string strName = signature.GetName();
				set< ::Uml::Uml::CompositionParentRole> setParentRoles = m_class.parentRoles();
				for ( set< ::Uml::Uml::CompositionParentRole>::iterator itParent = setParentRoles.begin() ; itParent != setParentRoles.end() ; itParent++ ) {
					::Uml::Uml::Composition composition = (*itParent).parent();
					::Uml::Uml::CompositionChildRole childRole = composition.childRole();
		 			GOCL_STL_NS()string strRole = childRole.name();
		 			::Uml::Uml::Class child = childRole.target();
		 			GOCL_STL_NS()string strClass = child.name();
					GOCL_STL_NS()string strNs = ((::Uml::Uml::Namespace)child.parent()).name();

					if ( ! strRole.empty() && strRole == strName || strName == LowerFirst( strClass ) ) {
		 				TypeSeq vecType;
		 				if ( childRole.max() > 1 || childRole.max() == -1 )
		 					vecType.push_back( "ocl::Set" );
		 				vecType.push_back( strNs + "::" + strClass );
		 				Udm::Object::CompositionInfo info;
		 				if ( ! strRole.empty() && strRole == strName ) {
		 					info.strParentRoleName = (*itParent).name();
		 					info.strChildRoleName = strRole;
		 				}
		 				vecFeatures.push_back( new OclMeta::Association( strName, "", vecType, new TObjectDerived_Children( info, child, vecType.size() > 1 ), true ) );
		 			}
		 		}
		 	}

		 	void GetAssociationEnds( const OclSignature::Association& signature, OclMeta::AssociationVector& vecFeatures )
		 	{
		 		if ( ! signature.GetAcceptableTypeName().empty() )
					return;

				GOCL_STL_NS()string strName = signature.GetName();
				set< ::Uml::Uml::AssociationRole> setFromRoles = m_class.associationRoles();
				for ( set< ::Uml::Uml::AssociationRole>::iterator itFrom = setFromRoles.begin() ; itFrom != setFromRoles.end() ; itFrom++ ) {
					::Uml::Uml::Association association = (*itFrom).parent();
					set< ::Uml::Uml::AssociationRole> setToRoles = association.roles();
					for ( set< ::Uml::Uml::AssociationRole>::iterator itTo = setToRoles.begin() ; itTo != setToRoles.end() ; itTo++ ) {
						if ( *itTo != *itFrom ) {
							GOCL_STL_NS()string strRole = (*itTo).name();
							::Uml::Uml::Class peer = (*itTo).target();
							GOCL_STL_NS()string strClass = peer.name();
							GOCL_STL_NS()string strNs = ((::Uml::Uml::Namespace)peer.parent()).name();
							if ( ! strRole.empty() && strRole == strName || strRole.empty() && strName == LowerFirst( strClass ) ) {
								TypeSeq vecType;
		 						if ( (*itTo).max() > 1 ||  (*itTo).max() == -1 )
		 							vecType.push_back( "ocl::Set" );
		 						vecType.push_back( strNs + "::" + strClass );
		 						TObjectDerived_Peers* pAssociation = new TObjectDerived_Peers( *itTo,  ( strRole.empty() && strName == LowerFirst( strClass ) ) ? m_class : ::Uml::Uml::Class( NULL ), vecType.size() > 1 );
		 						vecFeatures.push_back( new OclMeta::Association( strName, "", vecType, pAssociation , true ) );
		 					}
		 				}
		 			}
		 		}
		 	}

		 	void GetAssociationClasses( const OclSignature::Association& signature, OclMeta::AssociationVector& vecFeatures )
		 	{
				GOCL_STL_NS()string strName = signature.GetName();
				GOCL_STL_NS()string strAcceptable = signature.GetAcceptableTypeName();

				set< ::Uml::Uml::AssociationRole> setFromRoles = m_class.associationRoles();
				for ( set< ::Uml::Uml::AssociationRole>::iterator itFrom = setFromRoles.begin() ; itFrom != setFromRoles.end() ; itFrom++ ) {
					::Uml::Uml::Association association = (*itFrom).parent();
					::Uml::Uml::Class assocClass = association.assocClass();
					if ( assocClass ) {
						GOCL_STL_NS()string strClass = assocClass.name();
						GOCL_STL_NS()string strNs = ((::Uml::Uml::Namespace)assocClass.parent()).name();
						GOCL_STL_NS()string strRole = (*itFrom).name();
						GOCL_STL_NS()string strClassRole = LowerFirst( strClass );
						if ( strAcceptable.empty() && strClassRole == strName || ! strAcceptable.empty() && ! strRole.empty() && strRole == strName && strAcceptable == strClassRole ) {
							set< ::Uml::Uml::AssociationRole> setToRoles = association.roles();
							TypeSeq vecType;
							set< ::Uml::Uml::AssociationRole>::iterator itTo;
							for (  itTo = setToRoles.begin() ; itTo != setToRoles.end() ; itTo++ ) {
								if ( *itTo != *itFrom ) {
									long lMax = (*itTo).max();
			 						if ( lMax > 1 || lMax == -1 ) {
			 							vecType.push_back( "ocl::Set" );
			 							break;
			 						}
			 					}
		 					}
		 					vecType.push_back( strNs + "::" + strClass );
		 					vecFeatures.push_back( new OclMeta::Association( strName, strAcceptable, vecType, new TObjectDerived_AssocClasses( *itTo, vecType.size() > 1 ), true ) );
		 				}
		 			}
		 		}
		 	}

		 	void GetAssociationEndsFromClasses( const OclSignature::Association& signature, OclMeta::AssociationVector& vecFeatures )
		 	{
		 		if ( ! signature.GetAcceptableTypeName().empty() )
					return;

		 		GOCL_STL_NS()string strName = signature.GetName();
				::Uml::Uml::Association association = m_class.association();
		 		if ( association ) {
					set< ::Uml::Uml::AssociationRole> setRoles = association.roles();
					for ( set< ::Uml::Uml::AssociationRole>::iterator it = setRoles.begin() ; it != setRoles.end() ; it++ ) {
			 			::Uml::Uml::Class target = (*it).target();
			 			GOCL_STL_NS()string strClass = target.name();
						GOCL_STL_NS()string strNs = ((::Uml::Uml::Namespace)target.parent()).name();
			 			GOCL_STL_NS()string strRole = (*it).name();
			 			if ( ! strRole.empty() && strRole == strName || strRole.empty() && strName == LowerFirst( strClass ) ) {
			 				TypeSeq vecType( 1, strNs + "::" + strClass );
			 				vecFeatures.push_back( new OclMeta::Association( strName, "", vecType, new TObjectDerived_Targets( *it ), true ) );
			 			}
			 		}
			 	}
		 	}
	};

	class TObjectDerived_Attribute
		: public OclImplementation::Attribute
	{
		private :
			int 						m_iCompound;
			const ::Uml::Uml::Attribute m_attribute;

		public :
			TObjectDerived_Attribute( const ::Uml::Uml::Attribute& attribute, int iCompound )
				: m_attribute( attribute ), m_iCompound( iCompound )
			{
			}

			void operator()()
			{
				DECL_UDMOBJECT( objThis, GetThis() );
				if ( ! objThis )
					ThrowException( "Object is null." );
				GOCL_STL_NS()string strType = m_attribute.type();
				if ( strType == "ocl::Boolean" || strType == "Boolean" ) {
					if ( m_iCompound == 0 )
						SetResult( CREATE_BOOLEAN( GetTypeManager(), objThis.getBooleanAttr( m_attribute ) ) );
					else {
						GOCL_STL_NS()vector<bool> vec = objThis.getBooleanAttrArr( m_attribute );
						OclMeta::ObjectVector vecOut;
						for ( int i = 0 ; i< vec.size() ; i++ )
							vecOut.push_back( CREATE_BOOLEAN( GetTypeManager(), vec[ i ] ) );
						if ( m_iCompound == 1 )
							SetResult( CREATE_SET( GetTypeManager(), vecOut ) );
						else
							SetResult( CREATE_SEQUENCE( GetTypeManager(), vecOut ) );
					}
				}
				else if ( strType == "ocl::Integer" || strType == "Integer" ) {
					if ( m_iCompound == 0 )
						SetResult( CREATE_INTEGER( GetTypeManager(), objThis.getIntegerAttr( m_attribute ) ) );
					else {
						GOCL_STL_NS()vector<__int64> vec = objThis.getIntegerAttrArr( m_attribute );
						OclMeta::ObjectVector vecOut;
						for ( int i = 0 ; i< vec.size() ; i++ )
							vecOut.push_back( CREATE_INTEGER( GetTypeManager(), vec[ i ] ) );
						if ( m_iCompound == 1 )
							SetResult( CREATE_SET( GetTypeManager(), vecOut ) );
						else
							SetResult( CREATE_SEQUENCE( GetTypeManager(), vecOut ) );
					}
				}
				else if ( strType == "ocl::Real" || strType == "Real" ) {
					if ( m_iCompound == 0 )
						SetResult( CREATE_REAL( GetTypeManager(), objThis.getRealAttr( m_attribute ) ) );
					else {
						GOCL_STL_NS()vector<double> vec = objThis.getRealAttrArr( m_attribute );
						OclMeta::ObjectVector vecOut;
						for ( int i = 0 ; i< vec.size() ; i++ )
							vecOut.push_back( CREATE_REAL( GetTypeManager(), vec[ i ] ) );
						if ( m_iCompound == 1 )
							SetResult( CREATE_SET( GetTypeManager(), vecOut ) );
						else
							SetResult( CREATE_SEQUENCE( GetTypeManager(), vecOut ) );
					}
				}
				else {
					if ( m_iCompound == 0 )
						SetResult( CREATE_STRING( GetTypeManager(), objThis.getStringAttr( m_attribute ) ) );
					else {
						GOCL_STL_NS()vector<GOCL_STL_NS()string> vec = objThis.getStringAttrArr( m_attribute );
						OclMeta::ObjectVector vecOut;
						for ( int i = 0 ; i< vec.size() ; i++ )
							vecOut.push_back( CREATE_STRING( GetTypeManager(), vec[ i ] ) );
						if ( m_iCompound == 1 )
							SetResult( CREATE_SET( GetTypeManager(), vecOut ) );
						else
							SetResult( CREATE_SEQUENCE( GetTypeManager(), vecOut ) );
					}
				}
			}
	};

	class TObjectDerived_AttributeFactory
		: public OclImplementation::AttributeFactory
	{
		private :
		 	const ::Uml::Uml::Class m_class;

		 public :
		 	TObjectDerived_AttributeFactory( const ::Uml::Uml::Class&  classin )
		 		: m_class( classin )
		 	{
		 	}

		 public :
			virtual void GetFeatures( const OclSignature::Attribute& signature, OclMeta::AttributeVector& vecFeatures )
			{
				GOCL_STL_NS()string strName = signature.GetName();

				set< ::Uml::Uml::Attribute> setAttribs = m_class.attributes();
				for ( set< ::Uml::Uml::Attribute>::iterator it = setAttribs.begin() ; it != setAttribs.end() ; it++ ) {
					if ( strName == (GOCL_STL_NS()string) (*it).name() ) {
						TypeSeq vecType;
			 			int iCompound = ( (*it).max() > 1 || (*it).max() == -1 ) ? 1 : 0;
						if ( iCompound ) {
							if ( (bool) (*it).ordered() )
								iCompound = 2;
							vecType.push_back( ( iCompound == 2 ) ? "ocl::Sequence" : "ocl::Set" );
						}
						GOCL_STL_NS()string strType = (*it).type();
						if ( strType == "ocl::Boolean" || strType == "Boolean" )
							vecType.push_back( "ocl::Boolean" );
						else if ( strType == "ocl::Integer" || strType == "Integer" )
							vecType.push_back( "ocl::Integer" );
						else if ( strType == "ocl::Real" || strType == "Real" )
							vecType.push_back( "ocl::Real" );
						else if ( strType == "ocl::String" || strType == "String" )
							vecType.push_back( "ocl::String" );
						else
							continue;
						vecFeatures.push_back( new OclMeta::Attribute( strName, vecType, new TObjectDerived_Attribute( *it, iCompound ), true ) );
					}
				}
			}
	};

	class TObjectDerived_MethodFactory
		: public OclImplementation::MethodFactory
	{
		public :
			virtual void GetFeatures( const OclSignature::Method& signature, OclMeta::MethodVector& vecFeatures )
			{
				GOCL_STL_NS()string strName = signature.GetName();
				int iCount = signature.GetParameterCount();
				TypeSeq vecType;
				OclCommon::FormalParameterVector vecParams;

				if ( ( strName == "isNull" ) && iCount == 0 ) {
					vecType.push_back( "ocl::Boolean" );
					vecFeatures.push_back( new OclMeta::Method( strName, vecParams, vecType, NULL, false ) );
					return;
				}
			}
	};


//##############################################################################################################################################
//
//	G L O B A L   F A C T O R I E S
//
//==============================================================================================================================================
//
//	D E S C R I P T I O N :
//
//##############################################################################################################################################

	TypeFactory::TypeFactory( const ::Uml::Uml::Diagram& diagram )
		: m_diagram( diagram )
	{
	}

	void TypeFactory::GetTypes( const GOCL_STL_NS()string& strName, GOCL_STL_NS()vector<OclMeta::Type*>& vecTypes )
	{
		bool bHasNamespace = strName.find( "::" ) != GOCL_STL_NS()string::npos; // true if qualified type, false if local type

		GetDynamicTypes( strName, vecTypes );				//get the types from UML meta
		if ( ! bHasNamespace && ! vecTypes.empty() )		//if local type, and results not empty - return the results
			return;

		GetPredefinedTypes( strName, vecTypes );			//get the predefined types
		if ( ! bHasNamespace && ! vecTypes.empty() )		//if local type, and resulst not empty - return the results
			return;

		// WARNING :
		// hack.... we have to call the base class' GetTypes, but because of different namespace I could solve this only in that way
		// if the base class has member variables this call may lead to errors as copy constructor does not exist
		( ( OclBasic::TypeFactory ) *this ).GetTypes( strName, vecTypes );	//search & return the OCL types
	}

	void TypeFactory::GetDynamicTypes( const GOCL_STL_NS()string& strName, GOCL_STL_NS()vector<OclMeta::Type*>& vecTypes )
	{
		bool bHasNamespace = strName.find( "::" ) != GOCL_STL_NS()string::npos; // true if qualified type, false if local type

		GOCL_STL_NS()string strNsName, strClassName;

		if (bHasNamespace) 
		{
			strClassName = strName.substr(strName.find("::")+2, GOCL_STL_NS()string::npos);
			strNsName = strName.substr(0, strName.find("::"));
		}
		else
			strClassName = strName;
/*
		GOCL_STL_NS()string strRealName = strName;
		if ( strName.size() > 6 && strName.substr( 0, 6 ) == "meta::" )
			strRealName = strName.substr( 6 );
*/

		GOCL_STL_NS()vector< ::Uml::Uml::Namespace> vecNamespaces = m_diagram.namespaces();
		for ( int j = 0; j < vecNamespaces.size(); j++)
		{
			//if type is qualified, we search it only in the corresponding namespace
			//if type is not qualified, we search it in all namespaces 
			if ( (!bHasNamespace) || ( strNsName == (GOCL_STL_NS()string) vecNamespaces[ j ].name() ) )
			{
				GOCL_STL_NS()vector< ::Uml::Uml::Class> vecClasses = vecNamespaces[j].classes();
				for ( int i = 0 ; i < vecClasses.size() ; i++ ) 
				{
					if ( strClassName == (GOCL_STL_NS()string) vecClasses[ i ].name() ) 
					{
						StringVector vecSuperTypes;
						set< ::Uml::Uml::Class> setBases = vecClasses[ i ].baseTypes();
						for ( set< ::Uml::Uml::Class>::iterator it = setBases.begin(); it != setBases.end() ; it++ )
							vecSuperTypes.push_back( (GOCL_STL_NS()string)((::Uml::Uml::Namespace)it->parent()).name() + "::" + (GOCL_STL_NS()string) (*it).name() );
						if ( setBases.empty() )
							vecSuperTypes.push_back( "udm::Object" );
						::Uml::Uml::Class theClass = vecClasses[ i ];
						vecTypes.push_back( new OclMeta::Type( (GOCL_STL_NS()string)((::Uml::Uml::Namespace)theClass.parent()).name() + "::" + strClassName, vecSuperTypes, new TObjectDerived_AttributeFactory( theClass ), new TObjectDerived_AssociationFactory( theClass ), new TObjectDerived_MethodFactory(), true ) );
					}
				}
			}
		}
	}

	void TypeFactory::GetPredefinedTypes( const GOCL_STL_NS()string& strName, GOCL_STL_NS()vector<OclMeta::Type*>& vecTypes )
	{
		if ( strName == "udm::DataNetwork" || strName == "DataNetwork" ) {
			StringVector vecSupers;
			vecSupers.push_back( "ocl::Any" );
			vecTypes.push_back( new OclMeta::Type( "udm::DataNetwork", vecSupers, new OclImplementation::AttributeFactory(), new TDataNetwork_AssociationFactory( m_diagram ), new OclImplementation::MethodFactory(), true ) );
			return;
		}

		if ( strName == "udm::Object" || strName == "Object" ) {
			StringVector vecSupers;
			vecSupers.push_back( "ocl::Any" );
			vecTypes.push_back( new OclMeta::Type( "udm::Object", vecSupers, new OclImplementation::AttributeFactory(), new OclImplementation::AssociationFactory(), new TObjectDerived_MethodFactory(), true ) );
			return;
		}
	}

}; // namespace UmlOcl
