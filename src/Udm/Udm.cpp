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

  04/22/05 - kalmar
   added -q switch - all the contained elements in a namespace enlisted 
      here will be ignored during parsing, see udm.exe -i switch

    added -i switch - all the contained elements in a namespace enlisted 
      here will be ignored during parsing, see udm.exe -i switch

	12/12/04	-	endre
		-	small bugfix, for bug a which appeared only on Linux platforms. Filenames are case sensitive
	01/10/04	-	endre

		-	inputfile is checked by content and not by extension. .udm files containing XML format is OK and vice-versa.

    06/17/04	-	kalmar

        - separated GenerateCORBACPP method into UdmCorbaCppH.cpp
        - in presence of cross links the -c switch generates regular code for cross link meta and corba compliant Initialize method for other metas

	  06/16/04	-	endre
	  
			- Using the XSD/DTD generator from the UdmBase.
			- -c switch works with UDM Projects as well.

	  05/24/04	-	endre

			- when using a macro definition, Udm.exe also generates an export file which make easier the DLL export/import
			of the generated classes

		01/26/04	-	endre
			
			  Mainly porting issues to g++ 2.96, specially the compress/decompress stuff.
			  void type had to be add to all the functions declared with no return type

		10/25/02	-	endre

				removed support for temporary diagram. We use a new syntax
				for specifying nonpersistent attributes.

		07/31/02	- C# and Corba generators added

	meaning of switches:

				-s			 generate C# API, normal format
				-s -m		 generate C# API, meta format

				-c			 generate CORBA init .cpp file

	09/23/02	-	print usage if there are no arguments
*/


#include "Uml.h"
#include "UdmBase/DTDGen.h"

#include <UdmXmi.h>
#include <fstream>

#include "./JavaAPIGen/JavaAPIGen.h"

#ifdef WIN32
#include <contrib\minizip\unzip.h>
#else
#include <minizip/unzip.h>
#endif

#include "Udm.h"

