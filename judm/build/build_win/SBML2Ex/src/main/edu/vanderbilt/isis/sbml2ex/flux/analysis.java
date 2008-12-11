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

package edu.vanderbilt.isis.sbml2ex.flux;

import edu.vanderbilt.isis.udm.*;

/**
 * Domain specific class of <code>analysis</code>.
 */ 
public class analysis extends UdmPseudoObject
{
	// meta information
	public static final String META_TYPE = "analysis";
	public static final String META_TYPE_NS = "flux";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected analysis(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>analysis</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static analysis create(listOfAnalyses parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new analysis(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>id</code>.
	 */
	public static final String id = "id";

	/**
	 * Sets the value of the attribute <code>id</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setid(String _v)
		throws UdmException 
	{
		setStringVal(id, _v);
	}

	/**
	 * Returns the value of the attribute <code>id</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getid()
		throws UdmException 
	{
		return getStringVal(id);
	}

	/**
	 * Attribute for <code>name</code>.
	 */
	public static final String name = "name";

	/**
	 * Sets the value of the attribute <code>name</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setname(String _v)
		throws UdmException 
	{
		setStringVal(name, _v);
	}

	/**
	 * Returns the value of the attribute <code>name</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getname()
		throws UdmException 
	{
		return getStringVal(name);
	}

	/**
	 * Attribute for <code>analysisType</code>.
	 */
	public static final String analysisType = "analysisType";

	/**
	 * Sets the value of the attribute <code>analysisType</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setanalysisType(String _v)
		throws UdmException 
	{
		setStringVal(analysisType, _v);
	}

	/**
	 * Returns the value of the attribute <code>analysisType</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getanalysisType()
		throws UdmException 
	{
		return getStringVal(analysisType);
	}

	/* Associations */

}
