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
 * Domain specific class of <code>sbml</code>.
 */ 
public class sbml extends SBase
{
	// meta information
	public static final String META_TYPE = "sbml";
	public static final String META_TYPE_NS = "sbml";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected sbml(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * Return the child of type <code>model<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public model getmodelChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren("model",model.META_TYPE, model.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (model)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>level</code>.
	 */
	public static final String level = "level";

	/**
	 * Sets the value of the attribute <code>level</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setlevel(String _v)
		throws UdmException 
	{
		setStringVal(level, _v);
	}

	/**
	 * Returns the value of the attribute <code>level</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getlevel()
		throws UdmException 
	{
		return getStringVal(level);
	}

	/**
	 * Attribute for <code>version</code>.
	 */
	public static final String version = "version";

	/**
	 * Sets the value of the attribute <code>version</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setversion(String _v)
		throws UdmException 
	{
		setStringVal(version, _v);
	}

	/**
	 * Returns the value of the attribute <code>version</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getversion()
		throws UdmException 
	{
		return getStringVal(version);
	}

	/* Associations */

}
