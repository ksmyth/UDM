// cintstringTest.cpp


#include <UdmBase.h>
#include <cint_string.h>
#include "genericTest.h"
#include "LampDiagram.h"

// Registers the fixture into the 'registry'

CPPUNIT_TEST_SUITE_REGISTRATION( UdmTests::genericTest );

#define WIN_TEMP_ENV "TEMP"
#define WIN_TMP_ENV "TMP"


UDM_USE_DOM

#ifdef _WIN32
UDM_USE_MGA
#endif

using namespace LampDiagram;

const char * UdmTests::genericTest::getRndFileName()
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

bool UdmTests::genericTest::generictest(const char * src, const char * dst)
{

	Udm::SmartDataNetwork nw(LampDiagram::diagram);

		nw.CreateNew(src,"LampDiagram", RootFolder::meta);

		{
			RootFolder rrr = RootFolder::Cast(nw.GetRootObject());
			int count = 0;
			for (count = 0; count < 1; count++)
			{
				cout << "." ;
				Lamp doubleBulbLamp = Lamp::Create(rrr);

				
				vector<__int64> a;
				a.push_back(0x1234567890abcdefLL);	//64bit integer
				a.push_back(7);
				a.push_back(1);
				
				doubleBulbLamp.ArrayInt() = a;
				
				
				//testing already set attributes
				CPPUNIT_ASSERT(doubleBulbLamp.ArrayInt()[0] == 1);
				CPPUNIT_ASSERT(doubleBulbLamp.ArrayInt()[1] == 7);
				CPPUNIT_ASSERT(doubleBulbLamp.ArrayInt()[2] == 0x1234567890abcdefLL);
				//getting non-existing items - they should be zero
				CPPUNIT_ASSERT(doubleBulbLamp.ArrayInt()[4] == 0);
			
				
				
			
				//testing non-persistent array attributes
				doubleBulbLamp.TempArrayInt() = a;			//assign
				a = doubleBulbLamp.TempArrayInt();			//retrieve
				//test
				CPPUNIT_ASSERT(a[0] == 1);
				CPPUNIT_ASSERT(a[1] == 7);
				CPPUNIT_ASSERT(a[2] == 0x1234567890abcdefLL);
				//getting non-existing items - they should be zero
				CPPUNIT_ASSERT(doubleBulbLamp.TempArrayInt()[4] == 0);
			
			
				vector<double> b;
				b.push_back(2.4);
				b.push_back(1.1);
				b.push_back(3.141592653589793234);
				doubleBulbLamp.ArrayReal() = b;

				//the attribute is ordered array, the order is also checked
				CPPUNIT_ASSERT(doubleBulbLamp.ArrayReal()[0] == 1.1);
				CPPUNIT_ASSERT(doubleBulbLamp.ArrayReal()[1] == 2.4);
				CPPUNIT_ASSERT(doubleBulbLamp.ArrayReal()[2] == 3.141592653589793234);
				//getting non-existing items - they should be zero
				CPPUNIT_ASSERT(doubleBulbLamp.ArrayReal()[4] == 0);
			

				//testing non-persistent array attributes
				doubleBulbLamp.TempArrayReal() = b;			//assign
				b = doubleBulbLamp.TempArrayReal();			//retrieve

				CPPUNIT_ASSERT(b[0] == 1.1);
				CPPUNIT_ASSERT(b[1] == 2.4);
				CPPUNIT_ASSERT(b[2] == 3.141592653589793234);
				
				vector<bool> c;
				c.push_back(true);
				c.push_back(true);
				c.push_back(false);
				doubleBulbLamp.ArrayBool() = c;
				//ordered boolean array, that means that first the falses, then the trues
				CPPUNIT_ASSERT(doubleBulbLamp.ArrayBool()[0] == false);
				CPPUNIT_ASSERT(doubleBulbLamp.ArrayBool()[1] == true);
				CPPUNIT_ASSERT(doubleBulbLamp.ArrayBool()[2] == true);
				//unset index should be 0, which means false
				CPPUNIT_ASSERT(doubleBulbLamp.ArrayBool()[4] == false);
			
				

				//testing non-persistent array attributes
				doubleBulbLamp.TempArrayBoolean() = c;			//assign
				c = doubleBulbLamp.TempArrayBoolean();			//retrieve
				CPPUNIT_ASSERT(c[0] == false);
				CPPUNIT_ASSERT(c[1] == true);
				CPPUNIT_ASSERT(c[2] == true);
				
				
				vector<string> d;
				d.push_back("apple");
				d.push_back("orange");
				d.push_back("hello");
				d.push_back("semi;colon");
				d.push_back("doublesemi;;colon");
				d.push_back("triplesemi;;;colon");
				d.push_back("back\\slash");
				d.push_back("double back\\\\slash");
				d.push_back("triple back\\\\\\slash");
				d.push_back("triple semi-coloback\\;\\;\\;slash-1");
				d.push_back("triple semi-coloback\\\\\\;;;slash-2");
				doubleBulbLamp.ArrayStr() = d;
				
				CPPUNIT_ASSERT((string)doubleBulbLamp.ArrayStr()[0] == "apple");
				CPPUNIT_ASSERT((string)doubleBulbLamp.ArrayStr()[1] == "back\\slash");
				CPPUNIT_ASSERT((string)doubleBulbLamp.ArrayStr()[2] == "double back\\\\slash");
				CPPUNIT_ASSERT((string)doubleBulbLamp.ArrayStr()[3] == "doublesemi;;colon");
				CPPUNIT_ASSERT((string)doubleBulbLamp.ArrayStr()[4] == "hello");
				CPPUNIT_ASSERT((string)doubleBulbLamp.ArrayStr()[5] == "orange");
				CPPUNIT_ASSERT((string)doubleBulbLamp.ArrayStr()[6] == "semi;colon");
				CPPUNIT_ASSERT((string)doubleBulbLamp.ArrayStr()[7] == "triple back\\\\\\slash");
				CPPUNIT_ASSERT((string)doubleBulbLamp.ArrayStr()[8] == "triple semi-coloback\\;\\;\\;slash-1");
				CPPUNIT_ASSERT((string)doubleBulbLamp.ArrayStr()[9] == "triple semi-coloback\\\\\\;;;slash-2");
				CPPUNIT_ASSERT((string)doubleBulbLamp.ArrayStr()[10] == "triplesemi;;;colon");
				

							
				//testing non-persistent array attributes
				doubleBulbLamp.TempArrayStr() = d;			//assign
				d = doubleBulbLamp.TempArrayStr();			//retrieve
				//display
				CPPUNIT_ASSERT(d[0] == "apple");
				CPPUNIT_ASSERT(d[1] == "back\\slash");
				CPPUNIT_ASSERT(d[2] == "double back\\\\slash");
				CPPUNIT_ASSERT(d[3] == "doublesemi;;colon");
				CPPUNIT_ASSERT(d[4] == "hello");
				CPPUNIT_ASSERT(d[5] == "orange");
				CPPUNIT_ASSERT(d[6] == "semi;colon");
				CPPUNIT_ASSERT(d[7] == "triple back\\\\\\slash");
				CPPUNIT_ASSERT(d[8] == "triple semi-coloback\\;\\;\\;slash-1");
				CPPUNIT_ASSERT(d[9] == "triple semi-coloback\\\\\\;;;slash-2");
				CPPUNIT_ASSERT(d[10] == "triplesemi;;;colon");
				





				char lamp_name[70]; 
				sprintf(lamp_name, "HighLight XL150 instance no. %d, here follows end-of line:\n", count);
				doubleBulbLamp.name() = lamp_name;
				
				doubleBulbLamp.MaxVoltageRating() = 220.0; 
				doubleBulbLamp.MaxTempRating()    = 200; 
				ElectricTerminal termA = ElectricTerminal::Create(doubleBulbLamp);
				ElectricTerminal termB = ElectricTerminal::Create(doubleBulbLamp);
				termA.position() = "(500,20)";
				termB.position() = "(500,85)";

			
				Plug thePlug = Plug::Create(doubleBulbLamp);
				thePlug.position() = "(500,150)";
				thePlug.name() = "Plug";
				ElectricTerminal plt1 = ElectricTerminal::Create(thePlug);
				plt1.position() = "(20,100)";
				ElectricTerminal plt2 = ElectricTerminal::Create(thePlug);
				plt2.position() = "(20,200)";

		// create mainswitch and its terminals
				Switch mainSwitch = Switch::Create(doubleBulbLamp, Lamp::meta_MainSwitch);
				mainSwitch.position() = "(300,100)";
				mainSwitch.name() = "MainSW";
				ElectricTerminal mst1 = ElectricTerminal::Create(mainSwitch);
				mst1.position() = "(20,100)";
				ElectricTerminal mst2 = ElectricTerminal::Create(mainSwitch);
				mst2.position() = "(220,100)";

		//create switches and its terminals
				Switch switch1 = Switch::Create(doubleBulbLamp, Lamp::meta_FunctionSwitch);
				switch1.position() = "(300,250)";
				switch1.name() = "SW1";
				ElectricTerminal s1t1 = ElectricTerminal::Create(switch1);
				s1t1.position() = "(20,100)";
				ElectricTerminal s1t2 = ElectricTerminal::Create(switch1);
				s1t2.position() = "(220,100)";

				Switch switch2 = Switch::Create(doubleBulbLamp, Lamp::meta_FunctionSwitch);
				switch2.position() = "(300,250)";
				switch2.name() = "SW 2";
				ElectricTerminal s2t1 = ElectricTerminal::Create(switch2);
				s2t1.position() = "(20,100)";
				ElectricTerminal s2t2 = ElectricTerminal::Create(switch2);
				s2t2.position() = "(220,100)";


				Switch switch3 = Switch::Create(doubleBulbLamp, Lamp::meta_FunctionSwitch);
				switch3.position() = "(300,250)";
				switch3.name() = "Halogen switch";
				ElectricTerminal s3t1 = ElectricTerminal::Create(switch3);
				s3t1.position() = "(20,100)";
				ElectricTerminal s3t2 = ElectricTerminal::Create(switch3);
				s3t2.position() = "(220,100)";


			

	// Create bulbs with terminals
				Bulb bulb1	= Bulb::Create(doubleBulbLamp); 
				bulb1.name() = "Bulb1";
				bulb1.position() = "(100,150)";
				ElectricTerminal b1t1 = ElectricTerminal::Create(bulb1);
				b1t1.position() = "(220,100)";
				ElectricTerminal b1t2 = ElectricTerminal::Create(bulb1);
				b1t2.position() = "(220,200)";

				Bulb bulb2	= Bulb::Create(doubleBulbLamp); 
				bulb2.name() = "Bulb2";
				bulb2.position() = "(100,150)";
				ElectricTerminal b2t1 = ElectricTerminal::Create(bulb2);
				b2t1.position() = "(220,100)";
				ElectricTerminal b2t2 = ElectricTerminal::Create(bulb2);
				b2t2.position() = "(220,200)";
	
	//test inherited parentroles & childroles

				HalogenBulb bulb3 = HalogenBulb::Create(doubleBulbLamp, Lamp::meta_Bulb_children);
				bulb3.name() = "HalogenBulb3";
				bulb3.position() = "(100, 150)";
				ElectricTerminal b3t1 = ElectricTerminal::Create(bulb3, HalogenBulb::meta_ElectricTerminal_children);
				b3t1.position() = "(320,100)";
				ElectricTerminal b3t2 = ElectricTerminal::Create(bulb3);
				b3t2.position() = "(320,200)";
	







		// wire up the lamp
		//create wires in the lamp
				
				Wire w1 = Wire::Create(doubleBulbLamp);
				Wire w2 = Wire::Create(doubleBulbLamp);
				Wire w3 = Wire::Create(doubleBulbLamp);
				Wire w4 = Wire::Create(doubleBulbLamp);
				Wire w5 = Wire::Create(doubleBulbLamp);
				Wire w6 = Wire::Create(doubleBulbLamp);
				Wire w7 = Wire::Create(doubleBulbLamp);
				Wire w8 = Wire::Create(doubleBulbLamp);
				Wire w9 = Wire::Create(doubleBulbLamp);
				Wire w10 = Wire::Create(doubleBulbLamp);






		//connect them

				//live onnections
				//#1: connect plug 1 to main switch input
				//this is one way to connect it!

				w1.End1_end() = plt1;
				w1.End2_end() = mst1;


				//#2, #3: connect main switch output to sw1, sw2 inputs
				w2.End1_end() = mst2;
				w2.End2_end() = s1t1;

				w3.End1_end() = mst2;
				w3.End2_end() = s2t1;

				w10.End1_end() = mst2;
				w10.End2_end() = s3t1;
			
			
				//#4: connect sw1 output to bulb 1
				w4.End1_end() = s1t2;
				w4.End2_end() = b1t1;

				//#5: connect sw2 output to bulb 2
				w5.End1_end() = s2t2;
				w5.End2_end() = b2t1;

				//#8: connect sw3 output to halogenbulb
				w8.End1_end() = s3t2;
				w8.End2_end() = b3t1;


				//ground connections:
				//#6, #7 connect plug 2 to bulbs
				w6.End1_end() = plt2;
				w6.End2_end() = b1t2;

				w7.End1_end() = plt2;
				w7.End2_end() = b2t2;

				w9.End1_end() = plt2;
				w9.End2_end() = b3t2;

	// assign values to a few attrs		
			
				w1.Amps() = 3.5;
				w2.Amps() = 4;
				w3.Amps() = 5;
				w4.Amps() = 11;
				w5.Amps() = 12;
				w6.Amps() = 13;
				w7.Amps() = 15.0;
				w8.Amps() = 14.0;
				w9.Amps() = 16.0;
				w10.Amps() = 17.0;



				bulb1.Wattage() = 55;
				bulb2.Wattage() = 155;
				bulb3.Wattage() = 200;

				//this should got  a default value
				//doubleBulbLamp.ModelName() = "SuperDoubleLight 155";

				s1t1.Type() = string("Copper");
				s1t2.Type() = string("Aluminium");
				

				//creating control links

				ControlLink cl1 = ControlLink::Create(doubleBulbLamp);
				cl1.name() = "Bulb 1 switcher";

				//one way to set associations:
				//cl1.src_end() = bulb1;
				//cl1.dst_end() = switch1;
			
	
			
				//the other way to set associations would be
				set<ControlLink> s_cl;
				s_cl.insert(cl1);
				bulb1.dst() = s_cl;
				switch1.src() = s_cl;
	

				ControlLink cl2 = ControlLink::Create(doubleBulbLamp);
				cl2.src_end() = bulb2;
				cl2.dst_end() = switch2;
				cl2.name() = "Bulb 2 switcher";

				ControlLink cl3 = ControlLink::Create(doubleBulbLamp);
				cl3.src_end() = bulb3;
				cl3.dst_end() = switch3;
				cl3.name() = "Halogen Bulb  switcher";



			
				set<ControlLink> lks = doubleBulbLamp.ControlLink_kind_children();
				set<ControlLink>::iterator l1;

				for(l1 = lks.begin(); l1 != lks.end(); l1++) 
				{
					bool bvar11 = ((*l1 == cl1) && (Bulb(l1->src_end()) == bulb1));
					bool bvar12 = ((*l1 == cl1) && (Switch(l1->dst_end()) == switch1));

					bool bvar21 = ((*l1 == cl2) && (Bulb(l1->src_end()) == bulb2));
					bool bvar22 = ((*l1 == cl2) && (Switch(l1->dst_end()) == switch2));

					bool bvar31 = ((*l1 == cl3) && (Bulb(l1->src_end()) == bulb3));
					bool bvar32 = ((*l1 == cl3) && (Switch(l1->dst_end()) == switch3));

					bool bvar1 = bvar11 && bvar12;
					bool bvar2 = bvar21 && bvar22;
					bool bvar3 = bvar31 && bvar32;

					if (bvar1)	CPPUNIT_ASSERT((!bvar2 && !bvar3));
					if (bvar2)	CPPUNIT_ASSERT((!bvar3 && !bvar1));
					if (bvar3)	CPPUNIT_ASSERT((!bvar1 && !bvar2));

				}
				

				set<Bulb> s_bulb = doubleBulbLamp.Bulb_kind_children();
				CPPUNIT_ASSERT (s_bulb.size() == 3);

				for(set<Bulb>::iterator s_bulb_i = s_bulb.begin(); s_bulb_i != s_bulb.end(); s_bulb_i++)
				{
					set<ControlLink> s_cls = s_bulb_i->dst();
					ControlLink cll = *s_cls.begin();
					vector<Udm::ObjectImpl*> sw_ois = s_bulb_i->__impl()->getAssociation(Bulb::meta_dst, Udm::TARGETFROMPEER);
					Switch peer_switch(*sw_ois.begin());
					
					CPPUNIT_ASSERT(s_cls.size() == 1);
					CPPUNIT_ASSERT(sw_ois.size() == 1);
					CPPUNIT_ASSERT(peer_switch);
					CPPUNIT_ASSERT(cl1);

					CPPUNIT_ASSERT (peer_switch == Switch(cll.dst_end()));
			
				}

				//deleting by omission from the new set of children
				set<ControlLink> cl_test_set = doubleBulbLamp.ControlLink_kind_children();
				CPPUNIT_ASSERT( cl_test_set.size() == 3);				
				cl_test_set.erase(cl_test_set.begin(), cl_test_set.end());
				cl_test_set.insert(cl1);
				try
				{
					doubleBulbLamp.ControlLink_children() = cl_test_set;
				}
				catch (udm_exception &e)
				{
					cout << e.what() << endl;
				};
				cl_test_set = doubleBulbLamp.ControlLink_kind_children();
				CPPUNIT_ASSERT( cl_test_set.size() == 1);
				CPPUNIT_ASSERT(*(cl_test_set.begin()) == cl1);




				//deleting by setting the parent to NULL
				//this is  way to delete cl1
				cl1.parent() = NULL;
				cl_test_set = doubleBulbLamp.ControlLink_kind_children();
				CPPUNIT_ASSERT( cl_test_set.size() == 0);
				

				//recreate the deleted controlinks and reestablishthe connections
				cl1 = ControlLink::Create(doubleBulbLamp);
				cl1.src_end() = bulb1;
				cl1.dst_end() = switch1;
				cl1.name() = "Bulb 1 switcher";

				cl2 = ControlLink::Create(doubleBulbLamp);
				cl2.src_end() = bulb2;
				cl2.dst_end() = switch2;
				cl2.name() = "Bulb 2 switcher";

				cl3 = ControlLink::Create(doubleBulbLamp);
				cl3.src_end() = bulb3;
				cl3.dst_end() = switch3;
				cl3.name() = "Halogen Bulb  switcher";

				cl_test_set = doubleBulbLamp.ControlLink_kind_children();
				CPPUNIT_ASSERT( cl_test_set.size() == 3);
				CPPUNIT_ASSERT( Bulb(cl2.src_end()) == bulb2);
				CPPUNIT_ASSERT( Switch(cl2.dst_end()) == switch2);
				CPPUNIT_ASSERT( Bulb(cl3.src_end()) == bulb3);
				CPPUNIT_ASSERT( Switch(cl3.dst_end()) == switch3);
				CPPUNIT_ASSERT( Bulb(cl1.src_end()) == bulb1);
				CPPUNIT_ASSERT( Switch(cl1.dst_end()) == switch1);

			

				
				//testing now associations

				Bulb b11 = cl1.src_end();
				Bulb b12 = cl2.src_end();

				cl1.src_end() = b12;
				cl2.src_end() = b11;

			
				//cl1 points to bulb2 and cl2 points to bulb1
				lks = doubleBulbLamp.ControlLink_kind_children();
				for(l1 = lks.begin(); l1 != lks.end(); l1++) 
				{
					bool bvar11 = ((*l1 == cl1) && (Bulb(l1->src_end()) == bulb2));
					bool bvar12 = ((*l1 == cl1) && (Switch(l1->dst_end()) == switch1));

					
					bool bvar21 = ((*l1 == cl2) && (Bulb(l1->src_end()) == bulb1));
					bool bvar22 = ((*l1 == cl2) && (Switch(l1->dst_end()) == switch2));

					bool bvar31 = ((*l1 == cl3) && (Bulb(l1->src_end()) == bulb3));
					bool bvar32 = ((*l1 == cl3) && (Switch(l1->dst_end()) == switch3));

					bool bvar1 = bvar11 && bvar12;
					bool bvar2 = bvar21 && bvar22;
					bool bvar3 = bvar31 && bvar32;

					if (bvar1)	CPPUNIT_ASSERT((!bvar2 && !bvar3));
					if (bvar2)	CPPUNIT_ASSERT((!bvar3 && !bvar1));
					if (bvar3)	CPPUNIT_ASSERT((!bvar1 && !bvar2));

				}


			//testing parentroles
			


			Lamp lamp1 = switch1.MainSwitch_Lamp_parent();
			Lamp lamp2 = switch1.FunctionSwitch_Lamp_parent();
			RootFolder r1 = switch1.RootFolder_parent();
			

			CPPUNIT_ASSERT(!lamp1);		//this should be false, switch1 is not a mainswitch
			CPPUNIT_ASSERT(lamp2);		//this should be true
			CPPUNIT_ASSERT(!r1);		//this should be false again


			
			Udm::Object o1 = switch1.parent();
			CPPUNIT_ASSERT(o1);
			CPPUNIT_ASSERT(o1 == lamp2);

			long id = o1.uniqueId();
			CPPUNIT_ASSERT(id);
			Udm::Object o2 = nw.ObjectById(id);
			CPPUNIT_ASSERT(o2 == o1);

			

			//testing child roles
			set<ElectricDevice> ed_s = doubleBulbLamp.ElectricDevice_kind_children();
			CPPUNIT_ASSERT(ed_s.size() == 8); //all the devices: 3 Bulb, 3 switch, 1 plug, 1 lamp
			

			//testing assignment
						
			Udm::SmartDataNetwork snw(LampDiagram::diagram);
			snw.CreateNew(dst,"LampDiagram",RootFolder::meta);
			snw = nw;						//Datanetwork copy operator
			//snw = nw;						//this should be also OK, but it does not work yet in case of MEM-MEM copy


			snw.CloseWithUpdate();
			
		}
		nw.CloseWithUpdate();
			
		}
	return false;
};

