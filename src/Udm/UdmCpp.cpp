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

  01/11/06 - endre
   - setup associations roles to cross diagram in InitializeDgr(dgr) and InitializeNS(ns)

  11/23/05 - endre
   - remove redundant call to SingleCPPNamespace from UmlClassCPPName

	05/17/05	-	kalmar
              changed in genertion
              "Uml::SetClass" to
              ::Uml::SetClass
	12/20/04	-	endre

		took the functions from UdmCppH.cpp
		Also separated the huge generator function into a bunch of smaller functions to increase readability

*/

#include "Uml.h"
#include "UmlExt.h"
#include <time.h>
#include <fstream>
#include <map>
#include "Udm.h"

using namespace Uml;
typedef vector< ::Uml::Class> UmlClasses;
typedef pair<set<int>, set<int> > UmlCompositionInitFuncInfo;

string UmlClassCPPName(const ::Uml::Class &cl)
{
	return "::" + cl.getPath2("::");
}

/*
	Declarations in the namespace
*/
void GenerateCPPDeclareMetaClasses(const set< ::Uml::Class> & classes, ostream & output)
{
	//::Uml::Class A::meta;
	set< ::Uml::Class>::const_iterator c;
	for(c = classes.begin(); c != classes.end(); c++ )
	{
		::Uml::Class cl = *c;
		output << "\t\t::Uml::Class " << cl.name() << "::meta;" << endl;
	}
};
void GenerateCPPDeclareAttributes(const set< ::Uml::Class> & classes, ostream & output)
{
	set< ::Uml::Class>::const_iterator c;
	//	::Uml::::Uml::Attribute A::meta_a;
	for(c = classes.begin(); c != classes.end(); c++ )	
	{
		::Uml::Class cl = *c;
		//::Uml::Class tempcl(::Uml::ClassByName(tempdiagram, cl.name()));
		set< ::Uml::Attribute> attributes = cl.attributes();
		for( set< ::Uml::Attribute>::iterator i = attributes.begin(); i != attributes.end(); i++) 
		{
			output << "\t\t::Uml::Attribute " << cl.name() << "::meta_" << (*i).name() << ";" << endl;
		}
	}
};

void DeclareAssociationRoles(const ::Uml::Class &cl, const set< ::Uml::AssociationRole> &assocs, ostream &output)
{
	for( set< ::Uml::AssociationRole>::const_iterator i = assocs.begin(); i != assocs.end(); i++) 
	{
		::Uml::Association pp = (*i).parent();
		::Uml::Class aclass = pp.assocClass();
		string aname(MakeRoleName(::Uml::theOther(*i)));
		if(!aclass)
			output << "\t\t::Uml::AssociationRole " << cl.name() << "::meta_" << aname << ";" << endl;
		else 
			output << "\t\t::Uml::AssociationRole " << cl.name() << "::meta_" << aname << ", " << cl.name() << "::meta_" << aname << "_rev;" << endl;
	}
}

void DeclareAssociationRolesFromAssoc(const ::Uml::Class &cl, const ::Uml::Association &assoc, ostream &output)
{
	if(assoc)
	{
		set< ::Uml::AssociationRole> assocs = assoc.roles();
		for( set< ::Uml::AssociationRole>::iterator i = assocs.begin(); i != assocs.end(); i++) 
		{
			string aname(MakeRoleName(*i));
			if(aname.size()) 
				output << "\t\t::Uml::AssociationRole " << cl.name() << "::meta_" << aname << "_end_;" << endl;
		}
	}
}

void GenerateCPPDeclareAssociationRoles(const set< ::Uml::Class> &classes, const ::Uml::Diagram &cross_dgr, ostream & output, bool isCrossDgr)
{
//declarations for associationroles
	//	::Uml::AssociationRole A::meta_dst;
	set< ::Uml::Class>::const_iterator c;
	for(c = classes.begin(); c != classes.end(); c++ ) 
	{
		::Uml::Class cl = *c;

		DeclareAssociationRoles(cl, cl.associationRoles(), output);

		/*
			Here is printed the decalaration of the cross-association roles
		*/
		//if (cross_dgr &&(cross_dgr != dgr) )
		if (isCrossDgr)
		{
			//--//::Uml::Class cross_cl = ::Uml::ClassByName(cross_dgr, cl.name());
			::Uml::Class cross_cl = ::Uml::GetClassFromCrossDgr(cross_dgr, cl);
			if(cross_cl)
				DeclareAssociationRoles(cl, cross_cl.associationRoles(), output);
		};

		DeclareAssociationRolesFromAssoc(cl, cl.association(), output);
		if (isCrossDgr)
		//if (cross_dgr &&(cross_dgr != dgr) )
		{
			//--//::Uml::Class cross_cl = ::Uml::ClassByName(cross_dgr, cl.name());
			::Uml::Class cross_cl = ::Uml::GetClassFromCrossDgr(cross_dgr, cl);
			if(cross_cl)
				DeclareAssociationRolesFromAssoc(cl, cross_cl.association(), output);
		};
	};//end for cycle for declaration for associationRoles
};

void GenerateCPPDeclareCompositionRoles(const set< ::Uml::Class> &classes, ostream& output)
{
	set< ::Uml::Class>::const_iterator c;
	
//	::Uml::CompositionParentRole A::meta_parent;
	for(c = classes.begin(); c != classes.end(); c++ ) 
	{
		::Uml::Class cl = *c;
		set< ::Uml::CompositionChildRole> children = cl.childRoles();
		for( set< ::Uml::CompositionChildRole>::iterator i = children.begin(); i != children.end(); i++) {
			string aname(MakeRoleName(::Uml::theOther(*i)));
			output << "\t\t::Uml::CompositionParentRole " << cl.name() << "::meta_" << aname << ";" << endl;
		}
	}
//	::Uml::CompositionChildRole D::meta_as;
	for(c = classes.begin(); c != classes.end(); c++ ) 
	{
		::Uml::Class cl = *c;
		set< ::Uml::CompositionParentRole> children = cl.parentRoles();
		for( set< ::Uml::CompositionParentRole>::iterator i = children.begin(); i != children.end(); i++) {
			string aname(MakeRoleName(::Uml::theOther(*i)));
			output << "\t\t::Uml::CompositionChildRole " << cl.name() << "::meta_" << aname << ";" << endl;
		}
	}
};

