#include <Uml.h>
#include <UmlExt.h>
#include <UdmStatic.h>
#include <UdmUtil.h>

#if defined(HAVE_EXECINFO_H)
#include <execinfo.h>
#endif

#if defined(HAVE_DLFCN_H)
#include <dlfcn.h>
#endif

#if defined(HAVE_CXXABI_H)
#include <cxxabi.h>
#endif

#if defined(_WIN32)
#include <windows.h>
#include <dbghelp.h>
#endif

#include <sstream>
#include <limits>
#include <string.h>


using namespace Uml;
using namespace Udm;

/*
09/11/06	-	endre
			-		Add utility functions to convert array of strings attributes to a string and back

06/07/06	-	endre
			-		When copying to the same data network, also copy archetypes that are not out-of-the-box.

11/22/04	-	endre

			-	Extended ExtractName with the name of the "name attribute", by default : 'name'
30/08/04	-	endre

			-		Updated reqCopyLinks, reqCopyObjectHierachy and reqCreateMappingforDerivedObject to work with copy operations
			that copy object hierarchies within the same datanetwork, with peers, archetypes and references "out of the box".
			The rules are:
				-	If an object hiearchy has an instantiated/derived object with it's archetype out-of-the-box, the object hierarchy
					can be copied and the copy objects will be instantiated/derived from the same archetype.
				-	Same applies for references(Links with "ref" rolename at either end).
				-	Other links pointing "out of the box" are ignored


23/07/04	-	endre
			
			-		Changed the usage of reqcopyLinks. The function has to be called twice, with the
					first with simpleLinks = true, then with simpleLinks = false, in order to copy 
					both types of links

03/15/04	-	endre
		
		reqCopy changed to invoke createChild() with need_safetype arg  true when:
				- an object with an archetype is created AND
				- dst backend is not safetype
				

09/25/02	-	endre
	
		- Copy crashed if the same datanetwork was copied twice, 
			because of the temporary attributes stored in the
			source datanetwork. A clean function is added and invoked
			after a copy operation.


06/18/02	-	endre

  - updated copy functions to handle attribute arrays
  - also changed the error handling to throw exceptions instead
	of retval encoding


  */

namespace UdmUtil
{


	//functions for copying a data network
	
	const CopyOpts DefCopyOpts = {
		false,	// is_dn_copy
		false	// is_lib_part
	};

	int reqCopyObjectHierarchy(ObjectImpl* p_srcRoot, ObjectImpl* p_dstRoot, DataNetwork* p_dstBackend, bool & finished, copy_assoc_map& cam );



	UDM_DLL string ExtractName(const Udm::ObjectImpl *impl,  const string &att_name )
	{
		if (impl->type().__impl() == NULL)
			return string("<not discoverable>");

		::Uml::Class cls = impl->type();
		set< ::Uml::Attribute> attrs=cls.attributes();		
		
		// Adding parent attributes
		set< ::Uml::Attribute> aattrs=::Uml::AncestorAttributes(cls);
		attrs.insert(aattrs.begin(),aattrs.end());

		for(set< ::Uml::Attribute>::iterator ai = attrs.begin();ai != attrs.end(); ai++) 
		{
			if(string(ai->type())=="String")
			{
				string str=ai->name();
				if(str==att_name)
				{
					
					string value=impl->getStringAttr(*ai);
					if(value.empty())value="<empty string>";
					return value;
				}			
			}				
		}
		
		return string("<no name specified>");
	}

	UDM_DLL string ExtractName(const Udm::Object &ob, const string &att_name)
	{
		return ExtractName(ob.__impl(), att_name);
	}

	UDM_DLL int FlattenLibrariesAndCopyObjectHierarchy(Udm::Object& srcRoot, Udm::Object& dstRoot, Udm::DataNetwork* dstBackend, UdmUtil::copy_assoc_map &cam)
	{
		std::set<Udm::Object> children = srcRoot.GetChildObjects();
		for (std::set<Udm::Object> ::iterator childrenIt = children.begin(); childrenIt != children.end(); childrenIt++)
		{
			Udm::Object child = *childrenIt;
			std::string lib_name;
			if (child.isLibRoot())
			{
				if (FlattenLibrariesAndCopyObjectHierarchy(child, dstRoot, dstBackend, cam) != 0)
				{
					return 1;
				}
			}
		}
		if (CopyObjectHierarchy(srcRoot.__impl(), dstRoot.__impl(), dstBackend, cam) != 0)
		{
			return 1;
		}
		return 0;
	}


