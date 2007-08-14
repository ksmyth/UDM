#include <Uml.h>
#include <UmlExt.h>
#include <UdmStatic.h>
#include <UdmUtil.h>



using namespace Uml;
using namespace Udm;

/*
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
	
	int reqCopyObjectHierarchy(ObjectImpl* p_srcRoot, ObjectImpl* p_dstRoot, DataNetwork* p_dstBackend, bool & finished, copy_assoc_map& cam );



	UDM_DLL string ExtractName(Udm::Object ob,  const string att_name )
	{
		::Uml::Uml::Class cls= ob.type();				
		set< ::Uml::Uml::Attribute> attrs=cls.attributes();		
		
		// Adding parent attributes
		set< ::Uml::Uml::Attribute> aattrs=::Uml::AncestorAttributes(cls);
		attrs.insert(aattrs.begin(),aattrs.end());

		for(set< ::Uml::Uml::Attribute>::iterator ai = attrs.begin();ai != attrs.end(); ai++) 
		{
			if(string(ai->type())=="String")
			{
				string str=ai->name();
				if(str==att_name)
				{
					
					string value=ob.getStringAttr(*ai);
					if(value.empty())value="<empty string>";
					return value;
				}			
			}				
		}
		
		return string("<no name specified>");
	}



	UDM_DLL int CopyObjectHierarchy(Udm::ObjectImpl* p_srcRoot, Udm::ObjectImpl* p_dstRoot, Udm::DataNetwork* p_dstBackend, copy_assoc_map &cam)
	{
		if (cam.size()) throw udm_exception("Association map copied objects should be empty!");
		
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
			ret=reqCopyLinks(p_srcRoot,p_dstRoot,cam, false);			//copy simple links first
			ret=reqCopyLinks(p_srcRoot,p_dstRoot,cam, false, false);	//then assoc class based ones.
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
					if (same_dest_dn)
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
	
	
	int reqCopyObjectHierarchy(ObjectImpl* p_srcRoot, ObjectImpl* p_dstRoot, DataNetwork* p_dstBackend,  bool & finished, copy_assoc_map &cam)
	{
		int ret=0;
		
		::Uml::Uml::Class srcClass = p_srcRoot->type();
		::Uml::Uml::Class dstClass = p_dstRoot->type();

		bool dest_same_dn = (p_srcRoot->__getdn() == p_dstRoot->__getdn());

		// Root objects are of incompatible type
		if(srcClass!=dstClass) 
			throw udm_exception(string("Objects are of incompatible types: ") + ExtractName(srcClass) + " <-> " + ExtractName(dstClass));

		

		set< ::Uml::Uml::Class> ancestorClasses=::Uml::AncestorClasses(srcClass);


		for(set< ::Uml::Uml::Class>::iterator p_currClass=ancestorClasses.begin(); p_currClass!=ancestorClasses.end(); p_currClass++)
		{
			
			// Traversing the containtment hierarchy
			set< ::Uml::Uml::CompositionParentRole> compParentRoles=p_currClass->parentRoles();
			for(set< ::Uml::Uml::CompositionParentRole>::iterator p_currRole=compParentRoles.begin();
				p_currRole!=compParentRoles.end(); p_currRole++)
			{
				::Uml::Uml::Class childClass=theOther(*p_currRole).target();
			
				vector<ObjectImpl*>children= p_srcRoot->getChildren(theOther(*p_currRole),childClass);
				for(vector<ObjectImpl*>::iterator p_currImpl=children.begin();
					p_currImpl!=children.end();p_currImpl++)
				{
					ObjectImpl* p_srcChild=*p_currImpl;				//source child
					ObjectImpl* p_dstChild = &Udm::_null;			//the destination child(-to be-) variable

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
						
						//getArhcetype() clone()-s it first
						ObjectImpl * p_srcChildArc = p_srcChild->getArchetype();
						//destination archetype (-to be-) variable
						ObjectImpl * p_dstChildArc= &Udm::_null;


						Udm::Object srcChildArc(p_srcChildArc);//getArchetype() does the clone part
						Udm::Object dstChildArc;//this is Udm::_null for now ... 

						if (srcChildArc)//check if the source object has archetype
						{
							//if it's not a real archetype, we skip this child
							//(it's there because the parent has an archetype)
							if (!p_srcChild->hasRealArchetype()) continue;

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
								if (dest_same_dn)
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
									continue; //skip to the next children
								
							}
							else
							{
								//check if archetype's all children were copied OK
								//(recursively)
								//we don't require this condition if we are copying within the same datanetwork
								//because reqCreateMappingforDerivedObject function will automatically insert these objects in cam
								if (!dest_same_dn && !reqIsObjectCopied(srcChild,cam))
								{
									finished = false;
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
						
									p_dstChild=p_dstRoot->createChild(theOther(*p_currRole), p_srcChild->type(), p_dstChildArc, subtype);
								else
								{
									const ::Uml::Uml::Class & safe_type = ::Uml::SafeTypeContainer::GetSafeType(p_srcChild->type());
									p_dstChild=p_dstRoot->createChild(theOther(*p_currRole), safe_type, p_dstChildArc, subtype, true, true);
								}

								//do the mapping for the derived block as well
								//this function has to know whether we are copying on the same datanetwork
								reqCreateMappingforDerivedObject(srcChild, p_dstChild->clone(),cam, dest_same_dn);
							}
						}
						else
						{
							if (p_dstBackend->IsTypeSafe())
						
								p_dstChild=p_dstRoot->createChild(theOther(*p_currRole), p_srcChild->type());
							else
							{
								const ::Uml::Uml::Class & safe_type = ::Uml::SafeTypeContainer::GetSafeType(p_srcChild->type());
								p_dstChild=p_dstRoot->createChild(theOther(*p_currRole), safe_type);
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

						//getArhcetype() clone()-s it first
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
	
	
	UDM_DLL int reqCopyLinks(ObjectImpl* p_srcRoot, ObjectImpl* p_dstRoot,copy_assoc_map &cam, const bool direct,const bool simpleLinks)
	{
		int ret=0;
		::Uml::Uml::Class srcClass= p_srcRoot->type();
		::Uml::Uml::Class dstClass= p_dstRoot->type();

		//bool variable which is true when the copy is done within the same datanetwork (an object tree is moved)
		bool dest_same_dn = (p_srcRoot->__getdn() == p_dstRoot->__getdn());

		//static int depth = 1;
	
		//cout << "Now copying links for object p_srcRoot = " << ExtractName(p_srcRoot->clone()) << ", of type: " << (string)srcClass.name() << endl;
		// Root objects are of incompatible type
		if(srcClass!=dstClass) return -1;

		set< ::Uml::Uml::Class> ancestorClasses=AncestorClasses(srcClass);

		for(set< ::Uml::Uml::Class>::iterator p_currClass=ancestorClasses.begin();
						p_currClass!=ancestorClasses.end(); p_currClass++)
		{
			// Getting the association roles and iterating through them
			set< ::Uml::Uml::AssociationRole> assocRoles=p_currClass->associationRoles();
			for(set< ::Uml::Uml::AssociationRole>::iterator p_currAssocRole=assocRoles.begin();p_currAssocRole!=assocRoles.end();p_currAssocRole++)
			{
				::Uml::Uml::AssociationRole o_role = ::Uml::theOther(*p_currAssocRole);

				::Uml::Uml::Class assocClass=::Uml::Uml::Association(p_currAssocRole->parent()).assocClass();

				//this function is expected to be called twice, first iwth simplelinks true, and then with simpleLinks false
				//if simpleLinks is true, only simple associations are copied
				//if simpleLinks is ffalse, only assoc. class based associations are copied
				if (simpleLinks && assocClass) continue;	
				if (!simpleLinks &&  !assocClass) continue;	
				vector<ObjectImpl*>srcPeers=p_srcRoot->getAssociation(theOther(*p_currAssocRole),assocClass?Udm::CLASSFROMTARGET : Udm::TARGETFROMPEER);
				
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
								continue;
							};
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
					p_dstRoot->setAssociation(theOther(*p_currAssocRole),dstPeers, assocClass?Udm::CLASSFROMTARGET : Udm::TARGETFROMPEER, direct);
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
					
			if(!p_dstChild || p_dstChild==&Udm::_null)	throw udm_exception("Internal UdmCopy error");
			
					

			//depth++;
			/////////////// Recursive Call to Itself //////////////////
			ret=reqCopyLinks(p_srcChild,p_dstChild, cam, direct, simpleLinks);			
			/////////////////////////////////////////////////////
			//depth--;
			if(ret)return ret;
		}	
			
		return ret;

	}
};