void GenerateCPPDeclareConstraints(const set< ::Uml::Class> &classes, ostream & output)
{
	set< ::Uml::Class>::const_iterator c;
	
//  ::Uml::Constraint D::meta_constraint
	for(c = classes.begin(); c != classes.end(); c++ ) 
	{
		::Uml::Class cl = *c;
		set< ::Uml::Constraint> constraints = cl.constraints();
		for( set< ::Uml::Constraint>::iterator i = constraints.begin(); i != constraints.end(); i++) 
			output << "\t\t::Uml::Constraint " << cl.name() << "::meta_" << i->name() << ";" << endl;
	}

//	::Uml::ConstraintDefinition D::meta_constraint_definition
	for(c = classes.begin(); c != classes.end(); c++ ) 
	{
		::Uml::Class cl = *c;
		set< ::Uml::ConstraintDefinition> definitions = cl.definitions();
		for( set< ::Uml::ConstraintDefinition>::iterator i = definitions.begin(); i != definitions.end(); i++) 
			output << "\t\t::Uml::ConstraintDefinition " << cl.name() << "::meta_" << i->name() << ";" << endl;
	}
};

/*

	Generators of functions, outside Initialize()
*/
void GenerateCPPCreatesFunction(const set< ::Uml::Class> &classes, const string &meta_name, ostream & output)
{
	set< ::Uml::Class>::const_iterator c;
	
//void Create()
// {

	output << "\t\tvoid Creates()" << endl << "\t\t{" << endl;
		
//	A::meta = Uml::CreateClass();
	for(c = classes.begin(); c != classes.end(); c++ )
	{
		::Uml::Class cl = *c;
		output << "\t\t\t" << cl.name() << "::meta = ::Uml::Class::Create(" << meta_name << ");" << endl;
	}

//	A::meta_a = Uml::CreateAttribute();
	for(c = classes.begin(); c != classes.end(); c++ )	
	{
		::Uml::Class cl = *c;
		
		set< ::Uml::Attribute> attributes = cl.attributes();
		for( set< ::Uml::Attribute>::iterator i = attributes.begin(); i != attributes.end(); i++) 
		{
			output << "\t\t\t" << cl.name() << "::meta_" << (*i).name() << " = ::Uml::Attribute::Create(" << cl.name()<<"::meta);" << endl;
		}

			//constraints
		set< ::Uml::Constraint> constraints = cl.constraints();
		for (set< ::Uml::Constraint>::iterator j = constraints.begin(); j != constraints.end(); j++)
		{
			output << "\t\t\t" << cl.name() << "::meta_" << j->name() << " = ::Uml::Constraint::Create(" << cl.name() << "::meta);" << endl;
		}

			//constraintdefinitions
		set< ::Uml::ConstraintDefinition> definitions = cl.definitions();
		for (set< ::Uml::ConstraintDefinition>::iterator k = definitions.begin(); k != definitions.end(); k++)
		{
			output << "\t\t\t" << cl.name() << "::meta_" << k->name() << " = ::Uml::ConstraintDefinition::Create(" << cl.name() << "::meta);" << endl;
		}
	}
	output << "\t\t}" << endl;
};

void GenerateCPPCreates2Function(const set< ::Uml::Class> &classes, bool is_dgr, ostream & output)
{

	string parent_name;
	if (is_dgr) {
		output << "\t\tvoid Creates2(const ::Uml::Diagram &dgr)" << endl << "\t\t{" << endl;
		parent_name = "dgr";
	} else {
		output << "\t\tvoid Creates2(const ::Uml::Namespace &ns)" << endl << "\t\t{" << endl;
		parent_name = "ns";
	}
		
	for (set< ::Uml::Class>::const_iterator c = classes.begin(); c != classes.end(); c++)
	{
		::Uml::Class cl = *c;
//		::Uml::SetClass(class_name::meta, parent_name, "class_name");
		output << "\t\t\t::Uml::SetClass(" << cl.name() << "::meta, " << parent_name << ", \"" << cl.name() << "\");" << endl;

		//attributes
		set< ::Uml::Attribute> attributes = cl.attributes();
		for( set< ::Uml::Attribute>::iterator cla_i = attributes.begin(); cla_i != attributes.end(); cla_i++) 
		{
			::Uml::Attribute a = *cla_i;
			output << "\t\t\t::Uml::SetAttribute(" << cl.name() <<"::meta_" << a.name() << ", " << cl.name() << "::meta, \"" << a.name() << "\");" <<endl;
		}
	}
	output << "\t\t}" << endl;
};