	UDM_DLL int CopyObjectHierarchy(Udm::ObjectImpl* p_srcRoot, Udm::ObjectImpl* p_dstRoot, Udm::DataNetwork* p_dstBackend, copy_assoc_map &cam, const CopyOpts &opts)
	{
		// Due to library copying, we have to accept partially filled map.
		//if (cam.size()) throw udm_exception("Association map copied objects should be empty!");
		
		bool finished = true;
		bool first = true;

		int ret;

		while (!finished || first)
		{
			first = false;
			finished = true;

			//cout << endl << "Running again ... " << endl;
			ret=reqCopyObjectHierarchy(p_srcRoot,p_dstRoot, p_dstBackend, finished, cam);
		}
		
		//cout << endl << " Objects copied" << endl;	
		if(!ret)
		{
			p_dstRoot->CopyAttributesFrom(p_srcRoot);	
			ret=reqCopyLinks(p_srcRoot,p_dstRoot,cam, false, true, opts);			//copy simple links first
			ret=reqCopyLinks(p_srcRoot,p_dstRoot,cam, false, false, opts);	//then assoc class based ones.
		}
		
		return ret;

	}

	
	bool reqIsObjectCopied(const Udm::Object & srcDerived, const copy_assoc_map &cam)
	{
		set<Udm::Object> src_children = srcDerived.GetChildObjects();
		set<Udm::Object>::const_iterator src_i = src_children.begin();
		while (src_i != src_children.end())
		{
			Udm::Object src_child = *src_i++;

			Udm::Object src_child_archetype  = src_child.archetype();
			if (src_child_archetype && !src_child.hasRealArchetype())
			{
				copy_assoc_map::const_iterator cam_i = cam.find(src_child_archetype);
				if (cam_i != cam.end()) 
				{
					if (!reqIsObjectCopied(src_child, cam)) return false;
				}
				else
				{
					return false;
				}
			}
		}
		return true;
	};

	void reqCreateMappingforDerivedObject(const Udm::Object & srcDerived, const Udm::Object & dstDerived, copy_assoc_map &cam, bool same_dest_dn)
	{
		set<Udm::Object> src_children = srcDerived.GetChildObjects();
		set<Udm::Object> dst_children = dstDerived.GetChildObjects();

		//for each Object in arc_children,
		//we search the corresponding object in der_children,
		//we record the corresponding object pair and then we go recursive

		set<Udm::Object>::iterator src_i = src_children.begin();
		while (src_i != src_children.end())
		{
			Udm::Object src_child = *src_i++;

			

			Udm::Object src_child_archetype  = src_child.archetype();
			if (src_child_archetype && !src_child.hasRealArchetype())
			{
				//cout << "reqCreateMapping: Searching for the archetype of: " << ExtractName(src_child) << ", id:" << src_child.uniqueId() << endl;
				//cout << ", which is: " << ExtractName(src_child_archetype) << ", id: " << src_child_archetype.uniqueId() << endl;

				//src must be in the map!
				copy_assoc_map::iterator cam_i = cam.find(src_child_archetype);
				Udm::Object dst_child_archetype ;
				if (cam_i != cam.end()) 
				{
					dst_child_archetype  = (*cam_i).second;
				}
				else
				{
					if (same_dest_dn && !src_child_archetype.IsNodeOfTree(srcDerived))
					{
						
						//automatic mapping is done for all derived children
						//if they are archetypes "out of the box"
						//and we are copying objects within the same datanetworks
						dst_child_archetype  = src_child_archetype;
						cam[src_child_archetype] = dst_child_archetype;
						//cout <<"!!!reqCM: ADDED THE SAME DESTINATION AS SOURCE FOR: " << ExtractName(dst_child_archetype) << endl;
					}
					else throw udm_exception("Internal UDMCOPY error: reqCreateMappingforDerivedObject");

				}

				set<Udm::Object>::iterator dst_i = dst_children.begin();
				bool found = false;
				while (dst_i != dst_children.end() && !found)
				{
					Udm::Object dst_child = *dst_i++;
					if ((dst_child.archetype() == dst_child_archetype) && !dst_child.hasRealArchetype()) 
					{
						//record the mapping
						copy_assoc_map::value_type map_item(src_child,dst_child);
						cam.insert(map_item);
						found = true;
						//recursive step, we do it for the whole subtree
						reqCreateMappingforDerivedObject(src_child, dst_child, cam, same_dest_dn);

					}
				}
				
			}
			else
			{
				//this is not an error,
				//it might be that srcDerived is a subtype and in adition has other objects
			}
		}

	}
	bool isHelperAssociation(string roleName, bool isAssocClass)
	{
		return (!isAssocClass ? roleName.find("_rp_container_rev") != string::npos : roleName.find("_rp_container") != string::npos);
	}
	
