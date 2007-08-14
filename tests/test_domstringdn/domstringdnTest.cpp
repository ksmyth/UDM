// cintstringTest.cpp


#include <UdmBase.h>
#include <UdmDom.h>
#include "LampDiagram.h"
#include "domstringdnTest.h"


// Registers the fixture into the 'registry'

CPPUNIT_TEST_SUITE_REGISTRATION( UdmTests::domstringdnTest );


using namespace LampDiagram::LampDiagram;


void UdmTests::domstringdnTest::test()
{

	string xml_xsd = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<?udm interface=\"LampDiagram\" version=\"1.00\"?>\
<xsd:schema xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">\
<!-- generated on Thu Apr 01 12:28:35 2004 -->\
 <xsd:complexType name=\"BulbType\">\
  <xsd:sequence>\
   <xsd:element name=\"ElectricTerminal\" type=\"ElectricTerminalType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
   <xsd:element name=\"Wire\" type=\"WireType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
  </xsd:sequence>\
  <xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\
  <xsd:attribute name=\"Wattage\" type=\"xsd:double\" use=\"required\"/>\
  <xsd:attribute name=\"Voltage\" type=\"xsd:double\"/>\
  <xsd:attribute name=\"MaxTempRating\" type=\"xsd:long\"/>\
  <xsd:attribute name=\"MaxVoltageRating\" type=\"xsd:double\"/>\
  <xsd:attribute name=\"position\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"name\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"dst\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\
  <xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\
  <xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\
 </xsd:complexType>\
 <xsd:complexType name=\"WireType\">\
  <xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\
  <xsd:attribute name=\"Amps\" type=\"xsd:double\"/>\
  <xsd:attribute name=\"End2_end_\" type=\"xsd:IDREF\"/>\
  <xsd:attribute name=\"End1_end_\" type=\"xsd:IDREF\"/>\
  <xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\
  <xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\
  <xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\
 </xsd:complexType>\
 <xsd:complexType name=\"PlugType\">\
  <xsd:sequence>\
   <xsd:element name=\"ElectricTerminal\" type=\"ElectricTerminalType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
   <xsd:element name=\"Wire\" type=\"WireType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
  </xsd:sequence>";

	xml_xsd+= " <xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\
  <xsd:attribute name=\"MaxTempRating\" type=\"xsd:long\"/>\
  <xsd:attribute name=\"MaxVoltageRating\" type=\"xsd:double\"/>\
  <xsd:attribute name=\"position\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"name\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"Format\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\
  <xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\
  <xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\
 </xsd:complexType>\
 <xsd:complexType name=\"LampType\">\
  <xsd:sequence>\
   <xsd:element name=\"Bulb\" type=\"BulbType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
   <xsd:element name=\"ControlLink\" type=\"ControlLinkType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
   <xsd:element name=\"ElectricTerminal\" type=\"ElectricTerminalType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
   <xsd:element name=\"HalogenBulb\" type=\"HalogenBulbType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
   <xsd:element name=\"Plug\" type=\"PlugType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
   <xsd:element name=\"Switch\" type=\"SwitchType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
   <xsd:element name=\"Wire\" type=\"WireType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
  </xsd:sequence>\
  <xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\
  <xsd:attribute name=\"MaxTempRating\" type=\"xsd:long\"/>\
  <xsd:attribute name=\"MaxVoltageRating\" type=\"xsd:double\"/>\
  <xsd:attribute name=\"position\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"name\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"ArrayStr\" type=\"xsd:string\" default=\"second;first;\"/>\
  <xsd:attribute name=\"ModelName\" type=\"xsd:string\" default=\"Default Lamp Name\"/>\
  <xsd:attribute name=\"ArrayInt\" type=\"xsd:string\" default=\"5;4;3;2;\"/>\
  <xsd:attribute name=\"ArrayBool\" type=\"xsd:string\" default=\"false;true;false;true;\"/>\
  <xsd:attribute name=\"ArrayReal\" type=\"xsd:string\" default=\"9;8;7;6;\"/>\
  <xsd:attribute name=\"RegAttr\" type=\"xsd:string\"/>";

	xml_xsd += "<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\
  <xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\
  <xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\
 </xsd:complexType>\
 <xsd:complexType name=\"HalogenBulbType\">\
  <xsd:sequence>\
   <xsd:element name=\"ElectricTerminal\" type=\"ElectricTerminalType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
   <xsd:element name=\"Wire\" type=\"WireType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
  </xsd:sequence>\
  <xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\
  <xsd:attribute name=\"Wattage\" type=\"xsd:double\" use=\"required\"/>\
  <xsd:attribute name=\"Voltage\" type=\"xsd:double\"/>\
  <xsd:attribute name=\"MaxTempRating\" type=\"xsd:long\"/>\
  <xsd:attribute name=\"MaxVoltageRating\" type=\"xsd:double\"/>\
  <xsd:attribute name=\"position\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"name\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"dst\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\
  <xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\
  <xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\
 </xsd:complexType>\
 <xsd:complexType name=\"SwitchType\">\
  <xsd:sequence>\
   <xsd:element name=\"ElectricTerminal\" type=\"ElectricTerminalType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
   <xsd:element name=\"Wire\" type=\"WireType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
  </xsd:sequence>\
  <xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\
  <xsd:attribute name=\"__child_as\">\
   <xsd:simpleType>\
    <xsd:restriction base=\"xsd:string\">\
     <xsd:enumeration value=\"FunctionSwitch\"/>\
     <xsd:enumeration value=\"MainSwitch\"/>\
     <xsd:enumeration value=\"ElectricDevice\"/>\
    </xsd:restriction>\
   </xsd:simpleType>\
  </xsd:attribute>";

	xml_xsd += "<xsd:attribute name=\"MaxTempRating\" type=\"xsd:long\"/>\
  <xsd:attribute name=\"MaxVoltageRating\" type=\"xsd:double\"/>\
  <xsd:attribute name=\"position\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"name\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"Safe\" type=\"xsd:boolean\"/>\
  <xsd:attribute name=\"Amps\" type=\"xsd:double\"/>\
  <xsd:attribute name=\"src\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\
  <xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\
  <xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\
 </xsd:complexType>\
 <xsd:complexType name=\"ControlLinkType\">\
  <xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\
  <xsd:attribute name=\"name\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"dst_end_\" type=\"xsd:IDREF\"/>\
  <xsd:attribute name=\"src_end_\" type=\"xsd:IDREF\"/>\
  <xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\
  <xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\
  <xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\
 </xsd:complexType>\
 <xsd:complexType name=\"RootFolderType\">\
  <xsd:sequence>\
   <xsd:element name=\"Bulb\" type=\"BulbType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
   <xsd:element name=\"HalogenBulb\" type=\"HalogenBulbType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
   <xsd:element name=\"Lamp\" type=\"LampType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
   <xsd:element name=\"Plug\" type=\"PlugType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
   <xsd:element name=\"Switch\" type=\"SwitchType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\
  </xsd:sequence>\
  <xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\
  <xsd:attribute name=\"RegAttr\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\
  <xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>";

	xml_xsd += " <xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\
  <xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\
 </xsd:complexType>\
 <xsd:complexType name=\"ElectricTerminalType\">\
  <xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\
  <xsd:attribute name=\"position\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"Type\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"End2\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"End1\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\
  <xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\
  <xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\
  <xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\
  <xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\
 </xsd:complexType>\
 <xsd:element name=\"RootFolder\" type=\"RootFolderType\"/>\
</xsd:schema>";

	
	string xml_str = "<RootFolder xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"LampDiagram.xsd\"><Lamp name=\"Host Lamp \" ArrayInt=\"2;3;4;5\" ArrayStr=\"first;second;\" ArrayBool=\"false;false;true;true\" ArrayReal=\"6.000000000000000;7.000000000000000;8.000000000000000;9.000000000000000\" ModelName=\"Sequence tester lamp\"><Bulb name=\"Bulb 1\" Voltage=\"10.000000\" Wattage=\"100.000000\"/><Bulb name=\"Bulb 2\" Voltage=\"20.000000\" Wattage=\"200.000000\"/><Bulb name=\"Bulb 3\" Voltage=\"30.000000\" Wattage=\"300.000000\"/></Lamp></RootFolder>";
	string xml_verify_str = 

"<RootFolder xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"LampDiagram.xsd\">\n\
	<Lamp name=\" name changed!\" ArrayInt=\"2;3;4;5\" ArrayStr=\"first;second;\" ArrayBool=\"false;false;true;true\" ArrayReal=\"6.000000000000000;7.000000000000000;8.000000000000000;9.000000000000000\" ModelName=\"Sequence tester lamp\">\n\
		<Bulb name=\"Bulb 1\" Voltage=\"10.000000\" Wattage=\"100.000000\"/>\n\
		<Bulb name=\"Bulb 2\" Voltage=\"20.000000\" Wattage=\"200.000000\"/>\n\
		<Bulb name=\"Bulb 3\" Voltage=\"30.000000\" Wattage=\"300.000000\"/>\n\
	</Lamp>\n\
</RootFolder>\n\n";

	string xml_verify_str1 = 

"<RootFolder xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"LampDiagram.xsd\">\n\
	<Lamp name=\"cool!\" sample=\"3.141590\" ArrayInt=\"2;3;4;5\" ArrayStr=\"first;second;\" ArrayBool=\"false;false;true;true\" ArrayReal=\"6.000000000000000;7.000000000000000;8.000000000000000;9.000000000000000\" ModelName=\"Default Lamp Name\"/>\n\
</RootFolder>\n\n";


	UdmDom::str_xsd_storage::StoreXsd("LampDiagram.xsd", xml_xsd);
	

	UdmDom::DomDataNetwork ddn(LampDiagram::diagram);
	ddn.OpenExistingFromString(xml_str,"LampDiagram.xsd");
	RootFolder rf = RootFolder::Cast(ddn.GetRootObject());
	Lamp l = *( (set<Lamp>(rf.Lamp_kind_children())).begin());
	l.name() = " name changed!";
	ddn.CloseWithUpdate();

	
	const string& outstr = ddn.Str();

	
	
	CPPUNIT_ASSERT( strcmp(xml_verify_str.c_str(), outstr.c_str()) == 0);


	ddn.CreateNewToString("LampDiagram.xsd", RootFolder::meta);
	RootFolder rf1 = RootFolder::Cast(ddn.GetRootObject());
	Lamp l1 = Lamp::Create(rf1);
	l1.name() = "cool!";
	ddn.CloseWithUpdate();

	const string & outstr1 = ddn.Str();

	CPPUNIT_ASSERT( strcmp(xml_verify_str1.c_str(), outstr1.c_str()) == 0);

};

