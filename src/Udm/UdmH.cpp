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
#include <fstream>
#include <algorithm>
#include "Udm.h"

typedef set< ::Uml::Class> UmlClasses;
typedef map<string,  UmlClasses> UmlClassesByName;

class InheritenceSolver
{
	friend void GenerateH(const ::Uml::Diagram &diagram, ostream &output, string fname, bool visitor_sup, const ::Uml::Diagram& cross_dgr, const string& macro, const int source_unit);
	friend void GenerateHIncludeClasses(const ::Uml::Diagram &diagram, const InheritenceSolver &is, ostream &output, const string &fname, bool visitor_sup);
	friend void CheckNamespaceFlips(const InheritenceSolver &is);
	friend void GenerateHNamespace(const ::Uml::Diagram &diagram, const ::Uml::Namespace &ns, const ::Uml::Diagram &cross_dgr, const InheritenceSolver &is, const string &fname, ostream &output, bool visitor_sup, const string &macro, int source_unit);
	friend void GenerateHN(const ::Uml::Diagram &diagram, ostream &output, string fname, bool visitor_sup, const ::Uml::Diagram& cross_dgr, const string& macro, int source_unit);
	friend void GenerateHD(const ::Uml::Diagram &diagram, ostream &output, string fname, bool visitor_sup, const ::Uml::Diagram& cross_dgr, const string& macro, int source_unit);

	typedef map< ::Uml::Class, set< ::Uml::Class> > cltoclsmap;
	typedef map< ::Uml::Class, bool > cltoboolmap;

	cltoclsmap virtualchildren;
	cltoclsmap explicitinits;
	cltoboolmap objectneeded_map;
	set< ::Uml::Class> virtualbaseclasses;
	vector< ::Uml::Class> good_inheritence_order;

	struct sortByActiveNamespace : public binary_function< ::Uml::Class, ::Uml::Class, bool>
	{
	private:
		::Uml::Namespace active_ns;
	public:
		sortByActiveNamespace(const ::Uml::Namespace &ns)
		{
			active_ns = ns;
		}

		bool operator()(const ::Uml::Class &a, const ::Uml::Class &b) const
		{
			::Uml::Namespace a_ns = a.parent_ns();
			::Uml::Namespace b_ns = b.parent_ns();
			if (a_ns == active_ns && b_ns != active_ns)
				return true;
			if (a_ns != active_ns && b_ns == active_ns)
				return false;
			if ((a_ns == active_ns && b_ns == active_ns) ||
			    (a_ns != active_ns && b_ns != active_ns))
				return a < b;
		}
	};

public:

	InheritenceSolver(const ::Uml::Diagram& diagram)
	{
		vector< ::Uml::Class> classes;

		set< ::Uml::Class> dgr_classes = diagram.classes();
		for (set< ::Uml::Class>::const_iterator dgr_classes_i = dgr_classes.begin(); dgr_classes_i != dgr_classes.end(); dgr_classes_i++) {
			classes.push_back(*dgr_classes_i);
		}

		set< ::Uml::Namespace> ns_set = diagram.namespaces();
		for (set< ::Uml::Namespace>::iterator ns_set_i = ns_set.begin(); ns_set_i != ns_set.end(); ns_set_i++)
		{
			::Uml::Namespace ns = *ns_set_i;

			set< ::Uml::Class> ns_classes = ns.classes();
			for (set< ::Uml::Class>::iterator ns_classes_i = ns_classes.begin(); ns_classes_i != ns_classes.end(); ns_classes_i++) {
				classes.push_back(*ns_classes_i);
			}
		}

		while (!classes.empty())
		{
			::Uml::Class cl;
			set< ::Uml::Class> bases;
			vector< ::Uml::Class>::iterator c;
			for( c = classes.begin(); c != classes.end(); c++ )	
			{
				cl = *c;
				bases = cl.baseTypes();

				set< ::Uml::Class>::iterator i;
				for(i = bases.begin(); i != bases.end(); i++) 
				{
					if (find(classes.begin(), classes.end(), *i) != classes.end()) break;
				}
				if(i == bases.end()) break;  // this class had all its parents already printed
			}
			if(c == classes.end()) 
			{ // list is not empty, still we found no one to continue with
				throw udm_exception("inheritance circularity detected");
			}

			good_inheritence_order.push_back(cl);

			// sort classes, putting classes from the same
			// namespace as "cl" to the beginning
			classes.erase(c);
			if (!classes.empty())
			{
				::Uml::Namespace cl_ns = cl.parent_ns();
				sort(classes.begin(), classes.end(), sortByActiveNamespace(cl_ns));
			}

			virtualchildren.insert(cltoclsmap::value_type(cl, set< ::Uml::Class>()));
			
			//filling up virtual base classes
			if( bases.size() == 0) 
			{
// Object should be virtual, if any of the descendants has an immediate baseclass,
// that is not derived from the current class   (only descendants with >=2 baseclasses are to be checked)
				set< ::Uml::Class> descs = Uml::DescendantClasses(cl);
				for(set< ::Uml::Class>::iterator i = descs.begin(); i != descs.end(); i++) 
				{
					if(*i == cl) continue;
					set< ::Uml::Class> dirancs = i->baseTypes();
					if(dirancs.size() > 1) 
					{
						for(set< ::Uml::Class>::iterator j = dirancs.begin(); j != dirancs.end(); j++) 
						{
							if(!Uml::IsDerivedFrom(*j, cl)) 
							{
								virtualbaseclasses.insert(cl);
								break;
							}
						}
					}
				}
			}
			else 
			{
				set< ::Uml::Class>::iterator h;
				for(h = bases.begin(); h != bases.end(); h++) 
				{
// the current base should be virtual, if any of the descendants has an immediate baseclass,
// that is derived from the current base, but not from the current class 
// (only descendants with >=2 baseclasses are to be checked)
					cltoclsmap::iterator actmapi = virtualchildren.find(*h);
					if(actmapi == virtualchildren.end()) 
					{
						throw udm_exception("internal error in class ordering");
					}
					set< ::Uml::Class> descs = Uml::DescendantClasses(cl);
					set< ::Uml::Class>::iterator i;
					for( i = descs.begin(); i != descs.end(); i++) 
					{
						if(*i == cl) continue;
						set< ::Uml::Class> dirancs = i->baseTypes();
						if(dirancs.size() > 1) 
						{
							for(set< ::Uml::Class>::iterator j = dirancs.begin(); j != dirancs.end(); j++) 
							{
								if(!Uml::IsDerivedFrom(*j, cl) && Uml::IsDerivedFrom(*j, *h)) 
								{
									
										actmapi->second.insert(cl);
								}
							}
						}
					}

					descs = Uml::AncestorClasses(cl);
					for(i = descs.begin(); i != descs.end(); i++) 
					{
						if(*i == cl) continue;
						if (actmapi->second.find(*i) != actmapi->second.end())
						{
							actmapi->second.insert(cl);
							break;
						};
					}
				};
			};

			int object_needed = 0, object_notneeded = 0;
			set< ::Uml::Class> ancestors = Uml::AncestorClasses(cl); 
			set< ::Uml::Class> additionaexplicitinitializers;

			for(set< ::Uml::Class>::iterator i = ancestors.begin(); i != ancestors.end(); i++) 
			{
				if(*i == cl) continue;

				if(set< ::Uml::Class>(i->baseTypes()).size() == 0) 
				{
					if(virtualbaseclasses.find(*i) != virtualbaseclasses.end()) object_needed++;
					else object_notneeded++;
				}
				if(bases.find(*i) != bases.end()) continue;
			
				cltoclsmap::iterator actmapi = virtualchildren.find(*i);
				set< ::Uml::Class> subtypes = i->subTypes();
				int found_inset = 0, found_notinset = 0;
				for(set< ::Uml::Class>::iterator p = subtypes.begin(); p != subtypes.end(); p++) 
				{
				
					if(!Uml::IsDerivedFrom(cl, *p)) continue;
					if(actmapi->second.find(*p) != actmapi->second.end()) found_inset++;
					else found_notinset++;
				}
				if(found_notinset > 1 || (found_inset && found_notinset))
				{
					throw udm_exception(string("Internal error resolving inheritance from class ") + string(i->name()) + " to " + string(cl.name()));
				}
				else if(found_inset) 
				{
						additionaexplicitinitializers.insert(*i);
				}
			}
			if(object_notneeded > 1 || (object_needed && object_notneeded)) 
			{ 
					throw udm_exception("Internal error resolving inheritance from class Object to " + string(cl.name()));
			}
			
			cltoclsmap::value_type item1(cl, additionaexplicitinitializers);
			cltoboolmap::value_type item2(cl, (object_needed!=0));

			pair<cltoclsmap::iterator, bool> res1 = explicitinits.insert(item1);
			pair<cltoboolmap::iterator, bool> res2 = objectneeded_map.insert(item2);

			if (!res1.second || !res2.second)
				throw udm_exception(string("Error generating the explicit initializer lists for class:") + (string)cl.name());
		};


	};

