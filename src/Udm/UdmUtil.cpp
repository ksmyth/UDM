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
#include "File2Code/File2Code.h"

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
	if (!ns) return;
	ofstream ff;
	string nsfname = (string)((::Uml::Diagram)ns.parent()).name() + "_" + (string)ns.name();

	if (generate_dtd)
	{
		ff.open( (nsfname+".dtd").c_str() );
		if(!ff.good()) throw udm_exception("Error opening for write " + nsfname + ".dtd");
		else DTDGen::GenerateDTD(ns, ff);
		ff.close();
		ff.clear();
	}

	ff.open( (nsfname+".xsd").c_str() );
	if(!ff.good()) throw udm_exception("Error opening for write " + nsfname + ".xsd");
	else DTDGen::GenerateXMLSchema(ns, ff, ns_map, ns_ignore_set, uxsdi, xsd_el_ta, qualifiedAtrrsNS);
	ff.close();
}

void GenerateDSD(const ::Uml::Diagram &dgr,
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
		ff.open( (fname + ".dtd").c_str() );
		if(!ff.good()) throw udm_exception("Error opening for write " + fname + ".dtd");
		else DTDGen::GenerateDTD(dgr, ff);
		ff.close();
		ff.clear();
	}

	ff.open( (fname+".xsd").c_str() );
	if(!ff.good()) throw udm_exception("Error opening for write " + fname + ".xsd");
	else DTDGen::GenerateXMLSchema(dgr, ff, ns_map, ns_ignore_set, uxsdi, xsd_el_ta, qualifiedAtrrsNS);
	ff.close();
}

bool SingleCPPNamespace(const ::Uml::Diagram &diagram)
{
	return ((set < ::Uml::Namespace>) diagram.namespaces()).size() == 0;
}

bool SingleCPPNamespace(const ::Uml::Namespace &ns)
{
	return ns == ::Uml::Namespace(NULL);
}

bool SingleCPPNamespace(const ::Uml::Class &cl)
{
	return (::Uml::Namespace)cl.parent_ns() == ::Uml::Namespace(NULL);
}

::Uml::Class GetCrossClass(const ::Uml::Diagram &cross_dgr, const ::Uml::Class &cl)
{
	::Uml::Namespace ns = cl.parent_ns();
	string cross_cl_name = string(cl.name()) + string(Udm::cross_delimiter);
	if (ns)
		cross_cl_name += (string)ns.name();
	return ::Uml::classByName(cross_dgr, cross_cl_name);
}

void CPPSetXsdStorage(const ::Uml::Diagram &diagram, ostream &output)
{
	set< ::Uml::Namespace> nses = diagram.namespaces();
	for (set< ::Uml::Namespace>::const_iterator nses_i = nses.begin(); nses_i != nses.end(); ++nses_i)
	{
		const ::Uml::Namespace& ns = *nses_i;
		const std::string& nsn = (string)diagram.name() + "_" + (string)ns.name();
		std::string infname(nsn + std::string(".xsd"));

		File2Code f2c(nsn + std::string("_xsd"), infname, File2Code::CPP);
		std::string outfname(nsn + std::string("_xsd.h"));
		std::ofstream out(outfname.c_str());
		f2c.gen(out);
		out.close();
		output << "\t\t" << "UdmDom::str_xsd_storage::StoreXsd(\"" << nsn << ".xsd\", " << nsn <<"_xsd::getString());"<< endl;
	}
	const string& dgrn = diagram.name();
	string infname(dgrn + ".xsd");
	File2Code f2c(dgrn + "_xsd", infname, File2Code::CPP);
	string outfname(dgrn + "_xsd.h");
	std::ofstream out(outfname.c_str());
	f2c.gen(out);
	out.close();
	output << "\t\t" << "UdmDom::str_xsd_storage::StoreXsd(\"" << dgrn << ".xsd\", " << dgrn <<"_xsd::getString());"<< endl << endl;
}

void CPPIncludeXsdHeaders(const ::Uml::Diagram &diagram, ostream & output)
{
	output << "#include \"UdmDom.h\"" << endl; 
	output << "#include \"" << diagram.name() << "_xsd.h\"" << endl;
	set< ::Uml::Namespace> nses = diagram.namespaces();
	for (set< ::Uml::Namespace>::iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
	{
		::Uml::Namespace ns = *nses_i;	
		output << "#include \"" << diagram.name() << "_" << ns.name() << "_xsd.h\"" << endl << endl; 
	}
	output << endl;
}
