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

  01/12/05	-	endre

			-	More detailed error message in amapInitialize
  22/11/04	-	endre

			-	VC7.1 .net porting issues

  25/09/04	-	endre

			- struct UdmGme::assocmapitem now it's being defined here. In UdmGme.h it's being only forward declared in order to 
			keep the include file clean of MGA structs.

  24/09/04	-	endre

			- removed global variable amap and global function amapInitialize and placed as a member of GmeDataNetwork.
			Each GmeDataNetwork has it's own version of amap. This was required because GME wanted to have the meta objects released
			at the time of closing the project.
			the map is cleared when the datanetwork is closed.

  19/08/04	-	endre

			- fixed bug UDM-16 regarding inherited connections
  22/07/04	-	endre
	
			- minor bugfix regarding setting up the reference port helper connections
				(only navigable associationroles should be considered when setting registry values)
  13/07/04	-	endre

			-   addressed feature request UDM-6 regarding reference ports.

  21/06/04	-	endre

			- fixed amapInitialize to address bug UDM-10

  05/05/04	-	endre
	
			-	added support for abstract supertype connections 

  04/28/04	-	endre

			- folder objects could not be deleted, obvious fix in setParent() call
  04/26/04	-	endre

			-	createChild() bug. Scenario:
					
					- B is an abstract class
					- B is contained in A with empty child role
					- C is the only descendant of B
					- crateChild() tries to create C in A

  04/18/04	-	endre
			
				- when an object is detached, and the host datanetwork of the object is being part of a Udm project, 
				  the corresponding placeholder object (if any) should be detached as well.

  03/24/04	-	endre

				- Changing the syntax of createchild() as required by Udm::ObjectImpl
				- Added backendsemnatics to the OpenExisting function (BON version)

  11/04/02	-	endre

				- createChild() bug fixed. Still related to inherited childroles. 
				The newly inserted function GetMetaRole() should solve the problem.
				The problem was that MGA MetaRole it's composed like this:
				if ( child class has non-abstact derivates)
				{
					MetaRole = Kindname + Rolename;    // Rolename may be empty;
				}
				else 
				{
					 if (Rolename != "") MetaRole = Rolename
					 else MetaRole = KindName;
				}

  08/23/02	-	endre

				- fixed getParent() bug reported by Feng. Still related to 
				inherited childroles and parentroles.

  07/21/02	-	endre
				
				- fixed createChild(). Still problems with inherited childroles.

  06/18/02	-	endre

				-fixed createChild(role, kind) bug. 
					when both 'role' and  'kind' were provided, 
					and 'kind' was different from 'role.target()',
					(i.e. the type of the object(='kind') to be inserted 
					had only an inherited childrole), the new object was
					created with incosistent types: the target class of 
					the 'role' in the MGA layer, and with 'kind' in the 
					UDM layer. That could cause harm.
					
					  Scenario when this could happen:

						+---+a		+---+
						| A |-----<>| B |
						+-+-+		+---+
						  | 	
						 /_\
						  |
						+-+-+
						| C |
						+---+
					
						B Binst;

						If you wanted to create an object of type C in Binst, 
						you either did this:
						
						  C Cinst = C::Create(Binst); 
						
						or this:

						  C Cinst = C::Create(Binst, a)
						
						in both cases, Cinst would be created with it's type pointer
						set to C, but in MGA it would be an instance of type A.

					
	
				- fixed getChildren(role, kind) bug

					The desired behaviour of this function is that to return 
					all the children via role 'role' which are of type compatible
					with 'kind'. That is, either type 'kind' or a type derived from 'kind'

					However, this function returned only children with type 'kind' when
					kind was provided. 

					Scenario when this could happen:

						+---+a		+---+
						| A |-----<>| B |
						+-+-+		+---+
						  | 	
						 /_\
						  |
						+-+-+
						| C |
						+---+
					
						B Binst;						//we assume it's already created
						A Ainst = A::Create(Binst,a);	//childrole 'a' could be omitted 
						C Cinst = C::Create(Binst,a);	//childrole 'a' could be omitted  

					and then,

						Binst.__impl()->getChildren(a, A);

						is expected to return both Cinst and Ainst, but it returned
						only Ainst.

				
				Affected are mostly paradigm&backend indepent codes
				which use the createChild(role, kind) and getChildren(role, kind)
				functions with both params provided. 
				(UdmCopy, datanetwork assignment operator are such. PatternMatcher?)


  04/12/02	-	endre
				
				Fixed getParent(). Now it takes ParentRole() into account.
				It returns the parent only when tha parentrole matches.

  03/16/02  -   Fixed GmeDataNetwork::setChildren().  - Tihamer Levendovszky  
  03/16/02	-	BUG: parent()=NULL does not work. SetParent should be fixed
  03/10/02  -   Fixed GmeDataNetwork::OpenExisting(). - Tihamer Levendovszky
  03/06/02	-	Fixed GmeDataNetwork::SaveAs(). Now it works.	-	endre

*/
// Control SUPPORT for folders here!!!!!!!!!!!!!!!!!!




#pragma warning( disable : 4786 )	// this is the stupid warning with truncating identifiers to 255 chars
#include "CommonHeaders.h"
#include <map>


using namespace METALib;
using namespace MGALib;

#include "MgaDefs.h"


#define WRITE_OP_REFRESH_RATE 26		//this value was approximated by binary search, try&error
#define NS_REGNODE_NAME "__udm_namespace"
#include "UdmGme.h"
#include "GmeObject.h"



namespace UdmGme 
{
	struct assocmapitem
	{
		
		::Uml::AssociationRole primary;
		IMgaMetaFCOPtr  metaobj;
		//if metaobj is null, there may be, depending on the name of the class to be created,
		//multiple metaobjs,
		//which will be computed "runtime"
		// this is because inheritence is not supported by MGA at all,
		// if in UML there is a supertype association class,
		// metaobjs will contain the connection objects which are inherited from the UML assocclass
		// and also can be instantiated in the MGA layer
		IMgaMetaFCOPtr* metaobjs;		
		int metaobjs_count;
		objtype_enum ot;

		//we need a flag showing that this is just a refport container helper connection
		//if this is true, primary will be the rolw with the name
		//and metaobj will be the MGA Meta Connection object
		bool rp_helper;
		assocmapitem() : metaobjs_count(0),  metaobjs(NULL), rp_helper(false) {};
	};

	
	struct privdata 
	{
		IMgaProjectPtr project;
		IMgaTerritoryPtr terr;
	};

	void com_exception(HRESULT a, IUnknown *b, REFIID c) 
	{
		char s[100];
		ISupportErrorInfoPtr pp = b;
		SmartBSTR str;
		if(pp) 
		{
			if(pp->InterfaceSupportsErrorInfo(c) == S_OK) 
			{
				IErrorInfoPtr ee;
				GetErrorInfo(0, &ee);
				BSTR bbstr;
				ee->GetDescription(&bbstr);
				str = bbstr;
				SysFreeString(bbstr);
			}
		}
		if(!!str) sprintf(s, "Com exception: %S\n", (BSTR)str);
		else sprintf(s, "Com exception: #%08X\n", a);

		throw udm_exception(s);
	}

	string getnameforassoc(const ::Uml::Association &ass, bool generate_name) 
	{
		::Uml::Class acl = ass.assocClass();
		string ret;
		if(acl) ret = acl.name();
		else 
		{
			ret = ass.name();
			if(generate_name && ret.empty()) 
			{
				set< ::Uml::AssociationRole> roles = ass.roles();
				set< ::Uml::AssociationRole>::iterator j = roles.begin(); 
				ret = "noname_";
				ret += (string)((::Uml::Class)j->target()).name();
				ret += "_to_";
				ret += (string)((::Uml::Class)(++j)->target()).name();
			}
		}
		return ret;
	}
	
	

	typedef pair<bool, string> RpHelperID;	// pair<role_is_navigable, object_id>
	typedef vector<RpHelperID> RpHelperIDs;

	RpHelperIDs StringToList(const string &src)
	{
		RpHelperIDs ret;

		int begin, end;
		begin = src.find_first_not_of(' ');
		if (begin != string::npos)
		{
			end = src.find_first_of(' ', begin);
			string id = src.substr(begin, end - begin);
			while (id.length())
			{
				ret.push_back( RpHelperID((id.substr(0, 1) == "1"), id.substr(1)) );
				begin = src.find_first_not_of(' ', end);
				if (begin == string::npos) break;
				end = src.find_first_of(' ', begin);
				id = src.substr(begin, end - begin);
			}
		}

		return ret;
	}

	string ListToString(const RpHelperIDs &ids)
	{
		string ret;
		for (RpHelperIDs::const_iterator i = ids.begin(); i != ids.end(); i++)
		{
			if (ret.length()) ret += " ";
			ret += i->first ? "1" : "0";
			ret += i->second;
		}
		return ret;
	}

	// removes the ID of peer_toRemove from fco's registry
	// to clear peer_toRemove's registry too, call it again with arguments reversed and the other role name
	void RpHelperRemoveFromRegistry(const IMgaFCOPtr &fco, const IMgaFCOPtr &peer_toRemove, const string &role_name)
	{
		SmartBSTR co_ids = fco->RegistryValue[role_name.c_str()];
		if (!(!co_ids))
		{
			RpHelperIDs ids = StringToList(string(co_ids));
			for (RpHelperIDs::iterator i = ids.begin(); i != ids.end(); i++)
			{
				if (i->second.compare(peer_toRemove->GetID()) == 0)
					ids.erase(i);
			}
			if (ids.size())
				COMTHROW(fco->put_RegistryValue(SmartBSTR(role_name.c_str()), SmartBSTR(ListToString(ids).c_str())));
			else
				COMTHROW(fco->put_RegistryValue(SmartBSTR(role_name.c_str()), NULL));
		}
	}

	void RpHelperAddToRegistry(const IMgaFCOPtr &fco, const IMgaFCOPtr &peer_toAdd, const string &role_name, bool role_isNavigable)
	{
		SmartBSTR co_ids = fco->RegistryValue[role_name.c_str()];
		RpHelperIDs ids;
		if (!(!co_ids))
			ids = StringToList(string(co_ids));

		bool already_exists = false;
		for (RpHelperIDs::const_iterator i = ids.begin(); i != ids.end(); i++)
		{
			if (i->second.compare(peer_toAdd->GetID()) == 0)
			{
				already_exists = true;
				break;
			}
		}
		if (!already_exists)
		{
			ids.push_back( RpHelperID(role_isNavigable, string(peer_toAdd->GetID())) );
			COMTHROW(fco->put_RegistryValue(SmartBSTR(role_name.c_str()), SmartBSTR(ListToString(ids).c_str())));
		}
	}

	IMgaFCOsPtr RpHelperFindPeerFCOsFromRegistry(const IMgaFCOPtr &self, const string &role_name, bool only_ifNavigable, const GmeDataNetwork *dn)
	{
		IMgaFCOsPtr ret;
		ret.CreateInstance("Mga.MgaFCOs");

		SmartBSTR co_ids = self->RegistryValue[role_name.c_str()];
		if (!(!co_ids))
		{
			RpHelperIDs ids = StringToList(string(co_ids));
			for (RpHelperIDs::const_iterator i = ids.begin(); i != ids.end(); i++)
			{
				if (!only_ifNavigable || i->first)
				{
					//extra check if the obtained value is an ID
					string co_id_str = i->second;
					if ((co_id_str.length() > 3) && ( co_id_str.substr(0, 3).compare("id-") == 0))
					{
						IMgaFCOPtr obj = dn->priv.project->GetObjectByID(co_id_str.c_str());
						COMTHROW(ret->Append(obj));
					}
				}
			}
		};

		return ret;
	}

	IMgaFCOsPtr RpHelperFindPeerFCOs(const IMgaFCOPtr &self,
		const string &role_name, bool role_isNavigable,
		const string &other_role_name, bool other_role_isNavigable,
		const GmeDataNetwork *dn, bool only_ifNavigable, bool set_registry = true);

