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

/*
static Diagram linkdiag;
static Class linkpar;
static Attribute link;

void copy(ObjectImpl *from, ObjectImpl *to);
void assoccopy(ObjectImpl *from, ObjectImpl *to);
*/

void dummy(void) {; }


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
			UdmUtil::copy_assoc_map dummy;
			UdmUtil::CopyObjectHierarchy(fromDN.GetRootObject().__impl(), toDN.GetRootObject().__impl(), &toDN, dummy);

		}

		catch(udm_exception u) {
			cout << u.what() << endl;
			exit(-1);
		}

		return 0;
}




