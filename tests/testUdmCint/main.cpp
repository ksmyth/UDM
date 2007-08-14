#include "Test.h"
#include <afx.h>
#include <sstream>
#include <UdmBase.h>
#define CS_IN_UDMCINT
#include <UdmCintSwig.h>
#include <fstream>
#include "GeneTFxsd.h"
#include "Umlxsd.h"

void UdmTests::Test::readFromFile(std::istream& in, std::string& str)
{
	if (!in.good())
	{
    std::string err;
    err += " could not open";
    throw std::runtime_error(err.c_str());
	}


  while(in.good())
  {
    std::string s;
    std::getline(in, s);
    str += s + "\n";
  }

}
//===========================


void UdmTests::Test::testRead(const std::string& result)
{
  char metaname[] = "GeneTF";
  char ns[] = "GeneTF";
  char diagram_file[] = "GeneTF_udm.xml";
  char xsd_name[] = "GeneTF.xsd";

  UdmPseudoObject diagram;
  
  if(!UPO_LoadDiagram(diagram_file,diagram))
  {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
   }

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

  cint_string xsdn(xsd_name);
  cint_string xsd(getGeneTFxsd().c_str());

  if(!StoreXsd(xsdn,xsd))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
     
   }

/*
  std::string xml;
  std::ifstream inx("test2.xml");
  
  readFromFile(inx, xml);
*/
 if(!dn.OpenExistingFromString(result.c_str(),xsdn.buffer()))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
     
   }

//   if(!dn.OpenExisting("test2.xml",xsdn.buffer(),2))
//   {
//     cint_string str;
//     diagram.GetLastError(str);
//     std::cout << str.buffer() <<std::endl;
//     
//   }

  UdmPseudoObject root;
  if(!dn.GetRootObject(root))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
     
   }
  cint_string type;
  root.type(type);
  std::cout << type.buffer() << std::endl;

  UdmLong length(1);

  if(!root.getChildrenCount("","Gene","GeneTF", length))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
     
   }


  int size = (int)length.longVal;
  std::cout << size <<std::endl;
  UdmPseudoObjectS cont(size);

  if(!root.getChildren("","Gene","GeneTF", cont))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
     
   }

 
  for(int i= 0; i< cont.GetLength(); i++)
  {
    UdmPseudoObject& g = cont[i];

   cint_string str;
   if (!g.GetStrVal("name",str))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
     
   }
 
   std::cout << "Gene " << str.buffer() << " regulates : ";
    UdmLong length(1);

    if(!g.getAssociationCount("tf", length))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
     
   }


      int size = (int)length.longVal;
      std::cout << size << " ";
      UdmPseudoObjectS asscont(size);

      if(!g.getAssociation("tf",asscont))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
     
   }
    


      for(int ii= 0; ii< asscont.GetLength(); ii++)
      {
        UdmPseudoObject ga = asscont[ii];
/*
#ifdef _DEBUG
    CMemoryState oldMemState, newMemState, diffMemState;
    oldMemState.Checkpoint();
    {
#endif
*/
       cint_string str;
       ga.GetStrVal("name",str);
//        if (!ga.GetStrVal("name",str))
//        {
//         cint_string str;
//         diagram.GetLastError(str);
//         std::cout << str.buffer() <<std::endl;
//         exit(1);
//        }
       std::cout <<  str.buffer() << " " ;        
/*
#ifdef _DEBUG
    }
    newMemState.Checkpoint();
    if( diffMemState.Difference( oldMemState, newMemState ) )
    {
      diffMemState.DumpStatistics();

      std::cout << "\n---Memory leaked!\n" ;
    }
#endif
*/
      }//end ass


      std::cout <<  std::endl;        




    }//end gene
  RemoveXsd(xsdn);
  UPO_UnLoadDiagram(diagram_file);
}
//============================
void UdmTests::Test::testWrite(std::string& result)
{
  char metaname[] = "GeneTF";
  char ns[] = "GeneTF";
  char diagram_file[] = "GeneTF_udm.xml";
  char xsd_name[] = "GeneTF.xsd";


  UdmPseudoObject diagram;

  StoreXsd("Uml.xsd",cint_string (getUmlxsd().c_str()));

  if(!  UPO_LoadDiagram(diagram_file,diagram))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
     
   }
  

  cint_string xsdn(xsd_name);
  cint_string xsd(getGeneTFxsd().c_str());

  StoreXsd(xsdn,xsd);
  


  UdmBool b(false);
  
  UdmPseudoDataNetwork dn(metaname, b);

  
  UdmPseudoObject nsUPO;
  if(!UPO_SetNamespace(nsUPO,diagram,ns))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
   }
  
  UdmPseudoObject rootUPO;
  if(!UPO_SetClass(rootUPO,nsUPO,"Container"))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
   }
  