	IMgaFCOsPtr RpHelperFindPeerFCOsFromModel(const IMgaFCOPtr &self,
		const string &role_name, bool role_isNavigable,
		const string &other_role_name, bool other_role_isNavigable,
		const GmeDataNetwork *dn, bool only_ifNavigable, bool set_registry)
	{
		IMgaFCOsPtr ret;
		ret.CreateInstance("Mga.MgaFCOs");

		if (self->GetObjType() == OBJTYPE_CONNECTION)
		{
			// we are the connection, find the reference (the first reference from
			// the chain of references linking the connection to the source or
			// destination
			IMgaSimpleConnectionPtr conn(self);
			SmartBSTR src_role_name = conn->RegistryValue["sRefParent"];

			try
			{
				IMgaFCOsPtr references = role_name.compare(src_role_name) == 0 ? conn->GetSrcReferences() : conn->GetDstReferences();
				if (references->GetCount() > 0)
				{
					IMgaFCOPtr fco = references->GetItem(1);

					if (!only_ifNavigable || (only_ifNavigable && role_isNavigable))
						COMTHROW(ret->Append(fco));

					if (set_registry)
					{
						RpHelperAddToRegistry(self, fco, role_name, role_isNavigable);
						RpHelperAddToRegistry(fco, self, other_role_name, other_role_isNavigable);
					}
				}
			}
			catch (udm_exception &)
			{
			}
		}
		else if (self->GetObjType() == OBJTYPE_REFERENCE)
		{
			// we are the reference, find the connection (the first connection to
			// this reference for which RpHelperFindPeerFCOs()
			// returns the same reference)
			IMgaReferencePtr reference(self);
			IMgaConnPointsPtr cp = reference->GetUsedByConns();
			MGACOLL_ITERATE(IMgaConnPoint, cp)
			{
				IMgaSimpleConnectionPtr conn = MGACOLL_ITER->Owner;
				IMgaFCOsPtr references = RpHelperFindPeerFCOs(conn, other_role_name, other_role_isNavigable, role_name, role_isNavigable, dn, true, false);
				MGACOLL_ITERATE(IMgaFCO, references)
				{
					if (reference->GetIsEqual(MGACOLL_ITER) == VARIANT_TRUE)
					{
						if (!only_ifNavigable || (only_ifNavigable && role_isNavigable))
							COMTHROW(ret->Append(conn));
						if (set_registry)
						{
							RpHelperAddToRegistry(self, conn, role_name, role_isNavigable);
							RpHelperAddToRegistry(conn, self, other_role_name, other_role_isNavigable);
						}
					};
				}
				MGACOLL_ITERATE_END;
			}
			MGACOLL_ITERATE_END;
		}

		return ret;
	}

	IMgaFCOsPtr RpHelperFindPeerFCOs(const IMgaFCOPtr &self,
		const string &role_name, bool role_isNavigable,
		const string &other_role_name, bool other_role_isNavigable,
		const GmeDataNetwork *dn, bool only_ifNavigable, bool set_registry)
	{
		IMgaFCOsPtr ret;
		ret.CreateInstance("Mga.MgaFCOs");

		set<string> seen_fcos;

		IMgaFCOsPtr fcos = RpHelperFindPeerFCOsFromRegistry(self, role_name, only_ifNavigable, dn);
		MGACOLL_ITERATE(IMgaFCO, fcos)
		{
			if (seen_fcos.find(string(MGACOLL_ITER->GetID())) == seen_fcos.end())
			{
				COMTHROW(ret->Append(MGACOLL_ITER));
				seen_fcos.insert(string(MGACOLL_ITER->GetID()));
			}
		}
		MGACOLL_ITERATE_END;

		fcos = RpHelperFindPeerFCOsFromModel(self, role_name, role_isNavigable, other_role_name, other_role_isNavigable, dn, only_ifNavigable, set_registry);
		MGACOLL_ITERATE(IMgaFCO, fcos)
		{
			if (seen_fcos.find(string(MGACOLL_ITER->GetID())) == seen_fcos.end())
			{
				COMTHROW(ret->Append(MGACOLL_ITER));
				seen_fcos.insert(string(MGACOLL_ITER->GetID()));
			}
		}
		MGACOLL_ITERATE_END;

		return ret;
	}

	IMgaFCOPtr getPrefferedSrcRef(const IMgaSimpleConnectionPtr& conn, const GmeDataNetwork * dn)
	{
		SmartBSTR regrolename = conn->RegistryValue["sRefParent"];
		IMgaFCOPtr ret;
		if (!(!regrolename))
		{
			IMgaFCOsPtr references = RpHelperFindPeerFCOs(conn, string(regrolename), true, "", false, dn, true, false);
			if (references->GetCount() == 1)
					ret = references->GetItem(1);
		};
		return ret;
	};

	IMgaFCOPtr getPrefferedDstRef(const IMgaSimpleConnectionPtr& conn, const GmeDataNetwork * dn)
	{
		SmartBSTR regrolename = conn->RegistryValue["dRefParent"];
		IMgaFCOPtr ret;
		if (!(!regrolename))
		{
			IMgaFCOsPtr references = RpHelperFindPeerFCOs(conn, string(regrolename), true, "", false, dn, true, false);
			if (references->GetCount() == 1)
					ret = references->GetItem(1);
		};
		return ret;

	};

	IMgaFCOsPtr FindReferencesToFCOInParent(const IMgaModelPtr& connection_par,const IMgaFCOPtr& peer,const IMgaFCOPtr& preffered_ref = NULL) 
	{

		IMgaModelPtr peer_parent;

		peer->get_ParentModel(&peer_parent);//only models have ports, so this is also safe.

		if ((connection_par != NULL) && (peer_parent != NULL))
		{
			IMgaFCOsPtr cp_children;
			connection_par->get_ChildFCOs(&cp_children);

			IMgaFCOsPtr references;
				
			bool found = false;			
			MGACOLL_ITERATE(IMgaFCO, cp_children)
			{

				IMgaFCOPtr cp_child = MGACOLL_ITER;
				if (cp_child->GetObjType() != OBJTYPE_REFERENCE) continue;
				if ((preffered_ref != NULL) && (preffered_ref->GetIsEqual(cp_child) != VARIANT_TRUE)) continue;
							
				IMgaReferencePtr cp_ref_child(cp_child);
							
				IMgaFCOPtr reffered;//immediate reffered
				COMTHROW(cp_ref_child->get_Referred(&reffered));
				if (reffered==NULL) continue;//null reference

				IMgaFCOPtr final_reffered(reffered);//final reffered
			
				references.CreateInstance("Mga.MgaFCOs");
							
				COMTHROW(references->Append(cp_ref_child));

				while((reffered!=NULL) && reffered->GetObjType() == OBJTYPE_REFERENCE) 
				{
					//loop through references reffering references...
								
					IMgaReferencePtr new_reference(reffered);
					COMTHROW(new_reference->get_Referred(&reffered));
					if (reffered) 
					{
						final_reffered = reffered;
						COMTHROW(references->Append(new_reference));
					}
				}

								
				if (final_reffered->GetIsEqual(peer_parent) == VARIANT_TRUE)
				{	
					found = true;
					break;//ok, don't scan the other objects, we accomplished our objectives.
				}	
				
				references.Release();


			}
			MGACOLL_ITERATE_END

			if (found) return references;
		}



		string debug;

		debug.append("Parent model of the connection: ");
		debug.append( (char *)connection_par->GetName());
		debug.append(", name of peer: ");
		debug.append((char*) peer->GetName());
		


		throw udm_exception(string("Could not reach connecting port FCO through references to it's parent, starting from the connection object. Debug info:") + debug);
		return NULL;
	}


