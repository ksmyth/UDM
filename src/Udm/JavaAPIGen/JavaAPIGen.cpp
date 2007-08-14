#include ".\javaapigen.h"

void GenerateJava(const ::Uml::Uml::Diagram &diagram
, const map<string, string> & ns_map
, const string& inputfile);


JavaAPIGen::JavaAPIGen(void)
{
}

JavaAPIGen::~JavaAPIGen(void)
{
}
//================================================
void JavaAPIGen::generate(const ::Uml::Uml::Diagram &diagram, 
                  const map<std::string, std::string>& ns_map, 
                  const std::string& inputfile)
{
  GenerateJava(diagram,ns_map, inputfile);

}