void GenerateCPPInitClassesAttributes(const set< ::Uml::Class> & classes, const ::Uml::Diagram & cross_dgr, ostream & output, bool isCrossDgr)
{
	//void InitAttributes()
// {
	output << "\t\tvoid InitClassesAttributes()" << endl << "\t\t{" << endl;
	set< ::Uml::Class>::const_iterator c;
	for(c = classes.begin(); c != classes.end(); c++ )
	{
		::Uml::Class cl = *c;
		string ster;
		if(((string)cl.stereotype()).length()) ster = string(", \"")+(string)cl.stereotype()+"\"";
		output << "\t\t\t" << cl.name() << "::meta.name() = \"" << cl.name() << "\";" <<endl;
		output << "\t\t\t" << cl.name() << "::meta.isAbstract() = " << (cl.isAbstract() ? "true" : "false") << ";" << endl;
		
		if (!ster.empty()) 
			output << "\t\t\t" << cl.name() << "::meta.stereotype() = \"" << cl.stereotype() << "\";" <<endl;

		string from = cl.from();
		if (!from.empty())
			output << "\t\t\t" << cl.name() << "::meta.from() = \"" << cl.from() << "\";" <<endl;
	}

	output << "\t\t\t" << endl;

//		Uml::InitAttribute(A::meta_a, A::meta, "a", "String");
	for(c = classes.begin(); c != classes.end(); c++ )	
	{
		::Uml::Class cl = *c;
		set< ::Uml::Attribute> attributes = cl.attributes();
		for( set< ::Uml::Attribute>::iterator i = attributes.begin(); i != attributes.end(); i++) 
		{
			if (i->defvalue())
			{
				vector<string> dva = i->defvalue();
				output << "\t\t\tvector<string> " << cl.name() << "_" << (*i).name() << "_dva;" <<endl;
				vector<string>::const_iterator dva_ci = dva.begin();
				while (dva_ci != dva.end())
				{
					output << "\t\t\t" << cl.name() << "_" <<(*i).name() << "_dva.push_back(\"" << *dva_ci++ << "\");" << endl; 
				};
			}
			output << "\t\t\t" << cl.name() << "::meta_" << (*i).name() << ".name() = \"" << (*i).name() << "\";" << endl;
			output << "\t\t\t" << cl.name() << "::meta_" << (*i).name() << ".type() = \"" << (*i).type() << "\";" << endl;
			output << "\t\t\t" << cl.name() << "::meta_" << (*i).name() << ".min() = " << (*i).min() << ";" << endl;
			output << "\t\t\t" << cl.name() << "::meta_" << (*i).name() << ".max() = " << (*i).max() << ";" << endl;
			output << "\t\t\t" << cl.name() << "::meta_" << (*i).name() << ".nonpersistent() = " << ((*i).nonpersistent() ? "true" : "false") << ";" << endl;
			output << "\t\t\t" << cl.name() << "::meta_" << (*i).name() << ".registry() = " << ((*i).registry() ? "true" : "false") << ";" << endl;
			output << "\t\t\t" << cl.name() << "::meta_" << (*i).name() << ".ordered() = " << ((*i).ordered() ? "true" : "false") << ";" << endl;
			output << "\t\t\t" << cl.name() << "::meta_" << (*i).name() << ".visibility() = \"" << (*i).visibility() << "\";" << endl;
			if (i->defvalue())
				output << "\t\t\t" << cl.name() << "::meta_" << (*i).name() << ".defvalue() = " << cl.name() << "_" <<(*i).name() << "_dva;" << endl;
			else
				output << "\t\t\t" << cl.name() << "::meta_" << (*i).name() << ".defvalue() = vector<string>();" << endl;
		}

		set< ::Uml::Constraint> constraints= cl.constraints();
		for( set< ::Uml::Constraint>::iterator j = constraints.begin(); j != constraints.end(); j++) 
		{
			output << "\t\t\t" << cl.name() << "::meta_" << j->name() << ".name() = \"" << j->name() << "\";" << endl;
			output << "\t\t\t" << cl.name() << "::meta_" << j->name() << ".description() = \"" << j->description() << "\";" << endl;
			output << "\t\t\t" << cl.name() << "::meta_" << j->name() << ".expression() = \"" << j->expression() << "\";" << endl;
		}

		set< ::Uml::ConstraintDefinition> defs = cl.definitions();
		for( set< ::Uml::ConstraintDefinition>::iterator k = defs.begin(); k != defs.end(); k++) 
		{
			output << "\t\t\t" << cl.name() << "::meta_" << k->name() << ".name() = \"" << k->name() << "\";" << endl;
			output << "\t\t\t" << cl.name() << "::meta_" << k->name() << ".stereotype() = \"" << k->stereotype() << "\";" << endl;
			output << "\t\t\t" << cl.name() << "::meta_" << k->name() << ".parameterList() = \"" << k->parameterList() << "\";" << endl;
			output << "\t\t\t" << cl.name() << "::meta_" << k->name() << ".expression() = \"" << k->expression() << "\";" << endl;
			output << "\t\t\t" << cl.name() << "::meta_" << k->name() << ".returnType() = \"" << k->returnType() << "\";" << endl;
			
		}

		if (isCrossDgr)
		//if (cross_dgr &&(cross_dgr != diagram))
		{
			::Uml::Class cross_cl;
			::Uml::Association ass;
			if (cross_dgr)
			{
				//--//cross_cl = ::Uml::ClassByName(cross_dgr, cl.name());
				cross_cl = ::Uml::GetClassFromCrossDgr(cross_dgr, cl);
			}
			if (cross_cl)
				ass = cross_cl.association();
			if (ass)
			{
				set< ::Uml::AssociationRole> asrs = ass.roles();
				set< ::Uml::AssociationRole>::iterator asrs_i = asrs.begin();
				while (asrs_i != asrs.end())
				{
					output << " \t\t\t" << cl.name() << "::meta_" << asrs_i->name() << "_end_ = " 
					       << UmlClassCPPName((::Uml::Class)((::Uml::theOther(*asrs_i)).target())) << "::meta_" << asrs_i->name() << ";" <<endl;
					asrs_i++;
				}
			};
		}
	}
	output << "\t\t\t" << endl;
	output << "\t\t}" << endl;
};

void GenerateCPPCreatesNamespacesFunction(const set< ::Uml::Namespace> &nses, const string &meta_name, ostream & output)
{
	set< ::Uml::Namespace>::const_iterator ns;
	
	output << "\t\tvoid CreatesNamespaces()" << endl << "\t\t{" << endl;
		
	for(ns = nses.begin(); ns != nses.end(); ns++ )
	{
		output << "\t\t\t" << ns->name() << "::meta = ::Uml::Namespace::Create(" << meta_name << ");" << endl;
	}

	output << "\t\t}" << endl;
};

void GenerateCPPCreatesNamespaces2Function(const set< ::Uml::Namespace> &nses, bool is_dgr, ostream & output)
{
	string parent_name;
	if (is_dgr) {
		output << "\t\tvoid CreatesNamespaces2(const ::Uml::Diagram &dgr)" << endl << "\t\t{" << endl;
		parent_name = "dgr";
	} else {
		output << "\t\tvoid CreatesNamespaces2(const ::Uml::Namespace &ns)" << endl << "\t\t{" << endl;
		parent_name = "ns";
	}

	for (set< ::Uml::Namespace>::const_iterator ns = nses.begin(); ns != nses.end(); ns++ )
	{
		output << "\t\t\t" << "::Uml::SetNamespace(" << ns->name() << "::meta, " << parent_name << ", \"" << ns->name() << "\");" << endl;
	}

	output << "\t\t}" << endl;
};

void GenerateCPPInitNamespacesFunction(const set< ::Uml::Namespace> &nses, ostream & output)
{
	set< ::Uml::Namespace>::const_iterator ns;
	
	output << "\t\tvoid InitNamespaces()" << endl << "\t\t{" << endl;
		
	for(ns = nses.begin(); ns != nses.end(); ns++ )
	{
		output << "\t\t\t" << ns->name() << "::meta.name() = \"" << ns->name() <<"\";" << endl;
		output << "\t\t\t" << ns->name() << "::InitializeNS();" << endl;
	}

	output << "\t\t}" << endl;
};

