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
 * Domain specific class of <code>charon_annotation</code>.
 */ 
public class charon_annotation extends edu.vanderbilt.isis.sbml2ex.sbml.AnnotationType
{
	// meta information
	public static final String META_TYPE = "charon_annotation";
	public static final String META_TYPE_NS = "bc";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected charon_annotation(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>charon_annotation</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static charon_annotation create(edu.vanderbilt.isis.sbml2ex.sbml.annotation parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new charon_annotation(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/**
	 * Returns all the children of type <code>EffectorRepressorLaw<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public EffectorRepressorLaw[] getEffectorRepressorLawChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, EffectorRepressorLaw.META_TYPE, EffectorRepressorLaw.META_TYPE_NS);
		EffectorRepressorLaw[] res = new EffectorRepressorLaw[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (EffectorRepressorLaw)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>HillLaw<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public HillLaw[] getHillLawChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, HillLaw.META_TYPE, HillLaw.META_TYPE_NS);
		HillLaw[] res = new HillLaw[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (HillLaw)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>MichaelisMentenReversibleLaw<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public MichaelisMentenReversibleLaw[] getMichaelisMentenReversibleLawChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, MichaelisMentenReversibleLaw.META_TYPE, MichaelisMentenReversibleLaw.META_TYPE_NS);
		MichaelisMentenReversibleLaw[] res = new MichaelisMentenReversibleLaw[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (MichaelisMentenReversibleLaw)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>MichaelisMentenLaw<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public MichaelisMentenLaw[] getMichaelisMentenLawChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, MichaelisMentenLaw.META_TYPE, MichaelisMentenLaw.META_TYPE_NS);
		MichaelisMentenLaw[] res = new MichaelisMentenLaw[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (MichaelisMentenLaw)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>MassActionLaw<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public MassActionLaw[] getMassActionLawChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, MassActionLaw.META_TYPE, MassActionLaw.META_TYPE_NS);
		MassActionLaw[] res = new MassActionLaw[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (MassActionLaw)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>ConstantLaw<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public ConstantLaw[] getConstantLawChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, ConstantLaw.META_TYPE, ConstantLaw.META_TYPE_NS);
		ConstantLaw[] res = new ConstantLaw[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (ConstantLaw)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/* Attribute setters, getters */

	/* Associations */

}
