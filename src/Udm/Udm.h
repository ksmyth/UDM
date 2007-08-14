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

#ifndef MOBIES_UDM_H
#define MOBIES_UDM_H

#include <UdmDom.h>
#include <UmlExt.h>


enum CPPSourceUnit {
	CPP_SOURCE_UNIT_DIAGRAM,	// one .h and one .cpp file per diagram
	CPP_SOURCE_UNIT_NAMESPACE,	// one .h and one .cpp file per namespace
	CPP_SOURCE_UNIT_CLASS,		// one .h and one .cpp file per namespace, one .h file per class
};

extern bool single_cpp_namespace;

//cross-link-approved
void GenerateHExport(const ::Uml::Diagram &diagram,  ostream &output, string fname, const string& macro);
void GenerateH(const ::Uml::Diagram &diagram,  ostream &output, string fname, bool visitor_sup = false, const ::Uml::Diagram& cross_dgr = NULL, const string& macro = "", const int source_unit = CPP_SOURCE_UNIT_DIAGRAM);
void GenerateHH(const ::Uml::Diagram &dgr, const std::string &fname, const bool visitor_sup, const ::Uml::Diagram &cross_dgr, const std::string &macro, int source_unit);
void GenerateNewCPP(const ::Uml::Diagram &diagram, 
                    string fname, 
                    const map<string, string> &ns_map, 
                    const ::Uml::Diagram& cross_dgr = NULL, 
                    const string& macro = "",
                    bool integrate_xsd = false,
					int source_unit = CPP_SOURCE_UNIT_DIAGRAM);

void GenerateCPP(	const ::Uml::Diagram &diagram, 
					ostream &output, string fname, 
					const ::Uml::Diagram& cross_dgr = NULL, 
					const string& macro = "",
					bool integrate_xsd = false);
//void GenerateCORBACPP(const ::Uml::Diagram &diagram, ostream &output, string fname, const ::Uml::Diagram& cross_dgr = NULL, const string& macro = "");

// not cross-link approved
void GenerateCSInit(const ::Uml::Diagram &diagram, ostream &output, string fname);
void GenerateNewCSInit(const ::Uml::Diagram &diagram, ostream &output, string fname);
void GenerateCSApi(const ::Uml::Diagram &diagram, ostream &output, string fname);
void GenerateCS(const ::Uml::Diagram &diagram,  ostream &output, string fname);
void GenerateNewCS(const ::Uml::Diagram &diagram,  ostream &output, string fname);
void CheckDiagram(const ::Uml::Diagram & diagram);

// utils
std::string GetTime();
std::string UmlClassCPPName(const ::Uml::Class &cl);
std::string NameToFilename(const std::string src);
//generate DTD (only if asked) and XSD
void GenerateDSD(const ::Uml::Namespace &ns,
		 const string &fname,
		 bool generate_dtd,
		 bool uxsdi,
		 bool xsd_el_ta,
		 const map<string, string> &ns_map,
		 const set<string> &ns_ignore_set,
		 bool qualifiedAtrrsNS);

#endif //MOBIES_UDM_H