/*
  if(!dn.CreateNew("lofax.xml",xsdn.buffer(),rootUPO))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
   }
*/
 if(!dn.CreateNewToString(xsdn.buffer(),rootUPO))
  {
    cint_string str;
    diagram.GetLastError(str);
    std::cout << str.buffer() <<std::endl;
    
  }

  UdmPseudoObject root;
  if(!dn.GetRootObject(root))
  {
    cint_string str;
    diagram.GetLastError(str);
    std::cout << __LINE__ <<std::endl;
    std::cout << str.buffer() <<std::endl;
    exit(1);
  }

  int gn = 10;
  for (int i = 0; i < gn; ++i)
  {
    UdmPseudoObject gene;
   
    if(!root.CreateObject("Gene", ns, gene))
    {
      cint_string str;
      diagram.GetLastError(str);
      std::cout << __LINE__ <<std::endl;
      std::cout << str.buffer() <<std::endl;
      exit(1);
    }
    std::stringstream ss;
    ss << "gene_"<<i;
    gene.SetStrVal("name",ss.str().c_str());

    UdmPseudoObject tf;
   
    if(!root.CreateObject("TF", ns, tf))
    {
      cint_string str;
      diagram.GetLastError(str);
      std::cout << __LINE__ <<std::endl;
      std::cout << str.buffer() <<std::endl;
      exit(1);
    }

    std::stringstream sst;
    sst << "tf_"<<i;
    tf.SetStrVal("name",sst.str().c_str());


     UdmPseudoObject reg;
     if(!root.CreateObject("Regulation", ns, reg))
     {
      cint_string str;
      diagram.GetLastError(str);
      std::cout << __LINE__ <<std::endl;
      std::cout << str.buffer() <<std::endl;
      exit(1);
    }
  
  /*
  UdmPseudoObjectS asscont(1);
  asscont[0] = tf;
  if(!reg.setAssociation("tf",asscont,Udm::TARGETFROMCLASS))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
     
   }
   asscont[0] = gene;
   if(!reg.setAssociation("gene",asscont,Udm::TARGETFROMCLASS))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
     
   }

*/
    UdmPseudoObjectS asscont(1);
    asscont[0] = reg;

    if(!gene.setAssociation("tf",asscont,Udm::CLASSFROMTARGET))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
     
   }
    
    if(!tf.setAssociation("gene",asscont,Udm::CLASSFROMTARGET))
   {
     cint_string str;
     diagram.GetLastError(str);
     std::cout << __LINE__ <<std::endl;
     std::cout << str.buffer() <<std::endl;
     exit(1);
     
   }

  }//gene       

  if(!  dn.CloseWithUpdate())
  {
    cint_string str;
    diagram.GetLastError(str);
    std::cout << __LINE__ <<std::endl;
    std::cout << str.buffer() <<std::endl;
    exit(1);
  }

  cint_string buffer;

  if(!dn.SaveAsString(buffer))
  {
    cint_string str;
    diagram.GetLastError(str);
    std::cout << __LINE__ <<std::endl;
    std::cout << str.buffer() <<std::endl;
    exit(1);
  }

  result = string(buffer.buffer());
  std::ofstream out("lofax.xml");
  out << result << std::endl;
  
  UPO_UnLoadDiagram(diagram_file);

}


CPPUNIT_TEST_SUITE_REGISTRATION( UdmTests::Test );

void UdmTests::Test::test()
{

 //writeAPI();
 std::string result;
 testWrite(result);
 testRead(result);

 
}

int main(int argc, char* argv[])
{
	CPPUNIT_NS::Test *suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();

	// Adds the test to the list of test to run
	CPPUNIT_NS::TextUi::TestRunner runner;
	runner.addTest( suite );

	// Change the default outputter to a compiler error format outputter
	runner.setOutputter( new CPPUNIT_NS::CompilerOutputter( &runner.result(),
                                                       std::cerr ) );
	// Run the test.
	bool wasSucessful = runner.run();

	// Return error code 1 if the one of test failed.
	return wasSucessful ? 0 : 1;
	
}
