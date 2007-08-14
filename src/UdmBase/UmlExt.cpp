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

#include "UmlExt.h"
#include "UdmStatic.h"
#include "UdmUtil.h"

/*
	CHANGELOG
 	04/22/05	-	kalmar
        fixed OtherCompositionPeerParentRolesNamespaces : parents DescendantClasses need to be tested, too

	12/06/04	-	endre

			-		Added the GetChildRoleChain function, which returns all the possible paths how a class can be contained in an other
	09/11/04	-	endre

			-		Small fix in HasTextAttribytes/TextAttributes calls to also consider Ancestor attributes

	07/11/04	-	endre

			-		Addd two functions, HasTextAttributes and TextAttributes for checking the existence and for getting
					all the text attributes from a class.


	19/09/04	-	endre

			-		Added new function GetAncestorAssociation, which removes the only (if any) Association
					attached to a Class.


	12/12/02	endre
		 AncestorCrossAssociationRoles(): Changed the cross class-diagram delimiter from "_" to "_cross_ph_"
*/

namespace Uml
{

	UDM_DLL const AssociationRole theOther(const AssociationRole &role)
	{

		Association assoc = role.parent();

		set<AssociationRole> roles = assoc.roles();
		ASSERT( roles.size() == 2 );

		set<AssociationRole>::iterator i = roles.begin();
		if( *i == role )
			++i;

		return *i;
	}

	UDM_DLL const CompositionChildRole theOther(const CompositionParentRole &role)
	{
		const Composition &comp = role.parent();
		return comp.childRole();
	}

	UDM_DLL const CompositionParentRole theOther(const CompositionChildRole &role)
	{
		const Composition &comp = role.parent();
		return comp.parentRole();
	}

	// find an assoc.Class by name
	UDM_DLL Class assocClassByName(const Namespace &d, const string &name)
	{
		set<Class> ts = d.classes();
		for(set<Class>::iterator i = ts.begin(); i != ts.end(); i++) 
		{
			if ((Association)(i->association()) && string(i->name()) == name) return(*i);
		}
		return NULL;

	};

	
	// find a class by name
	UDM_DLL Class classByName(const Namespace &d, const string &name) 
	{
		set<Class> ts = d.classes();
			{
				for(set<Class>::iterator i = ts.begin(); i != ts.end(); i++) {
					if(string(i->name()) == name) return(*i);
				}
			}
			return NULL;
	}

// find an association by name
	UDM_DLL Association associationByName(const Namespace &d, const string &name) 
	{
			set<Association> ts = d.associations();
			{
				for(set<Association>::iterator i = ts.begin(); i != ts.end(); i++) {
					if(string(i->name()) == name) return(*i);
				}
			}
			return NULL;
	}


	UDM_DLL Composition compositionByName(const Namespace &d, const string &name) 
	{
			set<Composition> ts = d.compositions();
			{
				for(set<Composition>::iterator i = ts.begin(); i != ts.end(); i++) {
					if(string(i->name()) == name) return(*i);
				}
			}
			return NULL;
	}


	UDM_DLL set<Class> AncestorClasses(const Class &c)
	{
		set<Class> ret;
		ret.insert(c);

		set<Class> baseTypes = c.baseTypes();
		set<Class>::iterator i = baseTypes.begin();
		while( i != baseTypes.end() )
		{
			set<Class> a = AncestorClasses(*i);
			ret.insert(a.begin(), a.end());

			++i;
		}
		
		return ret;
	}

	UDM_DLL Association GetAncestorAssociation(const Class &c)	
	{
		Association Assoc = c.association();
		if (Assoc) return Assoc;

		set<Class> ancs = c.baseTypes();
		for (set<Class>::iterator ancs_i = ancs.begin(); ancs_i != ancs.end(); ancs_i++)
			return GetAncestorAssociation(*ancs_i);
	
		
		return &Udm::_null;
	};

