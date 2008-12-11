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
 * Domain specific class of <code>MichaelisMentenReversibleLaw</code>.
 */ 
public class MichaelisMentenReversibleLaw extends UdmPseudoObject
{
	// meta information
	public static final String META_TYPE = "MichaelisMentenReversibleLaw";
	public static final String META_TYPE_NS = "bc";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected MichaelisMentenReversibleLaw(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>MichaelisMentenReversibleLaw</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static MichaelisMentenReversibleLaw create(charon_annotation parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new MichaelisMentenReversibleLaw(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/**
	 * Returns all the children of type <code>Kmp<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public Kmp[] getKmpChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, Kmp.META_TYPE, Kmp.META_TYPE_NS);
		Kmp[] res = new Kmp[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (Kmp)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>Vf<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public Vf[] getVfChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, Vf.META_TYPE, Vf.META_TYPE_NS);
		Vf[] res = new Vf[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (Vf)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>Vb<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public Vb[] getVbChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, Vb.META_TYPE, Vb.META_TYPE_NS);
		Vb[] res = new Vb[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (Vb)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>Kms<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public Kms[] getKmsChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, Kms.META_TYPE, Kms.META_TYPE_NS);
		Kms[] res = new Kms[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (Kms)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/* Attribute setters, getters */

	/* Associations */

}