	string getAncestorList(const ::Uml::Class &cl) const
	{
		string ret;
		set< ::Uml::Class> bases = cl.baseTypes();
		if( bases.size() == 0) 
		{
			if (virtualbaseclasses.find(cl) != virtualbaseclasses.end()) ret+= " virtual";
			ret +=  " public Udm::Object";
		}
		else 
		{
			string sep("");
			set< ::Uml::Class>::iterator h;
			for(h = bases.begin(); h != bases.end(); h++) 
			{
				cltoclsmap::const_iterator actmapi = virtualchildren.find(*h);
				if(actmapi == virtualchildren.end()) 
				{
					throw udm_exception("internal error in class ordering");
				}
				if (actmapi->second.find(cl) != actmapi->second.end())
				{
					ret += sep;
					ret += " virtual";
					sep = "";
				};
				if(*h != cl) 
				{
					ret += sep;
					ret += " public ";
					ret += UmlClassCPPName(*h);
					sep = ",";
				}
			}
		};
		return ret;
	};
	string getInitializers(const ::Uml::Class &cl, const string& argument) const
	{
		set< ::Uml::Class> bases = cl.baseTypes();
		string ret;

		if( bases.size() == 0 ) 
		{
			ret +=  "UDM_OBJECT(";
			ret += argument;
			ret += ")";
		}
		else 
		{
			string sep("");
			set< ::Uml::Class>::iterator i;
			for(i = bases.begin(); i != bases.end(); i++) 
			{
				ret += sep;
				ret += UmlClassCPPName(*i);
				ret += "(";
				ret += argument;
				ret += ")";

				sep = ",";
			}
		}

		cltoclsmap::const_iterator ei_i = explicitinits.find(cl);
		if (ei_i == explicitinits.end())
			throw udm_exception("InheritenceSolver error");

		for(set< ::Uml::Class>::const_iterator i = ei_i->second.begin(); i != ei_i->second.end(); i++) 
		{
			ret += ", ";
			ret += UmlClassCPPName(*i);
			ret += "(";
			ret += argument;
			ret += ")";
		}

		cltoboolmap::const_iterator on_i = objectneeded_map.find(cl);
		if (on_i == objectneeded_map.end())
			throw udm_exception("InheritenceSolver error");

		if(on_i->second) 
		{
			ret += ", ";
			ret += "UDM_OBJECT(";
			ret += argument;
			ret += ")";
		}

		return ret;
	};

};

string CheckAttrType(const Udm::StringAttr &p) 
{

	string pv = p;
	if(pv.compare("String") && pv.compare("Boolean") && pv.compare("Integer") && pv.compare("Real")&& pv.compare("Text")) 
	{
		throw udm_exception("invalid attribute type '"+pv+"'");
	}

	//we use the same API for Text and String attributes
	if (!pv.compare("Text"))
	{
		return "String";
	};
	return pv;
};



string GetDgrfromFromStr(const string& fromstr)
{
	return fromstr.substr(0, fromstr.find(':'));
};
string GetNsfromFromStr(const string& fromstr )
{
	unsigned int i = fromstr.find(':');
	if (i == string::npos)
		return "";
	return fromstr.substr(i +1, string::npos);
};

void CheckNamespaceFlips(const InheritenceSolver &is)
{
	typedef map< ::Uml::Namespace, int> ns_flips_t;
	ns_flips_t ns_flips;

	::Uml::Namespace current_ns;

	for(vector< ::Uml::Class>::const_iterator gio_i = is.good_inheritence_order.begin(); gio_i != is.good_inheritence_order.end(); gio_i++)
	{
		::Uml::Namespace ns = gio_i->parent_ns();

		if (current_ns != ns)
		{
			ns_flips_t::iterator i = ns_flips.find(ns);
			if (i == ns_flips.end()) {
				ns_flips.insert(ns_flips_t::value_type(ns, 1));
			} else {
				i->second += 1;
			}
			current_ns = ns;
		}
	}
	for (ns_flips_t::iterator i = ns_flips.begin(); i != ns_flips.end(); i++)
	{
		if (i->second > 1)
			throw udm_exception("Cannot generate code due to interlaced namespaces; try the alternative options");
	}
}

void GenerateHPreamble(const ::Uml::Diagram &diagram, const string &fname, ostream &output, const string &macro)
{
	string uhname = "MOBIES_" + fname + "_H";

	string::iterator i;
	for(i = uhname.begin(); i != uhname.end(); i++) {
		*i = toupper(*i);
	}

	output << "#ifndef "<< uhname << endl <<"#define " << uhname << endl;
	output << "// header file " << fname << ".h generated from diagram " << (string)diagram.name() << endl;
	output << "// generated on " << GetTime().c_str() << endl << endl;


	output << "#ifndef MOBIES_UDMBASE_H" << endl;
	output << "#include \"UdmBase.h\""	<< endl;
	output << "#endif"	<< endl << endl;

	output << "#ifdef min" << endl;
	output << "#undef min" << endl;
	output << "#endif" << endl << endl;

	output << "#ifdef max" << endl;
	output << "#undef max" << endl;
	output << "#endif" << endl;


	if (macro.size())
		output << "#include \""<< fname << "_export.h\"" <<endl;
}

void GenerateHPostamble(const string &fname, ostream &output)
{
	string uhname = "MOBIES_" + fname + "_H";

	string::iterator i;
	for(i = uhname.begin(); i != uhname.end(); i++) {
		*i = toupper(*i);
	}
	output << "#endif //" << uhname << endl;
}


