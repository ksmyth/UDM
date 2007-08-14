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

  11/22/04	-	endre

			-	VC7++ .NET porting issues
  10/24/04	-	endre

			-		Added support for attributes persisted as text-nodes, like: 
					<cn>
						<value>
							1.64
						</value>
					</cn>
					
					Now cn has an attribute named "value" with value: 1.64

					Changed the function getStringAttr, setStringAttr and added three new functions:
					getElementNamed, getTextValue and setTextValue.



  02/10/04	-	endre

			-		DTDPath was not exported in DLL

  01/10/04	-	endre

			-		Fixed small bug in CreateNew(), even if the XSD location is provided with full path,
					in the XML file only the XSD filename should appear.

  07/09/04	-	endre

			-		Changed setChildren(). The function can be used to delete objects by omitting them
					from the new set of children which is passed to the function.
					If such deleted object had links, those links were not removed correctly..

  17/08/04	-	endre

			-		Changed setChildren(), ordering of XML elements (DOM_Node-s) was not taken care.
  23/07/04	-	endre
			
			-		Changed the usage of reqcopyLinks. The function has to be called twice, with the
					first with simpleLinks = true, then with simpleLinks = false, in order to copy 
					both types of links

  05/13/04	-	endre
			
				- fixed small bug in CreateNew: CreateNew() now sets the behaviour of the EntityResolver he uses
				if the DomDataNetwork is str based, it will set the entityresolver to UseStrXsd(), otherwise DontUseStrXSd()

  05/10/04	-	endre

				- added string based UdmDom::DomDataNetwork functionallity
  04/18/04	-	endre
			
				- when an object is detached, and the host datanetwork of the object is being part of a Udm project, 
				  the corresponding placeholder object (if any) should be detached as well.

  03/15/04	-	endre
				- Changed the syntax of createchild() according to Udm::ObjectImpl
*/


#include <xercesc/sax/EntityResolver.hpp>
#include <xercesc/dom/deprecated/DOM.hpp>
#include <xercesc/dom/deprecated/DOM_Document.hpp>
#include <xercesc/dom/deprecated/DOM_Element.hpp>
#include <xercesc/dom/deprecated/DOM_Node.hpp>
#include <xercesc/dom/deprecated/DOMString.hpp>
#include <xercesc/dom/deprecated/DOMParser.hpp>
#include <xercesc/dom/deprecated/DOM_ProcessingInstruction.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/BinInputStream.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/sax/HandlerBase.hpp>

XERCES_CPP_NAMESPACE_USE

#include "UdmDom.h"
#include "Uml.h"
#include "UmlExt.h"
#include "UdmUtil.h"
#include <time.h>


#ifdef _WIN32
#include <io.h>
#include <windows.h>
#else
#include <unistd.h>
#include <wchar.h>
#endif

#include <cstdio>
#include <cstdlib>
#include <fstream>


extern void printDOM(DOM_Node doc, const char *filename, XMLCh *encodingName = NULL);
extern void printDOM(DOM_Node doc, string & target, XMLCh *encodingName = NULL);


#ifdef max
#undef max
#endif
#define UDM_DOM_URI_PREFIX "http://www.isis.vanderbilt.edu/2004/schemas/"
/*
CHANGELOG
  03/15/04	-	endre
			
			changed the internal dom attributes from using literal strings to constants
			defined in UdmDom namespace

  03/15/04	-	endre
	
			changed the uniquedId() function, There was a minor bug which caused a crash when uniqueId()
			was invoked on DomObject's without a data network

  24/02/04	-	endre

			Versioning of XML interfaces and checking the version upon loading XML documents
				- changed the class MyEntityResolver
				- DomDataNetwork::OpenExisting
  20/01/04	-	endre
  
			DomDataNetwork::CreateNew() will create XML-s using DOCTYPE Defintion (DTD),
			if a dtd file is provided as metalocator. 


  01/01/04 -    endre

			a lot of changelog info missing.
			the main change is that XSD is used instead of DTD

  11/26/02	-	endre

		-	now using Xerces 2.1.0. However, we stil using the deprecated API.
			We will change to IDOM, the apache recomended C++ binding later.

  06/05/02	-	endre
	
		-	Xerces 1_7_0 is crashing, linking against 1.6.0
		-	DomDataNetwork() builds a type map keyed by classnames, and findClass() works with that.
			This speeds up constructors looking for their type
		-	DomObject() is constructed with it's datanetwork pointer passed. __getdn is optimizied...it
			just returns a pointer.
		
		

  06/02/02	-	endre

		Upgrading xerces iface to Xerces 1.7.0
		Removed the entitysolver, which obviously had a bug. A DTD is looked up in the current directory and the path. 
		If not found, it's passed as an URI to xerces to resolve it. Providing the DTD as a windows resource no longer works. 
		(it had bugs, and it's obviously not platform independent!)

	
  05/10/02	-	endre
		
		 If a DomDataNetwork was closed by either CloseWithUpdate() or CloseWithNoUpdate(), the rootobject is set to NULL;
		 the ~DomDataNetwork() destructor simply returned when rootobject was NULL, thus did not remove itself from the map,
		 causing DomObject::__getdn() functions to crash when polling each networks RootObject.

		 The fix is that ~DomDataNetwork() removes itself from the map even if it has NULL RootObject.


  04/26/02	-	endre

		 getChildren() problem. Similar to getParent() problems.  Fixed

  04/14/02	-	endre
		
		  fixed the fix;) getParent() did not work correctly, if the parentrole's target was
		  an ancestor of the real parent. In that case the correct behaviour is to return the parent.

  04/10/02	-	endre
	
		fixed DomObject::getParent(). in certain situations this function
		returned it's parent even when the parentRole did not match.

*/

namespace UdmDom
{	
	
// --------------------------- DomObject
	//typedefs for maps for enhancing DomObject::Search
	
	typedef list<DomDataNetwork *> ddnmap; 


	//static maps
	static ddnmap DDNMap;
	//static IdToDomElementMap DomElements;



	//function which returns the long id from the string id
	//used in Search(), and release()
	//the map of DOM_Element has this unsigned long id as key
	//to make it faster

	unsigned long GetLongID(const DOMString &a) 
	{
		//if DOMString comapres to 0 than it refers to no string at all!
		if (a == 0) return 0;
		//this assertation failes
		//we should take a look why is this invoked with empty string
		//ASSERT (a != 0);
		

#ifdef _WIN32
		//windows uses UTF-16 and xerces does the same,
		//so this is quite simple
		const wchar_t *buf = a.rawBuffer();
		wchar_t * endptr;
		unsigned long retval = wcstoul(buf+2, &endptr, 16);
		ASSERT(*endptr == NULL);
#else
		//gcc uses something else.
		//a wchar_t is a long int there
		
		const unsigned short * buf =  a.rawBuffer();
		char * buf_copy = new char[a.length() + 1];
		unsigned int a_length;
		for (a_length = 0; a_length < a.length(); a_length++)
		{
			if (*(buf + a_length) > 127 )
				throw udm_exception("Non ASCII characters are not supported on this platform!");
			*(buf_copy + a_length) = *(buf + a_length);
		};
		*(buf_copy + a_length) = '\0';
		char * endptr;
		unsigned long retval = strtoul(buf_copy+2, &endptr, 16);
		ASSERT(*endptr == '\0');
		delete buf_copy;
		
#endif
		return retval;
	};//eo unsigned long GetLongID(DOMString &a)


	class StrX
	{
	private :
		char*   fLocalForm;
	
	
	public :
		StrX(const DOMString &toTranscode)
		{
			
			fLocalForm = toTranscode.transcode();
		}
    
		StrX(const XMLCh* const toTranscode)
		{
			// Call the private transcoding method
			fLocalForm = XMLString::transcode(toTranscode);
		}

		~StrX()
		{
			delete [] fLocalForm;
		}

		const char* localForm() const { return fLocalForm; }

		
	};

	DOM_Element getElementNamed(DOM_Element parent, const DOMString &name, const DOMString &ns_name, bool create = false, int no = 1)
	{
		DOM_Element elem;
		int i = 0;
		DOM_Node n = parent.getFirstChild(); 
		while (n != (DOM_NullPtr *)NULL)
		{
			if( n.getNodeType() == DOM_Node::ELEMENT_NODE )
			{
				if ( (n.getLocalName().equals(name)) && (n.getPrefix().equals(ns_name)))
				{
					elem = (DOM_Element&)(n);
					i++;
					if (i == no)
						return elem;
				}
			}
			n = n.getNextSibling();
		}
		if (create)
		{
			DOMString ns_uri(UDM_DOM_URI_PREFIX);
			ns_uri += "/";
			ns_uri += ns_name;

			DOMString qualified_name(ns_name);
			qualified_name += ":";
			qualified_name += name;

			elem = parent.getOwnerDocument().createElementNS(ns_uri, qualified_name);
			parent.appendChild(elem);
			return elem;
		}
		return DOM_Element();
	};




	void setTextValue(DOM_Element parent_element, const DOMString &value, const DOMString &name, const DOMString &ns_name, int no = 1)
	{
		DOM_Element parent = getElementNamed(parent_element, name, ns_name, true, no);
		DOM_Text tn;
		if (!parent.hasChildNodes())
		{
			tn = parent.getOwnerDocument().createTextNode(value);
			parent.appendChild(tn);
		}
		else
		{
			DOM_Node ttn = parent.getFirstChild();
			if ( (ttn == (DOM_NullPtr *)NULL) || (ttn.getNodeType() != DOM_Node::TEXT_NODE))
			 throw udm_exception("UdmDom::setTextValue:Existing node is not a child node!");
			tn = (DOM_Text&)ttn;
		};
		tn.setNodeValue(value);
	};

	void setTextValues(DOM_Element parent_element, const vector<string> &values, const DOMString &name, const DOMString &ns_name)
	{
		int i = 0;
		for(vector<string>::const_iterator v_i = values.begin(); v_i != values.end(); v_i++)
		{
			i++;
			const DOMString value = v_i->c_str();
			setTextValue(parent_element, value, name, ns_name, i);
		};
	};


	DOMString getTextValue(DOM_Element parent_element, const DOMString &name, const DOMString& ns_name, int no = 1)
	{
		DOMString a;
		DOM_Element parent = getElementNamed(parent_element, name, ns_name, false, no);
		if (parent == (DOM_NullPtr *) NULL) return a;
		if (!parent.hasChildNodes()) return a;

		DOM_Node ttn = parent.getFirstChild();
		if ( (ttn == (DOM_NullPtr *)NULL) || (ttn.getNodeType() != DOM_Node::TEXT_NODE))
			throw udm_exception("UdmDom::setTextValue:Existing node is not a child node!");
		
		DOM_Text tn = (DOM_Text&)ttn;

		return tn.getNodeValue();
	};

	void getTextValues(DOM_Element parent_element, vector<string> &values, const DOMString &name, const DOMString &ns_name)
	{
		DOMString a;
		int i =0;
		do
		{
			i++;
			a = getTextValue(parent_element, name, ns_name, i);
			if (a != (const DOM_NullPtr *)NULL ) values.push_back(StrX(a).localForm());
		} while (a != (const DOM_NullPtr *)NULL);
	};


// --------------------------- DomObject

	typedef Udm::ObjectImpl ObjectImpl;
	typedef Udm::DataNetwork DataNetwork;

	class DomObject : public ObjectImpl
	{
	
		
	//friends	
	friend void		SaveAs(Object &rootelement, const char *filename);
	
	
	//we need to set static_order data
	//when OpenExisting() a Data Network which has 
	//ID assignments
	friend void		DomDataNetwork::MapExistingIDs(DOM_Node &d);
	

	private:
		static uniqueId_type static_orderdata;
		const DataNetwork * mydn;
	
		
	public:	
		DOM_Element dom_element;
		
		
		DomObject(const ::Uml::Uml::Class &meta, const DOM_Element &n, const DataNetwork * dn = NULL) :
		dom_element(n), m_type(meta)
		{
		
			mydn = dn;
			if (!mydn) throw udm_exception("DomObject without a data network ?");
		}

		
		DomObject(/*const ::Uml::Uml::Diagram &diagram,*/ DOM_Element &element,  const DataNetwork * dn = NULL) : dom_element(element)
		{
			mydn = dn;
			if (!mydn) throw udm_exception("DomObject without a data network ?");

			m_type = findClass(element);
			
		}

		// --- reference counting
		// DOM does the reference counting, DOM_Element is just another pointer
		

		ObjectImpl *clone()
		{
			TRY_XML_EXCEPTION
		
			return new DomObject(m_type, dom_element, mydn);

			CATCH_XML_EXCEPTION("DomObject::clone()");
		}//eo clone()

		void release()
		{
			//delete from map (do we need to ?)No! Only when parent is set to NULL!

			delete this;
		}//eo release()

		bool isSubtype() const
		{
			//DOMString a = dom_element.getAttribute("subtype");
			DOMString a = dom_element.getAttribute(_udm_dom_ia_subtype);

			if(!a.length()) return false;		 // default is false!
			return a.charAt(0) == XMLCh('t');	 // true			
		}

		bool isInstance() const
		{
			DOMString a = dom_element.getAttribute(_udm_dom_ia_subtype);

			if(!a.length()) return false;		 // default is false!
		
			return a.charAt(0) == XMLCh('f');	 // true			
		}

		Udm::DataNetwork *__getdn() 
		{
			return const_cast<Udm::DataNetwork*>(mydn);
		}//eo __getdn();


	// --- lookup

		::Uml::Uml::Class findClass(DOM_Element &element) const
		{
			//This could be faster also, diagram are relatively small
			//so I don't waste my time here
			/*
			StrX cl_name(element.getLocalName());		//class name
			StrX ns_name(element.getPrefix());		//name space	
			*/
			StrX key(element.getNodeName());		//namespace:class

			map<string, ::Uml::Uml::Class>::iterator mcc_i = ((DomDataNetwork *)mydn)->meta_class_cache.find(key.localForm());
			if (mcc_i != ((DomDataNetwork *)mydn)->meta_class_cache.end())
				return mcc_i->second;

			throw udm_exception("Not found");
		}; //eo findClass()


		//next set of functions are invoked a lot of times
		//and as such they must be fast

		

