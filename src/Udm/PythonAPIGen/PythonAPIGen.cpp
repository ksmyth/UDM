#include "../Udm.h"
#include "PythonAPIGen.h"

#include <iterator>


PythonInheritanceSolver::PythonInheritanceSolver(const Uml::Diagram &diagram, bool sort_by_namespace) : ::UdmCPPGen::InheritanceSolver(diagram, sort_by_namespace) {};
string PythonInheritanceSolver::getAncestorList(const ::Uml::Class &cl ) const
{
    string ret;
	typedef set< ::Uml::Class, ::UdmCPPGen::name_less<Uml::Class> > SortedClasses;
	::UdmCPPGen::name_less< ::Uml::Class> sort;
	SortedClasses bases = cl.baseTypes_sorted< ::UdmCPPGen::name_less<Uml::Class> >(sort);
	if( bases.size() == 0)
        ret += "(UdmPython)";
	else
	{
        ret += "(";
		string sep = "";
		SortedClasses::iterator h;
		for(h = bases.begin(); h != bases.end(); h++)
		{
			if(*h != cl)
			{
				ret += sep;
				ret += h->name();
				sep = ", ";
			}
		}
        ret += ")";
	}
    
	return ret;

}

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
  m_output << "import udm" << endl;
  m_output << "import Uml" << endl;
  m_output << "from UdmPython import *" << endl << endl;


    /*GENERATE PYTHON CLASSES*/
    set< ::Uml::Class> uml_classes = m_diagram.classes();
    PythonInheritanceSolver is(m_diagram);
    for ( vector < ::Uml::Class>::iterator gio_i = is.good_inheritence_order.begin(); gio_i != is.good_inheritence_order.end(); gio_i++)
        generateClass(*gio_i,is );
    
   

  /*INITIALIZE THE META STATIC VARIABLES*/
  
  
    m_output << endl;
    m_output << "def init_classes(diagram):" << endl;
    for( set< ::Uml::Class>::iterator uc_i = uml_classes.begin(); uc_i != uml_classes.end(); uc_i++ )
    {
        m_output << "\t" << uc_i->name() << ".Meta = GetUmlClassByName(diagram,\"" << uc_i->name()   << "\")"<< endl;
    }

    m_output << endl;
    m_output << "def init_attributes():" << endl;
    for( set< ::Uml::Class>::iterator uc_i = uml_classes.begin(); uc_i != uml_classes.end(); uc_i++ )
    {
        set< ::Uml::Attribute> attrs = uc_i->attributes();
        for( set< ::Uml::Attribute>::iterator attrs_i = attrs.begin(); attrs_i != attrs.end(); attrs_i++)
                m_output << "\t" << uc_i->name() << ".meta_" << attrs_i->name() << " = GetUmlAttributeByName(" << uc_i->name() << ".Meta, \"" << attrs_i->name() << "\")"<< endl;
    }
    m_output << endl;
    m_output << "def init_childroles():" << endl;
    for( set< ::Uml::Class>::iterator uc_i = uml_classes.begin(); uc_i != uml_classes.end(); uc_i++ )
    {
        ::Uml::Class c = *uc_i;
        string cl_name = c.name();
        
        set< ::Uml::Class> childrenkinds;
        set< ::Uml::CompositionParentRole> children = c.parentRoles();
        
        for( set< ::Uml::CompositionParentRole>::iterator i = children.begin(); i != children.end(); i++)
        {
            ::Uml::CompositionChildRole the_other = Uml::theOther(*i);
            
            ::Uml::Class thischildkind = (::Uml::Class)the_other.target();
            //childrenkinds.insert(thischildkind);
            
            string rel_name = ::Uml::MakeRoleName(the_other);
            
            m_output << "\t" << cl_name << ".meta_" << rel_name << " = GetUmlChildRoleByTypesAndRolenames(" << thischildkind.name() << ".Meta," << cl_name << ".Meta, \"" << the_other.name() <<  "\", \"" << i->name() << "\")" << endl;

        }
        
    }
    
    m_output << endl;
    m_output << "def init_parentroles():" << endl;
    for( set< ::Uml::Class>::iterator uc_i = uml_classes.begin(); uc_i != uml_classes.end(); uc_i++ )
    {
        ::Uml::Class c = *uc_i;
        string cl_name = c.name();
        
        set< ::Uml::Class> parentkinds;
        set< ::Uml::CompositionChildRole> parents = c.childRoles();
        
        for( set< ::Uml::CompositionChildRole>::iterator i = parents.begin(); i != parents.end(); i++)
        {
            ::Uml::CompositionParentRole the_other = Uml::theOther(*i);
            
            ::Uml::Class thisparentkind = (::Uml::Class)the_other.target();
            //parentkinds.insert(thischildkind);
            
            string rel_name = ::Uml::MakeRoleName(the_other);
            
            m_output << "\t" << cl_name << ".meta_" << rel_name << " = GetUmlParentRoleByTypesAndRolenames(" << cl_name << ".Meta," << thisparentkind.name() << ".Meta, \"" << i->name() <<  "\", \"" << the_other.name() << "\")" << endl;
        }
        
    }
    
		

  m_output << endl << endl;

  /*INITIALIZE THE META STATIC VARIABLE*/

    m_output << "def initialize(diagram):" << endl;
    m_output << "\t" << "try:" << endl;
    m_output << "\t\t" << "module_initialized" << endl;
    m_output << "\t" << "except NameError:" << endl;
    m_output << "\t\t" << "if sys.modules[__name__] != Uml:" << endl;
    m_output << "\t\t\t" << "Uml.initialize(udm.uml_diagram())" << endl;
    m_output << "\t\t" << "if sys.modules[__name__] == Uml:" << endl;
    m_output << "\t\t\t" << "meta_map = udm.map_uml_names(diagram)" << endl;
    m_output << "\t\t\t" << "#the only meta-object needed to bootstrap" << endl;
    m_output << "\t\t\t" << "Class.Meta = meta_map.Class" << endl;
    m_output << "\t\t" << "init_classes(Uml.Diagram(diagram))" << endl;
    m_output << "\t\t" << "init_childroles()" << endl;
    m_output << "\t\t" << "init_parentroles()" << endl;
    m_output << "\t\t" << "init_attributes()" << endl;
    m_output << "\t\t" << "module_initialized = True" << endl;
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

