/*
 * Created on Apr 7, 2005
 *
 * Java version 1.4.2_04
 */
package edu.vanderbilt.isis.udm;

import java.io.IOException;
import java.io.InputStream;


/**
 * An extended facotry class to the domain specific factory classes.
 * Includes methods for creation of metaDiagram and dataNetwork.
 *
 * @author nsomogyi
 *
 */
public abstract class ExtendedUdmFactory extends UdmFactory {
    private String xmlMetaFile;
    private String xsdMetaFile;
    private String metaName;
    private String packagePath;

    /**
     * @param xmlMetaFile
     * @param xsdMetaFile
     * @param metaName
     * @param packagePath
     * @throws UdmException
     */
    protected ExtendedUdmFactory(
        String xmlMetaFile, String xsdMetaFile, String metaName, String packagePath)
        throws UdmException {
        super(xmlMetaFile, xsdMetaFile, metaName, packagePath);
        this.xmlMetaFile = xmlMetaFile;
        this.xsdMetaFile = xsdMetaFile;
        this.metaName = metaName;
        this.packagePath = packagePath;
    }

    /**
     * @param instanceFileName
     */
    /*private void initAPIsXSDResources(String instanceFileName) {
        try {
            File f = new File(instanceFileName);
            if (f.exists()) {
                File dir = new File(f.getParent());
                if (dir.exists() && dir.isDirectory()) {
                    Resource.copyResourceToDir(packagePath + xsdMetaFile, dir.getAbsolutePath());
                } else {
                    System.out.println("Parent dir does not exist");
                }

                xsdMetaFile = dir.getAbsolutePath() + File.separator + xsdMetaFile;
            }
        } catch (Throwable t) {
            System.out.println("initAPIsXSDResources: " + t.getMessage());
        }
    }*/

    /**
     * Unloads the daigram.
     * @throws UdmException
     */
    public void unloadDiagram() throws UdmException {
        UdmHelper.unloadDiagram(getDiagramMetaXmlFileLocation());
    }

    /**
     * Unloads the XSD.
     * @throws UdmException
     */
    public void removeXSD() throws UdmException {
        // remove all the XSD from 
        UdmHelper.RemoveXsd(getDiagramMetaXsdFileLocation());
    }

    /**
     * @throws UdmException
     */
    /*private void initStrXSDResources() throws UdmException {
        String xsd = Resource.copyResourceToStr(packagePath + xsdMetaFile);
        UdmHelper.StoreXsd(xsdMetaFile, xsd);
    }*/

    /**
     * @param instanceFileName
     * @return
     * @throws UdmException
     */
    protected UdmPseudoObject openExistingDNFromFile(String instanceFileName)
        throws UdmException {
        createDataNetwork();

        //initStrXSDResources();

        dataNetwork.openExisting(
            instanceFileName, xsdMetaFile, UdmHelper.UPDN_CHANGES_LOST_DEFAULT);
        return dataNetwork.getRootObject();
    }

    /**
     * @param xml
     * @return
     * @throws UdmException
     */
    protected UdmPseudoObject openExistingDNFromString(String xml)
        throws UdmException {
        createDataNetwork();

        //initStrXSDResources();

        dataNetwork.openExistingFromString(xml, xsdMetaFile);
        return dataNetwork.getRootObject();
    }

    /**
     * @param in
     * @return
     * @throws UdmException
     */
    protected UdmPseudoObject openExistingDNFromStream(InputStream in)
        throws UdmException {
        java.io.DataInputStream din = new java.io.DataInputStream(in);
        String xml = new String("");
        try {
            String line = null;
            while ((line = din.readLine()) != null) {
                xml += (line + "\n");
            }
        } catch (IOException ex) {
            System.out.println("Error reading from stream: " + ex.getMessage());
        } finally {
            //  close stream
            try {
                din.close();
            } catch (Exception ex) {
            }
        }

        return openExistingDNFromString(xml);
    }

    /**
     * @param instanceFileName
     * @param rootMetaClass
     * @return
     * @throws UdmException
     */
    protected UdmPseudoObject createNewDNToFile(
        String instanceFileName, UdmPseudoObject rootMetaClass)
        throws UdmException {
        createDataNetwork();

        //initStrXSDResources();

        dataNetwork.createNew(
            instanceFileName, xsdMetaFile, rootMetaClass, UdmHelper.UPDN_CHANGES_LOST_DEFAULT);
        return dataNetwork.getRootObject();
    }

    /**
     * @param rootMetaClass
     * @return
     * @throws UdmException
     */
    protected UdmPseudoObject createNewDNToString(UdmPseudoObject rootMetaClass)
        throws UdmException {
        createDataNetwork();

        //initStrXSDResources();

        dataNetwork.createNewToString(xsdMetaFile, rootMetaClass);
        return dataNetwork.getRootObject();
    }

    /**
     * @throws UdmException
     */
    public void closeWithUpdate() throws UdmException {
        getDataNetwork().closeWithUpdate();
    }

    /**
     * @throws UdmException
     */
    public void closeNoUpdate() throws UdmException {
        getDataNetwork().closeNoUpdate();
    }

    /**
     * Returns true if the data network is open; otherwise, returns false.
     * @return
     * @throws UdmException
     */
    public boolean isDataNetworkOpen() throws UdmException {
        return getDataNetwork().isOpen();
    }

    /**
     * Saves and returns the data network in a string.
     * @return The data network.
     */
    protected String saveAsString() throws UdmException {
        return getDataNetwork().saveAsString();
    }

    /**
     * Saves the data network in the specified file.
     * @param systemName
     * @throws UdmException
     */
    protected void saveAsFile(String systemName) throws UdmException {
        getDataNetwork().saveAs(systemName);
    }

    /**
     * Saves and returns the data network in a stream.
     * @return The data network.
     * @throws UdmException
     */
    protected InputStream saveAsStream() throws UdmException {
        String dn = saveAsString();
        java.io.InputStream in = null;
        if (dn == null) {
            return null;
        }
        dn = dn.trim();

        try {
            in = new java.io.ByteArrayInputStream(dn.getBytes("UTF-8"));
        } catch (IOException ex) {
            System.out.println("Error reading from stream: " + ex.getMessage());
        } finally {
            //  close stream
            try {
                in.close();
            } catch (Exception ex) {
            }
        }
        return in;
    }

    /**
     * Overrides #java.lang.Object.toString().
     * Saves and returns the data network in a string.
     * @return The data network.
     * @deprecated
     */
    public String toString() {
        try {
            return getDataNetwork().saveAsString();
        } catch (UdmException udmEx) {
        }
        return null;
    }
}
