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
 * Domain specific class of <code>listOfRules</code>.
 */ 
public class listOfRules extends SBase
{
	// meta information
	public static final String META_TYPE = "listOfRules";
	public static final String META_TYPE_NS = "sbml";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected listOfRules(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>listOfRules</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static listOfRules create(model parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new listOfRules(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/**
	 * Returns all the children of type <code>rule<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public rule[] getruleChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren("child", rule.META_TYPE, rule.META_TYPE_NS);
		rule[] res = new rule[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (rule)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>rateRule<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public rateRule[] getrateRuleChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren("child", rateRule.META_TYPE, rateRule.META_TYPE_NS);
		rateRule[] res = new rateRule[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (rateRule)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>assignmentRule<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public assignmentRule[] getassignmentRuleChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren("child", assignmentRule.META_TYPE, assignmentRule.META_TYPE_NS);
		assignmentRule[] res = new assignmentRule[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (assignmentRule)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>algebraicRule<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public algebraicRule[] getalgebraicRuleChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren("child", algebraicRule.META_TYPE, algebraicRule.META_TYPE_NS);
		algebraicRule[] res = new algebraicRule[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (algebraicRule)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/* Attribute setters, getters */

	/* Associations */

}
