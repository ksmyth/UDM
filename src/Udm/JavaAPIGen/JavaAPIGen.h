#ifndef JavaAPIGen_H
#define JavaAPIGen_H
#include <Uml.h>

class JavaAPIGen
{
public:
  JavaAPIGen(void);
  ~JavaAPIGen(void);
  void  generate(const ::Uml::Uml::Diagram &diagram, 
                    const map<std::string, std::string>& ns_map, 
                    const std::string& inputfile);
};
#endif //JavaAPIGen_H
