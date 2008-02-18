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

		UdmOpts opts;
		opts.meta_init = UdmOpts::DYNAMIC_INIT;
		opts.visitor_sup = false;
		opts.cxx_source_unit = UdmOpts::UNIT_DIAGRAM;

		opts.generate_dtd = false;
		opts.uxsdi = false;
		opts.xsd_el_ta = false;
		opts.integrate_xsd = false;

		opts.rec_tstamp = true;

		string inputfile; 
		//string tempdiagfile; 
		string fname; 



		if (argc <= 1)
			throw udm_exception("Usage: udm <diagramfilename> [<genfilesnamebase>] [-d <Uml.xsd searchpath>] [-m|c] [-v] [-t] [-l] [-x]\n");

		for(int argn = 1; argn < argc; argn++) 
		{
			if(argv[argn][0] == '-') 
			{
				char c = argv[argn][1];
				if (c == 'm') 
				{
					opts.meta_init = UdmOpts::STATIC_INIT;
					continue;
				}
				else if (c == 'c')		// inserted by LA
				{
					opts.meta_init = UdmOpts::CORBA_INIT;
					continue;
				}
				// if parameter is 'j', call java API generation
				else if (c == 'j')
				{
					opts.mode = UdmOpts::JAVA;
					continue;
				}
				else if (c == 's')
				{
					opts.mode = UdmOpts::C_SHARP;
					continue;
				}
				else if (c == 'v')		
				{
					opts.visitor_sup = true;
					continue;
				}
				else if (c == 't')
				{
					opts.generate_dtd = true;
					continue;
				}
				else if (c == 'x')
				{
					opts.uxsdi = true;
					continue;
				}
				else if (c == 'e')
				{
					opts.xsd_el_ta = true;
					continue;
				}
				else if (c == 'g')
				{
					opts.integrate_xsd = true;
					continue;
				}
				else if (c == 'T')
				{
					opts.rec_tstamp = false;
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
							opts.macro = optp;
							opts.macro += " ";
							break;
					case 'u':
							DTDGen::AddUMLContainerNameToURIMapping(optp, opts.ns_map);
							break;
						/*
							switch(*optp)
							{
								case 'd':
									DTDGen::AddUMLContainerNameToURIMapping(string("__dgr_" + string(++optp)).c_str(), opts.ns_map);
									break;
								case 'n':
									DTDGen::AddUMLContainerNameToURIMapping(++optp, opts.ns_map);
									break;
								default:
									goto usage;
							}
							*/
					case 'i':
							DTDGen::AddUMLContainerNameToIgnoreList(optp, opts.ns_ignore);
							break;
						/*
							switch(*optp)
							{
								case 'd':
									DTDGen::AddUMLContainerNameToIgnoreList(string("__dgr_" + string(++optp)).c_str(), opts.ns_ignore);
									break;
								case 'n':
									DTDGen::AddUMLContainerNameToIgnoreList(++optp, opts.ns_ignore);
									break;
								default:
									goto usage;
							}
							*/
					case 'q':
							DTDGen::AddUMLContainerNameToQualifiedAttrsNSList(optp, opts.ns_qualified_attrs);
							break;
						/*
							switch(*optp)
							{
								case 'd':
									DTDGen::AddUMLContainerNameToQualifiedAttrsNSList(string("__dgr_" + string(++optp)).c_str(), opts.ns_qualified_attrs);
									break;
								case 'n':
									DTDGen::AddUMLContainerNameToQualifiedAttrsNSList(++optp, opts.ns_qualified_attrs);
									break;
								default:
									goto usage;
							}
							*/
					case 'w':
							switch(*optp)
							{
								case 'c':
									opts.cxx_source_unit = UdmOpts::UNIT_CLASS;
									break;
								case 'd':
									opts.cxx_source_unit = UdmOpts::UNIT_DIAGRAM;
									break;
								case 'n':
									opts.cxx_source_unit = UdmOpts::UNIT_NAMESPACE;
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
			else
			{
usage:
				throw udm_exception("Usage: udm <diagramfilename> [<genfilesnamebase>] [-d <Uml.XSD searchpath>] [-m|c|s] [-v] [-t] [-l] [-x]\n");
			}
		}

		UdmOpts opts_nomacro = opts;
		opts_nomacro.macro = "";

		if (opts.uxsdi)
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

			GenerateDSD(cross_meta, cm_name, opts, false);

			UdmCPPGen::UdmGen gen(cross_meta, opts_nomacro);
			gen.Generate(cross_meta, cm_name);


			cout << " Cross meta: " << cross_meta.name() << endl;
			vector<Udm::DataNetwork*> pr_dns = pr.GetDataNetworks();
			vector<Udm::DataNetwork*>::iterator pr_dns_i = pr_dns.begin();
			while (pr_dns_i != pr_dns.end())
			{
				//these should be UML diagrams
				::Uml::Diagram dgr = ::Uml::Diagram::Cast((*pr_dns_i)->GetRootObject());
				string sname = dgr.name();
				GenerateDSD(dgr, NameToFilename(sname), opts, false);

				::Uml::DiagramNamespaces nses(dgr);
				for (::Uml::DiagramNamespaces::iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
				{
					GenerateDSD(*nses_i, opts, false);
				}

				UdmCPPGen::UdmGen gen(dgr, opts);
				gen.Generate(cross_meta, sname);

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
			set<string>::const_iterator itf = opts.ns_qualified_attrs.find("__dgr_" + string(diagram.name()));
			bool qualifiedAtrrsNS = (itf != opts.ns_qualified_attrs.end());
			GenerateDSD(diagram, fname, opts, qualifiedAtrrsNS);
		}

		::Uml::DiagramNamespaces nses(diagram);
		for (::Uml::DiagramNamespaces::iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
		{
			::Uml::Namespace ns = *nses_i;
			string nspath = ns.getPath2("::", false);

			set<string>::const_iterator itf = opts.ns_qualified_attrs.find(nspath);
			bool qualifiedAtrrsNS = (itf != opts.ns_qualified_attrs.end());

			GenerateDSD(ns, opts, qualifiedAtrrsNS);
		}

		// call java API generation
		if (opts.mode == UdmOpts::JAVA) 
		{
			JavaAPIGen gen(diagram, opts.ns_map, inputfile);
			gen.generate();
			return 0;
		}

		if (opts.mode == UdmOpts::C_SHARP) {
			ofstream ff;
			ff.open( (fname + ".cs").c_str());
			if(!ff.good()) throw udm_exception("Error opening for write " + fname + ".cpp");
			else {
				//	if(new_meta) GenerateNewCS(diagram, ff, fname);
				//	else GenerateCS(diagram,  ff, fname);
			}
			ff.close();
			return 0;
		}

		UdmCPPGen::UdmGen gen(diagram, opts);
		gen.Generate(NULL, fname);
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


