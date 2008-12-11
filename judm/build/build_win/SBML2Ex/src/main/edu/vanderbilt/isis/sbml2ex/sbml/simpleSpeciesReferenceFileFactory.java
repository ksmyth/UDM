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

import java.io.InputStream;

import edu.vanderbilt.isis.udm.Diagram;
import edu.vanderbilt.isis.udm.UdmException;
import edu.vanderbilt.isis.udm.UdmFileFactory;
import edu.vanderbilt.isis.udm.UdmHelper;

/**
 * Domain specific factory class for <code>simpleSpeciesReference</code>.
 * <p>This factory allows only file and stream operations on the data network.
 * <p>This example opens an existing data network from a file
 * where the type of the root object is <code>simpleSpeciesReference</code>.
 * <blockquote><pre>
 *         ....;
 *        // open the data network
 *        simpleSpeciesReferenceFileFactory gtf = FactoryRepository.getsbmlsimpleSpeciesReferenceFileFactory();
 *        simpleSpeciesReference root = gtf.open("simpleSpeciesReference-existingmodel.xml");
 * 
 *         // manipulate the data network
 *         ....;
 * 
 *         // check constraints
 *         gtf.checkConstraints();
 * 
 *         // close the data network without saving the changes
 *         gtf.close();
 *         ....;
 * </pre></blockquote>
 */ 
public class simpleSpeciesReferenceFileFactory
{
	// resource information
	private static final String packagePath = "/edu/vanderbilt/isis/meta/";
	private static final String xmlMetaFile ="SBML2Ex_udm.xml";
	private static final String xsdMetaFile ="SBML2Ex_sbml.xsd";
	private static final String metaName ="SBML2Ex";
	// the wrapped file factory instance
	private UdmFileFactory factory;

