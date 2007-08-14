/**
* Created on Jan 24, 2005
*/
package edu.vanderbilt.isis.udm;



import java.io.File;
import java.io.IOException;
import java.io.InputStream;

import edu.vanderbilt.isis.util.Resource;

/**
* A base class for the domain specific factory classes. Includes methods for creation of
* metaDiagram and dataNetwork.
* 
* @author Himanshu Neema
*/
public abstract class UdmFactory {
   private static final String udmPackagePath = "/edu/vanderbilt/isis/udm/";
   private static final String umlXsdFile = "Uml.xsd";

   private String xmlMetaFile;
   private String xsdMetaFile;
   private String metaName;
   private String packagePath;

   protected Diagram metaDiagram;
   protected UdmPseudoDataNetwork dataNetwork;

   protected UdmFactory(String xmlMetaFile, String xsdMetaFile, String metaName, String packagePath) throws UdmException {
       System.loadLibrary("UdmCint");
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
       initResources();
       loadDiagram();
   }
   
   private void initResources() {
       Resource.copyResourceToTempDir(packagePath + xmlMetaFile);
       //Resource.copyResourceToTempDir(packagePath + xsdMetaFile);
       //Resource.copyResourceToTempDir(udmPackagePath + umlXsdFile);
       
       String tempDir = Resource.getTempDir();
       xmlMetaFile = tempDir + xmlMetaFile;
     //  xsdMetaFile = tempDir + xsdMetaFile;
   }
   
   private void loadDiagram() throws UdmException {
       metaDiagram = new Diagram(xmlMetaFile);
   }
   protected void createDataNetwork() throws UdmException {
       
       dataNetwork = new UdmPseudoDataNetwork(metaName);
       //dataNetwork = new UdmPseudoDataNetwork("SBML2Ex");
   }
   /*private void initAPIsXSDResources(String instanceFileName) 
   {
    try{
     File f = new File(instanceFileName);
     if (f.exists())
     {
             File dir = new File(f.getParent());
             if (dir.exists() && dir.isDirectory())
                Resource.copyResourceToDir(packagePath + xsdMetaFile, dir.getAbsolutePath());
             else 
                System.out.println("Parent dir does not exist");
             
             xsdMetaFile = dir.getAbsolutePath()+ File.separator+xsdMetaFile; 
     }
    } catch (Throwable t)
        {
        System.out.println("initAPIsXSDResources: " + t.getMessage());
        }
   }*/
   
   private void initStrXSDResources() throws UdmException
   {
    String xsd = Resource.copyResourceToStr(packagePath + xsdMetaFile);
    UdmHelper.StoreXsd(xsdMetaFile, xsd);
    
   }
   protected UdmPseudoObject openExistingDN(String instanceFileName) throws UdmException {
       return openExistingDNFromFile(instanceFileName);
   }
    
   protected UdmPseudoObject openExistingDNFromFile(String instanceFileName) throws UdmException {
       createDataNetwork();
       //initAPIsXSDResources(instanceFileName);
       //initStrXSDResources();
       dataNetwork.openExisting(instanceFileName, xsdMetaFile, UdmHelper.UPDN_CHANGES_LOST_DEFAULT);
       return dataNetwork.getRootObject();
   }
   protected UdmPseudoObject openExistingDNFromString(String xml) throws UdmException {
       createDataNetwork();
       //initStrXSDResources();
       dataNetwork.openExistingFromString(xml, xsdMetaFile);
       return dataNetwork.getRootObject();
   }
   
   protected UdmPseudoObject openExistingDNFromStream(InputStream in) throws UdmException {
       java.io.DataInputStream din = new java.io.DataInputStream(in);
       String xml= new String("");
       try
        {
        String line = null;     
        while((line=din.readLine()) != null)
        {
            xml += line+"\n";
        }
        }
       catch(IOException ex)
        {
        System.out.println("Error reading from stream: " + ex.getMessage());
        }
       finally
        {
    //  close stream
        try
            {
            din.close();
        }
        catch(Exception ex){}
       }        
       
       return openExistingDNFromString(xml);
   }
   protected UdmPseudoObject createNewDN(String instanceFileName, UdmPseudoObject rootMetaClass) throws UdmException {
    return createNewDNToFile(instanceFileName, rootMetaClass);
   }
   
   protected UdmPseudoObject createNewDNToFile(String instanceFileName, UdmPseudoObject rootMetaClass) throws UdmException {
        
       createDataNetwork();
       //initAPIsXSDResources(instanceFileName);
       //initStrXSDResources();
       dataNetwork.createNew(instanceFileName, xsdMetaFile, rootMetaClass, UdmHelper.UPDN_CHANGES_LOST_DEFAULT);
       return dataNetwork.getRootObject();
   }


   protected UdmPseudoObject createNewDNToString(UdmPseudoObject rootMetaClass) throws UdmException {
        
       createDataNetwork();
       //initStrXSDResources();
  
       dataNetwork.createNewToString(xsdMetaFile, rootMetaClass);
       return dataNetwork.getRootObject();
   }


}
