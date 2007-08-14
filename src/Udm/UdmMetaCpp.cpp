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

		took the functions from UdmCppH.cpp
		Also separated the huge generator function into a bunch of smaller functions to increase readability

*/




#include "Uml.h"
#include "UmlExt.h"
#include <time.h>
#include <map>
#include "Udm.h"

typedef vector< ::Uml::Class> UmlClasses;


/*
	Functions used to generate Initialize()
	They are defined here.
*/
void GenerateMetaCPPCreates(const set< ::Uml::Class> &classes, ostream &output)
{
	set< ::Uml::Class>::const_iterator c;
	//	A::meta = Uml::CreateClass();
	for(c = classes.begin(); c != classes.end(); c++ )
	{
		::Uml::Class cl = *c;
		output << "\t\t\t" << cl.name() << "::meta = ::Uml::CreateClass();" << endl;
	}

//	A::meta_a = Uml::CreateAttribute();
	for(c = classes.begin(); c != classes.end(); c++ )	
	{
		::Uml::Class cl = *c;
//		::Uml::Class tempcl(::Uml::ClassByName(tempdiagram, cl.name()));
		set< ::Uml::Attribute> attributes = cl.attributes();
/*		if(tempcl) {
			set< ::Uml::Attribute> tatts = tempcl.attributes();
			attributes.insert(tatts.begin(), tatts.end());
		}*/
		for( set< ::Uml::Attribute>::iterator i = attributes.begin(); i != attributes.end(); i++) {
			output << "\t\t\t" << cl.name() << "::meta_" << (*i).name() << " = ::Uml::CreateAttribute();" << endl;
		}
	}

//	A::meta_dst = Uml::CreateAssociationRole();
	for(c = classes.begin(); c != classes.end(); c++ ) {
			::Uml::Class cl = *c;
			set< ::Uml::AssociationRole> assocs = cl.associationRoles();
			for( set< ::Uml::AssociationRole>::iterator i = assocs.begin(); i != assocs.end(); i++) {
				string aname(::Uml::MakeRoleName(Uml::theOther(*i)));
				output << "\t\t\t" << cl.name() << "::meta_" << aname << " = ::Uml::CreateAssociationRole();" << endl;
		}
	}

//	A::meta_parent = Uml::CreateCompositionParentRole();
	for(c = classes.begin(); c != classes.end(); c++ ) {
		::Uml::Class cl = *c;
		set< ::Uml::CompositionChildRole> children = cl.childRoles();
		for( set< ::Uml::CompositionChildRole>::iterator i = children.begin(); i != children.end(); i++) {
			string aname(::Uml::MakeRoleName(Uml::theOther(*i)));
			output << "\t\t\t" << cl.name() << "::meta_" << aname << " = ::Uml::CreateCompositionParentRole();" << endl;
		}
	}

//	A::meta_as = Uml::CreateCompositionChildRole();

	for(c = classes.begin(); c != classes.end(); c++ ) {
		::Uml::Class cl = *c;
		set< ::Uml::CompositionParentRole> children = cl.parentRoles();
		for( set< ::Uml::CompositionParentRole>::iterator i = children.begin(); i != children.end(); i++) {
			string aname(::Uml::MakeRoleName(Uml::theOther(*i)));
			output << "\t\t\t" << cl.name() << "::meta_" << aname << " = ::Uml::CreateCompositionChildRole();" << endl;
		}
	}
// A::meta_constraintname = Uml::CreateConstraint();
	for(c = classes.begin(); c != classes.end(); c++ ) 
	{
		::Uml::Class cl = *c;
		set< ::Uml::Constraint> constraints = cl.constraints();
		for( set< ::Uml::Constraint>::iterator i = constraints.begin(); i != constraints.end(); i++) 
			output << "\t\t\t" << cl.name() << "::meta_" << i->name() << " = ::Uml::CreateConstraint();" << endl;
	}

// A::meta_definitionname = Uml::CreateConstraintDefinition();
		
	for(c = classes.begin(); c != classes.end(); c++ ) 
	{
		::Uml::Class cl = *c;
		set< ::Uml::ConstraintDefinition> definitions = cl.definitions();
		for( set< ::Uml::ConstraintDefinition>::iterator i = definitions.begin(); i != definitions.end(); i++) 
			output << "\t\t\t" << cl.name() << "::meta_" << i->name() << " = ::Uml::CreateConstraintDefinition();" << endl;
	}

	output << "\t\t" << endl;
};



