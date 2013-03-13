#ifndef PythonAPIGen_H
#define PythonAPIGen_H

#include <Uml.h>
#include <UmlExt.h>
#include <fstream>

using namespace std;

class PythonAPIGen
{
  public:
    //! Constructor.
    PythonAPIGen( const ::Uml::Diagram &diagram
      , const map<string, string>& ns_map
      , const string& inputfile );

    //! Destructor.
    ~PythonAPIGen( void );
    
    //! Entry point of Python API generation.
    void  generate( );

  private:  
    void open();
	void generateClass(::Uml::Class &cls);
	void generateAttributes(::Uml::Class &cls);
	void generateChildrenAccess(::Uml::Class &cls);
	void generateAssociations(::Uml::Class &cls);

  private:
    //! The UDM UML diagram.
    const ::Uml::Diagram & m_diagram;

    //! Namespace directory.
    const map<string, string>& m_ns_map;

    //! The input UDM XML file.
    const string & m_inputfile;

    ofstream m_output;



};
#endif //PythonAPIGen_H
