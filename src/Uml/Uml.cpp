// cpp (meta datanetwork format) source file Uml.cpp
// generated from diagram Uml
// generated on Mon May 02 10:02:54 2011

#include "Uml.h"
#include <UmlExt.h>
#include <UdmStatic.h>

#include <UdmDom.h>
#include "Uml_xsd.h"
using namespace std;

namespace Uml {

	::Uml::Class CompositionChildRole::meta;
	::Uml::Attribute CompositionChildRole::meta_max;
	::Uml::Attribute CompositionChildRole::meta_min;
	::Uml::AssociationRole CompositionChildRole::meta_target;
	::Uml::CompositionParentRole CompositionChildRole::meta_parent;

	::Uml::Class GenericRole::meta;
	::Uml::Attribute GenericRole::meta_isNavigable;
	::Uml::Attribute GenericRole::meta_name;

	::Uml::Class CompositionParentRole::meta;
	::Uml::AssociationRole CompositionParentRole::meta_target;
	::Uml::CompositionParentRole CompositionParentRole::meta_parent;

	::Uml::Class AssociationRole::meta;
	::Uml::Attribute AssociationRole::meta_max;
	::Uml::Attribute AssociationRole::meta_min;
	::Uml::Attribute AssociationRole::meta_isPrimary;
	::Uml::AssociationRole AssociationRole::meta_rp_helper;
	::Uml::AssociationRole AssociationRole::meta_rp_helper_user;
	::Uml::AssociationRole AssociationRole::meta_target;
	::Uml::CompositionParentRole AssociationRole::meta_parent;

	::Uml::Class Class::meta;
	::Uml::Attribute Class::meta_isAbstract;
	::Uml::Attribute Class::meta_stereotype;
	::Uml::Attribute Class::meta_name;
	::Uml::Attribute Class::meta_from;
	::Uml::AssociationRole Class::meta_childRoles;
	::Uml::AssociationRole Class::meta_parentRoles;
	::Uml::AssociationRole Class::meta_associationRoles;
	::Uml::AssociationRole Class::meta_association;
	::Uml::AssociationRole Class::meta_baseTypes;
	::Uml::AssociationRole Class::meta_subTypes;
	::Uml::CompositionChildRole Class::meta_definitions;
	::Uml::CompositionChildRole Class::meta_attributes;
	::Uml::CompositionChildRole Class::meta_constraints;
	::Uml::CompositionChildRole Class::meta_tagValues;
	::Uml::CompositionParentRole Class::meta_parent;
	::Uml::CompositionParentRole Class::meta_parent_ns;

	::Uml::Class Diagram::meta;
	::Uml::Attribute Diagram::meta_version;
	::Uml::Attribute Diagram::meta_name;
	::Uml::CompositionChildRole Diagram::meta_classes;
	::Uml::CompositionChildRole Diagram::meta_associations;
	::Uml::CompositionChildRole Diagram::meta_compositions;
	::Uml::CompositionChildRole Diagram::meta_namespaces;

	::Uml::Class Association::meta;
	::Uml::Attribute Association::meta_nonpersistent;
	::Uml::Attribute Association::meta_name;
	::Uml::AssociationRole Association::meta_assocClass;
	::Uml::CompositionChildRole Association::meta_roles;
	::Uml::CompositionChildRole Association::meta_tagValues;
	::Uml::CompositionParentRole Association::meta_parent;
	::Uml::CompositionParentRole Association::meta_parent_ns;

	::Uml::Class Composition::meta;
	::Uml::Attribute Composition::meta_nonpersistent;
	::Uml::Attribute Composition::meta_name;
	::Uml::CompositionChildRole Composition::meta_parentRole;
	::Uml::CompositionChildRole Composition::meta_childRole;
	::Uml::CompositionParentRole Composition::meta_parent;
	::Uml::CompositionParentRole Composition::meta_parent_ns;

