package edu.vanderbilt.isis.meta;


import edu.vanderbilt.isis.meta.GeneTF_genetf_xsd_0;

public class GeneTF_genetf_xsd {
	private static String str = new String();

	public static String getString()
	{
		if (str.length() == 0)
		{
			str += GeneTF_genetf_xsd_0.getString();
		}
		return str;
	}
}
