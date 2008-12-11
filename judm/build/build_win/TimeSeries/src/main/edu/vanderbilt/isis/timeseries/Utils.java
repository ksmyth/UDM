/* Generated on Thu Mar 23 13:55:47 2006 */

/* This is a generalt file, do not modify its content.
 * Copyright (c) Vanderbilt University, 2000-2005
 * ALL RIGHTS RESERVED
 * Vanderbilt University disclaims all warranties with regard to this 
 * software, including all implied warranties of merchantability and 
 * fitness.  In no event shall Vanderbilt University be liable for any 
 * special, indirect or consequential damages or any damages whatsoever
 * resulting from loss of use, data or profits, whether in an action of
 * contract, negligence or other tortious action, arising out of or in 
 * connection with the use or performance of this software.	
 */

package edu.vanderbilt.isis.timeseries;

import edu.vanderbilt.isis.udm.*;

/**
 * Utility class for diagram <code>TimeSeries</code>.
 */ 
public class Utils
{
	/**
	 * Generates a domain specific object from the object specified by the parameter.
	 * @param  obj The generic udm object
	 * @param  diagram The diagram of the data network that contains <code>obj</code>
	 * @return  The domain specific object
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static UdmPseudoObject wrapWithSubclass(UdmPseudoObject obj, Diagram diagram)
		 throws UdmException
	{
		String type = obj.getType();
		if (string_data.META_TYPE.equals(type))
		{
			return new string_data(obj, diagram);
		}
		else
		if (integer_data.META_TYPE.equals(type))
		{
			return new integer_data(obj, diagram);
		}
		else
		if (real_data.META_TYPE.equals(type))
		{
			return new real_data(obj, diagram);
		}
		else
		if (boolean_data.META_TYPE.equals(type))
		{
			return new boolean_data(obj, diagram);
		}
		else
		if (data_label.META_TYPE.equals(type))
		{
			return new data_label(obj, diagram);
		}
		else
		if (Container.META_TYPE.equals(type))
		{
			return new Container(obj, diagram);
		}
		else
		if (time_point.META_TYPE.equals(type))
		{
			return new time_point(obj, diagram);
		}
		else
		{
			throw new UdmException("Unexpected type: '" + type + "'", true);
		}
	}

	/**
	 * Generates an array of domain specific objects from the objects specified by the parameter.
	 * @param  objs The generic udm objects
	 * @param  arrayClass The type of the array class
	 * @param  diagram The diagram of the data network that contains <code>obj</code>
	 * @return  The array of domain specific objects
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static UdmPseudoObject[] wrapWithSubclass(UdmPseudoObjectContainer objs, Class arrayClass, Diagram diagram) 
		 throws UdmException 
	{
		if (!UdmPseudoObject.class.isAssignableFrom(arrayClass)) 
		{
			throw new IllegalArgumentException("" + arrayClass + " is not a subtype of "+ UdmPseudoObject.class.getName());
		}
		UdmPseudoObject[] res = (UdmPseudoObject[]) java.lang.reflect.Array.newInstance(arrayClass, objs.getLength());
		for (int i = 0; i < res.length; i++) 
		{
			UdmPseudoObject obj = objs.getAt(i);
			if (obj != null) 
			{
				res[i] = wrapWithSubclass(obj, diagram);
			}
		}
		return res;
	}
}
