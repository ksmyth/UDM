#include "PythonAPIGen.h"

#include <iterator>

void GeneratePythonClass(const ::Uml::Class &cl, const string & pckg_hierarcy, const string& diagName);

//! Constructor.
/*!
  Creates and initializes the Python API generation.
*/
PythonAPIGen::PythonAPIGen( const ::Uml::Diagram &diagram
                       , const map<string, string>& ns_map
                       , const string& inputfile )
:   m_diagram( diagram ), m_ns_map( ns_map ), m_inputfile( inputfile )
{
}

//! Destructor.
/*!
  .
*/
PythonAPIGen::~PythonAPIGen ( void )
{
}
//================================================

//! Entry point of Python API generation.
/*!
  .
*/
void PythonAPIGen::generate()
{
  
  // Generate the Python version of the input UDM XML file
  //Utils::XML2Python( string( m_diagram.name() ) + "_udm_xml", m_inputfile, m_meta_dir );

 
   open();
	
	

  /*CREATE MODUL DESCRIPTION*/
  
  m_output << "\"\"\"Generated" << endl;
  //...................................
  m_output << "\"\"\"" << endl << endl;

  /*CREATE IMPORT*/
  m_output << "import sys" << endl;
  m_output << "import Uml" << endl;
  m_output << "from UdmPython import *" << endl << endl;


  /*GENERATE PYTHON CLASSES*/
  set< ::Uml::Class> uml_classes = m_diagram.classes();
  for( set< ::Uml::Class>::iterator uc_i = uml_classes.begin(); uc_i != uml_classes.end(); uc_i++ )
  {

	  ::Uml::Class currCls = *uc_i;
	  generateClass(currCls);  
	  
  }

  /*INITIALIZE THE META STATIC VARIABLES*/
  
  m_output << endl;
  m_output << "def init_meta(meta_map):" << endl;
  
  for( set< ::Uml::Class>::iterator uc_i = uml_classes.begin(); uc_i != uml_classes.end(); uc_i++ )
  {
	  ::Uml::Class currCls = *uc_i;
	   set<Uml::Class> bases = currCls .baseTypes();
	  m_output << "\t" << currCls.name() << ".meta = meta_map." << currCls.name() << endl;
  }

  m_output << endl << endl;

  /*INITIALIZE THE META STATIC VARIABLE*/

  m_output << "def initialize(meta_map, uml_meta_map):" << endl;
  m_output << "\t" << "try:" << endl;
  m_output << "\t\t" << "module_initialized" << endl;
  m_output << "\t" << "except NameError:" << endl;
  m_output << "\t\t" << "init_meta(meta_map)" << endl;
  m_output << "\t\t" << "module_initialized = True" << endl;
  m_output << "\t\t" << "if sys.modules[__name__] != Uml:" << endl;
  m_output << "\t\t\t" << "Uml.initialize(uml_meta_map, uml_meta_map)" << endl;
  m_output << endl;
	

  
  // close the file
  m_output.close();

}

void PythonAPIGen::open()
{
	//opening ofstream
	string fname = string(m_diagram.name());
	fname+=+".py";
	m_output.open(fname.c_str());

	if ( !m_output.good() )
		throw udm_exception( "Error opening for write "+fname );
}

void PythonAPIGen::generateClass(::Uml::Class &cls)
{
	m_output << "class " << cls.name() << "(UdmPython):" << endl;
	m_output << "\t\"\"\"Generated\"\"\"" << endl;

	generateAttributes(cls);
	
	//cast method
	m_output << "\t@staticmethod" << endl;
	m_output << "\tdef cast(obj):"<< endl;
	m_output << "\t\t\"\"\"Object cast\"\"\"" << endl;
	m_output << "\t\treturn " << cls.name() << "(obj)" << endl;
	m_output << "\t" << endl;

	//type method
	m_output << "\tdef type(self):"<< endl;
	m_output << "\t\t\"\"\"returning the type of object (Uml.Class)\"\"\"" << endl;
	m_output << "\t\treturn " << "Uml.Class.cast(self.meta)" << endl;
	m_output << "\t" << endl;

	generateChildrenAccess(cls);
	generateAssociations(cls);
}

