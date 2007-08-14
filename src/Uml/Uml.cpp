// cpp source file Uml.cpp generated from diagram Uml
// generated on Sat Jul 02 23:17:41 2005

#include "Uml.h"
#include "UmlExt.h"

#include "UdmDom.h"
#include "Uml_xsd.h"

namespace Uml {

	::Uml::Diagram umldiagram;

		::Uml::Namespace meta;

		::Uml::Class CompositionChildRole::meta;
		::Uml::Class Diagram::meta;
		::Uml::Class CompositionParentRole::meta;
		::Uml::Class AssociationRole::meta;
		::Uml::Class Association::meta;
		::Uml::Class TaggedValue::meta;
		::Uml::Class Composition::meta;
		::Uml::Class Namespace::meta;
		::Uml::Class Class::meta;
		::Uml::Class Constraint::meta;
		::Uml::Class GenericRole::meta;
		::Uml::Class Attribute::meta;
		::Uml::Class ConstraintDefinition::meta;
		::Uml::Attribute CompositionChildRole::meta_max;
		::Uml::Attribute CompositionChildRole::meta_min;
		::Uml::Attribute Diagram::meta_version;
		::Uml::Attribute Diagram::meta_name;
		::Uml::Attribute AssociationRole::meta_max;
		::Uml::Attribute AssociationRole::meta_min;
		::Uml::Attribute AssociationRole::meta_isPrimary;
		::Uml::Attribute Association::meta_nonpersistent;
		::Uml::Attribute Association::meta_name;
		::Uml::Attribute TaggedValue::meta_value;
		::Uml::Attribute TaggedValue::meta_name;
		::Uml::Attribute Composition::meta_nonpersistent;
		::Uml::Attribute Composition::meta_name;
		::Uml::Attribute Namespace::meta_name;
		::Uml::Attribute Class::meta_isAbstract;
		::Uml::Attribute Class::meta_stereotype;
		::Uml::Attribute Class::meta_name;
		::Uml::Attribute Class::meta_from;
		::Uml::Attribute Constraint::meta_description;
		::Uml::Attribute Constraint::meta_name;
		::Uml::Attribute Constraint::meta_expression;
		::Uml::Attribute GenericRole::meta_isNavigable;
		::Uml::Attribute GenericRole::meta_name;
		::Uml::Attribute Attribute::meta_name;
		::Uml::Attribute Attribute::meta_type;
		::Uml::Attribute Attribute::meta_defvalue;
		::Uml::Attribute Attribute::meta_min;
		::Uml::Attribute Attribute::meta_max;
		::Uml::Attribute Attribute::meta_visibility;
		::Uml::Attribute Attribute::meta_ordered;
		::Uml::Attribute Attribute::meta_nonpersistent;
		::Uml::Attribute Attribute::meta_registry;
		::Uml::Attribute ConstraintDefinition::meta_stereotype;
		::Uml::Attribute ConstraintDefinition::meta_name;
		::Uml::Attribute ConstraintDefinition::meta_parameterList;
		::Uml::Attribute ConstraintDefinition::meta_expression;
		::Uml::Attribute ConstraintDefinition::meta_returnType;
		::Uml::AssociationRole CompositionChildRole::meta_target;
		::Uml::AssociationRole CompositionParentRole::meta_target;
		::Uml::AssociationRole AssociationRole::meta_target;
		::Uml::AssociationRole Association::meta_assocClass;
		::Uml::AssociationRole Class::meta_childRoles;
		::Uml::AssociationRole Class::meta_parentRoles;
		::Uml::AssociationRole Class::meta_associationRoles;
		::Uml::AssociationRole Class::meta_association;
		::Uml::AssociationRole Class::meta_baseTypes;
		::Uml::AssociationRole Class::meta_subTypes;
		::Uml::CompositionParentRole CompositionChildRole::meta_parent;
		::Uml::CompositionParentRole CompositionParentRole::meta_parent;
		::Uml::CompositionParentRole AssociationRole::meta_parent;
		::Uml::CompositionParentRole Association::meta_parent;
		::Uml::CompositionParentRole TaggedValue::meta_classParent;
		::Uml::CompositionParentRole TaggedValue::meta_assocParent;
		::Uml::CompositionParentRole Composition::meta_parent;
		::Uml::CompositionParentRole Namespace::meta_parent;
		::Uml::CompositionParentRole Class::meta_parent;
		::Uml::CompositionParentRole Constraint::meta_parent;
		::Uml::CompositionParentRole Attribute::meta_parent;
		::Uml::CompositionParentRole ConstraintDefinition::meta_parent;
		::Uml::CompositionChildRole Diagram::meta_namespaces;
		::Uml::CompositionChildRole Association::meta_tagValues;
		::Uml::CompositionChildRole Association::meta_roles;
		::Uml::CompositionChildRole Composition::meta_childRole;
		::Uml::CompositionChildRole Composition::meta_parentRole;
		::Uml::CompositionChildRole Namespace::meta_compositions;
		::Uml::CompositionChildRole Namespace::meta_classes;
		::Uml::CompositionChildRole Namespace::meta_associations;
		::Uml::CompositionChildRole Class::meta_attributes;
		::Uml::CompositionChildRole Class::meta_definitions;
		::Uml::CompositionChildRole Class::meta_constraints;
		::Uml::CompositionChildRole Class::meta_tagValues;
		UDM_DLL void InitializeNS()
		{
			CompositionChildRole::meta = ::Uml::CreateClass();
			Diagram::meta = ::Uml::CreateClass();
			CompositionParentRole::meta = ::Uml::CreateClass();
			AssociationRole::meta = ::Uml::CreateClass();
			Association::meta = ::Uml::CreateClass();
			TaggedValue::meta = ::Uml::CreateClass();
			Composition::meta = ::Uml::CreateClass();
			Namespace::meta = ::Uml::CreateClass();
			Class::meta = ::Uml::CreateClass();
			Constraint::meta = ::Uml::CreateClass();
			GenericRole::meta = ::Uml::CreateClass();
			Attribute::meta = ::Uml::CreateClass();
			ConstraintDefinition::meta = ::Uml::CreateClass();
			CompositionChildRole::meta_max = ::Uml::CreateAttribute();
			CompositionChildRole::meta_min = ::Uml::CreateAttribute();
			Diagram::meta_version = ::Uml::CreateAttribute();
			Diagram::meta_name = ::Uml::CreateAttribute();
			AssociationRole::meta_max = ::Uml::CreateAttribute();
			AssociationRole::meta_min = ::Uml::CreateAttribute();
			AssociationRole::meta_isPrimary = ::Uml::CreateAttribute();
			Association::meta_nonpersistent = ::Uml::CreateAttribute();
			Association::meta_name = ::Uml::CreateAttribute();
			TaggedValue::meta_value = ::Uml::CreateAttribute();
			TaggedValue::meta_name = ::Uml::CreateAttribute();
			Composition::meta_nonpersistent = ::Uml::CreateAttribute();
			Composition::meta_name = ::Uml::CreateAttribute();
			Namespace::meta_name = ::Uml::CreateAttribute();
			Class::meta_isAbstract = ::Uml::CreateAttribute();
			Class::meta_stereotype = ::Uml::CreateAttribute();
			Class::meta_name = ::Uml::CreateAttribute();
			Class::meta_from = ::Uml::CreateAttribute();
			Constraint::meta_description = ::Uml::CreateAttribute();
			Constraint::meta_name = ::Uml::CreateAttribute();
			Constraint::meta_expression = ::Uml::CreateAttribute();
			GenericRole::meta_isNavigable = ::Uml::CreateAttribute();
			GenericRole::meta_name = ::Uml::CreateAttribute();
			Attribute::meta_name = ::Uml::CreateAttribute();
			Attribute::meta_type = ::Uml::CreateAttribute();
			Attribute::meta_defvalue = ::Uml::CreateAttribute();
			Attribute::meta_min = ::Uml::CreateAttribute();
			Attribute::meta_max = ::Uml::CreateAttribute();
			Attribute::meta_visibility = ::Uml::CreateAttribute();
			Attribute::meta_ordered = ::Uml::CreateAttribute();
			Attribute::meta_nonpersistent = ::Uml::CreateAttribute();
			Attribute::meta_registry = ::Uml::CreateAttribute();
			ConstraintDefinition::meta_stereotype = ::Uml::CreateAttribute();
			ConstraintDefinition::meta_name = ::Uml::CreateAttribute();
			ConstraintDefinition::meta_parameterList = ::Uml::CreateAttribute();
			ConstraintDefinition::meta_expression = ::Uml::CreateAttribute();
			ConstraintDefinition::meta_returnType = ::Uml::CreateAttribute();
			CompositionChildRole::meta_target = ::Uml::CreateAssociationRole();
			CompositionParentRole::meta_target = ::Uml::CreateAssociationRole();
			AssociationRole::meta_target = ::Uml::CreateAssociationRole();
			Association::meta_assocClass = ::Uml::CreateAssociationRole();
			Class::meta_childRoles = ::Uml::CreateAssociationRole();
			Class::meta_parentRoles = ::Uml::CreateAssociationRole();
			Class::meta_associationRoles = ::Uml::CreateAssociationRole();
			Class::meta_association = ::Uml::CreateAssociationRole();
			Class::meta_baseTypes = ::Uml::CreateAssociationRole();
			Class::meta_subTypes = ::Uml::CreateAssociationRole();
			CompositionChildRole::meta_parent = ::Uml::CreateCompositionParentRole();
			CompositionParentRole::meta_parent = ::Uml::CreateCompositionParentRole();
			AssociationRole::meta_parent = ::Uml::CreateCompositionParentRole();
			Association::meta_parent = ::Uml::CreateCompositionParentRole();
			TaggedValue::meta_classParent = ::Uml::CreateCompositionParentRole();
			TaggedValue::meta_assocParent = ::Uml::CreateCompositionParentRole();
			Composition::meta_parent = ::Uml::CreateCompositionParentRole();
			Namespace::meta_parent = ::Uml::CreateCompositionParentRole();
			Class::meta_parent = ::Uml::CreateCompositionParentRole();
			Constraint::meta_parent = ::Uml::CreateCompositionParentRole();
			Attribute::meta_parent = ::Uml::CreateCompositionParentRole();
			ConstraintDefinition::meta_parent = ::Uml::CreateCompositionParentRole();
			Diagram::meta_namespaces = ::Uml::CreateCompositionChildRole();
			Association::meta_tagValues = ::Uml::CreateCompositionChildRole();
			Association::meta_roles = ::Uml::CreateCompositionChildRole();
			Composition::meta_childRole = ::Uml::CreateCompositionChildRole();
			Composition::meta_parentRole = ::Uml::CreateCompositionChildRole();
			Namespace::meta_compositions = ::Uml::CreateCompositionChildRole();
			Namespace::meta_classes = ::Uml::CreateCompositionChildRole();
			Namespace::meta_associations = ::Uml::CreateCompositionChildRole();
			Class::meta_attributes = ::Uml::CreateCompositionChildRole();
			Class::meta_definitions = ::Uml::CreateCompositionChildRole();
			Class::meta_constraints = ::Uml::CreateCompositionChildRole();
			Class::meta_tagValues = ::Uml::CreateCompositionChildRole();
		
			::Uml::InitClass(CompositionChildRole::meta, meta, "CompositionChildRole", false);
			::Uml::InitClass(Diagram::meta, meta, "Diagram", false);
			::Uml::InitClass(CompositionParentRole::meta, meta, "CompositionParentRole", false);
			::Uml::InitClass(AssociationRole::meta, meta, "AssociationRole", false);
			::Uml::InitClass(Association::meta, meta, "Association", false);
			::Uml::InitClass(TaggedValue::meta, meta, "TaggedValue", false);
			::Uml::InitClass(Composition::meta, meta, "Composition", false);
			::Uml::InitClass(Namespace::meta, meta, "Namespace", false);
			::Uml::InitClass(Class::meta, meta, "Class", false);
			::Uml::InitClass(Constraint::meta, meta, "Constraint", false);
			::Uml::InitClass(GenericRole::meta, meta, "GenericRole", true);
			::Uml::InitClass(Attribute::meta, meta, "Attribute", false);
			::Uml::InitClass(ConstraintDefinition::meta, meta, "ConstraintDefinition", false);
		
			::Uml::InitAttribute(CompositionChildRole::meta_max, CompositionChildRole::meta, "max", "Integer", false, false, 1, 1, false, "public");
			::Uml::InitAttribute(CompositionChildRole::meta_min, CompositionChildRole::meta, "min", "Integer", false, false, 1, 1, false, "public");
			::Uml::InitAttribute(Diagram::meta_version, Diagram::meta, "version", "String", false, false, 0, 1, false, "public");
			::Uml::InitAttribute(Diagram::meta_name, Diagram::meta, "name", "String", false, false, 1, 1, false, "public");
			::Uml::InitAttribute(AssociationRole::meta_max, AssociationRole::meta, "max", "Integer", false, false, 1, 1, false, "public");
			::Uml::InitAttribute(AssociationRole::meta_min, AssociationRole::meta, "min", "Integer", false, false, 1, 1, false, "public");
			vector<string> AssociationRole_isPrimary_dva;
			AssociationRole_isPrimary_dva.push_back("false");
			::Uml::InitAttribute(AssociationRole::meta_isPrimary, AssociationRole::meta, "isPrimary", "Boolean", false, false, 0, 1, false, "public", AssociationRole_isPrimary_dva);
			vector<string> Association_nonpersistent_dva;
			Association_nonpersistent_dva.push_back("false");
			::Uml::InitAttribute(Association::meta_nonpersistent, Association::meta, "nonpersistent", "Boolean", false, false, 0, 1, false, "public", Association_nonpersistent_dva);
			::Uml::InitAttribute(Association::meta_name, Association::meta, "name", "String", false, false, 0, 1, false, "public");
			::Uml::InitAttribute(TaggedValue::meta_value, TaggedValue::meta, "value", "String", false, false, 0, 1, false, "public");
			::Uml::InitAttribute(TaggedValue::meta_name, TaggedValue::meta, "name", "String", false, false, 1, 1, false, "public");
			vector<string> Composition_nonpersistent_dva;
			Composition_nonpersistent_dva.push_back("false");
			::Uml::InitAttribute(Composition::meta_nonpersistent, Composition::meta, "nonpersistent", "Boolean", false, false, 0, 1, false, "public", Composition_nonpersistent_dva);
			::Uml::InitAttribute(Composition::meta_name, Composition::meta, "name", "String", false, false, 0, 1, false, "public");
			::Uml::InitAttribute(Namespace::meta_name, Namespace::meta, "name", "String", false, false, 1, 1, false, "public");
			::Uml::InitAttribute(Class::meta_isAbstract, Class::meta, "isAbstract", "Boolean", false, false, 1, 1, false, "public");
			::Uml::InitAttribute(Class::meta_stereotype, Class::meta, "stereotype", "String", false, false, 0, 1, false, "public");
			::Uml::InitAttribute(Class::meta_name, Class::meta, "name", "String", false, false, 1, 1, false, "public");
			::Uml::InitAttribute(Class::meta_from, Class::meta, "from", "String", false, false, 0, 1, false, "public");
			::Uml::InitAttribute(Constraint::meta_description, Constraint::meta, "description", "String", false, false, 0, 1, false, "public");
			::Uml::InitAttribute(Constraint::meta_name, Constraint::meta, "name", "String", false, false, 1, 1, false, "public");
			::Uml::InitAttribute(Constraint::meta_expression, Constraint::meta, "expression", "String", false, false, 1, 1, false, "public");
			vector<string> GenericRole_isNavigable_dva;
			GenericRole_isNavigable_dva.push_back("true");
			::Uml::InitAttribute(GenericRole::meta_isNavigable, GenericRole::meta, "isNavigable", "Boolean", false, false, 0, 1, false, "public", GenericRole_isNavigable_dva);
			::Uml::InitAttribute(GenericRole::meta_name, GenericRole::meta, "name", "String", false, false, 0, 1, false, "public");
			::Uml::InitAttribute(Attribute::meta_name, Attribute::meta, "name", "String", false, false, 1, 1, false, "public");
			::Uml::InitAttribute(Attribute::meta_type, Attribute::meta, "type", "String", false, false, 1, 1, false, "public");
			::Uml::InitAttribute(Attribute::meta_defvalue, Attribute::meta, "defvalue", "String", false, false, 0, -1, false, "public");
			::Uml::InitAttribute(Attribute::meta_min, Attribute::meta, "min", "Integer", false, false, 1, 1, false, "public");
			::Uml::InitAttribute(Attribute::meta_max, Attribute::meta, "max", "Integer", false, false, 1, 1, false, "public");
			vector<string> Attribute_visibility_dva;
			Attribute_visibility_dva.push_back("public");
			::Uml::InitAttribute(Attribute::meta_visibility, Attribute::meta, "visibility", "String", false, false, 0, 1, false, "public", Attribute_visibility_dva);
			vector<string> Attribute_ordered_dva;
			Attribute_ordered_dva.push_back("false");
			::Uml::InitAttribute(Attribute::meta_ordered, Attribute::meta, "ordered", "Boolean", false, false, 0, 1, false, "public", Attribute_ordered_dva);
			vector<string> Attribute_nonpersistent_dva;
			Attribute_nonpersistent_dva.push_back("false");
			::Uml::InitAttribute(Attribute::meta_nonpersistent, Attribute::meta, "nonpersistent", "Boolean", false, false, 0, 1, false, "public", Attribute_nonpersistent_dva);
			vector<string> Attribute_registry_dva;
			Attribute_registry_dva.push_back("false");
			::Uml::InitAttribute(Attribute::meta_registry, Attribute::meta, "registry", "Boolean", false, false, 0, 1, false, "public", Attribute_registry_dva);
			vector<string> ConstraintDefinition_stereotype_dva;
			ConstraintDefinition_stereotype_dva.push_back("method");
			::Uml::InitAttribute(ConstraintDefinition::meta_stereotype, ConstraintDefinition::meta, "stereotype", "String", false, false, 1, 1, false, "public", ConstraintDefinition_stereotype_dva);
			::Uml::InitAttribute(ConstraintDefinition::meta_name, ConstraintDefinition::meta, "name", "String", false, false, 1, 1, false, "public");
			::Uml::InitAttribute(ConstraintDefinition::meta_parameterList, ConstraintDefinition::meta, "parameterList", "String", false, false, 0, 1, false, "public");
			::Uml::InitAttribute(ConstraintDefinition::meta_expression, ConstraintDefinition::meta, "expression", "String", false, false, 1, 1, false, "public");
			::Uml::InitAttribute(ConstraintDefinition::meta_returnType, ConstraintDefinition::meta, "returnType", "String", false, false, 1, 1, false, "public");
		
			{
				::Uml::Association ass = ::Uml::CreateAssociation();
				::Uml::InitAssociation(ass , meta, "");
				::Uml::InitAssociationRole(Class::meta_childRoles, ass, "childRoles", true, false, 0, -1, CompositionChildRole::meta);
				::Uml::InitAssociationRole(CompositionChildRole::meta_target, ass, "target", true, false, 1, 1, Class::meta);
			}
			{
				::Uml::Association ass = ::Uml::CreateAssociation();
				::Uml::InitAssociation(ass , meta, "");
				::Uml::InitAssociationRole(Class::meta_parentRoles, ass, "parentRoles", true, false, 0, -1, CompositionParentRole::meta);
				::Uml::InitAssociationRole(CompositionParentRole::meta_target, ass, "target", true, false, 1, 1, Class::meta);
			}
			{
				::Uml::Association ass = ::Uml::CreateAssociation();
				::Uml::InitAssociation(ass , meta, "");
				::Uml::InitAssociationRole(Class::meta_associationRoles, ass, "associationRoles", true, false, 0, -1, AssociationRole::meta);
				::Uml::InitAssociationRole(AssociationRole::meta_target, ass, "target", true, false, 1, 1, Class::meta);
			}
			{
				::Uml::Association ass = ::Uml::CreateAssociation();
				::Uml::InitAssociation(ass , meta, "");
				::Uml::InitAssociationRole(Class::meta_association, ass, "association", true, false, 0, 1, Association::meta);
				::Uml::InitAssociationRole(Association::meta_assocClass, ass, "assocClass", true, false, 0, 1, Class::meta);
			}
			{
				::Uml::Association ass = ::Uml::CreateAssociation();
				::Uml::InitAssociation(ass , meta, "");
				::Uml::InitAssociationRole(Class::meta_baseTypes, ass, "baseTypes", true, false, 0, -1, Class::meta);
				::Uml::InitAssociationRole(Class::meta_subTypes, ass, "subTypes", true, false, 0, -1, Class::meta);
			}
			{
				::Uml::Composition comp = ::Uml::CreateComposition();
				::Uml::InitComposition(comp , meta, "");
			
				::Uml::InitCompositionParentRole(Namespace::meta_parent, comp, "parent", true, Diagram::meta);
				::Uml::InitCompositionChildRole(Diagram::meta_namespaces, comp, "namespaces", true, 0, -1, Namespace::meta);
			}
			{
				::Uml::Composition comp = ::Uml::CreateComposition();
				::Uml::InitComposition(comp , meta, "");
			
				::Uml::InitCompositionParentRole(TaggedValue::meta_assocParent, comp, "assocParent", true, Association::meta);
				::Uml::InitCompositionChildRole(Association::meta_tagValues, comp, "tagValues", true, 0, -1, TaggedValue::meta);
			}
			{
				::Uml::Composition comp = ::Uml::CreateComposition();
				::Uml::InitComposition(comp , meta, "");
			
				::Uml::InitCompositionParentRole(AssociationRole::meta_parent, comp, "parent", true, Association::meta);
				::Uml::InitCompositionChildRole(Association::meta_roles, comp, "roles", true, 0, -1, AssociationRole::meta);
			}
			{
				::Uml::Composition comp = ::Uml::CreateComposition();
				::Uml::InitComposition(comp , meta, "");
			
				::Uml::InitCompositionParentRole(CompositionChildRole::meta_parent, comp, "parent", true, Composition::meta);
				::Uml::InitCompositionChildRole(Composition::meta_childRole, comp, "childRole", true, 1, 1, CompositionChildRole::meta);
			}
			{
				::Uml::Composition comp = ::Uml::CreateComposition();
				::Uml::InitComposition(comp , meta, "");
			
				::Uml::InitCompositionParentRole(CompositionParentRole::meta_parent, comp, "parent", true, Composition::meta);
				::Uml::InitCompositionChildRole(Composition::meta_parentRole, comp, "parentRole", true, 1, 1, CompositionParentRole::meta);
			}
			{
				::Uml::Composition comp = ::Uml::CreateComposition();
				::Uml::InitComposition(comp , meta, "");
			
				::Uml::InitCompositionParentRole(Composition::meta_parent, comp, "parent", true, Namespace::meta);
				::Uml::InitCompositionChildRole(Namespace::meta_compositions, comp, "compositions", true, 0, -1, Composition::meta);
			}
			{
				::Uml::Composition comp = ::Uml::CreateComposition();
				::Uml::InitComposition(comp , meta, "");
			
				::Uml::InitCompositionParentRole(Class::meta_parent, comp, "parent", true, Namespace::meta);
				::Uml::InitCompositionChildRole(Namespace::meta_classes, comp, "classes", true, 0, -1, Class::meta);
			}
			{
				::Uml::Composition comp = ::Uml::CreateComposition();
				::Uml::InitComposition(comp , meta, "");
			
				::Uml::InitCompositionParentRole(Association::meta_parent, comp, "parent", true, Namespace::meta);
				::Uml::InitCompositionChildRole(Namespace::meta_associations, comp, "associations", true, 0, -1, Association::meta);
			}
			{
				::Uml::Composition comp = ::Uml::CreateComposition();
				::Uml::InitComposition(comp , meta, "");
			
				::Uml::InitCompositionParentRole(Attribute::meta_parent, comp, "parent", true, Class::meta);
				::Uml::InitCompositionChildRole(Class::meta_attributes, comp, "attributes", true, 0, -1, Attribute::meta);
			}
			{
				::Uml::Composition comp = ::Uml::CreateComposition();
				::Uml::InitComposition(comp , meta, "");
			
				::Uml::InitCompositionParentRole(ConstraintDefinition::meta_parent, comp, "parent", true, Class::meta);
				::Uml::InitCompositionChildRole(Class::meta_definitions, comp, "definitions", true, 0, -1, ConstraintDefinition::meta);
			}
			{
				::Uml::Composition comp = ::Uml::CreateComposition();
				::Uml::InitComposition(comp , meta, "");
			
				::Uml::InitCompositionParentRole(Constraint::meta_parent, comp, "parent", true, Class::meta);
				::Uml::InitCompositionChildRole(Class::meta_constraints, comp, "constraints", true, 0, -1, Constraint::meta);
			}
			{
				::Uml::Composition comp = ::Uml::CreateComposition();
				::Uml::InitComposition(comp , meta, "");
			
				::Uml::InitCompositionParentRole(TaggedValue::meta_classParent, comp, "classParent", true, Class::meta);
				::Uml::InitCompositionChildRole(Class::meta_tagValues, comp, "tagValues", true, 0, -1, TaggedValue::meta);
			}
			::Uml::AddInheritance(GenericRole::meta, CompositionChildRole::meta);
			::Uml::AddInheritance(GenericRole::meta, CompositionParentRole::meta);
			::Uml::AddInheritance(GenericRole::meta, AssociationRole::meta);
			
		}
	UDM_DLL void Initialize()
	{
		static bool first = true;
		if(!first) return;
		first = false;
		::Uml::Initialize();

		ASSERT( umldiagram == Udm::null );
		umldiagram = ::Uml::CreateDiagram();
		
		Uml::meta = ::Uml::CreateNamespace();
		Uml::InitializeNS();
		::Uml::InitNamespace(Uml::meta, umldiagram,"Uml");
		UdmDom::str_xsd_storage::StoreXsd("Uml.xsd",Uml_xsd::getString());
		::Uml::InitDiagram(umldiagram, "Uml", "2.04");
	}
	UDM_DLL Udm::UdmDiagram diagram = { &umldiagram, Initialize };
	static struct _regClass
	{
		_regClass()
		{
			Udm::MetaDepository::StoreDiagram("Uml", diagram);
		};
		~_regClass()
		{
			Udm::MetaDepository::RemoveDiagram("Uml");
		};
	} __regUnUsed;

}
// END Uml.cpp