void GenerateHClassConstraints(const ::Uml::Class &cl, ostream &output)
{
	//constraints
	set< ::Uml::Constraint> constraints = cl.constraints();
	set< ::Uml::Constraint>::iterator c_i = constraints.begin();
	while (c_i != constraints.end())
	{
		output << "\t\t\tstatic ::Uml::Constraint meta_" << c_i->name() <<";" << endl;
		c_i++;
	}

	//constraint definitions
	set< ::Uml::ConstraintDefinition> definitions= cl.definitions();
	set< ::Uml::ConstraintDefinition>::iterator d_i = definitions.begin();
	while (d_i != definitions.end())
	{
		output << "\t\t\tstatic ::Uml::ConstraintDefinition meta_" << d_i->name() <<";" << endl;
		d_i++;
	}
};
void GenerateHClassBasic(const ::Uml::Class & cl, const InheritenceSolver& is, ostream & output)
{
	output << "\t\tpublic:" << endl;
	output << "\t\t\tstatic ::Uml::Class meta;" << endl << endl;

	output << "\t\t\t" << cl.name() << "() { }" << endl;
	output << "\t\t\t" << cl.name() << "(Udm::ObjectImpl *impl) : " << is.getInitializers(cl, "impl");
	output << " { }" << endl;

	output << "\t\t\t" << cl.name() << "(const " << cl.name() << " &master) : " << is.getInitializers(cl, "master");
	output << " { }" << endl;

			
	output << "\t\t\tstatic " << cl.name() << " Cast(const Udm::Object &a) { return __Cast(a, meta); }" << endl << endl;
	output << "\t\t\tstatic " << cl.name() << " Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE)"
			" { return __Create(meta, parent, role); }" << endl << endl;

	output << "\t\t\t" << cl.name() << " CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE)"
			" { return __Create(meta, parent, role, impl); }" << endl << endl;

	output << "\t\t\t" << cl.name() << " CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE)"
			" { return __Create(meta, parent, role, impl, true); }" << endl << endl;

	output << "\t\t\t" << "Udm::InstantiatedAttr< " << UmlClassCPPName(cl) << "> Instances()"
		" { return Udm::InstantiatedAttr< " << UmlClassCPPName(cl) << ">(impl);}" <<endl;

	output << "\t\t\t" << "template <class Pred> Udm::InstantiatedAttr< " << UmlClassCPPName(cl) << ", Pred> Instances_sorted(const Pred &)"
		" { return Udm::InstantiatedAttr< " << UmlClassCPPName(cl) << ", Pred>(impl);}" <<endl <<endl;


	output << "\t\t\t" << "Udm::DerivedAttr< " << UmlClassCPPName(cl) << "> Derived()"
		" { return Udm::DerivedAttr< " << UmlClassCPPName(cl) << ">(impl);}" <<endl ;

	output << "\t\t\t" << "template <class Pred> Udm::DerivedAttr< " << UmlClassCPPName(cl) << ", Pred> Derived_sorted(const Pred &)"
		" { return Udm::DerivedAttr< " << UmlClassCPPName(cl) << ", Pred>(impl);}" <<endl <<endl;


	output << "\t\t\t" << "Udm::ArchetypeAttr< " << UmlClassCPPName(cl) << "> Archetype()"
		" { return Udm::ArchetypeAttr< " << UmlClassCPPName(cl) << ">(impl);}" <<endl <<endl;

};

void GenerateHClassAssocEnds(const ::Uml::Class &cl, const ::Uml::Class& cross_cl, ostream & output, bool isCrossDgr)
{
	::Uml::Diagram dgr = ::Uml::GetDiagram(cl);

	::Uml::Association assoc = cl.association();
	string s = assoc.meta.name();
	if(assoc) 
	{
		set< ::Uml::AssociationRole> assocs = assoc.roles();
		for( set< ::Uml::AssociationRole>::iterator i = assocs.begin(); i != assocs.end(); i++) 
		{
			string aname(::Uml::MakeRoleName(*i));
			::Uml::Class oclass = (::Uml::Class)(*i).target();
			if(aname.size()) 
			{
			      output << "\t\t\tstatic ::Uml::AssociationRole meta_" << aname << "_end_;" << endl;
				  output << "\t\t\tUdm::AssocEndAttr< " << UmlClassCPPName(oclass) << "> " << aname << 
					  "_end() const { return Udm::AssocEndAttr< " << UmlClassCPPName(oclass) << ">(impl, meta_" << aname << "_end_); }\n\n";
			}
		}
	}
	if (cross_cl && !isCrossDgr)
	{
		::Uml::Association cross_cl_assoc = cross_cl.association();
		string s = cross_cl_assoc.meta.name();
		if (cross_cl_assoc)
		{
			set< ::Uml::AssociationRole> assocs = cross_cl_assoc.roles();
			for( set< ::Uml::AssociationRole>::iterator i = assocs.begin(); i != assocs.end(); i++) 
			{
				string aname(::Uml::MakeRoleName(*i));
				string oname(((::Uml::Class)(*i).target()).name());
				//Attention !
				oname = oname.substr(0, oname.find(Udm::cross_delimiter));
				//end of dangerous zone 
				string from_str(((::Uml::Class)(*i).target()).from());

				string from = string("::") + GetDgrfromFromStr(from_str);
				if (!SingleCPPNamespace(::Uml::diagramByName(dgr, GetDgrfromFromStr(from_str))))
					from += "::" + GetNsfromFromStr(from_str);

				if(aname.size()) 
				{
				      output << "\t\t\tstatic ::Uml::AssociationRole meta_" << aname << "_end_;" << endl;
				      output << "\t\t\tUdm::CrossAssocEndAttr< " << from << "::" << oname << "> " << aname << 
					  "_end() const { return Udm::CrossAssocEndAttr< " << from<< "::" << oname << ">(impl, meta_" << aname << "_end_); }\n\n";
				}
			}
		}
	}
};
void GenerateHClassParents(const ::Uml::Class &cl, ostream& output)
{

	set< ::Uml::CompositionChildRole> children = cl.childRoles();
	for( set< ::Uml::CompositionChildRole>::iterator i = children.begin(); i != children.end(); i++) 
	{
		string aname(::Uml::MakeRoleName(Uml::theOther(*i)));
		::Uml::Class oclass = (::Uml::Class)Uml::theOther(*i).target();

		output << "\t\t\tstatic ::Uml::CompositionParentRole meta_" << aname << ";" << endl;
		if(Uml::theOther(*i).isNavigable()) 
		{
			output << "\t\t\tUdm::" << "Parent" << "Attr< " << UmlClassCPPName(oclass) << "> " << aname << 
			  "() const { return Udm::" << "Parent" << "Attr< " << UmlClassCPPName(oclass) << 
			">(impl, meta_" << aname << "); }\n\n";
		}
		else 
		{
		  output << "\t\t\t// Access method for non-navigable association " << aname << " omitted \n\n";
		}
	}
	bool parent_defined = false;
	set< ::Uml::CompositionParentRole> parroles = Uml::AncestorCompositionPeerParentRoles(cl);
	for( set< ::Uml::CompositionParentRole>::iterator ri = parroles.begin(); ri != parroles.end(); ri++) 
	{
		if(string(ri->name()) == "parent") parent_defined = true;
	}
	if(!parent_defined) 
	{
		set< ::Uml::Class> ans = Uml::CommonAncestorClasses(Uml::AncestorContainerClasses(cl));
		if(ans.empty()) 
		{
			output << "\t\t\tUdm::ParentAttr<Udm::Object> parent() const " << "{ return Udm::ParentAttr<Udm::Object>(impl, Udm::NULLPARENTROLE); }" << endl;
		}
		else 
		{
			if (ans.size() == 1)
			{
				::Uml::Class ans_class = (::Uml::Class)(*ans.begin());
				output << "\t\t\tUdm::ParentAttr< " << UmlClassCPPName(ans_class) << "> parent() const " << 
					"{ return Udm::ParentAttr< " << UmlClassCPPName(ans_class) << ">(impl, Udm::NULLPARENTROLE); }" << endl;
			}
			else
			{
				for(set< ::Uml::Class>::iterator ccc = ans.begin(); ccc != ans.end(); ccc++) 
				{
					string ccc_name(ccc->name());
					output << "\t\t\tUdm::ParentAttr< " << UmlClassCPPName(*ccc) << "> " << ccc_name << "_parent() const " << 
						"{ return Udm::ParentAttr< " << UmlClassCPPName(*ccc) << ">(impl, Udm::NULLPARENTROLE); }" << endl;
				}
			}
		}
	}
};

