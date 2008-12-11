/* Generated on Thu Mar 23 13:54:53 2006 */

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

package edu.vanderbilt.isis.genetre.genetre;

import edu.vanderbilt.isis.udm.*;

/**
 * Domain specific class of <code>TRE</code>.
 */ 
public class TRE extends UdmPseudoObject
{
	// meta information
	public static final String META_TYPE = "TRE";
	public static final String META_TYPE_NS = "genetre";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected TRE(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>TRE</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static TRE create(Container parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new TRE(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>regulation</code>.
	 */
	public static final String regulation = "regulation";

	/**
	 * Sets the value of the attribute <code>regulation</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setregulation(long _v)
		throws UdmException 
	{
		setIntVal(regulation, _v);
	}

	/**
	 * Returns the value of the attribute <code>regulation</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long getregulation()
		throws UdmException 
	{
		return getIntVal(regulation);
	}

	/**
	 * Attribute for <code>position</code>.
	 */
	public static final String position = "position";

	/**
	 * Sets the value of the attribute <code>position</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setposition(long _v)
		throws UdmException 
	{
		setIntVal(position, _v);
	}

	/**
	 * Returns the value of the attribute <code>position</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long getposition()
		throws UdmException 
	{
		return getIntVal(position);
	}

	/**
	 * Attribute for <code>strand</code>.
	 */
	public static final String strand = "strand";

	/**
	 * Sets the value of the attribute <code>strand</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setstrand(boolean _v)
		throws UdmException 
	{
		setBooleanVal(strand, _v);
	}

	/**
	 * Returns the value of the attribute <code>strand</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public boolean getstrand()
		throws UdmException 
	{
		return getBooleanVal(strand);
	}

	/**
	 * Attribute for <code>coreScore</code>.
	 */
	public static final String coreScore = "coreScore";

	/**
	 * Sets the value of the attribute <code>coreScore</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setcoreScore(double _v)
		throws UdmException 
	{
		setRealVal(coreScore, _v);
	}

	/**
	 * Returns the value of the attribute <code>coreScore</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public double getcoreScore()
		throws UdmException 
	{
		return getRealVal(coreScore);
	}

	/**
	 * Attribute for <code>matrixScore</code>.
	 */
	public static final String matrixScore = "matrixScore";

	/**
	 * Sets the value of the attribute <code>matrixScore</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setmatrixScore(double _v)
		throws UdmException 
	{
		setRealVal(matrixScore, _v);
	}

	/**
	 * Returns the value of the attribute <code>matrixScore</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public double getmatrixScore()
		throws UdmException 
	{
		return getRealVal(matrixScore);
	}

	/* Associations */

	/*
	 * Asoociation with role name <code>site</code>.
	 */
	/**
	 * Sets the end of the association with role name <code>site</code>.
	 * @param a The end of the association
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setsite(PWM a)
		throws UdmException
	{
		UdmPseudoObjectContainer container = new UdmPseudoObjectContainer(1);
		container.setAt(0, a);
		setAssociation("site", container, UdmHelper.TARGET_FROM_CLASS);
	}

	/**
	 * Returns the end of the association with role name <code>site</code>.
	 * @return The end of the association
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public PWM getsite()
		throws UdmException
	{
		UdmPseudoObjectContainer container = getAssociation("site", UdmHelper.TARGET_FROM_CLASS);
		if (container.getLength() > 0)

			return (PWM) Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

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

}