#ifdef _WIN32
void UdmTests::genericTest::testDOMMGA()
{
	cout << endl << "generic tests and copy DOM to MGA";
	const char * fname = getRndFileName();
	std::string fname_std = std::string(fname) + ".xml";
	std::string fname_std_1 = std::string(fname) + ".mga";
	generictest(fname_std.c_str(),fname_std_1.c_str());
};

void UdmTests::genericTest::testMEMMGA()
{
	cout << endl << "generic tests and copy MEM to MGA:";
	const char * fname = getRndFileName();
	std::string fname_std = std::string(fname) + ".mem";
	std::string fname_std_1 = std::string(fname) + ".mga";
	generictest(fname_std.c_str(),fname_std_1.c_str());
};

void UdmTests::genericTest::testMGAMGA()
{
	cout << endl << "generic tests and copy MGA to MGA:";
	const char * fname = getRndFileName();
	std::string fname_std = std::string(fname) + ".mga";
	std::string fname_std_1 = std::string(fname) + "1.mga";
	generictest(fname_std.c_str(),fname_std_1.c_str());
};

void UdmTests::genericTest::testMGADOM()
{
	cout << endl << "generic tests and copy MGA to DOM:";
	const char * fname = getRndFileName();
	std::string fname_std = std::string(fname) + ".mga";
	std::string fname_std_1 = std::string(fname) + ".xml";
	generictest(fname_std.c_str(),fname_std_1.c_str());
};

