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

/*
CHANGELOG
=========
	12/06/04	-	endre

					Added
					
					  UDM_DLL void GetChildRoleChain(const Uml::Class & origin, const Uml::Class &what, vector<ChildRoleChain> &chains, ChildRoleChain curr_chain = ChildRoleChain());

					which returns the possible containments paths of class what in class origin, at any level
					

	23/11/04	-	endre
		
					Added getPath to Udm::Object.

	07/11/04	-	endre

			-		Addd two functions, HasTextAttributes and TextAttributes for checking the existence and for getting
					all the text attributes from a class.

	19/09/04	-	endre

			-		Added new function GetAncestorAssociation, which removes the only (if any) Association
					attached to a Class.

    14/07/04	-	endre

			-		Changed SetChildRole, setParentRole to include both role names as key.
					There could be a composition relationship between the same two classes and
					the same rolenames at one end. These two associations could not be differentiated
					by the target classes and one rolename.

	05/24/04	-	endre

			-		splitted SetGenericRole in 3 functions, SetChildRole, SetParentRole and SetAssocRole.
					
	05/06/04	-	endre

			-		added SetDiagram(), SetClass(), SetGenericRole() classes. They search and set a target diagram/class/role
					out from an existing diagram based on names and role targets.

	04/13/04	-	endre

		Added SafeTypeContainer::IsSafeType(const Uml::Class &a)
		to indicate if a Uml::Class was obtained through SafeTypeContainer.


	24/02/04	-	endre
		
		Extended InitDiagram() with version information
*/


#ifndef MOBIES_UMLEXT_H
#define MOBIES_UMLEXT_H

#ifndef MOBIES_UML_H
#include "Uml.h"
#endif

namespace Uml
{
// Get the other end of two-legged Uml classes 
	UDM_DLL const Uml::AssociationRole theOther(const Uml::AssociationRole &role);
	UDM_DLL const Uml::CompositionChildRole theOther(const Uml::CompositionParentRole &role);
	UDM_DLL const Uml::CompositionParentRole theOther(const Uml::CompositionChildRole &role);

// find an assoc.Class by name
	UDM_DLL Uml::Class assocClassByName(const Uml::Namespace &d, const string &name);

// find a class by name
	UDM_DLL Uml::Class classByName(const Uml::Diagram &d, const string &ns_name,const string &name );
	
// find a namespace by name
	UDM_DLL Uml::Namespace namespaceByName(const Uml::Diagram &d, const string &name);
// find a class by name
	UDM_DLL Uml::Class classByName(const Uml::Namespace &d, const string &name);
// find association by name
	UDM_DLL Uml::Association associationByName(const Uml::Namespace &d, const string &name);
//find composition by name
	UDM_DLL Uml::Composition compositionByName(const Uml::Namespace &d, const string &name);
// Get all the classes specified as ancestors, including self
	UDM_DLL set<Uml::Class> AncestorClasses(const Uml::Class &c);
// Get all the classes specified as descendants, including self
	UDM_DLL set<Uml::Class> DescendantClasses(const Uml::Class &c);
// Get classes directly specified for this class as parents  (both ancestors and descendants are ignored)
	UDM_DLL set<Uml::Class> ContainerClasses(const Uml::Class &c);
// Get classes directly specified for this class as children  (both ancestors and descendants are ignored)
	UDM_DLL set<Uml::Class> ContainedClasses(const Uml::Class &c);
//for association classes, there is only one attached association,
//but it can be either directly attached or inherited from a base association class
//returns NULL if the class does not have an Association attached
	UDM_DLL Uml::Association GetAncestorAssociation(const Uml::Class &c);

// Get classes that are ancestors of all the classes in a set
	UDM_DLL set<Uml::Class> CommonAncestorClasses(const set<Uml::Class> &cs);

// Get classes this object or its ancestors specify as parents (ancestors in child are extracted, decendants of parents are ignored)
	UDM_DLL set<Uml::Class> AncestorContainerClasses(const Uml::Class &c);
// Get classes this object or its ancestors specify as children (ancestors in parent are extracted, decendants of children are ignored)
	UDM_DLL set<Uml::Class> AncestorContainedClasses(const Uml::Class &c);
// Get classes this object can contain (ancestors in parent and descendants in children are extracted)
	UDM_DLL set<Uml::Class> AncestorContainedDescendantClasses(const Uml::Class &c);
// Get the target namespaces of children having the parent in this namespace
	UDM_DLL set<Uml::Namespace> TargetNSForAllContainerClasses(const Uml::Namespace &ns);

