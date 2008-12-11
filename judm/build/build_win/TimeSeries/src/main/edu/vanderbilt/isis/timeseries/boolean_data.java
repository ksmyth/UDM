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
 * Domain specific class of <code>boolean_data</code>.
 */ 
public class boolean_data extends data_value
{
	// meta information
	public static final String META_TYPE = "boolean_data";
	public static final String META_TYPE_NS = "";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected boolean_data(UdmPseudoObject upo, Diagram metaDiagram) 
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

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>boolean_data</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static boolean_data create(Container parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new boolean_data(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>value</code>.
	 */
	public static final String value = "value";

	/**
	 * Sets the value of the attribute <code>value</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setvalue(boolean _v)
		throws UdmException 
	{
		setBooleanVal(value, _v);
	}

	/**
	 * Returns the value of the attribute <code>value</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public boolean getvalue()
		throws UdmException 
	{
		return getBooleanVal(value);
	}

	/* Associations */

}
