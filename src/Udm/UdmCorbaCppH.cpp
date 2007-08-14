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
	11/26/04	-	kalmar

			Fixed some syntax errors in the generated code

	11/20/04	-	endre

			Changed the code generator to split the generated code in more functions to avoid C1509 compiler limit errors.

	06/17/04	-	kalmar
			
			Changed the GenerateCORBACPP to generate cross link related code
*/

#include "Uml.h"
#include "UmlExt.h"
#include <time.h>
#include <map>
#include "Udm.h"

// assign a name to a role
// if name is assigned, use that name
// otherwise, if navigable, get the peer class name and append _assoc, _parent, _child or _children 
//									(for _parent, prepend ChildRole name, if applicable)
//			  if not navigable, name is arolexxx, prolexxx, or crolexxx, where xxx is the uniqueid


/*
	Functions used to generate Initialize()
	They are defined here.
*/
void GenerateCORBACPPCreates(const set< ::Uml::Class> &classes, ostream &output)
{
	set< ::Uml::Class>::const_iterator c;
	//	A::meta = Uml::CreateClass();
	for(c = classes.begin(); c != classes.end(); c++ )
	{
		::Uml::Class cl = *c;
		output << "\t\t\t" << cl.name() << "::meta = ::Uml::CreateCORBAClass();" << endl;
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
			output << "\t\t\t" << cl.name() << "::meta_" << (*i).name() << " = ::Uml::CreateCORBAAttribute();" << endl;
		}
	}

//	A::meta_dst = Uml::CreateAssociationRole();
	for(c = classes.begin(); c != classes.end(); c++ ) {
			::Uml::Class cl = *c;
			set< ::Uml::AssociationRole> assocs = cl.associationRoles();
			for( set< ::Uml::AssociationRole>::iterator i = assocs.begin(); i != assocs.end(); i++) {
				string aname(::Uml::MakeRoleName(Uml::theOther(*i)));
				output << "\t\t\t" << cl.name() << "::meta_" << aname << " = ::Uml::CreateCORBAAssociationRole();" << endl;
		}
	}

//	A::meta_parent = Uml::CreateCompositionParentRole();
	for(c = classes.begin(); c != classes.end(); c++ ) {
		::Uml::Class cl = *c;
		set< ::Uml::CompositionChildRole> children = cl.childRoles();
		for( set< ::Uml::CompositionChildRole>::iterator i = children.begin(); i != children.end(); i++) {
			string aname(::Uml::MakeRoleName(Uml::theOther(*i)));
			output << "\t\t\t" << cl.name() << "::meta_" << aname << " = ::Uml::CreateCORBACompositionParentRole();" << endl;
		}
	}

//	A::meta_as = Uml::CreateCompositionChildRole();

	for(c = classes.begin(); c != classes.end(); c++ ) {
		::Uml::Class cl = *c;
		set< ::Uml::CompositionParentRole> children = cl.parentRoles();
		for( set< ::Uml::CompositionParentRole>::iterator i = children.begin(); i != children.end(); i++) {
			string aname(::Uml::MakeRoleName(Uml::theOther(*i)));
			output << "\t\t\t" << cl.name() << "::meta_" << aname << " = ::Uml::CreateCORBACompositionChildRole();" << endl;
		}
	}
};

void GenerateCORBACPPInitMetaObjects(const set< ::Uml::Class> &classes, const string &meta_name, const ::Uml::Diagram& cross_dgr, ostream & output, bool isCrossDgr)
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

		output << "\t\t\t::Uml::InitCORBAClass(" << cl.name() << "::meta, " << meta_name << ", \"" <<
			cl.name() << "\", " << (cl.isAbstract() ? "true" : "false")<< ster << from  <<");" << endl;

	}
	output << "\t\t" << endl;

	//intialization of attributes, cross association class's association ends.
//	Uml::InitAttribute(A::meta_a, A::meta, "a", "String");
	for(c = classes.begin(); c != classes.end(); c++ )	
	{
		::Uml::Class cl = *c;
		set< ::Uml::Attribute> attributes = cl.attributes();
		for( set< ::Uml::Attribute>::iterator i = attributes.begin(); i != attributes.end(); i++) 
		{
			//reproduce the defval string array

			vector<string> dva = i->defvalue();
			output << "\t\t\tvector<string> " << cl.name() << "_" << (*i).name() << "_dva;" <<endl;;

			vector<string>::const_iterator dva_ci = dva.begin();

			while (dva_ci != dva.end())
			{
				output << "\t\t\t" << cl.name() << "_" << (*i).name() << "_dva.push_back(\"" << *dva_ci++ << "\");" << endl; 
			};

			output << "\t\t\t::Uml::InitCORBAAttribute(" << cl.name() << "::meta_" << (*i).name() << ", " <<
				cl.name() << "::meta, \"" << (*i).name() << "\", \"" << (*i).type() << "\", " <<
				((*i).nonpersistent() ? "true" : "false") << ", " << (*i).min() << ", " << (*i).max() << ", " <<  
				((*i).ordered() ? "true" : "false") << ", \"" << (*i).visibility() <<
				"\", " << cl.name() << "_" << (*i).name() << "_dva" << ");" << endl;
		}

		//cross diagram - setting up cross-associationroles
		if (isCrossDgr)
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
	output << "\t\t" << endl;
};