	IMgaFCOsPtr GmeObject::FindReferencesToFCO(const IMgaFCOPtr& peer, const IMgaFCOPtr& preffered_ref ) const
	{
		if (self->GetObjType() != OBJTYPE_CONNECTION)
			throw udm_exception("Method valid only for connections!");

		IMgaModelPtr self_parent;
		self->get_ParentModel(&self_parent);
		return FindReferencesToFCOInParent(self_parent, peer, preffered_ref);
	}
	
	
	void GmeObject::setAssociation(const ::Uml::AssociationRole &meta, const vector<ObjectImpl*> &nvect, int mode, const bool direct)	
	{
		((GmeDataNetwork*)mydn)->CountWriteOps();

		::Uml::Association assoc = meta.parent();
		string rname = meta.name();

//		cout << "MGA BACKEND DEBUG: Self in setAssociation() is:" << (char *) self->GetName() << endl;



		assocmapitem nn =((UdmGme::GmeDataNetwork*) mydn)->amap.find(assoc.uniqueId())->second;

		bool reverse = (nn.primary == meta);

		if(nn.ot == OBJTYPE_MODEL) throw udm_exception("Setting Archetype/Derived relations is not supported");


		vector<ObjectImpl*> kvect = nvect;						 // things to add
		vector<ObjectImpl*> pvect = getAssociation(meta, mode);  // things to delete

		//cout << "MGA BACKEND DEBUG: size of kvect  is: " << kvect.size() << endl;
		//cout << "MGA BACKEND DEBUG: size of pvect  is: " << pvect.size() << endl;

		for(vector<ObjectImpl*>::iterator i = kvect.begin(); i != kvect.end(); ) 
		{
			//cout <<"MGA BACKEND DEBUG: Object present in original kvect: " <<  (char *)(static_cast<GmeObject *>(*i)->self->GetName()) << ", id:" << (char*)(static_cast<GmeObject *>(*i)->self->GetID()) <<  endl;
			for(vector<ObjectImpl*>::iterator j = pvect.begin(); j != pvect.end(); j++) 
			{
				
				/*
				Argh! COM pointers to the same object ain't the same!
				if(static_cast<GmeObject *>(*i)->self == static_cast<GmeObject *>(*j)->self) 
				*/
				IMgaFCOPtr n21 = static_cast<GmeObject *>(*i)->self;
				IMgaFCOPtr n22 = static_cast<GmeObject *>(*j)->self;
				VARIANT_BOOL n = n21->GetIsEqual(n22);
				
				if (n == VARIANT_TRUE)
				{
					(*j)->release();	//pvect is obtained by getAssociation()!!
					pvect.erase(j);
					kvect.erase(i);
					goto bbreak;
				}
			}
			i++;
bbreak:			;
		}

		//cout << "MGA BACKEND DEBUG: size of kvect  NOW is: " << kvect.size() << endl;
		//cout << "MGA BACKEND DEBUG: size of pvect  NOW is: " << pvect.size() << endl;

		


		
		if(nn.ot == OBJTYPE_CONNECTION) 
		{
			// if reverse, get src 
			if(mode == Udm::TARGETFROMCLASS) 
			{
				if(nvect.size() != 1) throw udm_exception("Connection must have exactly one src/dst");
				IMgaFCOPtr peer = static_cast<GmeObject *>(*nvect.begin())->self;
				if(reverse) 
				{
					IMgaFCOPtr pref_ref = getPrefferedSrcRef(IMgaSimpleConnectionPtr(self), (GmeDataNetwork*)mydn);
					if (pref_ref)
					{
						IMgaFCOsPtr references = FindReferencesToFCO(peer, pref_ref);
						COMTHROW(IMgaSimpleConnectionPtr(self)->SetSrc(references, peer));
						
					}
					else
					{
						try
						{
							IMgaSimpleConnectionPtr(self)->SetSrc(NULL, peer);
						}
						catch(udm_exception&) 
						{
							IMgaFCOsPtr references = FindReferencesToFCO(peer);
							COMTHROW(IMgaSimpleConnectionPtr(self)->SetSrc(references, peer));
						}
						
					}

				}//if(reverse) 
				else 
				{
					IMgaFCOPtr pref_ref = getPrefferedDstRef(IMgaSimpleConnectionPtr(self), (GmeDataNetwork*)mydn);
					if (pref_ref)
					{
						IMgaFCOsPtr references = FindReferencesToFCO(peer, pref_ref);
						COMTHROW(IMgaSimpleConnectionPtr(self)->SetDst(references, peer));
					}
					else
					{
						try 
						{

							COMTHROW(IMgaSimpleConnectionPtr(self)->SetDst(NULL, peer));
						}
						catch(udm_exception&) 
						{
							IMgaFCOsPtr references = FindReferencesToFCO(peer);
							COMTHROW(IMgaSimpleConnectionPtr(self)->SetDst(references, peer));
						}
					}
				}//else if(reverse) 
			}//	if(mode == Udm::TARGETFROMCLASS) 
			else if(mode == Udm::CLASSFROMTARGET) 
			{
/*
				IMgaConnPointsPtr conns = self->PartOfConns;
				MGACOLL_ITERATE(IMgaConnPoint, conns) {
					IMgaSimpleConnectionPtr conn = MGACOLL_ITER->Owner;
					if(MGACOLL_ITER->ConnRole == SmartBSTR(reverse ? "dst" : "src") &&
						conn->Meta == nn.metaobj) {
						conn->DestroyObject();
					}									
				}
				MGACOLL_ITERATE_END;
*/
				for(i = pvect.begin(); i != pvect.end(); i++) 
				{
					IMgaSimpleConnectionPtr conn = static_cast<GmeObject *>(*i)->self;
					
					//we need to check if there is an associated helper connection
					GmeObject * go = new GmeObject(conn, mydn);
					go->RemoveHelperConnections();
					delete go;

					conn->DestroyObject();
				}//for i pvect
				for(i = kvect.begin(); i != kvect.end(); i++) 
				{
					IMgaFCOPtr new_peer = static_cast<GmeObject *>(*i)->self;
					
					IMgaSimpleConnectionPtr conn = static_cast<GmeObject *>(*i)->self;
					if(reverse)
					{
						IMgaFCOPtr pref_ref = getPrefferedDstRef(conn, (GmeDataNetwork*)mydn);
						if (pref_ref)
						{
							IMgaFCOsPtr references = static_cast<GmeObject *>(*i)->FindReferencesToFCO(self, pref_ref);
							COMTHROW(conn->SetDst(references, self));
						}
						else
						{
							try
							{
								conn->SetDst(NULL, self);
							}
							catch (udm_exception&)
							{
								IMgaFCOsPtr references = static_cast<GmeObject *>(*i)->FindReferencesToFCO(self);
								COMTHROW(conn->SetDst(references, self));
							}
						}
					}//if(reverse)
					else 
					{
						IMgaFCOPtr pref_ref = getPrefferedSrcRef(conn, (GmeDataNetwork*)mydn);
						if (pref_ref)
						{
							IMgaFCOsPtr references = static_cast<GmeObject *>(*i)->FindReferencesToFCO(self, pref_ref);
							COMTHROW(conn->SetSrc(references, self));
						}
						else
						{
							try
							{
								conn->SetSrc(NULL, self);
							}
							catch(udm_exception&)
							{
							//	cout <<"\t\t SetSrc() failed. " << endl;
							//	cout <<"\t\t Source: " << (char *)(self->GetName())<<endl;
							//	cout <<"\t\t connection: " << (char*)(conn->GetName()) << endl;

								IMgaFCOsPtr references = static_cast<GmeObject *>(*i)->FindReferencesToFCO(self);
								COMTHROW(conn->SetSrc(references, self));

							}
						}
					}//else if(reverse)
				}//for i kvect
			}//if(mode == Udm::CLASSFROMTARGET) 
			else 
			{
				if (nn.rp_helper )
				{
					

					if (kvect.size() > 1 && self->GetObjType() != OBJTYPE_REFERENCE) throw udm_exception("In case of np_helper connection there should be maximum one connecting object!");
					if (kvect.size())
					{
						for (vector<ObjectImpl*>::const_iterator i = kvect.begin(); i != kvect.end(); i++)
						{
                            IMgaFCOPtr connecting_object = static_cast<GmeObject *>(*i)->self;
							RpHelperAddToRegistry(self, connecting_object, meta.name(), meta.isNavigable());
							RpHelperAddToRegistry(connecting_object, self, ::Uml::theOther(meta).name(), ::Uml::theOther(meta).isNavigable());
						}
					} else
					if (pvect.size())
					{
						for (vector<ObjectImpl*>::const_iterator i = pvect.begin(); i != pvect.end(); i++)
						{
                            IMgaFCOPtr connecting_object = static_cast<GmeObject *>(*i)->self;
							RpHelperRemoveFromRegistry(self, connecting_object, meta.name());
							RpHelperRemoveFromRegistry(connecting_object, self, ::Uml::theOther(meta).name());
						}
					};
				}//if (nn.rp_helper)
				else
				{
					IMgaConnPointsPtr conns = self->PartOfConns;
					
					MGACOLL_ITERATE(IMgaConnPoint, conns) 
					{
						IMgaSimpleConnectionPtr conn = MGACOLL_ITER->Owner;
						if(conn->Meta == nn.metaobj) 
						{
							IMgaFCOPtr peer = reverse ? conn->src : conn->dst;
							for(i = pvect.begin(); i != pvect.end(); i++) 
							{
								if(peer == static_cast<GmeObject *>(*i)->self) 
								{
									//we need to check if there is an associated helper connection
									GmeObject * go = new GmeObject( conn, mydn);
									go->RemoveHelperConnections();
									delete go;

									conn->DestroyObject();
									break;
								}
							}		
						}									
					}
					MGACOLL_ITERATE_END;

					IMgaModelPtr parent = self->ParentModel, gparent;
					IMgaMetaRolesPtr roles, groles;
					if(parent) 
					{
						roles = IMgaMetaModelPtr(parent->Meta)->LegalRoles(nn.metaobj);

						gparent = parent->ParentModel;

						if(gparent) 
						{
							groles = IMgaMetaModelPtr(gparent->Meta)->LegalRoles(nn.metaobj);
						}
					}

					for(i = kvect.begin(); i != kvect.end(); i++) 
					{
						IMgaFCOPtr o;
						IMgaFCOPtr oself = static_cast<GmeObject *>(*i)->self;
						HRESULT hs = S_OK+1;
						IMgaModelPtr op = oself->ParentModel, ogp;
						if(op) ogp = op->ParentModel;
						if(parent != NULL && ((parent->GetIsEqual(op)==VARIANT_TRUE) || (parent->GetIsEqual(ogp)==VARIANT_TRUE)) && roles->Count) 
						{
							try
							{
								COMTHROW(parent->raw_CreateSimpleConn(roles->Item[1], reverse ? oself : self, reverse ? self : oself,NULL,NULL, &o));
								hs = S_OK;
							}
							catch(udm_exception&)
							{
								//this is getting complicated,
								//because both connecting end may be through references
								IMgaFCOsPtr src_references, dst_references;
								try
								{
									src_references = FindReferencesToFCOInParent(parent,reverse ? oself : self);
								}
								catch(udm_exception&)
								{
									src_references = NULL;
								}

								try
								{
									dst_references = FindReferencesToFCOInParent(parent,reverse ? self : oself);
								}
								catch(udm_exception&)
								{
									dst_references = NULL;
								}

								hs = parent->raw_CreateSimpleConn(roles->Item[1], reverse ? oself : self, reverse ? self : oself,src_references,dst_references, &o);
							}

						}
						if(hs != S_OK && gparent != NULL && ((parent->GetIsEqual(op)==VARIANT_TRUE) || (parent->GetIsEqual(ogp)==VARIANT_TRUE)) && groles->Count) 
						{
							try
							{
								COMTHROW(gparent->raw_CreateSimpleConn(groles->Item[1], reverse ? oself : self, reverse ? self : oself,NULL,NULL, &o));
								hs = S_OK;
							}
							catch(udm_exception&)
							{
								IMgaFCOsPtr src_references, dst_references;
								try
								{
									src_references = FindReferencesToFCOInParent(gparent,reverse ? oself : self);
								}
								catch(udm_exception&)
								{
									src_references = NULL;
								}

								try
								{
									dst_references = FindReferencesToFCOInParent(gparent,reverse ? self : oself);
								}
								catch(udm_exception&)
								{
									dst_references = NULL;
								}

								hs = gparent->raw_CreateSimpleConn(groles->Item[1], reverse ? oself : self, reverse ? self : oself,src_references,dst_references, &o);
							}
						}

						if(hs != S_OK) throw udm_exception("Cannot create conn association " + getnameforassoc(assoc, true));
					}//for i kvect
				}//else if (nn.rp_helper)
			}//mode  TARGETFROMPEER		
		}//if(nn.ot == OBJTYPE_CONNECTION) 
		else 
		{
		  if(!reverse) 
		  {
			switch(nn.ot) 
			{
			case OBJTYPE_REFERENCE:
							if(nvect.size() > 1) throw udm_exception("Attempt to set multiple values for a reference");
							{
								IMgaFCOPtr tgt; 
								if(nvect.size())  tgt = static_cast<GmeObject *>(*nvect.begin())->self;
								IMgaReferencePtr(self)->Referred = tgt;
							}
							break;
			case OBJTYPE_SET:
							{
								vector<ObjectImpl*>::iterator i;
								for(i = pvect.begin(); i != pvect.end(); i++) {
									IMgaSetPtr(self)->RemoveMember(static_cast<GmeObject *>(*i)->self);										
								}									
								for(i = kvect.begin(); i != kvect.end(); i++) {
									IMgaSetPtr(self)->AddMember(static_cast<GmeObject *>(*i)->self);										
								}									
							}
							break;
		/*	case OBJTYPE_MODEL:
							{
								vector<ObjectImpl*>::iterator i;
								if ( ( pvect.size() > 1) || (nvect.size() > 1))
									throw udm_exception("More than one archetype requested to add/remove!");

								for(i = pvect.begin(); i != pvect.end(); i++) 
								{
									IMgaFCOPtr(self)->DetachFromArcheType();
								}									
								for(i = kvect.begin(); i != kvect.end(); i++) 
								{
									IMgaFCOPtr(self)->AttachToArcheType(static_cast<GmeObject *>(*i)->self, true);										
								}
							}
							break;
		*/	}
		  }
		  else {
			switch(nn.ot) {
			case OBJTYPE_REFERENCE:
							{
								vector<ObjectImpl*>::iterator i;
								for(i = pvect.begin(); i != pvect.end(); i++) {
									IMgaReferencePtr(static_cast<GmeObject *>(*i)->self)->Referred = NULL;										
								}									
								for(i = kvect.begin(); i != kvect.end(); i++) {
									objtype_enum oot = static_cast<GmeObject *>(*i)->self->ObjType;
									objtype_enum oot2 = self->ObjType;
									IMgaReferencePtr(static_cast<GmeObject *>(*i)->self)->Referred = self;										
								}									
							}
							break;
			case OBJTYPE_SET:
							{
								vector<ObjectImpl*>::iterator i;
								for(i = pvect.begin(); i != pvect.end(); i++) {
									IMgaSetPtr(static_cast<GmeObject *>(*i)->self)->RemoveMember(self);										
								}									
								for(i = kvect.begin(); i != kvect.end(); i++) {
									IMgaSetPtr(static_cast<GmeObject *>(*i)->self)->AddMember(self);										
								}									
							}
							break;
			}
		  }
		}  
		
		//free the ObjectImpls in pvect
		vector<ObjectImpl*>::iterator ii;
		for(ii = pvect.begin(); ii != pvect.end(); ii++) 
			(*ii)->release();
							
	};

	//GmeObject member functions
	vector<ObjectImpl*> GmeObject::getAssociation(const ::Uml::AssociationRole &meta, int mode) const 
	{
		vector<ObjectImpl*> ret;

		::Uml::Association assoc = meta.parent();
		
			string rname = meta.name();

			assocmapitem nn = ((GmeDataNetwork*)mydn)->amap.find(assoc.uniqueId())->second;

			bool reverse = (nn.primary == meta);
							
			if(nn.ot == OBJTYPE_CONNECTION) 
			{
				if (nn.rp_helper)
				{
					IMgaFCOsPtr fcos = RpHelperFindPeerFCOs(self,
						meta.name(), meta.isNavigable(),
						::Uml::theOther(meta).name(), ::Uml::theOther(meta).isNavigable(),
						(GmeDataNetwork *)mydn, true);
					MGACOLL_ITERATE(IMgaFCO, fcos)
					{
						ret.push_back(new GmeObject(MGACOLL_ITER, mydn));
					}
					MGACOLL_ITERATE_END;
				}
				else if(mode == Udm::TARGETFROMCLASS) 
				{
					IMgaSimpleConnectionPtr conn(self);
					IMgaFCOPtr peer;
					if(reverse) conn->get_src(&peer);
					else conn->get_dst(&peer);
					if(peer) ret.push_back(new GmeObject( peer, mydn));
				}
				else 
				{
					IMgaConnPointsPtr conns = self->PartOfConns;
					MGACOLL_ITERATE(IMgaConnPoint, conns) 
					{
						IMgaSimpleConnectionPtr conn = MGACOLL_ITER->Owner;
						/*
						BSTR debug_1 = MGACOLL_ITER->ConnRole;

						char * debug_1_ch = (char *)debug_1;
						bool debug_1_b = (MGACOLL_ITER->ConnRole == SmartBSTR(reverse ? "dst" : "src"));
						bool debug_2_b = (conn->Meta->GetMetaRef() == nn.metaobj->GetMetaRef());
						BSTR connection_meta = conn->Meta->GetName();
						BSTR ami_meta = nn.metaobj->GetName();
						*/

						if (nn.metaobj)
						{
							if(MGACOLL_ITER->ConnRole == SmartBSTR(reverse ? "dst" : "src") && 	conn->Meta->GetMetaRef() == nn.metaobj->GetMetaRef()) 
							{
								if(mode == Udm::CLASSFROMTARGET) 
								{
									//ret.push_back(new GmeObject(assoc.assocClass(), conn, mydn));
									ret.push_back(new GmeObject( conn, mydn));
								}
								else if(mode == Udm::TARGETFROMPEER) 
								{
									IMgaFCOPtr peer = reverse ? conn->src : conn->dst;
									ret.push_back(new GmeObject( peer, mydn));
								}
								else throw udm_exception("Invalid access mode");
							};									
						}
						else 
						{
							if (!nn.metaobjs_count) throw udm_exception("Expected >0 metaobjs_count!");
							for  (int i = 0; i < nn.metaobjs_count; i++)
							{
								
								IMgaMetaFCOPtr p = nn.metaobjs[i];
	/*
								BSTR debug_1 = MGACOLL_ITER->ConnRole;
								char * debug_1_ch = (char *)debug_1;
								bool debug_1_b = (MGACOLL_ITER->ConnRole == SmartBSTR(reverse ? "dst" : "src"));
								bool debug_2_b = (conn->Meta->GetMetaRef() == p->GetMetaRef());
								BSTR connection_meta = conn->Meta->GetName();
								BSTR ami_meta = p->GetName();
	*/
								
								if(MGACOLL_ITER->ConnRole == SmartBSTR(reverse ? "dst" : "src") && 	conn->Meta->GetMetaRef() == p->GetMetaRef()) 
								{
									if(mode == Udm::CLASSFROMTARGET) 
									{
										//ret.push_back(new GmeObject(assoc.assocClass(), conn, mydn));
										ret.push_back(new GmeObject( conn, mydn));
									}
									else if(mode == Udm::TARGETFROMPEER) 
									{
										IMgaFCOPtr peer = reverse ? conn->src : conn->dst;
										ret.push_back(new GmeObject( peer, mydn));
									}
									else throw udm_exception("Invalid access mode");
								};									
							};
						};
					}
					MGACOLL_ITERATE_END;
				}
			}
			else 
			{
				if(!reverse)
				{
					switch(nn.ot) 
					{
					case OBJTYPE_REFERENCE:
					{
						IMgaFCOPtr peer = IMgaReferencePtr(self)->Referred;
						if(peer) ret.push_back(new GmeObject( peer, mydn));
					}
					break;
					
					case OBJTYPE_SET:
					{
						IMgaFCOsPtr peers = IMgaSetPtr(self)->Members;
						MGACOLL_ITERATE(IMgaFCO, peers) 
						{
							ret.push_back(new GmeObject( MGACOLL_ITER, mydn));
						}
						MGACOLL_ITERATE_END;
					}
					break;
					case OBJTYPE_MODEL:
					{
						IMgaFCOsPtr peers = self->DerivedObjects;
						MGACOLL_ITERATE(IMgaFCO, peers) 
						{
							ret.push_back(new GmeObject( MGACOLL_ITER, mydn));
						}
						MGACOLL_ITERATE_END;
					}
					break;
					}
				}
				else 
				{
					switch(nn.ot) 
					{
					case OBJTYPE_REFERENCE:
									{
										IMgaFCOsPtr peers = self->ReferencedBy;
										MGACOLL_ITERATE(IMgaFCO, peers) 
										{
											if(MGACOLL_ITER->Meta->GetMetaRef() != nn.metaobj->GetMetaRef()) continue;
											ret.push_back(new GmeObject( MGACOLL_ITER, mydn));
										}
										MGACOLL_ITERATE_END;
									}
									break;
					case OBJTYPE_SET:
									{
										IMgaFCOsPtr peers = self->MemberOfSets;
										MGACOLL_ITERATE(IMgaFCO, peers) 
										{
											if(MGACOLL_ITER->Meta->GetMetaRef() != nn.metaobj->GetMetaRef()) continue;
											ret.push_back(new GmeObject( MGACOLL_ITER, mydn));
										}
										MGACOLL_ITERATE_END;
									}
									break;
					case OBJTYPE_MODEL:
									{
										IMgaFCOPtr peer = self->ArcheType;
										if(peer) ret.push_back(new GmeObject( peer, mydn));
									}
									break;
					}
				}
			};  
		
		return ret;
	}


