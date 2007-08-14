/*
Copyright (c) Vanderbilt University, 2000-2005
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

#include "Udm.h"
#include "UdmBase/DTDGen.h"

#include <time.h>
#include <fstream>

std::string GetTime()	{
		time_t t;
		time(&t);
		char *c = ctime(&t);

		c[24] = '\0';
		return c;
}

std::string NameToFilename(const std::string src)
{
	std::string ret = src;
	for (std::string::iterator i = ret.begin(); i != ret.end(); i++) {
		if (!isalnum(*i)) *i = '_';
	}
	return ret;
}

void GenerateDSD(const ::Uml::Namespace &ns,
		 const string &fname,
		 bool generate_dtd,
		 bool uxsdi,
		 bool xsd_el_ta,
		 const map<string, string> &ns_map,
		 const set<string> &ns_ignore_set,
		 bool qualifiedAtrrsNS)
{
	ofstream ff;

	if (generate_dtd)
	{
		ff.open( (fname+".dtd").c_str() );
		if(!ff.good()) throw udm_exception("Error opening for write " + fname + ".dtd");
		else DTDGen::GenerateDTD(ns, ff);
		ff.close();
		ff.clear();
	}

	ff.open( (fname+".xsd").c_str() );
	if(!ff.good()) throw udm_exception("Error opening for write " + fname + ".xsd");
	else DTDGen::GenerateXMLSchema(ns, ff, ns_map, ns_ignore_set, uxsdi, xsd_el_ta, qualifiedAtrrsNS);
	ff.close();
}

bool SingleCPPNamespace(const ::Uml::Diagram &diagram)
{
	set< ::Uml::Namespace> nses = diagram.namespaces();
	set< ::Uml::Namespace>::iterator nses_i = nses.begin();

	return nses.size() == 1 && (string) diagram.name() == (string) nses_i->name();
}


bool SingleCPPNamespace(const ::Uml::Namespace &ns)
{
	return SingleCPPNamespace(ns.parent());
}

bool SingleCPPNamespace(const ::Uml::Class &cl)
{
	return SingleCPPNamespace(((::Uml::Namespace)cl.parent()).parent());
}
