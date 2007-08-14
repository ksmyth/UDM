/*
 * Created on Apr 8, 2005
 *
 * Java version 1.4.2_04
 */
package edu.vanderbilt.isis.sbml2ex.test;

import java.io.IOException;
import java.io.InputStream;

import junit.framework.TestCase;
import edu.vanderbilt.isis.sbml2ex.FactoryRepository;
import edu.vanderbilt.isis.sbml2ex.math.apply;
import edu.vanderbilt.isis.sbml2ex.math.ci;
import edu.vanderbilt.isis.sbml2ex.math.cn;
import edu.vanderbilt.isis.sbml2ex.math.lambda;
import edu.vanderbilt.isis.sbml2ex.math.math;
import edu.vanderbilt.isis.sbml2ex.sbml.annotation;
import edu.vanderbilt.isis.sbml2ex.sbml.compartment;
import edu.vanderbilt.isis.sbml2ex.sbml.delay;
import edu.vanderbilt.isis.sbml2ex.sbml.dialect;
import edu.vanderbilt.isis.sbml2ex.sbml.event;
import edu.vanderbilt.isis.sbml2ex.sbml.functionDefinition;
import edu.vanderbilt.isis.sbml2ex.sbml.listOfCompartments;
import edu.vanderbilt.isis.sbml2ex.sbml.listOfEvents;
import edu.vanderbilt.isis.sbml2ex.sbml.listOfFunctionDefinitions;
import edu.vanderbilt.isis.sbml2ex.sbml.listOfSpecies;
import edu.vanderbilt.isis.sbml2ex.sbml.model;
import edu.vanderbilt.isis.sbml2ex.sbml.notes;
import edu.vanderbilt.isis.sbml2ex.sbml.sbml;
import edu.vanderbilt.isis.sbml2ex.sbml.sbmlFileFactory;
import edu.vanderbilt.isis.sbml2ex.sbml.species;
import edu.vanderbilt.isis.sbml2ex.unigene.acc;
import edu.vanderbilt.isis.sbml2ex.unigene.cluster_id;
import edu.vanderbilt.isis.sbml2ex.xhtml.head;
import edu.vanderbilt.isis.udm.UdmException;


/**
 * Test for SBML2Ex simple instance creation from file.
 *
 * @author nsomogyi
 *
 */
public class ReadFileTest extends TestCase {
    private static final String NEW_INSTANCE_FILE = "samples/NewEmptyInstanceFile.xml";

    /**
     * Fills the root object with some dummy data.
     * @param root
     * @throws UdmException
     */
    protected void fillSbml(sbml root) throws UdmException {
        // set the dialect
        annotation an = annotation.create(root);
        dialect di = dialect.create(an);
        di.setname("unigene");

        // create a model
        model mo = model.create(root);

        // create compartment
        listOfCompartments li = listOfCompartments.create(mo);
        compartment co = compartment.create(li);
        co.setid("compartment");

        // create some species with unigene annotation
        listOfSpecies lis = listOfSpecies.create(mo);
        species sp = species.create(lis);
        sp.setid("AA017353");
        sp.setcompartment("compartment");

        annotation ann = annotation.create(sp);
        acc _acc = acc.create(ann);
        _acc.setvalue("AA017353");

        edu.vanderbilt.isis.sbml2ex.unigene.title t =
            edu.vanderbilt.isis.sbml2ex.unigene.title.create(ann);
        t.setvalue("7-dehydrocholesterol reductase");

        cluster_id cid = cluster_id.create(ann);
        cid.setvalue("Hs.11806");

        edu.vanderbilt.isis.sbml2ex.unigene.gene g =
            edu.vanderbilt.isis.sbml2ex.unigene.gene.create(ann);
        g.setvalue("DHCR7");

        // create funtions with some math 
        listOfFunctionDefinitions lifd = listOfFunctionDefinitions.create(mo);
        functionDefinition fd = functionDefinition.create(lifd);
        math ma = math.create(fd);
        apply appl = apply.create(ma);
        cn _cn = cn.create(appl);
        _cn.settype("integer");
        _cn.setvalue("1");
    }

