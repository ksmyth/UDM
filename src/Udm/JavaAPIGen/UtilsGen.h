#ifndef UtilsGen_H
#define UtilsGen_H

#include <Uml.h>
#include <fstream>

using namespace std;

class UtilsGen
{
  public:
    //! Constructor.
    UtilsGen(const ::Uml::Namespace &ns
      , const string & package_name
      , const map<string, string> & ns_map);

    //! Destructor.
    ~UtilsGen( void );
    
    //! Entry point of domainspecific factory class generation.
    void  generate( );

  private:  
    //! Generate function that wraps a pseudoobject in a domain specific object.
    void wrapper( );

    //! Creates and opens the JAVA source file.
    void open( );
    void close( );

    //! Generates the header of the source file.
    void header( );

  private:
    //! The namespace of this factory.
    const ::Uml::Namespace & m_ns;

    //! The name of the package for the generated Java file.
    const string m_package_name;

    //! Namespace direcotry.
    const map<string, string>& m_ns_map;

   //! The name of the namespace
   const string m_ns_name;

   //! Destination utils file.
   ofstream m_output;

};
#endif //UtilsGen_H
