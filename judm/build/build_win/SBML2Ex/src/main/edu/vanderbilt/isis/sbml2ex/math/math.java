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

package edu.vanderbilt.isis.sbml2ex.math;

import edu.vanderbilt.isis.udm.*;

/**
 * Domain specific class of <code>math</code>.
 */ 
public class math extends Tokens
{
	// meta information
	public static final String META_TYPE = "math";
	public static final String META_TYPE_NS = "math";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected math(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.bc.K parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.bc.K_forward parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.bc.K_reverse parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.bc.Kcat parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.bc.V parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.bc.Kmp parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.bc.Vf parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.bc.Vb parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.bc.Kms parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.bc.S_Half parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.bc.h parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.bc.Rtot parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.bc.Km parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.bc.A parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.bc.B parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.sbml.stoichiometryMath parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.sbml.delay parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.sbml.trigger parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.sbml.eventAssignment parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.sbml.rule parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.sbml.functionDefinition parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>math</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static math create(edu.vanderbilt.isis.sbml2ex.sbml.kineticLaw parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new math(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/**
	 * Returns all the children of type <code>lambda<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public lambda[] getlambdaChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, lambda.META_TYPE, lambda.META_TYPE_NS);
		lambda[] res = new lambda[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (lambda)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/* Attribute setters, getters */

	/* Associations */

}