int main(int argc, char **argv) {
	try
	{

		string macro;
		string inputfile; 
		//string tempdiagfile; 
		string fname; 
		bool new_meta = true;
		bool c_sharp = false;
		bool corba_meta = false;		// inserted by LA
		bool visitor_sup = false;
		bool dll_gen = false;			//Code which generates a calling convetion specifier (as a MACRO)
										//to facilitate forexample DLL linkage
		bool generate_dtd = false;
		bool uxsdi = false;				//use XSD inheritence features when generating XSD
		bool xsd_el_ta = false;				//generate XSD elements like they would have text attributes
		bool integrate_xsd = false; //integrate xsd into the generated API;
		map<string, string> ns_map;
		set<string> ns_ignore_set;
		set<string> qualifiedAtrrsNS_set;

		// flag to indicate java api generation
		bool generate_java = false;
		int source_unit = CPP_SOURCE_UNIT_DIAGRAM;


		if (argc <= 1)
			throw udm_exception("Usage: udm <diagramfilename> [<genfilesnamebase>] [-d <Uml.xsd searchpath>] [-m|c] [-v] [-t] [-l] [-x]\n");

		for(int argn = 1; argn < argc; argn++) 
		{
			if(argv[argn][0] == '-') 
			{
				char c = argv[argn][1];
				if (c == 'm') 
				{
					new_meta = false;
					continue;
				}
				else if (c == 's')
				{
					c_sharp = true;
					continue;
				}
				else if (c == 'c')		// inserted by LA
				{
					corba_meta = true;
					continue;
				}
				else if (c == 'v')		
				{
					visitor_sup = true;
					continue;
				}
				else if (c == 't')
				{
					generate_dtd = true;
					continue;
				}
				else if (c == 'x')
				{
					uxsdi = true;
					continue;
				}
				// if parameter is 'j', call java API generation
				else if (c == 'j')
				{
					generate_java = true;
					continue;
				}
				else if (c == 'e')
				{
					xsd_el_ta = true;
					continue;
				}
				else if (c == 'g')
				{
					integrate_xsd = true;
					continue;
				}
				
				char *optp;
				if(strlen(argv[argn]) == 2) 
				{
					if(++argn >= argc) goto usage;
					 optp = argv[argn];
				}
				else 
					optp = argv[argn]+2;
				
				switch(c) 
				{
					case 'd': 
							UdmDom::DomDataNetwork::DTDPath = optp;
							break;
					case 'l': 
							macro = optp;
							break;
					case 'u':
							DTDGen::AddUMLContainerNameToURIMapping(optp, ns_map);
							break;
						/*
							switch(*optp)
							{
								case 'd':
									DTDGen::AddUMLContainerNameToURIMapping(string("__dgr_" + string(++optp)).c_str(), ns_map);
									break;
								case 'n':
									DTDGen::AddUMLContainerNameToURIMapping(++optp, ns_map);
									break;
								default:
									goto usage;
							}
							*/
					case 'i':
							DTDGen::AddUMLContainerNameToIgnoreList(optp, ns_ignore_set);
							break;
						/*
							switch(*optp)
							{
								case 'd':
									DTDGen::AddUMLContainerNameToIgnoreList(string("__dgr_" + string(++optp)).c_str(), ns_ignore_set);
									break;
								case 'n':
									DTDGen::AddUMLContainerNameToIgnoreList(++optp, ns_ignore_set);
									break;
								default:
									goto usage;
							}
							*/
					case 'q':
							DTDGen::AddUMLContainerNameToQualifiedAttrsNSList(optp, qualifiedAtrrsNS_set);
							break;
						/*
							switch(*optp)
							{
								case 'd':
									DTDGen::AddUMLContainerNameToQualifiedAttrsNSList(string("__dgr_" + string(++optp)).c_str(), qualifiedAtrrsNS_set);
									break;
								case 'n':
									DTDGen::AddUMLContainerNameToQualifiedAttrsNSList(++optp, qualifiedAtrrsNS_set);
									break;
								default:
									goto usage;
							}
							*/
					case 'w':
							switch(*optp)
							{
								case 'c':
									source_unit = CPP_SOURCE_UNIT_CLASS;
									break;
								case 'd':
									source_unit = CPP_SOURCE_UNIT_DIAGRAM;
									break;
								case 'n':
									source_unit = CPP_SOURCE_UNIT_NAMESPACE;
									break;
								default:
									goto usage;
							}
							break;
					default:
							goto usage;
				}
			}
			else if(inputfile.empty()) {
				inputfile = argv[argn];
			}
			else if(fname.empty()) {
				fname = argv[argn];
			}
			else if (argv[argn][0] == 'm'){
				new_meta = false;
			}
			else
			{
usage:
				throw udm_exception("Usage: udm <diagramfilename> [<genfilesnamebase>] [-d <Uml.XSD searchpath>] [-m|c|s] [-v] [-t] [-l] [-x]\n");
			}
		}

		if (uxsdi)
		{
			cout << " WARNING: If using the -x switch, the generated XSD file is not suitable for " << endl;
			cout << " validation of UDM DOM datanetworks (XML Files), but instead it correctly reflects " << endl;
			cout << " the inheritence relationships and the abstractness of types, as described in the UML" << endl;
			cout << " Diagram. This file might be used as input for other XML tools, like XSD code generators. " << endl;
		}

		//check for UDM Project input
		unzFile is_zip = unzOpen(inputfile.c_str());
		if (is_zip)
		{
			//open is succesfull, so we have to close it.
			unzClose(is_zip);
			//we will have n + 1 XML datanetworks
			//we will generate CPP for all of them
			//we will generate n .h file
			//and we willlook up the cross-package associations
			//so:
			

			// we need a different .h generator
			// which takes an a data network and the cross-link meta datanetwork
			// and generates the API


			Udm::UdmProject pr;
			pr.OpenExisting(inputfile, Udm::CHANGES_LOST_DEFAULT);


			const Udm::DataNetwork& cross_meta_dn = pr.GetCrossMetaNetwork();
			const ::Uml::Diagram &cross_meta = ::Uml::Diagram::Cast(cross_meta_dn.GetRootObject());

			string cm_name = NameToFilename(cross_meta.name());

			GenerateDSD(cross_meta, cm_name, generate_dtd, uxsdi, xsd_el_ta, ns_map, ns_ignore_set, false);

			GenerateHH(cross_meta, cm_name, visitor_sup, NULL, macro, source_unit);

			ofstream ff;

			if (new_meta && !corba_meta)
				GenerateNewCPP(cross_meta, cm_name, ns_map, cross_meta, "", integrate_xsd, source_unit);
			else
			{
				ff.open( (cm_name+ ".cpp").c_str());
				if(!ff.good()) throw udm_exception("Error opening for write " + cm_name + ".cpp");
				else 
				{
					if (corba_meta) GenerateCORBACPP(cross_meta,  ff, cm_name, cross_meta, macro);
					else GenerateCPP(cross_meta,  ff, cm_name, cross_meta, macro, integrate_xsd);
				}
				ff.close();
				ff.clear();
			}


			cout << " Cross meta: " << cross_meta.name() << endl;
			vector<Udm::DataNetwork*> pr_dns = pr.GetDataNetworks();
			vector<Udm::DataNetwork*>::iterator pr_dns_i = pr_dns.begin();
			while (pr_dns_i != pr_dns.end())
			{
				//these should be UML diagrams
				::Uml::Diagram dgr = ::Uml::Diagram::Cast((*pr_dns_i)->GetRootObject());
				string sname = dgr.name();
				GenerateDSD(dgr, NameToFilename(sname), generate_dtd, uxsdi, xsd_el_ta, ns_map, ns_ignore_set, false);

				::Uml::DiagramNamespaces nses(dgr);
				for (::Uml::DiagramNamespaces::iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
				{
					GenerateDSD(*nses_i, generate_dtd, uxsdi, xsd_el_ta, ns_map, ns_ignore_set, false);
				}

				// "_export.h" already generated
				GenerateHH(dgr, sname, visitor_sup, cross_meta, "", source_unit);

				if(new_meta && !corba_meta)
					GenerateNewCPP(dgr, sname, ns_map, cross_meta, macro, integrate_xsd, source_unit);
				else
				{
					ff.open( (sname + ".cpp").c_str() );
					if(!ff.good()) throw udm_exception("Error opening for write " + sname + ".cpp");
					else 
					{
						if (corba_meta) GenerateCORBACPP(dgr,  ff, sname, cross_meta, macro);
						else GenerateCPP(dgr,  ff, sname, cross_meta, macro, integrate_xsd);
					}
					ff.close();
					ff.clear();
				}

				pr_dns_i++;

			}

			return 0;
		};

		//check for XMI input
		//1. If there is no DTDPath, it can not be an XMI Input

		bool xmi_input = false;

		if (!UdmDom::DomDataNetwork::DTDPath.empty())
		{
			//the input might be XMI
			//we will try to find out,
			//but first we reset the DTD Path

			//reset the DTD PATH in the DOM BackEnd,
			//so the parser will use the Udm.dtd found near the XMI input
			//save,
			string _dom_path = UdmDom::DomDataNetwork::DTDPath;
			//then reset
			UdmDom::DomDataNetwork::DTDPath = string();

			try
			{
				xmi_input = UdmDom::isXmi(inputfile);
				//it did not fail,
				//so it means that it has a Uml.dtd near the XML file,
				//which seems to be able to validate the XML file
				// either is XMI or not, it's valid, and xmi_input has the right answer

			}
			catch(udm_exception&)
			{
				//there was no Uml.dtd near the file,
				//so it's not XMI input
				//we do nothing; The DTD Path will be restored
				//and probably parsed OK.
			}

			
			//re-set the DTD path, the resolver now should find the Uml.dtd in the DTD path and not 
			//the Uml.dtd(XMI) in the current directory
			UdmDom::DomDataNetwork::DTDPath = _dom_path;
		}

		//The actual parsing happens somewhere here!
		//now the entity resolver should look for files in the current directory
		
		//if it has not succeded, the user probably wants to 
		//open a normal UDM UML XML file, and needs the DTD path for this.

		//if it was XMI, convert it to UDM
		if (xmi_input)
		{
			if (UdmDom::DomDataNetwork::DTDPath.empty())
				throw udm_exception("DTD Path empty. When generating API directly from XMI input, the use of the DTD path switch is not optional. In the location pointed by DTDPath the UDM's Uml.dtd should reside. In the same directory with the input XMI the Uml.dtd defined by OMG should reside.");
			
			//compute the name of the new file
			string input_udm = inputfile + "_udm.xml";

			//do the XmiTUdm conversion
			if (XmiToUdm(inputfile.c_str(), input_udm.c_str()) != 0)
			{
				throw udm_exception("An error occured during translating from XMI UML to UDM UML.");
			}

			//set the input to the newly converted file
			inputfile = input_udm;

		}

		UdmDom::DomDataNetwork  nw(Uml::diagram);
		nw.OpenExisting(inputfile,"", Udm::CHANGES_LOST_DEFAULT);
		::Uml::Diagram diagram = ::Uml::Diagram::Cast(nw.GetRootObject());

		//check the diagram for reserver and duplicate names
		//which would generate invalid code
		CheckDiagram(diagram); //it will throw an exception if stg goes wrong.

		if(fname.empty()) {
			fname = NameToFilename(diagram.name());
		}

		{
			set<string>::const_iterator itf = qualifiedAtrrsNS_set.find("__dgr_" + string(diagram.name()));
			bool qualifiedAtrrsNS = (itf != qualifiedAtrrsNS_set.end());
			GenerateDSD(diagram, fname, generate_dtd, uxsdi, xsd_el_ta, ns_map, ns_ignore_set, qualifiedAtrrsNS);
		}

		::Uml::DiagramNamespaces nses(diagram);
		for (::Uml::DiagramNamespaces::iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
		{
			::Uml::Namespace ns = *nses_i;
			string nspath = ns.getPath2("::", false);

			set<string>::const_iterator itf = qualifiedAtrrsNS_set.find(nspath);
			bool qualifiedAtrrsNS = (itf != qualifiedAtrrsNS_set.end());

			GenerateDSD(ns, generate_dtd, uxsdi, xsd_el_ta, ns_map, ns_ignore_set, qualifiedAtrrsNS);
		}

		// call java API generation
		if (generate_java) 
		{
			JavaAPIGen gen(diagram, ns_map, inputfile);
			gen.generate();
			return 0;
		}

		ofstream ff;

		if (c_sharp) {
			ff.open( (fname + ".cs").c_str());
			if(!ff.good()) throw udm_exception("Error opening for write " + fname + ".cpp");
			else {
				//	if(new_meta) GenerateNewCS(diagram, ff, fname);
				//	else GenerateCS(diagram,  ff, fname);
			}
			ff.close();
			return 0;
		}

		GenerateHH(diagram, fname, visitor_sup, NULL, macro, source_unit);
		
		if(new_meta && !corba_meta)
			GenerateNewCPP(diagram, fname, ns_map, NULL, macro, integrate_xsd, source_unit);
		else
		{
			ff.open( (fname + ".cpp").c_str());

			if(!ff.good()) throw udm_exception("Error opening for write " + fname + ".cpp");
			else 
			{
				if (corba_meta) GenerateCORBACPP(diagram,  ff, fname);
				else GenerateCPP(diagram,  ff, fname, NULL, macro, integrate_xsd);
			}
			ff.close();
		}
	}
	catch(const udm_exception &e)
	{
		cout << "Exception: " << e.what() << endl;
		return(-1);

	}
	
	//just use the UdmDom::
	UdmDom::Dummy_For_Linker++;
	return 0;
}


