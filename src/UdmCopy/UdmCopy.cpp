#ifdef _WIN32
//#include <UdmGme.h>
#endif


//#include <UdmDom.h>

#include "Uml.h"
#include "UmlExt.h"

using namespace Uml;
using namespace Udm;

UDM_USE_DOM

#ifdef _WIN32
UDM_USE_MGA
#endif

#include <UdmUtil.h>

#include <cstdlib>

/*
static Diagram linkdiag;
static Class linkpar;
static Attribute link;

void copy(ObjectImpl *from, ObjectImpl *to);
void assoccopy(ObjectImpl *from, ObjectImpl *to);
*/

void dummy(void) {; }

class UdmCopy
{
	UdmDiagram m_meta;
	string m_metaloc;
	string m_backend_ext;

public:
	UdmCopy(const UdmDiagram &p_meta, const string &p_metaloc, const string &p_backend_ext)
		: m_meta(p_meta)
		, m_metaloc(p_metaloc)
		, m_backend_ext(p_backend_ext)
	{
	}

	void Copy(ObjectImpl *p_srcRoot, ObjectImpl *p_dstRoot, DataNetwork *p_dstBackend, UdmUtil::copy_assoc_map &cam)
	{
		vector<ObjectImpl*> children = p_srcRoot->getChildren(NULL, p_srcRoot->type());
		for (vector<ObjectImpl*>::const_iterator i = children.begin(); i != children.end(); i++) {

			ObjectImpl *p_srcChild = *i;

			string lib_name = p_srcChild->getLibraryName();
			if (lib_name.length() == 0) {
				p_srcChild->release();
				continue;
			}
			string new_lib_name = lib_name.substr(0, lib_name.length() - 4) + "." + m_backend_ext;


			// create datanetwork for standalone library and build map
			// from source object to standalone library object
			Udm::SmartDataNetwork libDN(m_meta);
			const ::Uml::Class & safe_type = ::Uml::SafeTypeContainer::GetSafeType(p_srcChild->type());
			libDN.CreateNew(new_lib_name, m_metaloc, safe_type);
			Object p_root = libDN.GetRootObject();
			ObjectImpl *p_libRoot = p_root.__impl();

			// copy, including nested libraries
			UdmUtil::copy_assoc_map lib_cam;
			Copy(p_srcChild, p_libRoot, &libDN, lib_cam);
			lib_cam.insert( make_pair(p_srcChild->clone(), p_libRoot->clone()) );
			libDN.SaveAs(new_lib_name);


			// attach library to destination host and build map
			// from standalone library object to private copy object
			// (the map already has a mapping from src root to dst root)
			Udm::t_lib_to_copy_impl_map lib_copy_impl_cam;
			ObjectImpl *p_newLibRoot = p_dstRoot->AttachLibrary(p_libRoot, new_lib_name, &lib_copy_impl_cam);

			// we need a new map with Object elements instead of ObjectImpl* elements
			UdmUtil::copy_assoc_map lib_copy_cam;
			for (Udm::t_lib_to_copy_impl_map::const_iterator i = lib_copy_impl_cam.begin(); i != lib_copy_impl_cam.end(); i++) {
				lib_copy_cam.insert( make_pair(i->first, i->second) );
			}


			// map from source to library private copy
			for (UdmUtil::copy_assoc_map::const_iterator i = lib_cam.begin(); i != lib_cam.end(); i++) {
				UdmUtil::copy_assoc_map::const_iterator fi = lib_copy_cam.find(i->second);
				if (fi == lib_copy_cam.end())
					throw udm_exception("object not found in map");
				cam.insert( make_pair(i->first, fi->second) );
			}

			libDN.CloseNoUpdate();

			cam.insert( make_pair(p_srcChild, p_newLibRoot) );
		}

		UdmUtil::CopyObjectHierarchy(p_srcRoot, p_dstRoot, p_dstBackend, cam);
	}
};


int main(int argc, char **argv) {
		
		if(argc != 4 && argc != 5) {
			cout << "Usage: UdmCopy <indataname> <outdataname> <diagramname> [<metalocator>]" << endl;
			return(-1);
		}

		// Loading the meta 
		Udm::SmartDataNetwork  ddnMeta(::Uml::diagram);	
		::Uml::Diagram theUmlDiagram;

		try {

			// Opening the XML meta of the host graph
			ddnMeta.OpenExisting(argv[3],"uml.dtd", Udm::CHANGES_LOST_DEFAULT);

			// Casting the DataNetwork to diagram
			theUmlDiagram = ::Uml::Diagram::Cast(ddnMeta.GetRootObject());
			
			// Creating the UDM diagram
			Udm::UdmDiagram udmDataDiagram;
			udmDataDiagram.dgr = &theUmlDiagram;
			udmDataDiagram.init = dummy;

				
	

	
			string metaloc;
			if(argc != 5) metaloc = theUmlDiagram.name();
			else metaloc = argv[4]; 
			
			Udm::Object root;
			Udm::SmartDataNetwork  fromDN(udmDataDiagram), toDN(udmDataDiagram);
			

			fromDN.OpenExisting(argv[1],"", Udm::CHANGES_LOST_DEFAULT);
			
			const ::Uml::Class & safe_type = ::Uml::SafeTypeContainer::GetSafeType(fromDN.GetRootObject().type());
			toDN.CreateNew(argv[2], metaloc, safe_type, Udm::CHANGES_PERSIST_DEFAULT);

			string toDN_name = argv[2];
			string toDN_ext = toDN_name.substr(toDN_name.length() - 3, 3);

			UdmCopy cp(udmDataDiagram, metaloc, toDN_ext);

			UdmUtil::copy_assoc_map dummy;
			cp.Copy(fromDN.GetRootObject().__impl(), toDN.GetRootObject().__impl(), &toDN, dummy);

		}

		catch(udm_exception u) {
			cout << u.what() << endl;
			exit(-1);
		}

		return 0;
}