	// All the other ends of associations (ancestors are ignored)
	UDM_DLL set<Uml::AssociationRole> AssociationTargetRoles(const Uml::Class &c);
	// All the other ends of associations this class can have (including those defined in ancestors)
	UDM_DLL set<Uml::AssociationRole> AncestorAssociationTargetRoles(const Uml::Class &c);

	// All the other ends of associations this class can have (including those defined in ancestors)
	UDM_DLL set<Uml::AssociationRole> AncestorCrossAssociationTargetRoles(const Uml::Class &c, const Uml::Namespace & ns);

	// All local ends of associations this class can have (including those defined in ancestors)
	UDM_DLL set<Uml::AssociationRole> AncestorAssociationRoles(const Uml::Class &c);

	// All local ends of associations this class can have (including those defined in ancestors)
	UDM_DLL set<Uml::AssociationRole> AncestorCrossAssociationRoles(const Uml::Class &c, const Uml::Namespace& cross_ns);

	// returns all the Text Attributes for class C
	UDM_DLL set<Uml::Attribute> TextAttributes(const Uml::Class &c);

	//returns true if class c has any Text Attribute (should be faster:)
	UDM_DLL bool HasTextAttributes(const Uml::Class &c);


// All the other ends of of compositions defined for this class as child (ancestors are ignored)
	UDM_DLL set<Uml::CompositionParentRole> CompositionPeerParentRoles(const Uml::Class &c);
// All the parent ends of compositions this class can participate in (including those defined for ancestors)
	UDM_DLL set<Uml::CompositionParentRole> AncestorCompositionPeerParentRoles(const Uml::Class &c);
// The namespaces of all the other ends of the compositions defined for this class as child; the set does not include the namespace of this class
	UDM_DLL set<Uml::Namespace> OtherCompositionPeerParentRolesNamespaces(const Uml::Class &c);

// All the child ends of compositions defined for this class as parent (ancestors are ignored)
	UDM_DLL set<Uml::CompositionChildRole> CompositionPeerChildRoles(const Uml::Class &c);
// All the child ends of compositions this class can participate in (including those defined for ancestors)
	UDM_DLL set<Uml::CompositionChildRole> AncestorCompositionPeerChildRoles(const Uml::Class &c);
// The namespaces of all the child ends of all compositions defined for all classes from this namespace that are parent
	UDM_DLL set<Uml::Namespace> CompositionPeerChildNamespaces(const Uml::Namespace &ns);

// Returns true if the parent and the child of this composition are in different namespaces
	UDM_DLL bool IsCrossNSComposition(const Uml::Composition &c);
	
// All attributes this class can have (including those defined in ancestors)
	UDM_DLL set<Uml::Attribute> AncestorAttributes(const Uml::Class &c);

// find the single way a class can be contained by another, return NULL none or if multiple roles are found
	UDM_DLL Uml::Composition matchChildToParent(Uml::Class c, Uml::Class p);

// returns true if derived = base
	UDM_DLL bool IsDerivedFrom(const Uml::Class &derived, const Uml::Class &base);
	UDM_DLL bool IsAssocClass(const Uml::Class &cl);
	UDM_DLL bool IsAssocClass(const Uml::Association &ass);

// The namespaces of all the base classes having derived classes in this namespace
	UDM_DLL set<Uml::Namespace> BaseTypesNamespaces(const Uml::Namespace &ns);

	UDM_DLL string MakeRoleName(const Uml::GenericRole &r);
	UDM_DLL string MakeShortRoleName(const Uml::GenericRole &r);

//returns true if childrole's target has more than one non-abstract derivate, including itself
	UDM_DLL bool HasChildRoleMultipleTargets(const Uml::CompositionChildRole & ccr);

	typedef vector<Uml::CompositionChildRole> ChildRoleChain;
	//returns the possible containments paths of class what in class origin, at any level
	UDM_DLL void GetChildRoleChain(const Uml::Class & origin, const Uml::Class &what, vector<ChildRoleChain> &chains, ChildRoleChain curr_chain = ChildRoleChain());

	UDM_DLL Uml::Namespace GetTheOnlyNamespace(const Uml::Diagram & dgr);

// Safe type mechanism

	class SafeTypeContainer
	{
		/*
			safe-type mechanism for StaticObject's
			their m_type variable is a reference
			so there need to be a way 
			which would guarantee that the referenced Uml::Class objects
			are not freed until th referees

		*/
		typedef Udm::ObjectImpl::uniqueId_type uniquedId_type;
		
		typedef map<uniquedId_type, const Uml::Class *>			type_map_t;
		typedef pair<uniquedId_type const, const Uml::Class *>	type_map_t_item;
		typedef pair<type_map_t::iterator, bool>				type_map_t_ires;


