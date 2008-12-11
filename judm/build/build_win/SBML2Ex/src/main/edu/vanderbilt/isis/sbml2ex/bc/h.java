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

package edu.vanderbilt.isis.sbml2ex.bc;

import edu.vanderbilt.isis.udm.*;

/**
 * Domain specific class of <code>h</code>.
 */ 
public class h extends UdmPseudoObject
{
	// meta information
	public static final String META_TYPE = "h";
	public static final String META_TYPE_NS = "bc";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected h(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>h</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static h create(HillLaw parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new h(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/**
	 * Returns all the children of type <code>math<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.math.math[] getmathChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.math.math.META_TYPE, edu.vanderbilt.isis.sbml2ex.math.math.META_TYPE_NS);
		edu.vanderbilt.isis.sbml2ex.math.math[] res = new edu.vanderbilt.isis.sbml2ex.math.math[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (edu.vanderbilt.isis.sbml2ex.math.math)edu.vanderbilt.isis.sbml2ex.math.Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/* Attribute setters, getters */

	/* Associations */

}