void PythonAPIGen::generateAttributes(::Uml::Class &cls)
{
	
	set < ::Uml::Attribute> atts = cls.attributes();
	for ( set< ::Uml::Attribute>::iterator atts_i = atts.begin(); atts_i != atts.end(); atts_i++ )
	{
		string att_name = atts_i->name();

		// name of the attribute
		m_output << "\t#" << att_name << " = \"" << att_name << "\";" << endl;
		m_output << endl;
	}
}

void PythonAPIGen::generateChildrenAccess(::Uml::Class &cls)
{
  //childrens ---------------------------------------------------
  set<Uml::Class> allContainedClasses;

  // set of contained classes
  set< ::Uml::Class> conts = Uml::ContainedClasses( cls );
  for ( set< ::Uml::Class>::iterator c_i = conts.begin(); c_i != conts.end(); c_i++ )
  {
	// the descendants of the contained class
	set < ::Uml::Class> conts_der = Uml::DescendantClasses( *c_i );
	std::copy(conts_der.begin(), conts_der.end(), std::inserter(allContainedClasses, allContainedClasses.begin()));
  }

  {
	for ( set< ::Uml::Class>::iterator c_d_i = allContainedClasses.begin(); c_d_i != allContainedClasses.end(); c_d_i++ )
	{
	  if ( c_d_i->isAbstract() )
		continue; 

	  ::Uml::Composition comp = Uml::matchChildToParent( *c_d_i, cls );
	  string c_i_name = (*c_d_i).name();
	  string pkg_name = "";

	  // without child role
	  if ( comp )
	  {
		::Uml::CompositionChildRole ccr = comp.childRole();
		string ccr_name = ccr.name();

		if ( (ccr.max() == -1) || (ccr.max() > 1) )
		{
		  m_output << "\tdef " << "get" << c_i_name << "Children(self):" << endl;
		  m_output << "\t\t\"\"\"" << endl;
		  m_output << "\t\tReturns all the children of type <code>" << c_i_name << "<code> of this container. " << endl;
		  m_output << "\t\t@return  The children in a lisst" << endl;
		  m_output << "\t\t\"\"\"" << endl;

		  m_output << "\t\tchilds = self.impl.children(child_type=" << c_i_name << ".meta)" << endl;
		  m_output << "\t\tlist = []" << endl;
		  m_output << "\t\t" << "for i in childs:" << endl;
		  m_output << "\t\t\t" << "list.append(" << c_i_name << "(i))" << endl;
		  m_output << "\t\treturn list" << endl;
		  m_output << endl;
		  
		}
		else
		{
		  m_output << "\tdef " << "get" << c_i_name << "Child(self): " << endl;
		  m_output << "\t\t\"\"\"" << endl;
		  m_output << "\t\tReturn the child of type <code>" << c_i_name << "<code> of this container. " << endl;
		  m_output << "\t\t@return  The child" << endl;
		  m_output << "\t\t\"\"\"" << endl;
		  m_output << "\t\tchilds = self.impl.children(child_type=" << c_i_name << ".meta)" << endl;
		  m_output << "\t\t" << "if len(childs) > 0:" << endl;
		  m_output << "\t\t\t" << "return " << c_i_name << "(childs[0])" << endl;
		  m_output << "\t\t" << "else: " << endl;
		  m_output << "\t\t\t" << "return None" << endl;
		  m_output << "\t" << endl;
		
		  /*
		  if ( strcmp(ccr_name.c_str(), "") == 0 )
		  {
			m_output << "\t\t'''UdmPseudoObjectContainer container = getChildren(null, " ;
			m_output << pkg_name << c_i_name << ".META_TYPE, " << pkg_name << c_i_name << ".META_TYPE_NS); " << endl;
		  }
		  else
		  {
			m_output << "\t\tUdmPseudoObjectContainer container = getChildren(\"" << ccr_name << "\",";
			m_output << pkg_name << c_i_name << ".META_TYPE, " << pkg_name << c_i_name << ".META_TYPE_NS); " << endl;
		  }
		  */
		  
		  //m_output << "\t\tif (container.getLength() > 0)" << endl << endl;
		  //m_output << "\t\t\treturn (" << pkg_name << c_i_name << ")" << pkg_name << "Utils.wrapWithSubclass(container.getAt(0), metaDiagram);" << endl;
		  //m_output << "\t\treturn null;'''" << endl << endl;
		  //m_output << "\t" << endl << endl;
		}
	  }
	  // with child role
	  else
	  {
		//generate a common getter function for these types of children
		/*
		m_output << "\t'''" << endl;
		m_output << "\t * Returns all the children of type <code>" << c_i_name << "<code> of this container. " << endl;
		m_output << "\t * @return  The children in a list" << endl;
		m_output << "\t ''' " << endl;
		
		m_output << "\tdef " << "get" << c_i_name << "Children(self):" << endl;
		m_output << "\t" << endl;
		m_output << "\t\t'''UdmPseudoObjectContainer container = getChildren(null," ;
		m_output << pkg_name << c_i_name << ".META_TYPE, " << pkg_name << c_i_name << ".META_TYPE_NS);" << endl;
		m_output << "\t\t" << pkg_name << c_i_name << "[] array = new " << pkg_name << c_i_name << "[container.getLength()];" << endl;
		m_output << "\t\tfor (int i = 0; i < container.getLength(); i++) " << endl;
		m_output << "\t\t{" << endl;
		m_output << "\t\t\tarray[i] = (" << pkg_name << c_i_name << ")" << pkg_name << "Utils.wrapWithSubclass(container.getAt(i), metaDiagram);" << endl;
		m_output << "\t\t}" << endl;
		m_output << "\t\treturn array;'''" << endl;
		m_output << "\t" << endl;
		*/
		//end of common getter function generation

		set < ::Uml::CompositionChildRole> ccrs = ::Uml::CompositionPeerChildRoles( cls );
		for ( set< ::Uml::CompositionChildRole>::iterator ccrs_i = ccrs.begin(); ccrs_i != ccrs.end(); ccrs_i++ )
		{
		  ::Uml::Class parent = Uml::theOther(*ccrs_i).target();
		  ::Uml::Class child = ccrs_i->target();
		  string child_name = string(child.name());
		  
		  ::Uml::Composition comp = Uml::matchChildToParent( child, parent );

		  if ( !comp )
		  {
			//will reach here only if more than one composition is possible

			//string child role name
			string ccr_name = ccrs_i->name();
			m_output << "\t'''" << endl;
			m_output << "\t *  Composition role name <code>" << ccr_name << "</code>." << endl;
			m_output << "\t '''" << endl;
			
			m_output << endl << endl;

			//getRoleName
			if ( (ccrs_i->max() == -1) || (ccrs_i->max() > 1) )
			{
			  m_output << "\t'''" << endl;
			  m_output << "\t * Returns the children <code>" << child_name << "<code> of this container. " << endl;
			  m_output << "\t * which have role <code>" << ccr_name << "<code>." << endl;
			  m_output << "\t * @return  The children in an array" << endl;
			  m_output << "\t ''' " << endl;
			  
			  m_output << "\tdef " << "get" << ccr_name << "Children(self):" << endl;
			  
			  m_output << "\t" << endl;
			  m_output << "\t\t'''UdmPseudoObjectContainer container = getChildren(";
			  
			  m_output << "\t\t" << pkg_name << child_name << "[] array = new " << pkg_name << child_name << "[container.getLength()];" << endl;
			  m_output << "\t\tfor (int i = 0; i < container.getLength(); i++) " << endl;
			  m_output << "\t\t{" << endl;
			  m_output << "\t\t\tarray[i] = (" << pkg_name << child_name << ")" << pkg_name << "Utils.wrapWithSubclass(container.getAt(i), metaDiagram);" << endl;
			  m_output << "\t\t}" << endl;
			  m_output << "\t\treturn array;'''" << endl;
			  m_output << "\t" << endl;
			}
			else
			{
			  /*
			  m_output << "\t'''" << endl;
			  m_output << "\t * Returns the child <code>" << child_name << "<code> of this container. " << endl;
			  m_output << "\t * which has role <code>" << ccr_name << "<code>." << endl;
			  m_output << "\t * @return  The children in a list" << endl;
			  m_output << "\t ''' " << endl;
			  
			  m_output << "\tdef " << " get" << ccr_name << "Child(self):" << endl;
			  m_output << "\t" << endl;
			  m_output << "\t\t'''UdmPseudoObjectContainer container = getChildren(" ;
			  //m_output << Utils::getCCRString(*ccrs_i) << "," << pkg_name << child_name << ".META_TYPE, " << pkg_name << child_name << ".META_TYPE_NS);" << endl;
			  m_output << "\t\tif (container.getLength() > 0)" << endl << endl;
			  m_output << "\t\t\t return (" << pkg_name << child_name << ")" << pkg_name << "Utils.wrapWithSubclass(container.getAt(0), metaDiagram);" << endl;
			  m_output << "\t\treturn null;'''" << endl << endl;
			  m_output << "\t" << endl;
			  */
			}
		  } 
		} 
	  }
	}
  }
  //childrens end ----------------------------------------------------------------
}

