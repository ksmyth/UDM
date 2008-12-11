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

package edu.vanderbilt.isis.sbml2ex.math;

import edu.vanderbilt.isis.udm.*;

/**
 * Domain specific class of <code>csymbol</code>.
 */ 
public class csymbol extends UdmPseudoObject
{
	// meta information
	public static final String META_TYPE = "csymbol";
	public static final String META_TYPE_NS = "math";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected csymbol(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>csymbol</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static csymbol create(Tokens parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new csymbol(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>encoding</code>.
	 */
	public static final String encoding = "encoding";

	/**
	 * Sets the value of the attribute <code>encoding</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setencoding(String _v)
		throws UdmException 
	{
		setStringVal(encoding, _v);
	}

	/**
	 * Returns the value of the attribute <code>encoding</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getencoding()
		throws UdmException 
	{
		return getStringVal(encoding);
	}

	/**
	 * Attribute for <code>definitionURL</code>.
	 */
	public static final String definitionURL = "definitionURL";

	/**
	 * Sets the value of the attribute <code>definitionURL</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setdefinitionURL(String _v)
		throws UdmException 
	{
		setStringVal(definitionURL, _v);
	}

	/**
	 * Returns the value of the attribute <code>definitionURL</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getdefinitionURL()
		throws UdmException 
	{
		return getStringVal(definitionURL);
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
	public void setvalue(String _v)
		throws UdmException 
	{
		setStringVal(value, _v);
	}

	/**
	 * Returns the value of the attribute <code>value</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getvalue()
		throws UdmException 
	{
		return getStringVal(value);
	}

	/* Associations */

}
