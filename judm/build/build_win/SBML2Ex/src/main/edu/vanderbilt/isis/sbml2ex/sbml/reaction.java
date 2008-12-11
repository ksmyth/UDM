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

package edu.vanderbilt.isis.sbml2ex.sbml;

import edu.vanderbilt.isis.udm.*;

/**
 * Domain specific class of <code>reaction</code>.
 */ 
public class reaction extends IdBase
{
	// meta information
	public static final String META_TYPE = "reaction";
	public static final String META_TYPE_NS = "sbml";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected reaction(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>reaction</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static reaction create(listOfReactions parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new reaction(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/**
	 * Return the child of type <code>listOfModifiers<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public listOfModifiers getlistOfModifiersChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren("listOfModifiers",listOfModifiers.META_TYPE, listOfModifiers.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (listOfModifiers)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>listOfReactants<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public listOfReactants getlistOfReactantsChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren("listOfReactants",listOfReactants.META_TYPE, listOfReactants.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (listOfReactants)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>listOfProducts<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public listOfProducts getlistOfProductsChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren("listOfProducts",listOfProducts.META_TYPE, listOfProducts.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (listOfProducts)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>kineticLaw<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public kineticLaw getkineticLawChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, kineticLaw.META_TYPE, kineticLaw.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (kineticLaw)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>fast</code>.
	 */
	public static final String fast = "fast";

	/**
	 * Sets the value of the attribute <code>fast</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setfast(boolean _v)
		throws UdmException 
	{
		setBooleanVal(fast, _v);
	}

	/**
	 * Returns the value of the attribute <code>fast</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public boolean getfast()
		throws UdmException 
	{
		return getBooleanVal(fast);
	}

	/**
	 * Attribute for <code>reversible</code>.
	 */
	public static final String reversible = "reversible";

	/**
	 * Sets the value of the attribute <code>reversible</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setreversible(boolean _v)
		throws UdmException 
	{
		setBooleanVal(reversible, _v);
	}

	/**
	 * Returns the value of the attribute <code>reversible</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public boolean getreversible()
		throws UdmException 
	{
		return getBooleanVal(reversible);
	}

	/* Associations */

}
