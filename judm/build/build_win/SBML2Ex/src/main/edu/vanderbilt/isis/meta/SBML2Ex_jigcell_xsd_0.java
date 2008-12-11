package edu.vanderbilt.isis.meta;



public class SBML2Ex_jigcell_xsd_0 {
	private static String str = new String();

	public static String getString()
	{
		if (str.length() == 0)
		{
			str +="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
			str +="<?udm interface=\"SBML2Ex\" version=\"1.00\"?>\n";
			str +="<xsd:schema xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" targetNamespace=\"http://mpf.biol.vt.edu/ns\"\n";
			str +=" xmlns:jigcell=\"http://mpf.biol.vt.edu/ns\"\n";
			str +=" elementFormDefault=\"qualified\" \n";
			str +=" attributeFormDefault=\"qualified\" \n";
			str +=">\n";
			str +="<!-- generated on Thu Mar 23 13:55:20 2006 -->\n";
			str +="\n";
			str +="\n";
			str +="	<xsd:complexType name=\"conservationlawType\">\n";
			str +="		<xsd:attribute name=\"dependent\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
			str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
			str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
			str +="	</xsd:complexType>\n";
			str +="\n";
			str +="	<xsd:complexType name=\"speciesType\">\n";
			str +="		<xsd:attribute name=\"equation\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"constmods\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
			str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
			str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
			str +="	</xsd:complexType>\n";
			str +="\n";
			str +="	<xsd:complexType name=\"ratelawType\">\n";
			str +="		<xsd:attribute name=\"equation\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"name\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
			str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
			str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
			str +="	</xsd:complexType>\n";
			str +="\n";
			str +="	<xsd:complexType name=\"blanklineType\">\n";
			str +="		<xsd:attribute name=\"count\" type=\"xsd:long\"/>\n";
			str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
			str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
			str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
			str +="	</xsd:complexType>\n";
			str +="\n";
			str +=" <xsd:element name=\"conservationlaw\" type=\"conservationlawType\"/>\n";
			str +=" <xsd:element name=\"species\" type=\"speciesType\"/>\n";
			str +=" <xsd:element name=\"ratelaw\" type=\"ratelawType\"/>\n";
			str +=" <xsd:element name=\"blankline\" type=\"blanklineType\"/>\n";
			str +="\n";
			str +="</xsd:schema>\n";
			str +="\n";
		}
		return str;
	}
}
