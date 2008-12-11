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
 * Domain specific class of <code>lambda</code>.
 */ 
public class lambda extends Tokens
{
	// meta information
	public static final String META_TYPE = "lambda";
	public static final String META_TYPE_NS = "math";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected lambda(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>lambda</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static lambda create(math parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new lambda(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/**
	 * Returns all the children of type <code>bvar<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public bvar[] getbvarChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, bvar.META_TYPE, bvar.META_TYPE_NS);
		bvar[] res = new bvar[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (bvar)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>apply<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public apply[] getapplyChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null,apply.META_TYPE, apply.META_TYPE_NS);
		apply[] array = new apply[container.getLength()];
		for (int i = 0; i < container.getLength(); i++) 
		{
			array[i] = (apply)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return array;
	}
	/**
	 *  Composition role name <code></code>.
	 */
	public static final String _ccr = "";

	/**
	 * Returns the children <code>apply<code> of this container. 
	 * which have role <code><code>.
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public apply[] getChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(_ccr,apply.META_TYPE, apply.META_TYPE_NS);
		apply[] array = new apply[container.getLength()];
		for (int i = 0; i < container.getLength(); i++) 
		{
			array[i] = (apply)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return array;
	}
	/* Attribute setters, getters */

	/* Associations */

}