void GenerateHClassChildren(const ::Uml::Class &cl, ostream & output)
{
	set< ::Uml::Class> childrenkinds; 
	set< ::Uml::CompositionParentRole> children = cl.parentRoles();
	for( set< ::Uml::CompositionParentRole>::iterator i = children.begin(); i != children.end(); i++) 
	{
		::Uml::CompositionParentRole k;
		string aname(::Uml::MakeRoleName(Uml::theOther(*i)));
		::Uml::Class thischildkind = (::Uml::Class)Uml::theOther(*i).target();
		childrenkinds.insert(thischildkind);
		output << "\t\t\tstatic ::Uml::CompositionChildRole meta_" << aname << ";" << endl;
		if(Uml::theOther(*i).isNavigable()) 
		{
			if ((int)Uml::theOther(*i).max() == 1 )
			{
				output << "\t\t\tUdm::ChildAttr< " << UmlClassCPPName(thischildkind) << "> " << aname << 
					"() const { return Udm::ChildAttr< " << UmlClassCPPName(thischildkind) << 
				">(impl, meta_" << aname << "); }\n\n";
			}
			else
			{
				output << "\t\t\tUdm::ChildrenAttr< " << UmlClassCPPName(thischildkind) << "> " << aname << 
					"() const { return Udm::ChildrenAttr< " << UmlClassCPPName(thischildkind) << 
				">(impl, meta_" << aname << "); }\n";

				output << "\t\t\ttemplate <class Pred> Udm::ChildrenAttr< " << UmlClassCPPName(thischildkind) << ", Pred> " << aname << 
					"_sorted(const Pred &) const { return Udm::ChildrenAttr< " << UmlClassCPPName(thischildkind) << 
				", Pred>(impl, meta_" << aname << "); }\n\n";
			}
		}
		else 
		{
		     output << "\t\t\t// Access method for non-navigable association " << aname << " omitted \n\n";
		}
	}

	::Uml::Namespace ns = cl.parent_ns();
	::Uml::Diagram dgr = ::Uml::GetDiagram(cl);
	set< ::Uml::Class> allclasses = ns ? ns.classes() : dgr.classes();

	for(set< ::Uml::Class>::iterator j = allclasses.begin(); j != allclasses.end(); j++) 
	{
		for(set< ::Uml::Class>::iterator k = childrenkinds.begin(); k != childrenkinds.end(); k++) 
		{
			if(Uml::IsDerivedFrom(*j, *k) || Uml::IsDerivedFrom(*k, *j)) 
			{
				string kind_children_name;
				if (SingleCPPNamespace(*j))
					kind_children_name = (*j).name();
				else {
					if (ns)
						kind_children_name = string(ns.name()) + "_";
					kind_children_name += (*j).name();
				}

				output << "\t\t\tUdm::ChildrenAttr< " << UmlClassCPPName(*j) << "> " << kind_children_name << 
					"_kind_children() const { return Udm::ChildrenAttr< " << UmlClassCPPName(*j) <<
				">(impl, Udm::NULLCHILDROLE); }\n";

				output << "\t\t\ttemplate<class Pred> Udm::ChildrenAttr< " << UmlClassCPPName(*j) << ", Pred> " << kind_children_name << 
					"_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< " << UmlClassCPPName(*j) <<
				", Pred>(impl, Udm::NULLCHILDROLE); }\n\n";

				break;
			}
		}
	}
};

