/* Generated on Thu Mar 23 13:55:22 2006 */

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

package edu.vanderbilt.isis.sbml2ex.sbml;

import edu.vanderbilt.isis.udm.*;

/**
 * Domain specific class of <code>parameter</code>.
 */ 
public class parameter extends IdBase
{
	// meta information
	public static final String META_TYPE = "parameter";
	public static final String META_TYPE_NS = "sbml";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected parameter(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>parameter</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static parameter create(listOfParameters parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new parameter(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>units</code>.
	 */
	public static final String units = "units";

	/**
	 * Sets the value of the attribute <code>units</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setunits(String _v)
		throws UdmException 
	{
		setStringVal(units, _v);
	}

	/**
	 * Returns the value of the attribute <code>units</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getunits()
		throws UdmException 
	{
		return getStringVal(units);
	}

	/**
	 * Attribute for <code>value</code>.
	 */
	public static final String value = "value";

	/**
	 * Sets the value of the attribute <code>value</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setvalue(double _v)
		throws UdmException 
	{
		setRealVal(value, _v);
	}

	/**
	 * Returns the value of the attribute <code>value</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public double getvalue()
		throws UdmException 
	{
		return getRealVal(value);
	}

	/**
	 * Attribute for <code>constant</code>.
	 */
	public static final String constant = "constant";

	/**
	 * Sets the value of the attribute <code>constant</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setconstant(boolean _v)
		throws UdmException 
	{
		setBooleanVal(constant, _v);
	}

	/**
	 * Returns the value of the attribute <code>constant</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public boolean getconstant()
		throws UdmException 
	{
		return getBooleanVal(constant);
	}

	/* Associations */

}