void PythonAPIGen::generateClass(::Uml::Class &cls, const PythonInheritanceSolver &is)
{

	m_output << "class " << cls.name() << is.getAncestorList(cls) <<  ":" << endl;
   	m_output << "\t\"\"\"Generated\"\"\"" << endl;
    m_output << "\t@property" << endl;
    m_output << "\tdef parent(self):" << endl;
    m_output << "\t\tparent_o = super(" << cls.name() << ", self).parent" << endl;
    m_output << "\t\treturn globals()[parent_o._type().name](parent_o) " << endl;

	generateAttributes(cls);
	
	//cast method
	m_output << "\t@staticmethod" << endl;
	m_output << "\tdef cast(obj):"<< endl;
	m_output << "\t\t\"\"\"Object cast\"\"\"" << endl;
	m_output << "\t\treturn " << cls.name() << "(obj)" << endl;
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
        if ((atts_i->max() > 1) || (atts_i->max() == -1) )
		{
            m_output << "\tdef " << att_name << "(self):" << endl;
            
            if (atts_i->type() == "String" )
                m_output << "\t\t return StrArrayAttr(self, " << cls.name() << ".meta_" <<  atts_i->name() << ")"<< endl;
            if (atts_i->type() == "Real" )
                m_output << "\t\t return RealArrayAttr(self, " << cls.name() << ".meta_" <<  atts_i->name() <<")"<<  endl;
            if (atts_i->type() == "Boolean" )
                m_output << "\t\t return BooleanArrayAttr(self, " << cls.name() << ".meta_" <<  atts_i->name() <<")"<<  endl;
            if (atts_i->type() == "Integer" )
                m_output << "\t\t return IntArrayAttr(self, " << cls.name() << ".meta_" <<  atts_i->name() << ")"<< endl;
            m_output << endl;
        }
	}
}

void PythonAPIGen::generateChildrenAccess(::Uml::Class &cls)
{
    
    string cl_name = cls.name();
    
	set< ::Uml::Class> childrenkinds;
	set< ::Uml::CompositionParentRole> children = cls.parentRoles();
    
    for( set< ::Uml::CompositionParentRole>::iterator i = children.begin(); i != children.end(); i++)
	{
        ::Uml::CompositionChildRole the_other = Uml::theOther(*i);
        
		::Uml::Class thischildkind = (::Uml::Class)the_other.target();
		childrenkinds.insert(thischildkind);
        
		string rel_name = ::Uml::MakeRoleName(the_other);
		
        if (the_other.isNavigable())
        {
            m_output << "\tdef " << rel_name << "(self):" <<endl;
            
            if(the_other.max() == 1)
            {
                m_output << "\t\t# return the single child contained via rolename: " << the_other.name() << ", rel_name: " << rel_name << endl;
                m_output << "\t\tchilds = self.children(child_role=" << cl_name << ".meta_" << rel_name <<")" << endl;
                m_output << "\t\t" << "if len(childs) > 0:" << endl;
                m_output << "\t\t\t" << "return globals()[childs[0]._type().name](childs[0])" << endl;
                m_output << "\t\t" << "else: " << endl;
                m_output << "\t\t\t" << "return None" << endl;
                
            }
            else
            {
                m_output << "\t\t# return the children contained via rolename: " << the_other.name() << ", rel_name: " << rel_name << endl;
                m_output << "\t\tchilds = self.children(child_role=" << cl_name << ".meta_" << rel_name <<")" << endl;
                m_output << "\t\tlist = []" << endl;
                m_output << "\t\t" << "for i in childs:" << endl;
                m_output << "\t\t\t" << "list.append(globals()[i._type().name](i))"  << endl;
                m_output << "\t\treturn list" << endl;
                
            }
        }
        else m_output << "\t# access method for non-navigable association " << rel_name << " omitted";
    }
    
    
    ::Uml::Diagram dgr = ::Uml::GetDiagram(cls);
	::Uml::DiagramClasses allclasses = ::Uml::DiagramClasses(dgr);
    
	for (::Uml::DiagramClasses::iterator j = allclasses.begin(); j != allclasses.end(); j++)
	{
		for (set< ::Uml::Class>::iterator k = childrenkinds.begin(); k != childrenkinds.end(); k++)
		{
			if (Uml::IsDerivedFrom(*j, *k) || Uml::IsDerivedFrom(*k, *j))
			{
				string kind_children_name = j->name();
				
                
                m_output << "\tdef " << kind_children_name << "_kind_children(self):" << endl;
                m_output << "\t\t# return the children of type: "  << kind_children_name << endl;
                m_output << "\t\tchilds = self.children(child_type=" << kind_children_name << ".Meta)" << endl;
                m_output << "\t\tlist = []" << endl;
                m_output << "\t\t" << "for i in childs:" << endl;
                m_output << "\t\t\t" << "list.append(globals()[i._type().name](i))"  << endl;
                m_output << "\t\treturn list" << endl;


				break;
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