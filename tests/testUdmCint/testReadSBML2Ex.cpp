#include "Test.h"
#ifdef _WIN32
#include <afx.h>
#endif
#include <stdexcept>
#include <sstream>
#include <UdmBase.h>
#include <UdmCintSwig.h>
#include <fstream>


#include "SBML2Ex_xsd.h"
#include "SBML2Ex_math_xsd.h"
#include "SBML2Ex_sbml_xsd.h"
#include "SBML2Ex_dbi_xsd.h"
#include "SBML2Ex_unigene_xsd.h"
#include "SBML2Ex_xhtml_xsd.h" 
#include "SBML2Ex_flux_xsd.h"
#include "SBML2Ex_jigcell_xsd.h"
#include "SBML2Ex_jd_xsd.h"
#include "SBML2Ex_bc_xsd.h"

void StoreXSD(const std::string& nn, const std::string& xsd)
{
  cint_string xsdn(nn.c_str());
  cint_string cxsd(xsd.c_str());

  if(!StoreXsd(xsdn,cxsd))
   {
     std::cout << nn <<std::endl;
     std::cout << __LINE__ <<std::endl;

     exit(1);
     
   }
}

 void AddURI(const std::string& uri, const std::string& ns)
 {

   cint_string xsdn(uri.c_str());
   cint_string cxsd(ns.c_str());

  if(!AddURIToUMLNamespaceMapping(xsdn,cxsd))
   {
     std::cout << uri <<std::endl;
     std::cout << __LINE__ <<std::endl;
     exit(1);
   }

 }

void UdmTests::Test::testReadSBML2Ex(const std::string& fname)
{
  char metaname[] = "SBML2Ex";
  char ns[] = "SBML2Ex";
  char diagram_file[] = "SBML2Ex_udm.xml";



  UdmPseudoObject diagram;

  std::ifstream ind(diagram_file);
  
  std::string dxml;
  readFromFile(ind, dxml);

    
  if(!UPO_LoadDiagramFromString(diagram_file,dxml.c_str(), diagram))
  {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
   }
/*


  if(!UPO_LoadDiagram(diagram_file,diagram))
  {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
   }
*/

  /*
  UdmPseudoObject swigNewUPO = new UdmPseudoObject();
  UDMCint.UPO_SetClass(swigNewUPO,diagram,"Gene");
UdmPseudoObject swigNewUPO = new UdmPseudoObject();
UDMCint.UPO_SetClass(swigNewUPO,diagram,"Container");
UdmPseudoObject swigNewUPO = new UdmPseudoObject();
UDMCint.UPO_SetClass(swigNewUPO,diagram,"TF");
UdmPseudoObject swigNewUPO = new UdmPseudoObject();
UDMCint.UPO_SetClass(swigNewUPO,diagram,"Regulation");
  */

  UdmBool b(false);
  UdmPseudoDataNetwork dn(metaname, b);

  StoreXSD("SBML2Ex_sbml.xsd", SBML2Ex_sbml_xsd::getString().c_str());
  StoreXSD("SBML2Ex_math.xsd", SBML2Ex_math_xsd::getString().c_str());
  StoreXSD("SBML2Ex_dbi.xsd", SBML2Ex_dbi_xsd::getString().c_str());
  StoreXSD("SBML2Ex_unigene.xsd", SBML2Ex_unigene_xsd::getString().c_str());
  StoreXSD("SBML2Ex_xhtml.xsd" , SBML2Ex_xhtml_xsd::getString().c_str());
  StoreXSD("SBML2Ex_flux.xsd", SBML2Ex_flux_xsd::getString().c_str());
  StoreXSD("SBML2Ex_jigcell.xsd", SBML2Ex_jigcell_xsd::getString().c_str());
  StoreXSD("SBML2Ex_jd.xsd", SBML2Ex_jd_xsd::getString().c_str());
  StoreXSD("SBML2Ex_bc.xsd", SBML2Ex_bc_xsd::getString().c_str());
  StoreXSD("SBML2Ex.xsd", SBML2Ex_xsd::getString().c_str());

  AddURI("http://www.sbml.org/2001/ns/biocharon","bc");
  AddURI("http://www.dbi.tju.edu/xmlns/dbi","dbi");
  AddURI("http://arep.med.harvard.edu/fluxns","flux");
  AddURI("http://mpf.biol.vt.edu/ns","jigcell");
  AddURI("http://www.w3.org/1998/Math/MathML","math");
  AddURI("http://www.sbml.org/sbml/level2","sbml");
  AddURI("http://www.dbi.tju.edu/xmlns/unigene","unigene");
  AddURI("http://www.w3.org/1999/xhtml","xhtml");

 string xml;
 std::ifstream inxml(fname.c_str());
 readFromFile(inxml, xml);
 if(!dn.OpenExistingFromString(xml.c_str(),"SBML2Ex_sbml.xsd"))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
     
   }


   cint_string res;
   if(!dn.OCL_Evaluate(res))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
     
   }
  
   cout << string(res.buffer()) << endl;
  


  UPO_UnLoadDiagram(diagram_file);
}
