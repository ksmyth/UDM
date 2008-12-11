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
 * Domain specific class of <code>arcSeg</code>.
 */ 
public class arcSeg extends edu.vanderbilt.isis.sbml2ex.sbml.AnnotationType
{
	// meta information
	public static final String META_TYPE = "arcSeg";
	public static final String META_TYPE_NS = "jd";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected arcSeg(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>arcSeg</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static arcSeg create(edu.vanderbilt.isis.sbml2ex.sbml.annotation parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new arcSeg(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/**
	 * Returns all the children of type <code>pt<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public pt[] getptChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, pt.META_TYPE, pt.META_TYPE_NS);
		pt[] res = new pt[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (pt)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>lineThickness</code>.
	 */
	public static final String lineThickness = "lineThickness";

	/**
	 * Sets the value of the attribute <code>lineThickness</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setlineThickness(long _v)
		throws UdmException 
	{
		setIntVal(lineThickness, _v);
	}

	/**
	 * Returns the value of the attribute <code>lineThickness</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long getlineThickness()
		throws UdmException 
	{
		return getIntVal(lineThickness);
	}

	/**
	 * Attribute for <code>lineColor</code>.
	 */
	public static final String lineColor = "lineColor";

	/**
	 * Sets the value of the attribute <code>lineColor</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setlineColor(long _v)
		throws UdmException 
	{
		setIntVal(lineColor, _v);
	}

	/**
	 * Returns the value of the attribute <code>lineColor</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long getlineColor()
		throws UdmException 
	{
		return getIntVal(lineColor);
	}

	/**
	 * Attribute for <code>FillColor</code>.
	 */
	public static final String FillColor = "FillColor";

	/**
	 * Sets the value of the attribute <code>FillColor</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setFillColor(long _v)
		throws UdmException 
	{
		setIntVal(FillColor, _v);
	}

	/**
	 * Returns the value of the attribute <code>FillColor</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long getFillColor()
		throws UdmException 
	{
		return getIntVal(FillColor);
	}

	/**
	 * Attribute for <code>SelectedLineColor</code>.
	 */
	public static final String SelectedLineColor = "SelectedLineColor";

	/**
	 * Sets the value of the attribute <code>SelectedLineColor</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setSelectedLineColor(long _v)
		throws UdmException 
	{
		setIntVal(SelectedLineColor, _v);
	}

	/**
	 * Returns the value of the attribute <code>SelectedLineColor</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long getSelectedLineColor()
		throws UdmException 
	{
		return getIntVal(SelectedLineColor);
	}

	/* Associations */

}
