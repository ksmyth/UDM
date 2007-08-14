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
#include "File2Code/File2Code.h"
#include "Udm.h"

using namespace Uml;
typedef vector< ::Uml::Uml::Class> UmlClasses;
typedef pair<set<int>, set<int> > UmlCompositionInitFuncInfo;

string UmlClassCPPName(const ::Uml::Uml::Class &cl)
{
	::Uml::Uml::Namespace cl_ns = (::Uml::Uml::Namespace)cl.parent();
	::Uml::Uml::Diagram diagr = (::Uml::Uml::Diagram)cl_ns.parent();
	return "::" + (string)diagr.name() + "::" + (string)cl_ns.name() + "::" + (string)cl.name();
}

/*
	Declarations in the namespace
*/
void GenerateCPPDeclareMetaClasses(const ::Uml::Uml::Namespace & ns, ostream & output)
{
	//::Uml::Uml::Class A::meta;
	set< ::Uml::Uml::Class> classes = ns.classes();
	set< ::Uml::Uml::Class>::iterator c;
	for(c = classes.begin(); c != classes.end(); c++ )
	{
		::Uml::Uml::Class cl = *c;
		output << "\t\t::Uml::Uml::Class " << cl.name() << "::meta;" << endl;
	}
};
void GenerateCPPDeclareAttributes(const ::Uml::Uml::Namespace & ns, ostream & output)
{
	set< ::Uml::Uml::Class> classes = ns.classes();
	set< ::Uml::Uml::Class>::iterator c;
	//	::Uml::::Uml::Uml::Attribute A::meta_a;
	for(c = classes.begin(); c != classes.end(); c++ )	
	{
		::Uml::Uml::Class cl = *c;
		//::Uml::Uml::Class tempcl(::Uml::Uml::ClassByName(tempdiagram, cl.name()));
		set< ::Uml::Uml::Attribute> attributes = cl.attributes();
		for( set< ::Uml::Uml::Attribute>::iterator i = attributes.begin(); i != attributes.end(); i++) 
		{
			output << "\t\t::Uml::Uml::Attribute " << cl.name() << "::meta_" << (*i).name() << ";" << endl;
		}
	}
};
void GenerateCPPDeclareAssociationRoles(const ::Uml::Uml::Namespace &ns, const ::Uml::Uml::Diagram &cross_dgr, ostream & output, bool isCrossDgr)
{
//declarations for associationroles
	//	::Uml::Uml::AssociationRole A::meta_dst;
	set< ::Uml::Uml::Class> classes = ns.classes();
	set< ::Uml::Uml::Class>::iterator c;
	for(c = classes.begin(); c != classes.end(); c++ ) 
	{
		::Uml::Uml::Class cl = *c;
	
		set< ::Uml::Uml::AssociationRole> assocs = cl.associationRoles();
		for( set< ::Uml::Uml::AssociationRole>::iterator i = assocs.begin(); i != assocs.end(); i++) 
		{
			::Uml::Uml::Association pp = (*i).parent();
			::Uml::Uml::Class aclass = pp.assocClass();
			string aname(MakeRoleName(::Uml::theOther(*i)));
			if(!aclass) 
			{
				output << "\t\t::Uml::Uml::AssociationRole " << cl.name() << "::meta_" << aname << ";" << endl;
			}
			else 
			{
				output << "\t\t::Uml::Uml::AssociationRole " << cl.name() << "::meta_" << aname << ", " << cl.name() << "::meta_" << aname << "_rev;" << endl;
			}
		}

		/*
			Here is printed the decalaration of the cross-association roles
		*/
		//if (cross_dgr &&(cross_dgr != dgr) )
		if (isCrossDgr)
		{
			//--//::Uml::Uml::Class cross_cl = ::Uml::Uml::ClassByName(cross_dgr, cl.name());
			string cross_cl_name = string(cl.name()) + string(Udm::cross_delimiter) + string(ns.name());

			::Uml::Uml::Class cross_cl = ::Uml::classByName(::Uml::GetTheOnlyNamespace(cross_dgr), cross_cl_name );
			if(cross_cl)
			{
				set< ::Uml::Uml::AssociationRole> assocs = cross_cl.associationRoles();
				for( set< ::Uml::Uml::AssociationRole>::iterator i = assocs.begin(); i != assocs.end(); i++) 
				{
					::Uml::Uml::Association pp = (*i).parent();
					::Uml::Uml::Class aclass = pp.assocClass();
					string aname(MakeRoleName(::Uml::theOther(*i)));
					if(!aclass) 
					{
						output << "\t\t::Uml::Uml::AssociationRole " << cl.name() << "::meta_" << aname << ";" << endl;
					}
					else 
					{
						output << "\t\t::Uml::Uml::AssociationRole " << cl.name() << "::meta_" << aname << ", " << cl.name() << "::meta_" << aname << "_rev;" << endl;
					}
				}
			};
		};
		::Uml::Uml::Association assoc = cl.association();
		string s = assoc.meta.name();
		if(assoc) 
		{
			set< ::Uml::Uml::AssociationRole> assocs = assoc.roles();
			for( set< ::Uml::Uml::AssociationRole>::iterator i = assocs.begin(); i != assocs.end(); i++) 
			{
				string aname(MakeRoleName(*i));
				if(aname.size()) 
				{
				  output << "\t\t::Uml::Uml::AssociationRole " << cl.name() << "::meta_" << aname << "_end_;" << endl;
				}
			}
		};
		if (isCrossDgr)
		//if (cross_dgr &&(cross_dgr != dgr) )
		{
			//--//::Uml::Uml::Class cross_cl = ::Uml::Uml::ClassByName(cross_dgr, cl.name());
			::Uml::Uml::Class cross_cl = ::Uml::classByName(::Uml::GetTheOnlyNamespace(cross_dgr), (string(cl.name()) + string(Udm::cross_delimiter) + string(ns.name())) );
			if(cross_cl)
			{
				::Uml::Uml::Association assoc = cross_cl.association();
				string s = assoc.meta.name();
				if(assoc) 
				{
					set< ::Uml::Uml::AssociationRole> assocs = assoc.roles();
					for( set< ::Uml::Uml::AssociationRole>::iterator i = assocs.begin(); i != assocs.end(); i++) 
					{
						string aname(MakeRoleName(*i));
						if(aname.size()) 
						{
							output << "\t\t::Uml::Uml::AssociationRole " << cl.name() << "::meta_" << aname << "_end_;" << endl;
						}
					}
				}
			}
		};
	};//end for cycle for declaration for associationRoles
};
void GenerateCPPDeclareCompositionRoles(const ::Uml::Uml::Namespace &ns, ostream& output)
{
	set< ::Uml::Uml::Class> classes = ns.classes();
	set< ::Uml::Uml::Class>::iterator c;
	
//	::Uml::Uml::CompositionParentRole A::meta_parent;
	for(c = classes.begin(); c != classes.end(); c++ ) 
	{
		::Uml::Uml::Class cl = *c;
		set< ::Uml::Uml::CompositionChildRole> children = cl.childRoles();
		for( set< ::Uml::Uml::CompositionChildRole>::iterator i = children.begin(); i != children.end(); i++) {
			string aname(MakeRoleName(::Uml::theOther(*i)));
			output << "\t\t::Uml::Uml::CompositionParentRole " << cl.name() << "::meta_" << aname << ";" << endl;
		}
	}
//	::Uml::Uml::CompositionChildRole D::meta_as;
	for(c = classes.begin(); c != classes.end(); c++ ) 
	{
		::Uml::Uml::Class cl = *c;
		set< ::Uml::Uml::CompositionParentRole> children = cl.parentRoles();
		for( set< ::Uml::Uml::CompositionParentRole>::iterator i = children.begin(); i != children.end(); i++) {
			string aname(MakeRoleName(::Uml::theOther(*i)));
			output << "\t\t::Uml::Uml::CompositionChildRole " << cl.name() << "::meta_" << aname << ";" << endl;
		}
	}
};
void GenerateCPPDeclareConstraints(const ::Uml::Uml::Namespace &ns, ostream & output)
{
	set< ::Uml::Uml::Class> classes = ns.classes();
	set< ::Uml::Uml::Class>::iterator c;
	
//  ::Uml::Uml::Constraint D::meta_constraint
	for(c = classes.begin(); c != classes.end(); c++ ) 
	{
		::Uml::Uml::Class cl = *c;
		set< ::Uml::Uml::Constraint> constraints = cl.constraints();
		for( set< ::Uml::Uml::Constraint>::iterator i = constraints.begin(); i != constraints.end(); i++) 
			output << "\t\t::Uml::Uml::Constraint " << cl.name() << "::meta_" << i->name() << ";" << endl;
	}

//	::Uml::Uml::ConstraintDefinition D::meta_constraint_definition
	for(c = classes.begin(); c != classes.end(); c++ ) 
	{
		::Uml::Uml::Class cl = *c;
		set< ::Uml::Uml::ConstraintDefinition> definitions = cl.definitions();
		for( set< ::Uml::Uml::ConstraintDefinition>::iterator i = definitions.begin(); i != definitions.end(); i++) 
			output << "\t\t::Uml::Uml::ConstraintDefinition " << cl.name() << "::meta_" << i->name() << ";" << endl;
	}
};