void GenerateCompositionInit(const ::Uml::Composition &c, const string &meta_name, ostream &output, int funct_no)
{
	output << "\t\tvoid InitComposition" << funct_no << "()" << endl << "\t\t{" << endl;
	output << "\t\t\t::Uml::Composition comp = ::Uml::Composition::Create(" << meta_name << ");" << endl;

	if (!((string)c.name()).empty())output << "\t\t\tcomp.name() =\"" << c.name() << "\";" <<endl;
	output << "\t\t\tcomp.nonpersistent() =" << (c.nonpersistent() ? "true" : "false") << ";" << endl;

	::Uml::CompositionParentRole zzp = c.parentRole();
	::Uml::CompositionChildRole zzc = c.childRole();
	string aname(MakeRoleName(zzp));
	output << "\t\t\t" << UmlClassCPPName((::Uml::Class)zzc.target()) << "::meta_" << aname <<" = ::Uml::CompositionParentRole::Create(comp);" << endl;
	output << "\t\t\t" << UmlClassCPPName((::Uml::Class)zzc.target()) << "::meta_" << aname <<".name() = \"" << aname << "\";" << endl;
	output << "\t\t\t" << UmlClassCPPName((::Uml::Class)zzc.target()) << "::meta_" << aname <<".isNavigable() = " << (zzp.isNavigable() ? "true;" : "false;") << endl;
	output << "\t\t\t" << UmlClassCPPName((::Uml::Class)zzc.target()) << "::meta_" << aname <<".target() = " << UmlClassCPPName((::Uml::Class)zzp.target()) << "::meta;" << endl;

	string cname(MakeRoleName(zzc));
	output << "\t\t\t" << UmlClassCPPName((::Uml::Class)zzp.target()) << "::meta_" << cname << " = ::Uml::CompositionChildRole::Create(comp);" << endl;

	output << "\t\t\t" << UmlClassCPPName((::Uml::Class)zzp.target()) << "::meta_" << cname << ".name() = \"" << MakeShortRoleName(zzc) << "\";" << endl;
	output << "\t\t\t" << UmlClassCPPName((::Uml::Class)zzp.target()) << "::meta_" << cname << ".min() = " << zzc.min() << ";"<< endl;
	output << "\t\t\t" << UmlClassCPPName((::Uml::Class)zzp.target()) << "::meta_" << cname << ".max() = " << zzc.max() << ";"<< endl;
	output << "\t\t\t" << UmlClassCPPName((::Uml::Class)zzp.target()) << "::meta_" << cname << ".isNavigable() = " << (zzc.isNavigable() ? "true;" : "false;") << endl;
	output << "\t\t\t" << UmlClassCPPName((::Uml::Class)zzp.target()) << "::meta_" << cname << ".target() = " << UmlClassCPPName((::Uml::Class)zzc.target()) << "::meta;" << endl;

	output << "\t\t}" << endl;
};

void GenerateAssociationInit(const ::Uml::Association &a,  const string &meta_name, ostream &output, int funct_no)
{
	output << "\t\tvoid InitAssociation" << funct_no << "()" << endl << "\t\t{" << endl;

	set< ::Uml::AssociationRole> ar = a.roles();
	ASSERT(ar.size() == 2);
	
	output << "\t\t\t::Uml::Association ass = ::Uml::Association::Create(" << meta_name << ");" << endl;

	::Uml::Class aclass = a.assocClass();
	if (!((string)a.name()).empty())output << "\t\t\tass.name() = \"" << a.name() << "\";" <<endl;
	if(aclass) 
	{
		output << "\t\t\tass.assocClass() = " << UmlClassCPPName(aclass) << "::meta;" << endl;
	}

	set< ::Uml::AssociationRole> roles = a.roles();
	for( set< ::Uml::AssociationRole>::iterator i = roles.begin(); i != roles.end(); i++) 
	{
		::Uml::AssociationRole zz	= ::Uml::theOther(*i);
		string aname(MakeRoleName(zz));
		::Uml::Class cl = i->target();
		
		output << "\t\t\t" << UmlClassCPPName(cl) << "::meta_" << aname << " = ::Uml::AssociationRole::Create(ass);" <<endl;
		output << "\t\t\t" << UmlClassCPPName(cl) << "::meta_" << aname << ".name() = \"" << aname << "\";" <<endl;
		output << "\t\t\t" << UmlClassCPPName(cl) << "::meta_" << aname << ".min() = " << zz.min() << ";" <<endl;
		output << "\t\t\t" << UmlClassCPPName(cl) << "::meta_" << aname << ".max() = " << zz.max() << ";" <<endl;
		output << "\t\t\t" << UmlClassCPPName(cl) << "::meta_" << aname << ".isNavigable() = " << (zz.isNavigable() ? "true":"false") << ";" <<endl;
		output << "\t\t\t" << UmlClassCPPName(cl) << "::meta_" << aname << ".isPrimary() = " << (zz.isPrimary() ? "true":"false") << ";" <<endl;
		output << "\t\t\t" << UmlClassCPPName(cl) << "::meta_" << aname << ".target() = " << UmlClassCPPName((::Uml::Class)zz.target()) << "::meta;" <<endl;

		::Uml::Class aclass = a.assocClass();
		if(aclass) 
		{
			::Uml::Class cl2 = zz.target();
			output << "\t\t\t" << UmlClassCPPName(aclass) << "::meta_" << aname << "_end_ = " <<
							UmlClassCPPName(cl2) << "::meta_" << MakeRoleName(*i) << "_rev = " << 
							UmlClassCPPName(cl) << "::meta_" << aname << ";" << endl;
		}
	}
	
	
	output << "\t\t};" << endl;

}

int GenerateCPPAssociationInitFunctions(const set< ::Uml::Association> & associations, const string &meta_name, ostream &output)
{
	int ass_inits = 0;
	set< ::Uml::Association>::const_iterator a;
	for(a = associations.begin(); a != associations.end(); a++ )	
		GenerateAssociationInit(*a, meta_name, output, ass_inits++);
	return ass_inits;	
};

UmlCompositionInitFuncInfo GenerateCPPCompositionInitFunctions(const set< ::Uml::Composition> & comps, const string &meta_name, ostream &output)
{
	UmlCompositionInitFuncInfo comp_inits;
	int comp_init_index = 0;
	set< ::Uml::Composition>::const_iterator c;
	for(c = comps.begin(); c != comps.end(); c++ ) {
		GenerateCompositionInit(*c, meta_name, output, comp_init_index);
		if (IsCrossNSComposition(*c)) {
			comp_inits.second.insert(comp_init_index);
		} else {
			comp_inits.first.insert(comp_init_index);
		}
		comp_init_index++;
	}

	return comp_inits;
}

