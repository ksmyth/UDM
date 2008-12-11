package edu.vanderbilt.isis.meta;


import edu.vanderbilt.isis.meta.SBML2Ex_sbml_xsd_0;

public class SBML2Ex_sbml_xsd {
	private static String str = new String();

	public static String getString()
	{
		if (str.length() == 0)
		{
			str += SBML2Ex_sbml_xsd_0.getString();
		}
		return str;
	}
}