		typedef map<const Uml::Class *, long>					ref_map_t;
		typedef pair<const Uml::Class * const, long>			ref_map_t_item;
		typedef pair<ref_map_t::iterator, bool>			ref_map_t_ires;

		
		static type_map_t type_map;				//this will hold a uniqueID->Uml::Class * mapping
		static ref_map_t ref_map;				//this will hold the references for the types created in here


		
public:
		
		UDM_DLL static const Uml::Class & GetSafeType(const Uml::Class &a) 
		{
			//check if we already have a type equivalent with this
			type_map_t::const_iterator i = type_map.find(a.uniqueId());
			if (i == type_map.end())
			{

				//we don't haven an equivalent type, so we create one
				//I believe this must be referenced, since we create an object from a pointer
				//make sure we don't mix the references to ObjectImpl's and references to Uml::ClassS ;-)


				const Uml::Class * new_type = new Uml::Class(a.__impl()->clone());
				if (!new_type) throw udm_exception(" new() failed in GetSafeType()");
				
				//insert in the type_map with it's unique ID as key,
				//so we can find it next time
				type_map_t_item map_item(a.uniqueId(), new_type);
				type_map_t_ires m_ins_res = type_map.insert(map_item);
				if (!m_ins_res.second) throw udm_exception("Could not insert new type in type_map!");

				//insert in reference map
				//with 1 as initial reference coutn value
				ref_map_t_item ref_item(new_type, 1);
				ref_map_t_ires ref_res = ref_map.insert(ref_item);
				if (!ref_res.second) throw udm_exception("Cound not insert new item in references map!");

			
				//return a reference
				return *new_type;
			}
			else
			{
				const Uml::Class * found = (*i).second;
				
				ref_map_t::iterator ref_i = ref_map.find(found);
				if (ref_i == ref_map.end())
					throw udm_exception("Pointer found in st_map was not found in references map!");
				(*ref_i).second++;
				
				
		
				return *found;
			}
		};

		UDM_DLL static void RemoveSafeType(const Uml::Class &a )
		{
			//since we will invoke this in every static Object  destructor.
			// it might happen the type of a StaticObect was not obtained
			// through this class
	

			//we first check our reference map
			//if it's found there, it means that this type was obtaind thru this class

			const Uml::Class * pointer = &a;
			ref_map_t::iterator ref_i = ref_map.find(pointer);
			if (ref_i != ref_map.end())
			{
				(*ref_i).second--;			//decrement the counter

				if ((*ref_i).second == 0)
				{
					
					//now we have to find it in the other map to and delete from both
					type_map_t::iterator i = type_map.find(a.uniqueId());
					if (i == type_map.end())
					{
						//we can not drop exception here 
						//because it might be called on main()-s '}' 
						//sow we just complain about this
						cout << " SafeTypeContainer: Fatal error, corrupt maps. Object found in reference map was not found in type map. Likely to crash from now on... " << endl;
					}
					
					ref_map.erase(ref_i);
					type_map.erase(i);
					delete pointer;
				}
			

			};
		}

