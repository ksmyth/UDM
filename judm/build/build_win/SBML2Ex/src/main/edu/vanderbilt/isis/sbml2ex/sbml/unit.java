/* Generated on Thu Mar 23 13:55:21 2006 */

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
 * Domain specific class of <code>unit</code>.
 */ 
public class unit extends SBase
{
	// meta information
	public static final String META_TYPE = "unit";
	public static final String META_TYPE_NS = "sbml";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected unit(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>unit</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static unit create(listOfUnits parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new unit(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>kind</code>.
	 */
	public static final String kind = "kind";

	/**
	 * Sets the value of the attribute <code>kind</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setkind(String _v)
		throws UdmException 
	{
		setStringVal(kind, _v);
	}

	/**
	 * Returns the value of the attribute <code>kind</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getkind()
		throws UdmException 
	{
		return getStringVal(kind);
	}

	/**
	 * Attribute for <code>exponent</code>.
	 */
	public static final String exponent = "exponent";

	/**
	 * Sets the value of the attribute <code>exponent</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setexponent(long _v)
		throws UdmException 
	{
		setIntVal(exponent, _v);
	}

	/**
	 * Returns the value of the attribute <code>exponent</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long getexponent()
		throws UdmException 
	{
		return getIntVal(exponent);
	}

	/**
	 * Attribute for <code>scale</code>.
	 */
	public static final String scale = "scale";

	/**
	 * Sets the value of the attribute <code>scale</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setscale(long _v)
		throws UdmException 
	{
		setIntVal(scale, _v);
	}

	/**
	 * Returns the value of the attribute <code>scale</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long getscale()
		throws UdmException 
	{
		return getIntVal(scale);
	}

	/**
	 * Attribute for <code>multiplier</code>.
	 */
	public static final String multiplier = "multiplier";

	/**
	 * Sets the value of the attribute <code>multiplier</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setmultiplier(double _v)
		throws UdmException 
	{
		setRealVal(multiplier, _v);
	}

	/**
	 * Returns the value of the attribute <code>multiplier</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public double getmultiplier()
		throws UdmException 
	{
		return getRealVal(multiplier);
	}

	/**
	 * Attribute for <code>offset</code>.
	 */
	public static final String offset = "offset";

	/**
	 * Sets the value of the attribute <code>offset</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setoffset(double _v)
		throws UdmException 
	{
		setRealVal(offset, _v);
	}

	/**
	 * Returns the value of the attribute <code>offset</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public double getoffset()
		throws UdmException 
	{
		return getRealVal(offset);
	}

	/* Associations */

}
