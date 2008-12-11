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
 * Domain specific class of <code>apply</code>.
 */ 
public class apply extends Tokens
{
	// meta information
	public static final String META_TYPE = "apply";
	public static final String META_TYPE_NS = "math";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected apply(UdmPseudoObject upo, Diagram metaDiagram) 
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
	 * @return  An instance of the class <code>apply</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static apply create(Tokens parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new apply(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>apply</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static apply create(lambda parent)
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new apply(parent.createObject(META_TYPE, META_TYPE_NS, ""), metaDiagram);
	}

	/* Accessing children */

	/**
	 * Returns all the children of type <code>lt<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public lt[] getltChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, lt.META_TYPE, lt.META_TYPE_NS);
		lt[] res = new lt[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (lt)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>exp<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public exp[] getexpChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, exp.META_TYPE, exp.META_TYPE_NS);
		exp[] res = new exp[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (exp)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>ln<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public ln[] getlnChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, ln.META_TYPE, ln.META_TYPE_NS);
		ln[] res = new ln[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (ln)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>degree<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public degree[] getdegreeChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, degree.META_TYPE, degree.META_TYPE_NS);
		degree[] res = new degree[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (degree)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>root<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public root[] getrootChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, root.META_TYPE, root.META_TYPE_NS);
		root[] res = new root[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (root)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>leq<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public leq[] getleqChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, leq.META_TYPE, leq.META_TYPE_NS);
		leq[] res = new leq[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (leq)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>gt<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public gt[] getgtChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, gt.META_TYPE, gt.META_TYPE_NS);
		gt[] res = new gt[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (gt)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>divide<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public divide[] getdivideChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, divide.META_TYPE, divide.META_TYPE_NS);
		divide[] res = new divide[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (divide)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>plus<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public plus[] getplusChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, plus.META_TYPE, plus.META_TYPE_NS);
		plus[] res = new plus[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (plus)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>power<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public power[] getpowerChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, power.META_TYPE, power.META_TYPE_NS);
		power[] res = new power[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (power)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>minus<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public minus[] getminusChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, minus.META_TYPE, minus.META_TYPE_NS);
		minus[] res = new minus[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (minus)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/**
	 * Returns all the children of type <code>times<code> of this container. 
	 * @return  The children in an array
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public times[] gettimesChildren()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, times.META_TYPE, times.META_TYPE_NS);
		times[] res = new times[container.getLength()];
		for (int i=0; i < container.getLength(); i++) 
		{
			res[i] = (times)Utils.wrapWithSubclass(container.getAt(i), metaDiagram);
		}
		return res;
	}

	/* Attribute setters, getters */

	/* Associations */

}