		// returns index (>= 0), -1 if not found
		static int DSFind(const DOMString &where, const DOMString &what) {
			if(what == NULL) throw udm_exception("Search for null string");
			if(where == NULL) return -1;
			
			int wl = what.length();
			int rl = where.length() - wl;
			
#ifdef _WIN32
			const wchar_t* rb = where.rawBuffer();
			const wchar_t* wb = what.rawBuffer();
			for(int i = 0; i <= rl; i++) {
				if(wcsncmp(rb++, wb, wl) == 0) return i; 
			}
#else
			const unsigned short * rb = where.rawBuffer();
			const unsigned short * wb = what.rawBuffer();
			
			char * rb_copy = new char[where.length() + 1];
			char * wb_copy = new char[what.length() + 1];
			unsigned int i;
			
			for( i= 0; i < where.length(); i++) 
			{
				if ( *(rb+i) > 127)
					throw udm_exception("Wide characters are not supported on this platform!");
				*(rb_copy+i) = *(rb+i);
			}
			*(rb_copy+i) = '\0';

			for ( i= 0; i < what.length(); i++) 
			{
				if ( *(wb+i) > 127)
					throw udm_exception("Wide characters are not supported on this platform!");
				*(wb_copy+i) = *(wb+i);
			}
			*(wb_copy+i) = '\0';
	


			for(int i = 0; i <= rl; i++) {
				if(strncmp(rb_copy + i, wb_copy, wl) == 0) return i; 
			}

			delete rb_copy;
			delete wb_copy;
#endif
			return -1;
		};


		DOMString GetID() 
		{
			//static unsigned long idcount = time(NULL);

			static unsigned long id;
			DOMString a = dom_element.getAttribute(DOMString("_id"));
			if(a == 0) 
			{
				//begins with 'id'				
				char buf[20];
				buf[0] = 'i';
				buf[1] = 'd';
				//we have a unique id for ordering
				//so why maintain two of them ?
				id  = uniqueId();	
				//build the string attribute
				
				//ultoa is not POSIX
				//ultoa(id , buf+2, 16);
				sprintf(buf,"id%lx", id);
				a = buf;
				//assign it

				dom_element.setAttribute(DOMString("_id"), a);
				
				//store in the map, so we can search.
				//the insert is expected to be very fast,
				//since the keys are inserted in the right order
				
			}
			return a;
		};

		


	// --- type

		::Uml::Uml::Class m_type;

		//const ::Uml::Uml::Class &m_type;

		const ::Uml::Uml::Class &type() const { return m_type; }

	// --- order

		

		uniqueId_type uniqueId() const 
		{
			void *p = dom_element.getUserData();
			

			if( p == NULL )
			{
				p = (void*)++static_orderdata;
				const_cast<DOM_Element&>(dom_element).setUserData(p);
				((DomDataNetwork*)mydn)->DoMapping(dom_element, reinterpret_cast<uniqueId_type>(p), true);		
			
			
				if (const_cast<DomObject*>(this)->__getdn()->GetProject() != NULL)
				{
					//this is part of the project
					//we will record every id in the backend

					static unsigned long id;
					DOMString a = dom_element.getAttribute(DOMString("_id"));
					if(a == 0) 
					{
						//begins with 'id'				
						char buf[20];
						buf[0] = 'i';
						buf[1] = 'd';
						id  = reinterpret_cast<uniqueId_type>(p);	
						sprintf(buf,"id%lx", id);
						a = buf;
						
						const_cast<DomObject*>(this)->dom_element.setAttribute(DOMString("_id"), a);
				
					}
				};
			};
			return reinterpret_cast<uniqueId_type>(p);
		}

		void desynch_attribute(const string myname)
		{
			
			//DOMString pa = dom_element.getAttribute(DOMString("desynched_atts"));
			DOMString pa = dom_element.getAttribute(DOMString(_udm_dom_ia_desynched_atts));
			if(pa == NULL) 
			{
				//dom_element.setAttribute( DOMString("desynched_atts"), DOMString(myname.c_str()));
				dom_element.setAttribute( DOMString(_udm_dom_ia_desynched_atts), DOMString(myname.c_str()));
			}
			else
			{
				//the attribute desynched_atts exists
				int k = DSFind(pa, DOMString(myname.c_str()));
				if(k <= 0) 
				{
					//meta is not yet desynched
					pa.appendData(' ');
					pa.appendData(DOMString(myname.c_str()));
					//dom_element.setAttribute(DOMString("desynched_atts"), pa);
					dom_element.setAttribute(DOMString(_udm_dom_ia_desynched_atts), pa);
				}
			}
				
		}

		bool is_attribute_desynched(const string &myname)
		{
			
			//DOMString pa = dom_element.getAttribute(DOMString("desynched_atts"));
			DOMString pa = dom_element.getAttribute(DOMString(_udm_dom_ia_desynched_atts));
			if(pa == NULL) return false;
			int k = DSFind(pa, DOMString(myname.c_str()));
			return (k >= 0);
			
		}
	/*

		Text attributes are supposed to generate multiple elements containing a single XML text node
	*/

		void setStringAttrArr(const ::Uml::Uml::Attribute &meta, const vector<string> &a, const bool direct)
		{
			//for String attibutes we have the same behaviour
			if ((string)meta.type() !=  "Text") ObjectImpl::setStringAttrArr(meta, a, direct);
			
			string name = meta.name();

			ObjectImpl * archetype = getArchetype();
			if (archetype && (archetype != (ObjectImpl*)&Udm::_null) )
			{
				if(direct)
				{
					DOMString ns_name =   ((string)((::Uml::Uml::Namespace)m_type.parent()).name()).c_str();
					setTextValues(dom_element,a,  DOMString(name.c_str()), ns_name);
					//desynch the attribute
					desynch_attribute(name);
				}
				else
				{
					//check if desynched
					if (!is_attribute_desynched(name))
					{
						DOMString ns_name =   ((string)((::Uml::Uml::Namespace)m_type.parent()).name()).c_str();
						setTextValues(dom_element,a,  DOMString(name.c_str()), ns_name);		
					}
				}
			}
			else
			{
				DOMString ns_name =   ((string)((::Uml::Uml::Namespace)m_type.parent()).name()).c_str();
				setTextValues(dom_element,a,  DOMString(name.c_str()), ns_name);
				//go through all derived and instances
				vector<ObjectImpl*>::iterator i;
				vector<ObjectImpl*> deriveds = getDerived();
				for (i = deriveds.begin(); i != deriveds.end(); i++)
				{
					ObjectImpl* derived = *i;
					derived->setStringAttrArr(meta, a, false);
					derived->release();
				}

				vector<ObjectImpl*> instances = getInstances();
				for (i = instances.begin(); i != instances.end(); i++)
				{
					ObjectImpl* instance = *i;
					instance->setStringAttrArr(meta, a, false);
					instance->release();
				}
			}
		
		};
		vector<string> getStringAttrArr(const ::Uml::Uml::Attribute &meta) const
		{
			//for String attibutes we have the same behaviour
			if ((string)meta.type() !=  "Text") return ObjectImpl::getStringAttrArr(meta);
			vector<string> ret;
			DOMString ns_name =   ((string)((::Uml::Uml::Namespace)m_type.parent()).name()).c_str();
			getTextValues(dom_element, ret, DOMString(((string)meta.name()).c_str()), ns_name);

			return ret;
		};
		
		string getStringAttr(const ::Uml::Uml::Attribute &meta) const
		{
			DOMString a;

			// TODO: avoid the name conversion
			if ((string)(meta.type()) == "Text")
			{
				DOMString ns_name =   ((string)((::Uml::Uml::Namespace)m_type.parent()).name()).c_str();

				a = getTextValue(dom_element, DOMString(((string)meta.name()).c_str()), ns_name);
			}	
			else
			{
				string name = meta.name();
				DOM_Attr as = dom_element.getAttributeNode(DOMString(name.c_str()));
				if(as != (DOM_NullPtr *)NULL && as.getSpecified()) 
				{
					a = as.getValue();
				}
	//			if(!a.length()) return meta.defvalue();
			}
			return StrX(a).localForm();
		}


		void setStringAttr(const ::Uml::Uml::Attribute &meta, const string &a, const bool direct = true)
		{
			// TODO: avoid the name conversion

			string name = meta.name();

			ObjectImpl * archetype = getArchetype();
			if (archetype && (archetype != (ObjectImpl*)&Udm::_null) )
			{
				if(direct)
				{
					//set the attribute
					if ((string)(meta.type()) == "Text")
					{
						DOMString ns_name =   ((string)((::Uml::Uml::Namespace)m_type.parent()).name()).c_str();
						setTextValue(dom_element,DOMString(a.c_str()),  DOMString(name.c_str()), ns_name);
					}
					else
						dom_element.setAttribute( DOMString(name.c_str()), DOMString(a.c_str()));

					//desynch the attribute
					desynch_attribute(name);
				}
				else
				{
					//check if desynched
					if (!is_attribute_desynched(name))
					{
						//if not, set the attribute
						if ((string)(meta.type()) == "Text")
						{
							DOMString ns_name =   ((string)((::Uml::Uml::Namespace)m_type.parent()).name()).c_str();
							setTextValue(dom_element,DOMString(a.c_str()),DOMString(name.c_str()), ns_name);
						}
						else
							dom_element.setAttribute( DOMString(name.c_str()), DOMString(a.c_str()));
					}
				}
				archetype->release();
			}
			else
			{
				if ((string)(meta.type()) == "Text")
				{
					DOMString ns_name =   ((string)((::Uml::Uml::Namespace)m_type.parent()).name()).c_str();
					setTextValue(dom_element,DOMString(a.c_str()),DOMString(name.c_str()), ns_name);
				}
				else		
					dom_element.setAttribute( DOMString(name.c_str()), DOMString(a.c_str()));
			}
			
			//go through all derived and instances
			vector<ObjectImpl*>::iterator i;
			vector<ObjectImpl*> deriveds = getDerived();
			for (i = deriveds.begin(); i != deriveds.end(); i++)
			{
				ObjectImpl* derived = *i;
				derived->setStringAttr(meta, a, false);
				derived->release();
			}

			vector<ObjectImpl*> instances = getInstances();
			for (i = instances.begin(); i != instances.end(); i++)
			{
				ObjectImpl* instance = *i;
				instance->setStringAttr(meta, a, false);
				instance->release();
			}

		}

		bool getBooleanAttr(const ::Uml::Uml::Attribute &meta) const
		{
			// TODO: avoid the name conversion
			string name = meta.name();
			DOMString a = dom_element.getAttribute(DOMString(name.c_str()));
//			if(!a.length()) {
//				a = string(meta.defvalue()).c_str();
//			}
			if(!a.length()) return false;
			return a.charAt(0) == XMLCh('t');	 // true
		}

		void setBooleanAttr(const ::Uml::Uml::Attribute &meta, bool a, const bool direct = true)
		{
			string name = meta.name();

			ObjectImpl * archetype = getArchetype();
			if (archetype && (archetype != (ObjectImpl*)&Udm::_null) )
			{
				if(direct)
				{
					//set the attribute
#ifdef _WIN32
					dom_element.setAttribute(DOMString(name.c_str()), DOMString(a?L"true":L"false"));
#else
					dom_element.setAttribute(DOMString(name.c_str()), DOMString(a?"true":"false"));
#endif
					//desynch the attribute
					desynch_attribute(name);
				}
				else
				{
					//check if desynched
					if (!is_attribute_desynched(name))
					//if not, set the attribute
#ifdef _WIN32
					dom_element.setAttribute(DOMString(name.c_str()), DOMString(a?L"true":L"false"));
#else
					dom_element.setAttribute(DOMString(name.c_str()), DOMString(a?"true":"false"));
#endif

				}
				archetype->release();
			}
			else
			{
#ifdef _WIN32
					dom_element.setAttribute(DOMString(name.c_str()), DOMString(a?L"true":L"false"));
#else
					dom_element.setAttribute(DOMString(name.c_str()), DOMString(a?"true":"false"));
#endif

			}
			
			//go through all derived and instances
			vector<ObjectImpl*>::iterator i;
			vector<ObjectImpl*> deriveds = getDerived();
			for (i = deriveds.begin(); i != deriveds.end(); i++)
			{
				ObjectImpl* derived = *i;
				derived->setBooleanAttr(meta, a, false);
				derived->release();
			}

			vector<ObjectImpl*> instances = getInstances();
			for (i = instances.begin(); i != instances.end(); i++)
			{
				ObjectImpl* instance = *i;
				instance->setBooleanAttr(meta, a, false);
				instance->release();
			}

			// TODO: avoid the name conversion
			
		}

		__int64 getIntegerAttr(const ::Uml::Uml::Attribute &meta) const
		{
			// TODO: avoid the name conversion
			string name = meta.name();
			DOMString a = dom_element.getAttribute(DOMString(name.c_str()));
//			if(!a.length()) {
//				a = string(meta.defvalue()).c_str();
//			}
			if(!a.length()) return 0;
			//_wtol is not posix, but works OK on WIN32
#ifdef _WIN32
			return _wtoi64(a.rawBuffer());  
#else
			int i;
			int a_length = a.length();
			const unsigned short * buf = a.rawBuffer();
			char * copy = new char[a_length + 1];
			for ( i = 0; i < a_length; i++)
			{
				if (*(buf + i) > 127)
					throw udm_exception("Wide characters not supported on this platform!");

				*(copy + i) = *(buf + i);
			}
			*(copy + i) = '\0';
			long retval;
			if (sscanf(copy, "%ld", &retval) != 1)
			{
				throw udm_exception("Attribute format error!");
			}
			delete copy;
			return retval;
#endif
			//TODO: error checking??
		}

		void setIntegerAttr(const ::Uml::Uml::Attribute &meta, __int64 a, const bool direct = true)
		{
			// TODO: avoid the name conversion
			string name = meta.name();

			ObjectImpl * archetype = getArchetype();
			if (archetype && (archetype != (ObjectImpl*)&Udm::_null) )
			{
				if(direct)
				{
					//set the attribute
					char astr[50];
#ifdef _WIN32
					sprintf(astr, "%I64d",a);
#else
					sprintf(astr, "%lld", a);
#endif
					dom_element.setAttribute(DOMString(name.c_str()), DOMString(astr));
					//desynch the attribute
					desynch_attribute(name);
				}
				else
				{
					//check if desynched
					if (!is_attribute_desynched(name))
					{
						//if not, set the attribute
						char astr[50];
#ifdef _WIN32
						sprintf(astr, "%I64d",a);
#else
						sprintf(astr, "%lld",a);
#endif
						dom_element.setAttribute(DOMString(name.c_str()), DOMString(astr));
					}
				}
				archetype->release();
			}
			else
			{
				char astr[50];
#ifdef _WIN32
				sprintf(astr, "%I64d",a);
#else	
				sprintf(astr, "%lld",a);
#endif
				dom_element.setAttribute(DOMString(name.c_str()), DOMString(astr));
			}
				
			//go through all derived and instances
			vector<ObjectImpl*>::iterator i;
			vector<ObjectImpl*> deriveds = getDerived();
			for (i = deriveds.begin(); i != deriveds.end(); i++)
			{
				ObjectImpl* derived = *i;
				derived->setIntegerAttr(meta, a, false);
				derived->release();
			}

			vector<ObjectImpl*> instances = getInstances();
			for (i = instances.begin(); i != instances.end(); i++)
			{
				ObjectImpl* instance = *i;
				instance->setIntegerAttr(meta, a, false);
				instance->release();
			}

/*			
			char astr[50];
			sprintf(astr, "%d",a);
			dom_element.setAttribute(DOMString(name.c_str()), DOMString(astr));
*/

		}

