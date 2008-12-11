package edu.vanderbilt.isis.meta;


import edu.vanderbilt.isis.meta.TimeSeries_udm_xml_0;

public class TimeSeries_udm_xml {
	private static String str = new String();

	public static String getString()
	{
		if (str.length() == 0)
		{
			str += TimeSeries_udm_xml_0.getString();
		}
		return str;
	}
}
