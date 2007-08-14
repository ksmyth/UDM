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
CHANGELOG:

	12/20/04	-	endre

			Finally splitted this file:
				CS Generators:	UdmCS.cpp
				.H Generator:	UdmH.cpp
		.CPP Generator(normal):	UdmCpp.cpp	(generates code which assumes that meta-meta objects are already created)
		.CPP Generator(meta):	UdmMetaCpp.cpp	(generates Uml.cpp)

		This file is kept because of the various comments.
		Some utility functions are also left here.
		Probably this is the last changelog information entered here.


	12/01/04	-	endre
			
			Minor vc7x porting issues.

	11/07/04	-	endre

			Removed the constraint which denied for a class to have both text attributes and children
	10/24/04	-	endre

			slight modification because of introducing a new type "Text", which is the
			same as "String", but it gets persisted differently in DOM backend.
			updated the code generator and CheckClass(), which now checks that a class either is a parent class
			or has text attributes

	14/07/04	-	endre

			Changed the code generator to include both rolenames when generating the SetChildRole, SetParentRole
			calls.

	06/20/04	-	endre

			Fixed Code generator bug in case of multiple inheritence, when having an immediate and an indirect
			inheritence relationship between two classes.


	06/16/04	-	endre
			
			Changed the signature of GenerateCORBACPP to also include macro and cross-diagram arguments

	06/15/04	-	endre

			Fixed bug UDM-7(http://escher.isis.vanderbilt.edu/JIRA/browse/UDM-7)
			Removed DTD/XSD generator functions and using thise defined in DTDGen.h
	06/15/04	-	endre
		
			Fixed bug UDM-8( http://escher.isis.vanderbilt.edu/JIRA/browse/UDM-8)

	06/04/04	-	endre


			Workaround for the previous compiler bug. Typedef removed from the code generator.

	05/24/04	-	endre

			- unfortunattly compiler failes in generated code if the Udm::Object typedef is not present
	05/24/04	-	endre

			- redesigned the new Initilize(const Uml::Diagram&) function generator such that unique rolenames are no more
			required.
			- removed the typedef namespace::Object Udm::Object, thus there can be a class named 'Object' in custom
			namespaces without conflicting with Udm::Object
			- when using a macro definition, Udm.exe also generates an export file which make easier the DLL export/import
			of the generated classes


	05/06/04	-	endre

			- added Initialize(const Uml::Diagram& dgr) function which can initialize the static meta pointers in the API
			from an existing UML diagram
	04/22/04	-	endre

			added _sorted()  templated versions for functions returning instances of instantiated template classes:
				CrossAssocAttr, AssocAttr, AClassCrossAssocAttr, 
				AClassAssocAttr, ChildrenAttr, DerivedAttr, InstantiatedAttr
			The *_sorted(const Pred &) versions accept a templae class parameter which is supposed to order the resulting set<CLASS>


	04/03/04	-	endre

			changed the generator to generate virtual destructor for Visitor classes
	03/15/04	-	endre
			
			changed the internal dom attributes from using literal strings to constants
			defined in UdmDom namespace

	24/02/04	-	endre
			
			  changed the DTD/XSD generators to generate version information as processing instructions
	02/02/04	-	endre

			Changed the new CPP generator - splitted  the Initialize() function 
			in three smaller functions because it created problems with MSVC' limitations.
		
	15/01/04	-	endre
			Changed XSD Schema generator's root element selection condition: All classes, 
			which have no container classes but self are allowed to be root elements.

	12/12/03	-	endre

			Changed the cross class - cross diagram delimitator character from
			"_" to string "_cross_ph_". This allows '_' characters in classnames.

	01/17/02	-	endre
		
			Added constraints that prevent the generation
			of invalid code because of using reserved or duplicate
			attirubute/role names

	11/05/02	-	endre

			DTD generator changed; subelements 
	10/25/02	-	endre

			Added support for array defvalues and new attribute notation
	07/31/02	-	endre
		
		  C#, CORBA  code generators added

	06/20/02	-	endre
			
			changed .h code generator to support array attributes in case 
			of non-persistent attributes as well

	06/17/02	-	endre
			
			changed code generators to support attribute arrays:
				.h:	 when max is not equal to 1 or 0 for an attribute,
					the generated functions returns a AttrArr type attribute object,
					which contains a vector
				.dtd: in case of boolean vectors, the DTD attrib definition is not
					  <true;false> but CDATA. (Parsing is done by the DOM backend)

						
	04/22/02	-	endre
			
			  changed the attribute generation code to generate the __child_as 
			  composition child role attribute in the DTD as an enum of all possible childroles
			  instead of an open NMTOKENS. As requested by Jonathan.

  */

#include "Uml.h"
#include "UmlExt.h"
#include <map>
#include "Udm.h"

// assign a name to a role
// if name is assigned, use that name
// otherwise, if navigable, get the peer class name and append _assoc, _parent, _child or _children 
//									(for _parent, prepend ChildRole name, if applicable)
//			  if not navigable, name is arolexxx, prolexxx, or crolexxx, where xxx is the uniqueid

using namespace Uml;
	
void CheckClass(const ::Uml::Class & cl)
{
	set<string> unique_names;
	//reserved names
	unique_names.insert("parent");
	unique_names.insert("meta");
	unique_names.insert("archetype");
	unique_names.insert("derived");
	unique_names.insert("instances");
	unique_names.insert("desycnhed_atts");
	unique_names.insert((string)cl.name());
	unsigned int i;

	//attributes
	set< ::Uml::Attribute> attrs = ::Uml::AncestorAttributes(cl);
	set< ::Uml::Attribute>::iterator attrs_i = attrs.begin();
	while (attrs_i != attrs.end())
	{
		::Uml::Attribute att = *attrs_i++;
	
		string att_type = att.type();

		string att_name = att.name();

		i = unique_names.size();
		unique_names.insert(att_name);
		if (i == unique_names.size()) goto err_att;
		
		i = unique_names.size();
		unique_names.insert(string("meta_") + att_name);
		if (i == unique_names.size()) goto err_att;

		continue;
err_att:
		throw udm_exception("Reserved or duplicate attribute name: " + att_name);
	}



	//associationroles
	set< ::Uml::AssociationRole> assocs = cl.associationRoles();
	set< ::Uml::AssociationRole>::iterator assocs_i = assocs.begin();
	while (assocs_i != assocs.end())
	{
		
		::Uml::AssociationRole ar = *assocs_i++;
		string aname(MakeRoleName(::Uml::theOther(ar)));
		
		i = unique_names.size();
		unique_names.insert(aname);
		if (i == unique_names.size()) goto err_ar;
		
		i = unique_names.size();
		unique_names.insert(string("meta_") + aname);
		if (i == unique_names.size()) goto err_ar;

		continue;
err_ar:
		throw udm_exception("Reserved or duplicate  association role name: " + aname);

	}
	

	
	//compositionparentroles
	//check meta_child declarations
	set< ::Uml::CompositionParentRole> cprs = cl.parentRoles();
	
	set< ::Uml::CompositionParentRole>::iterator cprs_i = cprs.begin();
	set< ::Uml::Class> kinds;

	while (cprs_i != cprs.end())
	{
		::Uml::CompositionParentRole cpr = *cprs_i++;
		string aname(::Uml::MakeRoleName(::Uml::theOther(cpr)));

		::Uml::Class thischildkind = (::Uml::Class)::Uml::theOther(cpr).target();
		kinds.insert(thischildkind);
		string oname(thischildkind.name());

		i = unique_names.size();
		unique_names.insert(string("meta_") + aname);
		if (i == unique_names.size()) goto err_cpr;

		
		continue;
err_cpr:
		throw udm_exception("Reserved or duplicate child role name: " + aname);
	}

	//check _kind_children stuff
	set< ::Uml::Class>::iterator kinds_i = kinds.begin();
	while (kinds_i != kinds.end())
	{
		i = unique_names.size();
		string kindname = (*kinds_i).name();
		string ns_name = ((::Uml::Namespace)kinds_i->parent()).name();
		kinds_i ++;

		unique_names.insert(ns_name + "_" + kindname + "_kind_children");
		if (i == unique_names.size()) goto err_kinds;
		continue;
err_kinds:
		throw udm_exception("Reserved or duplicate children kind name: " + kindname);
	}

	//check parent, meta_parent declarations 

	set< ::Uml::CompositionChildRole> ccrs = cl.childRoles();
	set< ::Uml::CompositionChildRole>::iterator ccrs_i = ccrs.begin();
	while (cprs_i != cprs.end())
	{
		::Uml::CompositionChildRole ccr = *ccrs_i++;
		string aname(::Uml::MakeRoleName(::Uml::theOther(ccr)));

		i = unique_names.size();
		unique_names.insert(aname );
		if (i == unique_names.size()) goto err_ccr;

		i = unique_names.size();
		unique_names.insert(string("meta_") + aname );
		if (i == unique_names.size()) goto err_ccr;

		continue;
err_ccr:
		throw udm_exception("Reserved or duplicate parent role name: " + aname);
	}


};

void CheckDiagram(const ::Uml::Diagram & diagram)
{
	//check the UML diagram against duplicate & reserved role, attribute & classnames
	set< ::Uml::Namespace> nses = diagram.namespaces();
	set<string> unique_ns_names;
	for (set< ::Uml::Namespace>::iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
	{
		::Uml::Namespace ns = *nses_i;
		string nsname = ns.name();

		set< ::Uml::Class> cls = ns.classes();
		set< ::Uml::Class>::iterator cls_i = cls.begin();

		unsigned int i = unique_ns_names.size();
		unique_ns_names.insert(nsname);
		if (i == unique_ns_names.size())
			throw udm_exception(string("Duplicate namespace name found: ") + (string)nses_i->name());

		set<string> unique_names;
		while (cls_i != cls.end())
		{
			::Uml::Class cl = *cls_i++;
			unsigned int i = unique_names.size();
			unique_names.insert(cl.name());
			if (i == unique_names.size())
				throw udm_exception(string("Duplicate class name found: ") + (string)cl.name());

			CheckClass(cl);
		}
	}
};
