
#include <Uml.h>
#include <UdmUtil.h>
#include <UmlExt.h>

UDM_USE_DOM
#ifdef _WIN32
UDM_USE_MGA
#endif

#include <string>
void dummy(void) {; }


int main(int argc, char **argv) 
{
    
    bool child_attr_subtree = false;
	if (argc > 2 && strcmp(argv[1], "-s") == 0)
	{
		child_attr_subtree = true;
		argc--;
		argv++;
	}

	if (argc != 4 )
	{
		cout << "Usage: UdmJson [-s] <inputdatafile> <outputjsonfile> <diagramname> " << endl;
		cout << "  where: <diagramname>: Udm .xml file" << endl;
        cout << " -s : generate children and attributes in _children and _attributes subtrees" << endl;
		cout << "Available backends: " + Udm::DataNetwork::DumpBackendNames() << endl;
                return(-1);


	}
	// Loading the meta
        Udm::SmartDataNetwork  ddnMeta(::Uml::diagram);
        ::Uml::Diagram theUmlDiagram;
        try {

                // Opening the XML meta of the host graph
                Udm::SmartDataNetwork ddnMeta_in(::Uml::diagram);
                ddnMeta_in.OpenExisting(argv[3],"uml.dtd", Udm::CHANGES_LOST_DEFAULT);
		
		// Casting the DataNetwork to diagram
                theUmlDiagram = ::Uml::Diagram::Cast(ddnMeta_in.GetRootObject());

                // Creating the UDM diagram
                Udm::UdmDiagram udmDataDiagram;
                udmDataDiagram.dgr = &theUmlDiagram;
                udmDataDiagram.init = dummy;

		Udm::SmartDataNetwork DN(udmDataDiagram);
		DN.OpenExisting(argv[1],"",Udm::CHANGES_LOST_DEFAULT);
		::UdmUtil::write_json(DN.GetRootObject(), argv[2],child_attr_subtree);
		DN.CloseNoUpdate();		
	}
	catch(udm_exception u) 
	{
                cerr << u.what() << endl;
                exit(-1);
        }
	
	return 0;

}

