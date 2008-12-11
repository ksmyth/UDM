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
 * Domain specific class of <code>Container</code>.
 */ 
public class Container extends UdmPseudoObject
{
	// meta information
	public static final String META_TYPE = "Container";
	public static final String META_TYPE_NS = "";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected Container(UdmPseudoObject upo, Diagram metaDiagram) 
		throws UdmException
	{
		super(upo, metaDiagram);
	}

	/**
	 * Returns the meta class.
	 * @return  The meta class
	 */ 
	UdmPseudoObject getMetaClass()
	{
		return metaClass;
	}

	/* Construction */

	/* Accessing children */

	/**
	 * Returns all the children of type <code>data_label<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public data_label[] getdata_labelChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, data_label.META_TYPE, data_label.META_TYPE_NS);
		data_label[] res = new data_label[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (data_label)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>string_data<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public string_data[] getstring_dataChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, string_data.META_TYPE, string_data.META_TYPE_NS);
		string_data[] res = new string_data[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (string_data)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>integer_data<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public integer_data[] getinteger_dataChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, integer_data.META_TYPE, integer_data.META_TYPE_NS);
		integer_data[] res = new integer_data[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (integer_data)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>real_data<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public real_data[] getreal_dataChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, real_data.META_TYPE, real_data.META_TYPE_NS);
		real_data[] res = new real_data[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (real_data)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>boolean_data<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public boolean_data[] getboolean_dataChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, boolean_data.META_TYPE, boolean_data.META_TYPE_NS);
		boolean_data[] res = new boolean_data[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (boolean_data)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>time_point<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public time_point[] gettime_pointChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, time_point.META_TYPE, time_point.META_TYPE_NS);
		time_point[] res = new time_point[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (time_point)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/* Attribute setters, getters */

	/* Associations */

}