	int reqCopyObjectHierarchy(ObjectImpl* p_srcRoot, ObjectImpl* p_dstRoot, DataNetwork* p_dstBackend,  bool & finished, copy_assoc_map &cam)
	{
		int ret=0;
		
		::Uml::Class srcClass = p_srcRoot->type();
		::Uml::Class dstClass = p_dstRoot->type();

		bool dest_same_dn = (p_srcRoot->__getdn() == p_dstRoot->__getdn());

		// Root objects are of incompatible type
		if(srcClass!=dstClass) 
			throw udm_exception(string("Objects are of incompatible types: ") + ExtractName(srcClass) + " <-> " + ExtractName(dstClass));

		

		// copy first the private library copies (createLibRootChild must be used instead of createChild)
		vector<ObjectImpl*> lib_roots = p_srcRoot->getLibRoots();
		for(vector<ObjectImpl*>::const_iterator p_currImpl = lib_roots.begin(); p_currImpl != lib_roots.end(); p_currImpl++)
		{
			ObjectImpl* p_srcChild = *p_currImpl;			//source child
			Udm::Object srcChild = p_srcChild->clone();		//the cloned copy will be released in ~Object
															//check whether the object was copied first
			copy_assoc_map::iterator cam_i = cam.find(srcChild);
			if (cam_i != cam.end()) 
			{
				// library root already copied, this means that the entire library is already copied
				p_srcChild->release();
				continue;
			}

			ObjectImpl* p_dstChild = &Udm::_null;			//the destination child(-to be-) variable
					
			//cout << " Now investigating libroot element: " << ExtractName(srcChild) << ", id: " << (long)srcChild.uniqueId() << endl;
			//cout << ".";
			if (p_dstBackend->IsTypeSafe())
				p_dstChild = p_dstRoot->createLibRootChild(p_srcChild->type());
			else
			{
				const ::Uml::Class & safe_type = ::Uml::SafeTypeContainer::GetSafeType(p_srcChild->type());
				p_dstChild = p_dstRoot->createLibRootChild(safe_type);
			}

			//cout << "Now inserting " << ExtractName(srcChild) << " in cam " << endl;
			//cout << "!";
			copy_assoc_map::value_type map_item(srcChild, p_dstChild->clone());
			cam.insert(map_item);

			p_dstChild->CopyAttributesFrom(p_srcChild);	

			ret = reqCopyObjectHierarchy(p_srcChild, p_dstChild, p_dstBackend, finished, cam);

			string lib_name;
			if (p_srcChild->getLibraryName(lib_name))
				p_dstChild->setLibraryName(lib_name.c_str());
					
			p_srcChild->release();		//this was obtained via getLibRoots()
										//so it should be released.
			p_dstChild->release();		//this was obtained from createLibRootChild and needs to be released.
					
			// If error go back
			if (ret) return ret;
		}

		set< ::Uml::Class> ancestorClasses=::Uml::AncestorClasses(srcClass);


		for(set< ::Uml::Class>::iterator p_currClass=ancestorClasses.begin(); p_currClass!=ancestorClasses.end(); p_currClass++)
		{
			
			// Traversing the containtment hierarchy
			set< ::Uml::CompositionParentRole> compParentRoles=p_currClass->parentRoles();
			for(set< ::Uml::CompositionParentRole>::iterator p_currRole=compParentRoles.begin();
				p_currRole!=compParentRoles.end(); p_currRole++)
			{
				::Uml::CompositionChildRole o_role = theOther(*p_currRole);
				::Uml::Class childClass = o_role.target();
			
				vector<ObjectImpl*>children= p_srcRoot->getChildren(o_role,childClass);
				for(vector<ObjectImpl*>::iterator p_currImpl=children.begin();
					p_currImpl!=children.end();p_currImpl++)
				{
					ObjectImpl* p_srcChild=*p_currImpl;				//source child
					ObjectImpl* p_dstChild = &Udm::_null;			//the destination child(-to be-) variable


					if (p_srcChild->isLibRoot()) {	// library root element has been copied above
						p_srcChild->release();
						continue;
					}

					Udm::Object srcChild = p_srcChild->clone();		//the cloned copy will be released in ~Object
					Udm::Object dstChild;

																	//check whether the object was copied first
					copy_assoc_map::iterator cam_i = cam.find(srcChild);
					if (cam_i != cam.end()) 
					{
						dstChild = (*cam_i).second;
						p_dstChild = dstChild.__impl()->clone();	//if it was clone()it, because of the release() at the end.

					}			
	
					
					//cout << " Now investigating : " << ExtractName(srcChild) << ", id: " << (long)srcChild.uniqueId() << endl;
					//cout << ".";
					if(p_dstChild==&Udm::_null) // The object has not been created yet
					{
						
						//getArchetype() clone()-s it first
						ObjectImpl * p_srcChildArc = p_srcChild->getArchetype();
						//destination archetype (-to be-) variable
						ObjectImpl * p_dstChildArc= &Udm::_null;


						Udm::Object srcChildArc(p_srcChildArc);//getArchetype() does the clone part
						Udm::Object dstChildArc;//this is Udm::_null for now ... 

						if (srcChildArc)//check if the source object has archetype
						{
							//if it's not a real archetype, we skip this child
							//(it's there because the parent has an archetype)
							if (!p_srcChild->hasRealArchetype()) {
								p_srcChild->release();
								continue;
							}

							//if same datanetwork, check if srcChild archetype is out-of-the-box or not
							bool outOfBox_srcChildArc = dest_same_dn && !srcChildArc.IsNodeOfTree(p_srcRoot->clone());

							//if it has, check whether it was already copied
							copy_assoc_map::iterator cam_i = cam.find(srcChildArc);
							if (cam_i != cam.end()) 
							{
								// if it was already copied, assign the copied archetype to variables
								dstChildArc = (*cam_i).second;
								p_dstChildArc = dstChildArc.__impl();

							}
							else
							{
								if (outOfBox_srcChildArc)
								{
									//when working on the same datanetwork,
									//if the archetype is found out-of-the-box, then it must be the same for both the copied and the copy object
									//cout <<"!!!reqCopyOH: ADDED THE SAME DESTINATION AS SOURCE FOR: " << ExtractName(srcChildArc) << endl;

									dstChildArc = srcChildArc;
									p_dstChildArc = dstChildArc.__impl();
									cam[srcChildArc] = dstChildArc;
								}
								
							};

							

							if (p_dstChildArc == &Udm::_null) 
							{
								
									finished = false;//archetype it is not copied, it will be needed to
												//walk the tree again
									p_srcChild->release();
									continue; //skip to the next children
								
							}
							else
							{
								//check if archetype's all children were copied OK
								//(recursively)
								//we don't require this condition if we are copying within the same datanetwork
								//because reqCreateMappingforDerivedObject function will automatically insert these objects in cam
								if (!outOfBox_srcChildArc && !reqIsObjectCopied(srcChild,cam))
								{
									finished = false;
									p_srcChild->release();
									continue;
								}
								//archetype is ready, so we create the new object, 
								//which is either subtype or instance
								/*bool subtype = false; //is instance by default

								set<Udm::Object> deriveds = srcChildArc.derived();
								if (deriveds.find(srcChild) != deriveds.end()) subtype =true;
								*/
								bool subtype = srcChild.isSubtype();

								if (p_dstBackend->IsTypeSafe())
						
									p_dstChild=p_dstRoot->createChild(o_role, p_srcChild->type(), p_dstChildArc, subtype);
								else
								{
									const ::Uml::Class & safe_type = ::Uml::SafeTypeContainer::GetSafeType(p_srcChild->type());
									p_dstChild=p_dstRoot->createChild(o_role, safe_type, p_dstChildArc, subtype, true, true);
								}

								//do the mapping for the derived block as well
								//this function has to know whether we are copying on the same datanetwork
								reqCreateMappingforDerivedObject(srcChild, p_dstChild->clone(),cam, dest_same_dn);
							}
						}
						else
						{
							if (p_dstBackend->IsTypeSafe())
						
								p_dstChild=p_dstRoot->createChild(o_role, p_srcChild->type());
							else
							{
								const ::Uml::Class & safe_type = ::Uml::SafeTypeContainer::GetSafeType(p_srcChild->type());
								p_dstChild=p_dstRoot->createChild(o_role, safe_type);
							}
						}

						/*
							Create association for the map.
						*/

						//cout << "Now inserting " << ExtractName(srcChild) << " in cam " << endl;
						//cout << "!";
						copy_assoc_map::iterator cam_i = cam.find(srcChild);
						if (cam_i != cam.end()) 
						{
							(*cam_i).second = p_dstChild->clone(); //Udm::Object(ObjectImpl) constructor is invoked
						}
						else
						{
							copy_assoc_map::value_type map_item(srcChild, p_dstChild->clone());
							cam.insert(map_item);
						}

						p_dstChild->CopyAttributesFrom(p_srcChild);	

						
					}
					else
					{

						//in case of inherited children object
						//which where created by createChild() call
						//attributes must be copied.

						//getArchetype() clone()-s it first
						ObjectImpl * p_srcChildArc = p_srcChild->getArchetype();
						if ( p_srcChildArc  && (p_srcChildArc != &Udm::_null))
						{
							if (!p_srcChild->hasRealArchetype())
								p_dstChild->CopyAttributesFrom(p_srcChild);	
							
							p_srcChildArc->release();
						}
					}
					
					ret=reqCopyObjectHierarchy(p_srcChild,p_dstChild, p_dstBackend, finished, cam);
					
					p_srcChild->release();		//this was obtained via getChildren()
												//so it should be released.
					p_dstChild->release();		//this was obtained either from map(and cloned after)
												//or from createChild(), so anyway, it should be released.
					
					// If error go back
					if(ret)return ret;
				}
			}		
		}
		return ret;
	}
	
	
	UDM_DLL int reqCopyLinks(ObjectImpl* p_srcRoot, ObjectImpl* p_dstRoot,copy_assoc_map &cam, const bool direct,const bool simpleLinks, const CopyOpts &opts)
	{
		int ret=0;

		// don't descend into a library part to copy the links, they will be created when copying the host
		if (opts.is_dn_copy && p_dstRoot->isLibRoot()) {
			//cout << "will not copy links inside a library" << endl;
			return ret;
		}

		::Uml::Class srcClass= p_srcRoot->type();
		::Uml::Class dstClass= p_dstRoot->type();

		//bool variable which is true when the copy is done within the same datanetwork (an object tree is moved)
		bool dest_same_dn = (p_srcRoot->__getdn() == p_dstRoot->__getdn());

		//static int depth = 1;
	
		//cout << "Now copying links for object p_srcRoot = " << ExtractName(p_srcRoot->clone()) << ", of type: " << (string)srcClass.name() << endl;
		// Root objects are of incompatible type
		if(srcClass!=dstClass) return -1;

		set< ::Uml::Class> ancestorClasses=AncestorClasses(srcClass);

		for(set< ::Uml::Class>::iterator p_currClass=ancestorClasses.begin();
						p_currClass!=ancestorClasses.end(); p_currClass++)
		{
			set< ::Uml::AssociationRole> assocRoles=p_currClass->associationRoles();
			Uml::Association assoc = p_currClass->association();
			if (assoc)
			{
				std::set<Uml::AssociationRole> roles = assoc.roles();
				for (std::set<Uml::AssociationRole>::iterator rolesIt = roles.begin(); rolesIt != roles.end(); rolesIt++)
				{
					assocRoles.insert(*rolesIt);
				}

			}
			// Getting the association roles and iterating through them
			for(set< ::Uml::AssociationRole>::iterator p_currAssocRole=assocRoles.begin();p_currAssocRole!=assocRoles.end();p_currAssocRole++)
			{

				::Uml::Class assocClass=::Uml::Association(p_currAssocRole->parent()).assocClass();

				//this function is expected to be called twice, first iwth simplelinks true, and then with simpleLinks false
				//if simpleLinks is true, only simple associations are copied
				//if simpleLinks is false, only assoc. class based associations are copied
				if (simpleLinks && assocClass) continue;	
				if (!simpleLinks &&  !assocClass) continue;	
				::Uml::AssociationRole o_role = ::Uml::theOther(*p_currAssocRole);
				int mode;
				if ((Udm::Object)p_currAssocRole->parent() == assoc)
				{
					mode = Udm::TARGETFROMCLASS;
				}
				else
				{
					mode = assocClass?Udm::CLASSFROMTARGET : Udm::TARGETFROMPEER;
				}

				vector<ObjectImpl*>srcPeers=p_srcRoot->getAssociation(o_role, mode);
				
				//if (srcPeers.size()) 
				//	cout <<"\t now copying links via role: " << (string)(p_currAssocRole->name()) << "<->" << (string)(o_role.name()) << endl;

				vector<ObjectImpl*>dstPeers;

				for(vector<ObjectImpl*>::iterator p_currSrcPeer=srcPeers.begin();p_currSrcPeer!=srcPeers.end(); p_currSrcPeer++)
				{
					ObjectImpl* p_srcChild=*p_currSrcPeer;

					Udm::Object srcChild = p_srcChild->clone();//will be released in ~Object
					
					
					//cout << "\t\t looking up the copy of : " << ExtractName(srcChild) << ", id: "<<  srcChild.uniqueId() << endl;
					//cout << ".";
	
					Udm::Object dstChild;

					copy_assoc_map::iterator cam_i = cam.find(srcChild);
					if (cam_i == cam.end()) 
					{
						if (dest_same_dn && (string)(o_role.name()) == "ref")
						{
							//only references are being copied within the same datanetwork
							//if the refered object is found to be out of the box, then it is OK to use the same
							//reffered object for the copy object
							dstChild = srcChild;
							cam[srcChild] = dstChild;
							//cout <<"!!!reqCopyLinks: Because of reference, ADDED THE SAME DESTINATION AS SOURCE FOR: " << ExtractName(srcChild) << endl;

						}
						else
						{
							//cout << " cam_i == cam.end() while looking for the copy " << endl;
							
							//if we copy inside a datanetwork, we simply skip this peer.
							//the user is responsible for recreating the connection

							if (dest_same_dn) 
							{
								//cout << "Ignoring the copy of link with peer " << ExtractName(srcChild) << ", it has been detected as out of the box object!" << endl;
								p_srcChild->release();
								continue;
							}
							else if (opts.is_lib_part && (string)(p_currAssocRole->name()) == "ref") {
								//cout << "The copied library object " << ExtractName(srcChild)
								//	<< " is referred from the host; skipping link, it will be created when copying the host" << endl;
								p_srcChild->release();
								continue;
							}
							//if we are copying complete data networks, this should not happen!
							throw udm_exception("Internal UdmCopy error");
						}
					}
					else
					{
						dstChild = cam_i->second;		//this is a safe Object to Object copy
					}

					//cout << "\t\t lookup OK:" << ExtractName(dstChild) << ", id: " << dstChild.uniqueId() << endl;

					ObjectImpl* p_dstChild = dstChild.__impl()->clone();	//will be released after setAssociation()
					
					//it has to be non-null at this time
					if(p_dstChild==&Udm::_null)	throw udm_exception("Internal UdmCopy error");
					
					dstPeers.push_back(p_dstChild);	//no need to clone it.. it will be passed to setAssociation()
					p_srcChild->release(); //it was obtained through getAssociation() call
				}
				if (!dstPeers.empty())
				{
			
				//	cout << "\t\t seting associations, vector contains: " << dstPeers.size() << endl;
					p_dstRoot->setAssociation(o_role,dstPeers, mode, direct);
				}
				
				// Releasing dstPeers cloned 
				for(vector<ObjectImpl*>::iterator p_currDstPeer=dstPeers.begin();
					p_currDstPeer!=dstPeers.end(); p_currDstPeer++)
				{
						(*p_currDstPeer)->release();
				}
			}
		}

		//Udm::Object p_src_archetype = p_srcRoot->getArchetype();
		//if (p_src_archetype) return ret; //no need to go inside, upon creation everything was copied OK

		// Traversing the source object network via the containtment hierarchy
		vector<ObjectImpl*>children=p_srcRoot->getChildren(NULL,NULL);
		for(vector<ObjectImpl*>::iterator p_currImpl=children.begin();
			p_currImpl!=children.end();p_currImpl++)
		{
			ObjectImpl* p_srcChild=*p_currImpl;
			//ObjectImpl* p_dstChild=GetPeer(p_srcChild,attrLink,p_dstBackend);
			
			Udm::Object srcChild = p_srcChild;//will be released in ~Object, p_srcChild is cloned, 
											  //because it's returned by getChildren
			
			
		//	for (int i = 0; i<depth; i++,cout<<"\t");		
		//	cout << "traversing: looking for: " << ExtractName(srcChild) << ", of type:" << ExtractName(srcChild.type()) << endl;
			copy_assoc_map::iterator cam_i = cam.find(srcChild);
			if (cam_i == cam.end()) throw udm_exception("Internal UdmCopy error");
							
			Udm::Object dstChild = cam_i->second;		//this is a safe Object to Object copy
			ObjectImpl* p_dstChild = dstChild.__impl();	//is also safe, we don't create an Object from this pointer
					
			if(!p_dstChild || p_dstChild==&Udm::_null) throw udm_exception("Internal UdmCopy error");
			
					

			//depth++;
			/////////////// Recursive Call to Itself //////////////////
			ret=reqCopyLinks(p_srcChild,p_dstChild, cam, direct, simpleLinks, opts);			
			/////////////////////////////////////////////////////
			//depth--;
			if(ret)return ret;
		}	
			
		return ret;

	}