	ObjectImpl * GmeObject::createChild(
		const ::Uml::CompositionChildRole &role,	
		const ::Uml::Class &kind, 
		const Udm::ObjectImpl* archetype, 
		const bool subtype,
		const bool real_archetype,
		const bool need_safetype )		//this is not used, since this call
										//does not recurse when a a derived/instace
										//object is created with an archetype that has children
										//(this is done by the underlaying MGA layer
	{
		((GmeDataNetwork*)mydn)->CountWriteOps();

		IMgaFCOPtr  nfco;
		if(folderself) 
		{
			if(role) 
			{
				::Uml::Composition comp = Uml::matchChildToParent(kind ? kind : role.target(), m_type);
				if(!comp || comp != role.parent()) 
				{
					throw udm_exception("Ambigious role specification for folder parents");
				}
			}
			IMgaMetaFolderPtr mf;
			IMgaMetaFCOPtr mfco;
			HRESULT hr1 = (folderself->MetaFolder->get_LegalRootObjectByName(SmartBSTR(NAMEGET(kind)), &mfco));
			HRESULT hr2 = (folderself->MetaFolder->get_LegalChildFolderByName(SmartBSTR(NAMEGET(kind)), &mf));
			
			if(mf) 
			{
				if(mfco) CASSERT("Multiple child kinds match");
				IMgaFolderPtr nf;
				COMTHROW(folderself->CreateFolder(mf, &nf));
				//string ns_name = (::Uml::Namespace)m_type.parent_ns() != ::Uml::Namespace(NULL) ? (string)((::Uml::Namespace)m_type.parent_ns()).name() : "";
				//COMTHROW(nf->put_RegistryValue(SmartBSTR(NS_REGNODE_NAME), SmartBSTR(ns_name.c_str())));
				::Uml::Namespace m_type_ns = m_type.parent_ns();
				COMTHROW(nf->put_RegistryValue(SmartBSTR(NS_REGNODE_NAME), SmartBSTR(m_type_ns ? ((string)m_type_ns.name()).c_str() : NULL)));
				GmeObject * retval = new GmeObject( nf, mydn);
				retval->setDefaultAttributes(false);
				return retval;
			}
			else if(mfco) 
			{
				IMgaFCOPtr nfco;
				if (!archetype)
				{
					COMTHROW(folderself->CreateRootObject(mfco, &nfco));
					//string ns_name = (::Uml::Namespace)m_type.parent_ns() != ::Uml::Namespace(NULL) ? (string)((::Uml::Namespace)m_type.parent_ns()).name() : "";
					//COMTHROW(nfco->put_RegistryValue(SmartBSTR(NS_REGNODE_NAME), SmartBSTR(ns_name.c_str())));
					::Uml::Namespace m_type_ns = m_type.parent_ns();
					COMTHROW(nfco->put_RegistryValue(SmartBSTR(NS_REGNODE_NAME), SmartBSTR(m_type_ns ? ((string)m_type_ns.name()).c_str() : NULL)));
					GmeObject * retval =   new GmeObject( nfco, mydn);
					retval->setDefaultAttributes(false);
					return retval;
				}
				else
				{
					COMTHROW(folderself->DeriveRootObject(((GmeObject *)archetype)->self, subtype ? VARIANT_FALSE : VARIANT_TRUE, &nfco));
					
					//string ns_name = (::Uml::Namespace)m_type.parent_ns() != ::Uml::Namespace(NULL) ? (string)((::Uml::Namespace)m_type.parent_ns()).name() : "";
					//COMTHROW(nfco->put_RegistryValue(SmartBSTR(NS_REGNODE_NAME), SmartBSTR(ns_name.c_str())));
					::Uml::Namespace m_type_ns = m_type.parent_ns();
					COMTHROW(nfco->put_RegistryValue(SmartBSTR(NS_REGNODE_NAME), SmartBSTR(m_type_ns ? ((string)m_type_ns.name()).c_str() : NULL)));
				
					GmeObject * retval =   new GmeObject( nfco, mydn);
					return retval;
				}
			}

			else 
				throw udm_exception("Parent cannot have children of this kind");
		}

		IMgaModelPtr m = self;
		IMgaMetaModelPtr pmeta = Meta();
		if(m == NULL || pmeta == NULL) COMTHROW(("Not a model", 1));
		IMgaMetaRolePtr rr;
		if(role) 
		{
			
			if(kind) 
			{
				/*
				if (((::Uml::Class)role.target()) != kind)
				{
					if (!Uml::IsDerivedFrom(kind, role.target()))
						throw udm_exception("GmeObject::CreateChild(): Role-Kindname mismatch");
					rr = GetMetaRoleForKind(kind, pmeta);
				}
				else rr = GetMetaRoleForChildRole(role, pmeta);
				*/
				if (((::Uml::Class)role.target()) != kind)
				{
					if (!Uml::IsDerivedFrom(kind, role.target()))
						throw udm_exception("GmeObject::CreateChild(): Role-Kindname mismatch");
				}
				
				rr = GetMetaRole(kind, role, pmeta);

			}
			else rr = GetMetaRoleForChildRole(role, pmeta);
		}

		else 
		{
			if(!kind) 
				throw udm_exception("Neither role nor kind is given!!!");
			IMgaMetaRolesPtr rrs = pmeta->Roles;
			MGACOLL_ITERATE(IMgaMetaRole, rrs) 
			{
				if(MGACOLL_ITER->kind->Name == SmartBSTR(NAMEGET(kind))) 
				{
					if(rr) 
						throw udm_exception("Multiple childroles match, role must be specified");
					rr = MGACOLL_ITER;
				}
			} MGACOLL_ITERATE_END;
			if(rr == NULL) 
				throw udm_exception("Parent cannot have children of this kind");
		}	

		if (!archetype)
		{
			COMTHROW(m->CreateChildObject(rr, &nfco));
			
			//string ns_name = (::Uml::Namespace)m_type.parent_ns() != ::Uml::Namespace(NULL) ? (string)((::Uml::Namespace)m_type.parent_ns()).name() : "";
			//COMTHROW(nfco->put_RegistryValue(SmartBSTR(NS_REGNODE_NAME), SmartBSTR(ns_name.c_str())));
			::Uml::Namespace m_type_ns = m_type.parent_ns();
			COMTHROW(nfco->put_RegistryValue(SmartBSTR(NS_REGNODE_NAME), SmartBSTR(m_type_ns ? ((string)m_type_ns.name()).c_str() : NULL)));
				
			GmeObject * retval =  new GmeObject( nfco, mydn);
			retval->setDefaultAttributes(false);
			return retval;
		}
		else
		{
			
			COMTHROW(m->DeriveChildObject( ((GmeObject *)archetype)->self,  rr, subtype ? VARIANT_FALSE : VARIANT_TRUE, &nfco));
			//string ns_name = (::Uml::Namespace)m_type.parent_ns() != ::Uml::Namespace(NULL) ? (string)((::Uml::Namespace)m_type.parent_ns()).name() : "";
			//COMTHROW(nfco->put_RegistryValue(SmartBSTR(NS_REGNODE_NAME), SmartBSTR(ns_name.c_str())));
			::Uml::Namespace m_type_ns = m_type.parent_ns();
			COMTHROW(nfco->put_RegistryValue(SmartBSTR(NS_REGNODE_NAME), SmartBSTR(m_type_ns ? ((string)m_type_ns.name()).c_str() : NULL)));
				
			GmeObject * retval =  new GmeObject( nfco, mydn);
			return retval;


		}
		
	};




	void GmeObject::setChildren(const ::Uml::CompositionChildRole &role, const vector<ObjectImpl*> &a, const bool direct) 
	{
		((GmeDataNetwork*)mydn)->CountWriteOps();

		IMgaModelPtr parent = self;
		if(parent == NULL) COMTHROW(("No parent or non-model parent specified", 1));
		
		vector<ObjectImpl*> aa = a;
		IMgaMetaRolePtr rr;

		// FIX: Tihamer Levendovszky - March 2002 
		if(role) rr=GetMetaRoleForChildRole(role,Meta());
		
		IMgaFCOsPtr chds = parent->ChildFCOs;

		MGACOLL_ITERATE(IMgaFCO, chds) 
		{
// keep children with other roles
			if(rr != NULL && rr != MGACOLL_ITER->MetaRole) continue;
// keep children if they are about to be moved here
			for(vector<ObjectImpl *>::iterator i = aa.begin(); i != aa.end(); i++) 
			{
				if(*i && MGACOLL_ITER == static_cast<GmeObject *const>(*i)->self) 
				{
						(*i) = NULL;
						break;
				}
			}
			if(i != aa.end()) continue;

			COMTHROW(MGACOLL_ITER->DestroyObject());
		} MGACOLL_ITERATE_END;

		int cnt = 0;
		IMgaMetaRolesPtr roles;
		IMgaFCOsPtr fcos;
		fcos.CreateInstance("Mga.MgaFCOs");
		roles.CreateInstance("Mga.MgaMetaRoles");
		for(vector<ObjectImpl *>::const_iterator i = aa.begin(); i != aa.end(); i++) 
		{
			if(*i == NULL) continue;
			COMTHROW(fcos->Append(static_cast<GmeObject *const>(*i)->self));
			COMTHROW(roles->Append(rr));
			cnt++;
		};
		
		if(cnt) 
		{
			COMTHROW(parent->MoveFCOs(fcos,roles,NULL));
		}
	};


