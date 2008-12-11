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
 * Domain specific class of <code>annotation</code>.
 */ 
public class annotation extends UdmPseudoObject
{
	// meta information
	public static final String META_TYPE = "annotation";
	public static final String META_TYPE_NS = "sbml";
	private static UdmPseudoObject metaClass;

	/**
	 * Constructor.
	 * @param  upo The object that helps the initialization of the instance 
	 * @param  metaDiagram The diagram of the data network
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	protected annotation(UdmPseudoObject upo, Diagram metaDiagram) 
		throws UdmException
	{
		super(upo, metaDiagram);
	}

	/**
	 * Returns the meta class.
	 * @return  The meta class
	 */ 
	UdmPseudoObject getMetaClass()
	{
		return metaClass;
	}

	/* Construction */

	/**
	 * Creates an instance of the class in the container specified by the parameter. 
	 * @param  parent The parent container
	 * @return  An instance of the class <code>annotation</code>
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public static annotation create(SBase parent) 
		throws UdmException 
	{
		Diagram metaDiagram = parent.getDiagram();
		return new annotation(parent.createObject(META_TYPE, META_TYPE_NS), metaDiagram);
	}

	/* Accessing children */

	/**
	 * Return the child of type <code>gene<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.unigene.gene getgeneChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.unigene.gene.META_TYPE, edu.vanderbilt.isis.sbml2ex.unigene.gene.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (edu.vanderbilt.isis.sbml2ex.unigene.gene)edu.vanderbilt.isis.sbml2ex.unigene.Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>cluster_id<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.unigene.cluster_id getcluster_idChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.unigene.cluster_id.META_TYPE, edu.vanderbilt.isis.sbml2ex.unigene.cluster_id.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (edu.vanderbilt.isis.sbml2ex.unigene.cluster_id)edu.vanderbilt.isis.sbml2ex.unigene.Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>title<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.unigene.title gettitleChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.unigene.title.META_TYPE, edu.vanderbilt.isis.sbml2ex.unigene.title.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (edu.vanderbilt.isis.sbml2ex.unigene.title)edu.vanderbilt.isis.sbml2ex.unigene.Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>acc<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.unigene.acc getaccChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.unigene.acc.META_TYPE, edu.vanderbilt.isis.sbml2ex.unigene.acc.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (edu.vanderbilt.isis.sbml2ex.unigene.acc)edu.vanderbilt.isis.sbml2ex.unigene.Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>conservationlaw<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.jigcell.conservationlaw getconservationlawChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.jigcell.conservationlaw.META_TYPE, edu.vanderbilt.isis.sbml2ex.jigcell.conservationlaw.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (edu.vanderbilt.isis.sbml2ex.jigcell.conservationlaw)edu.vanderbilt.isis.sbml2ex.jigcell.Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>species<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.jigcell.species getspeciesChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.jigcell.species.META_TYPE, edu.vanderbilt.isis.sbml2ex.jigcell.species.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (edu.vanderbilt.isis.sbml2ex.jigcell.species)edu.vanderbilt.isis.sbml2ex.jigcell.Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>ratelaw<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.jigcell.ratelaw getratelawChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.jigcell.ratelaw.META_TYPE, edu.vanderbilt.isis.sbml2ex.jigcell.ratelaw.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (edu.vanderbilt.isis.sbml2ex.jigcell.ratelaw)edu.vanderbilt.isis.sbml2ex.jigcell.Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>blankline<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.jigcell.blankline getblanklineChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.jigcell.blankline.META_TYPE, edu.vanderbilt.isis.sbml2ex.jigcell.blankline.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (edu.vanderbilt.isis.sbml2ex.jigcell.blankline)edu.vanderbilt.isis.sbml2ex.jigcell.Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>otherDisplayObjects<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.jd.otherDisplayObjects getotherDisplayObjectsChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.jd.otherDisplayObjects.META_TYPE, edu.vanderbilt.isis.sbml2ex.jd.otherDisplayObjects.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (edu.vanderbilt.isis.sbml2ex.jd.otherDisplayObjects)edu.vanderbilt.isis.sbml2ex.jd.Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>arcSeg<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.jd.arcSeg getarcSegChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.jd.arcSeg.META_TYPE, edu.vanderbilt.isis.sbml2ex.jd.arcSeg.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (edu.vanderbilt.isis.sbml2ex.jd.arcSeg)edu.vanderbilt.isis.sbml2ex.jd.Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>display<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.jd.display getdisplayChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.jd.display.META_TYPE, edu.vanderbilt.isis.sbml2ex.jd.display.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (edu.vanderbilt.isis.sbml2ex.jd.display)edu.vanderbilt.isis.sbml2ex.jd.Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>limit<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.flux.limit getlimitChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.flux.limit.META_TYPE, edu.vanderbilt.isis.sbml2ex.flux.limit.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (edu.vanderbilt.isis.sbml2ex.flux.limit)edu.vanderbilt.isis.sbml2ex.flux.Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>listOfAnalyses<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.flux.listOfAnalyses getlistOfAnalysesChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.flux.listOfAnalyses.META_TYPE, edu.vanderbilt.isis.sbml2ex.flux.listOfAnalyses.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (edu.vanderbilt.isis.sbml2ex.flux.listOfAnalyses)edu.vanderbilt.isis.sbml2ex.flux.Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>listOfAnalysisTypes<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.flux.listOfAnalysisTypes getlistOfAnalysisTypesChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.flux.listOfAnalysisTypes.META_TYPE, edu.vanderbilt.isis.sbml2ex.flux.listOfAnalysisTypes.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (edu.vanderbilt.isis.sbml2ex.flux.listOfAnalysisTypes)edu.vanderbilt.isis.sbml2ex.flux.Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>user_def<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.dbi.user_def getuser_defChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.dbi.user_def.META_TYPE, edu.vanderbilt.isis.sbml2ex.dbi.user_def.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (edu.vanderbilt.isis.sbml2ex.dbi.user_def)edu.vanderbilt.isis.sbml2ex.dbi.Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>charon_annotation<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public edu.vanderbilt.isis.sbml2ex.bc.charon_annotation getcharon_annotationChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, edu.vanderbilt.isis.sbml2ex.bc.charon_annotation.META_TYPE, edu.vanderbilt.isis.sbml2ex.bc.charon_annotation.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (edu.vanderbilt.isis.sbml2ex.bc.charon_annotation)edu.vanderbilt.isis.sbml2ex.bc.Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/**
	 * Return the child of type <code>dialect<code> of this container. 
	 * @return  The child
	 * @throws  UdmException If any Udm related exception occured
	 */ 
	public dialect getdialectChild()
		throws UdmException 
	{
		UdmPseudoObjectContainer container = getChildren(null, dialect.META_TYPE, dialect.META_TYPE_NS); 
		if (container.getLength() > 0)

			return (dialect)Utils.wrapWithSubclass(container.getAt(0), metaDiagram);
		return null;

	}

	/* Attribute setters, getters */

	/* Associations */

}
