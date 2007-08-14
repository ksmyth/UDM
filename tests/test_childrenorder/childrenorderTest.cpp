// cintstringTest.cpp


#include <UdmBase.h>
#include <cint_string.h>
#include "childrenorderTest.h"
#include "LampDiagram.h"

// Registers the fixture into the 'registry'

CPPUNIT_TEST_SUITE_REGISTRATION( UdmTests::childrenorderTest );

#define WIN_TEMP_ENV "TEMP"
#define WIN_TMP_ENV "TMP"

using namespace LampDiagram::LampDiagram;

const char * UdmTests::childrenorderTest::getRndFileName()
{
#ifdef WIN32
		char * def_tmp_dir = "c:\\";
#else
		char * def_tmp_dir = "/tmp/";
#endif
		
		char * tmp_dir = NULL;
		tmp_dir = getenv(WIN_TEMP_ENV);
		if (!tmp_dir)
			tmp_dir = getenv(WIN_TMP_ENV);
		
		if (!tmp_dir) tmp_dir = def_tmp_dir;
		
		//create a temporary folder and set the path
		//char t_dir_name[L_tmpnam +1];
		char * t_dir_name;
#ifdef WIN32
		t_dir_name = _tempnam(tmp_dir, "UDM");
#else	//WIN32
		t_dir_name = tempnam(tmp_dir, "UDM");
#endif

		return t_dir_name;
};

bool UdmTests::childrenorderTest::ordertest(const char * dgr_name)
{

	Udm::SmartDataNetwork nw(LampDiagram::diagram);

	nw.CreateNew(dgr_name,"LampDiagram", RootFolder::meta);

	{
		RootFolder rrr = RootFolder::Cast(nw.GetRootObject());
		Lamp lamp = Lamp::Create(rrr);
		lamp.name() = "Host Lamp ";
		lamp.ModelName() = "Sequence tester lamp";


		Bulb bulb1  = Bulb::Create(lamp);
		bulb1.name() = "Bulb 1";
		bulb1.Wattage() = 100;
		bulb1.Voltage() = 10;


		Bulb bulb2  = Bulb::Create(lamp);
		bulb2.name() = "Bulb 2";
		bulb2.Wattage() = 200;
		bulb2.Voltage() = 20;


		Bulb bulb3  = Bulb::Create(lamp);
		bulb3.name() = "Bulb 3";
		bulb3.Wattage() = 300;
		bulb3.Voltage() = 30;

		Plug pl = Plug::Create(lamp);


	}
	nw.CloseWithUpdate();
	nw.OpenExisting(dgr_name, "LampDiagram");
	{
		RootFolder rrr = RootFolder::Cast(nw.GetRootObject());
		set<Lamp> lamps = rrr.Lamp_kind_children();
		Lamp lamp = *(lamps.begin());

		//checking the order of the Bulbs
		vector<Bulb> bulbs = lamp.Bulb_children();
		CPPUNIT_ASSERT(bulbs[0].Voltage() == 10);
		CPPUNIT_ASSERT(bulbs[1].Voltage() == 20);
		CPPUNIT_ASSERT(bulbs[2].Voltage() == 30);

		//inverting order
		
		vector<Bulb> new_vector;
		vector<Bulb>::reverse_iterator bulb_ri = bulbs.rbegin();
		while (bulb_ri != bulbs.rend())
		{
			new_vector.push_back(*bulb_ri);
			++bulb_ri;
		}
		lamp.Bulb_children() = new_vector;

		//checking the order of the Bulbs
		bulbs = lamp.Bulb_children();
		
		CPPUNIT_ASSERT(bulbs[0].Voltage() == 30);
		CPPUNIT_ASSERT(bulbs[1].Voltage() == 20);
		CPPUNIT_ASSERT(bulbs[2].Voltage() == 10);

		
		//taking out from the middle - that's index 1
		Bulb middle_b = bulbs[1];
		bulbs = lamp.Bulb_children() -= middle_b;
		
		
		//checking the order of the Bulbs
		bulbs = lamp.Bulb_children();
		CPPUNIT_ASSERT(bulbs[0].Voltage() == 30);
		CPPUNIT_ASSERT(bulbs[1].Voltage() == 10);
	
		
		//adding back to the  end 
		middle_b = Bulb::Create(lamp);
		middle_b.name() = "Bulb 2 recreated";
		middle_b.Wattage() =2000;
		middle_b.Voltage() = 200;

		
		//checking the order of the bulbs
		bulbs = lamp.Bulb_children();
		
		
		CPPUNIT_ASSERT(bulbs[0].Voltage() == 30);
		CPPUNIT_ASSERT(bulbs[1].Voltage() == 10);
		CPPUNIT_ASSERT(bulbs[2].Voltage() == 200);
		
	}
	nw.CloseWithUpdate();

	return false;
};

void UdmTests::childrenorderTest::testDOM()
{
	const char * fname = getRndFileName();
	std::string fname_std = std::string(fname) + ".xml";
	ordertest(fname_std.c_str());
};

void UdmTests::childrenorderTest::testMEM()
{
	const char * fname = getRndFileName();
	std::string fname_std = std::string(fname) + ".mem";
	ordertest(fname_std.c_str());
};