	::Uml::Class Namespace::meta;
	::Uml::Attribute Namespace::meta_name;
	::Uml::CompositionChildRole Namespace::meta_namespaces;
	::Uml::CompositionChildRole Namespace::meta_classes;
	::Uml::CompositionChildRole Namespace::meta_compositions;
	::Uml::CompositionChildRole Namespace::meta_associations;
	::Uml::CompositionParentRole Namespace::meta_parent;
	::Uml::CompositionParentRole Namespace::meta_parent_ns;

	::Uml::Class TaggedValue::meta;
	::Uml::Attribute TaggedValue::meta_value;
	::Uml::Attribute TaggedValue::meta_name;
	::Uml::CompositionParentRole TaggedValue::meta_assocParent;
	::Uml::CompositionParentRole TaggedValue::meta_classParent;

	::Uml::Class ConstraintDefinition::meta;
	::Uml::Attribute ConstraintDefinition::meta_stereotype;
	::Uml::Attribute ConstraintDefinition::meta_name;
	::Uml::Attribute ConstraintDefinition::meta_parameterList;
	::Uml::Attribute ConstraintDefinition::meta_expression;
	::Uml::Attribute ConstraintDefinition::meta_returnType;
	::Uml::CompositionParentRole ConstraintDefinition::meta_parent;

	::Uml::Class Attribute::meta;
	::Uml::Attribute Attribute::meta_name;
	::Uml::Attribute Attribute::meta_type;
	::Uml::Attribute Attribute::meta_defvalue;
	::Uml::Attribute Attribute::meta_min;
	::Uml::Attribute Attribute::meta_max;
	::Uml::Attribute Attribute::meta_visibility;
	::Uml::Attribute Attribute::meta_ordered;
	::Uml::Attribute Attribute::meta_nonpersistent;
	::Uml::Attribute Attribute::meta_registry;
	::Uml::CompositionParentRole Attribute::meta_parent;

	::Uml::Class Constraint::meta;
	::Uml::Attribute Constraint::meta_description;
	::Uml::Attribute Constraint::meta_name;
	::Uml::Attribute Constraint::meta_expression;
	::Uml::CompositionParentRole Constraint::meta_parent;

	::Uml::Diagram meta;

