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
 * Utility class for namespace <code>math</code>.
 */ 
public class Utils
{
	/**
	 * Generates a domain specific object from the object specified by the parameter.
	 * @param  obj The generic udm object
	 * @param  diagram The diagram of the data network that contains <code>obj</code>
	 * @return  The domain specific object
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static UdmPseudoObject wrapWithSubclass(UdmPseudoObject obj, Diagram diagram)
		 throws UdmException
	{
		String type = obj.getType();
		if (math.META_TYPE.equals(type))
		{
			return new math(obj, diagram);
		}
		else
		if (lt.META_TYPE.equals(type))
		{
			return new lt(obj, diagram);
		}
		else
		if (exp.META_TYPE.equals(type))
		{
			return new exp(obj, diagram);
		}
		else
		if (ln.META_TYPE.equals(type))
		{
			return new ln(obj, diagram);
		}
		else
		if (degree.META_TYPE.equals(type))
		{
			return new degree(obj, diagram);
		}
		else
		if (root.META_TYPE.equals(type))
		{
			return new root(obj, diagram);
		}
		else
		if (leq.META_TYPE.equals(type))
		{
			return new leq(obj, diagram);
		}
		else
		if (gt.META_TYPE.equals(type))
		{
			return new gt(obj, diagram);
		}
		else
		if (divide.META_TYPE.equals(type))
		{
			return new divide(obj, diagram);
		}
		else
		if (csymbol.META_TYPE.equals(type))
		{
			return new csymbol(obj, diagram);
		}
		else
		if (ci.META_TYPE.equals(type))
		{
			return new ci(obj, diagram);
		}
		else
		if (cn.META_TYPE.equals(type))
		{
			return new cn(obj, diagram);
		}
		else
		if (plus.META_TYPE.equals(type))
		{
			return new plus(obj, diagram);
		}
		else
		if (bvar.META_TYPE.equals(type))
		{
			return new bvar(obj, diagram);
		}
		else
		if (lambda.META_TYPE.equals(type))
		{
			return new lambda(obj, diagram);
		}
		else
		if (power.META_TYPE.equals(type))
		{
			return new power(obj, diagram);
		}
		else
		if (minus.META_TYPE.equals(type))
		{
			return new minus(obj, diagram);
		}
		else
		if (times.META_TYPE.equals(type))
		{
			return new times(obj, diagram);
		}
		else
		if (apply.META_TYPE.equals(type))
		{
			return new apply(obj, diagram);
		}
		else
		{
			throw new UdmException("Unexpected type: '" + type + "'", true);
		}
	}

	/**
	 * Generates an array of domain specific objects from the objects specified by the parameter.
	 * @param  objs The generic udm objects
	 * @param  arrayClass The type of the array class
	 * @param  diagram The diagram of the data network that contains <code>obj</code>
	 * @return  The array of domain specific objects
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static UdmPseudoObject[] wrapWithSubclass(UdmPseudoObjectContainer objs, Class arrayClass, Diagram diagram) 
		 throws UdmException 
	{
		if (!UdmPseudoObject.class.isAssignableFrom(arrayClass)) 
		{
			throw new IllegalArgumentException("" + arrayClass + " is not a subtype of "+ UdmPseudoObject.class.getName());
		}
		UdmPseudoObject[] res = (UdmPseudoObject[]) java.lang.reflect.Array.newInstance(arrayClass, objs.getLength());
		for (int i = 0; i < res.length; i++) 
		{
			UdmPseudoObject obj = objs.getAt(i);
			if (obj != null) 
			{
				res[i] = wrapWithSubclass(obj, diagram);
			}
		}
		return res;
	}
}