	vector<ObjectImpl*> GmeObject::getChildren(const ::Uml::CompositionChildRole &role, const ::Uml::Class &kind) const 
	{
		vector<ObjectImpl*> ret;
		IMgaFCOsPtr chds;

		if(folderself) 
		{
			if(role) 
			{
				::Uml::Composition comp = Uml::matchChildToParent(kind ? kind : role.target(), m_type);
				if(!comp || comp != role.parent()) 
				{
					throw udm_exception("Ambigious role specification for folder parents");
				}
			}
			IMgaFoldersPtr fchds = folderself->ChildFolders;
			
			MGACOLL_ITERATE(IMgaFolder, fchds) 
			{
				GmeObject *p = new GmeObject( MGACOLL_ITER, mydn);
				if(!kind || Uml::IsDerivedFrom(p->m_type, kind))
					ret.push_back(p);
				else delete p;
			} MGACOLL_ITERATE_END;

			chds = folderself->ChildFCOs;
			MGACOLL_ITERATE(IMgaFCO, chds) 
			{
				GmeObject *p = new GmeObject( MGACOLL_ITER, mydn);
				if(!kind || Uml::IsDerivedFrom(p->m_type, kind))
					ret.push_back(p);
				else delete p;
			} MGACOLL_ITERATE_END;

			return ret;
		}

		IMgaModelPtr model = self;
		if(model == NULL) return ret;
		//IMgaMetaRolePtr rr;
		
		
		
		chds = model->ChildFCOs;
		MGACOLL_ITERATE(IMgaFCO, chds) 
		{
			/*
				MGA's MetaRole is completly different from UDM's CompositionChildRole:

						    _	CompostionRole if CompositionRole defined, and role.target() has no descendants
						   |	
				MetaRole = |_	kind+CompostionRole if CompositionRole defined and role.target() has descendants	
						   |
						   |_	the kind of the child, when CompostionRole is not defined

				This creates a lot of trouble when objects are contained via their
				inherited composition child roles. 
				 
				So, we create a set of strings, which will contain:

				1. role.name()
				2. all the names of role.target() descendants, including self
				3. for all 'name' in names of role.target()descendant, including self,
					the name + role.name()

				If we found the MGACOLL_ITER->MetaRole in this set of strings then it's OK,
				it should be returned

				the reason why we check against the first option right here and 
				avoid set operation is that this option will be the most common 
				case, when ever the target of the role has no descendant classes
				the name of the role will be the same as the MGA CompositionRole

				the set<string> containing the 2. and 3. options are obtained by
				GmeDataNetwork::getMetaRoleFilter(role), function which maintains
				a map<role, set<string>> and creates the sets only once.
			*/

			if (role)
			{
				//the CompositionRole of the contained FCO
				string MetaRole((const char *)MGACOLL_ITER->MetaRole->Name);

				if (MetaRole != (string)role.name())//most common case
				{
					//get the possible MetaRoles for containment via this role
					set<string> MetaRoleFilter = ((GmeDataNetwork*)mydn)->GetMetaRoleFilter(role);
					if (MetaRoleFilter.find(MetaRole) == MetaRoleFilter.end()) 
						continue;//this means that MGACOLL_ITER is not contained via 'role' 
					//else is OK!
				}//else is OK
			}
			try 
			{
				GmeObject *p = new GmeObject( MGACOLL_ITER, mydn);
				if(!kind || Uml::IsDerivedFrom(p->m_type, kind))	
					ret.push_back(p);
				else delete p;
			} catch(udm_exception &) 
			{ 
				if(MGACOLL_ITER->GetObjType() != OBJTYPE_CONNECTION) throw;
			} 
		} MGACOLL_ITERATE_END;
		return ret;
	};

	void GmeObject::detach() 
	{
	//	COMTHROW(("Cannot detach",1));
		setParent(NULL, NULL);
	};

	void GmeObject::RemoveHelperConnections()
	{
		//we have to check if this object has an rp_helper helper connection
		if (self)
		{//folders won;t have connections
			set< ::Uml::AssociationRole> all_roles;
			set< ::Uml::AssociationRole> ars = Uml::AncestorAssociationTargetRoles(m_type);//.associationRoles();
			set< ::Uml::AssociationRole>::iterator ars_i;
			for (ars_i = ars.begin(); ars_i != ars.end(); ars_i++)
			{
				if (ars_i->isNavigable()) all_roles.insert(*ars_i);
				if (Uml::theOther(*ars_i).isNavigable()) all_roles.insert(Uml::theOther(*ars_i));

			};
			
			for (ars_i = all_roles.begin(); ars_i != all_roles.end(); ars_i++)
			{
				string oar_name = ars_i->name();
				::Uml::Association assoc = ars_i->parent();
				assocmapitem nn = ((GmeDataNetwork *)__getdn())->amap.find(assoc.uniqueId())->second;
				if (nn.ot == OBJTYPE_CONNECTION && nn.rp_helper)
				{
					IMgaFCOsPtr fcos = RpHelperFindPeerFCOs(self,
						ars_i->name(), ars_i->isNavigable(),
						::Uml::theOther(*ars_i).name(), ::Uml::theOther(*ars_i).isNavigable(),
						(GmeDataNetwork *)__getdn(), false, false);
					MGACOLL_ITERATE(IMgaFCO, fcos)
					{
						RpHelperRemoveFromRegistry(MGACOLL_ITER, self, ars_i->name());
					}
					MGACOLL_ITERATE_END;
				};
			};
		};
	};

	void GmeObject::setParent(ObjectImpl *a, const ::Uml::CompositionParentRole &role, const bool direct) 
	{
		((GmeDataNetwork*)mydn)->CountWriteOps();

		IMgaModelPtr parent;
		if (!a || a == &Udm::_null)
		{	
			long oStatus;
			COMTHROW(objself->get_Status(&oStatus));
			if (oStatus == OBJECT_EXISTS)
			{
				
				RemoveHelperConnections();
				COMTHROW(objself->DestroyObject());	
			}
				
			
			//if this datanetwork is part of a project,
			//I might have a placeholder object,
			//which also should be deleted
			Udm::UdmProject * pr = NULL;
			if (__getdn()) pr = __getdn()->GetProject();
			if (pr)
			{
				Object po = pr->GetPlaceHolder(clone(), false);
				if (po) po.DeleteObject();
			}

			return;
		}
		parent = static_cast<GmeObject *>(a)->self;
		if(parent == NULL) COMTHROW(("No parent or non-model parent specified", 1));

		IMgaMetaRolePtr rr;
		if(role)  
		{
			rr = GetMetaRoleForChildRole(Uml::theOther(role), parent->Meta);
			if(rr->kind->Name != SmartBSTR(NAMEGET(m_type))) CASSERT("Role-Kindname mismatch");
		}
#ifndef DEDUCE_NULLROLES
		else 
		{

			IMgaMetaFCOPtr childmfco = Meta();
			
			// FIX:Tihamer Levendovszky
			IMgaMetaModelPtr pParentMeta=static_cast<GmeObject *>(a)->Meta();

			IMgaMetaRolesPtr mrs;
			COMTHROW(pParentMeta->get_Roles(&mrs));
			// end of FIX  

			MGACOLL_ITERATE(IMgaMetaRole, mrs) 
			{
				if(MGACOLL_ITER->kind == childmfco) 
				{
					rr = MGACOLL_ITER;
					break;
				}
			} 
			MGACOLL_ITERATE_END;
			if(rr == NULL) CASSERT("Parent cannot have this child");
		}
#endif
		IMgaFCOsPtr fcos;
		IMgaMetaRolesPtr roles;

		fcos.CreateInstance("Mga.MgaFCOs");
		roles.CreateInstance("Mga.MgaMetaRoles");
		COMTHROW(fcos->Append(self));
		COMTHROW(roles->Append(rr));
		COMTHROW(parent->MoveFCOs(fcos,roles,NULL));
	};


	ObjectImpl *GmeObject::getParent(const ::Uml::CompositionParentRole &role) const 
	{
		IMgaMetaRolePtr rr;

		if (role)
		{
			
			

			IMgaMetaRolePtr real_role;			
			COMTHROW (self->get_MetaRole(&real_role));
			::Uml::CompositionChildRole ccr = Uml::theOther(role);
			
			//in most cases, the role name matches
			if (real_role->Name != SmartBSTR(((string)ccr.name()).c_str()))
			{
				//however, if it doesn't it still may be an inerited childrole
				//and in such cases the MGA RoleName is not the same as the name
				//of the CompositionChildRole

				bool found = false;
				set< ::Uml::Class> descendants = Uml::DescendantClasses(ccr.target());
				set< ::Uml::Class>::iterator d_i = descendants.begin();

				while (!found && d_i != descendants.end())
				{
					::Uml::Class descendant = *d_i++;
					found = (real_role->Name == SmartBSTR( ((string)descendant.name()).c_str() ));
				}

				//and it also may be one of inherited multiple chilroles,
				//then the MGA RoleName is a concatenated string
				//kind + role 
				while (!found && d_i != descendants.end())
				{
					::Uml::Class descendant = *d_i++;
					found = (real_role->Name == SmartBSTR( ((string)descendant.name() + (string)ccr.name()).c_str()  ));
				}

				//if still not found, than the this is not contained via the requested role
				if (!found) return &Udm::_null;		
			}
		}

		
		IMgaObjectPtr po;
		COMTHROW(objself->GetParent(&po, NULL));
		IMgaModelPtr m(po);

		if(m) 
			return new GmeObject( m, mydn);
		
		IMgaFolderPtr f(po);
		
		if(f) 
			return new GmeObject( f, mydn);

		return &Udm::_null;
	}

	IMgaMetaRolePtr GmeObject::GetMetaRole(::Uml::Class kind, ::Uml::CompositionChildRole ccr, IMgaMetaModelPtr mmodel)
	{
		IMgaMetaRolePtr rr;
		if(mmodel == NULL) 
			throw udm_exception("Metamodel not found");
	
		string mn;
		if (Uml::HasChildRoleMultipleTargets(ccr))
		{
			//metarole = kindname + rolename

			//string shr = Uml::MakeShortRoleName(ccr);
			//string kn = kind.name();

			if ( ((string)ccr.name()).compare(((::Uml::Class)ccr.target()).name()) == 0)
			{
				//the rolename might be created with ccr.target().name()
				//by the CPP code generator. Hence, the MGA rolename may be
				//empty or may be Uml::MakeShortRoleName, no one can tell.
				
				//first we try without rolename appended, this happens more often
				try 
				{
					mn = kind.name();
					rr = mmodel->RoleByName[SmartBSTR(mn.c_str())];
				}
				catch(...)
				{
					mn = (string)kind.name() + (string)ccr.name();
					rr = mmodel->RoleByName[SmartBSTR(mn.c_str())];

				}
			}
			else
			{
				mn = (string)kind.name() + (string)ccr.name();
				rr = mmodel->RoleByName[SmartBSTR(mn.c_str())];
			}
		}
		else
		{
			//metarole = rolename ? rolename : kindname
			//this is exactly the same thing as MakeShortRolename

			
			//MakeShortRolename is not good - when ccr has no name, and it points towards an abstract base class,
			//the returned string will be the name of the abstract base class, but it should be 

			string rn = ccr.name();
			if (rn.empty())
			{
				string kn = kind.name();
				rr = mmodel->RoleByName[SmartBSTR(kn.c_str())];
			}
			else
				rr = mmodel->RoleByName[SmartBSTR(rn.c_str())];
			
			//mn = Uml::MakeShortRoleName(ccr);
			

		}

		if(rr == NULL) 
			throw udm_exception("Role not found in model: " + mn);

		return rr;

	};

	IMgaMetaRolePtr GmeObject::GetMetaRoleForChildRole(::Uml::CompositionChildRole meta, IMgaMetaModelPtr mmodel) 
	{ 
		IMgaMetaRolePtr rr;
		if(mmodel == NULL) 
			throw udm_exception("Metamodel not found");
		string mn = Uml::MakeShortRoleName(meta);
		if(mn.empty()) 
			mn = NAMEGET(::Uml::Class(meta.target()));
		rr = mmodel->RoleByName[SmartBSTR(mn.c_str())];
		if(rr == NULL) 
			throw udm_exception("Role not found in model: " + mn);
		return rr;
	};		
/*
	IMgaMetaRolePtr GmeObject::GetMetaRoleForKind(::Uml::Class kind, IMgaMetaModelPtr mmodel)
	{
		IMgaMetaRolePtr rr;
		if(mmodel == NULL) 
			throw udm_exception("Metamodel not found");
		string mn = kind.name();
		rr = mmodel->RoleByName[SmartBSTR(mn.c_str())];
	
		if(rr == NULL) 
			throw udm_exception("Role for kind not found in model: " + mn);
		return rr;
	};
*/
	string GmeObject::getStringAttr(const ::Uml::Attribute &meta) const
	{
		SmartBSTR val;
		string ret;

		if (meta.registry())
		{
			//to be written as a registry value
			IMgaRegNodePtr reg_node;
			BSTR reg_node_name = SmartBSTR(((string)meta.name()).c_str());
		
			if (folderself)
				COMTHROW(folderself->get_RegistryNode(reg_node_name, &reg_node));
			else
				COMTHROW(self->get_RegistryNode(reg_node_name, &reg_node));
				
			val = reg_node->Value;
			return val.length()? (char*)val : "";


		}
		if((string)meta.name() == "name") val = objself->Name;
		else if((string)meta.name() == "position") 
		{
			long x, y;
			IMgaPartsPtr parts; 
			if(testself->MetaRole != NULL && (parts = testself->Parts)->Count > 0) 
			{
				long count = testself->Parts->Count;
				if (count == 1)
				{
					IMgaPartPtr part = parts->Item[1];
					COMTHROW(part->GetGmeAttrs(NULL, &x, &y));
					char buf[30];
					sprintf(buf,"(%d,%d)", x, y);
					return buf;
				}
				else
				{
					//it's defitively  > 1
					for (int i = 1; i <= count; i++)
					{
						IMgaPartPtr part = parts->Item[i];
						COMTHROW(part->GetGmeAttrs(NULL, &x, &y));
						SmartBSTR aspect =  part->MetaAspect->Name;
						ret += (char *) aspect;

						char buf[20];
						sprintf(buf,"(%d,%d);", x, y);
						ret += buf;

					}

					return ret;
				}
			}
			else return("");
		}
		else val = testself->StrAttrByName[SmartBSTR(NAMEGET(meta))];
		return (char *)val;
	}