void GenerateMetaCPPInitMetaObjects(const set< ::Uml::Class> &classes, const string &meta_name, const ::Uml::Diagram& cross_dgr, ostream & output, bool isCrossDgr)
{
	set< ::Uml::Class>::const_iterator c;

	//Initialization of classes
//	Uml::InitClass(A::meta, diagram, "A", false);
	for(c = classes.begin(); c != classes.end(); c++ )
	{
		::Uml::Class cl = *c;
		string ster;
		if(((string)cl.stereotype()).length()) ster = string(", \"")+(string)cl.stereotype()+"\"";

		string from;
		if(((string)cl.from()).length()) from = string(", \"")+(string)cl.from()+"\"";

		output << "\t\t\t::Uml::InitClass(" << cl.name() << "::meta, " << meta_name << ", \"" <<
			cl.name() << "\", " << (cl.isAbstract() ? "true" : "false")<< ster << from  <<");" << endl;

	}
	output << "\t\t" << endl;

	//intialization of attributes, constraints, constraindefinitions, cross association class's association ends.
//	Uml::InitAttribute(A::meta_a, A::meta, "a", "String");
	for(c = classes.begin(); c != classes.end(); c++ )	
	{
		::Uml::Class cl = *c;
		set< ::Uml::Attribute> attributes = cl.attributes();
		for( set< ::Uml::Attribute>::iterator i = attributes.begin(); i != attributes.end(); i++) 
		{
			//reproduce the defval string array
			if (i->defvalue())
			{
				vector<string> dva = i->defvalue();
				output << "\t\t\tvector<string> " << cl.name() << "_" << (*i).name() << "_dva;" <<endl;;

				vector<string>::const_iterator dva_ci = dva.begin();
	
				while (dva_ci != dva.end())
				{
					output << "\t\t\t" << cl.name() << "_" << (*i).name() << "_dva.push_back(\"" << *dva_ci++ << "\");" << endl; 
				};
				output << "\t\t\t::Uml::InitAttribute(" << cl.name() << "::meta_" << (*i).name() << ", " <<
					cl.name() << "::meta, \"" << (*i).name() << "\", \"" << (*i).type() << "\", " <<
					((*i).nonpersistent() ? "true" : "false") << ", " << ((*i).registry() ? "true" : "false") << ", " << (*i).min() << ", " << (*i).max() << ", " <<  
					((*i).ordered() ? "true" : "false") << ", \"" << (*i).visibility() <<
					"\", " << cl.name() << "_" << (*i).name() << "_dva" << ");" << endl;
			}
			else
			{
				output << "\t\t\t::Uml::InitAttribute(" << cl.name() << "::meta_" << (*i).name() << ", " <<
					cl.name() << "::meta, \"" << (*i).name() << "\", \"" << (*i).type() << "\", " <<
					((*i).nonpersistent() ? "true" : "false") << ", " << ((*i).registry() ? "true" : "false") << ", " << (*i).min() << ", " << (*i).max() << ", " <<  
					((*i).ordered() ? "true" : "false") << ", \"" << (*i).visibility() <<
					"\");" << endl;
			}
		}

		//constraints
		//(const Constraint &obj, const Class &parent, const char * name, const char * description, const char * expression);
		set< ::Uml::Constraint> constraints = cl.constraints();
		for( set< ::Uml::Constraint>::iterator j = constraints.begin(); j != constraints.end(); j++) 
		{
			output << "\t\t\t::Uml::InitConstraint(" << cl.name() << "::meta_" << j->name() << ", " <<
				cl.name() << "::meta, \"" << j->name() <<"\", \"" << j->description() << "\", \"" <<
				j->expression() << "\");" << endl;;
		}


		//constraint definitions
		//(const ConstraintDefinition &obj, const Class &parent, const char * name, const char * stereotype, 
		//const char * parameterList, const char * expression, const char * returnType);
		set< ::Uml::ConstraintDefinition> defs = cl.definitions();
		for( set< ::Uml::ConstraintDefinition>::iterator k = defs.begin(); k != defs.end(); k++) 
		{
			output << "\t\t\t::Uml::InitConstraintDefinition(" << cl.name() << "::meta_" << k->name() << ", " <<
				cl.name() << "::meta, \"" << k->name() <<"\", \"" << k->stereotype() << "\", \"" <<
				k->parameterList() << "\", \"" << k->expression() << "\", \"" << k->returnType() << "\");" << endl ;
		}

		//cross diagram - setting up cross-associationroles
		if (isCrossDgr)
		{
			::Uml::Class cross_cl;
			::Uml::Association ass;
			if (cross_dgr)
			{
				//--//cross_cl = ::Uml::ClassByName(cross_dgr, cl.name());
				cross_cl = GetCrossClass(cross_dgr, cl);
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
						<< cross_dgr.name() << "::" << ((::Uml::Class)((::Uml::theOther(*asrs_i)).target())).name()<<"::meta_" << asrs_i->name() << ";" <<endl;
					asrs_i++;
				}
			};
		}
	}
	output << "\t\t" << endl;
};

