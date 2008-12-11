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
 * Domain specific class of <code>SBase</code>.
 */ 
public abstract class SBase extends UdmPseudoObject
{
	// meta information
	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected SBase(UdmPseudoObject upo, Diagram metaDiagram) 
		throws UdmException
	{
		super(upo, metaDiagram);
	}

	/* Accessing children */

	/**
	 * Return the child of type <code>notes<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public notes getnotesChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, notes.META_TYPE, notes.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (notes)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>annotation<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public annotation getannotationChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, annotation.META_TYPE, annotation.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (annotation)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>metaid</code>.
	 */
	public static final String metaid = "metaid";

	/**
	 * Sets the value of the attribute <code>metaid</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setmetaid(String _v)
		throws UdmException 
	{
		setStringVal(metaid, _v);
	}

	/**
	 * Returns the value of the attribute <code>metaid</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getmetaid()
		throws UdmException 
	{
		return getStringVal(metaid);
	}

	/* Associations */

}
