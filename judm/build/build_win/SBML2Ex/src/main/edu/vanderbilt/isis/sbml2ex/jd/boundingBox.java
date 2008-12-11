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

package edu.vanderbilt.isis.sbml2ex.jd;

import edu.vanderbilt.isis.udm.*;

/**
 * Domain specific class of <code>boundingBox</code>.
 */ 
public class boundingBox extends UdmPseudoObject
{
	// meta information
	public static final String META_TYPE = "boundingBox";
	public static final String META_TYPE_NS = "jd";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected boundingBox(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>boundingBox</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static boundingBox create(textObject parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new boundingBox(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>boundingBox</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static boundingBox create(display parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new boundingBox(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>h</code>.
	 */
	public static final String h = "h";

	/**
	 * Sets the value of the attribute <code>h</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void seth(long _v)
		throws UdmException 
	{
		setIntVal(h, _v);
	}

	/**
	 * Returns the value of the attribute <code>h</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long geth()
		throws UdmException 
	{
		return getIntVal(h);
	}

	/**
	 * Attribute for <code>w</code>.
	 */
	public static final String w = "w";

	/**
	 * Sets the value of the attribute <code>w</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setw(long _v)
		throws UdmException 
	{
		setIntVal(w, _v);
	}

	/**
	 * Returns the value of the attribute <code>w</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long getw()
		throws UdmException 
	{
		return getIntVal(w);
	}

	/**
	 * Attribute for <code>x</code>.
	 */
	public static final String x = "x";

	/**
	 * Sets the value of the attribute <code>x</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setx(long _v)
		throws UdmException 
	{
		setIntVal(x, _v);
	}

	/**
	 * Returns the value of the attribute <code>x</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long getx()
		throws UdmException 
	{
		return getIntVal(x);
	}

	/**
	 * Attribute for <code>y</code>.
	 */
	public static final String y = "y";

	/**
	 * Sets the value of the attribute <code>y</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void sety(long _v)
		throws UdmException 
	{
		setIntVal(y, _v);
	}

	/**
	 * Returns the value of the attribute <code>y</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long gety()
		throws UdmException 
	{
		return getIntVal(y);
	}

	/* Associations */

}