    /**
     * Prints the content of the specified input stream to the output.
     * @param is
     * @throws UdmException
     */
    protected void printInputStream(InputStream is) throws UdmException {
        java.io.DataInputStream din = new java.io.DataInputStream(is);
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
    }

    /**
     * Creates a new data network in a file.
     * @throws UdmException
     */
    public void testCreateBlankInstance() throws UdmException {
        sbmlFileFactory gtf = FactoryRepository.getsbmlsbmlFileFactory();
        sbml root = gtf.create(NEW_INSTANCE_FILE);

        System.out.println("\n------------\n");
        System.out.println(NEW_INSTANCE_FILE);

        fillSbml(root);
        printSBML(root);

        gtf.save();
    }


    /**
      * Opens an existing data network from a file.
      * @throws UdmException
      */
    public void testOpenExistingFromFile() throws UdmException {
        System.out.println("\n-----------------------------------");
        System.out.println("\tOpenExistingFromFile");
        System.out.println("-----------------------------------");

        /*readFileTest("samples/compOutRef.xml");
        readFileTest("samples/compUnitRef.xml");
        readFileTest("samples/delayLabelRef.xml");
        readFileTest("samples/eventUnitRef.xml");
        readFileTest("samples/eventVariableRef.xml");
        readFileTest("samples/functionLabelRef.xml");
        readFileTest("samples/invGlobalId.xml");
        readFileTest("samples/invParameterUnitRef.xml");
        readFileTest("samples/invReactParam.xml");
        readFileTest("samples/invReactRef.xml");
        readFileTest("samples/invSpCompartment.xml");
        readFileTest("samples/invSpeciesIC.xml");
        readFileTest("samples/invSpeciesUnitRef.xml");
        readFileTest("samples/invUnitDef.xml");
        readFileTest("samples/klawUnitRef.xml");
        readFileTest("samples/levelCheck.xml");
        readFileTest("samples/ruleLabelRef.xml");
        readFileTest("samples/ruleVariableRef.xml");
        readFileTest("samples/triggerLabelRef.xml");
        readFileTest("samples/unitDefs.xml");
        readFileTest("samples/uniqueRuleRef.xml");
        readFileTest("samples/versionCheck.xml");
        readFileTest("samples/l2v1-2D-compartments.xml");
        readFileTest("samples/l2v1-algebraic.xml");
        readFileTest("samples/l2v1-assignment.xml");
        readFileTest("samples/l2v1-boundary.xml");
        readFileTest("samples/l2v1-branch.xml");
        readFileTest("samples/l2v1-delay.xml");
        readFileTest("samples/l2v1-events.xml");
        readFileTest("samples/l2v1-functions.xml");
        readFileTest("samples/l2v1-mc-ode.xml");
        readFileTest("samples/l2v1-units.xml");

        //jigcell
        readFileTest("samples/yeastnew2_core.xml");
        readFileTest("samples/frogegg.xml");

        //bc
        readFileTest("samples/Lac_v1.2.2.xml");*/
        //dbi, unigene 
        readFileTest("samples/demo_30_paintfb_out.xml");
    }

    /**
     * Opens an existing data network from a file.
     * @throws UdmException
     */
    public void readFileTest(String fileName) throws UdmException {
        sbmlFileFactory gtf = FactoryRepository.getsbmlsbmlFileFactory();
        sbml root = gtf.open(fileName);

        System.out.println("\n------------\n");
        System.out.println(fileName);

        printSBML(root);

        gtf.close();
    }

