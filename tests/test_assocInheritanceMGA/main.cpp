#include "SignalFlow.h"

#ifdef _WIN32
UDM_USE_MGA
#endif

//UDM_USE_DOM


#include <Uml.h>
#include <UdmStatic.h>
#include <UmlExt.h>
#include <UdmBase.h>

#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>

#include "AssociationInheritanceTest.h"

int main(int argc, char* argv[])
{

	// Create the event manager and test controller
	CPPUNIT_NS::TestResult controller;

	// Add a listener that colllects test results
	CPPUNIT_NS::TestResultCollector result;
	controller.addListener( &result );        

	// Add a listener that prints dots as tests run.
	CPPUNIT_NS::TextTestProgressListener progress;
	controller.addListener( &progress ); 

	CPPUNIT_NS::TestRunner runner;
	runner.addTest( CAssociationInheritanceTest::suite() );
	runner.run(controller,"");

	// Print test results in a compiler like format.
    CPPUNIT_NS::CompilerOutputter outputter( &result, std::cerr );
    outputter.write(); 


	return 0;
}