	void CreateMeta() {
		// classes, with attributes, constraints and constraint definitions
		Association::meta = ::Uml::CreateClass();
		Association::meta_nonpersistent = ::Uml::CreateAttribute();
		Association::meta_name = ::Uml::CreateAttribute();

		AssociationRole::meta = ::Uml::CreateClass();
		AssociationRole::meta_max = ::Uml::CreateAttribute();
		AssociationRole::meta_min = ::Uml::CreateAttribute();
		AssociationRole::meta_isPrimary = ::Uml::CreateAttribute();

		Attribute::meta = ::Uml::CreateClass();
		Attribute::meta_name = ::Uml::CreateAttribute();
		Attribute::meta_type = ::Uml::CreateAttribute();
		Attribute::meta_defvalue = ::Uml::CreateAttribute();
		Attribute::meta_min = ::Uml::CreateAttribute();
		Attribute::meta_max = ::Uml::CreateAttribute();
		Attribute::meta_visibility = ::Uml::CreateAttribute();
		Attribute::meta_ordered = ::Uml::CreateAttribute();
		Attribute::meta_nonpersistent = ::Uml::CreateAttribute();
		Attribute::meta_registry = ::Uml::CreateAttribute();

		Class::meta = ::Uml::CreateClass();
		Class::meta_isAbstract = ::Uml::CreateAttribute();
		Class::meta_stereotype = ::Uml::CreateAttribute();
		Class::meta_name = ::Uml::CreateAttribute();
		Class::meta_from = ::Uml::CreateAttribute();

		Composition::meta = ::Uml::CreateClass();
		Composition::meta_nonpersistent = ::Uml::CreateAttribute();
		Composition::meta_name = ::Uml::CreateAttribute();

		CompositionChildRole::meta = ::Uml::CreateClass();
		CompositionChildRole::meta_max = ::Uml::CreateAttribute();
		CompositionChildRole::meta_min = ::Uml::CreateAttribute();

		CompositionParentRole::meta = ::Uml::CreateClass();

		Constraint::meta = ::Uml::CreateClass();
		Constraint::meta_description = ::Uml::CreateAttribute();
		Constraint::meta_name = ::Uml::CreateAttribute();
		Constraint::meta_expression = ::Uml::CreateAttribute();

		ConstraintDefinition::meta = ::Uml::CreateClass();
		ConstraintDefinition::meta_stereotype = ::Uml::CreateAttribute();
		ConstraintDefinition::meta_name = ::Uml::CreateAttribute();
		ConstraintDefinition::meta_parameterList = ::Uml::CreateAttribute();
		ConstraintDefinition::meta_expression = ::Uml::CreateAttribute();
		ConstraintDefinition::meta_returnType = ::Uml::CreateAttribute();

		Diagram::meta = ::Uml::CreateClass();
		Diagram::meta_version = ::Uml::CreateAttribute();
		Diagram::meta_name = ::Uml::CreateAttribute();

		GenericRole::meta = ::Uml::CreateClass();
		GenericRole::meta_isNavigable = ::Uml::CreateAttribute();
		GenericRole::meta_name = ::Uml::CreateAttribute();

		Namespace::meta = ::Uml::CreateClass();
		Namespace::meta_name = ::Uml::CreateAttribute();

		TaggedValue::meta = ::Uml::CreateClass();
		TaggedValue::meta_value = ::Uml::CreateAttribute();
		TaggedValue::meta_name = ::Uml::CreateAttribute();

		CompositionChildRole::meta_target = ::Uml::CreateAssociationRole();
		Class::meta_childRoles = ::Uml::CreateAssociationRole();
		CompositionParentRole::meta_target = ::Uml::CreateAssociationRole();
		Class::meta_parentRoles = ::Uml::CreateAssociationRole();
		AssociationRole::meta_rp_helper = ::Uml::CreateAssociationRole();
		AssociationRole::meta_rp_helper_user = ::Uml::CreateAssociationRole();
		AssociationRole::meta_target = ::Uml::CreateAssociationRole();
		Class::meta_associationRoles = ::Uml::CreateAssociationRole();
		Association::meta_assocClass = ::Uml::CreateAssociationRole();
		Class::meta_association = ::Uml::CreateAssociationRole();
		Class::meta_baseTypes = ::Uml::CreateAssociationRole();
		Class::meta_subTypes = ::Uml::CreateAssociationRole();

		ConstraintDefinition::meta_parent = ::Uml::CreateCompositionParentRole();
		Class::meta_definitions = ::Uml::CreateCompositionChildRole();
		Attribute::meta_parent = ::Uml::CreateCompositionParentRole();
		Class::meta_attributes = ::Uml::CreateCompositionChildRole();
		Constraint::meta_parent = ::Uml::CreateCompositionParentRole();
		Class::meta_constraints = ::Uml::CreateCompositionChildRole();
		TaggedValue::meta_classParent = ::Uml::CreateCompositionParentRole();
		Class::meta_tagValues = ::Uml::CreateCompositionChildRole();
		Class::meta_parent = ::Uml::CreateCompositionParentRole();
		Diagram::meta_classes = ::Uml::CreateCompositionChildRole();
		Association::meta_parent = ::Uml::CreateCompositionParentRole();
		Diagram::meta_associations = ::Uml::CreateCompositionChildRole();
		Composition::meta_parent = ::Uml::CreateCompositionParentRole();
		Diagram::meta_compositions = ::Uml::CreateCompositionChildRole();
		Namespace::meta_parent = ::Uml::CreateCompositionParentRole();
		Diagram::meta_namespaces = ::Uml::CreateCompositionChildRole();
		AssociationRole::meta_parent = ::Uml::CreateCompositionParentRole();
		Association::meta_roles = ::Uml::CreateCompositionChildRole();
		TaggedValue::meta_assocParent = ::Uml::CreateCompositionParentRole();
		Association::meta_tagValues = ::Uml::CreateCompositionChildRole();
		CompositionParentRole::meta_parent = ::Uml::CreateCompositionParentRole();
		Composition::meta_parentRole = ::Uml::CreateCompositionChildRole();
		CompositionChildRole::meta_parent = ::Uml::CreateCompositionParentRole();
		Composition::meta_childRole = ::Uml::CreateCompositionChildRole();
		Namespace::meta_parent_ns = ::Uml::CreateCompositionParentRole();
		Namespace::meta_namespaces = ::Uml::CreateCompositionChildRole();
		Class::meta_parent_ns = ::Uml::CreateCompositionParentRole();
		Namespace::meta_classes = ::Uml::CreateCompositionChildRole();
		Composition::meta_parent_ns = ::Uml::CreateCompositionParentRole();
		Namespace::meta_compositions = ::Uml::CreateCompositionChildRole();
		Association::meta_parent_ns = ::Uml::CreateCompositionParentRole();
		Namespace::meta_associations = ::Uml::CreateCompositionChildRole();

	}