		double getRealAttr(const ::Uml::Uml::Attribute &meta) const
		{
			// TODO: avoid the name conversion
			string name = meta.name();
			DOMString a = dom_element.getAttribute(DOMString(name.c_str()));
//			if(!a.length()) {
//				a = string(meta.defvalue()).c_str();
//			}
			if(!a.length()) return 0.0;
			double d;
#ifdef _WIN32
			if(swscanf(a.rawBuffer(), L"%lf", &d) != 1) throw udm_exception("Attr is of non-float format");
#else
			int i;
			int a_length = a.length();
			
			const unsigned short * buf = a.rawBuffer();
			char * copy = new char[a_length + 1];
			for(i = 0; i < a_length; i++)
			{
				if (*(buf + i) > 127)
					throw udm_exception("Wide characters not supported on this platform!");

				*(copy + i) = *(buf + i);
			}
			*(copy + i) = '\0';
			if(sscanf(copy, "%lf", &d) != 1) throw udm_exception("Attr is of non-float format");
			delete copy;

#endif		

			return d;
		}

		void setRealAttr(const ::Uml::Uml::Attribute &meta, double a, const bool direct = true)
		{
			

			// TODO: avoid the name conversion
			string name = meta.name();
			ObjectImpl * archetype = getArchetype();
			if (archetype && (archetype != (ObjectImpl*)&Udm::_null) )
			{
				if(direct)
				{
					//set the attribute
					char astr[50];
					sprintf(astr, "%lf", a);
					dom_element.setAttribute(DOMString(name.c_str()), DOMString(astr));

					//desynch the attribute
					desynch_attribute(name);
				}
				else
				{
					//check if desynched
					if (!is_attribute_desynched(name))
					{
						//if not, set the attribute
						char astr[50];
						sprintf(astr, "%lf", a);
						dom_element.setAttribute(DOMString(name.c_str()), DOMString(astr));
					}

				}
				archetype->release();
			}
			else
			{
				char astr[50];
				sprintf(astr, "%lf", a);
				dom_element.setAttribute(DOMString(name.c_str()), DOMString(astr));
			}
				
			//go through all derived and instances
			vector<ObjectImpl*>::iterator i;
			vector<ObjectImpl*> deriveds = getDerived();
			for (i = deriveds.begin(); i != deriveds.end(); i++)
			{
				ObjectImpl* derived = *i;
				derived->setRealAttr(meta, a, false);
				derived->release();
			}

			vector<ObjectImpl*> instances = getInstances();
			for (i = instances.begin(); i != instances.end(); i++)
			{
				ObjectImpl* instance = *i;
				instance->setRealAttr(meta, a, false);
				instance->release();
			}

			/*
			char astr[50];
			sprintf(astr, "%lf", a);
			dom_element.setAttribute(DOMString(name.c_str()), DOMString(astr));
			*/
			
		}

	


		string GetANameFor(const ::Uml::Uml::Composition &comp) const {

			::Uml::Uml::CompositionChildRole chr = comp.childRole();
			string ret = chr.name();
			if(ret.empty()) ret = string(::Uml::Uml::Class(chr.target()).name());
			return ret;
		}

	// --- containment
		ObjectImpl *getParent(const ::Uml::Uml::CompositionParentRole &role) const 
		{
// TODO: check role if not NULLROLE

			TRY_XML_EXCEPTION
			
			DOM_Node parent = dom_element.getParentNode();
			
			if ((parent == (DOM_NullPtr *)NULL) || (parent.getNodeType() != DOM_Node::ELEMENT_NODE)) 	return &Udm::_null;
			
			DomObject * do_parent = new DomObject(static_cast<DOM_Element&>(parent), mydn);
			
			
			if(role) {
				::Uml::Uml::Composition comp = Uml::matchChildToParent(m_type, role.target()); 
				

				//this will return the null object when there are multiple 
				//possible compositions and the current composition doesn't match
				//the requested compostion
				if(!comp && DSFind(dom_element.getAttribute("__child_as"), DOMString(GetANameFor(role.parent()).c_str())) < 0)  
					return &Udm::_null;

				//still need to check the type
				//even if there is only on possible composition between me as child
				//and role.target() as parent,
				//might happen that my parent is not the requested one
				
				set<::Uml::Uml::Class> cl_s = Uml::DescendantClasses(role.target());

				if (cl_s.find(do_parent->m_type)  != cl_s.end())
					return do_parent;
				else 
				{
					delete do_parent;
					return &Udm::_null;
				}

			}
			
			return do_parent;

			CATCH_XML_EXCEPTION("DomObject::getParent()");
			
			
		}


		void removeAssociation(const DOMString &tname, const DOMString &oname, 
								const DOMString &myid) 
		{



#ifndef DEBUG
char buf1[100]; strcpy(buf1, StrX(tname).localForm());
#endif
#ifndef DEBUG
char buf2[100]; strcpy(buf2, StrX(oname).localForm());
#endif
			DOMString origattr = dom_element.getAttribute(tname);
#ifndef DEBUG
char buf3[100]; strcpy(buf3, StrX(origattr).localForm());
#endif

//cout << "Attr remove" << buf1 << buf2 << buf3 << endl;
			dom_element.removeAttribute(tname);
			{
				const XMLCh *i = origattr.rawBuffer();
				const XMLCh *end = i + origattr.length();

				for(;;)
				{
					// skip the white spaces
					while( i < end && *i == XMLCh(' ') )
						++i;

					if( i >= end )
						break;

					// find the end of the IDREF
					const XMLCh *p = i + 1;
					while( p < end && *p != XMLCh(' ') )
						++p;

					DOM_Document doc = dom_element.getOwnerDocument();
					DOM_Element e = doc.getElementById(DOMString(i, p-i));
					if(e == NULL) e = ((DomDataNetwork*)mydn)->Search(doc, DOMString(i, p-i));

					// the ID must exists
					ASSERT( e != (DOM_NullPtr *)NULL );

					DOMString cpa = e.getAttribute(oname);
					int k = DSFind(cpa, myid);
					if(k >= 0) cpa.deleteData(k, myid.length()+1);
					if(cpa == NULL || !cpa.length()) e.removeAttribute(oname);
					else e.setAttribute(oname, cpa);

					i = p + 1;
				}
			}
		}

		void recursiveRemoveAssocs() 
		{

			TRY_XML_EXCEPTION

			// delete associations the element is involved in
			DOMString myid = dom_element.getAttribute(DOMString("_id"));
			
			if(myid != 0) 
			{
				set<::Uml::Uml::AssociationRole> rs = Uml::AncestorAssociationTargetRoles(m_type);
				for(set<::Uml::Uml::AssociationRole>::iterator role = rs.begin(); role != rs.end(); role++) 
				{
					DOMString tname = Uml::MakeRoleName(*role).c_str();
					DOMString oname = Uml::MakeRoleName(Uml::theOther(*role)).c_str();

					::Uml::Uml::Association aa = role->parent();
					if(::Uml::Uml::Class(aa.assocClass())) 
					{
						oname += "_end_";
					}
					removeAssociation(tname, oname, myid);		
				}
				::Uml::Uml::Association assoc = m_type.association();
				if(assoc) 
				{
					set<::Uml::Uml::AssociationRole> rs = assoc.roles();
					for(set<::Uml::Uml::AssociationRole>::iterator role = rs.begin(); role != rs.end(); role++) 
					{
						DOMString tname = Uml::MakeRoleName(*role).c_str();
						DOMString oname = Uml::MakeRoleName(Uml::theOther(*role)).c_str();
						removeAssociation(tname + "_end_", oname, myid);		

					}
				}
				//if an object with archetype is deleted
				//it should be removed from archetype's list of
				//derived/instances
				//because of the logic of removeAssociation()
				//we cannot simply attempt to return both of them
				//an object is exclusively instance or subtype
				//we remove only the corresponding association
				ObjectImpl * at = getArchetype();
				if ( at && ( at != &Udm::_null) )
				{
					vector<ObjectImpl*> at_deriveds = at->getDerived();
					bool found = false;
					vector<ObjectImpl*>::iterator atd_i = at_deriveds.begin();

					while ((atd_i != at_deriveds.end()))
					{
						ObjectImpl * derived = *atd_i++;
						if (derived->uniqueId() == uniqueId()) found = true;
						derived->release();
					}
					
					if (found)
						//removeAssociation("archetype","derived",myid);
						removeAssociation(_udm_dom_ia_archetype,_udm_dom_ia_derived,myid);
					else
						//removeAssociation("archetype","instances",myid);
						removeAssociation(_udm_dom_ia_archetype,_udm_dom_ia_instances,myid);
				}
			}
			vector<ObjectImpl*> chds = getChildren(NULL,  NULL);
			for(vector<ObjectImpl*>::iterator i = chds.begin(); i != chds.end(); i++) 
			{
				static_cast<DomObject*>(*i)->recursiveRemoveAssocs();
				(*i)->release();
			}

			CATCH_XML_EXCEPTION("DomObject::recursiveRemoveAssocs()");

		}
// role must be specified unless a is null, or child role in the new parent is unambigious
// if a was already the parent, existing other childroles are not deleted
// XML: if multiple roles are enabled, object will keep its existing role(s) as well if not moved to a new parent
		void setParent(ObjectImpl *a, const ::Uml::Uml::CompositionParentRole &role, const bool direct = true) 
		{

			TRY_XML_EXCEPTION 

			DOM_Node currentparent = dom_element.getParentNode();
			Udm::Object this_o = clone();
			
			
			if (direct && ( currentparent != (DOM_NullPtr *)NULL) && 	(currentparent.getNodeType() == DOM_Node::ELEMENT_NODE))
			{
				DomObject * cp_do  = new DomObject(static_cast<DOM_Element&>(currentparent), mydn);
				if (cp_do->isInstance())
					throw udm_exception("setParent: Instantiated objects can not be modified!");
				delete cp_do;
			}
			if(a != NULL && a != &Udm::_null) 
			{
				DomObject &aa = *static_cast<DomObject *>(a);
				
				DOMString chas;

				/*
				archetype/derived/subtype support
				we need to form three Udm::Objects here: this_o, curr_par_o, new_par_o
				we will use TOMI functions here

				*/

				Udm::Object new_par_o = aa.clone();
				
				if (direct)
				{
					if (aa.isInstance())
						throw udm_exception("setParent: Instantiated objects can not be modified!");

				}


				set<Udm::Object> derived_parent_set; 
				set<Udm::Object> derived = this_o.derived();
				set<Udm::Object>::iterator der_i = derived.begin();
				while (der_i != derived.end())
				{
					Udm::Object der_o = *der_i++;
					if (!der_o.hasRealArchetype())	//only matters if it is not a primarily inherited children
					{
						
						Udm::Object derived_subtree =der_o.FindClosestPrimarilyDerivedParent();
						Udm::Object new_par_coresp_o = new_par_o.FindCorrespondingObjectInSubtypesTree(derived_subtree, false);
						if (new_par_coresp_o)
						{
							der_o.__impl()->setParent(new_par_coresp_o.__impl(), role, false);
							derived_parent_set.insert(new_par_coresp_o);
						}
						else
						{
							//it was moved out from the inherited block
							//so what to do ?
							//simply detach it
							der_o.__impl()->setParent(NULL, NULL, false);
						}
					}
				}
	
				set<Udm::Object> instantiated_parent_set;
				set<Udm::Object> instances = this_o.instances();
				set<Udm::Object>::iterator inst_i = instances.begin();
				while (inst_i != instances.end())
				{
					Udm::Object inst_o = *inst_i++;
					if (!inst_o.hasRealArchetype())	//only matters if it is not a primarily inherited children
					{
						
						Udm::Object instance_subtree =inst_o.FindClosestPrimarilyDerivedParent();
						Udm::Object new_par_coresp_o = new_par_o.FindCorrespondingObjectInInstancesTree(instance_subtree, false);
						if (new_par_coresp_o)
						{
							inst_o.__impl()->setParent(new_par_coresp_o.__impl(), role, false);
							instantiated_parent_set.insert(new_par_coresp_o);
						}
						else
						{
							inst_o.__impl()->setParent(NULL, NULL, false);
						}
					}
				}

				

			   /*
				* order the children nodes in the alphabetical order of their types,
				* and as a 2nd level ordering, keep the order of creation of children,
				* within the same type

				currentparent:  DOM_Node,   the current parent of this->dom_element
				aa:				DomObject , the new parent
				m_type:			::Uml::Uml::Class, the type of this
			   */
			   
				if(currentparent != aa.dom_element) 
				{
					bool inserted = false;
					for(DOM_Node n = aa.dom_element.getFirstChild(); n != (DOM_NullPtr *)NULL;n = n.getNextSibling())	
					{
						if( n.getNodeType() == DOM_Node::ELEMENT_NODE )
						{
							StrX name = n.getLocalName();
							
							char * my_type_name = new char[((string)m_type.name()).size() + 1];
							strcpy(my_type_name, ((string)m_type.name()).c_str());

							const char * curr_child_name = name.localForm();

							if (strcmp(my_type_name, curr_child_name) < 0)
							{
								aa.dom_element.insertBefore(dom_element, n);
								inserted = true;
								delete my_type_name;
								break;
							}

							delete my_type_name;

						}
					}
				   if (!inserted)
					aa.dom_element.appendChild(dom_element);


			   }

			   else if(DomDataNetwork::MultiRolesEnabled()) 
				   chas = dom_element.getAttribute(DOMString("__child_as"));
				
			   ::Uml::Uml::CompositionChildRole c_role;

			   ::Uml::Uml::Composition comp = Uml::matchChildToParent(m_type, aa.m_type);
				if(!role) 
				{
					if(!comp) throw udm_exception("Childrole has to be specified");
					// if role == 0 and comp != 0, no test or __child_as is necessary
					c_role = comp.childRole();
				}
				else if(comp != role.parent()) 
				{  // either 0 or different kinds
					comp = role.parent();
					// if different, or comp is 0 because of 0 roles, one of the followings will catch it:
					if(!Uml::IsDerivedFrom(m_type,::Uml::Uml::CompositionChildRole(comp.childRole()).target())) 
					{
						throw udm_exception("Invalid parentrole specified");
					}
					if(!Uml::IsDerivedFrom(aa.m_type, ::Uml::Uml::CompositionParentRole(comp.parentRole()).target())) 
					{
						throw udm_exception("Invalid parent specified");
					}

					// we only get here, if multiple roles match, so they have to be recorded
					DOMString  ncomp(GetANameFor(comp).c_str());
					if(chas != (DOM_NullPtr *)NULL) 
					{
						if(DSFind(chas,ncomp) < 0) 
						{
							chas.appendData(' ');
							chas.appendData(ncomp);
							dom_element.setAttribute(DOMString("__child_as"), chas);
						}
					}
					else dom_element.setAttribute(DOMString("__child_as"), ncomp);

					c_role = Uml::theOther(role);
				}

				//what if new parent has derived/instantiated objects?
				//and the new object just added(this) is coming from outside
				if (direct)
				{
					derived = new_par_o.derived();
					der_i = derived.begin();
					while (der_i != derived.end())
					{
						if (derived_parent_set.find(*der_i) == derived_parent_set.end())
							Object newObj = der_i->__impl()->createChild(c_role, m_type, this, true, false);
						der_i++;
					}

					instances = new_par_o.instances();
					inst_i = instances.begin();
					while (inst_i != instances.end())
					{
						if (instantiated_parent_set.find(*inst_i) == instantiated_parent_set.end())
							Object newObj = inst_i->__impl()->createChild(c_role, m_type, this, false, false);
						inst_i++;
					}
				}

			}
			else 
			{   // new parent is null, unlink from the object tree
				ObjectImpl *parent = getParent(Udm::NULLPARENTROLE);
				if(parent && parent != &Udm::_null) 
				{  //delete parent


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

					{
						//unlink all derived objects
						//unlink all instances
						vector<ObjectImpl*>deriveds = getDerived();
						vector<ObjectImpl*>instances = getInstances();
						vector<ObjectImpl*>::iterator i;

						//the detach() call will result in setParent(NULL, NULL)
						//and that will result in recursion here
						//and that will take care of removing all the objects
						//along an archetype/derived or archetype/instances 
						//tree
						for(i = deriveds.begin(); i != deriveds.end(); i++)
							(*i)->setParent(NULL, NULL, false);

						for(i = instances.begin(); i != instances.end(); i++)
							(*i)->setParent(NULL, NULL, false);

					}

					recursiveRemoveAssocs();
					DomObject &aa = *static_cast<DomObject *>(parent);
					if(role) 
					{
						if(!Uml::IsDerivedFrom(m_type, Uml::theOther(role).target())) 
						{
							throw udm_exception("Invalid parentrole specified");
						}
						if(!Uml::IsDerivedFrom(aa.m_type, role.target())) 
						{			// irrelevant role, no change
							return;
						}
//#ifdef RECORD_ROLES
						::Uml::Uml::Composition comp = Uml::matchChildToParent(m_type, aa.m_type);
						if(!comp) 
						{
							comp = role.parent();
							DOMString ncomp(GetANameFor(comp).c_str());
							DOMString chas = dom_element.getAttribute(DOMString("__child_as"));
							int p = DSFind(chas , ncomp);
							if(p < 0) return; // not found, no change
							if(p != 0 || chas.length() != ncomp.length()) {
								chas.deleteData(p ? p-1 : 0, ncomp.length() + 1);  // make sure we delete a separator as well
								dom_element.setAttribute(DOMString("__child_as"), chas);
								return;												// do not delete child if multiroles were in effect
							}
							ASSERT( chas.compareString(ncomp) == 0);
						}
						else 
						{ 
							// Only a single compositionrole matches these two kinds
							ASSERT(comp == role.parent());
						}
//#endif
					}
					//we are class DOMObject
					//dom_element is our private var of type DOM_Element
					//in the map there *might* be a mapping from unique id to dom_element
					//we remove it, if there is
					//also note that it's not a must
					unsigned long id = uniqueId();
					//Minor bugfix here
					//element should be removed after removing from the mapping.
					//since __getdn() calls need the DOM tree to be consistent
					//endre, 02/22/02
					
					IdToDomElementMap::iterator i = ((DomDataNetwork*)__getdn())->DomElements.find(id);
					//there might be dom elements that unique id is not set!
					if (i != ((DomDataNetwork*)__getdn())->DomElements.end()) ((DomDataNetwork*)__getdn())->DomElements.erase(i);
			
//#ifdef RECORD_ROLES
				
					dom_element.removeAttribute(DOMString("__child_as"));
					aa.dom_element.removeChild(dom_element);
//#endif
				}
			}

			CATCH_XML_EXCEPTION("DomObject::setParent");
		}