void GenerateMetaCPPInitAssociations(const set< ::Uml::Association> & asss, const string &meta_name, ostream & output)
{
	//initialization of associations
	{
		set< ::Uml::Association>::const_iterator a;
		for(a = asss.begin(); a != asss.end(); a++ )	
		{
			set< ::Uml::AssociationRole> ar = a->roles();
			ASSERT(ar.size() == 2);
			output << "\t\t\t{" << endl;
			output << "\t\t\t\t::Uml::Association ass = ::Uml::CreateAssociation();" << endl;

			::Uml::Class aclass = a->assocClass();
			output << "\t\t\t\t::Uml::InitAssociation(ass , " << meta_name << ", \"" << a->name() << "\");" << endl;
			if(aclass) 
			{
				output << "\t\t\t\t::Uml::InitAssociationClass(ass, " << aclass.name() << "::meta);" << endl;
			}

			set< ::Uml::AssociationRole> roles = a->roles();
			for( set< ::Uml::AssociationRole>::iterator i = roles.begin(); i != roles.end(); i++) 
			{
					::Uml::AssociationRole zz	= Uml::theOther(*i);
					string aname(::Uml::MakeRoleName(zz));
					::Uml::Class cl = i->target();
					output << "\t\t\t\t::Uml::InitAssociationRole(" << cl.name() << "::meta_" << aname 
						<< ", ass, \"" << aname << "\", " <<
						(zz.isNavigable() ? "true, " : "false, ") <<
						(zz.isPrimary() ? "true, " : "false, ") <<
						zz.min() << ", " << zz.max() << ", " << ((::Uml::Class)zz.target()).name() << "::meta);" << endl;
					::Uml::Class aclass = a->assocClass();
					if(aclass) 
					{
						::Uml::Class cl2 = zz.target();
						output << "\t\t\t\t" << aclass.name() << "::meta_" << aname << "_end_ = " <<
											cl2.name() << "::meta_" << ::Uml::MakeRoleName(*i) << "_rev = " << 
											cl.name() << "::meta_" << aname << ";" << endl;
					}
			}		
			output << "\t\t\t}" << endl;
		}
	}
};

