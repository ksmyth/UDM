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
 * Domain specific class of <code>a_em</code>.
 */ 
public abstract class a_em extends UdmPseudoObject
{
	// meta information
	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected a_em(UdmPseudoObject upo, Diagram metaDiagram) 
		throws UdmException
	{
		super(upo, metaDiagram);
	}

	/* Accessing children */

	/**
	 * Returns all the children of type <code>em<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public em[] getemChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, em.META_TYPE, em.META_TYPE_NS);
		em[] res = new em[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (em)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>a<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public a[] getaChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, a.META_TYPE, a.META_TYPE_NS);
		a[] res = new a[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (a)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/* Attribute setters, getters */

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