		void detach() 
		{
				setParent(NULL, NULL);
		}

		vector<ObjectImpl*> getChildren(const ::Uml::Uml::CompositionChildRole &role, const ::Uml::Uml::Class &kind) const {
			vector<ObjectImpl*> ret;
			DOMString compname;
			::Uml::Uml::Class target;

				
			//::Uml::Uml::Diagram diagram = m_type.parent();

			//checking if role is valid for this object
			// getting the name for __child_as attribute, when composition is ambigous 
			if(role) 
			{
				target = role.target();

				if(!Uml::IsDerivedFrom(m_type, Uml::theOther(role).target())) throw udm_exception("Invalid role specified");
				compname = GetANameFor(::Uml::Uml::Composition(role.parent())).c_str();
			}

			
			for(DOM_Node n = dom_element.getFirstChild(); n != (DOM_NullPtr *)NULL;n = n.getNextSibling())	
			{
				if( n.getNodeType() == DOM_Node::ELEMENT_NODE )
				{
					DOM_Element e = static_cast<DOM_Element&>(n);
					::Uml::Uml::Class m = findClass( e);

					if(role &&  Uml::IsDerivedFrom(m, target) ) 
					{
						//both , role was provided AND element e of type m is derived from childrole's target
						::Uml::Uml::Composition comp = Uml::matchChildToParent(m, m_type);
						
						//this returns NULL if composition was ambigous
						
						if(!comp && DSFind(e.getAttribute("__child_as"), compname) < 0) 
							//composition was ambigous and the element e of type m is not via childrole role.(so it won't be in the vector)
							continue;
						
						//composition is not ambigous, it's OK to add to vector
						//if kind was provided, check the type .. 
						if(kind && !Uml::IsDerivedFrom(m, kind)) continue;
						ret.push_back(new DomObject(m, e, mydn));
					}
					else
					{
						//either role was not provided OR type m of element e is unrelated with target's role
						if (!role)
						{
							//role was not provided, but type is ok.
							if(kind && !Uml::IsDerivedFrom(m, kind)) continue;
							ret.push_back(new DomObject(m, e, mydn));
						}
					}
					
				}

			}
			return ret;
		}

		vector<ObjectImpl*> sortchildren(const vector<ObjectImpl*> &a)
		{
			typedef vector<ObjectImpl*> implvec;
			map<const string, implvec> map_seq;
			vector<ObjectImpl*>::const_iterator a_i = a.begin();
			while (a_i != a.end())
			{
				vector<ObjectImpl*> & vec = map_seq[(*a_i)->type().name()];
				vec.push_back(*a_i++);

			}

			vector<ObjectImpl*> ret;

			map<const string, implvec>::iterator map_seq_i = map_seq.begin();
			while (map_seq_i != map_seq.end())
			{

				vector<ObjectImpl*>  vec = map_seq_i->second;
				
				vector<ObjectImpl*>::iterator vec_i = vec.begin();

				while (vec_i != vec.end())
					ret.push_back(*vec_i++);

				map_seq_i++;
			};
			
			return ret;
		};

		void setChildren(const ::Uml::Uml::CompositionChildRole &role, const vector<ObjectImpl*> &a, const bool direct = true) 
		{
			
			Udm::Object this_o = clone();

			Udm::Object archetype = this_o.archetype();

			
			set<Udm::Object> erased;
			
			vector<ObjectImpl*> existing_children = getChildren(role, NULL);
			vector<ObjectImpl*>::iterator ec_i = existing_children.begin();
			while (ec_i != existing_children.end())
				erased.insert(*ec_i++);	//this is safe, getChildren() cloned the ObjectImpls
			

			set<Udm::Object> a_set;
			for(vector<ObjectImpl *>::const_iterator a_set_i = a.begin(); a_set_i != a.end(); a_set_i++) 
			{
				ObjectImpl * a_i = *a_set_i;
				a_set.insert(a_i->clone());		//Object is consturcted, will be released there
			}

			
			if (direct && archetype)
			{
				set<Udm::Object> instances = archetype.instances();

				if (instances.find(clone()) != instances.end()) //an Object is constructed, thus will be released
					throw udm_exception("Instance objects can not be modified!");

				//check whether instance children are going to be deleted
				//if so, that is an error.
				
			

				set<Object>::iterator ec_i = erased.begin();

				while (ec_i != erased.end())
				{
					if (a_set.find(*ec_i++) == a_set.end())
					{
						//an existing object is going to be deleted....
						if (ec_i->archetype() && !ec_i->hasRealArchetype())	//if it's an inherited children
							throw udm_exception("Inherited children objects can not be deleted!");
					}
				}
			}

			//we unlink all objects in erased, they would be deleted anyway.
			//but this way we make sure the links are removed OK.

			for( set<Object>::iterator erased_i = erased.begin();  erased_i != erased.end(); erased_i++)
			{
				erased_i->__impl()->detach();
			};


			DOM_Node n = dom_element.getFirstChild();
			while( n != (DOM_NullPtr *)NULL)	
			{
				if( n.getNodeType() == DOM_Node::ELEMENT_NODE )
				{
			
			
					DOM_Element nn = static_cast<DOM_Element&>(n);

					//const ::Uml::Uml::Diagram & diag = m_type.parent();
					
					DomObject * existing_child = new DomObject(/*diag,*/ nn, mydn);
					if (!(role && !Uml::IsDerivedFrom(existing_child->m_type, role.target())))
					{

						dom_element.removeChild(nn);
//#ifdef RECORD_ROLES
						//this doesn't make sense to me
						//dom_element.removeAttribute(DOMString("__child_as"));
						nn.removeAttribute(DOMString("__child_as"));

						n = dom_element.getFirstChild();

					}
//#endif

					else n = n.getNextSibling();
				}
			}

			//sort the children by their type!
			vector<ObjectImpl*> a_sorted = sortchildren(a);


			for(vector<ObjectImpl *>::const_iterator i = a_sorted.begin(); i != a_sorted.end(); i++) 
			{
				DomObject &de = *static_cast<DomObject *>(*i);
				
				
//#ifdef RECORD_ROLES
				::Uml::Uml::Composition comp = Uml::matchChildToParent(de.m_type, m_type);
				if(!role) 
				{
					if(!comp) throw udm_exception("Childrole has to be specified");
					// if role == 0 and comp != 0, no test or __child_as is necessary
					
				}
				else if(comp != role.parent()) 
				{  // either 0 or different
				
					comp = role.parent();
					// if different, or comp is 0 because of 0 roles, one of the followings will catch it:
					if(!Uml::IsDerivedFrom(m_type, ::Uml::Uml::CompositionParentRole(comp.parentRole()).target())) {
						throw udm_exception("Invalid childrole specified");
					}
					if(!Uml::IsDerivedFrom(de.m_type,::Uml::Uml::CompositionChildRole(comp.childRole()).target())) {
						throw udm_exception("Invalid child specified");
					}
					// only gets here if comp was 0 beacause of multiple valid roles
					dom_element.setAttribute(DOMString("__child_as"), DOMString(GetANameFor(comp).c_str()));

				}
//#endif

				//we need to take care about ordering

					bool inserted = false;
					for(DOM_Node n = dom_element.getFirstChild(); n != (DOM_NullPtr *)NULL;n = n.getNextSibling())	
					{
						if( n.getNodeType() == DOM_Node::ELEMENT_NODE )
						{
							StrX name = n.getNodeName();

							
							char * child_type_name = new char[((string)((*i)->type().name())).size() + 1];
							strcpy(child_type_name, ((string)((*i)->type().name())).c_str());

							const char * curr_child_name = name.localForm();

							if (strcmp(child_type_name, curr_child_name) < 0)
							{
								dom_element.insertBefore(de.dom_element, n);
								inserted = true;
								delete child_type_name;
								break;
							}

							delete child_type_name;

						}
					}
					if (!inserted)
						dom_element.appendChild(de.dom_element);

			}

			//derived & instantiated objects
			set<Object> derived = this_o.derived();
			set<Object>::iterator d_i = derived.begin();
			while (d_i != derived.end())
			{
				//this is a derived object of this_o
				Object d_o = *d_i++;

				//inside will contain the corresponding(!!) derived children
				//found to be in the same derived tree with this_o. 

				//outside will contain the set of our(!!!) children which are outside
				//the derived tree that contains this_o, and they need to be added
				//as inherited children with archetype to d_o
				vector<ObjectImpl*> inside;

				set<Object>::iterator a_set_i = a_set.begin();
				while (a_set_i != a_set.end())
				{
					Object a_set_o = *a_set_i++;
					Object a_set_o_der = a_set_o.getDerivedObjectInPrimarilyDerivedBlock(d_o);
					if (a_set_o_der) inside.push_back(a_set_o_der.__impl()->clone());
					else 
					{
						//for objects in outside, we create corresponding objects
						inside.push_back(d_o.__impl()->createChild(role, a_set_o.type(), a_set_o.__impl(), true, false));

					}
				}

				vector<ObjectImpl*> existing;	//subtype may have existing extension children
				
				existing = d_o.__impl()->getChildren(role, NULL);
				inside.insert(inside.end(), existing.begin(), existing.end());




				//for objects in inside, we invoke a setChildren on der_o
				d_o.__impl()->setChildren(role, inside, false);

				//we have to release the previously cloned impls
				vector<ObjectImpl*>::iterator inside_i = inside.begin();
				while (inside_i != inside.end())
				{
					ObjectImpl* in_inside = *inside_i++;
					in_inside->release();
				}

				
			}

			set<Object> instances = this_o.instances();
			set<Object>::iterator i_i = instances.begin();
			while (i_i != instances.end())
			{
				//this is a derived object of this_o
				Object i_o = *i_i++;

				//inside will contain the corresponding(!!) derived children
				//found to be in the same derived tree with this_o. 

				//outside will contain the set of our(!!!) children which are outside
				//the derived tree that contains this_o, and they need to be added
				//as inherited children with archetype to d_o
				vector<ObjectImpl*> inside;

				set<Object>::iterator a_set_i = a_set.begin();
				while (a_set_i != a_set.end())
				{
					Object a_set_o = *a_set_i++;
					Object a_set_o_der = a_set_o.getInstantiatedObjectInPrimarilyDerivedBlock(i_o);
					if (a_set_o_der) inside.push_back(a_set_o_der.__impl()->clone());
					else 
					{
						//for objects in outside, we create corresponding objects
						inside.push_back(i_o.__impl()->createChild(role, a_set_o.type(), a_set_o.__impl(), true, false));

					}
				}

				//for objects in inside, we invoke a setChildren on der_o
				i_o.__impl()->setChildren(role, inside, false);

				//we have to release the previously cloned impls
				vector<ObjectImpl*>::iterator inside_i = inside.begin();
				while (inside_i != inside.end())
				{
					ObjectImpl* in_inside = *inside_i++;
					in_inside->release();
				}

				
			}
		}