void GenerateMetaCPPInitCompositions(const set< ::Uml::Composition> & comps, const string &meta_name, ostream & output)
{
	//initialization of compositions
	set< ::Uml::Composition>::const_iterator c;
	for(c = comps.begin(); c != comps.end(); c++ )	
	{
		output << "\t\t\t{" << endl;
		::Uml::Composition comp = Uml::CreateComposition();
		output << "\t\t\t\t::Uml::Composition comp = ::Uml::CreateComposition();" << endl;

		
		output << "\t\t\t\t::Uml::InitComposition(comp , " << meta_name << ", \"" <<  c->name() << "\");" <<  endl;
		output << "\t\t\t" << endl;

		::Uml::CompositionParentRole x1 = (*c).parentRole();
		::Uml::CompositionChildRole x2 = (*c).childRole();

		::Uml::CompositionParentRole zzp = c->parentRole();
		::Uml::CompositionChildRole zzc = c->childRole();
		string aname(::Uml::MakeRoleName(zzp));
		
		output << "\t\t\t\t::Uml::InitCompositionParentRole(" << ((::Uml::Class)zzc.target()).name() << "::meta_" << aname << 
		", comp, \""<< aname << "\", " << (zzp.isNavigable() ? "true, " : "false, ") <<
		((::Uml::Class)zzp.target()).name() << "::meta);" << endl;
						
		string cname(::Uml::MakeRoleName(zzc));
		output << "\t\t\t\t::Uml::InitCompositionChildRole(" << ((::Uml::Class)zzp.target()).name() << "::meta_" << cname << 
			", comp, \""<< ::Uml::MakeShortRoleName(zzc) << "\", " << (zzc.isNavigable() ? "true, " : "false, ") <<
			zzc.min() << ", " << zzc.max() << ", " << ((::Uml::Class)zzc.target()).name() << "::meta);" << endl;
	
		output << "\t\t\t}" << endl;
	}
};

void GenerateMetaCPPInitCrossAssociations(const set< ::Uml::Class> & classes, const ::Uml::Diagram & cross_dgr, ostream & output, bool isCrossDgr)
{
	set< ::Uml::Class>::const_iterator c;
	//cross-association role equiv. generation
	if (isCrossDgr)
	{
		//		M2::meta_src = CL::M2::meta_src;		
		for(c = classes.begin(); c != classes.end(); c++ )	
		{
			::Uml::Class cl = *c;
			::Uml::Class cross_cl;
			if (cross_dgr)
			{
				//--//cross_cl = ::Uml::ClassByName(cross_dgr, cl.name());
				cross_cl = GetCrossClass(cross_dgr, cl);
			}
			if (cross_cl)
			{
				set< ::Uml::AssociationRole> ar = cross_cl.associationRoles();
				set< ::Uml::AssociationRole>::iterator ar_i = ar.begin();
				while (ar_i != ar.end())
				{
					output << "\t\t"  <<cl.name() << "::meta_"<<Uml::theOther((*ar_i)).name() << 
						" = " << cross_dgr.name()<< "::" << cross_cl.name() << "::meta_"<<Uml::theOther((*ar_i)).name()<< ";" <<endl;
					::Uml::AssociationRole zz	= Uml::theOther(*ar_i);
					string aname(::Uml::MakeRoleName(zz));
					::Uml::Association ass = ar_i->parent();
					::Uml::Class a_class = ass.assocClass();
						
					if(a_class) 
					{
						::Uml::Class cl2 = zz.target();
						//output << "\t\t" << a_class.from() <<"::" << a_class.name() << "::meta_" << aname << "_end_ = " <<
						//					cl2.from() << "::" << cl2.name() << "::meta_" << ::Uml::MakeRoleName(*ar_i) << "_rev = " << 
						//					cl.name() << "::meta_" << aname << ";" << endl;

						output << "\t\t" << cross_cl.name() << "::meta_"<<Uml::theOther((*ar_i)).name() << 
						"_rev = " << cross_dgr.name()<< "::" << cl2.name() << "::meta_"<<ar_i->name()<< ";" <<endl;

					}
					ar_i++;
				}
			}
		}
	}
};

void GenerateMetaCPPInitInheritance(const set< ::Uml::Class> &classes, ostream & output)
{
	//Uml::AddInheritance(A::meta, C::meta);
	
	set< ::Uml::Class>::const_iterator c;
	
	for(c = classes.begin(); c != classes.end(); c++ ) 
	{
		::Uml::Class cl = *c;
		set< ::Uml::Class> st = cl.subTypes();
		for( set< ::Uml::Class>::iterator i = st.begin(); i != st.end(); i++) 
		{
			output << "\t\t\t::Uml::AddInheritance(" << cl.name() << "::meta, " << (*i).name() << "::meta);" << endl;
		}
	}			
};

