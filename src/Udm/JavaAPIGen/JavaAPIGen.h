#ifndef JavaAPIGen_H
#define JavaAPIGen_H
#include <Uml.h>

class JavaAPIGen
{
  public:
    JavaAPIGen(const ::Uml::Uml::Diagram &diagram
      , const map<std::string, std::string>& ns_map
      , const std::string& inputfile);
    ~JavaAPIGen(void);
    void  generate();

  private:
    const ::Uml::Uml::Diagram & m_diagram;
    const map<std::string, std::string>& m_ns_map;
    const std::string& m_inputfile;
};
#endif //JavaAPIGen_H