void PythonAPIGen::generateAssociations(::Uml::Class &cls)
{

  m_output << "\t# Associations " << endl << endl;

  // association classes
  ::Uml::Association ass = Uml::GetAncestorAssociation( cls );

  if ( ass )
  {
	// set of association roles
	set < ::Uml::AssociationRole> ass_roles = ass.roles();
	for( set< ::Uml::AssociationRole>::iterator a_r_i = ass_roles.begin(); a_r_i != ass_roles.end(); a_r_i++ )
	{
	  ::Uml::Class target_cl = a_r_i->target();

	  string tname = target_cl.name();
	  string ar_name = a_r_i->name();

	  string pkg_name = "";//Utils::getPackageSignature(target_cl, m_ns_path, m_package_name);

	  m_output << "\t\"\"\"" << endl;
	  m_output << "\t Association with role name <code>" << ar_name << "</code>." << endl;
	  m_output << "\t\"\"\"" << endl;

	  // setter for the association
	  
	  //tname 
	  m_output << "\tdef set" << ar_name << "(self, a):" << endl;
	  m_output << "\t\t\"\"\"" << endl;
	  m_output << "\t\tSets the end of the association with role name <code>" << ar_name << "</code>." << endl;
	  m_output << "\t\t@param a The end of the association'''" << endl;
	  m_output << "\t\t\"\"\"" << endl;
	  
	  //m_output << "\t\t#UdmPseudoObjectContainer container = new UdmPseudoObjectContainer(1);" << endl;
	  //m_output << "\t\t#container.setAt(0, (UdmPseudoObject)a);" << endl;
	  //m_output << "\t\t#setAssociation(\"" << ar_name << "\", container, UdmHelper.TARGET_FROM_CLASS);" << endl;
	  m_output << "\t\tpass" << endl;

	  
	  // getter for the association
	  m_output << "\tdef " << "get" << ar_name << "(self):" << endl;
	  m_output << "\t\t\"\"\"" << endl;
	  m_output << "\t\tReturns the end of the association with role name <code>" << ar_name << "</code>." << endl;
	  m_output << "\t\t@return The end of the association" << endl;
	  m_output << "\t\t\"\"\"" << endl;
	  m_output << "\t\treturn " << tname << ".cast(self.impl.ar_name)" << endl;
	  //m_ioutput << "\tpublic " << pkg_name << tname << " get" << ar_name << "() throws UdmException;" << endl;
	  //m_output << "\t\tUdmPseudoObjectContainer container = getAssociation(\"" << ar_name << "\", UdmHelper.TARGET_FROM_CLASS);" << endl;
	  //m_output << "\t\tif (container.getLength() > 0)" << endl << endl;
	  //m_output << "\t\t\treturn (" << pkg_name << tname << ") " << pkg_name << "Utils.wrapWithSubclass(container.getAt(0), metaDiagram);" << endl;
	  //m_output << "\t\treturn null;" << endl << endl;
	  //m_output << "\t}" << endl;
	  m_output << "\t" << endl;
	} 
  }

	// associations
  // set of associations
  set < ::Uml::AssociationRole> assroles = cls.associationRoles();

  if ( assroles.size() )
	{
	for( set< ::Uml::AssociationRole>::iterator ar_i = assroles.begin(); ar_i != assroles.end(); ar_i++ )
	{
	  string asr_name = ar_i->name();
	  string to_asr_name = (string)Uml::theOther(*ar_i).name();

	  ::Uml::Class to_class = (::Uml::Class)((Uml::theOther(*ar_i)).target());
	  string helper_mode = "TARGET_FROM_PEER";
	  ::Uml::Association ass = ar_i->parent();
	  ::Uml::Class ass_class = ass.assocClass();

	  if ( ass_class )
	  {
		  to_class = ass_class;
		  helper_mode = "CLASS_FROM_TARGET";
	  }

	  string tname = to_class.name();

	  m_output << "\t\"\"\"" << endl;
	  m_output << "\t Association with role name <code>" << to_asr_name << "</code>." << endl;
	  m_output << "\t\"\"\"" << endl;
	  m_output << endl;

	  // the canonical form of the to_class
	  string pckg_signature = "";//Utils::getPackageSignature(to_class, m_ns_path, m_package_name);

	  if ( (Uml::theOther(*ar_i).max() == 0) || (Uml::theOther(*ar_i).max() == 1) )
	  {
		//single cardinality
		//method signature
		m_output << "\tdef " << "set" << to_asr_name << "(self," << " a): " << endl;//<< tname 
		
		//doc comment
		m_output << "\t\t\"\"\"" << endl;
		m_output << "\t\tSets the other end of the association with role name <code>" << to_asr_name << "</code>." << endl;
		m_output << "\t\t@param a The other end of the association" << endl;
		m_output << "\t\t\"\"\"" << endl;

		
		//m_output << "\t\t'''setAssociation(\"" << to_asr_name << "\", a, UdmHelper." << helper_mode << ");" << endl;
		m_output << "\t\tpass" << endl;
		m_output << endl;
		
		m_output << "\tdef " << to_asr_name << "(self):" << endl;

		m_output << "\t\t\"\"\" Returns the other end of the association with role name <code>" << to_asr_name << "</code>." << endl;
		m_output << "\t\t@return The other end of the association" << endl;
		m_output << "\t\t\"\"\"" << endl;
		//m_ioutput << "\tpublic " << pckg_signature << tname << " get" << to_asr_name << "() throws UdmException;" << endl;
		m_output << "\t\treturn " << tname << ".cast(self.impl." << to_asr_name << ")" << endl;
		/*
		if (isInterfaceNeeded(to_class)) {
			m_output << "\t\treturn (result == null) ? null : (" << pckg_signature << tname << ")Utils.wrapWithSubclass(new UdmPseudoObject(result, getDiagram()), getDiagram());" << endl;
		} else {
			m_output << "\t\treturn (result == null) ? null : new " << pckg_signature << tname << "(result, getDiagram());" << endl;
		}
		*/
		m_output << "\t" << endl;
		
	  }
	  else
	  {
		
		m_output << "\tdef set" << to_asr_name << "(self," << " a): " << endl; //tname []<<
		m_output << "\t\t\"\"\"" << endl;
		m_output << "\t\tSets the other ends of the association with role name <code>" << to_asr_name << "</code>." << endl;
		m_output << "\t\t@param a The other ends of the association" << endl;
		m_output << "\t\t\"\"\"" << endl;
		
		//m_output << "\t\t#setAssociation(\"" << to_asr_name << "\", new UdmPseudoObjectContainer(a), UdmHelper." << helper_mode << ");" << endl;
		m_output << "\t\tpass" << endl;
		m_output << endl;

		
		m_output << "\tdef " << to_asr_name << "(self):" << endl;
		m_output << "\t\t\"\"\"" << endl;
		m_output << "\t\tReturns the other ends of the association with role name <code>" << to_asr_name << "</code>." << endl;
		m_output << "\t\t@return The other ends of the association" << endl;
		m_output << "\t\t\"\"\" " << endl;
		//m_ioutput << "\tpublic " << pckg_signature << tname << "[] get" << to_asr_name << "() throws UdmException;" << endl;
		m_output << "\t\t" << "list = []" << endl;
		m_output << "\t\t" << "for i in self.impl." << to_asr_name << ":" << endl;
		m_output << "\t\t\t" << "list.append(" << tname << ".cast(i))" << endl;			 
		m_output << "\t\t" << "return list" << endl;
		m_output << "\t" << endl;
		m_output << endl;
	  }
	} 
  }
  
}