/*

	Generators of functions, outside Initialize()
*/
void GenerateCPPCreatesFunction(const ::Uml::Uml::Namespace &ns, ostream & output)
{
	set< ::Uml::Uml::Class> classes = ns.classes();
	set< ::Uml::Uml::Class>::iterator c;
	
//void Create()
// {

	output << "\t\tvoid Creates()" << endl << "\t\t{" << endl;
		
//	A::meta = Uml::CreateClass();
	for(c = classes.begin(); c != classes.end(); c++ )
	{
		::Uml::Uml::Class cl = *c;
		output << "\t\t\t" << cl.name() << "::meta = ::Uml::Uml::Class::Create(meta);" << endl;
	}

//	A::meta_a = Uml::CreateAttribute();
	for(c = classes.begin(); c != classes.end(); c++ )	
	{
		::Uml::Uml::Class cl = *c;
		
		set< ::Uml::Uml::Attribute> attributes = cl.attributes();
		for( set< ::Uml::Uml::Attribute>::iterator i = attributes.begin(); i != attributes.end(); i++) 
		{
			output << "\t\t\t" << cl.name() << "::meta_" << (*i).name() << " = ::Uml::Uml::Attribute::Create(" << cl.name()<<"::meta);" << endl;
		}

			//constraints
		set< ::Uml::Uml::Constraint> constraints = cl.constraints();
		for (set< ::Uml::Uml::Constraint>::iterator j = constraints.begin(); j != constraints.end(); j++)
		{
			output << "\t\t\t" << cl.name() << "::meta_" << j->name() << " = ::Uml::Uml::Constraint::Create(" << cl.name() << "::meta);" << endl;
		}

			//constraintdefinitions
		set< ::Uml::Uml::ConstraintDefinition> definitions = cl.definitions();
		for (set< ::Uml::Uml::ConstraintDefinition>::iterator k = definitions.begin(); k != definitions.end(); k++)
		{
			output << "\t\t\t" << cl.name() << "::meta_" << k->name() << " = ::Uml::Uml::ConstraintDefinition::Create(" << cl.name() << "::meta);" << endl;
		}
	}
	output << "\t\t}" << endl;
};

