
#include  <UdmBase.h>
#include  <UdmDom.h>
#include  "Test.h"


int main(int argc, char* argv[])
{
  UdmTests::Test t;
  t.test();
}
/*
CPPUNIT_TEST_SUITE_REGISTRATION( UdmTests::Test );
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
*/