	UDM_DLL set<Class> CommonAncestorClasses(const set<Class> &cs)
	{

		set<Class> ret;
		if(cs.begin() != cs.end()) {
			set<Class>::const_iterator ci = cs.begin();
			ret = AncestorClasses(*ci);
/*
#ifdef  ERASE_RETURNS_ITERATOR
			while(++ci != cs.end()) {
				for(set<Class>::iterator ri = ret.begin(); ri != ret.end();) {
					if(!::Uml::IsDerivedFrom(*ci, *ri)) ri = ret.erase(ri);
					else ++ri;
				}
			}
			for(set<Class>::iterator ri = ret.begin(); ri != ret.end();) {
				for(set<Class>::iterator ri2 = ret.begin(); ri2 != ret.end(); ri2++) {
					if(ri != ri2 && ::Uml::IsDerivedFrom(*ri, *ri2)) break;
				}
				if(ri2 == ret.end()) ri = ret.erase(ri);
				else ++ri;
			}
#else
*/
			while(++ci != cs.end()) {
				for(set<Class>::iterator ri = ret.begin(); ri != ret.end();) {
					set<Class>::iterator riact = ri++;
					if(!::Uml::IsDerivedFrom(*ci, *riact)) {
						ret.erase(riact);
					}
				}
			}
			for(set<Class>::iterator ri = ret.begin(); ri != ret.end();) {
				set<Class>::iterator riact = ri++;
				for(set<Class>::iterator ri2 = ret.begin(); ri2 != ret.end(); ri2++) {
					if(riact != ri2 && ::Uml::IsDerivedFrom(*riact, *ri2)) {
						ret.erase(riact);
						break;
					}
				}
			}
//#endif
		}

		return ret;
	}


	UDM_DLL set<Class> DescendantClasses(const Class &c)
	{
		set<Class> ret;
		ret.insert(c);

		set<Class> subTypes = c.subTypes();
		set<Class>::iterator i = subTypes.begin();
		while( i != subTypes.end() )
		{
			set<Class> a = DescendantClasses(*i);
			ret.insert(a.begin(), a.end());

			++i;
		}
		
		return ret;
	}

	UDM_DLL set<Class> ContainerClasses(const Class &c)
	{
		set<Class> ret;

		set<CompositionChildRole> childRoles = c.childRoles();
		set<CompositionChildRole>::iterator i = childRoles.begin();
		while( i != childRoles.end() )
		{
			Class d = theOther(*i).target();
			ret.insert(d);

			++i;
		}

		return ret;
	}

	UDM_DLL set<Class> ContainedClasses(const Class &c)
	{
		set<Class> ret;

		set<CompositionParentRole> parentRoles = c.parentRoles();
		set<CompositionParentRole>::iterator i = parentRoles.begin();
		while( i != parentRoles.end() )
		{
			Class d = theOther(*i).target();
			ret.insert(d);

			++i;
		}

		return ret;
	}

	UDM_DLL set<Class> AncestorContainerClasses(const Class &c)
	{
		set<Class> ret;

		set<Class> ancestors = AncestorClasses(c);
		set<Class>::iterator i = ancestors.begin();
		while( i != ancestors.end() )
		{
			set<Class> a = ContainerClasses(*i);
			ret.insert(a.begin(), a.end());

			++i;
		}

		return ret;
	}

	UDM_DLL set<Class> AncestorContainedClasses(const Class &c)
	{
		set<Class> ret;

		set<Class> ancestors = AncestorClasses(c);
		set<Class>::iterator i = ancestors.begin();
		while( i != ancestors.end() )
		{
			set<Class> a = ContainedClasses(*i);
			ret.insert(a.begin(), a.end());

			++i;
		}

		return ret;
	}

	UDM_DLL set<Class> AncestorContainedDescendantClasses(const Class &c)
	{
		set<Class> ret;

		set<Class> contained = AncestorContainedClasses(c);
		set<Class>::iterator i = contained.begin();
		while( i != contained.end() )
		{
  			set<Class> a = DescendantClasses(*i);
			ret.insert(a.begin(), a.end());

			++i;
		}

		return ret;
	}

