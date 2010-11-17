#include "RefPortsTest.h"
#include "RefPort.h"
#include <iostream>

#include <UdmUtil.h>

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
	Root root_refs2 = Root::Create(rf);
	root_refs2.name() = "root_refs2";

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

	BRef bref2 = BRef::Create(root_refs2);
	bref2.name() = "bref2";

	BRef bref3 = BRef::Create(root_refs);
	bref3.name() = "bref3";

	aref1.ref() = apar;
	bref.ref() = bpar;
	bref2.ref() = bpar2;
	bref3.ref() = bref2;

	A a = A::Create(apar);
	a.name() = "a";

	B b = B::Create(bpar);
	b.name() = "b";

	B b2 = B::Create(bpar2);
	b2.name() = "b2";

	C c = C::Create(root_refs);
	c.name() = "c";


	c.a_rp_container() = aref1;
	c.b_rp_container() = bref;

	// the refport containers are not visible until the port is connected
	CPPUNIT_ASSERT(ARef1::Cast(c.a_rp_container()) == Udm::null);
	CPPUNIT_ASSERT(BRef::Cast(c.b_rp_container()) == Udm::null);

	c.a_end_end() = a;
	c.b_end_end() = b;
	
	// the preferences are now visible
	CPPUNIT_ASSERT(ARef1::Cast(c.a_rp_container()) == aref1);
	CPPUNIT_ASSERT(BRef::Cast(c.b_rp_container()) == bref);

	ARef1 aref1_ = ARef1::Cast(c.a_rp_container());
	std::set<C> conns = aref1_.a_rp_container_rev();
	CPPUNIT_ASSERT_EQUAL((size_t)1, conns.size());
	cout << conns.begin()->name();
	CPPUNIT_ASSERT_EQUAL(c, *conns.begin());

	// we change the preference, but the visible one does not change since
	// the port has not been changed
	c.b_rp_container() = bref3;
	CPPUNIT_ASSERT(BRef::Cast(c.b_rp_container()) == bref);

	// after port change, the preference becomes visible
	c.b_end_end() = b2;
	CPPUNIT_ASSERT(BRef::Cast(c.b_rp_container()) == bref3);


	{
		C::b_end_chain_t r = c.b_end_chain();
		C::b_end_chain_t::second_type v = r.second;
		CPPUNIT_ASSERT(B::Cast(r.first) == b2);
		cerr << "Connecting chain between c and b2: " << v.size() << endl;
		for (vector<Udm::Object>::const_iterator i = v.begin(); i != v.end(); i++) {
			cout << "chain item: " << UdmUtil::ExtractName(*i) << "[" << i->uniqueId() << "]" << endl;
		}
	}

	{
		vector<Udm::Object> r = b2.getConnectingChain(B::meta_a_end_rev, c);
		cerr << "Connecting chain between b2 and c: " << r.size() << endl;
		for (vector<Udm::Object>::const_iterator i = r.begin(); i != r.end(); i++) {
			cout << "chain item: " << UdmUtil::ExtractName(*i) << "[" << i->uniqueId() << "]" << endl;
		}
	}

	{
		C::a_end_chain_t r = c.a_end_chain();
		C::a_end_chain_t::second_type v = r.second;
		cerr << "Connecting chain between c and a: " << v.size() << endl;
		for (vector<Udm::Object>::const_iterator i = v.begin(); i != v.end(); i++) {
			cout << "chain item: " << UdmUtil::ExtractName(*i) << "[" << i->uniqueId() << "]" << endl;
		}
	}

	{
		vector<Udm::Object> r = a.getConnectingChain(A::meta_b_end_rev, c);
		cerr << "Connecting chain between a and c: " << r.size() << endl;
		for (vector<Udm::Object>::const_iterator i = r.begin(); i != r.end(); i++) {
			cout << "chain item: " << UdmUtil::ExtractName(*i) << "[" << i->uniqueId() << "]" << endl;
		}
	}

	// disconnect src
	c.a_end_chain().disconnect();
	CPPUNIT_ASSERT(A::Cast(c.a_end_end()) == &Udm::_null);
	CPPUNIT_ASSERT(B::Cast(c.b_end_end()) == b2);

	// disconnect dst
	b2.disconnectFrom(B::meta_a_end_rev, c);
	CPPUNIT_ASSERT(B::Cast(c.b_end_end()) == &Udm::_null);


	c.a_end_end() = a;

	// connect dst using references chain
	vector<Udm::Object> v1_refs;
	v1_refs.push_back(bref3);
	v1_refs.push_back(bref2);
	c.b_end_chain() = make_pair(b2, v1_refs);
	CPPUNIT_ASSERT(B::Cast(c.b_end_end()) == b2);

	// disconnect dst
	c.b_end_chain().disconnect();
	CPPUNIT_ASSERT(B::Cast(c.b_end_end()) == &Udm::_null);

	// connect another dst using references chain
	v1_refs.clear();
	v1_refs.push_back(bref);
	c.b_end_chain() = make_pair(b, v1_refs);
	CPPUNIT_ASSERT(B::Cast(c.b_end_end()) == b);

	// disconnect dst
	c.b_end_chain().disconnect();
	CPPUNIT_ASSERT(B::Cast(c.b_end_end()) == &Udm::_null);


	// connect dst using reference port helper
	c.b_rp_container() = bref;
	//c.connectTo(C::meta_b_end_end_, b);
	c.b_end_chain() = b;
	CPPUNIT_ASSERT(B::Cast(c.b_end_end()) == b);

	// disconnect dst
	c.b_end_chain().disconnect();
	CPPUNIT_ASSERT(B::Cast(c.b_end_end()) == &Udm::_null);

	// connect another dst using reference port helper
	c.b_rp_container() = bref3;
	//c.connectTo(C::meta_b_end_end_, b2);
	c.b_end_chain() = b2;
	CPPUNIT_ASSERT(B::Cast(c.b_end_end()) == b2);
	 
	dn.CloseWithUpdate();
}
