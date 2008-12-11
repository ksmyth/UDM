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

package edu.vanderbilt.isis.sbml2ex.xhtml;

import edu.vanderbilt.isis.udm.*;

/**
 * Domain specific class of <code>body_base</code>.
 */ 
public abstract class body_base extends UdmPseudoObject
{
	// meta information
	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected body_base(UdmPseudoObject upo, Diagram metaDiagram) 
		throws UdmException
	{
		super(upo, metaDiagram);
	}

	/* Accessing children */

	/**
	 * Returns all the children of type <code>ul<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public ul[] getulChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, ul.META_TYPE, ul.META_TYPE_NS);
		ul[] res = new ul[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (ul)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>p1<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public p1[] getp1Children()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, p1.META_TYPE, p1.META_TYPE_NS);
		p1[] res = new p1[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (p1)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>p<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public p[] getpChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, p.META_TYPE, p.META_TYPE_NS);
		p[] res = new p[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (p)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>h1<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public h1[] geth1Children()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, h1.META_TYPE, h1.META_TYPE_NS);
		h1[] res = new h1[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (h1)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/* Attribute setters, getters */

	/* Associations */

}
