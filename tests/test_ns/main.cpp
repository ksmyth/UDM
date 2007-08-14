// test_ns.cpp : Defines the entry point for the console application.
//

#include "test_ns.h"

void writeTest(const std::string& fname)
{

	Udm::SmartDataNetwork  out(test_ns::diagram);
	out.CreateNew(fname.c_str(), "test_ns_AB.xsd",	test_ns::AB::AB::meta, Udm::CHANGES_PERSIST_ALWAYS);

	test_ns::AB::AB ab = test_ns::AB::AB::Cast(out.GetRootObject());

	test_ns::A::A1 a1 = test_ns::A::A1::Create(ab);
	test_ns::A::AA::A1 a_aa1 = test_ns::A::AA::A1::Create(ab);
	test_ns::B::B1 b1 = test_ns::B::B1::Create(ab);
	test_ns::AB::AB1 ab1 = test_ns::AB::AB1::Create(ab);
	test_ns::A::AA::A2 a2 = test_ns::A::AA::A2::Create(ab);
	test_ns::AB::ABAB::AB2 ab2 = test_ns::AB::ABAB::AB2::Create(ab, test_ns::AB::AB::meta_ab2);

	ab2.dst() += a2;

	out.CloseWithUpdate();
}

//==========================================
void readTest(const std::string& fname)
{

	Udm::SmartDataNetwork  out(test_ns::diagram);
	out.OpenExisting(fname.c_str(), "test_ns_AB.xsd");

	test_ns::AB::AB ab = test_ns::AB::AB::Cast(out.GetRootObject());

	out.CloseNoUpdate();
}
//=========================================

int main()
{
  try
  {
    std::string fn ="test.xml";
    writeTest(fn);
    readTest(fn);
  }
  catch(udm_exception& e)
  {
    std::cout << e.what();
    return 1;
  }

  return 0;
}