	UDM_DLL set<Namespace> TargetNSForAllContainerClasses(const Namespace &ns)
	{
		set<Namespace> ret;

		set<Class> classes = ns.classes();
		set<Class>::iterator c;
	
		for(c = classes.begin(); c != classes.end(); c++ ) {
			Class cl = *c;
			set<CompositionParentRole> children = cl.parentRoles();
			for(set<CompositionParentRole>::iterator i = children.begin(); i != children.end(); i++) {
				Class theother = (Class)(theOther(*i)).target();
				Namespace theother_ns = (Namespace)theother.parent();
				if (ns != theother_ns)
					ret.insert(theother_ns);
			}
		}

		return ret;
	}

	UDM_DLL set<AssociationRole> AssociationTargetRoles(const Class &c)
	{
		set<AssociationRole> roles;

		set<AssociationRole> a = c.associationRoles();
		set<AssociationRole>::iterator i = a.begin();
		while( i != a.end() )
		{
			roles.insert(theOther(*i));

			++i;
		}

		return roles;
	}

	UDM_DLL set<AssociationRole> AncestorAssociationTargetRoles(const Class &c)
	{
		set<AssociationRole> roles;

		set<Class> ancestors = AncestorClasses(c);
		set<Class>::iterator i = ancestors.begin();
		while( i != ancestors.end() )
		{
			set<AssociationRole> a = AssociationTargetRoles(*i);
			roles.insert(a.begin(), a.end());

			++i;
		}

		return roles;
	}

	// All the other ends of associations this class can have (including those defined in ancestors)
	UDM_DLL set<AssociationRole> AncestorCrossAssociationTargetRoles(const Class &c, const Namespace & cross_dgr)
	{
		set<AssociationRole> ret;
		set<Class> anc_cs = AncestorClasses(c);
		set<Class>::iterator i = anc_cs.begin();
		while (i != anc_cs.end())
		{
			Class a_i = *i;
			string cross_cl_name = string(a_i.name()) + "_cross_ph_" + string(Namespace(a_i.parent()).name());
			//Class ph_a_i = classByName(cross_dgr, a_i.name());
			Class ph_a_i = classByName(cross_dgr, cross_cl_name);
			if (ph_a_i)
			{
				set<AssociationRole> ret_i = AssociationTargetRoles(ph_a_i);
				ret.insert(ret_i.begin(), ret_i.end());
			}
			i++;
		};

		return ret;
	}


	UDM_DLL set<AssociationRole> AncestorCrossAssociationRoles(const Class &c, const Namespace & cross_dgr)
	{
		set<AssociationRole> ret;
		set<Class> anc_cs = AncestorClasses(c);
		set<Class>::iterator i = anc_cs.begin();
		while (i != anc_cs.end())
		{
			Class a_i = *i;
			string cross_cl_name = string(a_i.name()) + Udm::cross_delimiter + string(Namespace(a_i.parent()).name());
			//Class ph_a_i = classByName(cross_dgr, a_i.name());
			Class ph_a_i = classByName(cross_dgr, cross_cl_name);
			if (ph_a_i)
			{
				set<AssociationRole> ret_i = ph_a_i.associationRoles();
				ret.insert(ret_i.begin(), ret_i.end());
			}
			i++;
		};

		return ret;
	}


	UDM_DLL set<AssociationRole> AncestorAssociationRoles(const Class &c)
	{
		set<AssociationRole> roles;

		set<Class> ancestors = AncestorClasses(c);
		set<Class>::iterator i = ancestors.begin();
		while( i != ancestors.end() )
		{
			set<AssociationRole> a = i->associationRoles();
			roles.insert(a.begin(), a.end());

			++i;
		}

		return roles;
	}
	UDM_DLL set<CompositionChildRole> CompositionPeerChildRoles(const Class &c)
	{
		set<CompositionChildRole> roles;
		set<CompositionParentRole> a = c.parentRoles();
		set<CompositionParentRole>::iterator i = a.begin();
		while( i != a.end() )
		{
			roles.insert(theOther(*i));
			++i;
		}

		return roles;
	};

	UDM_DLL set<CompositionChildRole> AncestorCompositionPeerChildRoles(const Class &c)
	{
		set<CompositionChildRole> roles;

		set<Class> ancestors = AncestorClasses(c);
		set<Class>::iterator i = ancestors.begin();
		while( i != ancestors.end() )
		{
			set<CompositionChildRole> a = CompositionPeerChildRoles(*i);
			roles.insert(a.begin(), a.end());
			++i;
		}

		return roles;
	
	};