	UDM_DLL string escape_chars(const string &src, const char escape_char, const string &to_escape_chars)
	{
		string dst;
		dst.reserve(src.length());

		for (string::const_iterator i = src.begin(); i != src.end(); i++)
		{
			if (to_escape_chars.find(*i) != string::npos)
				dst.append(1, escape_char);

			dst.append(1, *i);
		}

		return dst;
	}


	UDM_DLL string vector_to_string(const vector<string> &v, const char separator, bool add_sep_at_end, bool unquote_strings)
	{
		string ret;

		string to_escape("\\");
		to_escape.append(1, separator);

		for (vector<string>::const_iterator i = v.begin(); i != v.end(); i++)
		{
			string src = *i;

			//if asked, remove double quotes from the beginning and the end of the string
			if (unquote_strings && src.length() > 1)
			{
				if (src.at(0) == '"')
					src.erase(0, 1);
				if (src.at(src.length() - 1) == '"')
					src.erase(src.length() - 1, 1);
			}

			ret.append(escape_chars(src, '\\', to_escape));
			ret.append(1, separator);
		}

		if (!add_sep_at_end && ret.length() >= 1)
			ret.erase(ret.length() - 1, 1);

		return ret;
	}


	UDM_DLL vector<string> string_to_vector(const string &src, const char separator)
	{
		vector<string> ret;

		bool in_escape = false;
		string w;
		for (string::const_iterator i = src.begin(); i != src.end(); i++)
		{
			if (*i == separator)
			{
				if (!in_escape)
				{
					// a not-escaped separator => end of an array token
					ret.push_back(w);
					w.clear();
				}
				else
				{
					// escaped separator
					in_escape = false;
					w.append(1, *i);
				}
			}
			else if (*i == '\\')
			{
				if (!in_escape)
					// beginning of an escape sequence
					in_escape = true;
				else
				{
					// escaped escape character
					in_escape = false;
					w.append(1, '\\');
				}
			}
			else
			{
				if (in_escape)
				{
					// unknown escape sequence; keep it
					in_escape = false;
					w.append(1, '\\');
				}
				w.append(1, *i);
			}
		}

		if (w.length())
			ret.push_back(w);

		return ret;
	}

