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
 * Domain specific class of <code>data_value</code>.
 */ 
public abstract class data_value extends UdmPseudoObject
{
	// meta information
	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected data_value(UdmPseudoObject upo, Diagram metaDiagram) 
		throws UdmException
	{
		super(upo, metaDiagram);
	}

	/* Accessing children */

	/* Attribute setters, getters */

	/* Associations */

	/*
	 * Asoociation with role name <code>dst</code>.
	 */

	/**
	 * Sets the other ends of the association with role name <code>dst</code>.
	 * @param a The other ends of the association
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setdst(data_label[] a)
		throws UdmException
	{
		setAssociation("dst", new UdmPseudoObjectContainer(a), UdmHelper.TARGET_FROM_PEER);
	}

	/**
	 * Returns the other ends of the association with role name <code>dst</code>.
	 * @return The other ends of the association
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public data_label[] getdst()
		throws UdmException
	{
		UdmPseudoObjectContainer objs = getAssociation("dst", UdmHelper.TARGET_FROM_PEER);
		return (data_label[]) Utils.wrapWithSubclass(objs, data_label.class, getDiagram());
	}

	/*
	 * Asoociation with role name <code>dst_dv</code>.
	 */

	/**
	 * Sets the other ends of the association with role name <code>dst_dv</code>.
	 * @param a The other ends of the association
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setdst_dv(time_point[] a)
		throws UdmException
	{
		setAssociation("dst_dv", new UdmPseudoObjectContainer(a), UdmHelper.TARGET_FROM_PEER);
	}

	/**
	 * Returns the other ends of the association with role name <code>dst_dv</code>.
	 * @return The other ends of the association
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public time_point[] getdst_dv()
		throws UdmException
	{
		UdmPseudoObjectContainer objs = getAssociation("dst_dv", UdmHelper.TARGET_FROM_PEER);
		return (time_point[]) Utils.wrapWithSubclass(objs, time_point.class, getDiagram());
	}

}