	UDM_DLL set<Namespace> CompositionPeerChildNamespaces(const Namespace &ns)
	{
		set<Namespace> ret;

		set<Class> classes = ns.classes();
		for (set<Class>::iterator i = classes.begin(); i != classes.end(); i++) {
			set<CompositionChildRole> comps_c = CompositionPeerChildRoles(*i);
			for (set<CompositionChildRole>::iterator j = comps_c.begin(); j != comps_c.end(); j++) {
				Class theother = j->target();
				set<Class> theother_descs = DescendantClasses(theother);
				theother_descs.insert(theother);
				for (set<Class>::iterator descs_i = theother_descs.begin(); descs_i != theother_descs.end(); descs_i++) {
					Namespace theother_ns = (Namespace)descs_i->parent();
					if (ns != theother_ns)
						ret.insert(theother_ns);
				}

			}
		}

		return ret;
	}

	UDM_DLL set<CompositionParentRole> CompositionPeerParentRoles(const Class &c) 
	{
		set<CompositionParentRole> roles;
		set<CompositionChildRole> a = c.childRoles();
		set<CompositionChildRole>::iterator i = a.begin();
		while( i != a.end() )
		{
			roles.insert(theOther(*i));

			++i;
		}

		return roles;
	}

 	UDM_DLL set<CompositionParentRole> AncestorCompositionPeerParentRoles(const Class &c) 
	{
		set<CompositionParentRole> roles;

		set<Class> ancestors = AncestorClasses(c);
		set<Class>::iterator i = ancestors.begin();
		while( i != ancestors.end() )
		{
			set<CompositionParentRole> a = CompositionPeerParentRoles(*i);
			roles.insert(a.begin(), a.end());
			++i;
		}

		return roles;
	}


	UDM_DLL set<CompositionParentRole> DescendantCompositionPeerParentRoles(const Class &c) 
	{
		set<CompositionParentRole> roles;

		set<Class> desc = DescendantClasses(c);
		set<Class>::iterator i = desc.begin();
		while( i != desc.end() )
		{
			set<CompositionParentRole> a = CompositionPeerParentRoles(*i);
			roles.insert(a.begin(), a.end());
			++i;
		}

		return roles;
	}

      //this was not enough, what about derived classes, they going to have this child,too
      // and those parents can be in other namespace....

	UDM_DLL set<Namespace> OtherCompositionPeerParentRolesNamespaces(const Class &c)
	{
		set<Namespace> ret;
		Namespace ns = c.parent();

		set<CompositionParentRole> comps_c = AncestorCompositionPeerParentRoles(c);
		for (set<CompositionParentRole>::iterator j = comps_c.begin(); j != comps_c.end(); j++)
		{
			Class theother = j->target();

      
			set<Class> desc = DescendantClasses(theother);
			for (set<Class>::iterator jd = desc.begin(); jd != desc.end(); jd++)
			{
				Class cc = *jd;

				Namespace theother_ns = (Namespace)cc.parent();
				if (ns != theother_ns)
					ret.insert(theother_ns);
			}
		}

		return ret;
	}

	UDM_DLL bool IsCrossNSComposition(const Composition &c)
	{
		CompositionParentRole p_r = c.parentRole();
		Class p_c = p_r.target();
		Namespace p_ns = p_c.parent();

		CompositionChildRole c_r = c.childRole();
		Class c_c = c_r.target();
		Namespace c_ns = c_c.parent();

		return p_ns != c_ns;

	}

	UDM_DLL set<Attribute> AncestorAttributes(const Class &c)
	{
		set<Attribute> attributes;

		set<Class> ancestors = AncestorClasses(c);
		set<Class>::iterator i = ancestors.begin();
		while( i != ancestors.end() )
		{
			set<Attribute> a = i->attributes();
			attributes.insert(a.begin(), a.end());

			++i;
		}

		return attributes;
	}