		ObjectImpl *createChild(
			const ::Uml::Uml::CompositionChildRole &childrole,	
			const ::Uml::Uml::Class &meta, 
			const Udm::ObjectImpl* archetype = NULL, 
			const bool subtype = false,
			const bool real_archetype = true,
			const bool need_safetype = false) 
		{
				if (!archetype || (archetype && real_archetype))
				{
					//normal child or primarily derived object is going to be created
					//if I'm an instantiated object, this operation should be denied.
					if (isInstance())
						throw udm_exception("createChild: Instantiated objects can not be modified!");
				}

				string casestr = (string)meta.name() + "-s in " + (string)m_type.name() + "-s";
				::Uml::Uml::CompositionChildRole role = childrole;
			    if(!role) {
					::Uml::Uml::Composition comp = Uml::matchChildToParent(meta, m_type);
					if(!comp) throw  udm_exception("Role must be specified for " + casestr);
					role = comp.childRole();
				}
				if(!Uml::IsDerivedFrom(m_type, Uml::theOther(role).target())) {
					throw udm_exception("Invalid childrole specified for creating " + casestr);
				}
				if(!Uml::IsDerivedFrom(meta, role.target())) {
					throw udm_exception("Invalid child specified: " + casestr);
				}
				DOMString nodename = DOMString((string(::Uml::Uml::Namespace(meta.parent()).name()) + ':' +  string(meta.name())).c_str());
				DOMString ns_uri = DOMString((string(UDM_DOM_URI_PREFIX) + '/' +  string(::Uml::Uml::Namespace(meta.parent()).name())).c_str());
				DomObject *dep = 
					new DomObject(meta, dom_element.getOwnerDocument().createElementNS(ns_uri, nodename), mydn);
				//dep does not have at this moment an archetype!!!
				dep->setParent(this, Uml::theOther(role), false);

				
				
				if (archetype && archetype != &Udm::_null)
				{

					if (!real_archetype)
					{
						//record that it is not a real archetype
						//dep->dom_element.setAttribute(DOMString("real_archetype"), DOMString("false") );
						dep->dom_element.setAttribute(DOMString(_udm_dom_ia_real_archetype), DOMString("false") );
					}

					if (subtype)
					{
						//record that it is a subtype
						//dep->dom_element.setAttribute(DOMString("subtype"), DOMString("true") );
						dep->dom_element.setAttribute(DOMString(_udm_dom_ia_subtype), DOMString("true") );
					}

					//set the archetype/derived/instances relationship
					DOMString myid = dep->GetID();
					//DOMString tname = "archetype";
					DOMString tname = _udm_dom_ia_archetype;
					
					//DOMString oname = subtype ? "derived" : "instances";
					DOMString oname = subtype ? _udm_dom_ia_derived : _udm_dom_ia_instances;

					DomObject peer = *const_cast<DomObject *>((const DomObject*)archetype);
					DOMString peerid = peer.GetID();


					dep->dom_element.setAttribute(tname,peerid);

					DOMString pa = peer.dom_element.getAttribute(oname);
					if(DSFind(pa, myid) >= 0) 
						throw udm_exception("DOM error: Previous archetype/derived/instances relationship not removed completly!");

					if(pa == NULL) 
						peer.dom_element.setAttribute(oname, myid);
					else 
					{
						if(pa != (DOM_NullPtr *)NULL) 
						{
							pa.appendData(' ');
						}
						pa.appendData(myid);
						peer.dom_element.setAttribute(oname, pa);
					}	
					dep->CopyAttributesFromArchetype();

					//set up archetype relations for children, recursively

					static UdmUtil::copy_assoc_map cam; //this need to be the same object
														//through recursive calls

					//if real_archetype is true, it means that this call is not coming
					//recursively, so we clear this map
					if (real_archetype)
						cam.erase(cam.begin(), cam.end());
						



					set<::Uml::Uml::Class> ancestorClasses=Uml::AncestorClasses(archetype->type());

					for(set<::Uml::Uml::Class>::iterator p_currClass=ancestorClasses.begin(); 
					p_currClass!=ancestorClasses.end(); p_currClass++)
					{
						set<::Uml::Uml::CompositionParentRole> compParentRoles=p_currClass->parentRoles();
						for(set<::Uml::Uml::CompositionParentRole>::iterator p_currRole=compParentRoles.begin();
							p_currRole!=compParentRoles.end(); p_currRole++)
							{
								::Uml::Uml::Class childClass=Uml::theOther(*p_currRole).target();
								vector<ObjectImpl*>children= archetype->getChildren(Uml::theOther(*p_currRole),childClass);
								for(vector<ObjectImpl*>::iterator p_currImpl=children.begin();
									p_currImpl!=children.end();p_currImpl++)
									{
										ObjectImpl* p_srcChild=*p_currImpl;
										Udm::Object srcChild = p_srcChild;	//it will be released OK

										Object newchild = dep->createChild(Uml::theOther(*p_currRole), p_srcChild->type(), p_srcChild, subtype, false);

										UdmUtil::copy_assoc_map::value_type map_item(srcChild, newchild);
										cam.insert(map_item);


										Object srcChildrefersto = srcChild.getReferencedObject();
										if (srcChildrefersto)
										{
											UdmUtil::copy_assoc_map::value_type map_item1(srcChildrefersto, srcChildrefersto);
											cam.insert(map_item1);
										}
									}
							}
					}

					if(real_archetype)
					{
						//copy links from archetype
						vector<ObjectImpl*>children= archetype->getChildren(NULL, NULL);
						for(vector<ObjectImpl*>::iterator p_currImpl=children.begin();p_currImpl!=children.end();p_currImpl++)
						{
								ObjectImpl* p_srcChild=*p_currImpl;
								Udm::Object srcChild = p_srcChild;	//it will be released OK
								
								UdmUtil::copy_assoc_map::iterator cam_i = cam.find(srcChild);
								if (cam_i == cam.end()) 
									throw udm_exception("Internal UdmCopy error");
									
								Udm::Object dstChild = cam_i->second;		//this is a safe Object to Object copy
								
								//copy all links recursively for this child
								UdmUtil::reqCopyLinks(p_srcChild, dstChild.__impl(),cam, false);			//copy simple links first
								UdmUtil::reqCopyLinks(p_srcChild, dstChild.__impl(),cam, false, false);		//then assoc. class based ones

						}
					}
				}
				else
					//set the default attributes
					dep->setDefaultAttributes();

				//if this has subtypes/instances, 
				//a new child has to be added to those objects as well
				vector<ObjectImpl*> deriveds = getDerived();
				vector<ObjectImpl*>::iterator deriveds_i  = deriveds.begin();

				while ( deriveds_i != deriveds.end())
				{
					Object newObject = (*deriveds_i)->createChild(childrole, meta, dep, true, false);
					(*deriveds_i)->release(); //getDerived() clones it.
					deriveds_i ++;
				}

				vector<ObjectImpl*> instances = getInstances();
				vector<ObjectImpl*>::iterator instances_i  = instances.begin();
				while ( instances_i != instances.end())
				{
					Object newObject = (*instances_i)->createChild(childrole, meta, dep, false, false);
					(*instances_i)->release(); //getInstances() clones it.
					instances_i ++;
				}

				return dep;
		}

	// --- associations

	public:
		vector<ObjectImpl*> getAssociation(const ::Uml::Uml::AssociationRole &meta, int mode = Udm::TARGETFROMPEER) const 
		{
			vector<ObjectImpl*> ret;

			DOM_Document doc = dom_element.getOwnerDocument();

			string name = Uml::MakeRoleName(meta);
			DOMString followattr;

			if((::Uml::Uml::Class)((::Uml::Uml::Association)meta.parent()).assocClass()) {
				if(mode == Udm::TARGETFROMPEER) {
					followattr = (name + "_end_").c_str();
				}
				else if(mode == Udm::TARGETFROMCLASS) {
					name = name + "_end_";
				}
			}
			else {
				if(mode != Udm::TARGETFROMPEER) 
						throw udm_exception("Invalid access for non-class association role "+name);
			}

			// this must be an IDREF or IDREFS attribute
			DOMString a = dom_element.getAttribute(DOMString(name.c_str()));

			const XMLCh *i = a.rawBuffer();
			const XMLCh *end = i + a.length();

			for(;;)
			{
				// skip the white spaces
				while( i < end && *i == XMLCh(' ') )
					++i;

				if( i >= end )
					break;

				// find the end of the IDREF
				const XMLCh *p = i + 1;
				while( p < end && *p != XMLCh(' ') )
					++p;

				//DOM_Element e = doc.getElementById(DOMString(i, p-i));
				//if(e == NULL) 	
				DOM_Element e = ((DomDataNetwork*)mydn)->Search(doc, DOMString(i, p-i));

				// the ID must exists
				ASSERT( e != (DOM_NullPtr *)NULL );

				if(followattr != (DOM_NullPtr *)NULL) {
					DOMString a = e.getAttribute(followattr);
					if(a == NULL) throw udm_exception("Invalid assocClass, (missing _end_ attribute)");
					//DOM_Element ee = doc.getElementById(a);
					//if(ee == NULL) 	
					DOM_Element ee = ((DomDataNetwork*)mydn)->Search(doc, a);
					e = ee;
				}
				// the ID must exists
				ASSERT( e != (DOM_NullPtr *)NULL );

				// create the object
				ret.push_back( new DomObject(/*m_type.parent(), */ e, mydn) );

				i = p + 1;
			}
			
			return ret;
		}


		
		ObjectImpl * findInstanceAt(const DomObject * where)
		{
			vector<ObjectImpl*> instances = getInstances();
			vector<ObjectImpl*>::iterator i = instances.begin();
			ObjectImpl * found = NULL;

			while (i != instances.end())
			{
				DomObject * instance = (DomObject*)(*i);
				if (!(instance->hasRealArchetype()))
				{
					if (instance->dom_element.getParentNode() == where->dom_element) 
						found = instance->clone();
				}
				(*i)->release();
				i++;
			};
			if (!found) throw udm_exception("Could not find the corresponding subtype or instance in one of the parent's subtype/instance object.");
			return found;//it is cloned!
		}


		ObjectImpl * findSubtypeAt(const DomObject * where)
		{
			vector<ObjectImpl*> deriveds = getDerived();
			vector<ObjectImpl*>::iterator i = deriveds.begin();
			ObjectImpl * found = NULL;

			while (i != deriveds.end())
			{
				DomObject * derived = (DomObject*)(*i);
				if (!(derived->hasRealArchetype()))
				{
					if (derived->dom_element.getParentNode() == where->dom_element) 
						found = derived->clone();
				}
				(*i)->release();
				i++;
			};
			if (!found) throw udm_exception("Could not find the corresponding subtype or instance in one of the parent's subtype/instance object.");
			return found;//it is cloned!
		}

		ObjectImpl * findInstanceIn(const DomObject * where)
		{
			vector<ObjectImpl*> instances = getInstances();
			vector<ObjectImpl*>::iterator i = instances.begin();
			ObjectImpl * found = NULL;

			while (i != instances.end())
			{
				DomObject * instance = (DomObject*)(*i);
				if (!(instance->hasRealArchetype()))
				{
					DOM_Node parent = instance->dom_element.getParentNode();
			
					while ((!found) && (parent != (DOM_NullPtr *)NULL) && (parent.getNodeType() == DOM_Node::ELEMENT_NODE))
					{
			
						if (parent == where->dom_element) 
							found = instance->clone();

						parent = parent.getParentNode();
					}

				}
				(*i)->release();
				i++;
			};
			//if (!found) throw udm_exception("Could not find the corresponding subtype or instance in one of the parent's subtype/instance object.");
			return found;//it is cloned or NULL!
		}

		ObjectImpl * findSubtypeIn(const DomObject * where)
		{
			vector<ObjectImpl*> deriveds = getDerived();
			vector<ObjectImpl*>::iterator i = deriveds.begin();
			ObjectImpl * found = NULL;

			while (i != deriveds.end())
			{
				DomObject * derived = (DomObject*)(*i);
				if (!(derived->hasRealArchetype()))
				{
					DOM_Node parent = derived->dom_element.getParentNode();
			
					while ((!found) && (parent != (DOM_NullPtr *)NULL) && (parent.getNodeType() == DOM_Node::ELEMENT_NODE))
					{
			
						if (parent == where->dom_element) 
							found = derived->clone();

						parent = parent.getParentNode();
					}

				}
				(*i)->release();
				i++;
			};
			//if (!found) throw udm_exception("Could not find the corresponding subtype or instance in one of the parent's subtype/instance object.");
			return found;//it is cloned or NULL!
		}

		



//			A  ( ROLE = 'as' )  C      (ROLE = 'bs')     B
// attrs	bs		    as_end_/ \bs_end_                as

//          C.bs_end_ = bs = 'bs' in A and  'bs_end_' in C
//		    C.as_end_ = as = 'as' in B and  'as_end_' in C

