#include "JavaAPIGen.h"

void GenerateJava(const ::Uml::Uml::Diagram &diagram
, const map<string, string> & ns_map
, const string& inputfile);


JavaAPIGen::JavaAPIGen(const ::Uml::Uml::Diagram &diagram
                       , const map<std::string, std::string>& ns_map
                       , const std::string& inputfile)
                       : m_diagram(diagram)
                       , m_ns_map(ns_map)
                       , m_inputfile(inputfile)
{
}

JavaAPIGen::~JavaAPIGen(void)
{
}
//================================================
void JavaAPIGen::generate()
{
  GenerateJava(m_diagram, m_ns_map, m_inputfile);

}
