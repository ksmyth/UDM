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
#include "UdmUtil.h"

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

void GenerateDSD(const ::Uml::Namespace &ns, const UdmOpts &opts, bool qualified_attrs_ns)
{
	if (!ns) return;
	ofstream ff;
	string nsfname = NameToFilename(ns.getPath2("_"));

	if (opts.generate_dtd)
	{
		ff.open( (nsfname+".dtd").c_str() );
		if(!ff.good()) throw udm_exception("Error opening for write " + nsfname + ".dtd");
		else DTDGen::GenerateDTD(ns, ff);
		ff.close();
		ff.clear();
	}

	ff.open( (nsfname+".xsd").c_str() );
	if(!ff.good()) throw udm_exception("Error opening for write " + nsfname + ".xsd");
	else DTDGen::GenerateXMLSchema(ns, ff, opts.ns_map, opts.ns_ignore, opts.uxsdi, opts.xsd_el_ta, qualified_attrs_ns);
	ff.close();
}

void GenerateDSD(const ::Uml::Diagram &dgr, const string &fname, const UdmOpts &opts, bool qualified_attrs_ns)
{
	ofstream ff;

	if (opts.generate_dtd)
	{
		ff.open( (fname + ".dtd").c_str() );
		if(!ff.good()) throw udm_exception("Error opening for write " + fname + ".dtd");
		else DTDGen::GenerateDTD(dgr, ff);
		ff.close();
		ff.clear();
	}

	ff.open( (fname+".xsd").c_str() );
	if(!ff.good()) throw udm_exception("Error opening for write " + fname + ".xsd");
	else DTDGen::GenerateXMLSchema(dgr, ff, opts.ns_map, opts.ns_ignore, opts.uxsdi, opts.xsd_el_ta, qualified_attrs_ns);
	ff.close();
}

void CPPSetURIMapping(const ::Uml::Diagram &diagram, 
                      const map<string, string>& ns_map,
                      ostream &output)
{
	if (!ns_map.empty())
	{
		output << "\n\t\t// URI namespace mapping for dom backend, udm was invoked with switch -u" << "\n";
		map<string, string>::const_iterator it =  ns_map.begin();
		for(;it != ns_map.end(); ++it)
		{
			const std::string& ns=it->first;
			const std::string& uri=it->second;
			std::string xsdname = (string)diagram.name() + "_" + UdmUtil::replace_delimiter(ns, "::", "_") + ".xsd";

			output << "\t\t" << "UdmDom::AddURIToUMLNamespaceMapping(\""<< uri<<"\",\""<<ns<<"\",\""<<xsdname<<"\" );" << std::endl;
		}
	}
}

void CPPSetXsdStorage(const ::Uml::Diagram &diagram, ostream &output)
{
	::Uml::DiagramNamespaces nses(diagram);
	for (::Uml::DiagramNamespaces::iterator nses_i = nses.begin(); nses_i != nses.end(); ++nses_i)
	{
		const ::Uml::Namespace& ns = *nses_i;
		const std::string& nsn = NameToFilename(ns.getPath2("_"));
		std::string infname(nsn + std::string(".xsd"));

		File2Code f2c(".//", nsn + std::string("_xsd"), infname, File2Code::CPP);
		f2c.gen();
		output << "\t\t" << "UdmDom::str_xsd_storage::StoreXsd(\"" << nsn << ".xsd\", " << nsn <<"_xsd::getString());"<< endl;
	}
	const string& dgrn = diagram.name();
	string infname(dgrn + ".xsd");
	File2Code f2c(".//", dgrn + "_xsd", infname, File2Code::CPP);
	f2c.gen();
	output << "\t\t" << "UdmDom::str_xsd_storage::StoreXsd(\"" << dgrn << ".xsd\", " << dgrn <<"_xsd::getString());"<< endl << endl;
}

void CPPIncludeXsdHeaders(const ::Uml::Diagram &diagram, ostream & output)
{
	output << "#include \"UdmDom.h\"" << endl; 
	output << "#include \"" << diagram.name() << "_xsd.h\"" << endl;
	::Uml::DiagramNamespaces nses(diagram);
	for (::Uml::DiagramNamespaces::iterator nses_i = nses.begin(); nses_i != nses.end(); nses_i++)
	{
		::Uml::Namespace ns = *nses_i;	
		output << "#include \"" << NameToFilename(ns.getPath2("_")) << "_xsd.h\"" << endl << endl; 
	}
	output << endl;
}

string UmlClassCPPName(const ::Uml::Class &cl)
{
	return "::" + cl.getPath2("::");
}

string UmlClassCPPName(const ::Uml::Class &cl, const ::Uml::Namespace &ns)
{
	if ((::Uml::Namespace) cl.parent_ns() == ns)
		return cl.name();
	else
		return "::" + cl.getPath2("::");
}

string join(const string &sep, const vector<string> &v)
{
	string result;

	vector<string>::const_iterator it_begin = v.begin();
	vector<string>::const_iterator it_end = v.end();

	if (it_begin != it_end) {
		result += *it_begin;
		it_begin++;
	}

	for (; it_begin != it_end; it_begin++) {
		result += sep;
		result += *it_begin;
	}

	return result;
}
