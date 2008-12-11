/* Generated on Thu Mar 23 13:54:29 2006 */

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

package edu.vanderbilt.isis.genetf.genetf;

import edu.vanderbilt.isis.udm.*;

/**
 * Domain specific class of <code>Regulation</code>.
 */ 
public class Regulation extends UdmPseudoObject
{
	// meta information
	public static final String META_TYPE = "Regulation";
	public static final String META_TYPE_NS = "genetf";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected Regulation(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>Regulation</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static Regulation create(Container parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new Regulation(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>type</code>.
	 */
	public static final String type = "type";

	/**
	 * Sets the value of the attribute <code>type</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void settype(long _v)
		throws UdmException 
	{
		setIntVal(type, _v);
	}

	/**
	 * Returns the value of the attribute <code>type</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long gettype()
		throws UdmException 
	{
		return getIntVal(type);
	}

	/* Associations */

	/*
	 * Asoociation with role name <code>gene</code>.
	 */
	/**
	 * Sets the end of the association with role name <code>gene</code>.
	 * @param a The end of the association
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setgene(Gene a)
		throws UdmException
	{
		UdmPseudoObjectContainer container = new UdmPseudoObjectContainer(1);
		container.setAt(0, a);
		setAssociation("gene", container, UdmHelper.TARGET_FROM_CLASS);
	}

	/**
	 * Returns the end of the association with role name <code>gene</code>.
	 * @return The end of the association
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public Gene getgene()
		throws UdmException
	{
		UdmPseudoObjectContainer container = getAssociation("gene", UdmHelper.TARGET_FROM_CLASS);
		if (container.getLength() > 0)

			return (Gene) Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/*
	 * Asoociation with role name <code>tf</code>.
	 */
	/**
	 * Sets the end of the association with role name <code>tf</code>.
	 * @param a The end of the association
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void settf(TF a)
		throws UdmException
	{
		UdmPseudoObjectContainer container = new UdmPseudoObjectContainer(1);
		container.setAt(0, a);
		setAssociation("tf", container, UdmHelper.TARGET_FROM_CLASS);
	}

	/**
	 * Returns the end of the association with role name <code>tf</code>.
	 * @return The end of the association
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public TF gettf()
		throws UdmException
	{
		UdmPseudoObjectContainer container = getAssociation("tf", UdmHelper.TARGET_FROM_CLASS);
		if (container.getLength() > 0)

			return (TF) Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

}
