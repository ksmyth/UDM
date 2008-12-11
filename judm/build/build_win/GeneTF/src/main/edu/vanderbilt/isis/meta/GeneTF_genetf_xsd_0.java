package edu.vanderbilt.isis.meta;



public class GeneTF_genetf_xsd_0 {
	private static String str = new String();

	public static String getString()
	{
		if (str.length() == 0)
		{
			str +="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
			str +="<?udm interface=\"GeneTF\" version=\"2.00\"?>\n";
			str +="<xsd:schema xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" targetNamespace=\"http://www.isis.vanderbilt.edu/2004/schemas/genetf\"\n";
			str +=" xmlns:genetf=\"http://www.isis.vanderbilt.edu/2004/schemas/genetf\"\n";
			str +=" elementFormDefault=\"qualified\" \n";
			str +=">\n";
			str +="<!-- generated on Thu Mar 23 13:54:29 2006 -->\n";
			str +="\n";
			str +="\n";
			str +="	<xsd:complexType name=\"RegulationType\">\n";
			str +="		<xsd:attribute name=\"type\" type=\"xsd:long\" default=\"0\"/>\n";
			str +="		<xsd:attribute name=\"gene_end_\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"tf_end_\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
			str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
			str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
			str +="	</xsd:complexType>\n";
			str +="\n";
			str +="	<xsd:complexType name=\"TFType\">\n";
			str +="		<xsd:attribute name=\"name\" type=\"xsd:string\" use=\"required\"/>\n";
			str +="		<xsd:attribute name=\"gene\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
			str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
			str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
			str +="	</xsd:complexType>\n";
			str +="\n";
			str +="	<xsd:complexType name=\"GeneType\">\n";
			str +="		<xsd:attribute name=\"name\" type=\"xsd:string\" use=\"required\"/>\n";
			str +="		<xsd:attribute name=\"tf\" type=\"xsd:IDREFS\"/>\n";
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
			str +="			<xsd:element name=\"Gene\" type=\"GeneType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
			str +="			<xsd:element name=\"Regulation\" type=\"RegulationType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
			str +="			<xsd:element name=\"TF\" type=\"TFType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
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
			str +=" <xsd:element name=\"Container\" type=\"ContainerType\"/>\n";
			str +="\n";
			str +="</xsd:schema>\n";
			str +="\n";
		}
		return str;
	}
}
