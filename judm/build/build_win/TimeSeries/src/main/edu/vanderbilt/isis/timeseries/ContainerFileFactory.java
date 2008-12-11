/* Generated on Thu Mar 23 13:55:46 2006 */

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

package edu.vanderbilt.isis.timeseries;

import java.io.InputStream;

import edu.vanderbilt.isis.udm.Diagram;
import edu.vanderbilt.isis.udm.UdmException;
import edu.vanderbilt.isis.udm.UdmFileFactory;
import edu.vanderbilt.isis.udm.UdmHelper;

/**
 * Domain specific factory class for <code>Container</code>.
 * <p>This factory allows only file and stream operations on the data network.
 * <p>This example opens an existing data network from a file
 * where the type of the root object is <code>Container</code>.
 * <blockquote><pre>
 *         ....;
 *        // open the data network
 *        ContainerFileFactory gtf = FactoryRepository.getTimeSeriesContainerFileFactory();
 *        Container root = gtf.open("Container-existingmodel.xml");
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
public class ContainerFileFactory
{
	// resource information
	private static final String packagePath = "/edu/vanderbilt/isis/meta/";
	private static final String xmlMetaFile ="TimeSeries_udm.xml";
	private static final String xsdMetaFile ="TimeSeries.xsd";
	private static final String metaName ="TimeSeries";
	// the wrapped file factory instance
	private UdmFileFactory factory;

	/**
	 * Constructor.
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public ContainerFileFactory()
		 throws UdmException 
	{
		factory = new UdmFileFactory(xmlMetaFile, xsdMetaFile, metaName, packagePath){
			protected void loadDiagram() throws UdmException {
				metaDiagram =
					new Diagram(
						xmlMetaFile, edu.vanderbilt.isis.meta.TimeSeries_udm_xml.getString());
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
		factory.getDiagram().getMetaClass(string_data.META_TYPE, string_data.META_TYPE_NS);
		factory.getDiagram().getMetaClass(integer_data.META_TYPE, integer_data.META_TYPE_NS);
		factory.getDiagram().getMetaClass(real_data.META_TYPE, real_data.META_TYPE_NS);
		factory.getDiagram().getMetaClass(boolean_data.META_TYPE, boolean_data.META_TYPE_NS);
		factory.getDiagram().getMetaClass(data_label.META_TYPE, data_label.META_TYPE_NS);
		factory.getDiagram().getMetaClass(Container.META_TYPE, Container.META_TYPE_NS);
		factory.getDiagram().getMetaClass(time_point.META_TYPE, time_point.META_TYPE_NS);
		// load XSDs
		UdmHelper.StoreXsd("TimeSeries.xsd", edu.vanderbilt.isis.meta.TimeSeries_xsd.getString());
	}

	/**
	 * Creates a new data network with root object of type <code>Container</code> in the file specified by the parameter.
	 * @param  instanceFileName The name of the instance file
	 * @return  The root object of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public Container create(String instanceFileName) 
		 throws UdmException
	{
		Container root =
			new Container(
				factory.createNewDataNetwork(instanceFileName, Container.META_TYPE, Container.META_TYPE_NS),
				factory.getDiagram());
		return root;
	}

	/**
	 * Opens an existing data network from the file specified by the parameter.
	 * @param  instanceFileName The name of the instance file
	 * @return  The root object of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public Container open(String instanceFileName) 
		 throws UdmException
	{
		Container root = 
			new Container(
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
