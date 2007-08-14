/**
* Created on Jan 24, 2005
*/
package edu.vanderbilt.isis.udm;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

import edu.vanderbilt.isis.udm.meta.Uml_xsd;


/**
* A base class for the domain specific factory classes. Includes methods for creation of
* metaDiagram and dataNetwork.
*
* @author Himanshu Neema
*/
public abstract class UdmFactory {
    private static String JUDM_CINT_LIB_PATH = null;
    //private static final String udmPackagePath = "/edu/vanderbilt/isis/udm/";
    private static final String umlXsdFile = "Uml.xsd";
    private String xmlMetaFile;
    private String xsdMetaFile;
    private String metaName;
    private String packagePath;
    protected Diagram metaDiagram;
    protected UdmPseudoDataNetwork dataNetwork;

    private static void findJUDM_PATH() {
        String judm_path = null;
        String cint_lib = "UdmSwig.dll";
        try {
            String os_name = System.getProperty("os.name");
            String exec = "cmd /c set";
            if (os_name.indexOf("Windows") == -1) {
                // linux specific
                cint_lib = "libUdmSwig.so";
                exec = "/bin/bash -c set";
            }

            Process p = Runtime.getRuntime().exec(exec);
            InputStream is = p.getInputStream();
            BufferedReader br = new BufferedReader(new InputStreamReader(is));
            String line;
            while ((line = br.readLine()) != null) {
                StringTokenizer st = new StringTokenizer(line, "=");
                while (st.hasMoreTokens()) {
                    String key = st.nextToken();
                    if (key.compareTo("JUDM_PATH") == 0) {
                        if (st.hasMoreTokens()) {
                            judm_path = st.nextToken();
                        }
                    }
                }
            }
        } catch (IOException ioEx) {
            System.out.println("exception: " + ioEx.getMessage());
        }

        if (judm_path == null) {
            throw new UnsatisfiedLinkError("No JUDM_PATH environment variable defined");
        }
        JUDM_CINT_LIB_PATH = judm_path + "/" + cint_lib;
    }

    protected UdmFactory(
        String xmlMetaFile, String xsdMetaFile, String metaName, String packagePath)
        throws UdmException {
        try {
            System.loadLibrary("UdmSwig");
            System.out.println("library path: UdmSwig");
        } catch (UnsatisfiedLinkError linkEx) {
            if (JUDM_CINT_LIB_PATH == null) {
                findJUDM_PATH();
            }

            System.out.println("judm path: " + JUDM_CINT_LIB_PATH);
            System.load(JUDM_CINT_LIB_PATH);
        }
        // store the Uml.xsd file
        UdmHelper.StoreXsd(umlXsdFile, Uml_xsd.getString());
        this.xmlMetaFile = xmlMetaFile;
        this.xsdMetaFile = xsdMetaFile;
        this.metaName = metaName;
        this.packagePath = packagePath;
        init();
    }

    public Diagram getDiagram() {
        return metaDiagram;
    }

    public UdmPseudoDataNetwork getDataNetwork() {
        return dataNetwork;
    }

    public String getDiagramMetaXmlFileLocation() {
        return xmlMetaFile;
    }

    public String getDiagramMetaXsdFileLocation() {
        return xsdMetaFile;
    }

    private void init() throws UdmException {
        loadDiagram();
    }

    protected abstract void loadDiagram() throws UdmException;
/*  {
         metaDiagram = new Diagram(xmlMetaFile, "cica");
    }*/

    protected void createDataNetwork() throws UdmException {
        dataNetwork = new UdmPseudoDataNetwork(metaName);
    }


    protected UdmPseudoObject openExistingDN(String instanceFileName)
        throws UdmException {
        return openExistingDNFromFile(instanceFileName);
    }

    protected UdmPseudoObject openExistingDNFromFile(String instanceFileName)
        throws UdmException {
        createDataNetwork();

        dataNetwork.openExisting(
            instanceFileName, xsdMetaFile, UdmHelper.UPDN_CHANGES_LOST_DEFAULT);
        return dataNetwork.getRootObject();
    }

    protected UdmPseudoObject openExistingDNFromString(String xml)
        throws UdmException {
        createDataNetwork();

        dataNetwork.openExistingFromString(xml, xsdMetaFile);
        return dataNetwork.getRootObject();
    }

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

    protected UdmPseudoObject createNewDN(String instanceFileName, UdmPseudoObject rootMetaClass)
        throws UdmException {
        return createNewDNToFile(instanceFileName, rootMetaClass);
    }

    protected UdmPseudoObject createNewDNToFile(
        String instanceFileName, UdmPseudoObject rootMetaClass)
        throws UdmException {
        createDataNetwork();

        dataNetwork.createNew(
            instanceFileName, xsdMetaFile, rootMetaClass, UdmHelper.UPDN_CHANGES_LOST_DEFAULT);
        return dataNetwork.getRootObject();
    }

    protected UdmPseudoObject createNewDNToString(UdmPseudoObject rootMetaClass)
        throws UdmException {
        createDataNetwork();

        dataNetwork.createNewToString(xsdMetaFile, rootMetaClass);
        return dataNetwork.getRootObject();
    }
}