void UdmTests::genericTest::testMGAMEM()
{
	cout << endl << "generic tests and copy MGA to MEM:";
	const char * fname = getRndFileName();
	std::string fname_std = std::string(fname) + ".mga";
	std::string fname_std_1 = std::string(fname) + ".mem";
	generictest(fname_std.c_str(),fname_std_1.c_str());
};
#endif // _WIN32

void UdmTests::genericTest::testDOMDOM()
{
	cout << endl << "generic tests and copy DOM to DOM:";
	const char * fname = getRndFileName();
	std::string fname_std = std::string(fname) + ".xml";
	std::string fname_std_1 = std::string(fname) + "1.xml";
	generictest(fname_std.c_str(),fname_std_1.c_str());
};

void UdmTests::genericTest::testDOMMEM()
{
	cout << endl << "generic tests and copy DOM to MEM:";
	const char * fname = getRndFileName();
	std::string fname_std = std::string(fname) + ".xml";
	std::string fname_std_1 = std::string(fname) + ".mem";
	generictest(fname_std.c_str(),fname_std_1.c_str());
};

void UdmTests::genericTest::testMEMMEM()
{
	cout << endl << "generic tests and copy MEM to MEM:";
	const char * fname = getRndFileName();
	std::string fname_std = std::string(fname) + ".mem";
	std::string fname_std_1 = std::string(fname) + "1.mem";
	generictest(fname_std.c_str(),fname_std_1.c_str());
};

void UdmTests::genericTest::testMEMDOM()
{
	cout << endl << "generic tests and copy MEM to DOM:";
	const char * fname = getRndFileName();
	std::string fname_std = std::string(fname) + ".mem";
	std::string fname_std_1 = std::string(fname) + ".xml";
	generictest(fname_std.c_str(),fname_std_1.c_str());
};
