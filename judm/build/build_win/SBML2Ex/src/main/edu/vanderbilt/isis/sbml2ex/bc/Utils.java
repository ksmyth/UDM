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
 * Utility class for namespace <code>bc</code>.
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
		if (K.META_TYPE.equals(type))
		{
			return new K(obj, diagram);
		}
		else
		if (K_forward.META_TYPE.equals(type))
		{
			return new K_forward(obj, diagram);
		}
		else
		if (K_reverse.META_TYPE.equals(type))
		{
			return new K_reverse(obj, diagram);
		}
		else
		if (Kcat.META_TYPE.equals(type))
		{
			return new Kcat(obj, diagram);
		}
		else
		if (V.META_TYPE.equals(type))
		{
			return new V(obj, diagram);
		}
		else
		if (Kmp.META_TYPE.equals(type))
		{
			return new Kmp(obj, diagram);
		}
		else
		if (Vf.META_TYPE.equals(type))
		{
			return new Vf(obj, diagram);
		}
		else
		if (Vb.META_TYPE.equals(type))
		{
			return new Vb(obj, diagram);
		}
		else
		if (Kms.META_TYPE.equals(type))
		{
			return new Kms(obj, diagram);
		}
		else
		if (S_Half.META_TYPE.equals(type))
		{
			return new S_Half(obj, diagram);
		}
		else
		if (h.META_TYPE.equals(type))
		{
			return new h(obj, diagram);
		}
		else
		if (Rtot.META_TYPE.equals(type))
		{
			return new Rtot(obj, diagram);
		}
		else
		if (Km.META_TYPE.equals(type))
		{
			return new Km(obj, diagram);
		}
		else
		if (A.META_TYPE.equals(type))
		{
			return new A(obj, diagram);
		}
		else
		if (B.META_TYPE.equals(type))
		{
			return new B(obj, diagram);
		}
		else
		if (EffectorRepressorLaw.META_TYPE.equals(type))
		{
			return new EffectorRepressorLaw(obj, diagram);
		}
		else
		if (HillLaw.META_TYPE.equals(type))
		{
			return new HillLaw(obj, diagram);
		}
		else
		if (MichaelisMentenReversibleLaw.META_TYPE.equals(type))
		{
			return new MichaelisMentenReversibleLaw(obj, diagram);
		}
		else
		if (MichaelisMentenLaw.META_TYPE.equals(type))
		{
			return new MichaelisMentenLaw(obj, diagram);
		}
		else
		if (MassActionLaw.META_TYPE.equals(type))
		{
			return new MassActionLaw(obj, diagram);
		}
		else
		if (ConstantLaw.META_TYPE.equals(type))
		{
			return new ConstantLaw(obj, diagram);
		}
		else
		if (charon_annotation.META_TYPE.equals(type))
		{
			return new charon_annotation(obj, diagram);
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
