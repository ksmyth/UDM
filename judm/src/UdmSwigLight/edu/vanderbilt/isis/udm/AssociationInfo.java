/**
 * Created on Jan 6, 2005
 */
package edu.vanderbilt.isis.udm;

import java.util.logging.Logger;

import edu.vanderbilt.isis.udm.swig.cint_string;

/**
 * Holds information about an association between objects
 * 
 * @author Himanshu Neema
 */
public class AssociationInfo {
    private static final Logger log = Logger.getLogger(AssociationInfo.class.getName());
    private edu.vanderbilt.isis.udm.swig.AssociationInfo swigAssoInfo;
    
    public AssociationInfo(String src, String dst, String assoc) {
        log.finer("new AssociationInfo(\"" + src +"\",\"" + dst + "\",\"" + assoc + "\");");
        swigAssoInfo = new edu.vanderbilt.isis.udm.swig.AssociationInfo(src, dst, assoc);
    }

    /**
     * A package private method
     */
    edu.vanderbilt.isis.udm.swig.AssociationInfo getInternal() {
        return swigAssoInfo;
    }

    public void setAssociationClass(String associationClass) {
        cint_string swigAssociationClass = new cint_string(associationClass);
        log.finer("AssocationInfo.setAssoc_class(new cint_string(\"" + associationClass + "\"))");
        swigAssoInfo.setAssoc_class(swigAssociationClass);
    }

    public String getAssociationClass() {
        log.finer("cint_string swigAssocClass = AssociationInfo.getAssoc_class();");
        cint_string swigAssociationClass = swigAssoInfo.getAssoc_class();
        if (swigAssociationClass == null) {
            return null;
        }
        log.finer("swigAssocClass.buffer();");
        return swigAssociationClass.buffer();
    }

    public void setSrcRolename(String srcRolename) {
        cint_string swigSrcRolename = new cint_string(srcRolename);
        log.finer("AssocationInfo.setSrcRolename(new cint_string(\"" + srcRolename + "\"));");
        swigAssoInfo.setSrcRolename(swigSrcRolename);
    }
    
    public String getSrcRolename() {
        log.finer("cint_string swigSrcRolename = AssociationInfo.getSrcRolename();");
        cint_string swigSrcRolename = swigAssoInfo.getSrcRolename();
        if (swigSrcRolename == null) {
            return null;
        }
        log.finer("swigSrcRolename.buffer();");
        return swigSrcRolename.buffer();
    }

    public void setDstRolename(String dstRolename) {
        cint_string swigDstRolename = new cint_string(dstRolename);
        log.finer("AssocationInfo.setDstRolename(new cint_string(\"" + dstRolename + "\"));");
        swigAssoInfo.setDstRolename(swigDstRolename);
    }

    public String getDstRolename() {
        log.finer("cint_string swigDstRolename = AssociationInfo.getDstRolename();");
        cint_string swigDstRolename = swigAssoInfo.getDstRolename();
        if (swigDstRolename == null) {
            return null;
        }
        log.finer("swigDstRolename.buffer();");
        return swigDstRolename.buffer();
    }
}
