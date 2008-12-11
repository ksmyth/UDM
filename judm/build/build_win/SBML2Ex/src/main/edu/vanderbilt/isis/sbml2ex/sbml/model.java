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
 * Domain specific class of <code>model</code>.
 */ 
public class model extends IdBase
{
	// meta information
	public static final String META_TYPE = "model";
	public static final String META_TYPE_NS = "sbml";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected model(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>model</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static model create(sbml parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new model(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/**
	 * Return the child of type <code>listOfUnitDefinitions<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public listOfUnitDefinitions getlistOfUnitDefinitionsChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren("listOfUnitDefinitions",listOfUnitDefinitions.META_TYPE, listOfUnitDefinitions.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (listOfUnitDefinitions)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>listOfFunctionDefinitions<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public listOfFunctionDefinitions getlistOfFunctionDefinitionsChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren("listOfFunctionDefinitions",listOfFunctionDefinitions.META_TYPE, listOfFunctionDefinitions.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (listOfFunctionDefinitions)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>listOfCompartments<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public listOfCompartments getlistOfCompartmentsChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren("listOfCompartments",listOfCompartments.META_TYPE, listOfCompartments.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (listOfCompartments)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>listOfParameters<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public listOfParameters getlistOfParametersChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren("listOfParameters",listOfParameters.META_TYPE, listOfParameters.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (listOfParameters)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>listOfEvents<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public listOfEvents getlistOfEventsChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren("listOfEvents",listOfEvents.META_TYPE, listOfEvents.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (listOfEvents)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>listOfRules<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public listOfRules getlistOfRulesChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, listOfRules.META_TYPE, listOfRules.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (listOfRules)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>listOfSpecies<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public listOfSpecies getlistOfSpeciesChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren("listOfSpecies",listOfSpecies.META_TYPE, listOfSpecies.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (listOfSpecies)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>listOfReactions<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public listOfReactions getlistOfReactionsChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren("listOfReactions",listOfReactions.META_TYPE, listOfReactions.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (listOfReactions)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/* Attribute setters, getters */

	/* Associations */

}
