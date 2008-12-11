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
 * Domain specific class of <code>display</code>.
 */ 
public class display extends edu.vanderbilt.isis.sbml2ex.sbml.AnnotationType
{
	// meta information
	public static final String META_TYPE = "display";
	public static final String META_TYPE_NS = "jd";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected display(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>display</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static display create(edu.vanderbilt.isis.sbml2ex.sbml.annotation parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new display(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/**
	 * Returns all the children of type <code>SBMLGraphicsHeader<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public SBMLGraphicsHeader[] getSBMLGraphicsHeaderChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, SBMLGraphicsHeader.META_TYPE, SBMLGraphicsHeader.META_TYPE_NS);
		SBMLGraphicsHeader[] res = new SBMLGraphicsHeader[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (SBMLGraphicsHeader)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>boundingBox<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public boundingBox[] getboundingBoxChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, boundingBox.META_TYPE, boundingBox.META_TYPE_NS);
		boundingBox[] res = new boundingBox[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (boundingBox)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>font<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public font[] getfontChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, font.META_TYPE, font.META_TYPE_NS);
		font[] res = new font[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (font)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/* Attribute setters, getters */

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

	/**
	 * Attribute for <code>iconIndex</code>.
	 */
	public static final String iconIndex = "iconIndex";

	/**
	 * Sets the value of the attribute <code>iconIndex</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void seticonIndex(long _v)
		throws UdmException 
	{
		setIntVal(iconIndex, _v);
	}

	/**
	 * Returns the value of the attribute <code>iconIndex</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long geticonIndex()
		throws UdmException 
	{
		return getIntVal(iconIndex);
	}

	/**
	 * Attribute for <code>edgeThickness</code>.
	 */
	public static final String edgeThickness = "edgeThickness";

	/**
	 * Sets the value of the attribute <code>edgeThickness</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setedgeThickness(long _v)
		throws UdmException 
	{
		setIntVal(edgeThickness, _v);
	}

	/**
	 * Returns the value of the attribute <code>edgeThickness</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long getedgeThickness()
		throws UdmException 
	{
		return getIntVal(edgeThickness);
	}

	/**
	 * Attribute for <code>edgeColor</code>.
	 */
	public static final String edgeColor = "edgeColor";

	/**
	 * Sets the value of the attribute <code>edgeColor</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setedgeColor(long _v)
		throws UdmException 
	{
		setIntVal(edgeColor, _v);
	}

	/**
	 * Returns the value of the attribute <code>edgeColor</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long getedgeColor()
		throws UdmException 
	{
		return getIntVal(edgeColor);
	}

	/**
	 * Attribute for <code>selectedEdgeColor</code>.
	 */
	public static final String selectedEdgeColor = "selectedEdgeColor";

	/**
	 * Sets the value of the attribute <code>selectedEdgeColor</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setselectedEdgeColor(long _v)
		throws UdmException 
	{
		setIntVal(selectedEdgeColor, _v);
	}

	/**
	 * Returns the value of the attribute <code>selectedEdgeColor</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long getselectedEdgeColor()
		throws UdmException 
	{
		return getIntVal(selectedEdgeColor);
	}

	/**
	 * Attribute for <code>borderType</code>.
	 */
	public static final String borderType = "borderType";

	/**
	 * Sets the value of the attribute <code>borderType</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setborderType(String _v)
		throws UdmException 
	{
		setStringVal(borderType, _v);
	}

	/**
	 * Returns the value of the attribute <code>borderType</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getborderType()
		throws UdmException 
	{
		return getStringVal(borderType);
	}

	/**
	 * Attribute for <code>fillColor</code>.
	 */
	public static final String fillColor = "fillColor";

	/**
	 * Sets the value of the attribute <code>fillColor</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setfillColor(long _v)
		throws UdmException 
	{
		setIntVal(fillColor, _v);
	}

	/**
	 * Returns the value of the attribute <code>fillColor</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long getfillColor()
		throws UdmException 
	{
		return getIntVal(fillColor);
	}

	/* Associations */

}