		void setAssociation(const ::Uml::Uml::AssociationRole &role, const vector<ObjectImpl*> &nvect, int mode = Udm::TARGETFROMPEER, const bool direct = true)	
		{
			

			Udm::Object this_o = clone();	//most of the archetype/derived/instances related 
											//code will use TOMI Object level functions
											//so we use objects
			
			
			DOMString aa;
			DOMString myid = GetID();
			DOMString tname = Uml::MakeRoleName(role).c_str();
			DOMString oname = Uml::MakeRoleName(Uml::theOther(role)).c_str();

			

			set<Udm::Object> existing_ass;
			//geth the existing associations
			vector<ObjectImpl*> existing_associations = getAssociation(role, mode);
			for(vector<ObjectImpl*>::iterator ea_i = existing_associations.begin(); ea_i != existing_associations.end(); ea_i++)
			{
				existing_ass.insert(*ea_i);	//it was cloned in getAssociation, so it's safe!
			}


			bool no_change = false;
			if(existing_ass.size() == nvect.size())
			{
				no_change = true;
				
				for(vector<ObjectImpl*>::const_iterator i = nvect.begin(); i != nvect.end(); i++) 
				{
					Object new_ass = (*i)->clone();
					if (existing_ass.find(new_ass) == existing_ass.end())
					{
						no_change = false;
						break;
					}
					
				};

			};

			if (no_change) return;//all OK!, nothing changed.
			
			
			DomObject * do_parent = (DomObject*)getParent(NULL);
			if (do_parent && ((ObjectImpl*)do_parent != &Udm::_null))
			{
				if (do_parent->isInstance())
				{
					throw udm_exception("Links can not be added/removed to/from children of instance objects!");				
				}
			}





			if(mode == Udm::CLASSFROMTARGET) 
			{
				oname += "_end_";
			}
			if(mode == Udm::TARGETFROMCLASS) 
			{
				tname += "_end_";
			}
			
			DOMString origattr = dom_element.getAttribute(tname);


#ifdef DEBUG
char buf[100]; strcpy(buf, StrX(origattr).localForm());
#endif

		

			for(vector<ObjectImpl* >::const_iterator i = nvect.begin(); i != nvect.end(); i++) 
			{
				DomObject peer = *static_cast<DomObject *>(*i);
				DOMString peerid = peer.GetID();
				if(aa != (DOM_NullPtr *)NULL) 
				{
					aa.appendData(' ');
				}
				aa.appendData(peerid);
				DOMString pa = peer.dom_element.getAttribute(oname);
				if(DSFind(pa, myid) >= 0) 
				{
					int k = DSFind(origattr, peerid);
					if(k >= 0) origattr.deleteData(k,peerid.length()+1);
					continue;  // no change on peer side
				}
				if(pa == NULL) peer.dom_element.setAttribute(oname, myid);
				else if(Uml::theOther(role).max() == 1) 
				{
					DOM_Element currentpeer = dom_element.getOwnerDocument().getElementById(pa);
					if(currentpeer != (DOM_NullPtr *)NULL) 
					{
						DOMString cpa = currentpeer.getAttribute(tname);
						int k = DSFind(cpa, peerid);
						if(k >= 0) cpa.deleteData(k, peerid.length()+1);
						if(cpa == NULL || !cpa.length()) currentpeer.removeAttribute(tname);
						else currentpeer.setAttribute(tname, cpa);
					}
					peer.dom_element.setAttribute(oname, myid);
				}
				else 
				{
					if(pa != (DOM_NullPtr *)NULL) 
					{
						pa.appendData(' ');
					}
					pa.appendData(myid);
					peer.dom_element.setAttribute(oname, pa);
				}
			}
			if(aa == NULL) dom_element.removeAttribute(tname);
			else dom_element.setAttribute(tname, aa);

			{
				const XMLCh *i = origattr.rawBuffer();
				const XMLCh *end = i + origattr.length();

				for(;;)
				{
					// skip the white spaces
					while( i < end && *i == XMLCh(' ') )
						++i;

					if( i >= end )
						break;

					// find the end of the IDREF
					const XMLCh *p = i + 1;
					while( p < end && *p != XMLCh(' ') )
						++p;

					DOM_Document doc = dom_element.getOwnerDocument();
					//DOM_Element e = doc.getElementById(DOMString(i, p-i));
					//if(e == NULL) 	
					DOM_Element e = ((DomDataNetwork*)mydn)->Search(doc, DOMString(i, p-i));

					// the ID must exists
					ASSERT( e != (DOM_NullPtr *)NULL );

					DOMString cpa = e.getAttribute(oname);
					int k = DSFind(cpa, myid);
					if(k >= 0) cpa.deleteData(k, myid.length()+1);
					if(cpa == NULL || !cpa.length()) e.removeAttribute(oname);
					else e.setAttribute(oname, cpa);


					i = p + 1;
				}
			}

			
			
			
			
			//for all instance objects
			//here is the thing:
			// for each instantiated object of my parent(let it be 'a')
			//	1. find the corresponding (not primarily instantiated) object of me in a (as direct 1st level child)
			//  2. find the corresponding (not primarily instantiated) object for each peer (must be conatined somewhere in the archetype)
			//  3. create a new vector
			//  4. invoke recursively setAssociation() for the corresponding objects, direct will be false

			//check if we are setting up references
			if ((string)(role.name()) == "ref" && mode == Udm::TARGETFROMPEER && (nvect.size() == 1))
			{
				vector<ObjectImpl*> instances = getInstances();
				vector<ObjectImpl*>::iterator instances_i = instances.begin();
				while (instances_i != instances.end())
				{
					(*instances_i)->setAssociation(role, nvect,mode, false);
					delete *instances_i;
					instances_i++;
				}


				vector<ObjectImpl*> deriveds = getDerived();
				vector<ObjectImpl*>::iterator deriveds_i = deriveds.begin();
				while (deriveds_i  != deriveds.end())
				{
					(*deriveds_i )->setAssociation(role, nvect,mode, false);
					delete *deriveds_i ;
					deriveds_i ++;
				}


				return; // no need for the rest ;)
			}
		
			

			if (do_parent && ((ObjectImpl*)do_parent != &Udm::_null))
			{
				vector<ObjectImpl*>::iterator oset_i;

				vector<ObjectImpl*> instances = do_parent->getInstances();
				oset_i = instances.begin();
				while (oset_i != instances.end())
				{
					
					//Udm::Object this_o_inst = this_o.FindCorrespondingObjectInInstances((*oset_i)->clone(), false);
					Udm::Object this_o_inst = findInstanceAt((DomObject*)(*oset_i));
					
					set<Object> new_vect;		//this will contain the vector of corresponding objects
					for(vector<ObjectImpl* >::const_iterator k = nvect.begin(); k != nvect.end(); k++) 
					{
						DomObject peer = *static_cast<DomObject *>(*k);
						Udm::Object peer_o_inst = peer.findInstanceIn((DomObject*)(*oset_i));
						if (peer_o_inst) new_vect.insert(peer_o_inst);
					}

					set<Object> existing_corresp;//this really needs to be a set
					for(set<Object>::iterator kk = existing_ass.begin(); kk != existing_ass.end(); kk++)
						existing_corresp.insert(kk->FindCorrespondingObjectInInstancesTree(*oset_i, false));
					
					//get the current associations for this_o_inst
					vector<ObjectImpl*> this_o_inst_curr_ass = this_o_inst.__impl()->getAssociation(role, mode);

					//basically all objects corresponding to nvect objects should be set in the derived objects
					// plus, all current associations which are not in the set of corresponding objects of existing peers
					for(vector<ObjectImpl* >::const_iterator kkk = this_o_inst_curr_ass.begin(); kkk != this_o_inst_curr_ass.end(); kkk++) 
					{
						Udm::Object toi_ca_o(*kkk);			//get association clones it
						if (existing_corresp.find(toi_ca_o) == existing_corresp.end())
							new_vect.insert(toi_ca_o);		//no problem if it's already there
					}

					//create the new vector
					vector<ObjectImpl *> new_vector;
					for(set<Object>::iterator kkkk = new_vect.begin(); kkkk != new_vect.end(); kkkk++)
					{
						new_vector.push_back(kkkk->__impl());
					}

					//set the associations (recurisevly)
					//cout << "*";
					this_o_inst.__impl()->setAssociation(role, new_vector, mode, false);
							
					(*oset_i)->release();//getInstances() clones it
					oset_i++;
				
				}
			

				


				//for all derived objects
				//here is the thing:
				// for each derived object of my parent (a)
				//	1. find the corresponding (not primarily instantiated) object of me in a (as direct 1st level child)
				//  2. find the corresponding (not primarily instantiated) object for each peer (must be conatined somewhere in the archetype)
				//  3. create a new vector
				//  4. get the existing peers of the corresponding objects
				//  5. somehow merge the two vectors in a set
				//	6. invoke recursively setAssociation() for the corresponding objects, direct will be false
				
				vector<ObjectImpl*> deriveds = do_parent->getDerived();
				oset_i = deriveds.begin();
				while (oset_i != deriveds.end())
				{
					//Udm::Object this_o_inst = this_o.FindCorrespondingObjectInSubtypes((*oset_i)->clone(), false);
					Udm::Object this_o_inst = findSubtypeAt((DomObject*)(*oset_i));
					
					set<Object> new_vect;		//this will contain the vector of corresponding objects
					for(vector<ObjectImpl* >::const_iterator k = nvect.begin(); k != nvect.end(); k++) 
					{
						DomObject peer = *static_cast<DomObject *>(*k);
						Udm::Object peer_o_inst = peer.findInstanceIn((DomObject*)(*oset_i));
						if (peer_o_inst)new_vect.insert(peer_o_inst);
					}

					set<Object> existing_corresp;
					for(set<Object>::iterator kk = existing_ass.begin(); kk != existing_ass.end(); kk++)
						existing_corresp.insert(kk->FindCorrespondingObjectInSubtypesTree(*oset_i, false));
					
					//get the current associations for this_o_inst
					vector<ObjectImpl*> this_o_inst_curr_ass = this_o_inst.__impl()->getAssociation(role, mode);

					//basically all objects corresponding to nvect objects should be set in the derived objects
					// plus, all current associations which are not in the set of corresponding objects of existing peers
					for(vector<ObjectImpl*>::const_iterator kkk = this_o_inst_curr_ass.begin(); kkk != this_o_inst_curr_ass.end(); kkk++) 
					{
						Udm::Object toi_ca_o(*kkk);			//get association clones it
						if (existing_corresp.find(toi_ca_o) == existing_corresp.end())
							new_vect.insert(toi_ca_o);		//no problem if it's already there
					}

					//create the new vector
					vector<ObjectImpl *> new_vector;
					for(set<Object>::iterator kkkk = new_vect.begin(); kkkk != new_vect.end(); kkkk++)
					{
						new_vector.push_back(kkkk->__impl());
					}

					//set the associations (recurisevly)
					//cout << "=";
					this_o_inst.__impl()->setAssociation(role, new_vector, mode, false);
							
					(*oset_i)->release();//getDerived() clones it.
					oset_i++;
				
				}

				delete do_parent;
			}		
		}

		vector<ObjectImpl*> getDerived() const
		{
			vector<ObjectImpl*> ret;
			
			// this must be an IDREF or IDREFS attribute
			//DOMString a = dom_element.getAttribute("derived");
			DOMString a = dom_element.getAttribute(_udm_dom_ia_derived);
			DOM_Document doc = dom_element.getOwnerDocument();

			const XMLCh *i = a.rawBuffer();
			const XMLCh *end = i + a.length();

			for(;;)
			{
				// skip the white spaces
				while( i < end && *i == XMLCh(' ') )
					++i;

				if( i >= end )
					break;

				// find the end of the IDREF
				const XMLCh *p = i + 1;
				while( p < end && *p != XMLCh(' ') )
					++p;

				DOMString idref(i, p-i);

				DOM_Element e;
				//DOM_Element e = doc.getElementById(DOMString(i, p-i));
				//if(e == NULL) 	
				e = ((DomDataNetwork*)mydn)->Search(doc, idref);

				// the ID must exists
				ASSERT( e != (DOM_NullPtr *)NULL );

				// create the object
				ret.push_back( new DomObject(/*m_type.parent(), */e, mydn) );

				i = p + 1;
			}
			return ret;
		};
		vector<ObjectImpl*> getInstances() const
		{
			vector<ObjectImpl*> ret;
			// this must be an IDREF or IDREFS attribute
			//DOMString a = dom_element.getAttribute("instances");
			DOMString a = dom_element.getAttribute(_udm_dom_ia_instances);
			DOM_Document doc = dom_element.getOwnerDocument();


			const XMLCh *i = a.rawBuffer();
			const XMLCh *end = i + a.length();

			for(;;)
			{
				// skip the white spaces
				while( i < end && *i == XMLCh(' ') )
					++i;	

				if( i >= end )
					break;

				// find the end of the IDREF
				const XMLCh *p = i + 1;
				while( p < end && *p != XMLCh(' ') )
					++p;

				DOMString idref(i, p-i);
				DOM_Element e;

				//e = doc.getElementById(idref);
				//if(e == NULL) 	
				e = ((DomDataNetwork*)mydn)->Search(doc, idref);

				// the ID must exists
				ASSERT( e != (DOM_NullPtr *)NULL );

				// create the object
				ret.push_back( new DomObject(/*m_type.parent(), */e, mydn) );

				i = p + 1;
			}
			
			return ret;

		};
		ObjectImpl* getArchetype() const
		{
	
			// this must be an IDREF or IDREFS attribute
			//DOMString a = dom_element.getAttribute("archetype");
			DOMString a = dom_element.getAttribute(_udm_dom_ia_archetype);

			
			DOM_Document doc = dom_element.getOwnerDocument();

			if(a == (DOM_NullPtr *)NULL) return &Udm::_null;

			DOM_Element e;
			//e = doc.getElementById(a);
			//if(e == NULL) 	
				e = ((DomDataNetwork*)mydn)->Search(doc, a);

			// the ID must exists
			ASSERT( e != (DOM_NullPtr *)NULL );

			// create the object
			return new DomObject(/*m_type.parent(), */e, mydn);
	
		};

		bool hasRealArchetype() const
		{
			//DOMString atype = dom_element.getAttribute("archetype");
			DOMString atype = dom_element.getAttribute(_udm_dom_ia_archetype);
			
			if (atype.length())
			{
				//DOMString a = dom_element.getAttribute("real_archetype");
				DOMString a = dom_element.getAttribute(_udm_dom_ia_real_archetype);

				if(!a.length()) return true;		 // default is true!
				return a.charAt(0) == XMLCh('t');	 // true
			}
			throw udm_exception("hasRealArchetype() can be evaluated only on instantiated  or derived objects, or (inherited)children of derived objects.");
			return false;							//it has no archetype
		};

		virtual ~DomObject(){};

	};

//	unsigned long DomObject::idcount = time(NULL);
	DomObject::uniqueId_type DomObject::static_orderdata = 1;

// --------------------------- parser

	class MobiesErrorHandler : public ErrorHandler
	{
	public:
		virtual void  warning (const SAXParseException& exception) { }
		virtual void  error (const SAXParseException& exception) { fatalError(exception); }
 
		virtual void  fatalError (const SAXParseException& exception)
		{
			char buffer[34];

			string description = "Error at file '";
			description += StrX(exception.getSystemId()).localForm();

			description += "', line ";
			//_itoa(exception.getLineNumber(), buffer, 10);
			sprintf(buffer,"%d", (unsigned int)exception.getLineNumber());
			description += buffer;

			description += ", column ";
			//_itoa(exception.getColumnNumber(), buffer, 10);
			sprintf(buffer,"%d", (unsigned int)exception.getColumnNumber());
			description += buffer;

			description += ". Message: ";
			description += StrX(exception.getMessage()).localForm();

			throw udm_exception(description);
		}

		virtual void  resetErrors () { }
	};

	static class strstorage {
		char *p;
	public:
		strstorage() { p = NULL; };
		~strstorage() { if(p) free(p); }
		typedef const char *charp;
		charp load(const char *str) {
			char *pt = str ? strdup(str) : NULL;
			if(p) free(p);
			return p = pt;
		}
		operator charp() { return p; }
	} pp;