	typedef pair<const long, const long> pos_in_aspect;
	typedef map<const string, const pos_in_aspect> part_position;

	part_position getPartPosition(const string &input)
	{
		part_position ret;
		long x, y;
		if (*(input.begin()) == '(')
		{
			//one(main) aspect, only one position in the string
			if (sscanf(input.c_str(),"(%d,%d)", &x, &y) != 2)
				throw udm_exception("Invalid location string");

			ret.insert(part_position::value_type(string(), pos_in_aspect(x, y)));
			return ret;
		};
		
		int newpos, prevpos = 0;
		

		while ((newpos = input.find(';', prevpos)) != string::npos)
		{
			string posstring = input.substr(prevpos, newpos-prevpos);
			prevpos = newpos + 1;

			int asppos = posstring.find('(', 0);
			
			string asp = posstring.substr(0, asppos);//the name of the aspect
			string position = posstring.substr(asppos);//the two coordinates
			
			if (sscanf(position.c_str(),"(%d,%d)", &x, &y) != 2)
				throw udm_exception("Invalid location string");

			ret.insert(part_position::value_type(asp, pos_in_aspect(x, y)));
			
		}
		return ret;
	};

	void GmeObject::setStringAttr(const ::Uml::Attribute &meta, const string &a, const bool direct)
	{
		((GmeDataNetwork*)mydn)->CountWriteOps();

		if (meta.registry())
		{
			//to be written as a registry value
			IMgaRegNodePtr reg_node;
			BSTR reg_node_name = SmartBSTR(((string)meta.name()).c_str());
		
			if (folderself)
				COMTHROW(folderself->get_RegistryNode(reg_node_name, &reg_node));
			else
				COMTHROW(self->get_RegistryNode(reg_node_name, &reg_node));
				
			COMTHROW(reg_node->put_Value(SmartBSTR(a.c_str())));


		}
		else if((string)meta.name() == "name") objself->Name = SmartBSTR(a.c_str());
		else if((string)meta.name() == "position") 
		{
			if (!a.size()) return;		//empty strings should be allowed and nothing should happen in such cases.

			if(testself->MetaRole == NULL) return;
			IMgaPartsPtr parts = testself->Parts;
			if(parts->Count == 0) return;

			const part_position poss = getPartPosition(a);

			if(poss.size()==1)
			{
				//position in main aspect will be set
				IMgaPartPtr part = parts->Item[1];
				COMTHROW(part->SetGmeAttrs(NULLBSTR, poss.begin()->second.first,poss.begin()->second.second ));
			}
			else
			{
				//set the positions in all aspects which are present in the position string
			
				MGACOLL_ITERATE(IMgaPart, parts) 
				{
					const string aspect = (const char *) (MGACOLL_ITER->MetaAspect->Name);
					part_position::const_iterator poss_i = poss.find(aspect);

					if ( poss_i != poss.end())
						COMTHROW(MGACOLL_ITER->SetGmeAttrs(NULLBSTR, poss_i->second.first,poss_i->second.second));
					
					
				} MGACOLL_ITERATE_END;
			}

		}
		else testself->StrAttrByName[SmartBSTR(NAMEGET(meta))] = SmartBSTR(a.c_str());
	};

	bool GmeObject::getBooleanAttr(const ::Uml::Attribute &meta) const	
	{
		return testself->BoolAttrByName[SmartBSTR(NAMEGET(meta))] == VARIANT_TRUE;
	}

	void GmeObject::setBooleanAttr(const ::Uml::Attribute &meta, bool a, const bool direct)
	{
		((GmeDataNetwork*)mydn)->CountWriteOps();
		testself->BoolAttrByName[SmartBSTR(NAMEGET(meta))] = a ? VARIANT_TRUE : VARIANT_FALSE;
	}

	__int64 GmeObject::getIntegerAttr(const ::Uml::Attribute &meta) const
	{
		return __int64(testself->IntAttrByName[SmartBSTR(NAMEGET(meta))]);
	}

	void GmeObject::setIntegerAttr(const ::Uml::Attribute &meta, __int64 a, const bool direct)
	{
		((GmeDataNetwork*)mydn)->CountWriteOps();
		testself->IntAttrByName[SmartBSTR(NAMEGET(meta))] = (long)a;
	}

	double GmeObject::getRealAttr(const ::Uml::Attribute &meta) const
	{
		return testself->FloatAttrByName[SmartBSTR(NAMEGET(meta))];
	}

	void GmeObject::setRealAttr(const ::Uml::Attribute &meta, double a, const bool direct)
	{
		((GmeDataNetwork*)mydn)->CountWriteOps();
		testself->FloatAttrByName[SmartBSTR(NAMEGET(meta))] = a;
	}

	

	uniqueId_type GmeObject::uniqueId() const 
	{
		long p, c;
		SmartBSTR nn;
		if (__uniqueId_set) return __uniqueId;

		if(folderself) 
			nn = folderself->ID;
		else 
			nn = self->ID;

		if(swscanf(nn, OLESTR("id-%04lx-%08lx"), &c, &p) != 2 ||
			(c-=100) > OBJTYPE_FOLDER || c < OBJTYPE_MODEL || p > 100000000) 
		{
			COMTHROW(("OBJID too big or invalid", 1));
		}
		return __set_uniqueId(100000000 * c + p);
	};


	uniqueId_type GmeObject::__set_uniqueId(uniqueId_type id) const
	{
		((GmeObject*)this)->__uniqueId = id;
		((GmeObject*)this)->__uniqueId_set = true;
		return id;
	};

	const ::Uml::Class & GmeObject::type() const 
	{ 
		return m_type;
	};

	IMgaMetaBasePtr GmeObject::Meta() const 
	{
		if(folderself) 
			return folderself->MetaBase;
		else 
			return self->MetaBase;
	};

	IMgaMetaFCOPtr GmeObject::MetaFCO() const 
	{
		return testself->Meta;
	};

	//::Uml::Class GmeObject::findClass(const set< ::Uml::Class> &classes) 


	
	::Uml::Class GmeObject::findClass() 
	{
		SmartBSTR name = Meta()->Name;
		SmartBSTR ns_name = Meta()->RegistryValue[NS_REGNODE_NAME];
		string key;
		if (!ns_name)
		{
			string dgr_name= mydn->GetRootMeta().name();
			//key = string((const char *)dgr_name.c_str()) + ':' + string((const char *)name);
			key = string((const char *)name);
		}
		else
		{
			key = string((const char *)ns_name) + ':' + string((const char *)name);
		}


		map<string, const ::Uml::Class>::iterator j = ((GmeDataNetwork*)mydn)->meta_class_cache.find(key);

		if (j == ((GmeDataNetwork*)mydn)->meta_class_cache.end())
			throw udm_exception("Cannot find Udm metaobject for GME kind: " + name);

		return j->second;	
	
	};


	inline GmeObject::GmeObject(const ::Uml::Class &meta, IMgaFCO *obj, const DataNetwork * dn) :  m_type(meta), self(obj) 
	{ 
		__uniqueId_set=false;
		mydn = dn;
	};

	inline GmeObject::GmeObject(IMgaFCO *obj, const DataNetwork * dn) : self(obj) 
	{
		//set< ::Uml::Class> classes = diagram.classes();
		__uniqueId_set=false;
		mydn = dn;
		m_type = findClass();
		if (!mydn) throw udm_exception("Data Network is NULL in constructor! GmeObject without a data network ?!");
	};

	inline GmeObject::GmeObject(const ::Uml::Class &meta, IMgaFolder *obj, const DataNetwork * dn) :  m_type(meta), folderself(obj) 
	{
		__uniqueId_set=false;
		mydn = dn;
		if (!mydn) throw udm_exception("Data Network is NULL in constructor! GmeObject without a data network ?!");
	};

	inline GmeObject::GmeObject( IMgaFolder *obj, const DataNetwork * dn) : folderself(obj) 
	{
		//set< ::Uml::Class> classes = diagram.classes();
		__uniqueId_set=false;
		mydn = dn;
		m_type = findClass();
		if (!mydn) throw udm_exception("Data Network is NULL in constructor! GmeObject without a data network ?!");
	};

	inline ObjectImpl * GmeObject::clone()
	{
		GmeObject *bb = new GmeObject(m_type, self, mydn);
		bb->folderself = folderself;
		return bb;
		if (!mydn) throw udm_exception("Data Network is NULL in constructor! GmeObject without a data network ?!");
	};

	inline void GmeObject::release()
	{
		delete this;
	};

	inline vector<ObjectImpl*> GmeObject::getDerived() const
	{
		vector<ObjectImpl*> ret;
		IMgaFCOsPtr peers = self->DerivedObjects;
		MGACOLL_ITERATE(IMgaFCO, peers) 
		{
			IMgaFCOPtr peer = MGACOLL_ITER;
			if (!peer->IsInstance)
				ret.push_back(new GmeObject( peer, mydn));
		}
		MGACOLL_ITERATE_END;
		return ret;
	};
	inline vector<ObjectImpl*> GmeObject::getInstances() const
	{
		vector<ObjectImpl*> ret;
		if (self)
		{
			IMgaFCOsPtr peers = self->DerivedObjects;
			MGACOLL_ITERATE(IMgaFCO, peers) 
			{
				IMgaFCOPtr peer = MGACOLL_ITER;
				if (peer->IsInstance)
					ret.push_back(new GmeObject( peer, mydn));
			}
			MGACOLL_ITERATE_END;
		}
		return ret;
	};
	inline ObjectImpl* GmeObject::getArchetype() const
	{
		ObjectImpl * ret = NULL;
		if (self)
		{
			IMgaFCOPtr peer = self->DerivedFrom;
			if(peer) ret = new GmeObject( peer, mydn);
		}
		return ret;
	};

	inline bool GmeObject::hasRealArchetype() const 
	{
		ObjectImpl * ret = getArchetype();
		if (!ret)
			throw udm_exception("hasRealArchetype() can be evaluated only on instantiated  or derived objects, or (inherited)children of derived objects.");
		bool retval = (self->IsPrimaryDerived == VARIANT_TRUE);
		delete ret;
		return retval;

	};

	bool GmeObject::isSubtype() const
	{
		if (self)
		{
			IMgaFCOPtr peer = self->DerivedFrom;
			if (peer)
				return (self->IsInstance == VARIANT_FALSE);
			else return false;
		
		}
		return false;
	};

	bool GmeObject::isInstance() const
	{
		if (self)
		{
			IMgaFCOPtr peer = self->DerivedFrom;
			if (peer)
				return (self->IsInstance == VARIANT_TRUE);
			else return false;
	
		}
		return false;
	};
	


	Udm::DataNetwork * GmeObject::__getdn()
	{ 
		if (mydn) return const_cast<Udm::DataNetwork*>(mydn);
		throw udm_exception("Data Network is NULL in constructor! GmeObject without a data network ?!");

		/*
		IMgaProjectPtr p = self->Project;
		for(gdnmap::iterator ff = GDNMap.begin(); ff != GDNMap.end(); ff++) 
		{
			Object root = (*ff)->GetRootObject();
			if(root && static_cast<GmeObject *>(root.__impl())->folderself->Project == p) 
				mydn = *ff;
				return *ff;
		}
		throw udm_exception("Error locating GME DN for object");
		*/

	};




		




	

	

