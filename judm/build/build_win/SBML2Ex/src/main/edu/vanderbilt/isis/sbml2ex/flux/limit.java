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

package edu.vanderbilt.isis.sbml2ex.flux;

import edu.vanderbilt.isis.udm.*;

/**
 * Domain specific class of <code>limit</code>.
 */ 
public class limit extends edu.vanderbilt.isis.sbml2ex.sbml.AnnotationType
{
	// meta information
	public static final String META_TYPE = "limit";
	public static final String META_TYPE_NS = "flux";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected limit(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>limit</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static limit create(edu.vanderbilt.isis.sbml2ex.sbml.annotation parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new limit(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>analysis</code>.
	 */
	public static final String analysis = "analysis";

	/**
	 * Sets the value of the attribute <code>analysis</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setanalysis(String _v)
		throws UdmException 
	{
		setStringVal(analysis, _v);
	}

	/**
	 * Returns the value of the attribute <code>analysis</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getanalysis()
		throws UdmException 
	{
		return getStringVal(analysis);
	}

	/**
	 * Attribute for <code>upper</code>.
	 */
	public static final String upper = "upper";

	/**
	 * Sets the value of the attribute <code>upper</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setupper(String _v)
		throws UdmException 
	{
		setStringVal(upper, _v);
	}

	/**
	 * Returns the value of the attribute <code>upper</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getupper()
		throws UdmException 
	{
		return getStringVal(upper);
	}

	/**
	 * Attribute for <code>lower</code>.
	 */
	public static final String lower = "lower";

	/**
	 * Sets the value of the attribute <code>lower</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setlower(String _v)
		throws UdmException 
	{
		setStringVal(lower, _v);
	}

	/**
	 * Returns the value of the attribute <code>lower</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getlower()
		throws UdmException 
	{
		return getStringVal(lower);
	}

	/**
	 * Attribute for <code>objective</code>.
	 */
	public static final String objective = "objective";

	/**
	 * Sets the value of the attribute <code>objective</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setobjective(String _v)
		throws UdmException 
	{
		setStringVal(objective, _v);
	}

	/**
	 * Returns the value of the attribute <code>objective</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getobjective()
		throws UdmException 
	{
		return getStringVal(objective);
	}

	/**
	 * Attribute for <code>prediction</code>.
	 */
	public static final String prediction = "prediction";

	/**
	 * Sets the value of the attribute <code>prediction</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setprediction(String _v)
		throws UdmException 
	{
		setStringVal(prediction, _v);
	}

	/**
	 * Returns the value of the attribute <code>prediction</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getprediction()
		throws UdmException 
	{
		return getStringVal(prediction);
	}

	/**
	 * Attribute for <code>enzymecommission</code>.
	 */
	public static final String enzymecommission = "enzymecommission";

	/**
	 * Sets the value of the attribute <code>enzymecommission</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setenzymecommission(String _v)
		throws UdmException 
	{
		setStringVal(enzymecommission, _v);
	}

	/**
	 * Returns the value of the attribute <code>enzymecommission</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getenzymecommission()
		throws UdmException 
	{
		return getStringVal(enzymecommission);
	}

	/* Associations */

}
