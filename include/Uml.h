#ifndef MOBIES_UML_H
#define MOBIES_UML_H

// header file Uml.h generated from diagram Uml
// generated with Udm version 3.27 on Mon Jan 24 23:17:31 2011

#include <UdmBase.h>

#if !defined(UDM_VERSION_MAJOR) || !defined(UDM_VERSION_MINOR)
#    error "Udm headers too old, they do not define UDM_VERSION"
#elif UDM_VERSION_MAJOR < 3
#    error "Udm headers too old, minimum version required 3.27"
#elif UDM_VERSION_MAJOR == 3 && UDM_VERSION_MINOR < 27
#    error "Udm headers too old, minimum version required 3.27"
#endif

#include <Uml.h>


#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#include "Uml_export.h"

namespace Uml {

	extern ::Uml::Diagram meta;
	class UDM_DLL CompositionChildRole;
	class UDM_DLL GenericRole;
	class UDM_DLL CompositionParentRole;
	class UDM_DLL AssociationRole;
	class UDM_DLL Class;
	class UDM_DLL Diagram;
	class UDM_DLL Association;
	class UDM_DLL Composition;
	class UDM_DLL Namespace;
	class UDM_DLL TaggedValue;
	class UDM_DLL ConstraintDefinition;
	class UDM_DLL Attribute;
	class UDM_DLL Constraint;

	UDM_DLL void Initialize();

	extern UDM_DLL Udm::UdmDiagram diagram;

	class UDM_DLL GenericRole : public Udm::Object {
	public:
		GenericRole() {}
		GenericRole(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) {}
		GenericRole(const GenericRole &master) : UDM_OBJECT(master) {}
		#ifdef UDM_RVALUE
		GenericRole(GenericRole &&master) : UDM_OBJECT(master) {}