/*
	Functions which build the Initalize() function
*/
void GenerateCPPCrossObjectInits(const set< ::Uml::Class> &classes, const ::Uml::Diagram & cross_dgr, ostream & output, bool isCrossDgr)
{
	if (cross_dgr && isCrossDgr)
	//if (cross_dgr &&(cross_dgr != diagram))
	{
		//		M2::meta_src = CL::M2::meta_src;		
		set< ::Uml::Class>::const_iterator c;
		for(c = classes.begin(); c != classes.end(); c++ )	
		{
			::Uml::Class cl = *c;
			::Uml::Class cross_cl = ::Uml::GetClassFromCrossDgr(cross_dgr, cl);
			if (cross_cl)
			{
				set< ::Uml::AssociationRole> ar = cross_cl.associationRoles();
				set< ::Uml::AssociationRole>::iterator ar_i = ar.begin();
				while (ar_i != ar.end())
				{
					string cross_cl_meta = UmlClassCPPName(cross_cl) + "::meta_" + (string) ::Uml::theOther((*ar_i)).name();
					output << "\t\t\t" << "if (" << cross_cl_meta << ")" << endl;
					output << "\t\t\t\t" << cl.name() << "::meta_"<<::Uml::theOther((*ar_i)).name() << 
					  " = " << cross_cl_meta << ";" << endl;
					output << "\t\t\telse" << endl;
					output << "\t\t\t\t" << "throw udm_exception(\"'" << cross_cl_meta << "' is NULL!\");" << endl;

					::Uml::AssociationRole zz	= ::Uml::theOther(*ar_i);

					::Uml::Association ass = ar_i->parent();
					::Uml::Class a_class = ass.assocClass();
					
					if(a_class) 
					{
						::Uml::Class cl2 = zz.target();
						string cross_cl2_meta = UmlClassCPPName(cl2) + "::meta_" + (string) ar_i->name();
						
						output << "\t\t\t" << "if (" << cross_cl2_meta << ")" << endl;
						output << "\t\t\t\t" << cl.name() << "::meta_"<<::Uml::theOther((*ar_i)).name() << 
						"_rev = " << cross_cl2_meta << ";" << endl;
						output << "\t\t\telse" << endl;
						output << "\t\t\t\t" << "throw udm_exception(\"'" << cross_cl2_meta << "' is NULL!\");" << endl;

					}
					ar_i++;
				}
			}
		}
	}
};

void GenerateCPPInitializeInheritence(const set< ::Uml::Class> &classes, ostream & output, bool cross)
{
	if (cross)
		output << "\t\tvoid InitCrossNSInheritence()" << endl << "\t\t{" << endl;
	else
		output << "\t\tvoid InitInheritence()" << endl << "\t\t{" << endl;

	set< ::Uml::Class>::const_iterator c;
	for(c = classes.begin(); c != classes.end(); c++ ) 
	{
		::Uml::Class cl = *c;
		::Uml::Namespace ns = cl.parent_ns();
		set< ::Uml::Class> st = cl.subTypes();
		for( set< ::Uml::Class>::iterator i = st.begin(); i != st.end(); i++)
		{
			if ((!cross && (::Uml::Namespace)i->parent_ns() == ns) ||
			    (cross && (::Uml::Namespace)i->parent_ns() != ns))
				output << "\t\t\t" << cl.name() << "::meta.subTypes() +=  " << UmlClassCPPName(*i) << "::meta;" << endl;
		}
	}	
	output << "\t\t}" << endl;
};

void GenerateCPPInitializeCrossNSCompositions(const UmlCompositionInitFuncInfo &comp_inits, ostream & output)
{
	output << "\t\tvoid InitCrossNSCompositions()" << endl << "\t\t{" << endl;

	for (set<int>::const_iterator comp_inits_i = comp_inits.second.begin(); comp_inits_i != comp_inits.second.end(); comp_inits_i++) {
		output << "\t\t\tInitComposition" << *comp_inits_i << "();" << endl;
	}

	output << "\t\t}" << endl;
};

void GenerateCPPStaticClass(const ::Uml::Diagram &diagram, ostream & output)
{
	output << "\tstatic struct _regClass" << endl;
	output << "\t{" << endl;
	output << "\t\t_regClass()" << endl;
	output << "\t\t{" << endl;
	output << "\t\t\tUdm::MetaDepository::StoreDiagram(\"" << diagram.name() <<"\", diagram);" << endl;
	output << "\t\t};" << endl;
	output << "\t\t~_regClass()" << endl;

	output << "\t\t{" << endl;
	output <<"\t\t\tUdm::MetaDepository::RemoveDiagram(\"" << diagram.name() << "\");" << endl;
	output <<"\t\t};" <<endl;
	output <<"\t} __regUnUsed;" << endl << endl;

};

void GenerateCPPInitialize(const ::Uml::Diagram &dgr, const ::Uml::Diagram & cross_dgr, ostream & output, const string& hname, int ass_inits, const UmlCompositionInitFuncInfo &comp_inits, bool isCrossDgr)
{
	output << "\t\tvoid InitializeDgr()" << endl
	       << "\t\t{" << endl; //begin of InitializeDgr()
	output << "\t\t\tCreates();" << endl;
	output << "\t\t\tInitClassesAttributes();" << endl;
		
	output << "\t\t\tCreatesNamespaces();" << endl;
	output << "\t\t\tInitNamespaces();" << endl;

	//call the InitAssociation functions

	for (int ass_inits_i = 0; ass_inits_i < ass_inits; ass_inits_i++) output << "\t\t\tInitAssociation" << ass_inits_i << "();" << endl;
			
	//call the InitComposition calls (only those that initialize local namespace compositions)

	for (set<int>::const_iterator comp_inits_i = comp_inits.first.begin(); comp_inits_i != comp_inits.first.end(); comp_inits_i++) {
		output << "\t\t\tInitComposition" << *comp_inits_i << "();" << endl;
	}

	//call the initializers for association roles created in the cross diagrams
	GenerateCPPCrossObjectInits(dgr.classes(), cross_dgr, output, isCrossDgr);

	//call the initializer for inheritence in the same namespace
	output << "\t\t\tInitInheritence();" << endl;


	output << "\t\t}" << endl;	//end of InitializeDgr()
};

