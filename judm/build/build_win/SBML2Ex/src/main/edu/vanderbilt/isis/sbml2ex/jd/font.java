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
 * Domain specific class of <code>font</code>.
 */ 
public class font extends UdmPseudoObject
{
	// meta information
	public static final String META_TYPE = "font";
	public static final String META_TYPE_NS = "jd";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected font(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>font</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static font create(textObject parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new font(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>font</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static font create(display parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new font(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>fontName</code>.
	 */
	public static final String fontName = "fontName";

	/**
	 * Sets the value of the attribute <code>fontName</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setfontName(String _v)
		throws UdmException 
	{
		setStringVal(fontName, _v);
	}

	/**
	 * Returns the value of the attribute <code>fontName</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getfontName()
		throws UdmException 
	{
		return getStringVal(fontName);
	}

	/**
	 * Attribute for <code>fontSize</code>.
	 */
	public static final String fontSize = "fontSize";

	/**
	 * Sets the value of the attribute <code>fontSize</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setfontSize(long _v)
		throws UdmException 
	{
		setIntVal(fontSize, _v);
	}

	/**
	 * Returns the value of the attribute <code>fontSize</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long getfontSize()
		throws UdmException 
	{
		return getIntVal(fontSize);
	}

	/**
	 * Attribute for <code>fontStyle</code>.
	 */
	public static final String fontStyle = "fontStyle";

	/**
	 * Sets the value of the attribute <code>fontStyle</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setfontStyle(String _v)
		throws UdmException 
	{
		setStringVal(fontStyle, _v);
	}

	/**
	 * Returns the value of the attribute <code>fontStyle</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getfontStyle()
		throws UdmException 
	{
		return getStringVal(fontStyle);
	}

	/**
	 * Attribute for <code>fontColor</code>.
	 */
	public static final String fontColor = "fontColor";

	/**
	 * Sets the value of the attribute <code>fontColor</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setfontColor(long _v)
		throws UdmException 
	{
		setIntVal(fontColor, _v);
	}

	/**
	 * Returns the value of the attribute <code>fontColor</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long getfontColor()
		throws UdmException 
	{
		return getIntVal(fontColor);
	}

	/* Associations */

}