	void InitMeta() {
		// classes, with attributes, constraints and constraint definitions
		::Uml::InitClass(Association::meta, meta, "Association", false, NULL, NULL);
		vector<string> Association_nonpersistent_dva;
		Association_nonpersistent_dva.push_back("false");
		::Uml::InitAttribute(Association::meta_nonpersistent, Association::meta, "nonpersistent", "Boolean", false, false, 0, 1, false, "public", Association_nonpersistent_dva);
		::Uml::InitAttribute(Association::meta_name, Association::meta, "name", "String", false, false, 0, 1, false, "public", vector<string>());

		::Uml::InitClass(AssociationRole::meta, meta, "AssociationRole", false, NULL, NULL);
		::Uml::InitAttribute(AssociationRole::meta_max, AssociationRole::meta, "max", "Integer", false, false, 1, 1, false, "public", vector<string>());
		::Uml::InitAttribute(AssociationRole::meta_min, AssociationRole::meta, "min", "Integer", false, false, 1, 1, false, "public", vector<string>());
		vector<string> AssociationRole_isPrimary_dva;
		AssociationRole_isPrimary_dva.push_back("false");
		::Uml::InitAttribute(AssociationRole::meta_isPrimary, AssociationRole::meta, "isPrimary", "Boolean", false, false, 0, 1, false, "public", AssociationRole_isPrimary_dva);

		::Uml::InitClass(Attribute::meta, meta, "Attribute", false, NULL, NULL);
		::Uml::InitAttribute(Attribute::meta_name, Attribute::meta, "name", "String", false, false, 1, 1, false, "public", vector<string>());
		::Uml::InitAttribute(Attribute::meta_type, Attribute::meta, "type", "String", false, false, 1, 1, false, "public", vector<string>());
		::Uml::InitAttribute(Attribute::meta_defvalue, Attribute::meta, "defvalue", "String", false, false, 0, -1, false, "public", vector<string>());
		::Uml::InitAttribute(Attribute::meta_min, Attribute::meta, "min", "Integer", false, false, 1, 1, false, "public", vector<string>());
		::Uml::InitAttribute(Attribute::meta_max, Attribute::meta, "max", "Integer", false, false, 1, 1, false, "public", vector<string>());
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

		::Uml::InitClass(Class::meta, meta, "Class", false, NULL, NULL);
		::Uml::InitAttribute(Class::meta_isAbstract, Class::meta, "isAbstract", "Boolean", false, false, 1, 1, false, "public", vector<string>());
		::Uml::InitAttribute(Class::meta_stereotype, Class::meta, "stereotype", "String", false, false, 0, 1, false, "public", vector<string>());
		::Uml::InitAttribute(Class::meta_name, Class::meta, "name", "String", false, false, 1, 1, false, "public", vector<string>());
		::Uml::InitAttribute(Class::meta_from, Class::meta, "from", "String", false, false, 0, 1, false, "public", vector<string>());

		::Uml::InitClass(Composition::meta, meta, "Composition", false, NULL, NULL);
		vector<string> Composition_nonpersistent_dva;
		Composition_nonpersistent_dva.push_back("false");
		::Uml::InitAttribute(Composition::meta_nonpersistent, Composition::meta, "nonpersistent", "Boolean", false, false, 0, 1, false, "public", Composition_nonpersistent_dva);
		::Uml::InitAttribute(Composition::meta_name, Composition::meta, "name", "String", false, false, 0, 1, false, "public", vector<string>());

		::Uml::InitClass(CompositionChildRole::meta, meta, "CompositionChildRole", false, NULL, NULL);
		::Uml::InitAttribute(CompositionChildRole::meta_max, CompositionChildRole::meta, "max", "Integer", false, false, 1, 1, false, "public", vector<string>());
		::Uml::InitAttribute(CompositionChildRole::meta_min, CompositionChildRole::meta, "min", "Integer", false, false, 1, 1, false, "public", vector<string>());

		::Uml::InitClass(CompositionParentRole::meta, meta, "CompositionParentRole", false, NULL, NULL);

		::Uml::InitClass(Constraint::meta, meta, "Constraint", false, NULL, NULL);
		::Uml::InitAttribute(Constraint::meta_description, Constraint::meta, "description", "String", false, false, 0, 1, false, "public", vector<string>());
		::Uml::InitAttribute(Constraint::meta_name, Constraint::meta, "name", "String", false, false, 1, 1, false, "public", vector<string>());
		::Uml::InitAttribute(Constraint::meta_expression, Constraint::meta, "expression", "String", false, false, 1, 1, false, "public", vector<string>());

		::Uml::InitClass(ConstraintDefinition::meta, meta, "ConstraintDefinition", false, NULL, NULL);
		vector<string> ConstraintDefinition_stereotype_dva;
		ConstraintDefinition_stereotype_dva.push_back("method");
		::Uml::InitAttribute(ConstraintDefinition::meta_stereotype, ConstraintDefinition::meta, "stereotype", "String", false, false, 1, 1, false, "public", ConstraintDefinition_stereotype_dva);
		::Uml::InitAttribute(ConstraintDefinition::meta_name, ConstraintDefinition::meta, "name", "String", false, false, 1, 1, false, "public", vector<string>());
		::Uml::InitAttribute(ConstraintDefinition::meta_parameterList, ConstraintDefinition::meta, "parameterList", "String", false, false, 0, 1, false, "public", vector<string>());
		::Uml::InitAttribute(ConstraintDefinition::meta_expression, ConstraintDefinition::meta, "expression", "String", false, false, 1, 1, false, "public", vector<string>());
		::Uml::InitAttribute(ConstraintDefinition::meta_returnType, ConstraintDefinition::meta, "returnType", "String", false, false, 1, 1, false, "public", vector<string>());

		::Uml::InitClass(Diagram::meta, meta, "Diagram", false, NULL, NULL);
		::Uml::InitAttribute(Diagram::meta_version, Diagram::meta, "version", "String", false, false, 0, 1, false, "public", vector<string>());
		::Uml::InitAttribute(Diagram::meta_name, Diagram::meta, "name", "String", false, false, 1, 1, false, "public", vector<string>());

		::Uml::InitClass(GenericRole::meta, meta, "GenericRole", true, NULL, NULL);
		vector<string> GenericRole_isNavigable_dva;
		GenericRole_isNavigable_dva.push_back("true");
		::Uml::InitAttribute(GenericRole::meta_isNavigable, GenericRole::meta, "isNavigable", "Boolean", false, false, 0, 1, false, "public", GenericRole_isNavigable_dva);
		::Uml::InitAttribute(GenericRole::meta_name, GenericRole::meta, "name", "String", false, false, 0, 1, false, "public", vector<string>());

		::Uml::InitClass(Namespace::meta, meta, "Namespace", false, NULL, NULL);
		::Uml::InitAttribute(Namespace::meta_name, Namespace::meta, "name", "String", false, false, 1, 1, false, "public", vector<string>());

		::Uml::InitClass(TaggedValue::meta, meta, "TaggedValue", false, NULL, NULL);
		::Uml::InitAttribute(TaggedValue::meta_value, TaggedValue::meta, "value", "String", false, false, 0, 1, false, "public", vector<string>());
		::Uml::InitAttribute(TaggedValue::meta_name, TaggedValue::meta, "name", "String", false, false, 1, 1, false, "public", vector<string>());

	}

