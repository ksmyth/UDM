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
 * Domain specific class of <code>otherDisplayObjects</code>.
 */ 
public class otherDisplayObjects extends edu.vanderbilt.isis.sbml2ex.sbml.AnnotationType
{
	// meta information
	public static final String META_TYPE = "otherDisplayObjects";
	public static final String META_TYPE_NS = "jd";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected otherDisplayObjects(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>otherDisplayObjects</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static otherDisplayObjects create(edu.vanderbilt.isis.sbml2ex.sbml.annotation parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new otherDisplayObjects(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/**
	 * Returns all the children of type <code>textObject<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public textObject[] gettextObjectChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, textObject.META_TYPE, textObject.META_TYPE_NS);
		textObject[] res = new textObject[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (textObject)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/* Attribute setters, getters */

	/* Associations */

}
