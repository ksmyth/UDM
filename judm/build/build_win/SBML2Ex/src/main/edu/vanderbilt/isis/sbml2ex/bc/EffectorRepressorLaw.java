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

package edu.vanderbilt.isis.sbml2ex.bc;

import edu.vanderbilt.isis.udm.*;

/**
 * Domain specific class of <code>EffectorRepressorLaw</code>.
 */ 
public class EffectorRepressorLaw extends UdmPseudoObject
{
	// meta information
	public static final String META_TYPE = "EffectorRepressorLaw";
	public static final String META_TYPE_NS = "bc";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected EffectorRepressorLaw(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>EffectorRepressorLaw</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static EffectorRepressorLaw create(charon_annotation parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new EffectorRepressorLaw(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/**
	 * Returns all the children of type <code>V<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public V[] getVChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, V.META_TYPE, V.META_TYPE_NS);
		V[] res = new V[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (V)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>Rtot<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public Rtot[] getRtotChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, Rtot.META_TYPE, Rtot.META_TYPE_NS);
		Rtot[] res = new Rtot[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (Rtot)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>A<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public A[] getAChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, A.META_TYPE, A.META_TYPE_NS);
		A[] res = new A[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (A)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>B<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public B[] getBChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, B.META_TYPE, B.META_TYPE_NS);
		B[] res = new B[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (B)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/* Attribute setters, getters */

	/* Associations */

}