		UDM_DLL static bool IsSafeType(const Uml::Class &a)
		{
			const Uml::Class * pointer = &a;
			ref_map_t::iterator ref_i = ref_map.find(pointer);
			return  (ref_i != ref_map.end());
			
		};


	};


// --------------------------- Construction

UDM_DLL Uml::Diagram CreateDiagram();
UDM_DLL Uml::Namespace CreateNamespace();
UDM_DLL Uml::Class CreateClass();
UDM_DLL Uml::Attribute CreateAttribute();
UDM_DLL Uml::Association CreateAssociation();
UDM_DLL Uml::AssociationRole CreateAssociationRole();
UDM_DLL Uml::Composition CreateComposition();
UDM_DLL Uml::CompositionParentRole CreateCompositionParentRole();
UDM_DLL Uml::CompositionChildRole CreateCompositionChildRole();
UDM_DLL Uml::Constraint CreateConstraint();
UDM_DLL Uml::ConstraintDefinition CreateConstraintDefinition();

// ---------------------------- Static Meta Initialization

UDM_DLL void InitDiagram(const Uml::Diagram &obj, const char *name, const char * version = "1.00");
UDM_DLL void InitNamespace(const Uml::Namespace &obj, const Uml::Diagram &parent, const char *name);
UDM_DLL void InitClass(const Uml::Class &obj, const Uml::Namespace &parent, const char *name, bool isAbstract, const char *stereo = NULL, const char * from = NULL);
UDM_DLL void InitAttribute(const Uml::Attribute &obj, const Uml::Class &parent, const char *name, const char *type, bool np, bool reg, int min, int max, const bool ordered, const string& visibility, const vector<string> & defval = vector<string>());
UDM_DLL void InitAssociation(const Uml::Association &obj, const Uml::Namespace &parent, const char *name);
UDM_DLL void InitAssociationClass(const Uml::Association &aobj, const Uml::Class &cobj);
UDM_DLL void InitAssociationRole(const Uml::AssociationRole &obj, const Uml::Association &parent, 
								 const char *name, bool navigable, bool primary, long min, long max, const Uml::Class &target);
UDM_DLL void InitComposition(const Uml::Composition &obj, const Uml::Namespace &parent, const char *name);
UDM_DLL void InitCompositionParentRole(const Uml::CompositionParentRole &obj, 
									   const Uml::Composition &parent, const char *name, bool navigable, const Uml::Class &target);
UDM_DLL void InitCompositionChildRole(const Uml::CompositionChildRole &obj,
									  const Uml::Composition &parent, const char *name, bool navigable, long min, long max, const Uml::Class &target);

UDM_DLL void InitConstraint(const Uml::Constraint &obj, const Uml::Class &parent, const char * name, const char * description, const char * expression);
UDM_DLL void InitConstraintDefinition(const Uml::ConstraintDefinition &obj, const Uml::Class &parent, const char * name, const char * stereotype, const char * parameterList, const char * expression, const char * returnType);
UDM_DLL void AddInheritance(const Uml::Class &baseType, const Uml::Class &subType);

	

// --------------------------- Static Corba Initialization 

Uml::Diagram CreateCORBADiagram();
Uml::Class CreateCORBAClass();
Uml::Attribute CreateCORBAAttribute();
Uml::Association CreateCORBAAssociation();
Uml::AssociationRole CreateCORBAAssociationRole();
Uml::Composition CreateCORBAComposition();
Uml::CompositionParentRole CreateCORBACompositionParentRole();
Uml::CompositionChildRole CreateCORBACompositionChildRole();

void InitCORBADiagram(const Uml::Diagram &obj, const char *name, const char * version = "1.00");
void InitCORBAClass(const Uml::Class &obj, const Uml::Diagram &parent, const char *name, bool isAbstract, const char *stereo = NULL);
void InitCORBAAttribute(const Uml::Attribute &obj, const Uml::Class &parent, const char *name, const char *type, bool np, int min, int max, const bool ordered, const string& visibility, const vector<string> & defval = vector<string>());
void InitCORBAAssociation(const Uml::Association &obj, const Uml::Diagram &parent, const char *name);
void InitCORBAAssociationClass(const Uml::Association &aobj, const Uml::Class &cobj);
void InitCORBAAssociationRole(const Uml::AssociationRole &obj, const Uml::Association &parent, const char *name, bool navigable, bool primary, long min, long max, const Uml::Class &target);
void InitCORBAComposition(const Uml::Composition &obj, const Uml::Diagram &parent, const char *name);
void InitCORBACompositionParentRole(const Uml::CompositionParentRole &obj, const Uml::Composition &parent, const char *name, bool navigable, const Uml::Class &target);
void InitCORBACompositionChildRole(const Uml::CompositionChildRole &obj,const Uml::Composition &parent, const char *name, bool navigable, long min, long max, const Uml::Class &target);
void AddCORBAInheritance(const Uml::Class &baseType, const Uml::Class &subType);


// ---------------------------- Dynamic Meta Initialization
// used to set the static API member variables to 

	UDM_DLL void SetNamespace(Uml::Namespace &what, const Uml::Diagram &what_dgr, const char *target_name);
	UDM_DLL void SetClass(Uml::Class &what, const Uml::Namespace &what_ns, const char *target_name);
	//UDM_DLL void SetClass(Uml::Class &what, Uml::Diagram &what_dgr, const char *target_name);
	UDM_DLL void SetAttribute(Uml::Attribute &what, Uml::Class &what_class,  const char *target_name);

	UDM_DLL void SetChildRole(Uml::CompositionChildRole &what, Uml::Class &what_target_class, Uml::Class &what_theo_target_class, const char *role_name, const char * orole_name);
	UDM_DLL void SetParentRole(Uml::CompositionParentRole &what, Uml::Class &what_target_class, Uml::Class &what_theo_target_class, const char *role_name, const char * orole_name);
	UDM_DLL void SetAssocRole(Uml::AssociationRole &what, Uml::Class &what_target_class, Uml::Class &what_theo_target_class, const char *target_name);
}

#endif//MOBIES_UMLEXT_H

