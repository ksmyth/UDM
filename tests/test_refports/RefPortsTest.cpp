#include "RefPortsTest.h"
#include "RefPort.h"
#include <iostream>

// Registers the fixture into the 'registry'

CPPUNIT_TEST_SUITE_REGISTRATION( UdmTests::refPortsTest );

using namespace RefPort;
using namespace Udm;

void UdmTests::refPortsTest::testRefPorts()
{
	Udm::SmartDataNetwork dn(RefPort::diagram);
	dn.CreateNew("RefPortInst.mga", "RefPort", RootFolder::meta, Udm::CHANGES_PERSIST_ALWAYS);

	//creating root folder
	RootFolder rf = RootFolder::Cast(dn.GetRootObject());
	rf.name() = "RootFolder";


	//creating root models
	Root root = Root::Create(rf);
	root.name() = "root";
	Root root_refs = Root::Create(rf);
	root_refs.name() = "root_refs";

	APar apar = APar::Create(root);
	apar.name() = "apar";

	BPar bpar = BPar::Create(root);
	bpar.name() = "bpar";

	BPar bpar2 = BPar::Create(root);
	bpar2.name() = "bpar2";

	ARef1 aref1 = ARef1::Create(root_refs);
	aref1.name() = "aref1";

	BRef bref = BRef::Create(root_refs);
	bref.name() = "bref";

	BRef bref2 = BRef::Create(root_refs);
	bref2.name() = "bref2";

	aref1.ref() = apar;
	bref.ref() = bpar;
	bref2.ref() = bpar2;

	A a = A::Create(apar);
	a.name() = "a";

	B b = B::Create(bpar);
	b.name() = "b";

	B b2 = B::Create(bpar2);
	b2.name() = "b2";

	C c = C::Create(root_refs);
	c.name() = "c";

	c.a_end__rp_helper() = aref1;
	c.b_end__rp_helper() = bref;

	// the preferences are not visible until the port is connected
	CPPUNIT_ASSERT(ARef1::Cast(c.a_end__rp_helper()) == Udm::null);
	CPPUNIT_ASSERT(BRef::Cast(c.b_end__rp_helper()) == Udm::null);

	c.a_end_end() = a;
	c.b_end_end() = b;
	
	// the preferences are now visible
	CPPUNIT_ASSERT(ARef1::Cast(c.a_end__rp_helper()) == aref1);
	CPPUNIT_ASSERT(BRef::Cast(c.b_end__rp_helper()) == bref);

	// we change the preference, but the visible one does not change since
	// the port has not been changed
	c.b_end__rp_helper() = bref2;
	CPPUNIT_ASSERT(BRef::Cast(c.b_end__rp_helper()) == bref);

	// after port change, the preference becomes visible
	c.b_end_end() = b2;
	CPPUNIT_ASSERT(BRef::Cast(c.b_end__rp_helper()) == bref2);

	dn.CloseWithUpdate();
}
