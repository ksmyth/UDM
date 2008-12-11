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
 * Domain specific class of <code>speciesReference</code>.
 */ 
public class speciesReference extends simpleSpeciesReference
{
	// meta information
	public static final String META_TYPE = "speciesReference";
	public static final String META_TYPE_NS = "sbml";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected speciesReference(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>simpleSpeciesReference</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static simpleSpeciesReference create(listOfReactants parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new speciesReference(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>simpleSpeciesReference</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static simpleSpeciesReference create(listOfProducts parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new speciesReference(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/**
	 * Return the child of type <code>stoichiometryMath<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public stoichiometryMath getstoichiometryMathChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, stoichiometryMath.META_TYPE, stoichiometryMath.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (stoichiometryMath)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>stoichiometry</code>.
	 */
	public static final String stoichiometry = "stoichiometry";

	/**
	 * Sets the value of the attribute <code>stoichiometry</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setstoichiometry(double _v)
		throws UdmException 
	{
		setRealVal(stoichiometry, _v);
	}

	/**
	 * Returns the value of the attribute <code>stoichiometry</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public double getstoichiometry()
		throws UdmException 
	{
		return getRealVal(stoichiometry);
	}

	/* Associations */

}
