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
 * Domain specific class of <code>Container</code>.
 */ 
public class Container extends UdmPseudoObject
{
	// meta information
	public static final String META_TYPE = "Container";
	public static final String META_TYPE_NS = "genetre";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected Container(UdmPseudoObject upo, Diagram metaDiagram) 
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

	/* Accessing children */

	/**
	 * Returns all the children of type <code>TRE<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public TRE[] getTREChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, TRE.META_TYPE, TRE.META_TYPE_NS);
		TRE[] res = new TRE[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (TRE)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>TF<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public TF[] getTFChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, TF.META_TYPE, TF.META_TYPE_NS);
		TF[] res = new TF[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (TF)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>PWM<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public PWM[] getPWMChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, PWM.META_TYPE, PWM.META_TYPE_NS);
		PWM[] res = new PWM[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (PWM)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>Gene<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public Gene[] getGeneChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, Gene.META_TYPE, Gene.META_TYPE_NS);
		Gene[] res = new Gene[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (Gene)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/* Attribute setters, getters */

	/* Associations */

}