	UDM_DLL string replace_delimiter(const string &s, const string &old_d, const string &new_d)
	{
		if (s.length() == 0 || old_d.length() == 0)
			return s;

		string r;
		string::size_type pi = 0;
		string::size_type i = s.find(old_d);
		while (i != string::npos) {
			r += s.substr(pi, i - pi);
			r += new_d;
			pi = i + old_d.length();
			i = s.find(old_d, pi);
		}
		r += s.substr(pi);
		return r;
	}

	// return: true if str represents -Inf, Inf, or NaN
	static bool ParseSpecialDouble(const char* str, double& out)
	{
		const char* val = (*str == '-' && *str != '\0') ? str + 1 : str;
#if defined(_WIN32)
#define strncasecmp _strnicmp
#endif
		if (strncasecmp("-Inf", str, 4) == 0 || strncasecmp("-1.#INF", str, 7) == 0)
		{
			out = -std::numeric_limits<double>::infinity();
			return true;
		}
		else if (strncasecmp("Inf", str, 3) == 0 || strncasecmp("1.#INF", str, 6) == 0)
		{
			out = std::numeric_limits<double>::infinity();
			return true;
		}
		else if (strncasecmp("NaN", val, 3) == 0 || strncasecmp("1.#IND", val, 7) == 0 || strncasecmp("1.#QNAN", val, 7) == 0 || strncasecmp("1.#SNAN", val, 7) == 0)
		{
			out = std::numeric_limits<double>::quiet_NaN();
			return true;
		}
		return false;
	}