    private void printSBML(sbml root) throws UdmException {
        // model child
        model m = root.getmodelChild();

        // note child
        notes n = m.getnotesChild();
        if (n != null) {
            head h = n.getheadChild();
            if (h != null) {
                edu.vanderbilt.isis.sbml2ex.xhtml.title t = h.gettitleChild();

                if (t != null) {
                    System.out.println("title " + t.getvalue());
                }
            }
        }

        // species
        listOfSpecies ls = m.getlistOfSpeciesChild();
        if (ls != null) {
            species[] sa = ls.getspeciesChildren();
            for (int i = 0; i < sa.length; i++) {
                System.out.print(sa[i].getid() + " ");
            }
            System.out.println();
        }

        // function defs
        listOfFunctionDefinitions fDefs = m.getlistOfFunctionDefinitionsChild();
        if (fDefs != null) {
            functionDefinition[] fDefA = fDefs.getfunctionDefinitionChildren();
            for (int i = 0; i < fDefA.length; i++) {
                functionDefinition fd = fDefA[i];
                System.out.println("functionDefinition " + fd.getid());

                math m_v = fd.getmathChild();

                apply[] appA = m_v.getapplyChildren();
                for (int k = 0; k < appA.length; k++) {
                    apply app = appA[k];

                    cn[] cnA = app.getcnChildren();
                    for (int l = 0; l < cnA.length; l++) {
                        cn cn_v = cnA[l];
                        System.out.println("cntype " + cn_v.gettype());
                        System.out.println("cnval " + cn_v.getvalue());
                    }

                    ci[] ciA = app.getciChildren();
                    for (int l = 0; l < ciA.length; l++) {
                        ci ci_v = ciA[l];
                        System.out.println("cival " + ci_v.getvalue());
                    }
                }

                lambda[] lmA = m_v.getlambdaChildren();
                for (int k = 0; k < lmA.length; k++) {
                    lambda lm_v = lmA[k];

                    apply[] appA2 = lm_v.getapplyChildren();
                    for (int l = 0; l < appA2.length; l++) {
                        apply app = appA2[l];

                        cn[] cnA = app.getcnChildren();
                        for (int x = 0; x < cnA.length; x++) {
                            cn cn_v = cnA[x];
                            System.out.println("cntype " + cn_v.gettype());
                            System.out.println("cnval " + cn_v.getvalue());
                        }

                        ci[] ciA = app.getciChildren();
                        for (int x = 0; x < ciA.length; x++) {
                            ci ci_v = ciA[x];
                            System.out.println("cival " + ci_v.getvalue());
                        }
                    }
                }
            }
        }

        // listOfEvents
        listOfEvents lEv = m.getlistOfEventsChild();
        if (lEv != null) {
            event[] evA = lEv.geteventChildren();
            for (int i = 0; i < evA.length; i++) {
                event e_v = evA[i];

                delay d_v = e_v.getdelayChild();

                math[] mvA = d_v.getmathChildren();
                for (int j = 0; j < mvA.length; j++) {
                    math m_v = mvA[j];

                    apply[] appA = m_v.getapplyChildren();
                    for (int k = 0; k < appA.length; k++) {
                        apply app = appA[k];

                        cn[] cnA = app.getcnChildren();
                        for (int l = 0; l < cnA.length; l++) {
                            cn cn_v = cnA[l];
                            System.out.println("cntype " + cn_v.gettype());
                            System.out.println("cnval " + cn_v.getvalue());
                        }

                        ci[] ciA = app.getciChildren();
                        for (int l = 0; l < ciA.length; l++) {
                            ci ci_v = ciA[l];
                            System.out.println("cival " + ci_v.getvalue());
                        }
                    }

                    lambda[] lmA = m_v.getlambdaChildren();
                    for (int k = 0; k < lmA.length; k++) {
                        lambda lm_v = lmA[k];

                        apply[] appA2 = lm_v.getapplyChildren();
                        for (int l = 0; l < appA2.length; l++) {
                            apply app = appA2[l];

                            cn[] cnA = app.getcnChildren();
                            for (int x = 0; x < cnA.length; x++) {
                                cn cn_v = cnA[x];
                                System.out.println("cntype " + cn_v.gettype());
                                System.out.println("cnval " + cn_v.getvalue());
                            }

                            ci[] ciA = app.getciChildren();
                            for (int x = 0; x < ciA.length; x++) {
                                ci ci_v = ciA[x];
                                System.out.println("cival " + ci_v.getvalue());
                            }
                        }
                    }
                }
            }
        }
    }
}
