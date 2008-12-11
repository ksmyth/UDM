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
 * Domain specific class of <code>RuleVariable</code>.
 */ 
public abstract class RuleVariable extends rule
{
	// meta information
	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected RuleVariable(UdmPseudoObject upo, Diagram metaDiagram) 
		throws UdmException
	{
		super(upo, metaDiagram);
	}

	/* Accessing children */

	/* Attribute setters, getters */

	/**
	 * Attribute for <code>variable</code>.
	 */
	public static final String variable = "variable";

	/**
	 * Sets the value of the attribute <code>variable</code> to a value specified by the parameter.
	 * @param _v The new value of the attribute
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void setvariable(String _v)
		throws UdmException 
	{
		setStringVal(variable, _v);
	}

	/**
	 * Returns the value of the attribute <code>variable</code>.
	 * @return  The value
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String getvariable()
		throws UdmException 
	{
		return getStringVal(variable);
	}

	/* Associations */

}