	UDM_DLL bool stringToDouble(const char* val, double& out)
	{
		if (ParseSpecialDouble(val, out))
		{
			return true;
		}
		else
		{
			char* endptr;
			double tmp;
			tmp = strtod(val, &endptr);

			if (*endptr != '\0')
			{
				return false;
			}
			out = tmp;
			return true;
		}
	}

	UDM_DLL string doubleToString(double val, int minimum_precision)
	{
		const int MAXIMAL_PRECISION = 19;
		int precision = minimum_precision;	// precision to start width

		char result[64];

		// special values per xml-xerces/c/src/util/XMLDouble.cpp
		if (val != val)
		{
			return "NaN";
		}
		else if(val == std::numeric_limits<double>::infinity())
		{
			return "INF";
		}
		else if (val == -std::numeric_limits<double>::infinity())
		{
			return "-INF";
		}

		// This works (but is not minimal):
		//_snprintf_s(result, 64, "%.17g", val);
		//return result;

		int precision_is_good;
		// KMS: this code is incredibly inefficient
		// TODO: use something like Gay's dtoa.c

		do {
			UDM_ASSERT(precision <= MAXIMAL_PRECISION);

#ifdef _WIN32
			if (_snprintf_s(result, 64, "%.*g", precision, val) < 0) {
				throw udm_exception("Internal error when converting from double to string");
			}
#else
			if (snprintf(result, 64, "%.*g", precision, val) >= 64) {
				throw udm_exception("Internal error when converting from double to string");
			}
#endif

			double d;
			if (sscanf(result, "%lf", &d) != 1)
				throw udm_exception("Internal error when converting from double to string");

			precision_is_good = d == val;
			precision++;
			    
		}
		while (!precision_is_good);

		return result;
	}



