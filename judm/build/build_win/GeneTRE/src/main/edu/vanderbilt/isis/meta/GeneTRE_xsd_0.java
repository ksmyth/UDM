package edu.vanderbilt.isis.meta;



public class GeneTRE_xsd_0 {
	private static String str = new String();

	public static String getString()
	{
		if (str.length() == 0)
		{
			str +="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
			str +="<?udm interface=\"GeneTRE\" version=\"2.00\"?>\n";
			str +="<xsd:schema xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"\n";
			str +=" elementFormDefault=\"qualified\" \n";
			str +=">\n";
			str +="<!-- generated on Thu Mar 23 13:54:52 2006 -->\n";
			str +="\n";
			str +="\n";
			str +="\n";
			str +="</xsd:schema>\n";
			str +="\n";
		}
		return str;
	}
}
