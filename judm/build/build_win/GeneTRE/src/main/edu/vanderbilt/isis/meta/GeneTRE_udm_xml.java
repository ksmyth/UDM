package edu.vanderbilt.isis.meta;


import edu.vanderbilt.isis.meta.GeneTRE_udm_xml_0;

public class GeneTRE_udm_xml {
	private static String str = new String();

	public static String getString()
	{
		if (str.length() == 0)
		{
			str += GeneTRE_udm_xml_0.getString();
		}
		return str;
	}
}
