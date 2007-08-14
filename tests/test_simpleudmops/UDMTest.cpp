// UDMTest.cpp: implementation of the CUDMTest class.
//
//////////////////////////////////////////////////////////////////////


#include "UDMTest.h"
#include <cppunit/Message.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUDMTest::CUDMTest():m_xmlfile(LampDiagram::diagram)
{

}

CUDMTest::~CUDMTest()
{

}

void CUDMTest::setUp()
{
	
}

void CUDMTest::tearDown()
{
	//close the network, so later tests can open it
	if(m_xmlfile.isOpen()) m_xmlfile.CloseWithUpdate(); 
}

void CUDMTest::TestFileCreation()
{
	m_xmlfile.CreateNew( "abc.xml", "LampDiagram.xsd", LampDiagram::LampDiagram::RootFolder::meta);
		
	CPPUNIT_ASSERT((m_root = LampDiagram::LampDiagram::RootFolder::Cast(m_xmlfile.GetRootObject())));
}

void CUDMTest::TestObjectCreation()
{
	m_xmlfile.OpenExisting( "abc.xml", "LampDiagram.xsd");
	m_root = LampDiagram::LampDiagram::RootFolder::Cast(m_xmlfile.GetRootObject());

	//test that each item is successfully created
	CPPUNIT_ASSERT((m_lamp = LampDiagram::LampDiagram::Lamp::Create(m_root)));
	CPPUNIT_ASSERT((m_bulb = LampDiagram::LampDiagram::Bulb::Create(m_lamp)));
	CPPUNIT_ASSERT((m_switch = LampDiagram::LampDiagram::Switch::Create(m_lamp,LampDiagram::LampDiagram::Lamp::meta_MainSwitch)));
	CPPUNIT_ASSERT((m_plug = LampDiagram::LampDiagram::Plug::Create(m_lamp)));
	CPPUNIT_ASSERT((m_term1 = LampDiagram::LampDiagram::ElectricTerminal::Create(m_plug)));
	CPPUNIT_ASSERT((m_term2 = LampDiagram::LampDiagram::ElectricTerminal::Create(m_bulb)));
}

void CUDMTest::TestExistingNetwork()
{
	GetNetwork();
	//test that GetNetwork got all the objects created in TestObjectCreation
	CPPUNIT_ASSERT(m_root);
	CPPUNIT_ASSERT(m_lamp);
	CPPUNIT_ASSERT(m_bulb);
	CPPUNIT_ASSERT(m_switch);
	CPPUNIT_ASSERT(m_plug);
	CPPUNIT_ASSERT(m_term1);
	CPPUNIT_ASSERT(m_term2);
}

void CUDMTest::TestAttributes()
{
	
	GetNetwork();

	//test attribute setting
	CPPUNIT_ASSERT(m_bulb.Voltage() = 115);
	CPPUNIT_ASSERT(m_bulb.Wattage() = 60);

	//test attribute checking
	CPPUNIT_ASSERT( m_bulb.Voltage() == 115);
	CPPUNIT_ASSERT( m_bulb.Wattage() == 60 );
	CPPUNIT_ASSERT( m_bulb.Voltage() != 100);
	CPPUNIT_ASSERT( m_bulb.Wattage() != 75 );
}

void CUDMTest::TestConnection()
{
	GetNetwork();

	//create connections
	CPPUNIT_ASSERT(m_wire = LampDiagram::LampDiagram::Wire::Create(m_lamp));
	CPPUNIT_ASSERT(m_link = LampDiagram::LampDiagram::ControlLink::Create(m_lamp));

	//connect the connection ends
	CPPUNIT_ASSERT(m_wire.End1_end() = m_term1);
	CPPUNIT_ASSERT(m_wire.End2_end() = m_term2);
	CPPUNIT_ASSERT(m_link.src_end() = m_bulb);
	CPPUNIT_ASSERT(m_link.dst_end() = m_switch);

	//check the connection ends
	CPPUNIT_ASSERT( LampDiagram::LampDiagram::Bulb::Cast(m_link.src_end()) == m_bulb);
	CPPUNIT_ASSERT( LampDiagram::LampDiagram::Switch::Cast(m_link.dst_end()) == m_switch );
	CPPUNIT_ASSERT( LampDiagram::LampDiagram::ElectricTerminal::Cast(m_wire.End1_end()) == m_term1);
	CPPUNIT_ASSERT( LampDiagram::LampDiagram::ElectricTerminal::Cast(m_wire.End2_end()) == m_term2);
}

void CUDMTest::TestObjectDestruction()
{
	GetNetwork();

	m_bulb.DeleteObject();
	CPPUNIT_ASSERT( (Udm::Object::Cast(m_bulb.parent())==Udm::null));
	//CPPUNIT_ASSERT( !(m_bulb) );//== LampDiagram::LampDiagram::Bulb(NULL));
	//CPPUNIT_ASSERT( !(m_term2)); //m_term2 was a child of m_bulb

	m_term2 = LampDiagram::LampDiagram::ElectricTerminal::Create(Udm::null); //will throw udm_exception that cppunit expects

}

void CUDMTest::GetNetwork()
{
	//cppunit uses a separate instance of this class to run each test
	//rebuild the existing network
	m_xmlfile.OpenExisting( "abc.xml", "LampDiagram.xsd");
	m_root = LampDiagram::LampDiagram::RootFolder::Cast(m_xmlfile.GetRootObject());
	set<LampDiagram::LampDiagram::Lamp> lamps = m_root.Lamp_kind_children();
	m_lamp = *(lamps.begin());
	set<LampDiagram::LampDiagram::Bulb> bulbs = m_lamp.Bulb_kind_children();
	m_bulb = *(bulbs.begin());
	set<LampDiagram::LampDiagram::Plug> plugs = m_lamp.Plug_kind_children();
	m_plug = *(plugs.begin());
	set<LampDiagram::LampDiagram::Switch> switches = m_lamp.Switch_kind_children();
	m_switch = *(switches.begin());
	set<LampDiagram::LampDiagram::ElectricTerminal> terms = m_plug.ElectricTerminal_kind_children();
	m_term1 = *(terms.begin());
	terms = m_bulb.ElectricTerminal_kind_children();
	m_term2 = *(terms.begin());
}