void GenerateHClassAssociations(const ::Uml::Class& cl, const ::Uml::Class& cross_cl, ostream & output, bool isCrossDgr)
{
	::Uml::Diagram dgr = ::Uml::GetDiagram(cl);

	set< ::Uml::AssociationRole> assocs = cl.associationRoles();
	for( set< ::Uml::AssociationRole>::iterator i = assocs.begin(); i != assocs.end(); i++) 
	{
		::Uml::Association pp = (*i).parent();
		::Uml::Class aclass = pp.assocClass();

		string aname(::Uml::MakeRoleName(Uml::theOther(*i)));
		::Uml::Class oclass = (::Uml::Class)Uml::theOther(*i).target();
		if(!aclass) 
		{
			output << "\t\t\tstatic ::Uml::AssociationRole meta_" << aname << ";" << endl;
			if(Uml::theOther(*i).isNavigable()) 
			{
				if (Uml::theOther(*i).max() == 1)
				{
					output << "\t\t\tUdm::PointerAttr< " << UmlClassCPPName(oclass) << "> " << aname << 
						"() const { return Udm::PointerAttr< " << UmlClassCPPName(oclass) << 
					">(impl, meta_" << aname << "); }\n\n";
					
				}
				else
				{
					output << "\t\t\tUdm::AssocAttr< " << UmlClassCPPName(oclass) << "> " << aname << 
						"() const { return Udm::AssocAttr< " << UmlClassCPPName(oclass) << 
					">(impl, meta_" << aname << "); }\n";

					output << "\t\t\ttemplate <class Pred> Udm::AssocAttr< " << UmlClassCPPName(oclass) << ", Pred > " << aname << 
						"_sorted(const Pred &) const { return Udm::AssocAttr< "<< UmlClassCPPName(oclass) << 
					", Pred>(impl, meta_" << aname << "); }\n\n";					
				}
			}
			else 
			{
				output << "\t\t\t// Access method for non-navigable association " << aname << " omitted \n\n";
			}
		}
		else 
		{
			output << "\t\t\tstatic ::Uml::AssociationRole meta_" << aname << ", meta_" << aname << "_rev;" << endl;
			if(Uml::theOther(*i).isNavigable()) 
			{
				if (Uml::theOther(*i).max() == 1)
				{
					output << "\t\t\tUdm::AClassPointerAttr< " << UmlClassCPPName(aclass) << ", " << UmlClassCPPName(oclass) << "> " << aname << 
						"() const { return Udm::AClassPointerAttr< " << UmlClassCPPName(aclass) << ", " << UmlClassCPPName(oclass) << 
					">(impl, meta_" << aname << ", meta_" << aname << "_rev); }\n\n";
				}
				else
				{	
					output << "\t\t\tUdm::AClassAssocAttr< " << UmlClassCPPName(aclass) << ", " << UmlClassCPPName(oclass) << "> " << aname << 
						"() const { return Udm::AClassAssocAttr< " << UmlClassCPPName(aclass) << ", " << UmlClassCPPName(oclass) << 
					">(impl, meta_" << aname << ", meta_" << aname << "_rev); }\n";

					output << "\t\t\ttemplate<class Pred> Udm::AClassAssocAttr< " << UmlClassCPPName(aclass) << ", " << UmlClassCPPName(oclass) << ", Pred> " << aname << 
						"_sorted(const Pred &) const { return Udm::AClassAssocAttr< " << UmlClassCPPName(aclass) << ", " << UmlClassCPPName(oclass) << 
					", Pred>(impl, meta_" << aname << ", meta_" << aname << "_rev); }\n\n";
				}
			}
			else 
			{
					output << "\t\t\t// Access method for non-navigable association " << aname << " omitted \n\n";
			}
		}
	}
	if (cross_cl && !isCrossDgr)
	{
		set< ::Uml::AssociationRole> assocs = cross_cl.associationRoles();
		for( set< ::Uml::AssociationRole>::iterator i = assocs.begin(); i != assocs.end(); i++) 
		{
			::Uml::Association pp = (*i).parent();
			::Uml::Class aclass = pp.assocClass();

			string aname(::Uml::MakeRoleName(Uml::theOther(*i)));
			string oname(((::Uml::Class)Uml::theOther(*i).target()).name());
			//Attention !!!
			oname = oname.substr(0,oname.find(Udm::cross_delimiter));
			//
			string from_name(((::Uml::Class)Uml::theOther(*i).target()).from());
			string cname = string("::") + GetDgrfromFromStr(from_name);
			if (!SingleCPPNamespace(::Uml::diagramByName(dgr, GetDgrfromFromStr(from_name))))
				cname += "::" + GetNsfromFromStr(from_name);

			if(!aclass) 
			{
				output << "\t\t\tstatic ::Uml::AssociationRole meta_" << aname << ";" << endl;
				if(Uml::theOther(*i).isNavigable()) 
				{
					if (Uml::theOther(*i).max() == 1 )
					{
						output << "\t\t\tUdm::CrossPointerAttr< " << cname << "::" << oname << "> " << aname << 
						"() const { return Udm::CrossPointerAttr< "<< cname << "::" << oname << 
						">(impl, meta_" << aname << "); }\n\n";
					}
					else
					{
						output << "\t\t\tUdm::CrossAssocAttr< " << cname << "::" << oname << "> " << aname << 
						"() const { return Udm::CrossAssocAttr< " << cname << "::" << oname << 
						">(impl, meta_" << aname << "); }\n";

						output << "\t\t\ttemplate<class Pred> Udm::CrossAssocAttr< " << cname << "::" << oname << ", Pred> " << aname << 
						"_sorted(const Pred &) const { return Udm::CrossAssocAttr< "<< cname << "::" << oname << 
						", Pred>(impl, meta_" << aname << "); }\n\n";
					};
				}
				else 
				{
					output << "\t\t\t// Access method for non-navigable association " << aname << " omitted \n\n";
				};
			}
			else 
			{
				string clname(aclass.name());
				//Attention !!!
				clname = clname.substr(0,clname.find(Udm::cross_delimiter));
				//end of dangerous zone
	
				string from_str(aclass.from());
				string cl_dgr = string("::") + GetDgrfromFromStr(from_str);
				if (!SingleCPPNamespace(::Uml::diagramByName(dgr, GetDgrfromFromStr(from_str))))
					cl_dgr += "::" + GetNsfromFromStr(from_str);

				output << "\t\t\tstatic ::Uml::AssociationRole meta_" << aname << ", meta_" << aname << "_rev;" << endl;
				if(Uml::theOther(*i).isNavigable()) 
				{
					if (Uml::theOther(*i).max() == 1)
					{
						output << "\t\t\tUdm::AClassCrossPointerAttr< " << cl_dgr << "::" << clname << ", " << cname << "::" << oname << "> " << aname << 
						"() const { return Udm::AClassCrossPointerAttr< " << cl_dgr << "::" << clname << ", " << cname << "::" << oname << 
						">(impl, meta_" << aname << ", meta_" << aname << "_rev); }\n\n";
					}
					else
					{
						output << "\t\t\tUdm::AClassCrossAssocAttr< " << cl_dgr << "::" << clname << ", " << cname << "::" << oname << "> " << aname << 
						"() const { return Udm::AClassCrossAssocAttr< " << cl_dgr << "::" << clname << ", " << cname << "::" << oname << 
						">(impl, meta_" << aname << ", meta_" << aname << "_rev); }\n";
						output << "\t\t\ttemplate<class Pred> Udm::AClassCrossAssocAttr< " << cl_dgr << "::" << clname << ", " << cname << "::" << oname << ", Pred> " << aname << 
						"_sorted(const Pred &) const { return Udm::AClassCrossAssocAttr< " << cl_dgr << "::" << clname << ", " << cname << "::" << oname << 
						", Pred>(impl, meta_" << aname << ", meta_" << aname << "_rev); }\n\n";
					};
				}
				else 
				{
					  output << "\t\t\t// Access method for non-navigable association " << aname << " omitted \n\n";
				};
			};
		};
	};
};

void GenerateHClassAttributes(const ::Uml::Class& cl, ostream & output)
{
	
//		static ::Uml::Attribute meta_d;
//		Udm::RealAttr d() const { return Udm::RealAttr(impl, meta_d); }
	set< ::Uml::Attribute> attributes = cl.attributes();
	for( set< ::Uml::Attribute>::iterator i = attributes.begin(); i != attributes.end(); i++) 
	{
		output << "\t\t\tstatic ::Uml::Attribute meta_" << (*i).name() << ";" << endl;
		::Uml::Attribute k;
		string np;
		if(i->nonpersistent()) np = "Temp";
		/*
			Array support
			endre, 06/17/2002
		*/
		if ((i->max() ==1) || (i->max() == 0))
			output << "\t\t\tUdm::" << np << CheckAttrType(i->type()) << "Attr " << (*i).name() << 
			"() const { return Udm::" << np <<CheckAttrType(i->type()) << "Attr(impl, meta_" << (*i).name() << "); }\n\n";
		else 
			output << "\t\t\tUdm::" << np << CheckAttrType(i->type()) << "AttrArr " << (*i).name() << 
			"() const { return Udm::" << np << CheckAttrType(i->type()) << "AttrArr(impl, meta_" << (*i).name() << "); }\n\n";
	}
};

void GenerateHVisitorClassContent(const ::Uml::Diagram &diagram, const ::Uml::Namespace &ns, ostream & output, const string& macro)
{
	set< ::Uml::Class> classes = ns ? ns.classes() : diagram.classes();
	set< ::Uml::Class>::const_iterator c;

	output << endl << "\t\tclass " << macro << " Visitor : public Udm::BaseVisitor " << endl << "\t\t{" << endl << "\t\tpublic:" <<endl;
	for(c = classes.begin(); c != classes.end(); c++ )
	{
		::Uml::Class cl = *c;
		if (!cl.isAbstract())
			output << "\t\t\tvirtual void Visit_" << (string)cl.name() << "(const " << (string)cl.name() << "&){};" << endl;	
	}

	output << "\t\t\tvirtual void Visit_Object(const Udm::Object&){};" << endl;	
	output << "\t\t\tvirtual ~Visitor(){};" << endl;	
	output << "\t\t};" << endl;
};