	UDM_DLL DomDataNetwork::DomDataNetwork(const Udm::UdmDiagram &metainfo, Udm::UdmProject* project) :
	Udm::DataNetwork(metainfo, project)  
	{

		str_based = false;
		str = "";
		
		DDNMap.push_front(this);
		saveondestroy = false;
		rootobject = NULL;
		/*if(!LoadLibrary("..\\lib\\xerces-c_1_2")) MessageBox(NULL, "Baj van", "Load lib", 0); */

		//create a cache for meta-classes 
		set<::Uml::Uml::Namespace> meta_namespaces= metaroot.dgr->namespaces();
		
		for (set<::Uml::Uml::Namespace>::iterator mni = meta_namespaces.begin(); mni != meta_namespaces.end(); mni++)
		{
			set<::Uml::Uml::Class> meta_classes = mni->classes();
			for (set<::Uml::Uml::Class>::iterator mci = meta_classes.begin(); mci != meta_classes.end(); mci++)
			{
				//namespace + ":" + classname
				string key = (string)(mni->name()) + ":" + (string)(mci->name());

				pair<string, ::Uml::Uml::Class> mcc_item(key, *mci);
				pair<map<string,  ::Uml::Uml::Class>::iterator, bool> ins_res = meta_class_cache.insert(mcc_item);
				if (!ins_res.second)
					throw udm_exception("Insert failed when creating meta classes by name map!");

			}
		}
	}


	void DomDataNetwork::DoMapping(const DOM_Element &e, long id,  bool force)
	{
			IdToDomElementMapItem item_to_store(id, e);
			pair<IdToDomElementMap::iterator, bool> ins_res;
			ins_res = DomElements.insert(item_to_store);
			ASSERT( (!force) || (force && ins_res.second) );

	};


	DOM_Element DomDataNetwork::Search(const DOM_Node &d, const DOMString &str) 
	{
	
		
		IdToDomElementMap::iterator i = DomElements.find(GetLongID(str));	
		if (i != DomElements.end() ) return (*i).second;
		return DOM_Element();
		
	};//eo Search()



	UDM_DLL DomDataNetwork::~DomDataNetwork() { 

		TRY_XML_EXCEPTION

		if(!rootobject)
		{
			//somebody might have already close it with either CloseUpdate or CloseNoUpdate ! 
			// you have to remove from the map in this cases as well
			// i guess it's still imperative that it should be in the map.
			ddnmap::iterator ff;
			for(ff = DDNMap.begin(); ff != DDNMap.end(); ff++) 
			{
				if(*ff == this) break;
			}
			
			if(ff == DDNMap.end()) throw udm_exception("Corrupt DOM DN map");
			DDNMap.erase(ff);

			return;
		}

		if(saveondestroy) CloseWithUpdate();
		rootobject = NULL;
		ddnmap::iterator ff ;
		for(ff = DDNMap.begin(); ff != DDNMap.end(); ff++) {
			if(*ff == this) break;
		}

		if(ff == DDNMap.end()) throw udm_exception("Corrupt DOM DN map");
		DDNMap.erase(ff);

		CATCH_XML_EXCEPTION("DomDataNetwork::~DataNetwork()")
	}


	class MyEntityResolver : public EntityResolver 
	{
		bool _resolved;
		bool vinfo;
		string name;
		string version;
		
		
		bool _use_str_xsd;

	

		bool CheckForVersionInfo(const InputSource* is, const string systemid)
		{
			if (!is) return false;
			/*
				<?udm interface="UdmProject" version="1.00"?>
			*/

			DOMParser parser;

			parser.setValidationScheme(DOMParser::Val_Never);

			try 
			{
				parser.parse(*is);
			}

			catch(const udm_exception& toCatch)
			{
				string description = "Error during parsing DTD/XSD: '";
				description += systemid;
				description += "'. Exception message is: ";
				description += toCatch.what();

				throw udm_exception(description);

			}

			XMLCh udm[]={ chLatin_u, chLatin_d, chLatin_m, chNull };
			DOM_Document pDoc=parser.getDocument();
			DOM_Node pNode=pDoc.getFirstChild();
			while(!pNode.isNull())
			{
				if(pNode.getNodeType()==DOM_Node::PROCESSING_INSTRUCTION_NODE)
				{

					// do what you want
					DOM_ProcessingInstruction * DPI = static_cast<DOM_ProcessingInstruction*>(&pNode);
					if (DPI->getTarget().equals(udm))
					{
						const char * interface_att_name="interface=\"";
						const char * version_att_name="version=\"";

						string version_string = DPI->getData().transcode();
						string vs_1 = version_string.substr(version_string.find(interface_att_name) + strlen(interface_att_name), string::npos);
						name = vs_1.substr(0, vs_1.find('"'));
						string vs_2 = version_string.substr(version_string.find(version_att_name) + strlen(version_att_name), string::npos);
						version = vs_2.substr(0, vs_2.find('"'));
						
						if (name.size() && version.size()) vinfo = true;
						return true;

					}
				}
				pNode=pNode.getNextSibling();
			}
			
			return false;
		};
	public:
		void clear()
		{
			_resolved = false;
			vinfo = false;
		};
		
		bool resolved()
		{
			return _resolved;
		};
		bool hasVersionInfo()
		{
			return vinfo;
		};

		string getName()
		{
			return name;
		};

		string getVersion()
		{
			return version;
		};

		void UseStrXsd()
		{
			_use_str_xsd = true;
		};

		void DontUseStrXsd()
		{
			_use_str_xsd = false;

		};

	  virtual InputSource* resolveEntity(const   XMLCh* const    publicId, const XMLCh* const systemId) 
	  {
		  string sysid = StrX(systemId).localForm();
		  InputSource* is = NULL;
		 
		  if (_use_str_xsd)
		  {
			  //look up in the string map.
			  str_xsd_storage::str_str_map::iterator it_sxc = str_xsd_storage::static_xsd_container.find(sysid);
			  if (it_sxc != str_xsd_storage::static_xsd_container.end())
			  {
				  const string & xsd_str = *(it_sxc->second);
				  is =  new MemBufInputSource((const unsigned char * )xsd_str.c_str(), xsd_str.size(), "MBIS");
			  }

			  else return HandlerBase().resolveEntity(publicId, systemId); 

		
		  }
		  else
		  {
			//removed the hacks from  here....
			//no automagic things: just current directory, PATH, and URI 

		
		
#ifdef _WIN32
			
			//search in resources
			//resource checking is done only when  DTDPath is not set
			//(not to confuse Udm.exe when the -d is provided
			//and probably XMI input is supplied)
			if (DomDataNetwork::DTDPath.empty())
			{
				HANDLE myProcId = GetCurrentProcess();
				HMODULE lpModules[100];
				HMODULE resFound = NULL;
				DWORD needed;

				//try to bring in psapi.dll
				HMODULE psmod = LoadLibrary("psapi.dll");

				HRSRC resource = NULL;

				if (psmod)
				{
					typedef BOOL (__stdcall *fp )(HANDLE, HMODULE*, DWORD, LPDWORD);

					fp fnctptr = (fp)GetProcAddress(psmod, "EnumProcessModules");
					if (fnctptr)
					{
						if ((*fnctptr)(myProcId, lpModules, 100*sizeof(HMODULE), &needed))
						{
							DWORD module_index = 0;
							while (!resource && (module_index < needed/sizeof(HMODULE)))
							{
								resource = FindResource(lpModules[module_index], sysid.c_str(), "XSD");
								if (resource) resFound = lpModules[module_index];
								module_index++;
							}
						}
					}
				}
				else
					resource = FindResource(NULL, sysid.c_str(), "XSD");
				if (resource)
				{

					DWORD size = SizeofResource(resFound, resource);
					HGLOBAL hResData = LoadResource(resFound, resource);
					if (hResData)
					{
						//a static map which will prevent locking the same resource twice
						static map<HGLOBAL, const unsigned char *> resBufferCache;
						map<HGLOBAL, const unsigned char *>::iterator i = resBufferCache.find(hResData);
						if (i != resBufferCache.end())
							//there is a 4th parameter which could be set to true 
							// - in that case the constructor would not adopt the buffer
							// Unfortunatly that caused an asertion when running Udm.exe in debug
							// mode at the point when the parser deleted the InputSource
							// new object is created on the heap, but the parser is responsible 
							//to clean up the returned object on the heap
							return new MemBufInputSource(i->second, size, "MBIS"); 

						//we assume 1byte/char encoding in the resource
						//MSDN: buffer returned by LockResource will be freed when the process exits

						const unsigned char * p = (const unsigned char *)LockResource(hResData);
						pair<HGLOBAL, const unsigned char *> item(hResData,p);
						resBufferCache.insert(item);

						//there is a 4th parameter which could be set to true 
						// - in that case the constructor would not adopt the buffer
						// Unfortunatly that caused an asertion when running Udm.exe in debug
						// mode at the point when the parser deleted the InputSource
						// new object is created on the heap, but the parser is responsible 
						//to clean up the returned object on the heap
						is =  new MemBufInputSource(p, size, "MBIS");
					}
				}
			}
#endif

			string filename = DomDataNetwork::FindFile(sysid);

			if(!filename.empty()) 
				is = new LocalFileInputSource(DOMString(filename.c_str()).rawBuffer());

			if (!is) 
				return HandlerBase().resolveEntity(publicId, systemId);
		  }

		//check vor version Info
		vinfo = CheckForVersionInfo(is,sysid);
		return is;
	  }
	};

	//ugly but necesarry
	UDM_DLL str_xsd_storage::str_str_map str_xsd_storage::static_xsd_container;
	

	UDM_DLL void DomDataNetwork::MapExistingIDs(DOM_Node &d) 
	{
			TRY_XML_EXCEPTION

		 DOM_Node child = d.getFirstChild();
         while (child != 0) 
		 {
			 if(child.getNodeType() == DOM_Node::ELEMENT_NODE) 
			 {
				
				 DOM_Element dd = (DOM_Element&)child;	
				 DOMString a = dd.getAttribute(DOMString("_id"));
				if (a != 0)
				{
					//convert to long
					long id = GetLongID(a);
					//check if a found id is higher then our id
					//so that newly created elements in this 
					//DOM would get a proper ID.
					if (id)
					{
						//id could be zero
						if (id > DomObject::static_orderdata)
							DomObject::static_orderdata = id;

						//insert in the map so we could find it
						//later on
						IdToDomElementMapItem item_to_store(id, dd);
						pair<IdToDomElementMap::iterator, bool> ins_res;
						ins_res = DomElements.insert(item_to_store);
						ASSERT(ins_res.second);

					}//eo if (id)
				}//eo if (a != 0)
				MapExistingIDs(child);
			 }//eo if(child.getNodeType() == DOM_Node::ELEMENT_NODE) 
			 child = child.getNextSibling();
		}//eo while (child != 0)
			
			CATCH_XML_EXCEPTION("DomDataNetwork::MapExistingIDs()");

	}//eo void DomDataNetwork::MapExistingIDs(DOM_Node &d) 


	UDM_DLL void DomDataNetwork::OpenExistingFromString(string &str, 
									const string &metalocator, 
									enum Udm::BackendSemantics sem)
	{
		TRY_XML_EXCEPTION

		str_based = true;

		MyEntityResolver resolver;
		resolver.clear();
		resolver.UseStrXsd();
		
		ASSERT( str.length());
		DOMParser parser;
		
		parser.setValidationScheme(DOMParser::Val_Always);
		//XSD
		//parser.setDoNamespaces(false);
		parser.setDoNamespaces(true);
		parser.setDoSchema(true);
		//eo XSD

		parser.setExpandEntityReferences(true);
		parser.setIncludeIgnorableWhitespace(false);
		parser.setEntityResolver(&resolver);

		MobiesErrorHandler errhand;
		parser.setErrorHandler(&errhand);
	
		::Uml::Uml::Diagram dgr = GetRootMeta();
		try
		{
			const InputSource * is = new MemBufInputSource( (const unsigned char *)str.c_str(), str.size(), "MBIS");
			parser.parse(*is);
			delete is;
		}
		/*
			Our MobiesErrorHandler throws udm_exceptions...
		*/
		catch(const udm_exception& toCatch)
		{
			//parsing failed
			//maybe it's the wrong version ?
			//we check this first, we report version mismatch error, if there is
			//version checking
			if (resolver.hasVersionInfo())
			{
				if (resolver.getName() != (string)dgr.name()) 
				{
					string err = string("Parsing failed, meta name information mismatch! DTD/XSD: ") + resolver.getName() + ", meta: " + (string)dgr.name();
					throw udm_exception(err);
				}
				if (resolver.getVersion() != (string)dgr.version()) 
				{
					string err = string("Parsing failed, meta version information mismatch! DTD/XSD: ") + resolver.getVersion() + ", meta: " + (string)dgr.version();
					throw udm_exception(err);
				}
			}
			//end of version checking

			//if we got here, the version info seems to be OK, but however the document still can not be parsed
			
			string description = "Error during parsing input string. ";
			description += "'. Exception message is: ";
			description += toCatch.what();

			throw udm_exception(description);
		}

		DOM_Element root = parser.getDocument().getDocumentElement();
		ASSERT( root != (DOM_NullPtr *)NULL );

		//parser.getDocument().setUserData((void *)pp.load(systemname.c_str()));

	
		rootobject = new DomObject(/*dgr, */root, this);
		//version checking
		if (resolver.hasVersionInfo())
		{
			if (resolver.getName() != (string)dgr.name()) 
			{
				string err = string("Meta name information mismatch! DTD/XSD: ") + resolver.getName() + ", meta: " + (string)dgr.name();
				throw udm_exception(err);
			}
			if (resolver.getVersion() != (string)dgr.version()) 
			{
				string err = string("Meta version information mismatch! DTD/XSD: ") + resolver.getVersion() + ", meta: " + (string)dgr.version();
				throw udm_exception(err);
			}
		
		
		}
		//end of version checking

		saveondestroy = (sem != Udm::CHANGES_LOST_DEFAULT);
		
		//empty the map of elements, one might open an existing
		//diagram on an already used diagram
		if (!DomElements.empty())
			DomElements.erase(DomElements.begin(), DomElements.end());
		//get all the id's
		//this must be recursive, but, at least, it's run only once/UDM session
		MapExistingIDs(root);


		
		this->str.erase();
		this->str = str;

		CATCH_XML_EXCEPTION("DomDataNetwork::OpenExistingFromString()");
	};

	UDM_DLL void DomDataNetwork::OpenExisting(const string &systemname, 
									const string &metalocator, 
									enum Udm::BackendSemantics sem) 
	{

		TRY_XML_EXCEPTION

