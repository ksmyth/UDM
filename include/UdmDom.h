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

CHANGELOG:
04/07/05 -kalmar 
            StoreXsd stores a copy of a string not pointer it was porblem when the original string deleted. e.g. in judm
11/07/04	-	endre

			-		updated to Xerces 2_5_0. (simply changed the forward declaration namespace
10/1/3		-	endre

			-		DTDPath was not exported in DLL

05/10/04	-	endre

				- added functions CreateNewToString and OpenExistingFromString functions
				to provide string based functionality
  
*/

#ifndef MOBIES_UDMDOM_H
#define MOBIES_UDMDOM_H

#ifndef MOBIES_UDMBASE_H
#include <UdmBase.h>
#endif

//these predefinitions are needed for typedefs

//GNU does not allow using namespace aliases in forward declarations
namespace xercesc_2_5
{
	class DOM_Node;
	class DOM_Element;
	class DOMString;
}
using namespace xercesc_2_5;

typedef map<unsigned long, DOM_Element> IdToDomElementMap;
typedef pair<const unsigned long, DOM_Element> IdToDomElementMapItem;

	
namespace UdmDom
{
	typedef Udm::Object Object;

	//check if an input XML is in UDM UML or XMI UML format
	//(used mainly by  Udm.exe)

	//these will be linked as an external .cpp file.
	
	
	bool isXmi(const string& filename);

	
	class DomDataNetwork : public Udm::DataNetwork 
	{
		static bool multiroles;
		static int instancecount;
		string savesystemname;
		bool saveondestroy;
		bool str_based;
		string str;

	public:
		static UDM_DLL string DTDPath;
		//meta type-cache-by-name
		map<string, ::Uml::Class> meta_class_cache;

		UDM_DLL DomDataNetwork(const Udm::UdmDiagram &metainfo, Udm::UdmProject* pr = NULL);
		UDM_DLL ~DomDataNetwork();
		UDM_DLL void CreateNew(const string &systemname, 
									const string &metalocator, const ::Uml::Class &rootclass, 
									enum Udm::BackendSemantics sem = Udm::CHANGES_PERSIST_ALWAYS);

		UDM_DLL void CreateNewToString(const string &metalocator, const ::Uml::Class &rootclass, 
									enum Udm::BackendSemantics sem = Udm::CHANGES_PERSIST_ALWAYS);


		UDM_DLL void OpenExisting(const string &systemname, 
									const string &metalocator, 
									enum Udm::BackendSemantics sem = Udm::CHANGES_PERSIST_ALWAYS);
		
		UDM_DLL void OpenExistingFromString(string &str, 
									const string &metalocator, 
									enum Udm::BackendSemantics sem = Udm::CHANGES_PERSIST_ALWAYS);
		
		UDM_DLL void MapExistingIDs(DOM_Node &d);
		UDM_DLL void SaveAs(string systemname); 
		UDM_DLL void CloseWithUpdate();
		UDM_DLL void CloseNoUpdate();

		UDM_DLL void CommitEditSequence();
		UDM_DLL void AbortEditSequence();

// if MultiRoles is enabled, a child object can assume 
//		multiple roles in its container simultaneously (but always at least one)
// otherwise, a new role assignment removes prior role 
		static bool MultiRolesEnabled() { return multiroles; }
		static bool EnableMultiRoles(bool p) { multiroles = p; return p;}

		UDM_DLL Object ObjectById(Object::uniqueId_type id);
		
		static Udm::DataNetwork *factory(const Udm::UdmDiagram &meta, Udm::UdmProject* project = NULL) 
		{
			return new DomDataNetwork(meta, project);
		}
	
		static const string FindFile(const string file_name);
		
		//map of Elements in the Diagram
		IdToDomElementMap DomElements;
		void DoMapping(const DOM_Element &e, long id,  bool force);
		DOM_Element Search(const DOM_Node &d, const DOMString &str);

		//get the string if datanetwork is str_based

		UDM_DLL const string & Str();

		

	};

	struct str_xsd_storage
	{

		typedef map<const string, const string> str_str_map;
		
		static UDM_DLL str_str_map static_xsd_container;
		static void StoreXsd(const string key, const string & xsd_str)
		{
			str_str_map::value_type item(key, xsd_str);
			pair<str_str_map::const_iterator, bool> ins_res = static_xsd_container.insert(item);
      if (!ins_res.second && (xsd_str!=ins_res.first->second)) // only if it differs from the stored one Kalmar
				throw udm_exception(string("An XSD by that name is already stored with a different content: ") + key);


		};

		static void RemoveXsd(const string key)
		{
			
			static_xsd_container.erase(key);

		}
 		static void ClearXsdStorage()
		{
			
			static_xsd_container.clear();

		}

	};


	//map namespace URI to UML namespace
	struct xsd_ns_mapping_storage
	{
		typedef map<const string, const string> str_str_map;
		static UDM_DLL str_str_map static_xsd_ns_mapping_container;
    static UDM_DLL str_str_map static_xsd_ns_back_mapping_container;
	};

	UDM_DLL void AddURIToUMLNamespaceMapping(const string & namespaceURI, const string & namespaceUML);
	UDM_DLL void RemoveURIToUMLNamespaceMapping(const string & namespaceURI);
	UDM_DLL void ClearURIToUMLNamespaceMappings();


	string GetTime();

	// MAKE SURE LINKER LOADS GmeLib
	extern UDM_DLL int DummyFL;
	static int *Dummy_For_Linker = &DummyFL;
	
}

//try & catch XML exception macros, which declare a block
//use careful, and together

#define TRY_XML_EXCEPTION try {
#define CATCH_XML_EXCEPTION(where)  }\
		catch(XMLException &e)\
		{\
			StrX msg = e.getMessage();\
			string what = "Udm: XMLException: ";\
			what += msg.localForm();\
			if (e.getType())\
			{\
				msg = e.getType();	\
				what += ", of type:";\
				what += msg.localForm();\
			}\
			what += ", in File: ";\
			what += e.getSrcFile();\
			what += ", in Line: ";\
			char * line_str = new char[20];/*should be enough for 32 bit integers */\
			if (line_str)\
			{\
				sprintf(line_str, "%d", e.getSrcLine());\
				what += line_str;\
				delete line_str;\
			}\
			what += where;\
			throw udm_exception(what);\
		}\


#endif//MOBIES_UDMDOM_H