int GenerateCORBACPPInitAssociations(const set< ::Uml::Association> & asss, const string &meta_name, ostream & output)
{
	//initialization of associations
	int associations = 0;
	{
		set< ::Uml::Association>::const_iterator a;
		for(a = asss.begin(); a != asss.end(); a++ )	
		{
			set< ::Uml::AssociationRole> ar = a->roles();
			ASSERT(ar.size() == 2);

			output << "\t\tvoid InitAssociation" << associations++ << "()" << endl << "\t\t{" << endl;
			output << "\t\t\t::Uml::Association ass = ::Uml::CreateCORBAAssociation();" << endl;

			::Uml::Class aclass = a->assocClass();
			output << "\t\t\t::Uml::InitCORBAAssociation(ass , " << meta_name << ", \"" << a->name() << "\");" << endl;
			if(aclass) 
			{
				output << "\t\t\t::Uml::InitCORBAAssociationClass(ass, " << UmlClassCPPName(aclass) << "::meta);" << endl;
			}

			set< ::Uml::AssociationRole> roles = a->roles();
			for( set< ::Uml::AssociationRole>::iterator i = roles.begin(); i != roles.end(); i++) 
			{
					::Uml::AssociationRole zz	= Uml::theOther(*i);
					string aname(::Uml::MakeRoleName(zz));
					::Uml::Class cl = i->target();
					output << "\t\t\t::Uml::InitCORBAAssociationRole(" << UmlClassCPPName(cl) << "::meta_" << aname 
						<< ", ass, \"" << aname << "\", " <<
						(zz.isNavigable() ? "true, " : "false, ") <<
						(zz.isPrimary() ? "true, " : "false, ") <<
						zz.min() << ", " << zz.max() << ", " << UmlClassCPPName((::Uml::Class)zz.target()) << "::meta);" << endl;
					::Uml::Class aclass = a->assocClass();
					if(aclass) 
					{
						::Uml::Class cl2 = zz.target();
						output << "\t\t\t" << UmlClassCPPName(aclass) << "::meta_" << aname << "_end_ = " <<
											UmlClassCPPName(cl2) << "::meta_" << ::Uml::MakeRoleName(*i) << "_rev = " << 
											UmlClassCPPName(cl) << "::meta_" << aname << ";" << endl;
					}
			}		
			output << "\t\t};" << endl << endl;
		}
	}

	return associations;
};

int GenerateCORBACPPInitCompositions(const set< ::Uml::Composition> & comps, const string &meta_name, ostream & output)
{
	//initialization of compositions
	int compositions = 0;
	set< ::Uml::Composition>::const_iterator c;
	for(c = comps.begin(); c != comps.end(); c++ )	
	{
		output << "\t\tvoid InitComposition" << compositions++ << "()" << endl <<"\t\t{" << endl;

		::Uml::Composition comp = Uml::CreateComposition();
		output << "\t\t\t::Uml::Composition comp = ::Uml::CreateCORBAComposition();" << endl;

		
		output << "\t\t\t::Uml::InitCORBAComposition(comp , " << meta_name << ", \"" <<  c->name() << "\");" <<  endl;
		output << "\t\t" << endl;

		::Uml::CompositionParentRole x1 = (*c).parentRole();
		::Uml::CompositionChildRole x2 = (*c).childRole();

		::Uml::CompositionParentRole zzp = c->parentRole();
		::Uml::CompositionChildRole zzc = c->childRole();
		string aname(::Uml::MakeRoleName(zzp));
		
		output << "\t\t\t::Uml::InitCORBACompositionParentRole(" << UmlClassCPPName((::Uml::Class)zzc.target()) << "::meta_" << aname << 
		", comp, \""<< aname << "\", " << (zzp.isNavigable() ? "true, " : "false, ") <<
		UmlClassCPPName((::Uml::Class)zzp.target()) << "::meta);" << endl;
						
		string cname(::Uml::MakeRoleName(zzc));
		output << "\t\t\t::Uml::InitCORBACompositionChildRole(" << UmlClassCPPName((::Uml::Class)zzp.target()) << "::meta_" << cname << 
			", comp, \""<< ::Uml::MakeShortRoleName(zzc) << "\", " << (zzc.isNavigable() ? "true, " : "false, ") <<
			zzc.min() << ", " << zzc.max() << ", " << UmlClassCPPName((::Uml::Class)zzc.target()) << "::meta);" << endl;
	
		output << "\t\t};" << endl << endl;
	}

	return compositions;
};