void GenerateCPPInitialize(const ::Uml::Namespace &ns, const ::Uml::Diagram & cross_dgr, ostream & output, const string& hname, int ass_inits, const UmlCompositionInitFuncInfo &comp_inits, bool isCrossDgr)
{
	output << "\t\tvoid InitializeNS()" << endl << "\t\t{" << endl; //begin of InitializeNS()
	output << "\t\t\tCreates();" << endl;
	output << "\t\t\tInitClassesAttributes();" << endl;
		
	output << "\t\t\tCreatesNamespaces();" << endl;
	output << "\t\t\tInitNamespaces();" << endl;

	//call the InitAssociation functions

	for (int ass_inits_i = 0; ass_inits_i < ass_inits; ass_inits_i++) output << "\t\t\tInitAssociation" << ass_inits_i << "();" << endl;
			
	//call the InitComposition calls (only those that initialize local namespace compositions)

	for (set<int>::const_iterator comp_inits_i = comp_inits.first.begin(); comp_inits_i != comp_inits.first.end(); comp_inits_i++) {
		output << "\t\t\tInitComposition" << *comp_inits_i << "();" << endl;
	}

	//call the initializers for association roles created in the cross diagrams
	GenerateCPPCrossObjectInits(ns.classes(), cross_dgr, output, isCrossDgr);

	//call the initializer for inheritence in the same namespace
	output << "\t\t\tInitInheritence();" << endl;


	output << "\t\t\t" << endl << "\t\t}" << endl;	//end of InitializeNS()

};

/*
	Function building the alternate InitializeNS(const ::Uml::Namespace &ns) function
*/

void GenerateCPPInitializeDgrSetupMeta(const ::Uml::Diagram & dgr, ostream & output)
{
	output << "\t\tvoid InitializeDgrSetupMeta(const ::Uml::Diagram & dgr)" << endl
	       << "\t\t{" << endl;
	output << "\t\t\tCreates2(dgr);" << endl;
	output << "\t\t\tCreatesNamespaces2(dgr);" << endl;

	set< ::Uml::Namespace> nses = dgr.namespaces();
	for (set< ::Uml::Namespace>::const_iterator ns_i = nses.begin(); ns_i != nses.end(); ns_i++) {
		output << "\t\t\t" << ns_i->name() << "::InitializeNSSetupMeta(" << ns_i->name() << "::meta);" << endl;
	}

	output << "\t\t}" << endl;
}

void GenerateCPPInitializeNSSetupMeta(const ::Uml::Namespace & ns, ostream & output)
{
	output << "\t\tvoid InitializeNSSetupMeta(const ::Uml::Namespace & ns)" << endl
	       << "\t\t{" << endl;
	output << "\t\t\tCreates2(ns);" << endl;
	output << "\t\t\tCreatesNamespaces2(ns);" << endl;

	set< ::Uml::Namespace> nses = ns.namespaces();
	for (set< ::Uml::Namespace>::const_iterator ns_i = nses.begin(); ns_i != nses.end(); ns_i++) {
		output << "\t\t\t" << ns_i->name() << "::InitializeNSSetupMeta(" << ns_i->name() << "::meta);" << endl;
	}

	output << "\t\t}" << endl;
}