void GenerateHVisitorClass(const ::Uml::Diagram &diagram, const ::Uml::Namespace &ns, const string &fname, ostream & output, const string& macro, int source_unit)
{
	if (source_unit == CPP_SOURCE_UNIT_CLASS)
	{
		string visitor_fname = NameToFilename(fname + "_" + (ns ? (string)ns.name() : "") + "_Visitor");
		bool single_cpp_namespace = SingleCPPNamespace(ns);

		ofstream ff;
		ff.open( (visitor_fname + ".h").c_str() );
		if(!ff.good()) throw udm_exception("Error opening for write " + visitor_fname + ".h");

		GenerateHPreamble(diagram, visitor_fname, ff, macro);

		ff << "namespace " << NameToFilename(diagram.name()) << " {" << endl;
		if (!single_cpp_namespace)
			ff << "\tnamespace " << NameToFilename(ns.name()) << " {" << endl << endl;

		GenerateHVisitorClassContent(diagram, ns, ff, macro);
		if (!single_cpp_namespace)
			ff << "\t}" << endl;
		ff << "}" << endl << endl;

		GenerateHPostamble(visitor_fname, ff);
		ff.close();
	} else {
		GenerateHVisitorClassContent(diagram, ns, output, macro);
	}
}

void GenerateHClassContent(const ::Uml::Class &cl, const ::Uml::Class &cross_cl, bool isCrossDgr, const InheritenceSolver &is, ostream &output, bool visitor_sup, const string &macro)
{

	output << "\t\tclass " << macro << " " << (string)cl.name() << " : " << is.getAncestorList(cl) << " {" << endl;

	GenerateHClassBasic(cl, is, output);
	GenerateHClassAttributes(cl, output);
	GenerateHClassAssociations(cl, cross_cl, output, isCrossDgr);
	GenerateHClassChildren(cl, output);
	GenerateHClassParents(cl, output);
	GenerateHClassAssocEnds(cl, cross_cl, output, isCrossDgr);
	GenerateHClassConstraints(cl, output);
				
	//visitor
	if (visitor_sup && !cl.isAbstract())
		output << "\t\t\tvirtual void Accept(Visitor &v){v.Visit_" << (string)cl.name() <<"(*this);};" << endl;
	output << "\t\t};" << endl;
}

void GenerateHClass(const ::Uml::Class &cl, const ::Uml::Class &cross_cl, bool isCrossDgr, const InheritenceSolver &is, const string &fname, ostream &output, bool visitor_sup, const string &macro, int source_unit)
{
	if (source_unit == CPP_SOURCE_UNIT_CLASS) {
		::Uml::Namespace ns = cl.parent_ns();
		::Uml::Diagram diagram = ::Uml::GetDiagram(cl);
		string cl_fname = NameToFilename(fname + "_" + (ns ? (string)ns.name() : "") + "_" + (string)cl.name());
		bool single_cpp_namespace = SingleCPPNamespace(cl);

		ofstream ff;
		ff.open( (cl_fname + ".h").c_str() );
		if(!ff.good()) throw udm_exception("Error opening for write " + cl_fname + ".h");

		GenerateHPreamble(diagram, cl_fname, ff, macro);

		ff << "namespace " << NameToFilename(diagram.name()) << " {" << endl;
		if (!single_cpp_namespace)
			ff << "\tnamespace " << NameToFilename(ns.name()) << " {" << endl << endl;

		GenerateHClassContent(cl, cross_cl, isCrossDgr, is, ff, visitor_sup, macro);

		if (!single_cpp_namespace)
			ff << "\t}" << endl;
		ff << "}" << endl << endl;

		GenerateHPostamble(cl_fname, ff);
		ff.close();
	} else {
		GenerateHClassContent(cl, cross_cl, isCrossDgr, is, output, visitor_sup, macro);
		output << endl;
	}
}