void GenerateCPPInitClassesAttributes(const ::Uml::Uml::Namespace & ns, const ::Uml::Uml::Diagram & cross_dgr, ostream & output, bool isCrossDgr)
{
	//void InitAttributes()
// {
	output << "\t\tvoid InitClassesAttributes()" << endl << "\t\t{" << endl;
	set< ::Uml::Uml::Class> classes = ns.classes();
	set< ::Uml::Uml::Class>::iterator c;
	for(c = classes.begin(); c != classes.end(); c++ )
	{
		::Uml::Uml::Class cl = *c;
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
		::Uml::Uml::Class cl = *c;
		set< ::Uml::Uml::Attribute> attributes = cl.attributes();
		for( set< ::Uml::Uml::Attribute>::iterator i = attributes.begin(); i != attributes.end(); i++) 
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

		set< ::Uml::Uml::Constraint> constraints= cl.constraints();
		for( set< ::Uml::Uml::Constraint>::iterator j = constraints.begin(); j != constraints.end(); j++) 
		{
			output << "\t\t\t" << cl.name() << "::meta_" << j->name() << ".name() = \"" << j->name() << "\";" << endl;
			output << "\t\t\t" << cl.name() << "::meta_" << j->name() << ".description() = \"" << j->description() << "\";" << endl;
			output << "\t\t\t" << cl.name() << "::meta_" << j->name() << ".expression() = \"" << j->expression() << "\";" << endl;
		}

		set< ::Uml::Uml::ConstraintDefinition> defs = cl.definitions();
		for( set< ::Uml::Uml::ConstraintDefinition>::iterator k = defs.begin(); k != defs.end(); k++) 
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
			::Uml::Uml::Class cross_cl;
			::Uml::Uml::Association ass;
			if (cross_dgr)
			{
				//--//cross_cl = ::Uml::Uml::ClassByName(cross_dgr, cl.name());
				cross_cl = ::Uml::classByName(::Uml::GetTheOnlyNamespace(cross_dgr), (string(cl.name()) + string(Udm::cross_delimiter) + string(ns.name())) );
			}
			if (cross_cl)
				ass = cross_cl.association();
			if (ass)
			{
				set< ::Uml::Uml::AssociationRole> asrs = ass.roles();
				set< ::Uml::Uml::AssociationRole>::iterator asrs_i = asrs.begin();
				while (asrs_i != asrs.end())
				{
					output << " \t\t\t" << cl.name() << "::meta_" << asrs_i->name() << "_end_ = " 
						<< "::" << cross_dgr.name() << "::"  << ::Uml::GetTheOnlyNamespace(cross_dgr).name() << "::" << ((::Uml::Uml::Class)((::Uml::theOther(*asrs_i)).target())).name()<<"::meta_" << asrs_i->name() << ";" <<endl;
					asrs_i++;
				}
			};
		}
	}
	output << "\t\t\t" << endl;
	output << "\t\t}" << endl;
};
void GenerateCompositionInit(const ::Uml::Uml::Namespace & ns, const ::Uml::Uml::Composition &c, ostream &output, int funct_no)
{
	output << "\t\tvoid InitComposition" << funct_no << "()" << endl << "\t\t{" << endl;
	output << "\t\t\t::Uml::Uml::Composition comp = ::Uml::Uml::Composition::Create(meta);" << endl;

	if (!((string)c.name()).empty())output << "\t\t\tcomp.name() =\"" << c.name() << "\";" <<endl;
	output << "\t\t\tcomp.nonpersistent() =" << (c.nonpersistent() ? "true" : "false") << ";" << endl;

	::Uml::Uml::CompositionParentRole zzp = c.parentRole();
	::Uml::Uml::CompositionChildRole zzc = c.childRole();
	string aname(MakeRoleName(zzp));
	output << "\t\t\t" << UmlClassCPPName((::Uml::Uml::Class)zzc.target()) << "::meta_" << aname <<" = ::Uml::Uml::CompositionParentRole::Create(comp);" << endl;
	output << "\t\t\t" << UmlClassCPPName((::Uml::Uml::Class)zzc.target()) << "::meta_" << aname <<".name() = \"" << aname << "\";" << endl;
	output << "\t\t\t" << UmlClassCPPName((::Uml::Uml::Class)zzc.target()) << "::meta_" << aname <<".isNavigable() = " << (zzp.isNavigable() ? "true;" : "false;") << endl;
	output << "\t\t\t" << UmlClassCPPName((::Uml::Uml::Class)zzc.target()) << "::meta_" << aname <<".target() = " << UmlClassCPPName((::Uml::Uml::Class)zzp.target()) << "::meta;" << endl;

	string cname(MakeRoleName(zzc));
	output << "\t\t\t" << UmlClassCPPName((::Uml::Uml::Class)zzp.target()) << "::meta_" << cname << " = ::Uml::Uml::CompositionChildRole::Create(comp);" << endl;

	output << "\t\t\t" << UmlClassCPPName((::Uml::Uml::Class)zzp.target()) << "::meta_" << cname << ".name() = \"" << MakeShortRoleName(zzc) << "\";" << endl;
	output << "\t\t\t" << UmlClassCPPName((::Uml::Uml::Class)zzp.target()) << "::meta_" << cname << ".min() = " << zzc.min() << ";"<< endl;
	output << "\t\t\t" << UmlClassCPPName((::Uml::Uml::Class)zzp.target()) << "::meta_" << cname << ".max() = " << zzc.max() << ";"<< endl;
	output << "\t\t\t" << UmlClassCPPName((::Uml::Uml::Class)zzp.target()) << "::meta_" << cname << ".isNavigable() = " << (zzc.isNavigable() ? "true;" : "false;") << endl;
	output << "\t\t\t" << UmlClassCPPName((::Uml::Uml::Class)zzp.target()) << "::meta_" << cname << ".target() = " << UmlClassCPPName((::Uml::Uml::Class)zzc.target()) << "::meta;" << endl;

	output << "\t\t}" << endl;
};