	UDM_DLL Composition matchChildToParent(Class c, Class p) 
	{
			   Composition comp;
			   set<Class> pancs = AncestorClasses(p);
			   set<Class> cancs = AncestorClasses(c);
			   for(set<Class>::iterator j = cancs.begin(); j != cancs.end(); j++) {
					set<CompositionChildRole> cr = (*j).childRoles();
					for(set<CompositionChildRole>::iterator i = cr.begin(); i != cr.end(); i++) {
						if(pancs.find(theOther(*i).target()) != pancs.end()) {
							if(comp) {
								return NULL;
							}
							comp = (*i).parent();
						}
					}
			   }
#ifdef DEBUG
			   if(!comp) {
				   return NULL;
			   }
#endif
			   return comp;
	}

	UDM_DLL bool IsAssocClass(const Class &cl) 
	{
		return (Association)cl.association();
	}

	UDM_DLL bool IsAssocClass(const Association &cl) 
	{
		return (Class)cl.assocClass();
	}

	UDM_DLL bool IsDerivedFrom(const Class &derived, const Class &base)
	{
		// speedup and to make the startup possible
		//debug
		//end of debug
		if( &derived == &base )
			return true;

		if( derived == base )
			return true;

		set<Class> baseTypes = derived.baseTypes();
		set<Class>::iterator i = baseTypes.begin();
		while( i != baseTypes.end() )
		{
			if( ::Uml::IsDerivedFrom(*i, base) )
				return true;

			++i;
		}

		return false;
	}

	UDM_DLL set<Namespace> BaseTypesNamespaces(const Namespace &ns)
	{
		set<Namespace> ret;

		set<Class> classes = ns.classes();
		for (set<Class>::iterator i = classes.begin(); i != classes.end(); i++) {
			set<Class> bases = i->baseTypes();
			for (set<Class>::iterator j = bases.begin(); j != bases.end(); j++) {
				Class theother = *j;
				Namespace theother_ns = (Namespace)theother.parent();
				if (ns != theother_ns)
					ret.insert(theother_ns);
			}
		}

		return ret;
	}


// --------------------------- Construction








	UDM_DLL string MakeRoleName(const GenericRole &r) 
	{
			string name = r.name();

			if(name.empty()) {
				string anonbase, auxname;
	
				if(::Uml::IsDerivedFrom(r.type(), AssociationRole::meta)) { 
					AssociationRole ar = AssociationRole::Cast(r);
					anonbase = "arole"; 
					auxname = (string)((Class)ar.target()).name();	
					auxname[0] = _tolower(auxname[0]);
					if((int)ar.max() != 1) {
						if(strchr("hsy", *auxname.rbegin())) {
							auxname.append("es");
						}
						else auxname.append("s");
					}	
				}

				if(::Uml::IsDerivedFrom(r.type(), CompositionParentRole::meta)) { 
					CompositionParentRole pr = CompositionParentRole::Cast(r);
					string revname = theOther(pr).name();
					if(!revname.empty()) revname += "_";
					anonbase = "crole"; auxname = revname +	(string)((Class)pr.target()).name() + "_parent"; 
				}

				if(::Uml::IsDerivedFrom(r.type(), CompositionChildRole::meta)) { 
					CompositionChildRole cr = CompositionChildRole::Cast(r);
					anonbase = "prole"; auxname = (string)((Class)cr.target()).name() + ((int)cr.max() == 1 ? "_child" : "_children");	
				}

				if(!anonbase.length()) {
					return "<namegen error>";
				}	

				if(r.isNavigable()) {
					name = auxname;
				}
				else {
					char buf[12];
#ifdef _WIN32
					ultoa(r.__impl()->uniqueId(),buf,10);
#else
					snprintf(buf, 11, "%ld", r.__impl()->uniqueId());
#endif
					name=anonbase;
//					name.append(ultoa(r.__impl()->uniqueId(),buf,10));	
					name.append(buf);
				}
			}
			return name;
	}

