package edu.vanderbilt.isis.meta;


import edu.vanderbilt.isis.meta.GeneTRE_xsd_0;

public class GeneTRE_xsd {
	private static String str = new String();

	public static String getString()
	{
		if (str.length() == 0)
		{
			str += GeneTRE_xsd_0.getString();
		}
		return str;
	}
}