void GenerateMetaCPPInitialize(const ::Uml::Namespace & ns, const ::Uml::Diagram & cross_dgr, ostream & output, const string& macro, const string& hname, bool isCrossDgr)
{
		//Generate the InitializeNS() function

	output << "\t\t" << macro << " void InitializeNS()" << endl << "\t\t{" << endl;
/*
	output << "\t\tstatic bool first = true;" << endl;
	output << "\t\tif(!first) return;" << endl;
	output << "\t\tfirst = false;" << endl;
	output << "\t\tUml::Initialize();" << endl << endl;

	//if (cross_dgr && (diagram != cross_dgr))
	if (isCrossDgr)
	output << "\t\t" << cross_dgr.name() << "::Initialize();" << endl << endl;


	output << "\t\tASSERT( umldiagram == Udm::null );" << endl;

	//Creating part
	output << "\t\tumldiagram = Uml::CreateDiagram();" << endl << endl;*/
	GenerateMetaCPPCreates(ns.classes(), output);

	//Initialization part

	//Uml::InitDiagram(diagram, "Sample");
	//output << "\t\tUml::InitNamespace(meta, \"" << hname << "\", \"" << diagram.version() << "\");" << endl << endl;

	//here: build the meta objects
	GenerateMetaCPPInitMetaObjects(ns.classes(), "meta", cross_dgr, output, isCrossDgr);
	

	//build the association and composition relationships
	GenerateMetaCPPInitAssociations(ns.associations(), "meta", output);
	GenerateMetaCPPInitCompositions(ns.compositions(), "meta", output);

	//build the cross association objects
	GenerateMetaCPPInitCrossAssociations(ns.classes(), cross_dgr, output, isCrossDgr);

	//build the inheritence relationship
	GenerateMetaCPPInitInheritance(ns.classes(), output);
	
	output << "\t\t\t" << endl << "\t\t}" << endl;
};

void GenerateMetaCPPInitialize(const ::Uml::Diagram & dgr, const ::Uml::Diagram & cross_dgr, ostream & output, const string& macro, const string& hname, bool isCrossDgr)
{
		//Generate the InitializeDgr() function

	output << "\t" << macro << " void InitializeDgr()" << endl << "\t{" << endl;
	GenerateMetaCPPCreates(dgr.classes(), output);

	//here: build the meta objects
	GenerateMetaCPPInitMetaObjects(dgr.classes(), "umldiagram", cross_dgr, output, isCrossDgr);
	

	//build the association and composition relationships
	GenerateMetaCPPInitAssociations(dgr.associations(), "umldiagram", output);
	GenerateMetaCPPInitCompositions(dgr.compositions(), "umldiagram", output);

	//build the cross association objects
	GenerateMetaCPPInitCrossAssociations(dgr.classes(), cross_dgr, output, isCrossDgr);

	//build the inheritence relationship
	GenerateMetaCPPInitInheritance(dgr.classes(), output);
	
	output << "\t\t" << endl << "\t}" << endl;
};

