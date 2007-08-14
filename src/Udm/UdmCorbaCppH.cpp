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
std::string GetTime();
#include <time.h>
#include <map>


// assign a name to a role
// if name is assigned, use that name
// otherwise, if navigable, get the peer class name and append _assoc, _parent, _child or _children 
//									(for _parent, prepend ChildRole name, if applicable)
//			  if not navigable, name is arolexxx, prolexxx, or crolexxx, where xxx is the uniqueid


//===========================
void GenerateCORBACPP(const ::Uml::Uml::Diagram &diagram,  ostream &output, string fname, const ::Uml::Uml::Diagram& cross_dgr , const string& macro ) 
{
		string hname = diagram.name();
		string::iterator i;
		for(i = hname.begin(); i != hname.end(); i++) 	if(!isalnum(*i)) *i = '_';


		output << "// cpp source file " << fname << ".cpp generated from diagram " << (string)diagram.name() << endl;
		output << "// generated on " << GetTime().c_str() << endl << endl;
		output << "#include \""<< fname << ".h\"" <<endl;
		output << "#include \"UmlExt.h\"" <<endl << endl; 

		if (cross_dgr && (diagram != cross_dgr))
		{
			output << "// cross-package metainformation header file" << endl;
			output << "#include \"" << cross_dgr.name() << ".h\"" << endl << endl; 
		}


		output << "namespace " << hname << " {" << endl << endl;

//	Uml::Diagram diagram;
		output << "\tUml::Diagram umldiagram;" << endl << endl;

//	Uml::Class A::meta;
		set< ::Uml::Uml::Class> classes = diagram.classes();
		set< ::Uml::Uml::Class>::iterator c;
		for(c = classes.begin(); c != classes.end(); c++ )
		{
			::Uml::Uml::Class cl = *c;
			output << "\tUml::Class " << cl.name() << "::meta;" << endl;

		}

//	Uml::Attribute A::meta_a;
		for(c = classes.begin(); c != classes.end(); c++ )	{
			::Uml::Uml::Class cl = *c;
//			Uml::Class tempcl(Uml::classByName(tempdiagram, cl.name()));
			set< ::Uml::Uml::Attribute> attributes = cl.attributes();
/*			if(tempcl) {
				set<Uml::Attribute> tatts = tempcl.attributes();
				attributes.insert(tatts.begin(), tatts.end());
			}
*/			for( set< ::Uml::Uml::Attribute>::iterator i = attributes.begin(); i != attributes.end(); i++) {
				output << "\tUml::Attribute " << cl.name() << "::meta_" << (*i).name() << ";" << endl;
			}
		}

//	Uml::AssociationRole A::meta_dst;
		for(c = classes.begin(); c != classes.end(); c++ ) 
		{
			::Uml::Uml::Class cl = *c;
			set< ::Uml::Uml::AssociationRole> assocs = cl.associationRoles();
			for( set< ::Uml::Uml::AssociationRole>::iterator i = assocs.begin(); i != assocs.end(); i++) 
			{
				::Uml::Uml::Association pp = (*i).parent();
				::Uml::Uml::Class aclass = pp.assocClass();
				string aname(MakeRoleName(Uml::theOther(*i)));
				if(!aclass)
				{
					output << "\tUml::AssociationRole " << cl.name() << "::meta_" << aname << ";" << endl;
				}
				else
				{
					output << "\tUml::AssociationRole " << cl.name() << "::meta_" << aname << ", " << cl.name() << "::meta_" << aname << "_rev;" << endl;
				}
			}

			if (cross_dgr &&(cross_dgr != diagram) )
			{
				//--//Uml::Class cross_cl = Uml::classByName(cross_dgr, cl.name());
				string cross_cl_name = string(cl.name()) + string(Udm::cross_delimiter) + string(diagram.name());
				::Uml::Uml::Class cross_cl = Uml::classByName(cross_dgr, cross_cl_name );
				if(cross_cl)
				{
					set< ::Uml::Uml::AssociationRole> assocs = cross_cl.associationRoles();
					for( set< ::Uml::Uml::AssociationRole>::iterator i = assocs.begin(); i != assocs.end(); i++) 
					{
						::Uml::Uml::Association pp = (*i).parent();
						::Uml::Uml::Class aclass = pp.assocClass();
						string aname(MakeRoleName(Uml::theOther(*i)));
						if(!aclass) 
						{
							output << "\tUml::AssociationRole " << cl.name() << "::meta_" << aname << ";" << endl;
						}
						else 
						{
							output << "\tUml::AssociationRole " << cl.name() << "::meta_" << aname << ", " << cl.name() << "::meta_" << aname << "_rev;" << endl;
						}
					}
				}
			 }

//	Uml::AssociationRole A::meta_End1_end_;

			::Uml::Uml::Association assoc = cl.association();
			string s = assoc.meta.name();
			if(assoc) 
			{
				set< ::Uml::Uml::AssociationRole> assocs = assoc.roles();
				for( set< ::Uml::Uml::AssociationRole>::iterator i = assocs.begin(); i != assocs.end(); i++) 
				{
					string aname(MakeRoleName(*i));
					string oname(((::Uml::Uml::Class)(*i).target()).name());
					if(aname.size()) 
					{
					      output << "\tUml::AssociationRole " << cl.name() << "::meta_" << aname << "_end_;" << endl;
					}
				}
			}

			if (cross_dgr &&(cross_dgr != diagram) )
			{
				//--//Uml::Class cross_cl = Uml::classByName(cross_dgr, cl.name());
				::Uml::Uml::Class cross_cl = Uml::classByName(cross_dgr, (string(cl.name()) + string(Udm::cross_delimiter) + string(diagram.name())) );
				if(cross_cl)
				{
					Uml::Association assoc = cross_cl.association();
					string s = assoc.meta.name();
					if(assoc) 
					{
						set<Uml::AssociationRole> assocs = assoc.roles();
						for( set<Uml::AssociationRole>::iterator i = assocs.begin(); i != assocs.end(); i++) 
						{
							string aname(MakeRoleName(*i));
							string oname(((Uml::Class)(*i).target()).name());
							if(aname.size()) 
							{
								output << "\tUml::AssociationRole " << cl.name() << "::meta_" << aname << "_end_;" << endl;
							}
						}
					}
				}
			}
		}//end for cycle for declaration for associationRoles

		

//	Uml::CompositionParentRole A::meta_parent;
		for(c = classes.begin(); c != classes.end(); c++ ) 
		{
			Uml::Class cl = *c;
			set<Uml::CompositionChildRole> children = cl.childRoles();
			for( set<Uml::CompositionChildRole>::iterator i = children.begin(); i != children.end(); i++) 
			{
				string aname(MakeRoleName(Uml::theOther(*i)));
				output << "\tUml::CompositionParentRole " << cl.name() << "::meta_" << aname << ";" << endl;
			}
		}

//	Uml::CompositionChildRole D::meta_as;

		for(c = classes.begin(); c != classes.end(); c++ ) 
		{
			Uml::Class cl = *c;
			set<Uml::CompositionParentRole> children = cl.parentRoles();
			for( set<Uml::CompositionParentRole>::iterator i = children.begin(); i != children.end(); i++) 
			{
				string aname(MakeRoleName(Uml::theOther(*i)));
				output << "\tUml::CompositionChildRole " << cl.name() << "::meta_" << aname << ";" << endl;
			}
		}


		output << "\tvoid Creates()" << endl << "\t{" << endl;
		
//	A::meta = Uml::CreateClass();
		for(c = classes.begin(); c != classes.end(); c++ )
		{
			Uml::Class cl = *c;
			output << "\t\t" << cl.name() << "::meta = Uml::CreateCORBAClass();" << endl;
		}

//	A::meta_a = Uml::CreateAttribute();
		for(c = classes.begin(); c != classes.end(); c++ )	
		{
			Uml::Class cl = *c;
//			Uml::Class tempcl(Uml::classByName(tempdiagram, cl.name()));
			set<Uml::Attribute> attributes = cl.attributes();
/*			if(tempcl) {
				set<Uml::Attribute> tatts = tempcl.attributes();
				attributes.insert(tatts.begin(), tatts.end());
			}
*/			for( set<Uml::Attribute>::iterator i = attributes.begin(); i != attributes.end(); i++) 
			{
				output << "\t\t" << cl.name() << "::meta_" << (*i).name() << " = Uml::CreateCORBAAttribute();" << endl;
			}
		}

//	A::meta_dst = Uml::CreateAssociationRole();
		for(c = classes.begin(); c != classes.end(); c++ ) 
		{
			Uml::Class cl = *c;
			set<Uml::AssociationRole> assocs = cl.associationRoles();
			for( set<Uml::AssociationRole>::iterator i = assocs.begin(); i != assocs.end(); i++) 
			{
					string aname(MakeRoleName(Uml::theOther(*i)));
					output << "\t\t" << cl.name() << "::meta_" << aname << " = Uml::CreateCORBAAssociationRole();" << endl;
			}
		}

//	A::meta_parent = Uml::CreateCompositionParentRole();
		for(c = classes.begin(); c != classes.end(); c++ ) 
		{
			Uml::Class cl = *c;
			set<Uml::CompositionChildRole> children = cl.childRoles();
			for( set<Uml::CompositionChildRole>::iterator i = children.begin(); i != children.end(); i++) 
			{
				string aname(MakeRoleName(Uml::theOther(*i)));
				output << "\t\t" << cl.name() << "::meta_" << aname << " = Uml::CreateCORBACompositionParentRole();" << endl;
			}
		}

//	A::meta_as = Uml::CreateCompositionChildRole();

		for(c = classes.begin(); c != classes.end(); c++ ) 
		{
			Uml::Class cl = *c;
			set<Uml::CompositionParentRole> children = cl.parentRoles();
			for( set<Uml::CompositionParentRole>::iterator i = children.begin(); i != children.end(); i++) 
			{
				string aname(MakeRoleName(Uml::theOther(*i)));
				output << "\t\t" << cl.name() << "::meta_" << aname << " = Uml::CreateCORBACompositionChildRole();" << endl;
			}
		}

		output << "\t};" << endl;

	

		output << "\tvoid Inits()" << endl << "\t{" << endl;

//		Uml::InitDiagram(diagram, "Sample");
		output << "\t\tUml::InitCORBADiagram(umldiagram, \"" << hname << "\");" << endl << endl;

//		Uml::InitClass(A::meta, diagram, "A", false);
//	A::meta = Uml::CreateClass();
		for(c = classes.begin(); c != classes.end(); c++ )
		{
			Uml::Class cl = *c;
			string ster;
			if(((string)cl.stereotype()).length()) ster = string(", \"")+(string)cl.stereotype()+"\"";

			string from;
			if(((string)cl.from()).length()) from= string(", \"")+(string)cl.from()+"\"";
			
			output << "\t\tUml::InitCORBAClass(" << cl.name() << "::meta, umldiagram, \"" <<
				cl.name() << "\", " << (cl.isAbstract() ? "true" : "false")<< ster << from << ");" << endl;

		}
		output << "\t\t" << endl;

//		Uml::InitAttribute(A::meta_a, A::meta, "a", "String");
		for(c = classes.begin(); c != classes.end(); c++ )
		{
			Uml::Class cl = *c;
//			Uml::Class tempcl(Uml::classByName(tempdiagram, cl.name()));
			set<Uml::Attribute> attributes = cl.attributes();


			for( set<Uml::Attribute>::iterator i = attributes.begin(); i != attributes.end(); i++) 
			{
				//reproduce the defval string array

				vector<string> dva = i->defvalue();
				output << "\t\tvector<string> " << cl.name() << "_" << (*i).name() << "_dva;" <<endl;;

				vector<string>::const_iterator dva_ci = dva.begin();
	
				while (dva_ci != dva.end())
				{
					output << "\t\t" << cl.name() << "_" << (*i).name() << "_dva.push_back(\"" << *dva_ci++ << "\");" << endl; 
				};


				output << "\t\tUml::InitCORBAAttribute(" << cl.name() << "::meta_" << (*i).name() << ", " <<
					cl.name() << "::meta, \"" << (*i).name() << "\", \"" << (*i).type() << "\", " <<
					((*i).nonpersistent() ? "true" : "false") << ", " << (*i).min() << ", " << (*i).max() << ", " <<  
					((*i).ordered() ? "true" : "false") << ", \"" << (*i).visibility() <<
					"\", " << cl.name() << "_" << (*i).name() << "_dva" << ");" << endl;
			}

			if (cross_dgr &&(cross_dgr != diagram))
			{
				Uml::Class cross_cl;
				Uml::Association ass;
				if (cross_dgr)
				{
					//--//cross_cl = Uml::classByName(cross_dgr, cl.name());
					cross_cl = Uml::classByName(cross_dgr, (string(cl.name()) + string(Udm::cross_delimiter) + string(diagram.name())) );
				}
				if (cross_cl)
					ass = cross_cl.association();
				if (ass)
				{
					set<Uml::AssociationRole> asrs = ass.roles();
					set<Uml::AssociationRole>::iterator asrs_i = asrs.begin();
					
					while (asrs_i != asrs.end())
					{

						output << " \t\t" << cl.name() << "::meta_" << asrs_i->name() << "_end_ = " 
							<< cross_dgr.name() << "::" << ((Uml::Class)((Uml::theOther(*asrs_i)).target())).name()<<"::meta_" << asrs_i->name() << ";" <<endl;
						asrs_i++;
					}
				};
			
			}
		}
//		output << "\t\t" << endl;

		output << "\t};" << endl;

		int compositions = 0;
		int associations = 0;


		{
			const set<Uml::Association> &asss = diagram.associations();
			set<Uml::Association>::const_iterator a;
			for(a = asss.begin(); a != asss.end(); a++ )	
			{
				set<Uml::AssociationRole> ar = a->roles();
				ASSERT(ar.size() == 2);
//	{
				output << "\tvoid InitAssociation" << associations++ << "()"<< endl << "\t{" << endl;
//		Uml::Association ass = Uml::CreateAssociation();
				output << "\t\tUml::Association ass = Uml::CreateCORBAAssociation();" << endl;

//		Uml::InitAssociation(ass, diagram, "AtoB");
// or : Uml::InitAssociationClass(ass, C::meta);
				Uml::Class aclass = a->assocClass();
				output << "\t\tUml::InitCORBAAssociation(ass , umldiagram, \"" << a->name() << "\");" << endl;
				if(aclass) 
				{
					output << "\t\tUml::InitCORBAAssociationClass(ass, " << aclass.name() << "::meta);" << endl;
				}

//		Uml::InitAssociationRole(A::meta_dst, ass, "dst", 0, 1, B::meta);
//								C:: meta_dst_end_ = B:meta_src_rev = A::meta_dst;
				set<Uml::AssociationRole> roles = a->roles();
				for( set<Uml::AssociationRole>::iterator i = roles.begin(); i != roles.end(); i++) 
				{
					Uml::AssociationRole zz	= Uml::theOther(*i);
					string aname(MakeRoleName(zz));
					Uml::Class cl = i->target();
					output << "\t\tUml::InitCORBAAssociationRole(" << cl.name() << "::meta_" << aname 
						<< ", ass, \"" << aname << "\", " <<
						(zz.isNavigable() ? "true, " : "false, ") <<
						(zz.isPrimary() ? "true, " : "false, ") <<
						zz.min() << ", " << zz.max() << ", " << ((Uml::Class)zz.target()).name() << "::meta);" << endl;
					Uml::Class aclass = a->assocClass();
					if(aclass) 
					{
						Uml::Class cl2 = zz.target();
						output << "\t\t" << aclass.name() << "::meta_" << aname << "_end_ = " <<
											cl2.name() << "::meta_" << MakeRoleName(*i) << "_rev = " << 
											cl.name() << "::meta_" << aname << ";" << endl;
					}
				}
//	}
				output << "\t};" << endl;
			}

			if (cross_dgr &&(cross_dgr != diagram))
			{
				output << "\tvoid InitAssociation" << associations++ << "()"<< endl << "\t{" << endl;


			//		M2::meta_src = CL::M2::meta_src;		

				for(c = classes.begin(); c != classes.end(); c++ )	
				{
					Uml::Class cl = *c;
					Uml::Class cross_cl;
					if (cross_dgr)
					{
						cross_cl = Uml::classByName(cross_dgr, (string(cl.name()) + string(Udm::cross_delimiter) + string(diagram.name())) );
						//--//cross_cl = Uml::classByName(cross_dgr, cl.name());
					}
					if (cross_cl)
					{
						set<Uml::AssociationRole> ar = cross_cl.associationRoles();
						set<Uml::AssociationRole>::iterator ar_i = ar.begin();
						while (ar_i != ar.end())
						{
							//--//output << "\t\t" << cross_cl.name() << "::meta_"<<Uml::theOther((*ar_i)).name() << 
							//--//	" = " << cross_dgr.name()<< "::" << cross_cl.name() << "::meta_"<<Uml::theOther((*ar_i)).name()<< ";" <<endl;

							output << "\t\t" << cl.name() << "::meta_"<<Uml::theOther((*ar_i)).name() << 
							" = " << cross_dgr.name()<< "::" << cross_cl.name() << "::meta_"<<Uml::theOther((*ar_i)).name()<< ";" <<endl;

							Uml::AssociationRole zz	= Uml::theOther(*ar_i);
							string aname(MakeRoleName(zz));

							Uml::Association ass = ar_i->parent();
							Uml::Class a_class = ass.assocClass();
							
							if(a_class) 
							{
								Uml::Class cl2 = zz.target();
								//output << "\t\t" << a_class.from() <<"::" << a_class.name() << "::meta_" << aname << "_end_ = " <<
								//					cl2.from() << "::" << cl2.name() << "::meta_" << MakeRoleName(*ar_i) << "_rev = " << 
								//					cl.name() << "::meta_" << aname << ";" << endl;

								//--//output << "\t\t" << cross_cl.name() << "::meta_"<<Uml::theOther((*ar_i)).name() << 
								//--//"_rev = " << cross_dgr.name()<< "::" << cl2.name() << "::meta_"<<ar_i->name()<< ";" <<endl;

								output << "\t\t" << cl.name() << "::meta_"<<Uml::theOther((*ar_i)).name() << 
								"_rev = " << cross_dgr.name()<< "::" << cl2.name() << "::meta_"<<ar_i->name()<< ";" <<endl;

							}


							ar_i++;
						}

					}
				}

				output << "\t};" << endl;

			}

		}// end associations

		
		




		{
			const set<Uml::Composition> &comps = diagram.compositions();
			set<Uml::Composition>::const_iterator c;
			for(c = comps.begin(); c != comps.end(); c++ )	
			{
//	{
				output << "\tvoid InitComposition" << compositions++ << "()" << endl <<"\t{" << endl;
//		Uml::Composition comp = Uml::CreateComposition();
				output << "\t\tUml::Composition comp = Uml::CreateCORBAComposition();" << endl;

//		Uml::InitComposition(comp, diagram, "DtoA");
				output << "\t\tUml::InitCORBAComposition(comp , umldiagram, \"" << c->name() << "\");" <<  endl;
				output << "\t" << endl;

				Uml::CompositionParentRole x1 = (*c).parentRole();
				Uml::CompositionChildRole x2 = (*c).childRole();

//		Uml::InitCompositionParentRole(A::meta_parent, comp, "parent", D::meta);
				Uml::CompositionParentRole zzp = c->parentRole();
				Uml::CompositionChildRole zzc = c->childRole();
				string aname(MakeRoleName(zzp));
				output << "\t\tUml::InitCORBACompositionParentRole(" << ((Uml::Class)zzc.target()).name() << "::meta_" << aname << ", comp, \""<< aname << "\", " << (zzp.isNavigable() ? "true, " : "false, ") << ((Uml::Class)zzp.target()).name() << "::meta);" << endl;
					
//		Uml::InitCompositionChildRole(D::meta_as, comp, "as", true, 0, -1, A::meta); 
				string cname(MakeRoleName(zzc));
				output << "\t\tUml::InitCORBACompositionChildRole(" << ((Uml::Class)zzp.target()).name() << "::meta_" << cname << ", comp, \""<< MakeShortRoleName(zzc) << "\", " << (zzc.isNavigable() ? "true, " : "false, ") << zzc.min() << ", " << zzc.max() << ", " << ((Uml::Class)zzc.target()).name() << "::meta);" << endl;
//	}
				output << "\t};" << endl;
			}
		}


//	void Initialize()
//	{
//		static bool first = true;
//		if(!first) return;
//		first = false;
//		Uml::Initialize();
//		ASSERT( umldiagram == Udm::null );
//		umldiagram = Uml::CreateDiagram();
		output << "\tvoid Initialize()" << endl << "\t{" << endl;
		output << "\t\tstatic bool first = true;" << endl;
		output << "\t\tif(!first) return;" << endl;
		output << "\t\tfirst = false;" << endl;
		output << "\t\tUml::Initialize();" << endl << endl;


//    GenerateCreateCORBADiagram(diagram,  output);
		output << "\t\tASSERT( umldiagram == Udm::null );" << endl;
		output << "\t\tumldiagram = Uml::CreateCORBADiagram();" << endl << endl;

 		if (cross_dgr && (diagram != cross_dgr))
			output << "\t\t" << cross_dgr.name() << "::Initialize();" << endl << endl;


		output << "\t\tCreates();" << endl;	
		output << "\t\tInits();" << endl;	
		for (int comp_i  = 0; comp_i < compositions; comp_i++) 
			output << "\t\tInitComposition" << comp_i << "();" << endl;
		

		for (int ass_i  = 0; ass_i < associations; ass_i++) 
			output << "\t\tInitAssociation" << ass_i << "();" << endl;


//		Uml::AddInheritance(A::meta, C::meta);
		for(c = classes.begin(); c != classes.end(); c++ ) 
		{
			Uml::Class cl = *c;
			set<Uml::Class> st = cl.subTypes();
			for( set<Uml::Class>::iterator i = st.begin(); i != st.end(); i++) 
			{
				output << "\t\tUml::AddCORBAInheritance(" << cl.name() << "::meta, " << (*i).name() << "::meta);" << endl;
			}
		}			
		output << "\t\t" << endl << "\t};" << endl;
//	Udm::UdmDiagram diagram = { &umldiagram, Initialize };
		output << "\tUdm::UdmDiagram diagram = { &umldiagram, Initialize };" << endl;
		output << "};" << endl <<"// END " << hname << ".cpp" <<endl;
}
