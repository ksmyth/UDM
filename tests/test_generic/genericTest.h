
#ifndef GENERICTEST_H
#define GENERICTEST_H

#include <cppunit/extensions/HelperMacros.h>
asdfsdf
namespace UdmTests
{
	class genericTest : public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE( genericTest );
		CPPUNIT_TEST( testDOMDOM );
		CPPUNIT_TEST( testDOMMGA );
		CPPUNIT_TEST( testDOMMEM );
		CPPUNIT_TEST( testMGADOM );
		CPPUNIT_TEST( testMGAMGA );
		CPPUNIT_TEST( testMGAMEM );
		CPPUNIT_TEST( testMEMMEM );
		CPPUNIT_TEST( testMEMDOM );
		CPPUNIT_TEST( testMEMMGA );
		CPPUNIT_TEST_SUITE_END();

		
	private:
		const char * getRndFileName();
		bool generictest(const char *, const char *);	//returns false if failed
		public:
		void testDOMDOM();
		void testDOMMGA();
		void testDOMMEM();
		void testMEMDOM();
		void testMEMMGA();
		void testMEMMEM();
		void testMGADOM();
		void testMGAMGA();
		void testMGAMEM();
	};
};
#endif  // GENERICTEST_H