void GenerateCORBACPPInitCrossAssociations(const set< ::Uml::Class> & classes, const ::Uml::Diagram & cross_dgr, ostream & output, bool isCrossDgr)
{
	set< ::Uml::Class>::const_iterator c;
	//cross-association role equiv. generation
	if (isCrossDgr)
	{
		output << "\t\tvoid InitCrossAssociations()" << endl << "\t\t{" << endl;

		//		M2::meta_src = CL::M2::meta_src;		
		for(c = classes.begin(); c != classes.end(); c++ )	
		{
			::Uml::Class cl = *c;
			::Uml::Class cross_cl;
			if (cross_dgr)
			{
				//--//cross_cl = ::Uml::ClassByName(cross_dgr, cl.name());
				cross_cl = ::Uml::GetClassFromCrossDgr(cross_dgr, cl);
			}
			if (cross_cl)
			{
				set< ::Uml::AssociationRole> ar = cross_cl.associationRoles();
				set< ::Uml::AssociationRole>::iterator ar_i = ar.begin();
				while (ar_i != ar.end())
				{
					output << "\t\t\t"  << UmlClassCPPName(cl) << "::meta_"<<Uml::theOther((*ar_i)).name() << 
						" = " << UmlClassCPPName(cross_cl) << "::meta_"<<Uml::theOther((*ar_i)).name()<< ";" <<endl;
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

						output << "\t\t\t" << UmlClassCPPName(cross_cl) << "::meta_"<<Uml::theOther((*ar_i)).name() << 
						"_rev = " << UmlClassCPPName(cl2) << "::meta_"<<ar_i->name()<< ";" <<endl;

					}
					ar_i++;
				}
			}
		}
		output << "\t\t};" << endl << endl;
	}
};

void GenerateCORBACPPInitInheritance(const set< ::Uml::Class> &classes, ostream & output)
{
	//Uml::AddInheritance(A::meta, C::meta);
	
	set< ::Uml::Class>::const_iterator c;
	
	for(c = classes.begin(); c != classes.end(); c++ ) 
	{
		::Uml::Class cl = *c;
		set< ::Uml::Class> st = cl.subTypes();
		for( set< ::Uml::Class>::iterator i = st.begin(); i != st.end(); i++) 
		{
			output << "\t\t\t::Uml::AddCORBAInheritance(" << cl.name() << "::meta, " << UmlClassCPPName(*i) << "::meta);" << endl;
		}
	}			
};

void GenerateCORBACPPInitialize(const ::Uml::Namespace & ns, const ::Uml::Diagram & cross_dgr, ostream & output, const string& macro, const string& hname, bool isCrossDgr)
{
		//Generate the Inits() function

	output << "\t\tvoid Inits()" << endl << "\t\t{" << endl;

	output << "\t\t\t::Uml::InitCORBANamespace(meta, umldiagram, \"" << ns.name() << "\");" << endl << endl;

	//here: build the meta objects
	GenerateCORBACPPInitMetaObjects(ns.classes(), "meta", cross_dgr, output, isCrossDgr);

	output << "\t\t};" << endl << endl;


	//build the association and composition relationships
	int associations = GenerateCORBACPPInitAssociations(ns.associations(), "meta", output);
	int compositions = GenerateCORBACPPInitCompositions(ns.compositions(), "meta", output);

	//build the cross association objects
	GenerateCORBACPPInitCrossAssociations(ns.classes(), cross_dgr, output, isCrossDgr);


	output << "\t\t" << macro << " void InitializeNs()" << endl << "\t\t{" << endl;
	output << "\t\t\tCreates();" << endl;
	output << "\t\t\tInits();" << endl;

	for (int comp_i  = 0; comp_i < compositions; comp_i++) 
		output << "\t\t\tInitComposition" << comp_i << "();" << endl;

	for (int ass_i  = 0; ass_i < associations; ass_i++) 
		output << "\t\t\tInitAssociation" << ass_i << "();" << endl;

	if (isCrossDgr)
		output << "\t\t\tInitCrossAssociations();" << endl;

	//build the inheritence relationship
	GenerateCORBACPPInitInheritance(ns.classes(), output);

	output << endl << "\t\t};" << endl << endl;

};