void GenerateMetaCPPDiagramInitialize(const ::Uml::Diagram &dgr, 
									  const ::Uml::Diagram & cross_dgr, 
									  ostream & output, 
									  const string& macro,
									  bool integrate_xsd)
{
	//Generate the Initialize() function

	output << "\t" << macro << " void Initialize()" << endl << "\t{" << endl;

	output << "\t\tstatic bool first = true;" << endl;
	output << "\t\tif(!first) return;" << endl;
	output << "\t\tfirst = false;" << endl;
	output << "\t\t::Uml::Initialize();" << endl << endl;

	if (cross_dgr && (dgr != cross_dgr))
		output << "\t\t" << cross_dgr.name() << "::Initialize();" << endl << endl;


	output << "\t\tASSERT( umldiagram == Udm::null );" << endl;

	//Creating part
	output << "\t\tumldiagram = ::Uml::CreateDiagram();" << endl;

	set< ::Uml::Namespace> nses = dgr.namespaces();
	for (set< ::Uml::Namespace>::iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
	{
		output << "\t\t" << endl;
		::Uml::Namespace ns = *nses_i;
		output << "\t\t" << ns.name() << "::meta = ::Uml::CreateNamespace();" <<endl;
		output << "\t\t" << ns.name() << "::InitializeNS();" <<endl;
		output << "\t\t::Uml::InitNamespace("<< ns.name() << "::meta, umldiagram,\"" << ns.name() <<  "\");" <<endl;
	}

	output << endl;
	output << "\t\tInitializeDgr();" << endl << endl;

	if (integrate_xsd)
		CPPSetXsdStorage(dgr, output);

	output << "\t\t::Uml::InitDiagram(umldiagram, \"" << dgr.name() << "\", \"" << dgr.version() << "\");" <<endl;
	output << "\t}" << endl;
};

void GenerateCPP(const ::Uml::Diagram &diagram,
				 ostream &output, string fname, 
				 const ::Uml::Diagram& cross_dgr, 
				 const string& macro,
				 bool integrate_xsd) 
{
		string hname = diagram.name();
		string::iterator i;
		for(i = hname.begin(); i != hname.end(); i++) {
			if(!isalnum(*i)) *i = '_';
		}

		output << "// cpp source file " << fname << ".cpp generated from diagram " << (string)diagram.name() << endl;
		output << "// generated on " << GetTime().c_str() << endl << endl;
		output << "#include \""<< fname << ".h\"" <<endl;
		output << "#include \"UmlExt.h\"" <<endl << endl; 
//		output << "#include \"UdmStatic.h\"" << endl << endl; 

		if (integrate_xsd)
			CPPIncludeXsdHeaders(diagram, output);


		bool isCrossDgr = (cross_dgr && (diagram != cross_dgr));
		if (isCrossDgr)
		{
			output << "// cross-package metainformation header file" << endl;
			output << "#include \"" << cross_dgr.name() << ".h\"" << endl << endl; 
		}

		output << "namespace " << fname << " {" << endl << endl;
		output << "\t::Uml::Diagram umldiagram;" << endl << endl;

		//declarations inside the diagram
		GenerateCPPDeclareMetaClasses(diagram.classes(), output);
		GenerateCPPDeclareAttributes(diagram.classes(), output);
		GenerateCPPDeclareAssociationRoles(diagram.classes(), cross_dgr, output, isCrossDgr);
		GenerateCPPDeclareCompositionRoles(diagram.classes(), output);
		GenerateCPPDeclareConstraints(diagram.classes(), output);
	
		//initialize function for diagram
		GenerateMetaCPPInitialize(diagram, cross_dgr, output, macro, hname, isCrossDgr);


		bool single_cpp_namespace = SingleCPPNamespace(diagram);
		set< ::Uml::Namespace> nses = diagram.namespaces();
		
		for (set< ::Uml::Namespace>::iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
		{
			::Uml::Namespace ns = *nses_i;
				//begin of namespace
			if (!single_cpp_namespace)
				output << "\tnamespace " << ns.name() << " {" << endl << endl;
			
			output << "\t\t::Uml::Namespace meta;" << endl<< endl;

			//declarations inside the namespace
			GenerateCPPDeclareMetaClasses(ns.classes(), output);
			GenerateCPPDeclareAttributes(ns.classes(), output);
			GenerateCPPDeclareAssociationRoles(ns.classes(), cross_dgr, output, isCrossDgr);
			GenerateCPPDeclareCompositionRoles(ns.classes(), output);
			GenerateCPPDeclareConstraints(ns.classes(), output);
	
			//initialize function
			GenerateMetaCPPInitialize(ns, cross_dgr, output, macro, hname, isCrossDgr);
		

			//end of namespace
			if (!single_cpp_namespace)
				output << "\t}// END namespace " << ns.name()  <<endl;

		};

		GenerateMetaCPPDiagramInitialize(diagram, cross_dgr, output, macro, integrate_xsd);

		//Udm::UdmDiagram declaration
		output << "\t" << macro << " Udm::UdmDiagram diagram = { &umldiagram, Initialize };" << endl;
		//static registrator class
		GenerateCPPStaticClass(diagram, output);

		//end of diagram
		output << "}" << endl <<"// END " << hname << ".cpp" <<endl;
		
	
}