		static GenericRole Cast(Udm::Object &&a) { return __Cast(std::move(a), meta); }
		GenericRole& operator=(GenericRole &&a) { Udm::Object::operator =(std::move(a)); return *this; }
		#endif
		static GenericRole Cast(const Udm::Object &a) { return __Cast(a, meta); }
		static GenericRole Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }
		GenericRole CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::InstantiatedAttr<GenericRole> Instances() { return Udm::InstantiatedAttr<GenericRole>(impl); }
		template <class Pred> Udm::InstantiatedAttr<GenericRole, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<GenericRole, Pred>(impl); }
		GenericRole CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::DerivedAttr<GenericRole> Derived() { return Udm::DerivedAttr<GenericRole>(impl); }
		template <class Pred> Udm::DerivedAttr<GenericRole, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<GenericRole, Pred>(impl); }
		Udm::ArchetypeAttr<GenericRole> Archetype() const { return Udm::ArchetypeAttr<GenericRole>(impl); }
		Udm::BooleanAttr isNavigable() const { return Udm::BooleanAttr(impl, meta_isNavigable); }
		Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }
		Udm::ParentAttr<Udm::Object> parent() const { return Udm::ParentAttr<Udm::Object>(impl, Udm::NULLPARENTROLE); }

		static ::Uml::Class meta;
		static ::Uml::Attribute meta_isNavigable;
		static ::Uml::Attribute meta_name;

	};

	class UDM_DLL CompositionChildRole :  public GenericRole {
	public:
		CompositionChildRole() {}
		CompositionChildRole(Udm::ObjectImpl *impl) : GenericRole(impl) {}
		CompositionChildRole(const CompositionChildRole &master) : GenericRole(master) {}
		#ifdef UDM_RVALUE
		CompositionChildRole(CompositionChildRole &&master) : GenericRole(master) {}

		static CompositionChildRole Cast(Udm::Object &&a) { return __Cast(std::move(a), meta); }
		CompositionChildRole& operator=(CompositionChildRole &&a) { Udm::Object::operator =(std::move(a)); return *this; }
		#endif
		static CompositionChildRole Cast(const Udm::Object &a) { return __Cast(a, meta); }
		static CompositionChildRole Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }
		CompositionChildRole CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::InstantiatedAttr<CompositionChildRole> Instances() { return Udm::InstantiatedAttr<CompositionChildRole>(impl); }
		template <class Pred> Udm::InstantiatedAttr<CompositionChildRole, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<CompositionChildRole, Pred>(impl); }
		CompositionChildRole CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::DerivedAttr<CompositionChildRole> Derived() { return Udm::DerivedAttr<CompositionChildRole>(impl); }
		template <class Pred> Udm::DerivedAttr<CompositionChildRole, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<CompositionChildRole, Pred>(impl); }
		Udm::ArchetypeAttr<CompositionChildRole> Archetype() const { return Udm::ArchetypeAttr<CompositionChildRole>(impl); }
		Udm::IntegerAttr max() const { return Udm::IntegerAttr(impl, meta_max); }
		Udm::IntegerAttr min() const { return Udm::IntegerAttr(impl, meta_min); }
		Udm::PointerAttr< Class> target() const { return Udm::PointerAttr< Class>(impl, meta_target); }
		Udm::ParentAttr< ::Uml::Composition> parent() const { return Udm::ParentAttr< ::Uml::Composition>(impl, meta_parent); }

		static ::Uml::Class meta;
		static ::Uml::Attribute meta_max;
		static ::Uml::Attribute meta_min;
		static ::Uml::AssociationRole meta_target;
		static ::Uml::CompositionParentRole meta_parent;

	};

	class UDM_DLL CompositionParentRole :  public GenericRole {
	public:
		CompositionParentRole() {}
		CompositionParentRole(Udm::ObjectImpl *impl) : GenericRole(impl) {}
		CompositionParentRole(const CompositionParentRole &master) : GenericRole(master) {}
		#ifdef UDM_RVALUE
		CompositionParentRole(CompositionParentRole &&master) : GenericRole(master) {}

		static CompositionParentRole Cast(Udm::Object &&a) { return __Cast(std::move(a), meta); }
		CompositionParentRole& operator=(CompositionParentRole &&a) { Udm::Object::operator =(std::move(a)); return *this; }
		#endif
		static CompositionParentRole Cast(const Udm::Object &a) { return __Cast(a, meta); }
		static CompositionParentRole Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }
		CompositionParentRole CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::InstantiatedAttr<CompositionParentRole> Instances() { return Udm::InstantiatedAttr<CompositionParentRole>(impl); }
		template <class Pred> Udm::InstantiatedAttr<CompositionParentRole, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<CompositionParentRole, Pred>(impl); }
		CompositionParentRole CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::DerivedAttr<CompositionParentRole> Derived() { return Udm::DerivedAttr<CompositionParentRole>(impl); }
		template <class Pred> Udm::DerivedAttr<CompositionParentRole, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<CompositionParentRole, Pred>(impl); }
		Udm::ArchetypeAttr<CompositionParentRole> Archetype() const { return Udm::ArchetypeAttr<CompositionParentRole>(impl); }
		Udm::PointerAttr< Class> target() const { return Udm::PointerAttr< Class>(impl, meta_target); }
		Udm::ParentAttr< ::Uml::Composition> parent() const { return Udm::ParentAttr< ::Uml::Composition>(impl, meta_parent); }

		static ::Uml::Class meta;
		static ::Uml::AssociationRole meta_target;
		static ::Uml::CompositionParentRole meta_parent;

	};

	class UDM_DLL AssociationRole :  public GenericRole {
	public:
		AssociationRole() {}
		AssociationRole(Udm::ObjectImpl *impl) : GenericRole(impl) {}
		AssociationRole(const AssociationRole &master) : GenericRole(master) {}
		#ifdef UDM_RVALUE
		AssociationRole(AssociationRole &&master) : GenericRole(master) {}

		static AssociationRole Cast(Udm::Object &&a) { return __Cast(std::move(a), meta); }
		AssociationRole& operator=(AssociationRole &&a) { Udm::Object::operator =(std::move(a)); return *this; }
		#endif
		static AssociationRole Cast(const Udm::Object &a) { return __Cast(a, meta); }
		static AssociationRole Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }
		AssociationRole CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::InstantiatedAttr<AssociationRole> Instances() { return Udm::InstantiatedAttr<AssociationRole>(impl); }
		template <class Pred> Udm::InstantiatedAttr<AssociationRole, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<AssociationRole, Pred>(impl); }
		AssociationRole CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::DerivedAttr<AssociationRole> Derived() { return Udm::DerivedAttr<AssociationRole>(impl); }
		template <class Pred> Udm::DerivedAttr<AssociationRole, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<AssociationRole, Pred>(impl); }
		Udm::ArchetypeAttr<AssociationRole> Archetype() const { return Udm::ArchetypeAttr<AssociationRole>(impl); }
		Udm::IntegerAttr max() const { return Udm::IntegerAttr(impl, meta_max); }
		Udm::IntegerAttr min() const { return Udm::IntegerAttr(impl, meta_min); }
		Udm::BooleanAttr isPrimary() const { return Udm::BooleanAttr(impl, meta_isPrimary); }
		Udm::PointerAttr< AssociationRole> rp_helper() const { return Udm::PointerAttr< AssociationRole>(impl, meta_rp_helper); }
		Udm::PointerAttr< AssociationRole> rp_helper_user() const { return Udm::PointerAttr< AssociationRole>(impl, meta_rp_helper_user); }
		Udm::PointerAttr< Class> target() const { return Udm::PointerAttr< Class>(impl, meta_target); }
		Udm::ParentAttr< ::Uml::Association> parent() const { return Udm::ParentAttr< ::Uml::Association>(impl, meta_parent); }

		static ::Uml::Class meta;
		static ::Uml::Attribute meta_max;
		static ::Uml::Attribute meta_min;
		static ::Uml::Attribute meta_isPrimary;
		static ::Uml::AssociationRole meta_rp_helper;
		static ::Uml::AssociationRole meta_rp_helper_user;
		static ::Uml::AssociationRole meta_target;
		static ::Uml::CompositionParentRole meta_parent;

	};

	class UDM_DLL Class : public Udm::Object {
	public:
		Class() {}
		Class(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) {}
		Class(const Class &master) : UDM_OBJECT(master) {}
		#ifdef UDM_RVALUE
		Class(Class &&master) : UDM_OBJECT(master) {}

		static Class Cast(Udm::Object &&a) { return __Cast(std::move(a), meta); }
		Class& operator=(Class &&a) { Udm::Object::operator =(std::move(a)); return *this; }
		#endif
		static Class Cast(const Udm::Object &a) { return __Cast(a, meta); }
		static Class Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }
		Class CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::InstantiatedAttr<Class> Instances() { return Udm::InstantiatedAttr<Class>(impl); }
		template <class Pred> Udm::InstantiatedAttr<Class, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<Class, Pred>(impl); }
		Class CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::DerivedAttr<Class> Derived() { return Udm::DerivedAttr<Class>(impl); }
		template <class Pred> Udm::DerivedAttr<Class, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<Class, Pred>(impl); }
		Udm::ArchetypeAttr<Class> Archetype() const { return Udm::ArchetypeAttr<Class>(impl); }
		Udm::BooleanAttr isAbstract() const { return Udm::BooleanAttr(impl, meta_isAbstract); }
		Udm::StringAttr stereotype() const { return Udm::StringAttr(impl, meta_stereotype); }
		Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }
		Udm::StringAttr from() const { return Udm::StringAttr(impl, meta_from); }
		Udm::AssocAttr< CompositionChildRole> childRoles() const { return Udm::AssocAttr< CompositionChildRole>(impl, meta_childRoles); }
		template <class Pred> Udm::AssocAttr< CompositionChildRole, Pred> childRoles_sorted(const Pred &) const { return Udm::AssocAttr< CompositionChildRole, Pred>(impl, meta_childRoles); }
		Udm::AssocAttr< CompositionParentRole> parentRoles() const { return Udm::AssocAttr< CompositionParentRole>(impl, meta_parentRoles); }
		template <class Pred> Udm::AssocAttr< CompositionParentRole, Pred> parentRoles_sorted(const Pred &) const { return Udm::AssocAttr< CompositionParentRole, Pred>(impl, meta_parentRoles); }
		Udm::AssocAttr< AssociationRole> associationRoles() const { return Udm::AssocAttr< AssociationRole>(impl, meta_associationRoles); }
		template <class Pred> Udm::AssocAttr< AssociationRole, Pred> associationRoles_sorted(const Pred &) const { return Udm::AssocAttr< AssociationRole, Pred>(impl, meta_associationRoles); }
		Udm::PointerAttr< Association> association() const { return Udm::PointerAttr< Association>(impl, meta_association); }
		Udm::AssocAttr< Class> baseTypes() const { return Udm::AssocAttr< Class>(impl, meta_baseTypes); }
		template <class Pred> Udm::AssocAttr< Class, Pred> baseTypes_sorted(const Pred &) const { return Udm::AssocAttr< Class, Pred>(impl, meta_baseTypes); }
		Udm::AssocAttr< Class> subTypes() const { return Udm::AssocAttr< Class>(impl, meta_subTypes); }
		template <class Pred> Udm::AssocAttr< Class, Pred> subTypes_sorted(const Pred &) const { return Udm::AssocAttr< Class, Pred>(impl, meta_subTypes); }
		Udm::ChildrenAttr< ::Uml::ConstraintDefinition> definitions() const { return Udm::ChildrenAttr< ::Uml::ConstraintDefinition>(impl, meta_definitions); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::ConstraintDefinition, Pred> definitions_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::ConstraintDefinition, Pred>(impl, meta_definitions); }
		Udm::ChildrenAttr< ::Uml::Attribute> attributes() const { return Udm::ChildrenAttr< ::Uml::Attribute>(impl, meta_attributes); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Attribute, Pred> attributes_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Attribute, Pred>(impl, meta_attributes); }
		Udm::ChildrenAttr< ::Uml::Constraint> constraints() const { return Udm::ChildrenAttr< ::Uml::Constraint>(impl, meta_constraints); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Constraint, Pred> constraints_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Constraint, Pred>(impl, meta_constraints); }
		Udm::ChildrenAttr< ::Uml::TaggedValue> tagValues() const { return Udm::ChildrenAttr< ::Uml::TaggedValue>(impl, meta_tagValues); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::TaggedValue, Pred> tagValues_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::TaggedValue, Pred>(impl, meta_tagValues); }
		Udm::ChildrenAttr< ::Uml::TaggedValue> TaggedValue_kind_children() const { return Udm::ChildrenAttr< ::Uml::TaggedValue>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::TaggedValue, Pred> TaggedValue_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::TaggedValue, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ChildrenAttr< ::Uml::ConstraintDefinition> ConstraintDefinition_kind_children() const { return Udm::ChildrenAttr< ::Uml::ConstraintDefinition>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::ConstraintDefinition, Pred> ConstraintDefinition_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::ConstraintDefinition, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ChildrenAttr< ::Uml::Attribute> Attribute_kind_children() const { return Udm::ChildrenAttr< ::Uml::Attribute>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Attribute, Pred> Attribute_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Attribute, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ChildrenAttr< ::Uml::Constraint> Constraint_kind_children() const { return Udm::ChildrenAttr< ::Uml::Constraint>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Constraint, Pred> Constraint_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Constraint, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ParentAttr< ::Uml::Diagram> parent() const { return Udm::ParentAttr< ::Uml::Diagram>(impl, meta_parent); }
		Udm::ParentAttr< ::Uml::Namespace> parent_ns() const { return Udm::ParentAttr< ::Uml::Namespace>(impl, meta_parent_ns); }

		static ::Uml::Class meta;
		static ::Uml::Attribute meta_isAbstract;
		static ::Uml::Attribute meta_stereotype;
		static ::Uml::Attribute meta_name;
		static ::Uml::Attribute meta_from;
		static ::Uml::AssociationRole meta_childRoles;
		static ::Uml::AssociationRole meta_parentRoles;
		static ::Uml::AssociationRole meta_associationRoles;
		static ::Uml::AssociationRole meta_association;
		static ::Uml::AssociationRole meta_baseTypes;
		static ::Uml::AssociationRole meta_subTypes;
		static ::Uml::CompositionChildRole meta_definitions;
		static ::Uml::CompositionChildRole meta_attributes;
		static ::Uml::CompositionChildRole meta_constraints;
		static ::Uml::CompositionChildRole meta_tagValues;
		static ::Uml::CompositionParentRole meta_parent;
		static ::Uml::CompositionParentRole meta_parent_ns;

	};

	class UDM_DLL Diagram : public Udm::Object {
	public:
		Diagram() {}
		Diagram(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) {}
		Diagram(const Diagram &master) : UDM_OBJECT(master) {}
		#ifdef UDM_RVALUE
		Diagram(Diagram &&master) : UDM_OBJECT(master) {}

		static Diagram Cast(Udm::Object &&a) { return __Cast(std::move(a), meta); }
		Diagram& operator=(Diagram &&a) { Udm::Object::operator =(std::move(a)); return *this; }
		#endif
		static Diagram Cast(const Udm::Object &a) { return __Cast(a, meta); }
		static Diagram Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }
		Diagram CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::InstantiatedAttr<Diagram> Instances() { return Udm::InstantiatedAttr<Diagram>(impl); }
		template <class Pred> Udm::InstantiatedAttr<Diagram, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<Diagram, Pred>(impl); }
		Diagram CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::DerivedAttr<Diagram> Derived() { return Udm::DerivedAttr<Diagram>(impl); }
		template <class Pred> Udm::DerivedAttr<Diagram, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<Diagram, Pred>(impl); }
		Udm::ArchetypeAttr<Diagram> Archetype() const { return Udm::ArchetypeAttr<Diagram>(impl); }
		Udm::StringAttr version() const { return Udm::StringAttr(impl, meta_version); }
		Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }
		Udm::ChildrenAttr< ::Uml::Class> classes() const { return Udm::ChildrenAttr< ::Uml::Class>(impl, meta_classes); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Class, Pred> classes_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Class, Pred>(impl, meta_classes); }
		Udm::ChildrenAttr< ::Uml::Association> associations() const { return Udm::ChildrenAttr< ::Uml::Association>(impl, meta_associations); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Association, Pred> associations_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Association, Pred>(impl, meta_associations); }
		Udm::ChildrenAttr< ::Uml::Composition> compositions() const { return Udm::ChildrenAttr< ::Uml::Composition>(impl, meta_compositions); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Composition, Pred> compositions_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Composition, Pred>(impl, meta_compositions); }
		Udm::ChildrenAttr< ::Uml::Namespace> namespaces() const { return Udm::ChildrenAttr< ::Uml::Namespace>(impl, meta_namespaces); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Namespace, Pred> namespaces_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Namespace, Pred>(impl, meta_namespaces); }
		Udm::ChildrenAttr< ::Uml::Class> Class_kind_children() const { return Udm::ChildrenAttr< ::Uml::Class>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Class, Pred> Class_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Class, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ChildrenAttr< ::Uml::Association> Association_kind_children() const { return Udm::ChildrenAttr< ::Uml::Association>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Association, Pred> Association_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Association, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ChildrenAttr< ::Uml::Composition> Composition_kind_children() const { return Udm::ChildrenAttr< ::Uml::Composition>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Composition, Pred> Composition_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Composition, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ChildrenAttr< ::Uml::Namespace> Namespace_kind_children() const { return Udm::ChildrenAttr< ::Uml::Namespace>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Namespace, Pred> Namespace_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Namespace, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ParentAttr<Udm::Object> parent() const { return Udm::ParentAttr<Udm::Object>(impl, Udm::NULLPARENTROLE); }

		static ::Uml::Class meta;
		static ::Uml::Attribute meta_version;
		static ::Uml::Attribute meta_name;
		static ::Uml::CompositionChildRole meta_classes;
		static ::Uml::CompositionChildRole meta_associations;
		static ::Uml::CompositionChildRole meta_compositions;
		static ::Uml::CompositionChildRole meta_namespaces;

	};

	class UDM_DLL Association : public Udm::Object {
	public:
		Association() {}
		Association(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) {}
		Association(const Association &master) : UDM_OBJECT(master) {}
		#ifdef UDM_RVALUE
		Association(Association &&master) : UDM_OBJECT(master) {}

		static Association Cast(Udm::Object &&a) { return __Cast(std::move(a), meta); }
		Association& operator=(Association &&a) { Udm::Object::operator =(std::move(a)); return *this; }
		#endif
		static Association Cast(const Udm::Object &a) { return __Cast(a, meta); }
		static Association Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }
		Association CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::InstantiatedAttr<Association> Instances() { return Udm::InstantiatedAttr<Association>(impl); }
		template <class Pred> Udm::InstantiatedAttr<Association, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<Association, Pred>(impl); }
		Association CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::DerivedAttr<Association> Derived() { return Udm::DerivedAttr<Association>(impl); }
		template <class Pred> Udm::DerivedAttr<Association, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<Association, Pred>(impl); }
		Udm::ArchetypeAttr<Association> Archetype() const { return Udm::ArchetypeAttr<Association>(impl); }
		Udm::BooleanAttr nonpersistent() const { return Udm::BooleanAttr(impl, meta_nonpersistent); }
		Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }
		Udm::PointerAttr< Class> assocClass() const { return Udm::PointerAttr< Class>(impl, meta_assocClass); }
		Udm::ChildrenAttr< ::Uml::AssociationRole> roles() const { return Udm::ChildrenAttr< ::Uml::AssociationRole>(impl, meta_roles); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::AssociationRole, Pred> roles_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::AssociationRole, Pred>(impl, meta_roles); }
		Udm::ChildrenAttr< ::Uml::TaggedValue> tagValues() const { return Udm::ChildrenAttr< ::Uml::TaggedValue>(impl, meta_tagValues); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::TaggedValue, Pred> tagValues_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::TaggedValue, Pred>(impl, meta_tagValues); }
		Udm::ChildrenAttr< ::Uml::GenericRole> GenericRole_kind_children() const { return Udm::ChildrenAttr< ::Uml::GenericRole>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::GenericRole, Pred> GenericRole_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::GenericRole, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ChildrenAttr< ::Uml::AssociationRole> AssociationRole_kind_children() const { return Udm::ChildrenAttr< ::Uml::AssociationRole>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::AssociationRole, Pred> AssociationRole_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::AssociationRole, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ChildrenAttr< ::Uml::TaggedValue> TaggedValue_kind_children() const { return Udm::ChildrenAttr< ::Uml::TaggedValue>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::TaggedValue, Pred> TaggedValue_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::TaggedValue, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ParentAttr< ::Uml::Diagram> parent() const { return Udm::ParentAttr< ::Uml::Diagram>(impl, meta_parent); }
		Udm::ParentAttr< ::Uml::Namespace> parent_ns() const { return Udm::ParentAttr< ::Uml::Namespace>(impl, meta_parent_ns); }

		static ::Uml::Class meta;
		static ::Uml::Attribute meta_nonpersistent;
		static ::Uml::Attribute meta_name;
		static ::Uml::AssociationRole meta_assocClass;
		static ::Uml::CompositionChildRole meta_roles;
		static ::Uml::CompositionChildRole meta_tagValues;
		static ::Uml::CompositionParentRole meta_parent;
		static ::Uml::CompositionParentRole meta_parent_ns;

	};

	class UDM_DLL Composition : public Udm::Object {
	public:
		Composition() {}
		Composition(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) {}
		Composition(const Composition &master) : UDM_OBJECT(master) {}
		#ifdef UDM_RVALUE
		Composition(Composition &&master) : UDM_OBJECT(master) {}

		static Composition Cast(Udm::Object &&a) { return __Cast(std::move(a), meta); }
		Composition& operator=(Composition &&a) { Udm::Object::operator =(std::move(a)); return *this; }
		#endif
		static Composition Cast(const Udm::Object &a) { return __Cast(a, meta); }
		static Composition Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }
		Composition CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::InstantiatedAttr<Composition> Instances() { return Udm::InstantiatedAttr<Composition>(impl); }
		template <class Pred> Udm::InstantiatedAttr<Composition, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<Composition, Pred>(impl); }
		Composition CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::DerivedAttr<Composition> Derived() { return Udm::DerivedAttr<Composition>(impl); }
		template <class Pred> Udm::DerivedAttr<Composition, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<Composition, Pred>(impl); }
		Udm::ArchetypeAttr<Composition> Archetype() const { return Udm::ArchetypeAttr<Composition>(impl); }
		Udm::BooleanAttr nonpersistent() const { return Udm::BooleanAttr(impl, meta_nonpersistent); }
		Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }
		Udm::ChildAttr< ::Uml::CompositionParentRole> parentRole() const { return Udm::ChildAttr< ::Uml::CompositionParentRole>(impl, meta_parentRole); }
		Udm::ChildAttr< ::Uml::CompositionChildRole> childRole() const { return Udm::ChildAttr< ::Uml::CompositionChildRole>(impl, meta_childRole); }
		Udm::ChildrenAttr< ::Uml::CompositionChildRole> CompositionChildRole_kind_children() const { return Udm::ChildrenAttr< ::Uml::CompositionChildRole>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::CompositionChildRole, Pred> CompositionChildRole_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::CompositionChildRole, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ChildrenAttr< ::Uml::GenericRole> GenericRole_kind_children() const { return Udm::ChildrenAttr< ::Uml::GenericRole>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::GenericRole, Pred> GenericRole_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::GenericRole, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ChildrenAttr< ::Uml::CompositionParentRole> CompositionParentRole_kind_children() const { return Udm::ChildrenAttr< ::Uml::CompositionParentRole>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::CompositionParentRole, Pred> CompositionParentRole_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::CompositionParentRole, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ParentAttr< ::Uml::Diagram> parent() const { return Udm::ParentAttr< ::Uml::Diagram>(impl, meta_parent); }
		Udm::ParentAttr< ::Uml::Namespace> parent_ns() const { return Udm::ParentAttr< ::Uml::Namespace>(impl, meta_parent_ns); }

		static ::Uml::Class meta;
		static ::Uml::Attribute meta_nonpersistent;
		static ::Uml::Attribute meta_name;
		static ::Uml::CompositionChildRole meta_parentRole;
		static ::Uml::CompositionChildRole meta_childRole;
		static ::Uml::CompositionParentRole meta_parent;
		static ::Uml::CompositionParentRole meta_parent_ns;

	};

	class UDM_DLL Namespace : public Udm::Object {
	public:
		Namespace() {}
		Namespace(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) {}
		Namespace(const Namespace &master) : UDM_OBJECT(master) {}
		#ifdef UDM_RVALUE
		Namespace(Namespace &&master) : UDM_OBJECT(master) {}

		static Namespace Cast(Udm::Object &&a) { return __Cast(std::move(a), meta); }
		Namespace& operator=(Namespace &&a) { Udm::Object::operator =(std::move(a)); return *this; }
		#endif
		static Namespace Cast(const Udm::Object &a) { return __Cast(a, meta); }
		static Namespace Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }
		Namespace CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::InstantiatedAttr<Namespace> Instances() { return Udm::InstantiatedAttr<Namespace>(impl); }
		template <class Pred> Udm::InstantiatedAttr<Namespace, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<Namespace, Pred>(impl); }
		Namespace CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::DerivedAttr<Namespace> Derived() { return Udm::DerivedAttr<Namespace>(impl); }
		template <class Pred> Udm::DerivedAttr<Namespace, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<Namespace, Pred>(impl); }
		Udm::ArchetypeAttr<Namespace> Archetype() const { return Udm::ArchetypeAttr<Namespace>(impl); }
		Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }
		Udm::ChildrenAttr< ::Uml::Namespace> namespaces() const { return Udm::ChildrenAttr< ::Uml::Namespace>(impl, meta_namespaces); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Namespace, Pred> namespaces_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Namespace, Pred>(impl, meta_namespaces); }
		Udm::ChildrenAttr< ::Uml::Class> classes() const { return Udm::ChildrenAttr< ::Uml::Class>(impl, meta_classes); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Class, Pred> classes_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Class, Pred>(impl, meta_classes); }
		Udm::ChildrenAttr< ::Uml::Composition> compositions() const { return Udm::ChildrenAttr< ::Uml::Composition>(impl, meta_compositions); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Composition, Pred> compositions_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Composition, Pred>(impl, meta_compositions); }
		Udm::ChildrenAttr< ::Uml::Association> associations() const { return Udm::ChildrenAttr< ::Uml::Association>(impl, meta_associations); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Association, Pred> associations_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Association, Pred>(impl, meta_associations); }
		Udm::ChildrenAttr< ::Uml::Class> Class_kind_children() const { return Udm::ChildrenAttr< ::Uml::Class>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Class, Pred> Class_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Class, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ChildrenAttr< ::Uml::Association> Association_kind_children() const { return Udm::ChildrenAttr< ::Uml::Association>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Association, Pred> Association_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Association, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ChildrenAttr< ::Uml::Composition> Composition_kind_children() const { return Udm::ChildrenAttr< ::Uml::Composition>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Composition, Pred> Composition_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Composition, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ChildrenAttr< ::Uml::Namespace> Namespace_kind_children() const { return Udm::ChildrenAttr< ::Uml::Namespace>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::Uml::Namespace, Pred> Namespace_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Namespace, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ParentAttr< ::Uml::Diagram> parent() const { return Udm::ParentAttr< ::Uml::Diagram>(impl, meta_parent); }
		Udm::ParentAttr< ::Uml::Namespace> parent_ns() const { return Udm::ParentAttr< ::Uml::Namespace>(impl, meta_parent_ns); }

		static ::Uml::Class meta;
		static ::Uml::Attribute meta_name;
		static ::Uml::CompositionChildRole meta_namespaces;
		static ::Uml::CompositionChildRole meta_classes;
		static ::Uml::CompositionChildRole meta_compositions;
		static ::Uml::CompositionChildRole meta_associations;
		static ::Uml::CompositionParentRole meta_parent;
		static ::Uml::CompositionParentRole meta_parent_ns;

	};

	class UDM_DLL TaggedValue : public Udm::Object {
	public:
		TaggedValue() {}
		TaggedValue(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) {}
		TaggedValue(const TaggedValue &master) : UDM_OBJECT(master) {}
		#ifdef UDM_RVALUE
		TaggedValue(TaggedValue &&master) : UDM_OBJECT(master) {}

		static TaggedValue Cast(Udm::Object &&a) { return __Cast(std::move(a), meta); }
		TaggedValue& operator=(TaggedValue &&a) { Udm::Object::operator =(std::move(a)); return *this; }
		#endif
		static TaggedValue Cast(const Udm::Object &a) { return __Cast(a, meta); }
		static TaggedValue Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }
		TaggedValue CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::InstantiatedAttr<TaggedValue> Instances() { return Udm::InstantiatedAttr<TaggedValue>(impl); }
		template <class Pred> Udm::InstantiatedAttr<TaggedValue, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<TaggedValue, Pred>(impl); }
		TaggedValue CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::DerivedAttr<TaggedValue> Derived() { return Udm::DerivedAttr<TaggedValue>(impl); }
		template <class Pred> Udm::DerivedAttr<TaggedValue, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<TaggedValue, Pred>(impl); }
		Udm::ArchetypeAttr<TaggedValue> Archetype() const { return Udm::ArchetypeAttr<TaggedValue>(impl); }
		Udm::StringAttr value() const { return Udm::StringAttr(impl, meta_value); }
		Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }
		Udm::ParentAttr< ::Uml::Association> assocParent() const { return Udm::ParentAttr< ::Uml::Association>(impl, meta_assocParent); }
		Udm::ParentAttr< ::Uml::Class> classParent() const { return Udm::ParentAttr< ::Uml::Class>(impl, meta_classParent); }
		Udm::ParentAttr<Udm::Object> parent() const { return Udm::ParentAttr<Udm::Object>(impl, Udm::NULLPARENTROLE); }

		static ::Uml::Class meta;
		static ::Uml::Attribute meta_value;
		static ::Uml::Attribute meta_name;
		static ::Uml::CompositionParentRole meta_assocParent;
		static ::Uml::CompositionParentRole meta_classParent;

	};

	class UDM_DLL ConstraintDefinition : public Udm::Object {
	public:
		ConstraintDefinition() {}
		ConstraintDefinition(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) {}
		ConstraintDefinition(const ConstraintDefinition &master) : UDM_OBJECT(master) {}
		#ifdef UDM_RVALUE
		ConstraintDefinition(ConstraintDefinition &&master) : UDM_OBJECT(master) {}

		static ConstraintDefinition Cast(Udm::Object &&a) { return __Cast(std::move(a), meta); }
		ConstraintDefinition& operator=(ConstraintDefinition &&a) { Udm::Object::operator =(std::move(a)); return *this; }
		#endif
		static ConstraintDefinition Cast(const Udm::Object &a) { return __Cast(a, meta); }
		static ConstraintDefinition Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }
		ConstraintDefinition CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::InstantiatedAttr<ConstraintDefinition> Instances() { return Udm::InstantiatedAttr<ConstraintDefinition>(impl); }
		template <class Pred> Udm::InstantiatedAttr<ConstraintDefinition, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<ConstraintDefinition, Pred>(impl); }
		ConstraintDefinition CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::DerivedAttr<ConstraintDefinition> Derived() { return Udm::DerivedAttr<ConstraintDefinition>(impl); }
		template <class Pred> Udm::DerivedAttr<ConstraintDefinition, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<ConstraintDefinition, Pred>(impl); }
		Udm::ArchetypeAttr<ConstraintDefinition> Archetype() const { return Udm::ArchetypeAttr<ConstraintDefinition>(impl); }
		Udm::StringAttr stereotype() const { return Udm::StringAttr(impl, meta_stereotype); }
		Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }
		Udm::StringAttr parameterList() const { return Udm::StringAttr(impl, meta_parameterList); }
		Udm::StringAttr expression() const { return Udm::StringAttr(impl, meta_expression); }
		Udm::StringAttr returnType() const { return Udm::StringAttr(impl, meta_returnType); }
		Udm::ParentAttr< ::Uml::Class> parent() const { return Udm::ParentAttr< ::Uml::Class>(impl, meta_parent); }

		static ::Uml::Class meta;
		static ::Uml::Attribute meta_stereotype;
		static ::Uml::Attribute meta_name;
		static ::Uml::Attribute meta_parameterList;
		static ::Uml::Attribute meta_expression;
		static ::Uml::Attribute meta_returnType;
		static ::Uml::CompositionParentRole meta_parent;

	};

	class UDM_DLL Attribute : public Udm::Object {
	public:
		Attribute() {}
		Attribute(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) {}
		Attribute(const Attribute &master) : UDM_OBJECT(master) {}
		#ifdef UDM_RVALUE
		Attribute(Attribute &&master) : UDM_OBJECT(master) {}

		static Attribute Cast(Udm::Object &&a) { return __Cast(std::move(a), meta); }
		Attribute& operator=(Attribute &&a) { Udm::Object::operator =(std::move(a)); return *this; }
		#endif
		static Attribute Cast(const Udm::Object &a) { return __Cast(a, meta); }
		static Attribute Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }
		Attribute CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::InstantiatedAttr<Attribute> Instances() { return Udm::InstantiatedAttr<Attribute>(impl); }
		template <class Pred> Udm::InstantiatedAttr<Attribute, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<Attribute, Pred>(impl); }
		Attribute CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::DerivedAttr<Attribute> Derived() { return Udm::DerivedAttr<Attribute>(impl); }
		template <class Pred> Udm::DerivedAttr<Attribute, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<Attribute, Pred>(impl); }
		Udm::ArchetypeAttr<Attribute> Archetype() const { return Udm::ArchetypeAttr<Attribute>(impl); }
		Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }
		Udm::StringAttr type() const { return Udm::StringAttr(impl, meta_type); }
		Udm::StringAttrArr defvalue() const { return Udm::StringAttrArr(impl, meta_defvalue); }
		Udm::IntegerAttr min() const { return Udm::IntegerAttr(impl, meta_min); }
		Udm::IntegerAttr max() const { return Udm::IntegerAttr(impl, meta_max); }
		Udm::StringAttr visibility() const { return Udm::StringAttr(impl, meta_visibility); }
		Udm::BooleanAttr ordered() const { return Udm::BooleanAttr(impl, meta_ordered); }
		Udm::BooleanAttr nonpersistent() const { return Udm::BooleanAttr(impl, meta_nonpersistent); }
		Udm::BooleanAttr registry() const { return Udm::BooleanAttr(impl, meta_registry); }
		Udm::ParentAttr< ::Uml::Class> parent() const { return Udm::ParentAttr< ::Uml::Class>(impl, meta_parent); }

		static ::Uml::Class meta;
		static ::Uml::Attribute meta_name;
		static ::Uml::Attribute meta_type;
		static ::Uml::Attribute meta_defvalue;
		static ::Uml::Attribute meta_min;
		static ::Uml::Attribute meta_max;
		static ::Uml::Attribute meta_visibility;
		static ::Uml::Attribute meta_ordered;
		static ::Uml::Attribute meta_nonpersistent;
		static ::Uml::Attribute meta_registry;
		static ::Uml::CompositionParentRole meta_parent;

	};

	class UDM_DLL Constraint : public Udm::Object {
	public:
		Constraint() {}
		Constraint(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) {}
		Constraint(const Constraint &master) : UDM_OBJECT(master) {}
		#ifdef UDM_RVALUE
		Constraint(Constraint &&master) : UDM_OBJECT(master) {}

		static Constraint Cast(Udm::Object &&a) { return __Cast(std::move(a), meta); }
		Constraint& operator=(Constraint &&a) { Udm::Object::operator =(std::move(a)); return *this; }
		#endif
		static Constraint Cast(const Udm::Object &a) { return __Cast(a, meta); }
		static Constraint Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }
		Constraint CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::InstantiatedAttr<Constraint> Instances() { return Udm::InstantiatedAttr<Constraint>(impl); }
		template <class Pred> Udm::InstantiatedAttr<Constraint, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<Constraint, Pred>(impl); }
		Constraint CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::DerivedAttr<Constraint> Derived() { return Udm::DerivedAttr<Constraint>(impl); }
		template <class Pred> Udm::DerivedAttr<Constraint, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<Constraint, Pred>(impl); }
		Udm::ArchetypeAttr<Constraint> Archetype() const { return Udm::ArchetypeAttr<Constraint>(impl); }
		Udm::StringAttr description() const { return Udm::StringAttr(impl, meta_description); }
		Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }
		Udm::StringAttr expression() const { return Udm::StringAttr(impl, meta_expression); }
		Udm::ParentAttr< ::Uml::Class> parent() const { return Udm::ParentAttr< ::Uml::Class>(impl, meta_parent); }

		static ::Uml::Class meta;
		static ::Uml::Attribute meta_description;
		static ::Uml::Attribute meta_name;
		static ::Uml::Attribute meta_expression;
		static ::Uml::CompositionParentRole meta_parent;

	};

}

#endif // MOBIES_UML_H