void GenerateCORBACPPInitialize(const ::Uml::Diagram & dgr, const ::Uml::Diagram & cross_dgr, ostream & output, const string& macro, const string& hname, bool isCrossDgr)
{
		//Generate the Inits() function

	output << "\tvoid Inits()" << endl << "\t{" << endl;

	output << "\t\t::Uml::InitCORBADiagram(umldiagram, \"" << hname << "\");" << endl << endl;

	//here: build the meta objects
	GenerateCORBACPPInitMetaObjects(dgr.classes(), "umldiagram", cross_dgr, output, isCrossDgr);

	output << "\t};" << endl << endl;


	//build the association and composition relationships
	int associations = GenerateCORBACPPInitAssociations(dgr.associations(), "umldiagram", output);
	int compositions = GenerateCORBACPPInitCompositions(dgr.compositions(), "umldiagram", output);

	//build the cross association objects
	GenerateCORBACPPInitCrossAssociations(dgr.classes(), cross_dgr, output, isCrossDgr);


	output << "\t" << macro << " void InitializeDgr()" << endl << "\t{" << endl;
	output << "\t\tCreates();" << endl;
	output << "\t\tInits();" << endl;

	for (int comp_i  = 0; comp_i < compositions; comp_i++) 
		output << "\t\tInitComposition" << comp_i << "();" << endl;

	for (int ass_i  = 0; ass_i < associations; ass_i++) 
		output << "\t\tInitAssociation" << ass_i << "();" << endl;

	if (isCrossDgr)
		output << "\t\tInitCrossAssociations();" << endl;

	//build the inheritence relationship
	GenerateCORBACPPInitInheritance(dgr.classes(), output);

	output << endl << "\t};" << endl << endl;
};

void GenerateCORBACPPDiagramInitialize(const ::Uml::Diagram &dgr, 
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

	output << "\t\tumldiagram = ::Uml::CreateCORBADiagram();" << endl;
	output << "\t\tInitializeDgr();" << endl << endl;

	set< ::Uml::Namespace> nses = dgr.namespaces();
	for (set< ::Uml::Namespace>::iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
	{
		output << "\t\t" << endl;
		::Uml::Namespace ns = *nses_i;
		output << "\t\t" << ns.name() << "::meta = ::Uml::CreateCORBANamespace();" <<endl;
		output << "\t\t" << ns.name() << "::InitializeNS();" <<endl;
	}

	output << endl;

	output << "\t};" << endl;
};

//===========================
void GenerateCORBACPP(const ::Uml::Diagram &diagram,  ostream &output, string fname, const ::Uml::Diagram& cross_dgr , const string& macro ) 
{
		string hname = NameToFilename(diagram.name());


		output << "// cpp source file " << fname << ".cpp generated from diagram " << (string)diagram.name() << endl;
		output << "// generated on " << GetTime().c_str() << endl << endl;
		output << "#include \""<< fname << ".h\"" <<endl;
		output << "#include \"UmlExt.h\"" <<endl << endl; 

		bool isCrossDgr = (cross_dgr && (diagram != cross_dgr));

		if (isCrossDgr)
		{
			output << "// cross-package metainformation header file" << endl;
			output << "#include \"" << cross_dgr.name() << ".h\"" << endl << endl; 
		}


		output << "namespace " << hname << " {" << endl << endl;

//	Uml::Diagram diagram;
		output << "\t::Uml::Diagram umldiagram;" << endl << endl;

		//declarations inside the diagram
		GenerateCPPDeclareMetaClasses(diagram.classes(), output);
		GenerateCPPDeclareAttributes(diagram.classes(), output);
		GenerateCPPDeclareAssociationRoles(diagram.classes(), cross_dgr, output, isCrossDgr);
		GenerateCPPDeclareCompositionRoles(diagram.classes(), output);

		output << "\tvoid Creates()" << endl << "\t{" << endl;
		GenerateCORBACPPCreates(diagram.classes(), output);
		output << "\t};" << endl << endl;

		//initialize function for diagram
		GenerateCORBACPPInitialize(diagram, cross_dgr, output, macro, hname, isCrossDgr);


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

			output << "\t\tvoid Creates()" << endl << "\t\t{" << endl;
			GenerateCORBACPPCreates(ns.classes(), output);
			output << "\t\t};" << endl << endl;
	
			//initialize function
			GenerateCORBACPPInitialize(ns, cross_dgr, output, macro, hname, isCrossDgr);
		

			//end of namespace
			if (!single_cpp_namespace)
				output << "\t};// END namespace " << ns.name()  << endl << endl;

		};

		GenerateCORBACPPDiagramInitialize(diagram, cross_dgr, output, macro, false);

//	Udm::UdmDiagram diagram = { &umldiagram, Initialize };
		output << "\tUdm::UdmDiagram diagram = { &umldiagram, Initialize };" << endl;
		output << "};" << endl <<"// END " << hname << ".cpp" <<endl;
}
