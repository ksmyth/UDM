#ifndef ClassGen_H
#define ClassGen_H

#include <Uml.h>
#include <fstream>

using namespace std;

class ClassGen
{
  public:
    //! Constructor.
    ClassGen(const ::Uml::Class &cl
      , const string & pckg_name
      , const string & diag_name
      , const string & ns_name);

    //! Destructor.
    ~ClassGen( void );
    
    //! Entry point of domain-specific class generation.
    void  generate( );

  private:  
    //! Creates and opens the JAVA source file.
    void open( );
    void close( );

    //! Generates the header of the source file.
    void header( );

    //! Generates the constructor for this class.
    void constructor( );

    //! Find the base class. Note: java does not support multiple inheritance.
    void findBaseClass( );

    //! Generates the function that returns the meta class for non-abstract classes.
    void getMetaClass( );

    //! Generates the composition roles ( create ).
    void construction( );
    
    //! Generates containments ( createChild + getXXXChildren ).
    void accessChildren( );
    
    //! Generates attribute setters and getters.
    void accessAttributes( );

    //! Generate association functions.
    void associations( );

  private:
    //! The UML representation of this class.
    const ::Uml::Class & m_cl;

    //! The name of the package for the generated Java file.
    const string m_package_name;

   //! The name of the diagram
   const string m_diag_name;

   //! Destination class file.
   ofstream m_output;

  //! Tha name of the class.
  const string m_cl_name;

  //! The name of the namespace of the class (lower case).
  const string m_ns_name;

  //! The name of the namespace of the class (unchanged).
  const string m_ns_name_orig;

  // The name of the base class of this class.
  string m_base_name;
};
#endif //ClassGen_H