	#if defined(HAVE_EXECINFO_H)

	string demangled_symbol(const char *str)
	{
		ostringstream sym;

#if defined(HAVE_CXXABI_H)
		int status = 0;

		char *demangled = abi::__cxa_demangle(str, 0, 0, &status);
		if (demangled) {
			sym << demangled;
			free(demangled);
		} else
			sym << str;
#else
		sym << str;
#endif

		return sym.str();
	}

#if defined(HAVE_DLFCN_H)

	vector<string> get_symbols(void * const *addresses, int stack_depth)
	{
		vector<string> res;
		res.reserve(stack_depth - 1);

		for (size_t i = 1; i < stack_depth; i++) {
			ostringstream sym;

			if (addresses[i]) {
				Dl_info info = { 0 };
				if (dladdr(addresses[i], &info) == 0)
					sym << "???";
				else {
					if (info.dli_sname)
						sym << demangled_symbol(info.dli_sname);
					else
						sym << "???";

					unsigned offset = (char *)addresses[i] - (char *)info.dli_saddr;
					sym << hex << " + 0x" << offset;

					sym << " [" << addresses[i] << "]";
				}
			}

			res.push_back(sym.str());
		}

		return res;
	}

#else // if defined(HAVE_DLFCN_H)

	vector<string> get_symbols(void * const *addresses, int stack_depth)
	{
		vector<string> res;
		res.reserve(stack_depth - 1);

		char **symbols = backtrace_symbols(addresses, stack_depth);
		if (symbols == NULL)
			return res;

		for (size_t i = 1; i < stack_depth; i++) {
			ostringstream sym;

			if (symbols[i]) {
				char *str;
				// look for the string starting after the first '(' and ended by the following ')' or '+'
				if (1 == sscanf(symbols[i], "%*[^(](%a[^)+]", &str)) {
					sym << demangled_symbol(str);
					free(str);

					// look for the offset between '+' and ')'
					if (1 == sscanf(symbols[i], "%*[^(]%*[^+]+%a[^)]", &str)) {
						sym << " + " << str;
						free(str);
					}
				} else
					sym << symbols[i];

				sym << " [" << addresses[i] << "]";
			}

			res.push_back(sym.str());
		}

		free(symbols);

		return res;
	}

#endif // if defined(HAVE_DLFCN_H)

