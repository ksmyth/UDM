package edu.vanderbilt.isis.meta;



public class TimeSeries_xsd_0 {
	private static String str = new String();

	public static String getString()
	{
		if (str.length() == 0)
		{
			str +="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
			str +="<?udm interface=\"TimeSeries\" version=\"1.00\"?>\n";
			str +="<xsd:schema xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"\n";
			str +=" elementFormDefault=\"qualified\" \n";
			str +=">\n";
			str +="<!-- generated on Thu Mar 23 13:55:46 2006 -->\n";
			str +="\n";
			str +="\n";
			str +="	<xsd:complexType name=\"string_dataType\">\n";
			str +="		<xsd:attribute name=\"value\" type=\"xsd:string\" use=\"required\"/>\n";
			str +="		<xsd:attribute name=\"dst\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"dst_dv\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
			str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
			str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
			str +="	</xsd:complexType>\n";
			str +="\n";
			str +="	<xsd:complexType name=\"integer_dataType\">\n";
			str +="		<xsd:attribute name=\"value\" type=\"xsd:long\" use=\"required\"/>\n";
			str +="		<xsd:attribute name=\"dst\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"dst_dv\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
			str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
			str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
			str +="	</xsd:complexType>\n";
			str +="\n";
			str +="	<xsd:complexType name=\"real_dataType\">\n";
			str +="		<xsd:attribute name=\"value\" type=\"xsd:double\" use=\"required\"/>\n";
			str +="		<xsd:attribute name=\"dst\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"dst_dv\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
			str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
			str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
			str +="	</xsd:complexType>\n";
			str +="\n";
			str +="	<xsd:complexType name=\"boolean_dataType\">\n";
			str +="		<xsd:attribute name=\"value\" type=\"xsd:boolean\" use=\"required\"/>\n";
			str +="		<xsd:attribute name=\"dst\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"dst_dv\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
			str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
			str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
			str +="	</xsd:complexType>\n";
			str +="\n";
			str +="	<xsd:complexType name=\"data_labelType\">\n";
			str +="		<xsd:attribute name=\"name\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"src\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
			str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
			str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
			str +="	</xsd:complexType>\n";
			str +="\n";
			str +="	<xsd:complexType name=\"ContainerType\">\n";
			str +="		<xsd:sequence>\n";
			str +="			<xsd:element name=\"boolean_data\" type=\"boolean_dataType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
			str +="			<xsd:element name=\"data_label\" type=\"data_labelType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
			str +="			<xsd:element name=\"integer_data\" type=\"integer_dataType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
			str +="			<xsd:element name=\"real_data\" type=\"real_dataType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
			str +="			<xsd:element name=\"string_data\" type=\"string_dataType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
			str +="			<xsd:element name=\"time_point\" type=\"time_pointType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
			str +="		</xsd:sequence>\n";
			str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
			str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
			str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
			str +="	</xsd:complexType>\n";
			str +="\n";
			str +="	<xsd:complexType name=\"time_pointType\">\n";
			str +="		<xsd:attribute name=\"at\" type=\"xsd:double\" use=\"required\"/>\n";
			str +="		<xsd:attribute name=\"src_tp\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
			str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
			str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
			str +="	</xsd:complexType>\n";
			str +="\n";
			str +=" <xsd:element name=\"Container\" type=\"ContainerType\"/>\n";
			str +="\n";
			str +="</xsd:schema>\n";
			str +="\n";
		}
		return str;
	}
}