void GenerateHCrossForwardDeclarations(const ::Uml::Diagram &dgr, ostream &output,  const ::Uml::Diagram& cross_dgr, const string& dgr_name, const string & macro)
{
	if (cross_dgr)
	{
		set< ::Uml::Namespace> nses = dgr.namespaces();
		
		set< ::Uml::Class> cross_classes = cross_dgr.classes();
		map<string, UmlClassesByName> cr_cls_nsp;

		for(set< ::Uml::Class>::iterator i = cross_classes.begin(); i != cross_classes.end(); i++)
		{
			string from = i->from();
			if (from.size() == 0) continue;
			string dgr_from = GetDgrfromFromStr(from);
			string ns_from = GetNsfromFromStr(from);
			map<string, UmlClasses> & cr_cls = cr_cls_nsp[dgr_from];
			UmlClasses & clss = cr_cls[ns_from];
			
			for(set< ::Uml::Namespace>::iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
			{
				string ns_name = nses_i->name();
				
				if (dgr_from == dgr_name && ns_from == ns_name) continue;

	//			vector< ::Uml::Class> & clss = cr_cls_nsp[from];
				clss.insert(*i);
			};

			if (!(dgr_from == dgr_name && ns_from == ""))
				clss.insert(*i);
		}
		for(map<string, UmlClassesByName>::iterator j = cr_cls_nsp.begin(); j != cr_cls_nsp.end(); j++)
		{
			bool single_cpp_namespace = SingleCPPNamespace(::Uml::diagramByName(dgr, j->first));
			output << "namespace " << j->first << endl << "{ " << endl;
			map<string, UmlClasses>  cr_cls = j->second;
			for(map<string, UmlClasses>::iterator jj = cr_cls.begin(); jj != cr_cls.end(); jj++)
			{
				if (!single_cpp_namespace)
					output << "\tnamespace " << jj->first << endl << "\t{ " << endl;
				set< ::Uml::Class>& clss = jj->second;
				for(set< ::Uml::Class>::iterator jjj = clss.begin(); jjj != clss.end(); jjj++)
				{
					string class_name = jjj->name();
					//Attention - dangerous zone
					class_name = class_name.substr(0, class_name.find(Udm::cross_delimiter));
					//end of dangerous zone
					output << "\t\tclass " << macro << " " << class_name << ";" << endl;
				};
				if (!single_cpp_namespace)
					output << "\t};" << endl;
			};
			output << "};" << endl;
		}
	};
};

void GenerateHExport(const ::Uml::Diagram &diagram, ostream &output, string fname,  const string& macro)
{
	string hname = diagram.name();
	string::iterator i;
	for(i = hname.begin(); i != hname.end(); i++) 
	{
		if(!isalnum(*i)) *i = '_';
	}
	
	string uhname = "MOBIES_" + fname + "_H";
	string hasdll_string = hname + "_HAS_DLL";
	string export_string = hname + "_EXPORT";
	
	output << "#ifndef " << uhname <<endl;
	output << "#	define " << uhname <<endl;
	output << "#	ifndef " << macro << endl;
	output << "#		if defined (" << hasdll_string << ") && (" << hasdll_string << " == 1)" <<endl;
	output << "#			if defined (" << export_string << " )" << endl;
	output << "#				define " << macro << " __declspec(dllexport)" << endl;
	output << "#			else" << endl;
	output << "#				define " << macro << " __declspec(dllimport)" << endl;
	output << "#			endif /* " << export_string << " */" << endl;
	output << "#		else" <<endl;
	output << "#			define " << macro << endl;
	output << "#		endif /*" << hasdll_string << "*/" << endl;
	output << "#	endif /* ifndef " << macro << " */ " << endl;
	output << "#endif /* " << uhname << " */ " << endl;
};

void GenerateHForwardDeclarations(const ::Uml::Diagram &diagram, const ::Uml::Namespace& ns, ostream & output, const string &fname, bool visitor_sup, const string& macro, int source_unit)
{
	bool single_cpp_namespace = SingleCPPNamespace(ns);

	if (!single_cpp_namespace)
		output << "\tnamespace " << ns.name() << " {" << endl;

	set< ::Uml::Class> classes = ns ? ns.classes() : diagram.classes();

	if (classes.size()) 
	{

		set< ::Uml::Class>::iterator c;

		for(c = classes.begin(); c != classes.end(); c++ )
		{
			::Uml::Class cl = *c;
			output << "\t\tclass " << macro <<" "<< (string)cl.name() << ";" << endl;
		}
	}

	output << endl;

	if (ns)
		output << "\t\t" << macro << " extern ::Uml::Namespace meta;" << endl;

	if (visitor_sup)
	{
		GenerateHVisitorClass(diagram, ns, fname, output, macro, source_unit);
	}
	output << endl;

	if (ns) {
		output << "\t\t" << macro << " void InitializeNS();" << endl;
		output << "\t\t" << macro << " void InitializeNS(const ::Uml::Diagram &dgr);" << endl;
		output << "\t\t" << macro << " void InitializeNS(const ::Uml::Namespace &ns);" << endl;
		output << "\t\t" << macro << " void InitCrossNSInheritence();" << endl;
		output << "\t\t" << macro << " void InitCrossNSCompositions();" << endl;
		output << endl;
	}

	if (!single_cpp_namespace)
		output << "\t}" << endl << endl;

}

void GenerateHIncludeNamespaceFwdDeclarations(const ::Uml::Diagram &diagram, ostream &output, const string &fname)
{
	set< ::Uml::Namespace> ns_set = diagram.namespaces();

	for(set< ::Uml::Namespace>::const_iterator i = ns_set.begin(); i != ns_set.end(); i++)
	{
		string ns_fname = NameToFilename(fname + "_" + (string)i->name());
		output << "#include \"" << ns_fname << "__fwd.h\"" << endl;
	}
}

void GenerateHNamespace(const ::Uml::Diagram &diagram, const ::Uml::Namespace &ns, const ::Uml::Diagram &cross_dgr, const InheritenceSolver &is, const string &fname, ostream &output, bool visitor_sup, const string &macro, int source_unit)
{
	string ns_fname = NameToFilename(fname + "_" + (string)ns.name() + "__fwd");
	ofstream ff;
	ff.open( (ns_fname+".h").c_str() );
	if(!ff.good()) throw udm_exception("Error opening for write " + ns_fname + ".h");

	GenerateHPreamble(diagram, ns_fname, ff, macro);

	ff << "namespace " << NameToFilename(diagram.name()) << " {" << endl;
	GenerateHForwardDeclarations(diagram, ns, ff, fname, visitor_sup, macro, source_unit);
	ff << "}" << endl;
	GenerateHPostamble(ns_fname, ff);
	ff.close();


	ns_fname = NameToFilename(fname + "_" + (string)ns.name());
	bool single_cpp_namespace = SingleCPPNamespace(ns);

	output << "#include \"" << ns_fname << ".h\"" << endl;

	ff.open( (ns_fname+".h").c_str() );
	if(!ff.good()) throw udm_exception("Error opening for write " + ns_fname + ".h");

	GenerateHPreamble(diagram, ns_fname, ff, macro);

	ff << "namespace " << NameToFilename(diagram.name()) << " {" << endl;

	if (!single_cpp_namespace)
		ff << "\tnamespace " << ns.name() << " {" << endl;

	for(vector< ::Uml::Class>::const_iterator gio_i = is.good_inheritence_order.begin(); gio_i != is.good_inheritence_order.end(); gio_i++)
	{
		::Uml::Class cl = *gio_i;
		::Uml::Class cross_cl;
		::Uml::Namespace ns_cl = cl.parent_ns();
			
		if (ns == ns_cl)
		{
			if (cross_dgr)
				cross_cl = GetCrossClass(cross_dgr, cl);

			GenerateHClass(cl, cross_cl, (diagram == cross_dgr), is, fname, ff, visitor_sup, macro, source_unit);
		}
	}

	if (!single_cpp_namespace)
		ff << "\t}" << endl;

	ff << "}" << endl << endl;
	GenerateHPostamble(ns_fname, ff);
	ff.close();
}

void GenerateHClassesHeaders(const ::Uml::Diagram &diagram, const set< ::Uml::Class> &classes, const ::Uml::Diagram &cross_dgr, const InheritenceSolver &is, const string &fname, ostream &output, bool visitor_sup, const string &macro, int source_unit)
{
	for (set< ::Uml::Class>::const_iterator ci = classes.begin(); ci != classes.end(); ci++)
	{
		::Uml::Class cl = *ci;
		::Uml::Class cross_cl;

		if (cross_dgr)
			cross_cl = GetCrossClass(cross_dgr, cl);

		GenerateHClass(cl, cross_cl, (diagram == cross_dgr), is, fname, output, visitor_sup, macro, source_unit);
	}
}

void GenerateHIncludeClasses(const ::Uml::Diagram &diagram, const InheritenceSolver &is, ostream &output, const string &fname, bool visitor_sup)
{
	// include visitor class headers
	if (visitor_sup)
	{
		// diagram classes visitor
		output << "#include \"" << NameToFilename(fname + "_Visitor") << ".h\"" << endl;

		// namespace classes visitors
		set< ::Uml::Namespace> ns_set = diagram.namespaces();

		for (set< ::Uml::Namespace>::const_iterator ns_set_i = ns_set.begin(); ns_set_i != ns_set.end(); ns_set_i++)
			output << "#include \"" << NameToFilename(fname + "_" + (string)ns_set_i->name() + "_Visitor") << ".h\"" << endl;

		output << endl;
	}

	// include class headers
	for (vector< ::Uml::Class>::const_iterator gio_i = is.good_inheritence_order.begin(); gio_i != is.good_inheritence_order.end(); gio_i++)
	{
		::Uml::Class cl = *gio_i;
		::Uml::Namespace ns = cl.parent_ns();
		string cl_fname = fname + "_";
		if (ns)
			cl_fname += (string)ns.name();
		cl_fname += "_" + (string)cl.name();
		output << "#include \"" << NameToFilename(cl_fname) << ".h\"" << endl;

	}
	output << endl;
}

void GenerateHN(const ::Uml::Diagram &diagram, ostream &output, string fname, bool visitor_sup, const ::Uml::Diagram& cross_dgr, const string& macro, int source_unit)	
{
	InheritenceSolver is(diagram);

	CheckNamespaceFlips(is);

	string hname = NameToFilename(diagram.name());
		
	GenerateHPreamble(diagram, fname, output, macro);
	
	GenerateHCrossForwardDeclarations(diagram, output, cross_dgr, diagram.name(), macro);

	// generate namespace headers, visitor class headers
	GenerateHIncludeNamespaceFwdDeclarations(diagram, output, fname);


	output << "namespace " << hname << " {" << endl;
	output << "\textern " << macro << " Udm::UdmDiagram diagram;" << endl;

	GenerateHForwardDeclarations(diagram, ::Uml::Namespace(NULL), output, fname, visitor_sup, macro, source_unit);

	output << "\t" << macro << " void Initialize(const ::Uml::Diagram &dgr);" << endl;
	output << "\t" << macro << " void Initialize();" << endl << endl;

	output << "}" << endl << endl;


	::Uml::Namespace current_ns;
	for(vector< ::Uml::Class>::const_iterator gio_i = is.good_inheritence_order.begin(); gio_i != is.good_inheritence_order.end(); gio_i++)
	{
		::Uml::Namespace ns = gio_i->parent_ns();
		if (current_ns != ns)
		{
			if (ns)
				GenerateHNamespace(diagram, ns, cross_dgr, is, fname, output, visitor_sup, macro, source_unit);
			else {
				output << "namespace " << hname << " {" << endl;
				set < ::Uml::Class> classes = diagram.classes();
				for (vector< ::Uml::Class>::const_iterator dgr_gio_i = is.good_inheritence_order.begin(); dgr_gio_i != is.good_inheritence_order.end(); dgr_gio_i++)
				{
					::Uml::Class cl = *dgr_gio_i;
					if ((::Uml::Namespace)cl.parent_ns() == ::Uml::Namespace(NULL))
					{
						::Uml::Class cross_cl;
						if (cross_dgr)
							cross_cl = GetCrossClass(cross_dgr, cl);
						GenerateHClass(cl, cross_cl, (diagram == cross_dgr), is, fname, output, visitor_sup, macro, source_unit);
					}
				}
				output << "}" << endl << endl;
			}
			current_ns = ns;
		}
	}
	output << endl;

	GenerateHPostamble(fname, output);
}

void GenerateHD(const ::Uml::Diagram &diagram, ostream &output, string fname, bool visitor_sup, const ::Uml::Diagram& cross_dgr, const string& macro, int source_unit)	
{
	set< ::Uml::Namespace> ns_set = diagram.namespaces();
	InheritenceSolver is(diagram);

	string hname = NameToFilename(diagram.name());
		
	GenerateHPreamble(diagram, fname, output, macro);
	
	GenerateHCrossForwardDeclarations(diagram, output, cross_dgr, diagram.name(), macro);

	output << "namespace " << hname << " {" << endl;
	output << "\textern " << macro << " Udm::UdmDiagram diagram;" << endl;

	output << "\t" << macro << " void Initialize(const ::Uml::Diagram &dgr);" << endl;
	output << "\t" << macro << " void Initialize();" << endl << endl;

	// forward declarations
	GenerateHForwardDeclarations(diagram, ::Uml::Namespace(NULL), output, fname, visitor_sup, macro, source_unit);
	for (set< ::Uml::Namespace>::iterator ns_set_i = ns_set.begin(); ns_set_i != ns_set.end(); ns_set_i++)
		GenerateHForwardDeclarations(diagram, *ns_set_i, output, fname, visitor_sup, macro, source_unit);

	::Uml::Namespace current_ns;

	for(vector< ::Uml::Class>::const_iterator gio_i = is.good_inheritence_order.begin();gio_i != is.good_inheritence_order.end(); gio_i++)
	{
		::Uml::Class cl = *gio_i;
		::Uml::Namespace ns = cl.parent_ns();
			
		if (current_ns != ns)
		{
			if (gio_i != is.good_inheritence_order.begin()) {
				if (!SingleCPPNamespace(current_ns))
					output << "\t}" << endl;
				output << endl << endl;
			}
			if (!SingleCPPNamespace(ns))
				output << "\tnamespace " << ns.name() << " {" << endl << endl;
			current_ns = ns;
		}

		::Uml::Class cross_cl;
		if (cross_dgr)
			cross_cl = GetCrossClass(cross_dgr, cl);

		GenerateHClass(cl, cross_cl, (diagram == cross_dgr), is, fname, output, visitor_sup, macro, source_unit);
	}

	if (is.good_inheritence_order.size() > 0 && !SingleCPPNamespace(current_ns))
		output << "\t}" << endl;

	output << endl << endl;
	output << "}" << endl << endl;

	GenerateHPostamble(fname, output);
}

void GenerateHC(const ::Uml::Diagram &diagram, ostream &output, string fname, bool visitor_sup, const ::Uml::Diagram& cross_dgr, const string& macro, int source_unit)	
{
	set< ::Uml::Namespace> ns_set = diagram.namespaces();
	InheritenceSolver is(diagram);

	string hname = NameToFilename(diagram.name());
		
	GenerateHPreamble(diagram, fname, output, macro);
	
	GenerateHCrossForwardDeclarations(diagram, output, cross_dgr, diagram.name(), macro);


	output << "namespace " << hname << " {" << endl;
	output << "\textern " << macro << " Udm::UdmDiagram diagram;" << endl;

	output << "\t" << macro << " void Initialize(const ::Uml::Diagram &dgr);" << endl;
	output << "\t" << macro << " void Initialize();" << endl << endl;

	// forward declarations
	GenerateHForwardDeclarations(diagram, ::Uml::Namespace(NULL), output, fname, visitor_sup, macro, source_unit);
	for (set< ::Uml::Namespace>::iterator ns_set_i = ns_set.begin(); ns_set_i != ns_set.end(); ns_set_i++)
		GenerateHForwardDeclarations(diagram, *ns_set_i, output, fname, visitor_sup, macro, source_unit);

	output << "}" << endl << endl;


	// generate classes headers
	GenerateHClassesHeaders(diagram, diagram.classes(), cross_dgr, is, fname, output, visitor_sup, macro, source_unit);
	for (set< ::Uml::Namespace>::iterator ns_set_i = ns_set.begin(); ns_set_i != ns_set.end(); ns_set_i++)
		GenerateHClassesHeaders(diagram, ns_set_i->classes(), cross_dgr, is, fname, output, visitor_sup, macro, source_unit);

	// include classes and visitor headers
	GenerateHIncludeClasses(diagram, is, output, fname, visitor_sup);

	GenerateHPostamble(fname, output);
}

void GenerateHH(const ::Uml::Diagram &dgr, const std::string &fname, const bool visitor_sup, const ::Uml::Diagram &cross_dgr, const std::string &macro, int source_unit)
{
	ofstream ff;

	ff.open( (fname+".h").c_str() );
	if(!ff.good()) throw udm_exception("Error opening for write " + fname + ".h");
	else 
	{
		if (macro.size())
		{
			string exp_name = fname + "_export";
			ofstream fff;
			fff.open( (exp_name+".h").c_str() );
			if(!fff.good()) throw udm_exception("Error opening for write " + exp_name + ".h");
			else GenerateHExport(dgr, fff, exp_name, macro);
		};
		switch (source_unit)
		{
			case CPP_SOURCE_UNIT_CLASS: 
				GenerateHC(dgr, ff, fname, visitor_sup, cross_dgr, macro, source_unit);
				break;
			case CPP_SOURCE_UNIT_NAMESPACE: 
				GenerateHN(dgr, ff, fname, visitor_sup, cross_dgr, macro, source_unit);
				break;
			default:
				GenerateHD(dgr, ff, fname, visitor_sup, cross_dgr, macro, source_unit);
				break;
		}
	}
	ff.close();
	ff.clear();
}
