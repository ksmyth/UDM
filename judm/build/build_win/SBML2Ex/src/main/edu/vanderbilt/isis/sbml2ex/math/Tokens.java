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
 * Domain specific class of <code>Tokens</code>.
 */ 
public abstract class Tokens extends UdmPseudoObject
{
	// meta information
	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected Tokens(UdmPseudoObject upo, Diagram metaDiagram) 
		throws UdmException
	{
		super(upo, metaDiagram);
	}

	/* Accessing children */

	/**
	 * Returns all the children of type <code>csymbol<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public csymbol[] getcsymbolChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, csymbol.META_TYPE, csymbol.META_TYPE_NS);
		csymbol[] res = new csymbol[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (csymbol)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>ci<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public ci[] getciChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, ci.META_TYPE, ci.META_TYPE_NS);
		ci[] res = new ci[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (ci)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>cn<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public cn[] getcnChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, cn.META_TYPE, cn.META_TYPE_NS);
		cn[] res = new cn[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (cn)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
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
		UdmPseudoObjectContainer container = getChildren(null, apply.META_TYPE, apply.META_TYPE_NS);
		apply[] res = new apply[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (apply)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/* Attribute setters, getters */

	/* Associations */

}