	UDM_DLL GmeDataNetwork::GmeDataNetwork(const Udm::UdmDiagram& dia, Udm::UdmProject* project) 
		: priv(*new privdata), DataNetwork(dia, project) 
	{
		writeOps=0;
		GDNMap.push_front(this);
		static bool first = true; 
		if(first) 
		{ 
			// Modification: Tihamer Levendovszky - for Udm Interpreter //////////////////
			HRESULT res=CoInitializeEx(NULL,COINIT_APARTMENTTHREADED );
			if(res!=S_FALSE) // If a library has been initialized we are happy with that
				COMTHROW(res);
			//////////////////////////////////////////////////////////////////////////////
			first = false; 
		}
		hasOpened=false;

		//create a cache for meta-classes 
		set< ::Uml::Class> meta_classes = dia.dgr->classes();
		for (set< ::Uml::Class>::iterator mci = meta_classes.begin(); mci != meta_classes.end(); mci++)
		{
			string key = (string)mci->name();//class
			pair<string const, const ::Uml::Class> mcc_item(key, *mci);
			pair<map<string, const ::Uml::Class>::iterator, bool> ins_res = meta_class_cache.insert(mcc_item);
			if (!ins_res.second)
				throw udm_exception("Insert failed when creating meta classes by name map!");
		}

		set< ::Uml::Namespace> meta_namespaces = dia.dgr->namespaces();
		for (set< ::Uml::Namespace>::iterator mni = meta_namespaces.begin(); mni != meta_namespaces.end(); mni++)
		{
			set< ::Uml::Class> meta_classes = mni->classes();
			for (set< ::Uml::Class>::iterator mci = meta_classes.begin(); mci != meta_classes.end(); mci++)
			{
				string key =(string)mni->name() + ':' + (string)mci->name();//namespace:class
				pair<string const, const ::Uml::Class> mcc_item(key, *mci);
				pair<map<string, const ::Uml::Class>::iterator, bool> ins_res = meta_class_cache.insert(mcc_item);
				if (!ins_res.second)
					throw udm_exception("Insert failed when creating meta classes by name map!");

			}
		}
	}
	UDM_DLL GmeDataNetwork::~GmeDataNetwork() 
	{ 
		switch(semantics) {
			case Udm::CHANGES_PERSIST_ALWAYS:
			case Udm::CHANGES_PERSIST_DEFAULT:
				CloseWithUpdate();
				break;
			default:
				CloseNoUpdate();
		}
		delete &priv; 
		for(gdnmap::iterator ff = GDNMap.begin(); ff != GDNMap.end(); ff++) {
			if(*ff == this) break;
		}
		if(ff == GDNMap.end()) throw udm_exception("Corrupt GME DN map");
		GDNMap.erase(ff);

	}

	


// if the assoc has an aclass, or it has a name and that name does not match either of the end class names -> connection
//		we will identify the metaconnection where 
//			the name of the metaconnection matches the UML name
//			the names of the navigable directions match the arrow names
// otherwise -> set or reference
// 		at either end (from which navigation is available) we expect to find a
// 		set or a reference  with
//			relation names matching the end names
	IMgaMetaFCOPtr MetaObjLookup(IMgaMetaModel *metam, SmartBSTR &name) {
		IMgaMetaFCOPtr p;
		if(metam->get_DefinedFCOByName(name, VARIANT_FALSE, &p) == S_OK) return p;
		if(p) return p;
		IMgaMetaFCOsPtr FCOs = metam->DefinedFCOs;
		MGACOLL_ITERATE(IMgaMetaFCO, FCOs) {
			if(MGACOLL_ITER->ObjType == OBJTYPE_MODEL) {
				p = MetaObjLookup(IMgaMetaModelPtr(MGACOLL_ITER),name);
				if(p) return p;
			}
		}
		MGACOLL_ITERATE_END;
		return NULL;
	}

	IMgaMetaFCOPtr MetaObjLookup(IMgaMetaFolder *metaf, SmartBSTR &name) {
		IMgaMetaFCOPtr p;
		if(metaf->get_DefinedFCOByName(name, VARIANT_FALSE, &p) == S_OK) return p;

		IMgaMetaFoldersPtr folds = metaf->DefinedFolders;
		MGACOLL_ITERATE(IMgaMetaFolder, folds) {
			p = MetaObjLookup(MGACOLL_ITER,name);
			if(p) return p;
		}
		MGACOLL_ITERATE_END;
		IMgaMetaFCOsPtr FCOs = metaf->DefinedFCOs;
		MGACOLL_ITERATE(IMgaMetaFCO, FCOs) {
			if(MGACOLL_ITER->ObjType == OBJTYPE_MODEL) {
				p = MetaObjLookup(IMgaMetaModelPtr(MGACOLL_ITER),name);
				if(p) return p;
			}
		}
		MGACOLL_ITERATE_END;
		return NULL;
	}

	IMgaMetaFCOPtr MetaObjLookup(IMgaMetaProject *metap, string name) {
		return MetaObjLookup(metap->RootFolder, SmartBSTR(name.c_str()));
	}
	

// primary points to the set or reference object, to the source of the connection, or to the baseclass
// herename should be the name towards the primary

