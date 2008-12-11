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
 * Domain specific class of <code>TF</code>.
 */ 
public class TF extends UdmPseudoObject
{
	// meta information
	public static final String META_TYPE = "TF";
	public static final String META_TYPE_NS = "genetf";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected TF(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>TF</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static TF create(Container parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new TF(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>name</code>.
	 */
	public static final String name = "name";

	/**
	 * Sets the value of the attribute <code>name</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setname(String _v)
		throws UdmException 
	{
		setStringVal(name, _v);
	}

	/**
	 * Returns the value of the attribute <code>name</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getname()
		throws UdmException 
	{
		return getStringVal(name);
	}

	/* Associations */

	/*
	 * Asoociation with role name <code>gene</code>.
	 */

	/**
	 * Sets the other ends of the association with role name <code>gene</code>.
	 * @param a The other ends of the association
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setgene(Regulation[] a)
		throws UdmException
	{
		setAssociation("gene", new UdmPseudoObjectContainer(a), UdmHelper.CLASS_FROM_TARGET);
	}

	/**
	 * Returns the other ends of the association with role name <code>gene</code>.
	 * @return The other ends of the association
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public Regulation[] getgene()
		throws UdmException
	{
		UdmPseudoObjectContainer objs = getAssociation("gene", UdmHelper.CLASS_FROM_TARGET);
		return (Regulation[]) Utils.wrapWithSubclass(objs, Regulation.class, getDiagram());
	}

}
