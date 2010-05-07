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

#ifndef MOBIES_UDMGME_H
#define MOBIES_UDMGME_H

#ifndef MOBIES_UDMBASE_H
#include "UdmBase.h"
#endif

#ifndef MOBIES_UML_H
#include "Uml.h"
#endif

#include <comdef.h>


/*
CHANGELOG
	25/09/04	-	endre

			- removed the #include MgaDefs.h and the definition of struct assocmapitem in order to keep this header file independent
			from COM header files. Forward declaration for METALib::IMgaMetaProject has been also added.. 

	24/09/04	-	endre

			- removed global variable amap and global function amapInitialize and placed as a member of GmeDataNetwork.
			Each GmeDataNetwork has it's own version of amap. This was required because GME wanted to have the meta objects released
			at the time of closing the project.

	13/07/04	-	endre

			addressed feature request UDM-6 regarding reference ports.
	03/15/04	-	endre
		
			added backendsemnatics parameter to the BON version of openexisting.

	
	06/19/02	-	endre
	
			Added 
				
				  set<string> GmeDataNetwork::GetMetaRoleFilter(role):

			retrieves a set of strings containing all the possible
			GME CompositionRole values for a given CompositionChildRole

			Added 
			
				IMgaMetaRolePtr GmeObject::GetMetaRoleForKind(kind, mmodel)
			
			retrieves a MetaRole via an object of type 'kind' can be contained
			in a model of type 'mmodel'. Caller makes sure that there is a role 
			for such containment, and that role.target() is compatible with kind.
*/

//we need to forward declare some COM structs in order to keep this .f file indepdent 
//from the COM header files: METALib::IMgaMetaProject, UdmGme::assocmapitem, UdmGme::privdata
namespace METALib
{
	//this is defined in Meta.dll and will be imported in UdmGme.cpp through commonheaders.h
	struct IMgaMetaProject;
};

namespace UdmGme
{
	typedef Udm::Object Object;

	//these structs are defined in UdmGme.cpp
	struct privdata;
	struct assocmapitem;

	//type of the map which holds the mapping of associations to GME Meta Objects
	typedef map< ::Uml::Association::uniqueId_type, assocmapitem> assocmap;
	

	class GmeDataNetwork : public Udm::DataNetwork 
	{
	
		Udm::BackendSemantics semantics;
		
		//map the Udm Composition Child Role to the corresponding set of MGA CompositionRole(MetaRole)s.
		typedef set<string> string_set;			//the compiler doesn't like when templates are nested
		map< ::Uml::CompositionChildRole, string_set> meta_role_filter_cache;
	
	
		void amapInitialize(const ::Uml::Diagram &dgr, METALib::IMgaMetaProject *metaproj);
	
	
		
	public:
		assocmap amap;
		struct privdata &priv;
		void CountWriteOps();
		//type cache by name 
		map<string, const ::Uml::Class> meta_class_cache;
		
		UDM_DLL GmeDataNetwork(const Udm::UdmDiagram &metainfo, Udm::UdmProject* project = NULL);
		UDM_DLL ~GmeDataNetwork();
		UDM_DLL void CreateNew(const string &systemname, 
			const string &metalocator, const ::Uml::Class &rootclass, 
									enum Udm::BackendSemantics sem = Udm::CHANGES_PERSIST_ALWAYS);
		
		// For Udm-based Interpreters ///////////////////
		UDM_DLL void OpenExisting(LPUNKNOWN pUnknown, enum Udm::BackendSemantics sem = Udm::CHANGES_PERSIST_ALWAYS);
		// KMS: Two OpenExistings for ABI Compatibility. Merge next minor release
		UDM_DLL void OpenExisting(LPUNKNOWN pUnknown, enum Udm::BackendSemantics sem /*= Udm::CHANGES_PERSIST_ALWAYS*/, bool customtransactions /*= false*/);
		UDM_DLL Object Gme2Udm(LPUNKNOWN pUnknown);
		/////////////////////////////////////////////////

		UDM_DLL void OpenExisting(const string &systemname, 
									const string &metalocator, 
									enum Udm::BackendSemantics sem = Udm::CHANGES_PERSIST_ALWAYS);
		UDM_DLL void CloseWithUpdate();
		UDM_DLL void CloseNoUpdate();
		UDM_DLL void SaveAs(string systemname); 
		UDM_DLL void CloseAs(string systemname); 

		UDM_DLL void CommitEditSequence();
		UDM_DLL void AbortEditSequence();
		UDM_DLL Object ObjectById(Object::uniqueId_type id);

		UDM_DLL set<string> GetMetaRoleFilter(::Uml::CompositionChildRole role);

		static Udm::DataNetwork *factory(const Udm::UdmDiagram &meta, Udm::UdmProject* project = NULL) {
			return new GmeDataNetwork(meta, project);
		}

	private:
		int writeOps;
		bool hasOpened;
	};


	// Id conversion routines
	UDM_DLL string UdmId2GmeId(Udm::Object::uniqueId_type udmId);
	UDM_DLL Udm::Object::uniqueId_type GmeId2UdmId(const wchar_t* gmeId);
	UDM_DLL Udm::Object::uniqueId_type GmeId2UdmId(const char* gmeId);

	UDM_USE_MGA
}

#endif//MOBIES_UDMGME_H
