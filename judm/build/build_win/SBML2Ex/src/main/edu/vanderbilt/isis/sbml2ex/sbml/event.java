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
 * Domain specific class of <code>event</code>.
 */ 
public class event extends IdBase
{
	// meta information
	public static final String META_TYPE = "event";
	public static final String META_TYPE_NS = "sbml";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected event(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>event</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static event create(listOfEvents parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new event(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/**
	 * Return the child of type <code>delay<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public delay getdelayChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, delay.META_TYPE, delay.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (delay)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>trigger<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public trigger gettriggerChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, trigger.META_TYPE, trigger.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (trigger)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>listOfEventAssignments<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public listOfEventAssignments getlistOfEventAssignmentsChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, listOfEventAssignments.META_TYPE, listOfEventAssignments.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (listOfEventAssignments)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
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

	/* Associations */

}
