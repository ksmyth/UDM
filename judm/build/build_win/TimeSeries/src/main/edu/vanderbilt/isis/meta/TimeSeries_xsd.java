package edu.vanderbilt.isis.meta;


import edu.vanderbilt.isis.meta.TimeSeries_xsd_0;

public class TimeSeries_xsd {
	private static String str = new String();

	public static String getString()
	{
		if (str.length() == 0)
		{
			str += TimeSeries_xsd_0.getString();
		}
		return str;
	}
}