	void GmeDataNetwork::amapInitialize(const ::Uml::Diagram &dgr, IMgaMetaProject *metaproj) 
	{
		set< ::Uml::Association> assocs;
		set< ::Uml::Association> dgr_assocs = dgr.associations();
		assocs.insert(dgr_assocs.begin(), dgr_assocs.end());

		set< ::Uml::Namespace> nses = dgr.namespaces();
		for (set< ::Uml::Namespace>::iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
		{
			set< ::Uml::Association> ns_assocs = nses_i->associations();
			assocs.insert(ns_assocs.begin(), ns_assocs.end());
		}

		for(set< ::Uml::Association>::iterator i = assocs.begin(); i != assocs.end(); i++) 
		{
			//for each association in the meta 
			::Uml::Association assoc = *i;
			set< ::Uml::AssociationRole> roles = assoc.roles();
			assocmapitem nn;
			objtype_enum expect = OBJTYPE_NULL;
			bool reservednamesinUML = false;
			string searchname = assoc.name();

			::Uml::Class aclass = assoc.assocClass();
			for(set< ::Uml::AssociationRole>::iterator j = roles.begin(); j != roles.end(); j++) 
			{
				//for each (two) role of the association
				if(j->isNavigable()) 
				{
					//if the role is navigable
					string rolename = Uml::MakeRoleName(*j);
					/*
					if(searchname.empty() && !aclass && (rolename == "archetype") && ((string)Uml::theOther(*j).name() == "derived")) 
					{
						nn.ot = OBJTYPE_MODEL;
						nn.primary = *j;
						goto archetype_ready;
					}
					*/
					//check if the rolename is reference or set-member relationship
					if(!aclass && (rolename == "ref" || rolename == "members")) 
					{
						nn.metaobj = MetaObjLookup(metaproj, ((::Uml::Class)Uml::theOther(*j).target()).name());
						nn.primary = Uml::theOther(*j);
						expect = rolename == "ref" ? OBJTYPE_REFERENCE : OBJTYPE_SET;
						break;
					}
					//check if it is a connection and the rolenames directly identify the source and the destination
					if(rolename == "dst" && (!Uml::theOther(*j).isNavigable() || (string)Uml::theOther(*j).name() == "src")) 
					{
						set< ::Uml::Class> deriveds = Uml::DescendantClasses(aclass);
						nn.primary = Uml::theOther(*j);
						expect = OBJTYPE_CONNECTION;
						
						if (deriveds.size() <= 1)
						{
							nn.metaobj = MetaObjLookup(metaproj, getnameforassoc(assoc, false));	
							break;
						}
						else
						{
							nn.metaobj = NULL;
							set< ::Uml::Class> descs = Uml::DescendantClasses(aclass);
							if (descs.size())
							{

								//first we compute the real size: the number of descendant association classes,
								//which can be mapped to an MGA connection object.
								//this means that they are not abstract
								int real_size = 0;
								for (set< ::Uml::Class>::iterator desc_i = descs.begin();desc_i != descs.end();desc_i++)
								{	
									IMgaMetaFCOPtr p = MetaObjLookup(metaproj, desc_i->name());
									if (p) real_size++;
								};

								//fill in the nn structure
								nn.metaobjs_count = real_size;
								nn.metaobjs = new IMgaMetaFCOPtr[real_size];
								int j = 0;

								//copy the MgaMetaFCOPtrs to the allocated array in the nn structure
								for (set< ::Uml::Class>::iterator desc_ii = descs.begin();desc_ii != descs.end();desc_ii++)
								{	
									IMgaMetaFCOPtr p = MetaObjLookup(metaproj, desc_ii->name());
									if (p)
									{
										nn.metaobjs[j] = p;
										j++;
									};
								};
								
							};
							break;
						};
						
						
					}

				}
			}
			if((nn.metaobj != NULL) || (nn.metaobjs != NULL) )
			{	
				//association already resolved - it's either a connection or a reference or a set-member relationship
				reservednamesinUML = true;
			}
			else 
			{
				//the association is not resolved yet,
				//by the rolenames, so we try to resolve it through special registry key/value pairs
				if(!aclass) 
				{
					if(searchname.empty()) 
					{  // the assoc name is empty, it must be a reference or set
						//or reference parent helper
						set< ::Uml::AssociationRole>::iterator j;
						for(j = roles.begin(); j != roles.end(); j++) 
						{
							if(!Uml::theOther(*j).isNavigable()) continue;
							string lookupstr = ((::Uml::Class)j->target()).name();
							string lookupstr1 = j->name();

							bool isnavi1 = j->isNavigable();
							bool isnavi2 = Uml::theOther(*j).isNavigable();

							IMgaMetaFCOPtr bt = MetaObjLookup(metaproj, ((::Uml::Class)j->target()).name());
							if(bt) 
							{   // not abstract, etc;
								SmartBSTR herename, therename, sRefParent, dRefParent;
								switch(bt->GetObjType()) 
								{
									case OBJTYPE_REFERENCE:
											herename = bt->RegistryValue["rrName"];
											therename = bt->RegistryValue["rName"];
											break;
									case OBJTYPE_SET:						
											herename = bt->RegistryValue["sName"];
											therename = bt->RegistryValue["mName"];
											break;
									case OBJTYPE_CONNECTION:
											sRefParent = bt->RegistryValue["sRefParent"];
											dRefParent = bt->RegistryValue["dRefParent"];
											nn.rp_helper = true;//it's an rp_helper connection
											break;
									default:
										continue;
								}//switch(bt->GetObjType()) 
								if (nn.rp_helper)
								{
									if ( (sRefParent == SmartBSTR(Uml::MakeRoleName(Uml::theOther(*j)).c_str())) || (dRefParent == SmartBSTR(Uml::MakeRoleName(Uml::theOther(*j)).c_str())) )
									{
										nn.primary = Uml::theOther( *j);
										nn.metaobj = bt;
										expect = bt->GetObjType();
									}
									break;

								};//	if (nn.rp_helper)
								if( Uml::theOther(*j).isNavigable() && therename == SmartBSTR(Uml::MakeRoleName(Uml::theOther(*j)).c_str()) && 	(!j->isNavigable() || herename == SmartBSTR(Uml::MakeRoleName(*j).c_str())) ) 
								{
									nn.primary = *j;
									nn.metaobj = bt;
									expect = bt->GetObjType();
									break;
								}
							}//if(bt)
						}//for j = roles.begin

					}//if(searchname.empty()) 
					else 
					{
						// the assoc name is not empty; 
						// if it matches any of the end class names, it is a reference or a set
						for(set< ::Uml::AssociationRole>::iterator j = roles.begin(); j != roles.end(); j++) 
						{
							if(searchname == NAMEGET((::Uml::Class)j->target()) && Uml::theOther(*j).isNavigable()) 
							{
								nn.primary = *j;
								nn.metaobj = MetaObjLookup(metaproj, ((::Uml::Class)j->target()).name());
								expect = nn.metaobj->GetObjType();
								break;
							}
						}
						if(j == roles.end()) 
						{  
							// otherwise it is a connection
							nn.metaobj = MetaObjLookup(metaproj, searchname);
							expect = OBJTYPE_CONNECTION;
						}
					}//else if(searchname.empty()) 
				}//if !aclass
				else 
				{
					// the assoc has an aclass, it must be a connection
					nn.metaobj = MetaObjLookup(metaproj, aclass.name());
					expect = OBJTYPE_CONNECTION;
					if (nn.metaobj == NULL)
					{
						//probably aclass is an abstract  supertype
						//we have to list all the subtypes and put in the metaobjs
						set< ::Uml::Class> descs = Uml::DescendantClasses(aclass);
						if (descs.size())
						{

							//first we compute the real size: the number of descendant association classes,
							//which can be mapped to an MGA connection object.
							//this means that they are not abstract
							int real_size = 0;
							for (set< ::Uml::Class>::iterator desc_i = descs.begin();desc_i != descs.end();desc_i++)
							{	
								IMgaMetaFCOPtr p = MetaObjLookup(metaproj, desc_i->name());
								if (p) real_size++;
							};

							//fill in the nn structure
							nn.metaobjs_count = real_size;
							nn.metaobjs = new IMgaMetaFCOPtr[real_size];
							int j = 0;

							//copy the MgaMetaFCOPtrs to the allocated array in the nn structure
							for (set< ::Uml::Class>::iterator desc_ii = descs.begin();desc_ii != descs.end();desc_ii++)
							{	
								IMgaMetaFCOPtr p = MetaObjLookup(metaproj, desc_ii->name());
								if (p)
								{
									nn.metaobjs[j] = p;
									j++;
								};
							};
							
						};//if (descs.size())
					};
				} //if (nn.metaobj == NULL)
			}//if (nn.metaobj == NULL)
			if(nn.metaobj == NULL && !nn.metaobjs_count) 
				throw udm_exception(string("Cannot resolve association ") +  getnameforassoc(assoc, true) + "\n");


			{
				SmartBSTR herename, therename;
				if (nn.metaobj)
				{
					//normal cases, without an association class or the association class could be mapped
					//directly to a IMgaMetaFCOPtr
					nn.ot = nn.metaobj->ObjType;
					if(nn.ot != expect) goto typeerr;
					switch(nn.ot) 
					{
						case OBJTYPE_REFERENCE:
							herename = nn.metaobj->RegistryValue["rrName"];
							therename = nn.metaobj->RegistryValue["rName"];
							break;
						case OBJTYPE_SET:
							herename = nn.metaobj->RegistryValue["sName"];
							therename = nn.metaobj->RegistryValue["mName"];
							break;
						case OBJTYPE_CONNECTION:
							if (nn.rp_helper) break;
							
							herename = nn.metaobj->RegistryValue["sName"];
							therename = nn.metaobj->RegistryValue["dName"];
							{
								for(set< ::Uml::AssociationRole>::iterator j = roles.begin(); j != roles.end(); j++) 
								{
									if(therename == SmartBSTR(Uml::MakeRoleName(Uml::theOther(*j)).c_str()) && 	(!j->isNavigable() || herename == SmartBSTR(Uml::MakeRoleName(*j).c_str())) ) 
									{
										nn.primary = *j;
										break;
									}
								}
							}
							

							break;
						default:
		typeerr:
							throw udm_exception("Association resolves to invalid object type: " +  (string)nn.metaobj->Name);
					}
				}//if (nn.metaobj)
				else
				{
					//the association class is an abstract supertype 
					//so a corresponding GME connection meta object does not exist
					//it can be mapped to more GME connection metaobjects
					
					
					for (int i = 0; i < nn.metaobjs_count; i++)
					{
						IMgaMetaFCOPtr p = nn.metaobjs[i];

						//we expect that all the metaobjects are the same and equal to the one expected, OBJTYPE_CONNECTION
						nn.ot = p->ObjType;
						if(nn.ot != expect) throw udm_exception("Association resolves to invalid object type: " +  (string)p->Name);
				
						//compute which one is the primary role name
						herename = p->RegistryValue["sName"];
						therename = p->RegistryValue["dName"];
						{
							for(set< ::Uml::AssociationRole>::iterator j = roles.begin(); j != roles.end(); j++) 
							{
								if(therename == SmartBSTR(Uml::MakeRoleName(Uml::theOther(*j)).c_str()) && 	(!j->isNavigable() || herename == SmartBSTR(Uml::MakeRoleName(*j).c_str())) ) 
								{
									if (!nn.primary) 
										nn.primary = *j;
									else
									{
										//it should be the same for all the metaobjects!
										if (nn.primary != *j)
											throw udm_exception("amapInitialize: Different primary rolenames found in descendant connection meta objects of the same connection supertype!");
									}
									break;
								}
							}
						}
						//break;
					};
				};//else if (nn.metaobj)

				if(!nn.primary)
				{
					if (nn.metaobj)
						throw udm_exception("Association resolves to invalid object type: " +  (string)nn.metaobj->Name);
					else 
					{
						string descr = "amapInitialize: Incosistency between UML rolenames and sName/dName specifications for these related connections :";
						for (int i = 0; i < nn.metaobjs_count; i++)
						{
							if (i) descr += ",";
							IMgaMetaFCOPtr p = nn.metaobjs[i];
							descr += p->Name; 
						};
						throw udm_exception(descr);
					};
				}
				if((!nn.rp_helper) &&(!reservednamesinUML) && (therename != SmartBSTR(Uml::MakeRoleName(Uml::theOther(nn.primary)).c_str()) || (nn.primary.isNavigable() && herename != SmartBSTR(Uml::MakeRoleName(nn.primary).c_str()))) ) 
				{
					throw udm_exception("Association end names mismatch: " +  (string)nn.metaobj->Name);
				}
			}
//archetype_ready:
			amap.insert(assocmap::value_type(assoc.uniqueId(), nn));
		}
	}

	void CheckVersion(IMgaProject *p) {
		GmeLib::IMgaVersionInfoPtr vi=p;
		GmeLib::MgaInterfaceVersion_enum v = GmeLib::MgaInterfaceVersion_None;
		if(vi) COMTHROW(vi->get_Version(&v));
		if(v != GmeLib::MgaInterfaceVersion_Current) {
			char buf[200]; 
			sprintf(buf, "Incompatible GME version GME:%X UDM:%X", v, GmeLib::MgaInterfaceVersion_Current);
			throw udm_exception(buf);
		}
	}
	
	SmartBSTR createGMEconnstr(string sn) {
		if(!strnicmp(sn.c_str(),"GME:", 4))	sn.erase(0,4);
		if(sn[3] != '=' && !strnicmp(sn.c_str() + sn.size() - 4 , ".mga",4)) {
			sn.insert(0, "MGA=");
		}
		return SmartBSTR(sn.c_str());
	}

	// For BON: Tihamer Levendovszky

	void GmeDataNetwork::OpenExisting(LPUNKNOWN pUnknown, enum Udm::BackendSemantics sem )
	{
		semantics = sem;
		hasOpened=true;
		IMgaProjectPtr  &project = priv.project;
		project.Attach((IMgaProject *)pUnknown, true);

		COMTHROW(project->CreateTerritory(NULL, &priv.terr, NULL));

		// For write
		project->Preferences |= MGAPREF_IGNORECONNCHECKS;


		COMTHROW(project->BeginTransaction(priv.terr, TRANSACTION_GENERAL));
		try {
			amapInitialize(GetRootMeta(), project->RootMeta);
// get rootfolder & get name

			rootobject = new GmeObject( project->RootFolder, this);
		}
		catch(gme_exc &s) { 
			COMTHROW(project->AbortTransaction());
			COMTHROW(priv.terr->Destroy());
			COMTHROW(project->Close(VARIANT_TRUE));
			throw s;
		}

	}



	
	UDM_DLL void GmeDataNetwork::OpenExisting(const string &systemname, 
									const string &metalocator, 
									enum Udm::BackendSemantics sem) 
	{
		hasOpened=false;
		semantics = sem;
		IMgaProjectPtr  &project = priv.project;
		COMTHROW(project.CreateInstance(	OLESTR("Mga.MgaProject")));
		CheckVersion(project);
		VARIANT_BOOL ro;
		COMTHROW(project->Open( createGMEconnstr(systemname), &ro));
		COMTHROW(project->CreateTerritory(NULL, &priv.terr, NULL));

	// BUGFIX:
		project->Preferences |= MGAPREF_IGNORECONNCHECKS;


		COMTHROW(project->BeginTransaction(priv.terr, TRANSACTION_GENERAL));
		try {
			amapInitialize(GetRootMeta(), project->RootMeta);
// get rootfolder & get name
			rootobject = new GmeObject( project->RootFolder, this );
		}
		catch(gme_exc &s) { 
			COMTHROW(project->AbortTransaction());
			COMTHROW(priv.terr->Destroy());
			COMTHROW(project->Close(VARIANT_TRUE));
			throw s;
		}
	}

	UDM_DLL void GmeDataNetwork::CreateNew(const string &systemname, 
									const string &metalocator, const ::Uml::Class &rootclass, 
									enum Udm::BackendSemantics sem) 
	{
		hasOpened=false;
		semantics = sem;
		IMgaProjectPtr  &project = priv.project;
		COMTHROW(project.CreateInstance(	OLESTR("MGA.MgaProject")));
		CheckVersion(project);
		COMTHROW(project->Create( createGMEconnstr(systemname), SmartBSTR(metalocator.c_str())));
		IMgaTerritoryPtr terr;
		COMTHROW(project->CreateTerritory(NULL, &terr, NULL));

		project->Preferences |= MGAPREF_IGNORECONNCHECKS;
		COMTHROW(project->BeginTransaction(terr, TRANSACTION_GENERAL));
		try {
// get rootfolder & get name
			amapInitialize(GetRootMeta(), project->RootMeta);
			GmeObject *bb =  new GmeObject( project->RootFolder, this);
			if(bb->m_type != rootclass) 
			{
				delete bb;
				CASSERT("Cannot create this object as root");
			}

			::Uml::Namespace rootclass_ns = rootclass.parent_ns();
			COMTHROW(project->RootFolder->put_RegistryValue(SmartBSTR(NS_REGNODE_NAME), SmartBSTR(rootclass_ns ? ((string)rootclass_ns.name()).c_str() : NULL)));
			rootobject = bb;
		}
		catch(gme_exc &s) { 
			COMTHROW(project->AbortTransaction());
			COMTHROW(priv.terr->Destroy());
			COMTHROW(project->Close(VARIANT_TRUE));
			throw s;
		}
	}


	// For Udm-based interpreters - Tihamer Levendovszky
	UDM_DLL Object GmeDataNetwork::Gme2Udm(LPUNKNOWN pUnknown)
	{
		IMgaFolderPtr pFolder(pUnknown);
		if(pFolder)
		{
			return new GmeObject( IMgaFolderPtr(pUnknown), this);
		}
		else
		{
			return new GmeObject( IMgaFCOPtr(pUnknown), this);
		}
		

	}


	UDM_DLL Object GmeDataNetwork::ObjectById(Object::uniqueId_type id) 
	{ 
			char buf[100];
			int kindcode = id/100000000;
			if(kindcode < OBJTYPE_MODEL || kindcode  > OBJTYPE_FOLDER) return NULL;
			sprintf(buf, "id-%04lx-%08lx", kindcode + 100 ,  id%100000000);
			
			IMgaObjectPtr obj;
			/*
			HRESULT hr = priv.project->GetObjectByID(SmartBSTR(buf), &obj);
			*/
			obj = priv.project->GetObjectByID(SmartBSTR(buf));
			IMgaFolderPtr fold(obj);
			//if(hr != S_OK) return NULL;
			//else
			if(fold) return new GmeObject( IMgaFolderPtr(obj), this);
			else return new GmeObject( IMgaFCOPtr(obj), this);
	}

	UDM_DLL void GmeDataNetwork::CloseWithUpdate() 
	{
		if(rootobject) {
			rootobject = NULL;

			// only if this is the lastdata network closed.
			//if (GDNMap.size() == 1 && *(GDNMap.begin()) == this)
			//since the last change, amap is local to the datanetwork, and has to be cleaned each time.
			amap.clear();
			
			COMTHROW(priv.project->CommitTransaction());
			priv.terr = NULL;
			if(!hasOpened)
				COMTHROW(priv.project->Close(VARIANT_FALSE));
		}
	}

	UDM_DLL void GmeDataNetwork::CloseNoUpdate()			
	{  
		if(rootobject) {
			rootobject = NULL;
			
			// only if this is the lastdata network closed.
			//if (GDNMap.size() == 1 && *(GDNMap.begin()) == this)
			//since the last change, amap is local to the datanetwork, and has to be cleaned each time.
			amap.clear();
			
			COMTHROW(priv.project->AbortTransaction());
			priv.terr = NULL;
			if(!hasOpened)
				COMTHROW(priv.project->Close(VARIANT_TRUE));
		}
	}
	
	UDM_DLL void GmeDataNetwork::SaveAs(string systemname) 
	{  
		if(rootobject) {
			COMTHROW(priv.project->CommitTransaction());
			COMTHROW(priv.project->Save(createGMEconnstr(systemname), VARIANT_TRUE	));
			COMTHROW(priv.project->BeginTransaction(priv.terr, TRANSACTION_GENERAL));
		}
	}
	UDM_DLL void GmeDataNetwork::CloseAs(string systemname) 
	{  
		SaveAs(systemname); 
		CloseNoUpdate();
	}

	UDM_DLL void GmeDataNetwork::CommitEditSequence() 
	{
			COMTHROW(priv.project->CommitTransaction());
			COMTHROW(priv.project->BeginTransaction(priv.terr, TRANSACTION_GENERAL));
	}
	UDM_DLL void GmeDataNetwork::AbortEditSequence() 
	{
			COMTHROW(priv.project->AbortTransaction());
			COMTHROW(priv.project->BeginTransaction(priv.terr, TRANSACTION_GENERAL));
	}

	void GmeDataNetwork::CountWriteOps()
	{
		if(semantics== Udm::CHANGES_LOST_DEFAULT)return;

		if(writeOps%WRITE_OP_REFRESH_RATE==WRITE_OP_REFRESH_RATE-1)
		{
			writeOps=0;
			CommitEditSequence();
		}
		else
		{
			writeOps++;
		}
	}

	set<string> GmeDataNetwork::GetMetaRoleFilter(::Uml::CompositionChildRole role)
	{
		//search the cache 
		map< ::Uml::CompositionChildRole, string_set>::iterator cache_i = meta_role_filter_cache.find(role);
		
		//return if found
		if (cache_i != meta_role_filter_cache.end()) return cache_i->second;

		//create the valid MGA CompositionRoles for this role
		string_set MetaRoleFilter;
		set< ::Uml::Class> des = Uml::DescendantClasses(role.target());
		for (set< ::Uml::Class>::iterator des_i = des.begin(); des_i != des.end(); des_i++)
		{
			MetaRoleFilter.insert((string)(*des_i).name());
			MetaRoleFilter.insert((string)(*des_i).name() + (string)role.name());
		}

		//insert the newly created set<string> in a cache
		pair< ::Uml::CompositionChildRole const, string_set> cache_item(role, MetaRoleFilter);
		pair<map< ::Uml::CompositionChildRole, string_set>::iterator, bool> ins_res;
		ins_res = meta_role_filter_cache.insert(cache_item);
		if (!ins_res.second)
			throw udm_exception("MetaRoleFilter cache insert operation failed!");
		
		//return the set of string
		return MetaRoleFilter;
	}



	static class reg {
		public:
		reg() {
			GmeDataNetwork::RegisterBackend("GME", "mga", &GmeDataNetwork::factory);
		}	
		~reg() {
			GmeDataNetwork::UnRegisterBackends();
		}
	} _reg_unused;

	UDM_DLL int DummyFL;   // for linker
}