	void InitMetaLinks() {
		::Uml::AddInheritance(GenericRole::meta, CompositionChildRole::meta);
		::Uml::AddInheritance(GenericRole::meta, CompositionParentRole::meta);
		::Uml::AddInheritance(GenericRole::meta, AssociationRole::meta);

		// associations
		{
			::Uml::Association ass = ::Uml::CreateAssociation();
			::Uml::InitAssociation(ass, meta, "Association");
			::Uml::InitAssociationRole(CompositionChildRole::meta_target, ass, "target", true, false, 1, 1, Class::meta);
			::Uml::InitAssociationRole(Class::meta_childRoles, ass, "childRoles", true, false, 0, -1, CompositionChildRole::meta);

		}
		{
			::Uml::Association ass = ::Uml::CreateAssociation();
			::Uml::InitAssociation(ass, meta, "Association");
			::Uml::InitAssociationRole(CompositionParentRole::meta_target, ass, "target", true, false, 1, 1, Class::meta);
			::Uml::InitAssociationRole(Class::meta_parentRoles, ass, "parentRoles", true, false, 0, -1, CompositionParentRole::meta);

		}
		{
			::Uml::Association ass = ::Uml::CreateAssociation();
			::Uml::InitAssociation(ass, meta, "Association");
			::Uml::InitAssociationRole(AssociationRole::meta_rp_helper, ass, "rp_helper", true, false, 0, 1, AssociationRole::meta);
			::Uml::InitAssociationRole(AssociationRole::meta_rp_helper_user, ass, "rp_helper_user", true, false, 0, 1, AssociationRole::meta);

		}
		{
			::Uml::Association ass = ::Uml::CreateAssociation();
			::Uml::InitAssociation(ass, meta, "Association");
			::Uml::InitAssociationRole(AssociationRole::meta_target, ass, "target", true, false, 1, 1, Class::meta);
			::Uml::InitAssociationRole(Class::meta_associationRoles, ass, "associationRoles", true, false, 0, -1, AssociationRole::meta);

		}
		{
			::Uml::Association ass = ::Uml::CreateAssociation();
			::Uml::InitAssociation(ass, meta, "Association");
			::Uml::InitAssociationRole(Association::meta_assocClass, ass, "assocClass", true, false, 0, 1, Class::meta);
			::Uml::InitAssociationRole(Class::meta_association, ass, "association", true, false, 0, 1, Association::meta);

		}
		{
			::Uml::Association ass = ::Uml::CreateAssociation();
			::Uml::InitAssociation(ass, meta, "Association");
			::Uml::InitAssociationRole(Class::meta_baseTypes, ass, "baseTypes", true, false, 0, -1, Class::meta);
			::Uml::InitAssociationRole(Class::meta_subTypes, ass, "subTypes", true, false, 0, -1, Class::meta);

		}

		// compositions
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(ConstraintDefinition::meta_parent, comp, "parent", true, Class::meta);
			::Uml::InitCompositionChildRole(Class::meta_definitions, comp, "definitions", true, 0, -1, ConstraintDefinition::meta);

		}
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(Attribute::meta_parent, comp, "parent", true, Class::meta);
			::Uml::InitCompositionChildRole(Class::meta_attributes, comp, "attributes", true, 0, -1, Attribute::meta);

		}
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(Constraint::meta_parent, comp, "parent", true, Class::meta);
			::Uml::InitCompositionChildRole(Class::meta_constraints, comp, "constraints", true, 0, -1, Constraint::meta);

		}
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(TaggedValue::meta_classParent, comp, "classParent", true, Class::meta);
			::Uml::InitCompositionChildRole(Class::meta_tagValues, comp, "tagValues", true, 0, -1, TaggedValue::meta);

		}
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(Class::meta_parent, comp, "parent", true, Diagram::meta);
			::Uml::InitCompositionChildRole(Diagram::meta_classes, comp, "classes", true, 0, -1, Class::meta);

		}
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(Association::meta_parent, comp, "parent", true, Diagram::meta);
			::Uml::InitCompositionChildRole(Diagram::meta_associations, comp, "associations", true, 0, -1, Association::meta);

		}
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(Composition::meta_parent, comp, "parent", true, Diagram::meta);
			::Uml::InitCompositionChildRole(Diagram::meta_compositions, comp, "compositions", true, 0, -1, Composition::meta);

		}
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(Namespace::meta_parent, comp, "parent", true, Diagram::meta);
			::Uml::InitCompositionChildRole(Diagram::meta_namespaces, comp, "namespaces", true, 0, -1, Namespace::meta);

		}
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(AssociationRole::meta_parent, comp, "parent", true, Association::meta);
			::Uml::InitCompositionChildRole(Association::meta_roles, comp, "roles", true, 0, -1, AssociationRole::meta);

		}
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(TaggedValue::meta_assocParent, comp, "assocParent", true, Association::meta);
			::Uml::InitCompositionChildRole(Association::meta_tagValues, comp, "tagValues", true, 0, -1, TaggedValue::meta);

		}
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(CompositionParentRole::meta_parent, comp, "parent", true, Composition::meta);
			::Uml::InitCompositionChildRole(Composition::meta_parentRole, comp, "parentRole", true, 1, 1, CompositionParentRole::meta);

		}
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(CompositionChildRole::meta_parent, comp, "parent", true, Composition::meta);
			::Uml::InitCompositionChildRole(Composition::meta_childRole, comp, "childRole", true, 1, 1, CompositionChildRole::meta);

		}
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(Namespace::meta_parent_ns, comp, "parent_ns", true, Namespace::meta);
			::Uml::InitCompositionChildRole(Namespace::meta_namespaces, comp, "namespaces", true, 0, -1, Namespace::meta);

		}
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(Class::meta_parent_ns, comp, "parent_ns", true, Namespace::meta);
			::Uml::InitCompositionChildRole(Namespace::meta_classes, comp, "classes", true, 0, -1, Class::meta);

		}
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(Composition::meta_parent_ns, comp, "parent_ns", true, Namespace::meta);
			::Uml::InitCompositionChildRole(Namespace::meta_compositions, comp, "compositions", true, 0, -1, Composition::meta);

		}
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(Association::meta_parent_ns, comp, "parent_ns", true, Namespace::meta);
			::Uml::InitCompositionChildRole(Namespace::meta_associations, comp, "associations", true, 0, -1, Association::meta);

		}

	}

	void _SetXsdStorage()
	{
		UdmDom::str_xsd_storage::StoreXsd("Uml.xsd", Uml_xsd::getString());
	}

	UDM_DLL void Initialize()
	{
		static bool first = true;
		if (!first) return;
		first = false;
		::Uml::Initialize();

	
		UDM_ASSERT( meta == Udm::null );

		meta = ::Uml::CreateDiagram();

		UdmStatic::StaticDataNetwork* dn = new UdmStatic::StaticDataNetwork(diagram);
		dn->rootobject = meta;
		static_cast<UdmStatic::StaticObject*>(dn->rootobject.__impl())->mydn = dn;
		dn->systemname = "Uml";
		dn->sem = Udm::CHANGES_LOST_DEFAULT;

		CreateMeta();
		InitMeta();
		InitMetaLinks();

		::Uml::InitDiagram(meta, "Uml", "2.04");


		_SetXsdStorage();

	}


	UDM_DLL Udm::UdmDiagram diagram = { &meta, Initialize };
	static struct _regClass
	{
		_regClass()
		{
			Udm::MetaDepository::StoreDiagram("Uml", diagram);
		}
		~_regClass()
		{
			Udm::MetaDepository::RemoveDiagram("Uml");
		}
	} __regUnUsed;

}

