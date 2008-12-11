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

package edu.vanderbilt.isis.sbml2ex;

import edu.vanderbilt.isis.udm.UdmException;

/**
 * Repository of domain specific factory classes.
 */ 
public class FactoryRepository 
{
	/**
	 * Returns an instance of the factory <code>simpleSpeciesReferenceFileFactory</code>
	 * in namespace <code>sbml</code>.
	 * @return An instance of the factory <code>simpleSpeciesReferenceFileFactory</code>.
	 * @throws UdmException If any Udm related exception occured
	 * @see edu.vanderbilt.isis.sbml2ex.sbml.simpleSpeciesReferenceFileFactory 
	 */ 
	public static edu.vanderbilt.isis.sbml2ex.sbml.simpleSpeciesReferenceFileFactory getsbmlsimpleSpeciesReferenceFileFactory() 
		 throws UdmException 
	{
		return new edu.vanderbilt.isis.sbml2ex.sbml.simpleSpeciesReferenceFileFactory();
	}

	/**
	 * Returns an instance of the factory <code>simpleSpeciesReferenceStringFactory</code>
	 * in namespace <code>sbml</code>.
	 * @return An instance of the factory <code>simpleSpeciesReferenceStringFactory</code>.
	 * @throws UdmException If any Udm related exception occured
	 * @see edu.vanderbilt.isis.sbml2ex.sbml.simpleSpeciesReferenceStringFactory 
	 */ 
	public static edu.vanderbilt.isis.sbml2ex.sbml.simpleSpeciesReferenceStringFactory getsbmlsimpleSpeciesReferenceStringFactory() 
		 throws UdmException 
	{
		return new edu.vanderbilt.isis.sbml2ex.sbml.simpleSpeciesReferenceStringFactory();
	}

	/**
	 * Returns an instance of the factory <code>sbmlFileFactory</code>
	 * in namespace <code>sbml</code>.
	 * @return An instance of the factory <code>sbmlFileFactory</code>.
	 * @throws UdmException If any Udm related exception occured
	 * @see edu.vanderbilt.isis.sbml2ex.sbml.sbmlFileFactory 
	 */ 
	public static edu.vanderbilt.isis.sbml2ex.sbml.sbmlFileFactory getsbmlsbmlFileFactory() 
		 throws UdmException 
	{
		return new edu.vanderbilt.isis.sbml2ex.sbml.sbmlFileFactory();
	}

	/**
	 * Returns an instance of the factory <code>sbmlStringFactory</code>
	 * in namespace <code>sbml</code>.
	 * @return An instance of the factory <code>sbmlStringFactory</code>.
	 * @throws UdmException If any Udm related exception occured
	 * @see edu.vanderbilt.isis.sbml2ex.sbml.sbmlStringFactory 
	 */ 
	public static edu.vanderbilt.isis.sbml2ex.sbml.sbmlStringFactory getsbmlsbmlStringFactory() 
		 throws UdmException 
	{
		return new edu.vanderbilt.isis.sbml2ex.sbml.sbmlStringFactory();
	}

}