void GenerateAssociationInit(const ::Uml::Uml::Namespace & ns, const ::Uml::Uml::Association &a,  ostream &output, int funct_no)
{
	output << "\t\tvoid InitAssociation" << funct_no << "()" << endl << "\t\t{" << endl;

	set< ::Uml::Uml::AssociationRole> ar = a.roles();
	ASSERT(ar.size() == 2);
	
	output << "\t\t\t::Uml::Uml::Association ass = ::Uml::Uml::Association::Create(meta);" << endl;

	::Uml::Uml::Class aclass = a.assocClass();
	if (!((string)a.name()).empty())output << "\t\t\tass.name() = \"" << a.name() << "\";" <<endl;
	if(aclass) 
	{
		output << "\t\t\tass.assocClass() = " << UmlClassCPPName(aclass) << "::meta;" << endl;
	}

	set< ::Uml::Uml::AssociationRole> roles = a.roles();
	for( set< ::Uml::Uml::AssociationRole>::iterator i = roles.begin(); i != roles.end(); i++) 
	{
		::Uml::Uml::AssociationRole zz	= ::Uml::theOther(*i);
		string aname(MakeRoleName(zz));
		::Uml::Uml::Class cl = i->target();
		
		output << "\t\t\t" << UmlClassCPPName(cl) << "::meta_" << aname << " = ::Uml::Uml::AssociationRole::Create(ass);" <<endl;
		output << "\t\t\t" << UmlClassCPPName(cl) << "::meta_" << aname << ".name() = \"" << aname << "\";" <<endl;
		output << "\t\t\t" << UmlClassCPPName(cl) << "::meta_" << aname << ".min() = " << zz.min() << ";" <<endl;
		output << "\t\t\t" << UmlClassCPPName(cl) << "::meta_" << aname << ".max() = " << zz.max() << ";" <<endl;
		output << "\t\t\t" << UmlClassCPPName(cl) << "::meta_" << aname << ".isNavigable() = " << (zz.isNavigable() ? "true":"false") << ";" <<endl;
		output << "\t\t\t" << UmlClassCPPName(cl) << "::meta_" << aname << ".isPrimary() = " << (zz.isPrimary() ? "true":"false") << ";" <<endl;
		output << "\t\t\t" << UmlClassCPPName(cl) << "::meta_" << aname << ".target() = " << UmlClassCPPName((::Uml::Uml::Class)zz.target()) << "::meta;" <<endl;

		::Uml::Uml::Class aclass = a.assocClass();
		if(aclass) 
		{
			::Uml::Uml::Class cl2 = zz.target();
			output << "\t\t\t" << UmlClassCPPName(aclass) << "::meta_" << aname << "_end_ = " <<
							UmlClassCPPName(cl2) << "::meta_" << MakeRoleName(*i) << "_rev = " << 
							UmlClassCPPName(cl) << "::meta_" << aname << ";" << endl;
		}
	}
	
	
	output << "\t\t};" << endl;

}

