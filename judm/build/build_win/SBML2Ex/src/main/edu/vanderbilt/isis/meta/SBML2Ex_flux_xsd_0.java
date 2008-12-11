package edu.vanderbilt.isis.meta;



public class SBML2Ex_flux_xsd_0 {
	private static String str = new String();

	public static String getString()
	{
		if (str.length() == 0)
		{
			str +="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
			str +="<?udm interface=\"SBML2Ex\" version=\"1.00\"?>\n";
			str +="<xsd:schema xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" targetNamespace=\"http://www.isis.vanderbilt.edu/2004/schemas/flux\"\n";
			str +=" xmlns:flux=\"http://www.isis.vanderbilt.edu/2004/schemas/flux\"\n";
			str +=" elementFormDefault=\"qualified\" \n";
			str +=">\n";
			str +="<!-- generated on Thu Mar 23 13:55:20 2006 -->\n";
			str +="\n";
			str +="\n";
			str +="	<xsd:complexType name=\"limitType\">\n";
			str +="		<xsd:attribute name=\"analysis\" type=\"xsd:string\" use=\"required\"/>\n";
			str +="		<xsd:attribute name=\"upper\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"lower\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"objective\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"prediction\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"enzymecommission\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
			str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
			str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
			str +="	</xsd:complexType>\n";
			str +="\n";
			str +="	<xsd:complexType name=\"analysisType\">\n";
			str +="		<xsd:attribute name=\"id\" type=\"xsd:string\" use=\"required\"/>\n";
			str +="		<xsd:attribute name=\"name\" type=\"xsd:string\" use=\"required\"/>\n";
			str +="		<xsd:attribute name=\"analysisType\" type=\"xsd:string\" use=\"required\"/>\n";
			str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
			str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
			str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
			str +="	</xsd:complexType>\n";
			str +="\n";
			str +="	<xsd:complexType name=\"analysisTypeType\">\n";
			str +="		<xsd:attribute name=\"id\" type=\"xsd:string\" use=\"required\"/>\n";
			str +="		<xsd:attribute name=\"name\" type=\"xsd:string\" use=\"required\"/>\n";
			str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
			str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
			str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
			str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
			str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
			str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
			str +="	</xsd:complexType>\n";
			str +="\n";
			str +="	<xsd:complexType name=\"listOfAnalysesType\">\n";
			str +="		<xsd:sequence minOccurs=\"0\" maxOccurs=\"unbounded\">\n";
			str +="			<xsd:element name=\"analysis\" type=\"analysisType\" minOccurs=\"0\"/>\n";
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
			str +="	<xsd:complexType name=\"listOfAnalysisTypesType\">\n";
			str +="		<xsd:sequence minOccurs=\"0\" maxOccurs=\"unbounded\">\n";
			str +="			<xsd:element name=\"analysisType\" type=\"analysisTypeType\" minOccurs=\"0\"/>\n";
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
			str +=" <xsd:element name=\"limit\" type=\"limitType\"/>\n";
			str +=" <xsd:element name=\"listOfAnalyses\" type=\"listOfAnalysesType\"/>\n";
			str +=" <xsd:element name=\"listOfAnalysisTypes\" type=\"listOfAnalysisTypesType\"/>\n";
			str +="\n";
			str +="</xsd:schema>\n";
			str +="\n";
		}
		return str;
	}
}
