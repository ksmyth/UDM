#include "CrossLinkTester.h"
//#include "CLPackage.h"
#include "CL.h"
#include "CD1.h"
#include "CD2.h"
#include "CD3.h"

CPPUNIT_TEST_SUITE_REGISTRATION( UdmTests::CrossLinkTester );

//using namespace Package1;
//using namespace Package2;
using namespace CD1;
using namespace CD2;
using namespace CD3;
using namespace std;

void UdmTests::CrossLinkTester::test()
{
	try {
		Udm::UdmProject prj;
		//specifying instance data networks which will be present in the project
		Udm::DataNetworkSpecifier cd1_dn("CD1_inst.xml", "CD1", M1::meta);
		Udm::DataNetworkSpecifier cd2_dn("CD2_inst.xml", "CD2", M2::meta);
		Udm::DataNetworkSpecifier cd3_dn("CD3_inst.xml", "CD3", MM3::meta);
		//Udm::DataNetworkSpecifier BdnsP1("Package1_inst.xml", "CD1", ClassA::meta);
		//Udm::DataNetworkSpecifier dnsP2("Package2_inst.xml", "CD2", Class1::meta);
		vector<Udm::DataNetworkSpecifier> dnsvec;
		dnsvec.push_back(cd1_dn);
		dnsvec.push_back(cd2_dn);
		dnsvec.push_back(cd3_dn);
		//creating a Udm Project
		prj.CreateNew("test.udm", dnsvec, CL::diagram, Udm::CHANGES_LOST_DEFAULT);
		//obtaining handles to the datanetworks which were created
		Udm::DataNetwork& p1 = prj.GetDataNetwork("CD1_inst.xml");
		Udm::DataNetwork& p2 = prj.GetDataNetwork("CD2_inst.xml");
		Udm::DataNetwork& p3 = prj.GetDataNetwork("CD3_inst.xml");
		//obtaining handles to the root objects (this is normal - existing - Udm operation)
		CD1::M1 m1 = CD1::M1::Cast( p1.GetRootObject());
		CD2::M2 m2 = CD2::M2::Cast( p2.GetRootObject());
		CD3::MM3 m3 = CD3::MM3::Cast( p3.GetRootObject());
		// create Class2
		//M2 class2= M2::Create( m2);
		// create Class3
		//NSp::NSc::Class3 class3 = NSp::NSc::Class3::Create(rootP2);
		//MM3 class3 = MM3::Create( m2);
		// create cross links
		//rootP1.dst1()= rootP2;
		//rootP1.dst1()= class3;
		//rootP1.dst2()= class2;
		//rootP1.dst3()+= class3;
		
		// verification
		set<CD1::M1> a;
		m2.dst() = m1;
		a.insert(m1);
		m3.src() = a;

		CD1::M1 m1_too = m2.dst();
		CPPUNIT_ASSERT( m1 == m1_too);
		set<CD1::M1> a_too = m3.src();
		CPPUNIT_ASSERT(a_too.size() == a.size());
		CPPUNIT_ASSERT(a_too.begin() != a.find(m1));



		//std::set< Class1> dst1s= rootP1.dst();
		//CPPUNIT_ASSERT( dst1s.size() == 2);
		//CPPUNIT_ASSERT( dst1s.find( rootP2) != dst1s.end());
		//CPPUNIT_ASSERT( dst1s.find( class2) != dst1s.end());
		//const Class2& dst2= rootP1.dst2();
		//CPPUNIT_ASSERT( dst2 == class2);
		//std::set< NSp::NSc::Class3> dst3s = rootP1.dst3();
		//CPPUNIT_ASSERT( dst3s.size() == 1);
		//CPPUNIT_ASSERT( dst3s.find( class3) != dst3s.end());
	} catch( udm_exception &e)
	{
		std::cout << e.what() << std::endl;
		CPPUNIT_ASSERT( false);
	}
}



