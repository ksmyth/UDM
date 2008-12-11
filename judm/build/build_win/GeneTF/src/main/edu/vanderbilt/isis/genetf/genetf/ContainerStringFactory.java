/* Generated on Thu Mar 23 13:54:29 2006 */

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

package edu.vanderbilt.isis.genetf.genetf;

import java.io.InputStream;

import edu.vanderbilt.isis.udm.Diagram;
import edu.vanderbilt.isis.udm.UdmException;
import edu.vanderbilt.isis.udm.UdmStringFactory;
import edu.vanderbilt.isis.udm.UdmHelper;

/**
 * Domain specific factory class for <code>Container</code>.
 * <p>This factory allows only string and stream operations on the data network.
 * <p>This example opens an existing data network from a string
 * where the type of the root object is <code>Container</code>.
 * <blockquote><pre>
 *         ....;
 *         String xmlString = "<...>";
 *        // open the data network
 *        ContainerStringFactory gtf = FactoryRepository.getgenetfContainerStringFactory();
 *        Container root = gtf.open(xmlString);
 * 
 *         // manipulate the data network
 *         ....;
 * 
 *         // check constraints
 *         gtf.checkConstraints();
 * 
 *         // close  and save the data network in a string
 *         String resul = gtf.save();
 *         ....;
 * </pre></blockquote>
 */ 
public class ContainerStringFactory
{
	// resource information
	private static final String packagePath = "/edu/vanderbilt/isis/meta/";
	private static final String xmlMetaFile ="GeneTF_udm.xml";
	private static final String xsdMetaFile ="GeneTF_genetf.xsd";
	private static final String metaName ="GeneTF";
	// the wrapped string factory instance
	private UdmStringFactory factory;

	/**
	 * Constructor.
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public ContainerStringFactory()
		 throws UdmException 
	{
		factory = new UdmStringFactory(xmlMetaFile, xsdMetaFile, metaName, packagePath){
			protected void loadDiagram() throws UdmException {
				metaDiagram =
					new Diagram(
						xmlMetaFile, edu.vanderbilt.isis.meta.GeneTF_udm_xml.getString());
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
		factory.getDiagram().getMetaClass(Regulation.META_TYPE, Regulation.META_TYPE_NS);
		factory.getDiagram().getMetaClass(TF.META_TYPE, TF.META_TYPE_NS);
		factory.getDiagram().getMetaClass(Gene.META_TYPE, Gene.META_TYPE_NS);
		factory.getDiagram().getMetaClass(Container.META_TYPE, Container.META_TYPE_NS);
		// load XSDs
		UdmHelper.StoreXsd("GeneTF.xsd", edu.vanderbilt.isis.meta.GeneTF_xsd.getString());
		UdmHelper.StoreXsd("GeneTF_genetf.xsd", edu.vanderbilt.isis.meta.GeneTF_genetf_xsd.getString());
	}

	/**
	 * Creates a new data network with root object of type <code>Container</code> in a string.
	 * @return  The root object of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public Container create()
		 throws UdmException
	{
		Container root =
			new Container(
				factory.createNewDataNetwork(Container.META_TYPE, Container.META_TYPE_NS)
				, factory.getDiagram());
		return root;
	}

	/**
	 * Opens an existing data network from a string specified by the parameter.
	 * @param  xmlString The string containing the xml.
	 * @return  The root object of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public Container open(String xmlString) 
		 throws UdmException
	{
		Container root = 
			new Container(
				factory.openExistingDataNetwork(xmlString)
				, factory.getDiagram());
		return root;
	}

	/**
	 * Opens an existing data network from the stream specified by the parameter.
	 * @param  xmlStream The stream that contains the xml
	 * @return  The root object of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public Container open(InputStream xmlStream) 
		 throws UdmException
	{
		Container root = 
			new Container(
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
	 * @return  The data network in a string
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public String save() 
		 throws UdmException
	{
		factory.closeWithUpdate();
		String result = factory.saveAs();
		UdmHelper.ClearXsdStorage();
		factory.unloadDiagram();
		return result;
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
