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
 * Domain specific class of <code>kineticLaw</code>.
 */ 
public class kineticLaw extends SBase
{
	// meta information
	public static final String META_TYPE = "kineticLaw";
	public static final String META_TYPE_NS = "sbml";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected kineticLaw(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>kineticLaw</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static kineticLaw create(reaction parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new kineticLaw(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/**
	 * Return the child of type <code>listOfParameters<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public listOfParameters getlistOfParametersChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, listOfParameters.META_TYPE, listOfParameters.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (listOfParameters)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>math<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.math.math getmathChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.math.math.META_TYPE, edu.vanderbilt.isis.sbml2ex.math.math.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (edu.vanderbilt.isis.sbml2ex.math.math)edu.vanderbilt.isis.sbml2ex.math.Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>timeUnits</code>.
	 */
	public static final String timeUnits = "timeUnits";

	/**
	 * Sets the value of the attribute <code>timeUnits</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void settimeUnits(String _v)
		throws UdmException 
	{
		setStringVal(timeUnits, _v);
	}

	/**
	 * Returns the value of the attribute <code>timeUnits</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String gettimeUnits()
		throws UdmException 
	{
		return getStringVal(timeUnits);
	}

	/**
	 * Attribute for <code>substanceUnits</code>.
	 */
	public static final String substanceUnits = "substanceUnits";

	/**
	 * Sets the value of the attribute <code>substanceUnits</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setsubstanceUnits(String _v)
		throws UdmException 
	{
		setStringVal(substanceUnits, _v);
	}

	/**
	 * Returns the value of the attribute <code>substanceUnits</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getsubstanceUnits()
		throws UdmException 
	{
		return getStringVal(substanceUnits);
	}

	/* Associations */

}