void GenerateCPPInitializeContainer(const set< ::Uml::Class> & classes, const set< ::Uml::Namespace> & nses, const ::Uml::Diagram &cross_dgr, bool isCrossDgr, bool is_dgr, ostream & output)
{
	if (is_dgr)
		output << "\t\tvoid InitializeDgr2()" << endl << "\t\t{" << endl;
	else
		output << "\t\tvoid InitializeNS2()" << endl << "\t\t{" << endl;

	set< ::Uml::Class>::const_iterator c;

	output << "\t\t\t" << "//composition child roles " << endl;
	for (c = classes.begin(); c != classes.end(); c++)
	{
	
		::Uml::Class cl = *c;

		//composition parent roles
		set< ::Uml::CompositionChildRole> ccrs = cl.childRoles();
		for (set< ::Uml::CompositionChildRole>::iterator ccrs_i = ccrs.begin(); ccrs_i != ccrs.end(); ccrs_i ++)
		{
			::Uml::CompositionChildRole ccr = *ccrs_i;
			string rolename = ::Uml::MakeRoleName(::Uml::theOther(ccr));
			::Uml::Class theot = (::Uml::Class)::Uml::theOther(ccr).target();
			output << "\t\t\t::Uml::SetParentRole(" << cl.name() <<"::meta_" << rolename << ", " << cl.name() << "::meta, " << UmlClassCPPName(theot) << "::meta, \"" << ccr.name() << "\", \"" << ::Uml::theOther(ccr).name() << "\");" <<endl;

		};

	};
	output << endl;
	
	output << "\t\t\t" << "// composition parentroles " << endl;
	for (c = classes.begin(); c != classes.end(); c++)
	{
		::Uml::Class cl = *c;

		//composition child roles
		set< ::Uml::CompositionParentRole> cprs = cl.parentRoles();
		for (set< ::Uml::CompositionParentRole>::iterator cprs_i = cprs.begin(); cprs_i != cprs.end(); cprs_i ++)
		{
			::Uml::CompositionParentRole cpr = *cprs_i;
			string rolename = ::Uml::MakeRoleName(::Uml::theOther(cpr));
			::Uml::Class theot = (::Uml::Class)::Uml::theOther(cpr).target();
			output << "\t\t\t::Uml::SetChildRole(" << cl.name() <<"::meta_" << rolename << ", " << cl.name() << "::meta, " << UmlClassCPPName(theot) << "::meta, \"" << cpr.name() << "\", \"" << ::Uml::theOther(cpr).name() << "\");" <<endl;

		};
	};
	output << endl;
	
	output << "\t\t\t" << "// Association roles " << endl;
	for (c = classes.begin(); c != classes.end(); c++)
	{
		::Uml::Class cl = *c;

		//association roles
		set< ::Uml::AssociationRole> ars = cl.associationRoles();
		for (set< ::Uml::AssociationRole>::iterator ars_i = ars.begin(); ars_i != ars.end(); ars_i ++)
		{
			::Uml::AssociationRole ar = *ars_i;
			string rolename = ::Uml::MakeRoleName(::Uml::theOther(ar));
			::Uml::Class theot = (::Uml::Class)::Uml::theOther(ar).target();

			output << "\t\t\t::Uml::SetAssocRole(" << cl.name() <<"::meta_" << rolename << ", " << cl.name() << "::meta, " << UmlClassCPPName(theot) << "::meta, \"" << ar.name() << "\");" <<endl;

			::Uml::Association as = ar.parent();
			::Uml::Class aclass = as.assocClass();
			if (aclass)
			{
				string revrolename = ::Uml::MakeRoleName(ar) + "_rev";
				//set the _rev -s
				output << "\t\t\t" << UmlClassCPPName(theot) << "::meta_" << revrolename <<" = " << cl.name() << "::meta_" << rolename <<";" << endl;
			}
		};
	}
	for (c = classes.begin(); c != classes.end(); c++)
	{
		::Uml::Class cl = *c;

		::Uml::Association as = cl.association();
		if (as)
		{
			set< ::Uml::AssociationRole> ars = as.roles();
			for (set< ::Uml::AssociationRole>::iterator ars_i = ars.begin();ars_i != ars.end(); ars_i++)
			{
				::Uml::AssociationRole ar = *ars_i;
				output << "\t\t\t" << cl.name() << "::meta_" << ::Uml::MakeRoleName(ar) << "_end_ = " << UmlClassCPPName((::Uml::Class)::Uml::theOther(ar).target()) << "::meta_" <<::Uml::MakeRoleName(ar) << ";" << endl;

			};
		};
		//_end_ association roles
	};
	output << endl;

	output << "\t\t\t" << "// namespaces" << endl;
	for (set< ::Uml::Namespace>::const_iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
	{
		::Uml::Namespace ns = *nses_i;
		output << "\t\t\t" << ns.name() << "::InitializeNS2();" << endl;
	}

	//call the initializers for association roles created in the cross diagrams
	GenerateCPPCrossObjectInits(classes, cross_dgr, output, isCrossDgr);

	output << "\t\t\t" << endl << "\t\t}" << endl; //end of InitializeNS(const ::Uml::Namespace & ns); || InitializeDgr(const ::Uml::Diagram & dgr)
};

void GenerateCPPPreamble(const ::Uml::Diagram &diagram, const ::Uml::Diagram &cross_dgr, bool isCrossDgr, const string &h_fname, const string &fname, ostream &output)
{
	output << "// cpp(meta datanetwork format) source file " << fname << ".cpp generated from diagram " << (string)diagram.name() << endl;
	output << "// generated on " << GetTime().c_str() << endl << endl;
	output << "#include \""<< h_fname << ".h\"" <<endl;
	output << "#include \"UmlExt.h\"" <<endl << endl; 
	output << "#include \"UdmStatic.h\"" << endl<<endl; 

	if (isCrossDgr)
	{
		output << "// cross-package metainformation header file" << endl;
		output << "#include \"" << cross_dgr.name() << ".h\"" << endl << endl; 
	}
}

void GenerateCPPDiagram(const ::Uml::Diagram &diagram, const ::Uml::Diagram &cross_dgr, bool isCrossDgr, const string &fname, ostream &output, int source_unit)
{
	string hname = NameToFilename(diagram.name());

	GenerateCPPDeclareMetaClasses(diagram.classes(), output);
	GenerateCPPDeclareAttributes(diagram.classes(), output);
	GenerateCPPDeclareAssociationRoles(diagram.classes(), cross_dgr, output, isCrossDgr);
	GenerateCPPDeclareCompositionRoles(diagram.classes(), output);
	GenerateCPPDeclareConstraints(diagram.classes(), output);
	GenerateCPPCreatesFunction(diagram.classes(), "umldiagram", output);
	GenerateCPPInitClassesAttributes(diagram.classes(), cross_dgr, output, isCrossDgr);

	GenerateCPPCreatesNamespacesFunction(diagram.namespaces(), "umldiagram", output);
	GenerateCPPInitNamespacesFunction(diagram.namespaces(), output);

	int ass_inits = GenerateCPPAssociationInitFunctions(diagram.associations(), "umldiagram", output);

	UmlCompositionInitFuncInfo comps_inits = GenerateCPPCompositionInitFunctions(diagram.compositions(), "umldiagram", output);
	GenerateCPPInitializeCrossNSCompositions(comps_inits, output);

	//generate inheritence initializers
	GenerateCPPInitializeInheritence(diagram.classes(), output, false); // in same namespace
	GenerateCPPInitializeInheritence(diagram.classes(), output, true); // across namespaces

	//generate Initialize() function
	GenerateCPPInitialize(diagram, cross_dgr, output, hname, ass_inits, comps_inits, isCrossDgr);


	// initialize from another diagram
	output << endl << "\t\t// initialize from another diagram" << endl;
	GenerateCPPCreates2Function(diagram.classes(), true, output);
	GenerateCPPCreatesNamespaces2Function(diagram.namespaces(), true, output);
	GenerateCPPInitializeDgrSetupMeta(diagram, output);
	GenerateCPPInitializeContainer(diagram.classes(), diagram.namespaces(), cross_dgr, isCrossDgr, true, output);

	output << endl;
}

void GenerateCPPNamespace(const ::Uml::Namespace &ns, const ::Uml::Diagram &cross_dgr, bool isCrossDgr, const string &fname, ostream &output, int source_unit)
{
	::Uml::Diagram diagram = ::Uml::GetDiagram(ns);
	string hname = NameToFilename(diagram.name());
	string ns_fname = fname + "_" + NameToFilename(ns.getPath2("_", false));
	bool single_cpp_namespace = SingleCPPNamespace(diagram);

	if (source_unit == CPP_SOURCE_UNIT_NAMESPACE)
	{
		GenerateCPPPreamble(diagram, cross_dgr, isCrossDgr, fname, ns_fname, output);
		output << "namespace " << hname << " {" << endl << endl;
	}

	if (!single_cpp_namespace)
		GenerateNamespaceStart(ns, output);

	output << "\t\t::Uml::Namespace meta;" << endl;

	GenerateCPPDeclareMetaClasses(ns.classes(), output);
	GenerateCPPDeclareAttributes(ns.classes(), output);
	GenerateCPPDeclareAssociationRoles(ns.classes(), cross_dgr, output, isCrossDgr);
	GenerateCPPDeclareCompositionRoles(ns.classes(), output);
	GenerateCPPDeclareConstraints(ns.classes(), output);
	GenerateCPPCreatesFunction(ns.classes(), "meta", output);
	GenerateCPPInitClassesAttributes(ns.classes(), cross_dgr, output, isCrossDgr);

	GenerateCPPCreatesNamespacesFunction(ns.namespaces(), "meta", output);
	GenerateCPPInitNamespacesFunction(ns.namespaces(), output);

	int ass_inits = GenerateCPPAssociationInitFunctions(ns.associations(), "meta", output);

	UmlCompositionInitFuncInfo comps_inits = GenerateCPPCompositionInitFunctions(ns.compositions(), "meta", output);
	GenerateCPPInitializeCrossNSCompositions(comps_inits, output);

	//generate inheritence initializers
	GenerateCPPInitializeInheritence(ns.classes(), output, false); // in same namespace
	GenerateCPPInitializeInheritence(ns.classes(), output, true); // across namespaces

	//generate Initialize() function
	GenerateCPPInitialize(ns, cross_dgr, output, hname, ass_inits, comps_inits, isCrossDgr);
			

	// initialize from another namespace
	output << endl << "\t\t// initialize from another namespace" << endl;
	GenerateCPPCreates2Function(ns.classes(), false, output);
	GenerateCPPCreatesNamespaces2Function(ns.namespaces(), false, output);
	GenerateCPPInitializeNSSetupMeta(ns, output);
	GenerateCPPInitializeContainer(ns.classes(), ns.namespaces(), cross_dgr, isCrossDgr, false, output);

	if (!single_cpp_namespace) {
		GenerateNamespaceStop(ns, output);
		output << endl;
	}

	if (source_unit == CPP_SOURCE_UNIT_NAMESPACE)
		output << "}" << endl <<"// END " << ns_fname << ".cpp" <<endl;
}


void GenerateCPPDiagramInitialize(const ::Uml::Diagram &diagram, const ::Uml::Diagram cross_dgr, 
                                  ostream & output, const map<string, string> &ns_map, 
                                  const string & macro,
                                  bool integrate_xsd)
{
	output << "\t" << macro << " void Initialize()" << endl << "\t{" << endl; //begin of Initialize()

	output << "\t\tstatic bool first = true;" << endl;
	output << "\t\tif(!first) return;" << endl;
	output << "\t\tfirst = false;" << endl;

	output << "\t\t::Uml::Initialize();" << endl << endl;

	if (cross_dgr && (diagram != cross_dgr))
		output << "\t\t::" << cross_dgr.name() << "::Initialize();" << endl << endl;

	output << "\t\tASSERT( umldiagram == Udm::null );" << endl;

	output << "\t\tUdmStatic::StaticDataNetwork * meta_dn = new UdmStatic::StaticDataNetwork(::Uml::diagram);" << endl;
	output << "\t\tmeta_dn->CreateNew(\"" << diagram.name() << ".mem\", \"\", ::Uml::Diagram::meta, Udm::CHANGES_LOST_DEFAULT);"<< endl;
	output << "\t\tumldiagram = ::Uml::Diagram::Cast(meta_dn->GetRootObject());" << endl;
	output << "\t\tumldiagram.name() =\"" << diagram.name() << "\";" << endl;
	output << "\t\tumldiagram.version() =\"" << diagram.version() << "\";" << endl;
	output << "\t\tInitializeDgr();" << endl << endl;

	if (integrate_xsd)
		CPPSetXsdStorage(diagram, output);

	CPPSetURIMapping(diagram, ns_map, output);

	//call cross namespace inheritence and compositions initializers
	output << "\t\tInitCrossNSInheritence();" << endl;
	output << "\t\tInitCrossNSCompositions();" << endl;

	::Uml::DiagramNamespaces all_nses(diagram);
	for (::Uml::DiagramNamespaces::iterator all_nses_i = all_nses.begin(); all_nses_i != all_nses.end(); all_nses_i++)
	{
		::Uml::Namespace ns = *all_nses_i;
		output << "\t\t" << ns.getPath2("::", false) << "::InitCrossNSInheritence();" << endl;
		output << "\t\t" << ns.getPath2("::", false) << "::InitCrossNSCompositions();" << endl;
	}
	output << endl;

	output << "\t};" << endl << endl;


	output << "\t" << macro << " void Initialize(const ::Uml::Diagram &dgr)" << endl << "\t{" << endl; //begin of Initialize()
	output << "\t\t" << "umldiagram = dgr;" << endl;
	output << "\t\t" << "InitializeDgrSetupMeta(dgr);" << endl;
	output << "\t\t" << "InitializeDgr2();" << endl << endl;

	CPPSetURIMapping(diagram, ns_map, output);
	output << "\t};" << endl << endl;


};
void GenerateNewCPP(const ::Uml::Diagram &diagram, string fname, 
                    const map<string, string> &ns_map, 
                    const ::Uml::Diagram& cross_dgr, 
                    const string& macro,
                    bool integrate_xsd,
		    int source_unit) 
{
		string hname = NameToFilename(diagram.name());

		ofstream output;
		output.open( (fname + ".cpp").c_str() );
		if(!output.good()) throw udm_exception("Error opening for write " + fname + ".cpp");

		bool isCrossDgr = (cross_dgr && (diagram != cross_dgr));

		GenerateCPPPreamble(diagram, cross_dgr, isCrossDgr, fname, fname, output);
		if (integrate_xsd)
			CPPIncludeXsdHeaders(diagram, output);

		if (!ns_map.empty() && !integrate_xsd) 
			output << "#include \"UdmDom.h\"" << endl << endl; 

		output << "namespace " << hname << " {" << endl << endl;
//	::Uml::Diagram diagram;
		output << "\t\t::Uml::Diagram umldiagram;" << endl << endl;

		GenerateCPPDiagram(diagram, cross_dgr, isCrossDgr, fname, output, source_unit);

		::Uml::DiagramNamespaces nses(diagram);
		for (::Uml::DiagramNamespaces::iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
		{
			if (source_unit == CPP_SOURCE_UNIT_NAMESPACE)
			{
				ofstream output;
				string ns_fname = fname + "_" + NameToFilename(nses_i->getPath2("_", false));
				output.open( (ns_fname + ".cpp").c_str() );
				if(!output.good()) throw udm_exception("Error opening for write " + ns_fname + ".cpp");
				GenerateCPPNamespace(*nses_i, cross_dgr, isCrossDgr, fname, output, source_unit);
				output.close();
			}
			else
				GenerateCPPNamespace(*nses_i, cross_dgr, isCrossDgr, fname, output, source_unit);
		}
		
		GenerateCPPDiagramInitialize(diagram, cross_dgr, output, ns_map, macro, integrate_xsd);
		//Udm::UdmDiagram diagram = { &umldiagram, Initialize };
		output << "\t" << macro << " Udm::UdmDiagram diagram = { &umldiagram, Initialize };" << endl;
		//generate the registering static class
		GenerateCPPStaticClass(diagram, output);
		//end of the namespace
		output << "}" << endl <<"// END " << hname << ".cpp" <<endl;
		output.close();
}



