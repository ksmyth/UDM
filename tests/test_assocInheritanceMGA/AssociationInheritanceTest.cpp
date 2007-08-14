// AssociationInheritanceTest.cpp: implementation of the AssociationInheritanceTest class.
//
//////////////////////////////////////////////////////////////////////

#include "AssociationInheritanceTest.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

using namespace SignalFlow;

CAssociationInheritanceTest::CAssociationInheritanceTest()
{

}

CAssociationInheritanceTest::~CAssociationInheritanceTest()
{

}

void CAssociationInheritanceTest::TestAssociationInheritance()
{
	try {
	Udm::SmartDataNetwork nw1(diagram);
	nw1.OpenExisting("sf1.mga");

	RootFolder rf = RootFolder::Cast(nw1.GetRootObject());
	set<CompoundComponent> cps = rf.CompoundComponent_children();
	CompoundComponent cp = *(cps.begin());
	
	set<LocalPort> lps = cp.LocalPort_children();
	LocalPort lp = *(lps.begin());

	set<BaseSignal> bsfs = lp.dst();
	BaseSignal bsf = *(bsfs.begin());
	//cout<<(string)bsf.type().name()<<endl;    //It is supposed to be Signal
	Signal sf = Signal::Cast(bsf);	//It failed, before bug was fixed would throw invalid cast

	nw1.CloseNoUpdate();
	CPPUNIT_ASSERT(true /*made it here with no Exception*/);
	}

	catch(const udm_exception &e)	{
		cout << endl << "Exception: " << e.what()  << endl;
		CPPUNIT_ASSERT(false /* Exception occured */);
	} 
}

void CAssociationInheritanceTest::setUp()
{
}

void CAssociationInheritanceTest::tearDown()
{
}
