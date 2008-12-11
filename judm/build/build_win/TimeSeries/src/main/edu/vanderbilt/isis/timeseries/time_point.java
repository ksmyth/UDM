/* Generated on Thu Mar 23 13:55:47 2006 */

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

package edu.vanderbilt.isis.timeseries;

import edu.vanderbilt.isis.udm.*;

/**
 * Domain specific class of <code>time_point</code>.
 */ 
public class time_point extends UdmPseudoObject
{
	// meta information
	public static final String META_TYPE = "time_point";
	public static final String META_TYPE_NS = "";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected time_point(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>time_point</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static time_point create(Container parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new time_point(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>at</code>.
	 */
	public static final String at = "at";

	/**
	 * Sets the value of the attribute <code>at</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setat(double _v)
		throws UdmException 
	{
		setRealVal(at, _v);
	}

	/**
	 * Returns the value of the attribute <code>at</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public double getat()
		throws UdmException 
	{
		return getRealVal(at);
	}

	/* Associations */

	/*
	 * Asoociation with role name <code>src_tp</code>.
	 */

	/**
	 * Sets the other ends of the association with role name <code>src_tp</code>.
	 * @param a The other ends of the association
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setsrc_tp(data_value[] a)
		throws UdmException
	{
		setAssociation("src_tp", new UdmPseudoObjectContainer(a), UdmHelper.TARGET_FROM_PEER);
	}

	/**
	 * Returns the other ends of the association with role name <code>src_tp</code>.
	 * @return The other ends of the association
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public data_value[] getsrc_tp()
		throws UdmException
	{
		UdmPseudoObjectContainer objs = getAssociation("src_tp", UdmHelper.TARGET_FROM_PEER);
		return (data_value[]) Utils.wrapWithSubclass(objs, data_value.class, getDiagram());
	}

}