	#else // if defined(HAVE_EXECINFO_H)

	vector<string> get_symbols()
	{
		vector<string> res;

		static HANDLE hProcess = 0;
		static bool syms_ready = false;

		// initialization of Symbol Handler
		if (hProcess == 0) {
			hProcess = GetCurrentProcess();

			SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES);
			if (SymInitialize(hProcess, NULL, TRUE))
				syms_ready = true;
		}

		if (!syms_ready)
			return res;

		void *addresses[62];
		size_t stack_depth = RtlCaptureStackBackTrace(1, 62, addresses, NULL);
		res.reserve(stack_depth);

		for (size_t i = 1; i < stack_depth; i++) {
			ostringstream sym;

			if (addresses[i]) {
				DWORD64 dwAddress = (DWORD64)addresses[i];

				// get source file info
				{
					DWORD dwDisplacement;
					IMAGEHLP_LINE64 line;

					line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
					if (SymGetLineFromAddr64(hProcess, dwAddress, &dwDisplacement, &line))
						sym << line.FileName << ":" << line.LineNumber << " ";
				}

				// get symbol info
				vector<char> buffer(sizeof(SYMBOL_INFO) + MAX_SYM_NAME);
				PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)&buffer.front();

				pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
				pSymbol->MaxNameLen = MAX_SYM_NAME;

				DWORD64 dwDisplacement = 0;
				if (SymFromAddr(hProcess, dwAddress, &dwDisplacement, pSymbol))
					sym << pSymbol->Name << hex << " + 0x" << dwDisplacement;
                else
					sym << "???";
			}

			res.push_back(sym.str());
		}

		return res;
	}

	#endif // if defined(HAVE_EXECINFO_H)

	UDM_DLL string stacktrace()
	{
		string trace = "Call stack:\n";

#if defined(HAVE_EXECINFO_H)

		// limit stack depth to 64 frames
		void *stack_addrs[64];
		size_t stack_depth = backtrace(stack_addrs, 64);

		vector<string> v = get_symbols(stack_addrs, stack_depth);

#elif defined(_WIN32)
		vector<string> v = get_symbols();
#endif // defined(HAVE_EXECINFO_H)

		for (size_t i = 0; i < v.size(); i++)
			trace += "    " + v[i] + "\n";

		return trace;
	};
};
