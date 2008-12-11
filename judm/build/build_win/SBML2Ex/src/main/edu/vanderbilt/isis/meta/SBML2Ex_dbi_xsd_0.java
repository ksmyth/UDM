package edu.vanderbilt.isis.meta;



public class SBML2Ex_dbi_xsd_0 {
	private static String str = new String();

	public static String getString()
	{
		if (str.length() == 0)
		{
			str +="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
			str +="<?udm interface=\"SBML2Ex\" version=\"1.00\"?>\n";
			str +="<xsd:schema xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" targetNamespace=\"http://www.dbi.tju.edu/xmlns/dbi\"\n";
			str +=" xmlns:dbi=\"http://www.dbi.tju.edu/xmlns/dbi\"\n";
			str +=" elementFormDefault=\"qualified\" \n";
			str +=">\n";
			str +="<!-- generated on Thu Mar 23 13:55:20 2006 -->\n";
			str +="\n";
			str +="\n";
			str +="	<xsd:complexType name=\"user_defType\">\n";
			str +="		<xsd:attribute name=\"name\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"value\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
			str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
			str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
			str +="	</xsd:complexType>\n";
			str +="\n";
			str +=" <xsd:element name=\"user_def\" type=\"user_defType\"/>\n";
			str +="\n";
			str +="</xsd:schema>\n";
			str +="\n";
		}
		return str;
	}
}
