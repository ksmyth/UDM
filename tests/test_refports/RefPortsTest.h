#ifndef REFPORTSTEST_H
#define REFPORTSTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace UdmTests
{
	class refPortsTest : public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE( refPortsTest );
		CPPUNIT_TEST( testRefPorts );
		CPPUNIT_TEST_SUITE_END();

	public:
		void testRefPorts();
	};
};

#endif // REFPORTSTEST_H