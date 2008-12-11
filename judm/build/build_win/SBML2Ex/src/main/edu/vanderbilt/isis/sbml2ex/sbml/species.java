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
 * Domain specific class of <code>species</code>.
 */ 
public class species extends IdBase
{
	// meta information
	public static final String META_TYPE = "species";
	public static final String META_TYPE_NS = "sbml";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected species(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>species</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static species create(listOfSpecies parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new species(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>compartment</code>.
	 */
	public static final String compartment = "compartment";

	/**
	 * Sets the value of the attribute <code>compartment</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setcompartment(String _v)
		throws UdmException 
	{
		setStringVal(compartment, _v);
	}

	/**
	 * Returns the value of the attribute <code>compartment</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getcompartment()
		throws UdmException 
	{
		return getStringVal(compartment);
	}

	/**
	 * Attribute for <code>initialConcentration</code>.
	 */
	public static final String initialConcentration = "initialConcentration";

	/**
	 * Sets the value of the attribute <code>initialConcentration</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setinitialConcentration(double _v)
		throws UdmException 
	{
		setRealVal(initialConcentration, _v);
	}

	/**
	 * Returns the value of the attribute <code>initialConcentration</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public double getinitialConcentration()
		throws UdmException 
	{
		return getRealVal(initialConcentration);
	}

	/**
	 * Attribute for <code>charge</code>.
	 */
	public static final String charge = "charge";

	/**
	 * Sets the value of the attribute <code>charge</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setcharge(long _v)
		throws UdmException 
	{
		setIntVal(charge, _v);
	}

	/**
	 * Returns the value of the attribute <code>charge</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public long getcharge()
		throws UdmException 
	{
		return getIntVal(charge);
	}

	/**
	 * Attribute for <code>boundaryCondition</code>.
	 */
	public static final String boundaryCondition = "boundaryCondition";

	/**
	 * Sets the value of the attribute <code>boundaryCondition</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setboundaryCondition(boolean _v)
		throws UdmException 
	{
		setBooleanVal(boundaryCondition, _v);
	}

	/**
	 * Returns the value of the attribute <code>boundaryCondition</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public boolean getboundaryCondition()
		throws UdmException 
	{
		return getBooleanVal(boundaryCondition);
	}

	/**
	 * Attribute for <code>constant</code>.
	 */
	public static final String constant = "constant";

	/**
	 * Sets the value of the attribute <code>constant</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setconstant(boolean _v)
		throws UdmException 
	{
		setBooleanVal(constant, _v);
	}

	/**
	 * Returns the value of the attribute <code>constant</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public boolean getconstant()
		throws UdmException 
	{
		return getBooleanVal(constant);
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

	/**
	 * Attribute for <code>hasOnlySubstanceUnits</code>.
	 */
	public static final String hasOnlySubstanceUnits = "hasOnlySubstanceUnits";

	/**
	 * Sets the value of the attribute <code>hasOnlySubstanceUnits</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void sethasOnlySubstanceUnits(boolean _v)
		throws UdmException 
	{
		setBooleanVal(hasOnlySubstanceUnits, _v);
	}

	/**
	 * Returns the value of the attribute <code>hasOnlySubstanceUnits</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public boolean gethasOnlySubstanceUnits()
		throws UdmException 
	{
		return getBooleanVal(hasOnlySubstanceUnits);
	}

	/**
	 * Attribute for <code>spatialSizeUnits</code>.
	 */
	public static final String spatialSizeUnits = "spatialSizeUnits";

	/**
	 * Sets the value of the attribute <code>spatialSizeUnits</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setspatialSizeUnits(String _v)
		throws UdmException 
	{
		setStringVal(spatialSizeUnits, _v);
	}

	/**
	 * Returns the value of the attribute <code>spatialSizeUnits</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getspatialSizeUnits()
		throws UdmException 
	{
		return getStringVal(spatialSizeUnits);
	}

	/**
	 * Attribute for <code>initialAmount</code>.
	 */
	public static final String initialAmount = "initialAmount";

	/**
	 * Sets the value of the attribute <code>initialAmount</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setinitialAmount(double _v)
		throws UdmException 
	{
		setRealVal(initialAmount, _v);
	}

	/**
	 * Returns the value of the attribute <code>initialAmount</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public double getinitialAmount()
		throws UdmException 
	{
		return getRealVal(initialAmount);
	}

	/* Associations */

}
