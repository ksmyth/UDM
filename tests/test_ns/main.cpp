// test_ns.cpp : Defines the entry point for the console application.
//


#include "test_ns.h"

void writeTest(const std::string& fname)
{

	Udm::SmartDataNetwork  out(test_ns::diagram);
  out.CreateNew(fname.c_str(), "AB.xsd",	test_ns::AB::AB::meta, Udm::CHANGES_PERSIST_ALWAYS);

  test_ns::AB::AB ab = test_ns::AB::AB::Cast(out.GetRootObject());
  test_ns::test_ns::B1 b1 = test_ns::test_ns::B1::Create(ab);
  test_ns::AB::AB1 ab1 = test_ns::AB::AB1::Create(ab);

	out.CloseWithUpdate();
}

//==========================================
void readTest(const std::string& fname)
{

	Udm::SmartDataNetwork  out(test_ns::diagram);
  out.OpenExisting(fname.c_str(), "test_ns.xsd");

  
  test_ns::AB::AB ab = test_ns::AB::AB::Cast(out.GetRootObject());

	
  out.CloseNoUpdate();
}
//=========================================

void main()
{
  try
  {
    std::string fn ="test.xml";
    //writeTest(fn);
    readTest(fn);
  }
  catch(udm_exception& e)
  {
    std::cout << e.what();
  }

	
}