	/**
	 * Constructor.
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public simpleSpeciesReferenceFileFactory()
		 throws UdmException 
	{
		factory = new UdmFileFactory(xmlMetaFile, xsdMetaFile, metaName, packagePath){
			protected void loadDiagram() throws UdmException {
				metaDiagram =
					new Diagram(
						xmlMetaFile, edu.vanderbilt.isis.meta.SBML2Ex_udm_xml.getString());
			}
		};
		initializeMetaClasses();
	}

	/**
	 * Initializes the meta classes.
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	private void initializeMetaClasses() 
		 throws UdmException 
	{
		factory.getDiagram().getMetaClass(stoichiometryMath.META_TYPE, stoichiometryMath.META_TYPE_NS);
		factory.getDiagram().getMetaClass(dialect.META_TYPE, dialect.META_TYPE_NS);
		factory.getDiagram().getMetaClass(delay.META_TYPE, delay.META_TYPE_NS);
		factory.getDiagram().getMetaClass(trigger.META_TYPE, trigger.META_TYPE_NS);
		factory.getDiagram().getMetaClass(listOfEventAssignments.META_TYPE, listOfEventAssignments.META_TYPE_NS);
		factory.getDiagram().getMetaClass(eventAssignment.META_TYPE, eventAssignment.META_TYPE_NS);
		factory.getDiagram().getMetaClass(listOfModifiers.META_TYPE, listOfModifiers.META_TYPE_NS);
		factory.getDiagram().getMetaClass(listOfReactants.META_TYPE, listOfReactants.META_TYPE_NS);
		factory.getDiagram().getMetaClass(listOfProducts.META_TYPE, listOfProducts.META_TYPE_NS);
		factory.getDiagram().getMetaClass(notes.META_TYPE, notes.META_TYPE_NS);
		factory.getDiagram().getMetaClass(annotation.META_TYPE, annotation.META_TYPE_NS);
		factory.getDiagram().getMetaClass(unit.META_TYPE, unit.META_TYPE_NS);
		factory.getDiagram().getMetaClass(rule.META_TYPE, rule.META_TYPE_NS);
		factory.getDiagram().getMetaClass(modifierSpeciesReference.META_TYPE, modifierSpeciesReference.META_TYPE_NS);
		factory.getDiagram().getMetaClass(speciesReference.META_TYPE, speciesReference.META_TYPE_NS);
		factory.getDiagram().getMetaClass(simpleSpeciesReference.META_TYPE, simpleSpeciesReference.META_TYPE_NS);
		factory.getDiagram().getMetaClass(sbml.META_TYPE, sbml.META_TYPE_NS);
		factory.getDiagram().getMetaClass(unitDefinition.META_TYPE, unitDefinition.META_TYPE_NS);
		factory.getDiagram().getMetaClass(compartment.META_TYPE, compartment.META_TYPE_NS);
		factory.getDiagram().getMetaClass(species.META_TYPE, species.META_TYPE_NS);
		factory.getDiagram().getMetaClass(model.META_TYPE, model.META_TYPE_NS);
		factory.getDiagram().getMetaClass(functionDefinition.META_TYPE, functionDefinition.META_TYPE_NS);
		factory.getDiagram().getMetaClass(event.META_TYPE, event.META_TYPE_NS);
		factory.getDiagram().getMetaClass(reaction.META_TYPE, reaction.META_TYPE_NS);
		factory.getDiagram().getMetaClass(parameter.META_TYPE, parameter.META_TYPE_NS);
		factory.getDiagram().getMetaClass(kineticLaw.META_TYPE, kineticLaw.META_TYPE_NS);
		factory.getDiagram().getMetaClass(listOfUnits.META_TYPE, listOfUnits.META_TYPE_NS);
		factory.getDiagram().getMetaClass(listOfUnitDefinitions.META_TYPE, listOfUnitDefinitions.META_TYPE_NS);
		factory.getDiagram().getMetaClass(listOfFunctionDefinitions.META_TYPE, listOfFunctionDefinitions.META_TYPE_NS);
		factory.getDiagram().getMetaClass(listOfCompartments.META_TYPE, listOfCompartments.META_TYPE_NS);
		factory.getDiagram().getMetaClass(listOfParameters.META_TYPE, listOfParameters.META_TYPE_NS);
		factory.getDiagram().getMetaClass(listOfEvents.META_TYPE, listOfEvents.META_TYPE_NS);
		factory.getDiagram().getMetaClass(listOfRules.META_TYPE, listOfRules.META_TYPE_NS);
		factory.getDiagram().getMetaClass(listOfSpecies.META_TYPE, listOfSpecies.META_TYPE_NS);
		factory.getDiagram().getMetaClass(listOfReactions.META_TYPE, listOfReactions.META_TYPE_NS);
		factory.getDiagram().getMetaClass(rateRule.META_TYPE, rateRule.META_TYPE_NS);
		factory.getDiagram().getMetaClass(assignmentRule.META_TYPE, assignmentRule.META_TYPE_NS);
		factory.getDiagram().getMetaClass(algebraicRule.META_TYPE, algebraicRule.META_TYPE_NS);
		// map namespace to uri
		UdmHelper.AddURIToUMLNamespaceMapping("http://www.sbml.org/2001/ns/biocharon","bc","SBML2Ex_bc.xsd" );
		UdmHelper.AddURIToUMLNamespaceMapping("http://www.dbi.tju.edu/xmlns/dbi","dbi","SBML2Ex_dbi.xsd" );
		UdmHelper.AddURIToUMLNamespaceMapping("http://mpf.biol.vt.edu/ns","jigcell","SBML2Ex_jigcell.xsd" );
		UdmHelper.AddURIToUMLNamespaceMapping("http://www.w3.org/1998/Math/MathML","math","SBML2Ex_math.xsd" );
		UdmHelper.AddURIToUMLNamespaceMapping("http://www.sbml.org/sbml/level2","sbml","SBML2Ex_sbml.xsd" );
		UdmHelper.AddURIToUMLNamespaceMapping("http://www.dbi.tju.edu/xmlns/unigene","unigene","SBML2Ex_unigene.xsd" );
		UdmHelper.AddURIToUMLNamespaceMapping("http://www.w3.org/1999/xhtml","xhtml","SBML2Ex_xhtml.xsd" );
		// load XSDs
		UdmHelper.StoreXsd("SBML2Ex.xsd", edu.vanderbilt.isis.meta.SBML2Ex_xsd.getString());
		UdmHelper.StoreXsd("SBML2Ex_xhtml.xsd", edu.vanderbilt.isis.meta.SBML2Ex_xhtml_xsd.getString());
		UdmHelper.StoreXsd("SBML2Ex_unigene.xsd", edu.vanderbilt.isis.meta.SBML2Ex_unigene_xsd.getString());
		UdmHelper.StoreXsd("SBML2Ex_jigcell.xsd", edu.vanderbilt.isis.meta.SBML2Ex_jigcell_xsd.getString());
		UdmHelper.StoreXsd("SBML2Ex_jd.xsd", edu.vanderbilt.isis.meta.SBML2Ex_jd_xsd.getString());
		UdmHelper.StoreXsd("SBML2Ex_flux.xsd", edu.vanderbilt.isis.meta.SBML2Ex_flux_xsd.getString());
		UdmHelper.StoreXsd("SBML2Ex_dbi.xsd", edu.vanderbilt.isis.meta.SBML2Ex_dbi_xsd.getString());
		UdmHelper.StoreXsd("SBML2Ex_bc.xsd", edu.vanderbilt.isis.meta.SBML2Ex_bc_xsd.getString());
		UdmHelper.StoreXsd("SBML2Ex_sbml.xsd", edu.vanderbilt.isis.meta.SBML2Ex_sbml_xsd.getString());
		UdmHelper.StoreXsd("SBML2Ex_math.xsd", edu.vanderbilt.isis.meta.SBML2Ex_math_xsd.getString());
	}

	/**
	 * Creates a new data network with root object of type <code>simpleSpeciesReference</code> in the file specified by the parameter.
	 * @param  instanceFileName The name of the instance file
	 * @return  The root object of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public simpleSpeciesReference create(String instanceFileName) 
		 throws UdmException
	{
		simpleSpeciesReference root =
			new simpleSpeciesReference(
				factory.createNewDataNetwork(instanceFileName, simpleSpeciesReference.META_TYPE, simpleSpeciesReference.META_TYPE_NS),
				factory.getDiagram());
		return root;
	}

	/**
	 * Opens an existing data network from the file specified by the parameter.
	 * @param  instanceFileName The name of the instance file
	 * @return  The root object of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public simpleSpeciesReference open(String instanceFileName) 
		 throws UdmException
	{
		simpleSpeciesReference root = 
			new simpleSpeciesReference(
				factory.openExistingDataNetwork(instanceFileName)
				, factory.getDiagram());
			return root;
	}

	/**
	 * Opens an existing data network from the stream specified by the parameter.
	 * @param  xmlStream The stream that contains the xml
	 * @return  The root object of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public simpleSpeciesReference open(InputStream xmlStream) 
		 throws UdmException
	{
		simpleSpeciesReference root = 
			new simpleSpeciesReference(
				factory.openExistingDataNetworkFromStream(xmlStream)
				, factory.getDiagram());
		return root;
	}

	/**
	 * Closes the data network without updating it and unloads the diagram.
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void close() 
		 throws UdmException
	{
		factory.closeNoUpdate();
		UdmHelper.ClearXsdStorage();
		factory.unloadDiagram();
	}
	/**
	 * Closes and updates the data network by saving the changes in the data network.
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void save() 
		 throws UdmException
	{
		factory.closeWithUpdate();
		UdmHelper.ClearXsdStorage();
		factory.unloadDiagram();
	}

	/**
	 * Closes the data network, saves the changes in a file
	 * specified by the parameter, and unloads the diagram.
	 * @param  instanceFileName The name of the m_output file where the xml will be stored
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public void saveAs(String instanceFileName) 
		 throws UdmException
	{
		factory.saveAs(instanceFileName);
		UdmHelper.ClearXsdStorage();
		factory.unloadDiagram();
	}

	/**
	 * Closes and updates the data network, saves the changes in a stream,
	 * and unloads the diagram.
	 * @return  The data network in a stream
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public InputStream saveAsStream() 
		 throws UdmException
	{
		factory.closeWithUpdate();
		InputStream result = factory.saveAsStream();
		UdmHelper.ClearXsdStorage();
		factory.unloadDiagram();
		return result;
	}

	/**
	 * Calls the constraint checker.
	 * @return  The result of the constriant evaluation
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String checkConstraints() 
		 throws UdmException
	{
		return (factory.getDataNetwork().checkConstraints());
	}

}