int GenerateCPPAssociationInitFunctions(const ::Uml::Uml::Namespace & ns, ostream &output)
{
	int ass_inits = 0;
	const set< ::Uml::Uml::Association> &asss = ns.associations();
	set< ::Uml::Uml::Association>::const_iterator a;
	for(a = asss.begin(); a != asss.end(); a++ )	
		GenerateAssociationInit(ns, *a, output, ass_inits++);
	return ass_inits;	
};
UmlCompositionInitFuncInfo GenerateCPPCompositionInitFunctions(const ::Uml::Uml::Namespace & ns, ostream &output)
{
	UmlCompositionInitFuncInfo comp_inits;
	int comp_init_index = 0;
	const set< ::Uml::Uml::Composition> &comps = ns.compositions();
	set< ::Uml::Uml::Composition>::const_iterator c;
	for(c = comps.begin(); c != comps.end(); c++ ) {
		GenerateCompositionInit(ns, *c, output, comp_init_index);
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
void GenerateCPPCrossObjectInits(const ::Uml::Uml::Namespace &ns, const ::Uml::Uml::Diagram & cross_dgr, ostream & output, bool isCrossDgr)
{
	set< ::Uml::Uml::Class> classes = ns.classes();
	set< ::Uml::Uml::Class>::iterator c;
	if (isCrossDgr)
	//if (cross_dgr &&(cross_dgr != diagram))
	{
		//		M2::meta_src = CL::M2::meta_src;		
		for(c = classes.begin(); c != classes.end(); c++ )	
		{
			::Uml::Uml::Class cl = *c;
			::Uml::Uml::Class cross_cl;
			if (cross_dgr)
			{
				cross_cl = ::Uml::classByName(::Uml::GetTheOnlyNamespace(cross_dgr), (string(cl.name()) + string(Udm::cross_delimiter) + string(ns.name())) );
				//--//cross_cl = ::Uml::Uml::ClassByName(cross_dgr, cl.name());
			}
			if (cross_cl)
			{
				set< ::Uml::Uml::AssociationRole> ar = cross_cl.associationRoles();
				set< ::Uml::Uml::AssociationRole>::iterator ar_i = ar.begin();
				while (ar_i != ar.end())
				{
					output << "\t\t\t" << cl.name() << "::meta_"<<::Uml::theOther((*ar_i)).name() << 
					" = " << "::" << cross_dgr.name()<< "::" << ::Uml::GetTheOnlyNamespace(cross_dgr).name() << "::"  << cross_cl.name() << "::meta_"<<::Uml::theOther((*ar_i)).name()<< ";" <<endl;

					::Uml::Uml::AssociationRole zz	= ::Uml::theOther(*ar_i);
					string aname(MakeRoleName(zz));

					::Uml::Uml::Association ass = ar_i->parent();
					::Uml::Uml::Class a_class = ass.assocClass();
					
					if(a_class) 
					{
						::Uml::Uml::Class cl2 = zz.target();
						
						output << "\t\t\t" << cl.name() << "::meta_"<<::Uml::theOther((*ar_i)).name() << 
							"_rev = " << "::" << cross_dgr.name()<< "::" << ::Uml::GetTheOnlyNamespace(cross_dgr).name() << "::" << cl2.name() << "::meta_"<<ar_i->name()<< ";" <<endl;

					}
					ar_i++;
				}
			}
		}
	}
};

void GenerateCPPInitializeInheritence(const ::Uml::Uml::Namespace &ns, ostream & output)
{
	output << "\t\tvoid InitInheritence()" << endl << "\t\t{" << endl;

	set< ::Uml::Uml::Class> classes = ns.classes();;
	set< ::Uml::Uml::Class>::iterator c;
	for(c = classes.begin(); c != classes.end(); c++ ) 
	{
		::Uml::Uml::Class cl = *c;
		set< ::Uml::Uml::Class> st = cl.subTypes();
		for( set< ::Uml::Uml::Class>::iterator i = st.begin(); i != st.end(); i++)
		{
			if ((::Uml::Uml::Namespace)i->parent() == ns)
				output << "\t\t\t" << cl.name() << "::meta.subTypes() +=  " << UmlClassCPPName(*i) << "::meta;" << endl;
		}
	}	
	output << "\t\t}" << endl;
};

void GenerateCPPInitializeCrossNSInheritence(const ::Uml::Uml::Namespace &ns, ostream & output)
{
	output << "\t\tvoid InitCrossNSInheritence()" << endl << "\t\t{" << endl;

	set< ::Uml::Uml::Class> classes = ns.classes();;
	set< ::Uml::Uml::Class>::iterator c;
	for(c = classes.begin(); c != classes.end(); c++ ) 
	{
		::Uml::Uml::Class cl = *c;
		set< ::Uml::Uml::Class> st = cl.subTypes();
		for( set< ::Uml::Uml::Class>::iterator i = st.begin(); i != st.end(); i++)
		{
			if ((::Uml::Uml::Namespace)i->parent() != ns)
				output << "\t\t\t" << cl.name() << "::meta.subTypes() +=  " << UmlClassCPPName(*i) << "::meta;" << endl;
		}
	}	
	output << "\t\t}" << endl;
};

void GenerateCPPInitializeCrossNSCompositions(const ::Uml::Uml::Namespace &ns, const UmlCompositionInitFuncInfo &comp_inits, ostream & output)
{
	output << "\t\tvoid InitCrossNSCompositions()" << endl << "\t\t{" << endl;

	for (set<int>::const_iterator comp_inits_i = comp_inits.second.begin(); comp_inits_i != comp_inits.second.end(); comp_inits_i++) {
		output << "\t\t\tInitComposition" << *comp_inits_i << "();" << endl;
	}

	output << "\t\t}" << endl;
};

void GenerateCPPStaticClass(const ::Uml::Uml::Diagram &diagram, ostream & output)
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
void GenerateCPPInitialize(const ::Uml::Uml::Namespace &ns, const ::Uml::Uml::Diagram & cross_dgr, ostream & output, const string& macro, const string& hname, int ass_inits, const UmlCompositionInitFuncInfo &comp_inits, bool isCrossDgr)
{
	output << "\t\t" << macro << " void Initialize()" << endl << "\t\t{" << endl; //begin of Initialize()
/*
	output << "\t\tstatic bool first = true;" << endl;
	output << "\t\tif(!first) return;" << endl;
	output << "\t\tfirst = false;" << endl;

	output << "\t\tUml::Initialize();" << endl << endl;

	//bool isCrossDgr = (cross_dgr &&(cross_dgr != diagram));
	
	//if (cross_dgr && (diagram != cross_dgr))
	if (isCrossDgr)
		output << "\t\t" << cross_dgr.name() << "::Initialize();" << endl << endl;

	output << "\t\tASSERT( umldiagram == Udm::null );" << endl;

	output << "\t\tUdmStatic::StaticDataNetwork * meta_dn = new UdmStatic::StaticDataNetwork(::Uml::Uml::Diagram);" << endl;
	output << "\t\tmeta_dn->CreateNew(\"" << hname << ".mem\", \"\", ::Uml::Uml::Diagram::meta, Udm::CHANGES_LOST_DEFAULT);"<< endl;
	output << "\t\tumldiagram = ::Uml::Uml::Diagram::Cast(meta_dn->GetRootObject());" << endl;
	output << "\t\tumldiagram.name() =\"" << hname << "\";" << endl;
//	output << "\t\tumldiagram.version() =\"" << diagram.version() << "\";" << endl;
*/
	output << "\t\t\tCreates();" << endl;
	output << "\t\t\tInitClassesAttributes();" << endl;
		
//	output << "\t\tUml::InitNamespace(meta, umldiagram, \"" << hname << "\", \"" << diagram.version() << "\");" << endl << endl;
		
	
	//call the InitAssociation functions
		
	for (int ass_inits_i = 0; ass_inits_i < ass_inits; ass_inits_i++) output << "\t\t\tInitAssociation" << ass_inits_i << "();" << endl;
			
	//call the InitComposition calls (only those that initialize local namespace compositions)

	for (set<int>::const_iterator comp_inits_i = comp_inits.first.begin(); comp_inits_i != comp_inits.first.end(); comp_inits_i++) {
		output << "\t\t\tInitComposition" << *comp_inits_i << "();" << endl;
	}

	//call the intializers for association roles created in the cross diagrams
	GenerateCPPCrossObjectInits(ns, cross_dgr, output, isCrossDgr);

	//call the initializer for inheritence in the same namespace
	output << "\t\t\tInitInheritence();" << endl;


	output << "\t\t\t" << endl << "\t\t}" << endl;	//end of Initialize()

};

/*
	Function building the alternate Initialize(const ::Uml::Uml::Namespace &ns) function
*/

void GenerateCPPInitializeNamespace(const ::Uml::Uml::Namespace & ns, ostream & output, const string & macro)
{
	set< ::Uml::Uml::Class> classes = ns.classes();
	set< ::Uml::Uml::Class>::iterator c;
	
	output << "\t\t" << macro << " void Initialize(const ::Uml::Uml::Namespace & ns)" << endl << "\t\t{" << endl;

	for (c = classes.begin(); c != classes.end(); c++)
	{
		::Uml::Uml::Class cl = *c;
    output << "\t\t\t::Uml::SetClass(" << cl.name() <<"::meta, ns, \"" << cl.name() << "\");" <<endl;

		//attributes
		set< ::Uml::Uml::Attribute> cl_atts = cl.attributes();
		for (set< ::Uml::Uml::Attribute>::iterator cla_i = cl_atts.begin(); cla_i != cl_atts.end(); cla_i++)
		{
			::Uml::Uml::Attribute a = *cla_i;
      output << "\t\t\t::Uml::SetAttribute(" << cl.name() <<"::meta_" << a.name() << "," << cl.name() << "::meta, \"" << a.name() << "\");" <<endl;

		};
	};

	output << "\t\t\t" << "//composition child roles " << endl;
	for (c = classes.begin(); c != classes.end(); c++)
	{
	
		::Uml::Uml::Class cl = *c;

		//composition parent roles
		set< ::Uml::Uml::CompositionChildRole> ccrs = cl.childRoles();
		for (set< ::Uml::Uml::CompositionChildRole>::iterator ccrs_i = ccrs.begin(); ccrs_i != ccrs.end(); ccrs_i ++)
		{
			::Uml::Uml::CompositionChildRole ccr = *ccrs_i;
			string rolename = ::Uml::MakeRoleName(::Uml::theOther(ccr));
			::Uml::Uml::Class theot = (::Uml::Uml::Class)::Uml::theOther(ccr).target();
      output << "\t\t\t::Uml::SetParentRole(" << cl.name() <<"::meta_" << rolename << "," << cl.name() << "::meta," << UmlClassCPPName(theot) << "::meta, \"" << ccr.name() << "\", \"" << ::Uml::theOther(ccr).name() << "\");" <<endl;

		};

	};
	
	output << "\t\t\t" << "// composition parentroles " << endl;
	for (c = classes.begin(); c != classes.end(); c++)
	{
		::Uml::Uml::Class cl = *c;

		//composition child roles
		set< ::Uml::Uml::CompositionParentRole> cprs = cl.parentRoles();
		for (set< ::Uml::Uml::CompositionParentRole>::iterator cprs_i = cprs.begin(); cprs_i != cprs.end(); cprs_i ++)
		{
			::Uml::Uml::CompositionParentRole cpr = *cprs_i;
			string rolename = ::Uml::MakeRoleName(::Uml::theOther(cpr));
			::Uml::Uml::Class theot = (::Uml::Uml::Class)::Uml::theOther(cpr).target();
      output << "\t\t\t::Uml::SetChildRole(" << cl.name() <<"::meta_" << rolename << "," << cl.name() << "::meta," << UmlClassCPPName(theot) << "::meta, \"" << cpr.name() << "\", \"" << ::Uml::theOther(cpr).name() << "\");" <<endl;

		};
	};
	
	output << "\t\t\t" << "// Association roles " << endl;
	for (c = classes.begin(); c != classes.end(); c++)
	{
		::Uml::Uml::Class cl = *c;

		//association roles
		set< ::Uml::Uml::AssociationRole> ars = cl.associationRoles();
		for (set< ::Uml::Uml::AssociationRole>::iterator ars_i = ars.begin(); ars_i != ars.end(); ars_i ++)
		{
			::Uml::Uml::AssociationRole ar = *ars_i;
			string rolename = ::Uml::MakeRoleName(::Uml::theOther(ar));
			::Uml::Uml::Class theot = (::Uml::Uml::Class)::Uml::theOther(ar).target();

      output << "\t\t\t::Uml::SetAssocRole(" << cl.name() <<"::meta_" << rolename << "," << cl.name() << "::meta," << UmlClassCPPName(theot) << "::meta, \"" << ar.name() << "\");" <<endl;

			::Uml::Uml::Association as = ar.parent();
			::Uml::Uml::Class aclass = as.assocClass();
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
		::Uml::Uml::Class cl = *c;

		::Uml::Uml::Association as = cl.association();
		if (as)
		{
			set< ::Uml::Uml::AssociationRole> ars = as.roles();
			for (set< ::Uml::Uml::AssociationRole>::iterator ars_i = ars.begin();ars_i != ars.end(); ars_i++)
			{
				::Uml::Uml::AssociationRole ar = *ars_i;
				output << "\t\t\t" << cl.name() << "::meta_" << ::Uml::MakeRoleName(ar) << "_end_ = " << UmlClassCPPName((::Uml::Uml::Class)::Uml::theOther(ar).target()) << "::meta_" <<::Uml::MakeRoleName(ar) << ";" << endl;

			};
		};
		//_end_ association roles
	};
	output << endl;
	
	output << "\t\t\t" << endl << "\t\t}" << endl; //end of Initialize(const ::Uml::Uml::Diagram & dgr);
};

void GenerateCPPPreamble(const ::Uml::Uml::Diagram &diagram, const ::Uml::Uml::Diagram &cross_dgr, bool isCrossDgr, const string &h_fname, const string &fname, ostream &output)
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

void GenerateCPPNamespace(const ::Uml::Uml::Namespace &ns, const ::Uml::Uml::Diagram &cross_dgr, bool isCrossDgr, const string &fname, ostream &output, const string &macro, int source_unit)
{
	::Uml::Uml::Diagram diagram = ns.parent();
	string hname = NameToFilename(diagram.name());
	string ns_fname = fname + "_" + NameToFilename(ns.name());

	if (source_unit == CPP_SOURCE_UNIT_NAMESPACE)
	{
		GenerateCPPPreamble(diagram, cross_dgr, isCrossDgr, fname, ns_fname, output);
		output << "namespace " << hname << " {" << endl << endl;
	}

	output << "\tnamespace " << ns.name() << " {" << endl << endl;
	output << "\t\t::Uml::Uml::Namespace meta;" << endl;

	GenerateCPPDeclareMetaClasses(ns, output);
	GenerateCPPDeclareAttributes(ns, output);
	GenerateCPPDeclareAssociationRoles(ns, cross_dgr, output, isCrossDgr);
	GenerateCPPDeclareCompositionRoles(ns, output);
	GenerateCPPDeclareConstraints(ns, output);
	GenerateCPPCreatesFunction(ns, output);
	GenerateCPPInitClassesAttributes(ns, cross_dgr, output, isCrossDgr);
		
	int ass_inits = GenerateCPPAssociationInitFunctions(ns, output);

	UmlCompositionInitFuncInfo comps_inits = GenerateCPPCompositionInitFunctions(ns, output);
	GenerateCPPInitializeCrossNSCompositions(ns, comps_inits, output);

	//generate inheritence initializers
	GenerateCPPInitializeInheritence(ns, output);
	GenerateCPPInitializeCrossNSInheritence(ns, output);

	//generate Initialize() function
	GenerateCPPInitialize(ns, cross_dgr, output, macro, hname, ass_inits, comps_inits, isCrossDgr);
			
	//generate Initialize(const ::Uml::Uml::Namespace &ns); function
	GenerateCPPInitializeNamespace(ns, output,macro);

	output << "\t}" << endl;	

	if (source_unit == CPP_SOURCE_UNIT_NAMESPACE)
		output << "}" << endl <<"// END " << ns_fname << ".cpp" <<endl;
}


void GenerateCPPDiagramInitialize(const ::Uml::Uml::Diagram &diagram, const ::Uml::Uml::Diagram cross_dgr, 
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
	output << "\t\tmeta_dn->CreateNew(\"" << diagram.name() << ".mem\", \"\", ::Uml::Uml::Diagram::meta, Udm::CHANGES_LOST_DEFAULT);"<< endl;
	output << "\t\tumldiagram = ::Uml::Uml::Diagram::Cast(meta_dn->GetRootObject());" << endl;
	output << "\t\tumldiagram.name() =\"" << diagram.name() << "\";" << endl;
	output << "\t\tumldiagram.version() =\"" << diagram.version() << "\";" << endl;

	const set< ::Uml::Uml::Namespace>& nses = diagram.namespaces();
	for (set< ::Uml::Uml::Namespace>::const_iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
	{
		::Uml::Uml::Namespace ns = *nses_i;
		output << "\t\t" << endl;
		output << "\t\t" << ns.name() << "::meta = ::Uml::Uml::Namespace::Create(umldiagram);" << endl;
		output << "\t\t" << ns.name() << "::meta.name() = \"" << ns.name() <<"\";" << endl;
		output << "\t\t" << ns.name() << "::Initialize();" << endl;
	}
	output << endl;

	if (integrate_xsd)
	{
  
		for (set< ::Uml::Uml::Namespace>::const_iterator nses_i = nses.begin(); nses_i != nses.end(); ++nses_i)
		{
			const ::Uml::Uml::Namespace& ns = *nses_i;
			const std::string& nsn = ns.name();
			output << "\t\t" << "UdmDom::str_xsd_storage::StoreXsd(\"" << ns.name() << ".xsd\"," << ns.name() <<"_xsd::getString());"<< endl;
		}
	}

	if (!ns_map.empty())
	{
		output << "\n\t\t// URI namespace mapping for dom backend, udm was invoked with switch -u" << "\n";
		map<string, string>::const_iterator it =  ns_map.begin();
		for(;it != ns_map.end(); ++it)
		{
			output << "\t\t" << "UdmDom::AddURIToUMLNamespaceMapping(\""<< it->second<<"\",\""<<it->first<<"\");" << std::endl;
		}
	}

	//call cross namespace inheritence and compositions initializers
	for (set< ::Uml::Uml::Namespace>::const_iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
	{
		::Uml::Uml::Namespace ns = *nses_i;
		output << "\t\t" << ns.name() << "::InitCrossNSInheritence();" << endl;
		output << "\t\t" << ns.name() << "::InitCrossNSCompositions();" << endl;
	}
	output << endl;

	output << "\t};"<<endl;


	output << "\t" << macro << " void Initialize(const ::Uml::Uml::Diagram &dgr)" << endl << "\t{" << endl; //begin of Initialize()
	output << "\t\t" << "umldiagram = dgr;" << endl;
	for (set< ::Uml::Uml::Namespace>::const_iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
	{
		::Uml::Uml::Namespace ns = *nses_i;
		output << "\t\t" << "::Uml::SetNamespace(" << ns.name() << "::meta, dgr, \"" << ns.name() << "\");" << endl;
		output << "\t\t" << ns.name() << "::Initialize(" << ns.name() << "::meta);" << endl;
	}

	if (integrate_xsd)
	{
  
		for (set< ::Uml::Uml::Namespace>::const_iterator nses_i = nses.begin(); nses_i != nses.end(); ++nses_i)
		{
			const ::Uml::Uml::Namespace& ns = *nses_i;
			const std::string& nsn = ns.name();
			std::string infname(nsn + std::string(".xsd"));

			File2Code f2c(nsn + std::string("_xsd"), infname, File2Code::CPP);

			std::string outfname(nsn + std::string("_xsd.h"));
			std::ofstream out(outfname.c_str());
			f2c.gen(out);
			out.close();
			output << "\t\t" << "UdmDom::str_xsd_storage::StoreXsd(\"" << ns.name() << ".xsd\"," << ns.name() <<"_xsd::getString());"<< endl;
		}
	}

	if (!ns_map.empty())
	{
		output << "\n\t\t// URI namespace mapping for dom backend, udm was invoked with switch -u" << "\n";
		map<string, string>::const_iterator it =  ns_map.begin();
		for(;it != ns_map.end(); ++it)
		{
			output << "\t\t" << "UdmDom::AddURIToUMLNamespaceMapping(\""<< it->second<<"\",\""<<it->first<<"\");" << std::endl;
		}
	}
	output << "\t};"<<endl;


};
void GenerateNewCPP(const ::Uml::Uml::Diagram &diagram, string fname, 
                    const map<string, string> &ns_map, 
                    const ::Uml::Uml::Diagram& cross_dgr, 
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
		{
			output << "#include \"UdmDom.h\"" << endl; 
			set< ::Uml::Uml::Namespace> nses = diagram.namespaces();
			for (set< ::Uml::Uml::Namespace>::iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
			{
				::Uml::Uml::Namespace ns = *nses_i;	
				output << "#include \"" << ns.name() << "_xsd.h\"" << endl << endl; 
			}
		}

		if (!ns_map.empty() && !integrate_xsd) 
			output << "#include \"UdmDom.h\"" << endl << endl; 

		output << "namespace " << hname << " {" << endl << endl;
//	::Uml::Uml::Diagram diagram;
		output << "\t::Uml::Uml::Diagram umldiagram;" << endl << endl;

		set< ::Uml::Uml::Namespace> nses = diagram.namespaces();
		for (set< ::Uml::Uml::Namespace>::iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
		{
			if (source_unit == CPP_SOURCE_UNIT_NAMESPACE)
			{
				ofstream output;
				string ns_fname = fname + "_" + NameToFilename(nses_i->name());
				output.open( (ns_fname + ".cpp").c_str() );
				if(!output.good()) throw udm_exception("Error opening for write " + ns_fname + ".cpp");
				GenerateCPPNamespace(*nses_i, cross_dgr, isCrossDgr, fname, output, macro, source_unit);
				output.close();
			}
			else
				GenerateCPPNamespace(*nses_i, cross_dgr, isCrossDgr, fname, output, macro, source_unit);
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