		MyEntityResolver resolver;
		resolver.clear();
		resolver.DontUseStrXsd();

		ASSERT( systemname.length());

		savesystemname = systemname;
		if(!strnicmp(savesystemname.c_str(),"DOM:", 4)) savesystemname.erase(0,4);
		DOMParser parser;

		parser.setValidationScheme(DOMParser::Val_Always);
		//XSD
		//parser.setDoNamespaces(false);
		parser.setDoNamespaces(true);
		parser.setDoSchema(true);
		//eo XSD

		parser.setExpandEntityReferences(true);
		parser.setIncludeIgnorableWhitespace(false);
		parser.setEntityResolver(&resolver);

		MobiesErrorHandler errhand;
		parser.setErrorHandler(&errhand);

		::Uml::Uml::Diagram dgr = GetRootMeta();
		try
		{
			parser.parse(savesystemname.c_str());
		}
		/*
			Our MobiesErrorHandler throws udm_exceptions...
		*/
		catch(const udm_exception& toCatch)
		{
			//parsing failed
			//maybe it's the wrong version ?
			//we check this first, we report version mismatch error, if there is
			//version checking
			if (resolver.hasVersionInfo())
			{
				if (resolver.getName() != (string)dgr.name()) 
				{
					string err = string("Parsing failed, meta name information mismatch! DTD/XSD: ") + resolver.getName() + ", meta: " + (string)dgr.name();
					throw udm_exception(err);
				}
				if (resolver.getVersion() != (string)dgr.version()) 
				{
					string err = string("Parsing failed, meta version information mismatch! DTD/XSD: ") + resolver.getVersion() + ", meta: " + (string)dgr.version();
					throw udm_exception(err);
				}
			}
			//end of version checking

			//if we got here, the version info seems to be OK, but however the document still can not be parsed
			
			string description = "Error during parsing: '";
			description += systemname;
			description += "'. Exception message is: ";
			description += toCatch.what();

			throw udm_exception(description);
		}

		DOM_Element root = parser.getDocument().getDocumentElement();
		ASSERT( root != (DOM_NullPtr *)NULL );

		parser.getDocument().setUserData((void *)pp.load(systemname.c_str()));

	
		rootobject = new DomObject(/*dgr,*/ root, this);
		//version checking
		if (resolver.hasVersionInfo())
		{
			if (resolver.getName() != (string)dgr.name()) 
			{
				string err = string("Meta name information mismatch! DTD/XSD: ") + resolver.getName() + ", meta: " + (string)dgr.name();
				throw udm_exception(err);
			}
			if (resolver.getVersion() != (string)dgr.version()) 
			{
				string err = string("Meta version information mismatch! DTD/XSD: ") + resolver.getVersion() + ", meta: " + (string)dgr.version();
				throw udm_exception(err);
			}
		
		
		}
		//end of version checking

		saveondestroy = (sem != Udm::CHANGES_LOST_DEFAULT);
		
		//empty the map of elements, one might open an existing
		//diagram on an already used diagram
		if (!DomElements.empty())
			DomElements.erase(DomElements.begin(), DomElements.end());
		//get all the id's
		//this must be recursive, but, at least, it's run only once/UDM session
		MapExistingIDs(root);

		CATCH_XML_EXCEPTION("DomDataNetwork::OpenExisting()");

	}

	UDM_DLL void DomDataNetwork::CreateNewToString(const string &metalocator, const ::Uml::Uml::Class &rootclass, 
									enum Udm::BackendSemantics sem )
	{
		CreateNew("",metalocator, rootclass,sem);
		str_based = true;
		str.erase();
	};

	UDM_DLL const string& DomDataNetwork::Str()
	{
		return str;
	};



	UDM_DLL void DomDataNetwork::CreateNew(const string &systemname, 
									const string &metalocator, const ::Uml::Uml::Class &rootclass, 
									enum Udm::BackendSemantics sem) 
	{

#ifdef _WIN32
		static const char path_dlim =';';
		static const char path_hier ='\\';
#else
		static const char path_dlim =':';
		static const char path_hier ='/';
#endif


		TRY_XML_EXCEPTION


			bool force_dtd = false; //default is xsd
			if (metalocator.size() > 4)
			{
				if (metalocator.find('.') != metalocator.npos)
				{
					string extension = metalocator.substr(metalocator.find('.')+1, metalocator.npos);
					force_dtd = (strncmp(extension.c_str(), "dtd", 3) == 0);
				}
			}
			

			ASSERT( metalocator.length());
			savesystemname = systemname;
			if(!strnicmp(savesystemname.c_str(),"DOM:", 4)) savesystemname.erase(0,4);

			DOMString ml(metalocator.c_str());
			MyEntityResolver mr;
			
			if (str_based) mr.UseStrXsd();
			else mr.DontUseStrXsd();

		

			/*
				This hack is unfortunatly needed because of GME & SmartDataNetwork.
				For ex., LampDiagram can be used as metalocator in SmartDataNetworks. 
				
				//XSD
				That *must* identify both the MGA paradigm and the XML dtd. So we look it up first
				and if it's not succesfull we  try again with .dtd appended. 

				That *must* identify both the MGA paradigm and the XML Schema or DTD.
				So we look it up first and if it's not succesfull we try again with
				.xsd or .dtd appended.


			*/
				
			InputSource *pp = mr.resolveEntity(ml.rawBuffer(),ml.rawBuffer());


			//XSD
			/*
			if(!pp &&
					(metalocator.size() < 4 || 
					strnicmp(metalocator.c_str() + metalocator.size() - 4, ".dtd",4) != 0)) 
			{
					DOMString ml2((metalocator + string(".dtd")).c_str());
					pp = mr.resolveEntity(ml2.rawBuffer(),ml2.rawBuffer());
				
					ml = ml2;	
			}
			*/

	
			//XSD
			string xsd_file = metalocator;
			if(!pp)
			{
				string mlExtension = xsd_file.size() >= 4 ?	xsd_file.substr(xsd_file.size() - 4, 4) : "";
				if(strnicmp(mlExtension.c_str(), ".xsd", 4) != 0 )
				{
					xsd_file += ".xsd";
					DOMString ml2(xsd_file.c_str());
					pp = mr.resolveEntity(ml2.rawBuffer(), ml2.rawBuffer());
		
				}
			}


			if(!pp) 
			{
				string err;
				err = "Metalocator could not be resolved: ";
				err += metalocator;
				err += ". Make sure that it's a valid FILE either in the current directory, or in PATH, or it's a valid URI, and it identifies a valid DTD.";

				throw udm_exception(err);
			}	
			
			delete pp;			//it surely does exist ;-)
			
			DOM_DOMImplementation impl;
			DOM_Document doc;
			DOM_DocumentType dtd;

			string rootname = rootclass.name();
			string ns_name = ::Uml::Uml::Namespace(rootclass.parent()).name();
			string qualified_name = ns_name + ":" + rootname;
			string ns_uri = string(UDM_DOM_URI_PREFIX) + ns_name;

			//XSD
			//dtd= impl.createDocumentType(DOMString(rootname.c_str()),DOMString(), ml);

			//XSD
			if(force_dtd)  // XXX: should be: if use DTD
			{
				dtd = impl.createDocumentType(DOMString(rootname.c_str()),DOMString(), ml);
			}
			else
			{
				dtd = (DOM_NullPtr *)NULL;
			}





			doc = impl.createDocument(
					ns_uri.c_str(),                    // root element namespace URI.
					qualified_name.c_str(),            // root element name
					dtd);  // document type object (DTD).
		
			

			DOM_Element rootElem = doc.getDocumentElement();
			ASSERT( rootElem != (DOM_NullPtr *)NULL );

			rootobject = new DomObject(/*GetRootMeta(),*/ rootElem, this);
			
			//set the default attributes
			rootobject.__impl()->setDefaultAttributes();

			//XSD
			if(!force_dtd)  // XXX: should be: if use XML Schema
			{
				std::string fname_pathless;
				if (xsd_file.rfind(path_hier) != std::string::npos)
					fname_pathless = xsd_file.substr(xsd_file.rfind(path_hier) + 1, std::string::npos);
				else 
					fname_pathless = xsd_file;

				// set XML Schema
				DOM_Element de = static_cast<DomObject *>(GetRootObject().__impl())->dom_element;
				
				de.setAttributeNS(DOMString("http://www.w3.org/2000/xmlns/"),
					DOMString((string("xmlns:") + ns_name).c_str()), DOMString(ns_uri.c_str()));
				
				de.setAttributeNS(DOMString("http://www.w3.org/2000/xmlns/"),
						  DOMString("xmlns:xsi"), DOMString("http://www.w3.org/2001/XMLSchema-instance"));
				de.setAttributeNS(DOMString("http://www.w3.org/2001/XMLSchema-instance"),
						  DOMString("xsi:schemaLocation"), DOMString((ns_uri + ' ' + fname_pathless).c_str()));
			}



			saveondestroy = (sem != Udm::CHANGES_LOST_DEFAULT);

		

		
		CATCH_XML_EXCEPTION("DomDataNetwork::CreateNew()") 
		
	}

	UDM_DLL void DomDataNetwork::CommitEditSequence() { ; }
	UDM_DLL void DomDataNetwork::AbortEditSequence() { ; }

	UDM_DLL void DomDataNetwork::CloseNoUpdate() 
	{
		TRY_XML_EXCEPTION

			rootobject = NULL;

		CATCH_XML_EXCEPTION("DomDataNetwork::CloseNoUpdate()");
	}


	UDM_DLL void DomDataNetwork::CloseWithUpdate() 
	{

		TRY_XML_EXCEPTION

			DOM_Element de = static_cast<DomObject *>(GetRootObject().__impl())->dom_element;
			DOM_Document doc = de.getOwnerDocument();
			ASSERT( doc != (DOM_NullPtr *)NULL);
			if (str_based) 
			{
				str.erase();
				printDOM(doc, str);
			}
			else
				printDOM(doc, savesystemname.c_str());
			rootobject = NULL;
		
		CATCH_XML_EXCEPTION("DomDataNetwork::CloseWithUpdate()") 

	}

	UDM_DLL void DomDataNetwork::SaveAs(string systemname)
	{
		TRY_XML_EXCEPTION

			DOM_Element de = static_cast<DomObject *>(GetRootObject().__impl())->dom_element;
			DOM_Document doc = de.getOwnerDocument();
			ASSERT( doc != (DOM_NullPtr *)NULL);
			printDOM(doc, systemname.c_str());
		
		CATCH_XML_EXCEPTION("DomDataNetwork::SaveAs()") 
	}; 


	UDM_DLL Object DomDataNetwork::ObjectById(Object::uniqueId_type id) 
	{ 
		TRY_XML_EXCEPTION

		
			IdToDomElementMap::iterator i = DomElements.find(id);
			DOM_Element d;

			if (i != DomElements.end())
			{
				d = (*i).second;
				return new DomObject(/*GetRootMeta(),*/ d, this);
			} 
			else return NULL;

		CATCH_XML_EXCEPTION("DomDataNetwork::ObjectById()") 
	}


	const string DomDataNetwork::FindFile(const string file_name)
	{


#ifdef _WIN32
		static const char path_dlim =';';
		static const char path_hier ='\\';
#else
		static const char path_dlim =':';
		static const char path_hier ='/';
#endif

		

		string ret;			// we return this;

		if (DTDPath.empty())
		{
			//look in curent folder;

			if (access(file_name.c_str(), 4) == 0) return file_name;

			//check PATH environment variable
			const char * _path = getenv("PATH");
			char * path = NULL;
			char * full_file_name = NULL;

			//
			//follows state-of-the-art file lookup in PATH
			//
			if (_path)
			{
				path = new char[strlen(_path) + 1]; strcpy(path, _path);			//safe copy of the env. var we can fool arround with
				char * curr_path = path;											//jump start
				bool found = false;													//we keep lookin'

				while (!found && curr_path && *curr_path != '\0')					
				{
					char * next_delim = strchr(curr_path, path_dlim);
					if (next_delim) *next_delim++ = '\0';

					full_file_name = new char[strlen(curr_path) + file_name.size() + 2];//hier. char+ ending '\0'
					sprintf(full_file_name, "%s%c%s", curr_path, path_hier, file_name.c_str());
					if (access(full_file_name, 4) == 0)
					{
						found = true;
						ret = full_file_name;
						continue;
					}
					delete full_file_name;
					curr_path = next_delim;
				}

				delete path;
				
			}

		}
		else
		{
			char * full_file_name = new char[DTDPath.size() + file_name.size() + 2];//hier. char+ ending '\0'
			sprintf(full_file_name, "%s%c%s", DTDPath.c_str(), path_hier, file_name.c_str());
			
			if (access(full_file_name, 4) == 0) ret = full_file_name;
			delete full_file_name;

		}
		return ret;
	};


	struct Startup
	{
		Startup()
		{
	        XMLPlatformUtils::Initialize();
		}

		~Startup()
		{
			XMLPlatformUtils::Terminate();
		}
	} __startup;

	bool  DomDataNetwork::multiroles;
	UDM_DLL string  DomDataNetwork::DTDPath;

	static class reg {
		public:
		reg() {
			DomDataNetwork::RegisterBackend("DOM", "xml", &DomDataNetwork::factory);
			UdmDom::Dummy_For_Linker++;	//just to use the variable...
		}	
		~reg() {
			DomDataNetwork::UnRegisterBackends();
		}
	} _reg_unused;

	UDM_DLL int DummyFL;   // for linker
	
	
	bool isXmi(const string& systemname)
	{
		
		TRY_XML_EXCEPTION

		MyEntityResolver resolver;
		ASSERT( systemname.length());

/*		savesystemname = systemname;
		if(!strnicmp(savesystemname.c_str(),"DOM:", 4)) savesystemname.erase(0,4);*/
		DOMParser parser;

		parser.setValidationScheme(DOMParser::Val_Always);
		parser.setDoNamespaces(false);
		parser.setExpandEntityReferences(true);
		parser.setIncludeIgnorableWhitespace(false);
		parser.setEntityResolver(&resolver);

		MobiesErrorHandler errhand;
		parser.setErrorHandler(&errhand);

		try
		{
			parser.parse(systemname.c_str());
		}
		catch(const XMLException& toCatch)
		{
			string description = "Error during parsing: '";
			description += systemname;
			description += "'. Exception message is: ";
			description += StrX(toCatch.getMessage()).localForm();

			throw udm_exception(description);
		}

		DOM_Element root = parser.getDocument().getDocumentElement();
		StrX name(root.getNodeName());
	
		if ( (strlen(name.localForm())== 3) && (strcmp(name.localForm(), "XMI") == 0))
			return true;
		
		return false;

		CATCH_XML_EXCEPTION("UdmDom::isXmi()");
	};


}

