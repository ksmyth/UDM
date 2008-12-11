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

package edu.vanderbilt.isis.sbml2ex.sbml;

import edu.vanderbilt.isis.udm.*;

/**
 * Utility class for namespace <code>sbml</code>.
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
		if (stoichiometryMath.META_TYPE.equals(type))
		{
			return new stoichiometryMath(obj, diagram);
		}
		else
		if (dialect.META_TYPE.equals(type))
		{
			return new dialect(obj, diagram);
		}
		else
		if (delay.META_TYPE.equals(type))
		{
			return new delay(obj, diagram);
		}
		else
		if (trigger.META_TYPE.equals(type))
		{
			return new trigger(obj, diagram);
		}
		else
		if (listOfEventAssignments.META_TYPE.equals(type))
		{
			return new listOfEventAssignments(obj, diagram);
		}
		else
		if (eventAssignment.META_TYPE.equals(type))
		{
			return new eventAssignment(obj, diagram);
		}
		else
		if (listOfModifiers.META_TYPE.equals(type))
		{
			return new listOfModifiers(obj, diagram);
		}
		else
		if (listOfReactants.META_TYPE.equals(type))
		{
			return new listOfReactants(obj, diagram);
		}
		else
		if (listOfProducts.META_TYPE.equals(type))
		{
			return new listOfProducts(obj, diagram);
		}
		else
		if (notes.META_TYPE.equals(type))
		{
			return new notes(obj, diagram);
		}
		else
		if (annotation.META_TYPE.equals(type))
		{
			return new annotation(obj, diagram);
		}
		else
		if (unit.META_TYPE.equals(type))
		{
			return new unit(obj, diagram);
		}
		else
		if (rule.META_TYPE.equals(type))
		{
			return new rule(obj, diagram);
		}
		else
		if (modifierSpeciesReference.META_TYPE.equals(type))
		{
			return new modifierSpeciesReference(obj, diagram);
		}
		else
		if (speciesReference.META_TYPE.equals(type))
		{
			return new speciesReference(obj, diagram);
		}
		else
		if (simpleSpeciesReference.META_TYPE.equals(type))
		{
			return new simpleSpeciesReference(obj, diagram);
		}
		else
		if (sbml.META_TYPE.equals(type))
		{
			return new sbml(obj, diagram);
		}
		else
		if (unitDefinition.META_TYPE.equals(type))
		{
			return new unitDefinition(obj, diagram);
		}
		else
		if (compartment.META_TYPE.equals(type))
		{
			return new compartment(obj, diagram);
		}
		else
		if (species.META_TYPE.equals(type))
		{
			return new species(obj, diagram);
		}
		else
		if (model.META_TYPE.equals(type))
		{
			return new model(obj, diagram);
		}
		else
		if (functionDefinition.META_TYPE.equals(type))
		{
			return new functionDefinition(obj, diagram);
		}
		else
		if (event.META_TYPE.equals(type))
		{
			return new event(obj, diagram);
		}
		else
		if (reaction.META_TYPE.equals(type))
		{
			return new reaction(obj, diagram);
		}
		else
		if (parameter.META_TYPE.equals(type))
		{
			return new parameter(obj, diagram);
		}
		else
		if (kineticLaw.META_TYPE.equals(type))
		{
			return new kineticLaw(obj, diagram);
		}
		else
		if (listOfUnits.META_TYPE.equals(type))
		{
			return new listOfUnits(obj, diagram);
		}
		else
		if (listOfUnitDefinitions.META_TYPE.equals(type))
		{
			return new listOfUnitDefinitions(obj, diagram);
		}
		else
		if (listOfFunctionDefinitions.META_TYPE.equals(type))
		{
			return new listOfFunctionDefinitions(obj, diagram);
		}
		else
		if (listOfCompartments.META_TYPE.equals(type))
		{
			return new listOfCompartments(obj, diagram);
		}
		else
		if (listOfParameters.META_TYPE.equals(type))
		{
			return new listOfParameters(obj, diagram);
		}
		else
		if (listOfEvents.META_TYPE.equals(type))
		{
			return new listOfEvents(obj, diagram);
		}
		else
		if (listOfRules.META_TYPE.equals(type))
		{
			return new listOfRules(obj, diagram);
		}
		else
		if (listOfSpecies.META_TYPE.equals(type))
		{
			return new listOfSpecies(obj, diagram);
		}
		else
		if (listOfReactions.META_TYPE.equals(type))
		{
			return new listOfReactions(obj, diagram);
		}
		else
		if (rateRule.META_TYPE.equals(type))
		{
			return new rateRule(obj, diagram);
		}
		else
		if (assignmentRule.META_TYPE.equals(type))
		{
			return new assignmentRule(obj, diagram);
		}
		else
		if (algebraicRule.META_TYPE.equals(type))
		{
			return new algebraicRule(obj, diagram);
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