	UDM_DLL string MakeShortRoleName(const GenericRole &r) 
	{
			string name = r.name();

			if(name.empty()) {
				string anonbase, auxname;

/*				
				if(::Uml::IsDerivedFrom(r.type(), AssociationRole::meta)) { 
					AssociationRole ar = AssociationRole::Cast(r);
					anonbase = "arole"; auxname = (string)((Class)ar.target()).name() + ((int)ar.max() == 1 ? "_assoc" : "_assocs");	
				}

				if(::Uml::IsDerivedFrom(r.type(), CompositionParentRole::meta)) { 
					CompositionParentRole pr = CompositionParentRole::Cast(r);
					string revname = theOther(pr).name();
					if(!revname.empty()) revname += "_";
					anonbase = "crole"; auxname = revname +	(string)((Class)pr.target()).name() + "_parent"; 
				}
*/

				if(::Uml::IsDerivedFrom(r.type(), CompositionChildRole::meta)) { 
					CompositionChildRole cr = CompositionChildRole::Cast(r);
					anonbase = "prole"; auxname = (string)((Class)cr.target()).name();	
				}

				if(!anonbase.length()) {
					return "<namegen error>";
				}	

				if(r.isNavigable()) {
					name = auxname;
				}
				else name = "";
			}
			return name;
	}


	UDM_DLL bool HasChildRoleMultipleTargets(const CompositionChildRole & ccr)
	{
		int i = 0;
		set<Class> descs = DescendantClasses(ccr.target());
		set<Class>::iterator descs_i = descs.begin();

		while (descs_i != descs.end())
		{
			if (i > 1) return true;
			if ((bool)(descs_i->isAbstract()) == false) i++;
			descs_i++;
		}
		if (i> 1) return true;

		return false;
	}

	UDM_DLL set<Attribute> TextAttributes(const Class &c)
	{
		set<Attribute> ret;
		set<Attribute> atts = AncestorAttributes(c);
		for (set<Attribute>::iterator i = atts.begin(); i != atts.end(); i++)
			if ((string)(i->type()) == "Text") ret.insert(*i);
		
		return ret;
	};
	

	//hope this will be just a little bit more performant
	UDM_DLL bool HasTextAttributes(const Class &c)
	{
		set<Attribute> atts = AncestorAttributes(c);
		for (set<Attribute>::iterator i = atts.begin(); i != atts.end(); i++)
			if ((string)(i->type()) == "Text") return true;

		return false;
	};

	/*
		returns all the possibile composition child role chains(paths), how 'what' can be contained in 'origin'
		the results are vectors of CompositionChildRoles
	*/
	UDM_DLL void GetChildRoleChain(const Class & origin, const Class &what, vector<ChildRoleChain> &chains, ChildRoleChain curr_chain)
	{
		set<CompositionParentRole> cprs = origin.parentRoles();
		if (cprs.size())
		{
			set<CompositionParentRole>::iterator cprs_i = cprs.begin();
			while (cprs_i != cprs.end())
			{
				const CompositionChildRole ccr = theOther(*cprs_i);
				curr_chain.insert(curr_chain.begin(), ccr);
				
				const Class new_orig  = ccr.target();
				set<Class> new_orig_descs = DescendantClasses(new_orig);
				
				for (set<Class>::iterator nod_i = new_orig_descs.begin(); nod_i != new_orig_descs.end(); nod_i++)
					GetChildRoleChain(*nod_i, what, chains, curr_chain);
				
				cprs_i++;
				curr_chain.erase(curr_chain.begin());
			};
		}
		else if(::Uml::IsDerivedFrom(origin, what)) chains.push_back(curr_chain);
	};

	UDM_DLL Namespace GetTheOnlyNamespace(const Diagram & dgr)
	{
		if (!dgr) return NULL;
		set<Namespace> nses = dgr.namespaces();
		if (nses.size() != 1) throw udm_exception("Uml::Namespace GetTheOnlyNamespace: More than one namespace found in diagram!");
		return *(nses.begin());
	};

	// find a class by name
	UDM_DLL Class classByName(const Diagram &d, const string &ns_name,const string &name )
	{
		Namespace ns = namespaceByName(d, ns_name);
		if (ns) return classByName(ns, name);
		else return Class();
	};
	
// find a namespace by name
	UDM_DLL Namespace namespaceByName(const Diagram &d, const string &name)
	{
		set<Namespace> nses = d.namespaces();
		for (set<Namespace>::iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
			if ((string)(nses_i->name()) == name) return *nses_i;
		
		return Namespace();
	};


}
