#ifndef MOBIES_UML_H
#define MOBIES_UML_H
// header file Uml.h generated from diagram Uml
// generated on Sun Jan 16 11:06:52 2005

#ifndef MOBIES_UDMBASE_H
#include "UdmBase.h"
#endif

namespace Uml {
	extern UDM_DLL Udm::UdmDiagram diagram;
	UDM_DLL void Initialize(const ::Uml::Uml::Diagram &dgr);
	UDM_DLL void Initialize();


	namespace Uml {

		class UDM_DLL Composition;
		class UDM_DLL Attribute;
		class UDM_DLL Class;
		class UDM_DLL Association;
		class UDM_DLL ConstraintDefinition;
		class UDM_DLL AssociationRole;
		class UDM_DLL Constraint;
		class UDM_DLL CompositionParentRole;
		class UDM_DLL Diagram;
		class UDM_DLL TaggedValue;
		class UDM_DLL Namespace;
		class UDM_DLL GenericRole;
		class UDM_DLL CompositionChildRole;
		UDM_DLL extern ::Uml::Uml::Namespace meta;

		UDM_DLL void Initialize();
		UDM_DLL void Initialize(const ::Uml::Uml::Diagram &dgr);

		class UDM_DLL Composition :  public Udm::Object {
		public:
			static ::Uml::Uml::Class meta;

			Composition() { }
			Composition(Udm::ObjectImpl *impl) : Object(impl) { }
			Composition(const Composition &master) : Object(master) { }
			static Composition Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static Composition Create(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			Composition CreateInstance(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			Composition CreateDerived(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr<Composition> Instances() { return Udm::InstantiatedAttr<::Uml::Uml::Composition>(impl);}
			template <class Pred> Udm::InstantiatedAttr<Composition, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<::Uml::Uml::Composition, Pred>(impl);}

			Udm::DerivedAttr<::Uml::Uml::Composition> Derived() { return Udm::DerivedAttr<::Uml::Uml::Composition>(impl);}
			template <class Pred> Udm::DerivedAttr<::Uml::Uml::Composition, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<::Uml::Uml::Composition, Pred>(impl);}

			Udm::ArchetypeAttr<::Uml::Uml::Composition> Archetype() { return Udm::ArchetypeAttr<::Uml::Uml::Composition>(impl);}

			static ::Uml::Uml::Attribute meta_nonpersistent;
			Udm::BooleanAttr nonpersistent() const { return Udm::BooleanAttr(impl, meta_nonpersistent); }

			static ::Uml::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::Uml::CompositionChildRole meta_parentRole;
			Udm::ChildAttr<::Uml::Uml::CompositionParentRole> parentRole() const { return Udm::ChildAttr<::Uml::Uml::CompositionParentRole>(impl, meta_parentRole); }

			static ::Uml::Uml::CompositionChildRole meta_childRole;
			Udm::ChildAttr<::Uml::Uml::CompositionChildRole> childRole() const { return Udm::ChildAttr<::Uml::Uml::CompositionChildRole>(impl, meta_childRole); }

			Udm::ChildrenAttr<::Uml::Uml::CompositionParentRole> CompositionParentRole_kind_children() const { return Udm::ChildrenAttr<::Uml::Uml::CompositionParentRole>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr<::Uml::Uml::CompositionParentRole, Pred> CompositionParentRole_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::CompositionParentRole, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr<::Uml::Uml::GenericRole> GenericRole_kind_children() const { return Udm::ChildrenAttr<::Uml::Uml::GenericRole>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr<::Uml::Uml::GenericRole, Pred> GenericRole_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::GenericRole, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr<::Uml::Uml::CompositionChildRole> CompositionChildRole_kind_children() const { return Udm::ChildrenAttr<::Uml::Uml::CompositionChildRole>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr<::Uml::Uml::CompositionChildRole, Pred> CompositionChildRole_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::CompositionChildRole, Pred>(impl, Udm::NULLCHILDROLE); }

			static ::Uml::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr<::Uml::Uml::Namespace> parent() const { return Udm::ParentAttr<::Uml::Uml::Namespace>(impl, meta_parent); }

		};
		class UDM_DLL Attribute :  public Udm::Object {
		public:
			static ::Uml::Uml::Class meta;

			Attribute() { }
			Attribute(Udm::ObjectImpl *impl) : Object(impl) { }
			Attribute(const Attribute &master) : Object(master) { }
			static Attribute Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static Attribute Create(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			Attribute CreateInstance(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			Attribute CreateDerived(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr<Attribute> Instances() { return Udm::InstantiatedAttr<::Uml::Uml::Attribute>(impl);}
			template <class Pred> Udm::InstantiatedAttr<Attribute, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<::Uml::Uml::Attribute, Pred>(impl);}

			Udm::DerivedAttr<::Uml::Uml::Attribute> Derived() { return Udm::DerivedAttr<::Uml::Uml::Attribute>(impl);}
			template <class Pred> Udm::DerivedAttr<::Uml::Uml::Attribute, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<::Uml::Uml::Attribute, Pred>(impl);}

			Udm::ArchetypeAttr<::Uml::Uml::Attribute> Archetype() { return Udm::ArchetypeAttr<::Uml::Uml::Attribute>(impl);}

			static ::Uml::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::Uml::Attribute meta_type;
			Udm::StringAttr type() const { return Udm::StringAttr(impl, meta_type); }

			static ::Uml::Uml::Attribute meta_defvalue;
			Udm::StringAttrArr defvalue() const { return Udm::StringAttrArr(impl, meta_defvalue); }

			static ::Uml::Uml::Attribute meta_min;
			Udm::IntegerAttr min() const { return Udm::IntegerAttr(impl, meta_min); }

			static ::Uml::Uml::Attribute meta_max;
			Udm::IntegerAttr max() const { return Udm::IntegerAttr(impl, meta_max); }

			static ::Uml::Uml::Attribute meta_visibility;
			Udm::StringAttr visibility() const { return Udm::StringAttr(impl, meta_visibility); }

			static ::Uml::Uml::Attribute meta_ordered;
			Udm::BooleanAttr ordered() const { return Udm::BooleanAttr(impl, meta_ordered); }

			static ::Uml::Uml::Attribute meta_nonpersistent;
			Udm::BooleanAttr nonpersistent() const { return Udm::BooleanAttr(impl, meta_nonpersistent); }

			static ::Uml::Uml::Attribute meta_registry;
			Udm::BooleanAttr registry() const { return Udm::BooleanAttr(impl, meta_registry); }

			static ::Uml::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr<::Uml::Uml::Class> parent() const { return Udm::ParentAttr<::Uml::Uml::Class>(impl, meta_parent); }

		};
		class UDM_DLL Class :  public Udm::Object {
		public:
			static ::Uml::Uml::Class meta;

			Class() { }
			Class(Udm::ObjectImpl *impl) : Object(impl) { }
			Class(const Class &master) : Object(master) { }
			static Class Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static Class Create(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			Class CreateInstance(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			Class CreateDerived(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr<Class> Instances() { return Udm::InstantiatedAttr<::Uml::Uml::Class>(impl);}
			template <class Pred> Udm::InstantiatedAttr<Class, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<::Uml::Uml::Class, Pred>(impl);}

			Udm::DerivedAttr<::Uml::Uml::Class> Derived() { return Udm::DerivedAttr<::Uml::Uml::Class>(impl);}
			template <class Pred> Udm::DerivedAttr<::Uml::Uml::Class, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<::Uml::Uml::Class, Pred>(impl);}

			Udm::ArchetypeAttr<::Uml::Uml::Class> Archetype() { return Udm::ArchetypeAttr<::Uml::Uml::Class>(impl);}

			static ::Uml::Uml::Attribute meta_isAbstract;
			Udm::BooleanAttr isAbstract() const { return Udm::BooleanAttr(impl, meta_isAbstract); }

			static ::Uml::Uml::Attribute meta_stereotype;
			Udm::StringAttr stereotype() const { return Udm::StringAttr(impl, meta_stereotype); }

			static ::Uml::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::Uml::Attribute meta_from;
			Udm::StringAttr from() const { return Udm::StringAttr(impl, meta_from); }

			static ::Uml::Uml::AssociationRole meta_subTypes;
			Udm::AssocAttr<::Uml::Uml::Class> subTypes() const { return Udm::AssocAttr<::Uml::Uml::Class>(impl, meta_subTypes); }
			template <class Pred> Udm::AssocAttr<::Uml::Uml::Class, Pred > subTypes_sorted(const Pred &) const { return Udm::AssocAttr<::Uml::Uml::Class, Pred>(impl, meta_subTypes); }

			static ::Uml::Uml::AssociationRole meta_baseTypes;
			Udm::AssocAttr<::Uml::Uml::Class> baseTypes() const { return Udm::AssocAttr<::Uml::Uml::Class>(impl, meta_baseTypes); }
			template <class Pred> Udm::AssocAttr<::Uml::Uml::Class, Pred > baseTypes_sorted(const Pred &) const { return Udm::AssocAttr<::Uml::Uml::Class, Pred>(impl, meta_baseTypes); }

			static ::Uml::Uml::AssociationRole meta_association;
			Udm::PointerAttr<::Uml::Uml::Association> association() const { return Udm::PointerAttr<::Uml::Uml::Association>(impl, meta_association); }

			static ::Uml::Uml::AssociationRole meta_associationRoles;
			Udm::AssocAttr<::Uml::Uml::AssociationRole> associationRoles() const { return Udm::AssocAttr<::Uml::Uml::AssociationRole>(impl, meta_associationRoles); }
			template <class Pred> Udm::AssocAttr<::Uml::Uml::AssociationRole, Pred > associationRoles_sorted(const Pred &) const { return Udm::AssocAttr<::Uml::Uml::AssociationRole, Pred>(impl, meta_associationRoles); }

			static ::Uml::Uml::AssociationRole meta_parentRoles;
			Udm::AssocAttr<::Uml::Uml::CompositionParentRole> parentRoles() const { return Udm::AssocAttr<::Uml::Uml::CompositionParentRole>(impl, meta_parentRoles); }
			template <class Pred> Udm::AssocAttr<::Uml::Uml::CompositionParentRole, Pred > parentRoles_sorted(const Pred &) const { return Udm::AssocAttr<::Uml::Uml::CompositionParentRole, Pred>(impl, meta_parentRoles); }

			static ::Uml::Uml::AssociationRole meta_childRoles;
			Udm::AssocAttr<::Uml::Uml::CompositionChildRole> childRoles() const { return Udm::AssocAttr<::Uml::Uml::CompositionChildRole>(impl, meta_childRoles); }
			template <class Pred> Udm::AssocAttr<::Uml::Uml::CompositionChildRole, Pred > childRoles_sorted(const Pred &) const { return Udm::AssocAttr<::Uml::Uml::CompositionChildRole, Pred>(impl, meta_childRoles); }

			static ::Uml::Uml::CompositionChildRole meta_attributes;
			Udm::ChildrenAttr<::Uml::Uml::Attribute> attributes() const { return Udm::ChildrenAttr<::Uml::Uml::Attribute>(impl, meta_attributes); }
			template <class Pred> Udm::ChildrenAttr<::Uml::Uml::Attribute, Pred> attributes_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::Attribute, Pred>(impl, meta_attributes); }

			static ::Uml::Uml::CompositionChildRole meta_tagValues;
			Udm::ChildrenAttr<::Uml::Uml::TaggedValue> tagValues() const { return Udm::ChildrenAttr<::Uml::Uml::TaggedValue>(impl, meta_tagValues); }
			template <class Pred> Udm::ChildrenAttr<::Uml::Uml::TaggedValue, Pred> tagValues_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::TaggedValue, Pred>(impl, meta_tagValues); }

			static ::Uml::Uml::CompositionChildRole meta_constraints;
			Udm::ChildrenAttr<::Uml::Uml::Constraint> constraints() const { return Udm::ChildrenAttr<::Uml::Uml::Constraint>(impl, meta_constraints); }
			template <class Pred> Udm::ChildrenAttr<::Uml::Uml::Constraint, Pred> constraints_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::Constraint, Pred>(impl, meta_constraints); }

			static ::Uml::Uml::CompositionChildRole meta_definitions;
			Udm::ChildrenAttr<::Uml::Uml::ConstraintDefinition> definitions() const { return Udm::ChildrenAttr<::Uml::Uml::ConstraintDefinition>(impl, meta_definitions); }
			template <class Pred> Udm::ChildrenAttr<::Uml::Uml::ConstraintDefinition, Pred> definitions_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::ConstraintDefinition, Pred>(impl, meta_definitions); }

			Udm::ChildrenAttr<::Uml::Uml::Attribute> Attribute_kind_children() const { return Udm::ChildrenAttr<::Uml::Uml::Attribute>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr<::Uml::Uml::Attribute, Pred> Attribute_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::Attribute, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr<::Uml::Uml::ConstraintDefinition> ConstraintDefinition_kind_children() const { return Udm::ChildrenAttr<::Uml::Uml::ConstraintDefinition>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr<::Uml::Uml::ConstraintDefinition, Pred> ConstraintDefinition_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::ConstraintDefinition, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr<::Uml::Uml::Constraint> Constraint_kind_children() const { return Udm::ChildrenAttr<::Uml::Uml::Constraint>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr<::Uml::Uml::Constraint, Pred> Constraint_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::Constraint, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr<::Uml::Uml::TaggedValue> TaggedValue_kind_children() const { return Udm::ChildrenAttr<::Uml::Uml::TaggedValue>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr<::Uml::Uml::TaggedValue, Pred> TaggedValue_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::TaggedValue, Pred>(impl, Udm::NULLCHILDROLE); }

			static ::Uml::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr<::Uml::Uml::Namespace> parent() const { return Udm::ParentAttr<::Uml::Uml::Namespace>(impl, meta_parent); }

		};
		class UDM_DLL Association :  public Udm::Object {
		public:
			static ::Uml::Uml::Class meta;

			Association() { }
			Association(Udm::ObjectImpl *impl) : Object(impl) { }
			Association(const Association &master) : Object(master) { }
			static Association Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static Association Create(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			Association CreateInstance(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			Association CreateDerived(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr<Association> Instances() { return Udm::InstantiatedAttr<::Uml::Uml::Association>(impl);}
			template <class Pred> Udm::InstantiatedAttr<Association, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<::Uml::Uml::Association, Pred>(impl);}

			Udm::DerivedAttr<::Uml::Uml::Association> Derived() { return Udm::DerivedAttr<::Uml::Uml::Association>(impl);}
			template <class Pred> Udm::DerivedAttr<::Uml::Uml::Association, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<::Uml::Uml::Association, Pred>(impl);}

			Udm::ArchetypeAttr<::Uml::Uml::Association> Archetype() { return Udm::ArchetypeAttr<::Uml::Uml::Association>(impl);}

			static ::Uml::Uml::Attribute meta_nonpersistent;
			Udm::BooleanAttr nonpersistent() const { return Udm::BooleanAttr(impl, meta_nonpersistent); }

			static ::Uml::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::Uml::AssociationRole meta_assocClass;
			Udm::PointerAttr<::Uml::Uml::Class> assocClass() const { return Udm::PointerAttr<::Uml::Uml::Class>(impl, meta_assocClass); }

			static ::Uml::Uml::CompositionChildRole meta_roles;
			Udm::ChildrenAttr<::Uml::Uml::AssociationRole> roles() const { return Udm::ChildrenAttr<::Uml::Uml::AssociationRole>(impl, meta_roles); }
			template <class Pred> Udm::ChildrenAttr<::Uml::Uml::AssociationRole, Pred> roles_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::AssociationRole, Pred>(impl, meta_roles); }

			static ::Uml::Uml::CompositionChildRole meta_tagValues;
			Udm::ChildrenAttr<::Uml::Uml::TaggedValue> tagValues() const { return Udm::ChildrenAttr<::Uml::Uml::TaggedValue>(impl, meta_tagValues); }
			template <class Pred> Udm::ChildrenAttr<::Uml::Uml::TaggedValue, Pred> tagValues_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::TaggedValue, Pred>(impl, meta_tagValues); }

			Udm::ChildrenAttr<::Uml::Uml::AssociationRole> AssociationRole_kind_children() const { return Udm::ChildrenAttr<::Uml::Uml::AssociationRole>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr<::Uml::Uml::AssociationRole, Pred> AssociationRole_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::AssociationRole, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr<::Uml::Uml::TaggedValue> TaggedValue_kind_children() const { return Udm::ChildrenAttr<::Uml::Uml::TaggedValue>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr<::Uml::Uml::TaggedValue, Pred> TaggedValue_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::TaggedValue, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr<::Uml::Uml::GenericRole> GenericRole_kind_children() const { return Udm::ChildrenAttr<::Uml::Uml::GenericRole>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr<::Uml::Uml::GenericRole, Pred> GenericRole_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::GenericRole, Pred>(impl, Udm::NULLCHILDROLE); }

			static ::Uml::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr<::Uml::Uml::Namespace> parent() const { return Udm::ParentAttr<::Uml::Uml::Namespace>(impl, meta_parent); }

		};
		class UDM_DLL ConstraintDefinition :  public Udm::Object {
		public:
			static ::Uml::Uml::Class meta;

			ConstraintDefinition() { }
			ConstraintDefinition(Udm::ObjectImpl *impl) : Object(impl) { }
			ConstraintDefinition(const ConstraintDefinition &master) : Object(master) { }
			static ConstraintDefinition Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static ConstraintDefinition Create(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			ConstraintDefinition CreateInstance(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			ConstraintDefinition CreateDerived(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr<ConstraintDefinition> Instances() { return Udm::InstantiatedAttr<::Uml::Uml::ConstraintDefinition>(impl);}
			template <class Pred> Udm::InstantiatedAttr<ConstraintDefinition, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<::Uml::Uml::ConstraintDefinition, Pred>(impl);}

			Udm::DerivedAttr<::Uml::Uml::ConstraintDefinition> Derived() { return Udm::DerivedAttr<::Uml::Uml::ConstraintDefinition>(impl);}
			template <class Pred> Udm::DerivedAttr<::Uml::Uml::ConstraintDefinition, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<::Uml::Uml::ConstraintDefinition, Pred>(impl);}

			Udm::ArchetypeAttr<::Uml::Uml::ConstraintDefinition> Archetype() { return Udm::ArchetypeAttr<::Uml::Uml::ConstraintDefinition>(impl);}

			static ::Uml::Uml::Attribute meta_stereotype;
			Udm::StringAttr stereotype() const { return Udm::StringAttr(impl, meta_stereotype); }

			static ::Uml::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::Uml::Attribute meta_parameterList;
			Udm::StringAttr parameterList() const { return Udm::StringAttr(impl, meta_parameterList); }

			static ::Uml::Uml::Attribute meta_expression;
			Udm::StringAttr expression() const { return Udm::StringAttr(impl, meta_expression); }

			static ::Uml::Uml::Attribute meta_returnType;
			Udm::StringAttr returnType() const { return Udm::StringAttr(impl, meta_returnType); }

			static ::Uml::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr<::Uml::Uml::Class> parent() const { return Udm::ParentAttr<::Uml::Uml::Class>(impl, meta_parent); }

		};
		class UDM_DLL Constraint :  public Udm::Object {
		public:
			static ::Uml::Uml::Class meta;

			Constraint() { }
			Constraint(Udm::ObjectImpl *impl) : Object(impl) { }
			Constraint(const Constraint &master) : Object(master) { }
			static Constraint Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static Constraint Create(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			Constraint CreateInstance(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			Constraint CreateDerived(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr<Constraint> Instances() { return Udm::InstantiatedAttr<::Uml::Uml::Constraint>(impl);}
			template <class Pred> Udm::InstantiatedAttr<Constraint, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<::Uml::Uml::Constraint, Pred>(impl);}

			Udm::DerivedAttr<::Uml::Uml::Constraint> Derived() { return Udm::DerivedAttr<::Uml::Uml::Constraint>(impl);}
			template <class Pred> Udm::DerivedAttr<::Uml::Uml::Constraint, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<::Uml::Uml::Constraint, Pred>(impl);}

			Udm::ArchetypeAttr<::Uml::Uml::Constraint> Archetype() { return Udm::ArchetypeAttr<::Uml::Uml::Constraint>(impl);}

			static ::Uml::Uml::Attribute meta_description;
			Udm::StringAttr description() const { return Udm::StringAttr(impl, meta_description); }

			static ::Uml::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::Uml::Attribute meta_expression;
			Udm::StringAttr expression() const { return Udm::StringAttr(impl, meta_expression); }

			static ::Uml::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr<::Uml::Uml::Class> parent() const { return Udm::ParentAttr<::Uml::Uml::Class>(impl, meta_parent); }

		};
		class UDM_DLL Diagram :  public Udm::Object {
		public:
			static ::Uml::Uml::Class meta;

			Diagram() { }
			Diagram(Udm::ObjectImpl *impl) : Object(impl) { }
			Diagram(const Diagram &master) : Object(master) { }
			static Diagram Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static Diagram Create(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			Diagram CreateInstance(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			Diagram CreateDerived(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr<Diagram> Instances() { return Udm::InstantiatedAttr<::Uml::Uml::Diagram>(impl);}
			template <class Pred> Udm::InstantiatedAttr<Diagram, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<::Uml::Uml::Diagram, Pred>(impl);}

			Udm::DerivedAttr<::Uml::Uml::Diagram> Derived() { return Udm::DerivedAttr<::Uml::Uml::Diagram>(impl);}
			template <class Pred> Udm::DerivedAttr<::Uml::Uml::Diagram, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<::Uml::Uml::Diagram, Pred>(impl);}

			Udm::ArchetypeAttr<::Uml::Uml::Diagram> Archetype() { return Udm::ArchetypeAttr<::Uml::Uml::Diagram>(impl);}

			static ::Uml::Uml::Attribute meta_version;
			Udm::StringAttr version() const { return Udm::StringAttr(impl, meta_version); }

			static ::Uml::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::Uml::CompositionChildRole meta_namespaces;
			Udm::ChildrenAttr<::Uml::Uml::Namespace> namespaces() const { return Udm::ChildrenAttr<::Uml::Uml::Namespace>(impl, meta_namespaces); }
			template <class Pred> Udm::ChildrenAttr<::Uml::Uml::Namespace, Pred> namespaces_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::Namespace, Pred>(impl, meta_namespaces); }

			Udm::ChildrenAttr<::Uml::Uml::Namespace> Namespace_kind_children() const { return Udm::ChildrenAttr<::Uml::Uml::Namespace>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr<::Uml::Uml::Namespace, Pred> Namespace_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::Namespace, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ParentAttr<Udm::Object> parent() const { return Udm::ParentAttr<Udm::Object>(impl, Udm::NULLPARENTROLE); }
		};
		class UDM_DLL TaggedValue :  public Udm::Object {
		public:
			static ::Uml::Uml::Class meta;

			TaggedValue() { }
			TaggedValue(Udm::ObjectImpl *impl) : Object(impl) { }
			TaggedValue(const TaggedValue &master) : Object(master) { }
			static TaggedValue Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static TaggedValue Create(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			TaggedValue CreateInstance(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			TaggedValue CreateDerived(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr<TaggedValue> Instances() { return Udm::InstantiatedAttr<::Uml::Uml::TaggedValue>(impl);}
			template <class Pred> Udm::InstantiatedAttr<TaggedValue, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<::Uml::Uml::TaggedValue, Pred>(impl);}

			Udm::DerivedAttr<::Uml::Uml::TaggedValue> Derived() { return Udm::DerivedAttr<::Uml::Uml::TaggedValue>(impl);}
			template <class Pred> Udm::DerivedAttr<::Uml::Uml::TaggedValue, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<::Uml::Uml::TaggedValue, Pred>(impl);}

			Udm::ArchetypeAttr<::Uml::Uml::TaggedValue> Archetype() { return Udm::ArchetypeAttr<::Uml::Uml::TaggedValue>(impl);}

			static ::Uml::Uml::Attribute meta_value;
			Udm::StringAttr value() const { return Udm::StringAttr(impl, meta_value); }

			static ::Uml::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::Uml::CompositionParentRole meta_assocParent;
			Udm::ParentAttr<::Uml::Uml::Association> assocParent() const { return Udm::ParentAttr<::Uml::Uml::Association>(impl, meta_assocParent); }

			static ::Uml::Uml::CompositionParentRole meta_classParent;
			Udm::ParentAttr<::Uml::Uml::Class> classParent() const { return Udm::ParentAttr<::Uml::Uml::Class>(impl, meta_classParent); }

			Udm::ParentAttr<Udm::Object> parent() const { return Udm::ParentAttr<Udm::Object>(impl, Udm::NULLPARENTROLE); }
		};
		class UDM_DLL Namespace :  public Udm::Object {
		public:
			static ::Uml::Uml::Class meta;

			Namespace() { }
			Namespace(Udm::ObjectImpl *impl) : Object(impl) { }
			Namespace(const Namespace &master) : Object(master) { }
			static Namespace Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static Namespace Create(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			Namespace CreateInstance(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			Namespace CreateDerived(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr<Namespace> Instances() { return Udm::InstantiatedAttr<::Uml::Uml::Namespace>(impl);}
			template <class Pred> Udm::InstantiatedAttr<Namespace, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<::Uml::Uml::Namespace, Pred>(impl);}

			Udm::DerivedAttr<::Uml::Uml::Namespace> Derived() { return Udm::DerivedAttr<::Uml::Uml::Namespace>(impl);}
			template <class Pred> Udm::DerivedAttr<::Uml::Uml::Namespace, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<::Uml::Uml::Namespace, Pred>(impl);}

			Udm::ArchetypeAttr<::Uml::Uml::Namespace> Archetype() { return Udm::ArchetypeAttr<::Uml::Uml::Namespace>(impl);}

			static ::Uml::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::Uml::CompositionChildRole meta_associations;
			Udm::ChildrenAttr<::Uml::Uml::Association> associations() const { return Udm::ChildrenAttr<::Uml::Uml::Association>(impl, meta_associations); }
			template <class Pred> Udm::ChildrenAttr<::Uml::Uml::Association, Pred> associations_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::Association, Pred>(impl, meta_associations); }

			static ::Uml::Uml::CompositionChildRole meta_classes;
			Udm::ChildrenAttr<::Uml::Uml::Class> classes() const { return Udm::ChildrenAttr<::Uml::Uml::Class>(impl, meta_classes); }
			template <class Pred> Udm::ChildrenAttr<::Uml::Uml::Class, Pred> classes_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::Class, Pred>(impl, meta_classes); }

			static ::Uml::Uml::CompositionChildRole meta_compositions;
			Udm::ChildrenAttr<::Uml::Uml::Composition> compositions() const { return Udm::ChildrenAttr<::Uml::Uml::Composition>(impl, meta_compositions); }
			template <class Pred> Udm::ChildrenAttr<::Uml::Uml::Composition, Pred> compositions_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::Composition, Pred>(impl, meta_compositions); }

			Udm::ChildrenAttr<::Uml::Uml::Composition> Composition_kind_children() const { return Udm::ChildrenAttr<::Uml::Uml::Composition>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr<::Uml::Uml::Composition, Pred> Composition_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::Composition, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr<::Uml::Uml::Class> Class_kind_children() const { return Udm::ChildrenAttr<::Uml::Uml::Class>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr<::Uml::Uml::Class, Pred> Class_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::Class, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr<::Uml::Uml::Association> Association_kind_children() const { return Udm::ChildrenAttr<::Uml::Uml::Association>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr<::Uml::Uml::Association, Pred> Association_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr<::Uml::Uml::Association, Pred>(impl, Udm::NULLCHILDROLE); }

			static ::Uml::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr<::Uml::Uml::Diagram> parent() const { return Udm::ParentAttr<::Uml::Uml::Diagram>(impl, meta_parent); }

		};
		class UDM_DLL GenericRole :  public Udm::Object {
		public:
			static ::Uml::Uml::Class meta;

			GenericRole() { }
			GenericRole(Udm::ObjectImpl *impl) : Object(impl) { }
			GenericRole(const GenericRole &master) : Object(master) { }
			static GenericRole Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static GenericRole Create(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			GenericRole CreateInstance(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			GenericRole CreateDerived(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr<GenericRole> Instances() { return Udm::InstantiatedAttr<::Uml::Uml::GenericRole>(impl);}
			template <class Pred> Udm::InstantiatedAttr<GenericRole, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<::Uml::Uml::GenericRole, Pred>(impl);}

			Udm::DerivedAttr<::Uml::Uml::GenericRole> Derived() { return Udm::DerivedAttr<::Uml::Uml::GenericRole>(impl);}
			template <class Pred> Udm::DerivedAttr<::Uml::Uml::GenericRole, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<::Uml::Uml::GenericRole, Pred>(impl);}

			Udm::ArchetypeAttr<::Uml::Uml::GenericRole> Archetype() { return Udm::ArchetypeAttr<::Uml::Uml::GenericRole>(impl);}

			static ::Uml::Uml::Attribute meta_isNavigable;
			Udm::BooleanAttr isNavigable() const { return Udm::BooleanAttr(impl, meta_isNavigable); }

			static ::Uml::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			Udm::ParentAttr<Udm::Object> parent() const { return Udm::ParentAttr<Udm::Object>(impl, Udm::NULLPARENTROLE); }
		};
		class UDM_DLL AssociationRole :  public GenericRole {
		public:
			static ::Uml::Uml::Class meta;

			AssociationRole() { }
			AssociationRole(Udm::ObjectImpl *impl) : GenericRole(impl) { }
			AssociationRole(const AssociationRole &master) : GenericRole(master) { }
			static AssociationRole Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static AssociationRole Create(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			AssociationRole CreateInstance(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			AssociationRole CreateDerived(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr<AssociationRole> Instances() { return Udm::InstantiatedAttr<::Uml::Uml::AssociationRole>(impl);}
			template <class Pred> Udm::InstantiatedAttr<AssociationRole, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<::Uml::Uml::AssociationRole, Pred>(impl);}

			Udm::DerivedAttr<::Uml::Uml::AssociationRole> Derived() { return Udm::DerivedAttr<::Uml::Uml::AssociationRole>(impl);}
			template <class Pred> Udm::DerivedAttr<::Uml::Uml::AssociationRole, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<::Uml::Uml::AssociationRole, Pred>(impl);}

			Udm::ArchetypeAttr<::Uml::Uml::AssociationRole> Archetype() { return Udm::ArchetypeAttr<::Uml::Uml::AssociationRole>(impl);}

			static ::Uml::Uml::Attribute meta_max;
			Udm::IntegerAttr max() const { return Udm::IntegerAttr(impl, meta_max); }

			static ::Uml::Uml::Attribute meta_min;
			Udm::IntegerAttr min() const { return Udm::IntegerAttr(impl, meta_min); }

			static ::Uml::Uml::Attribute meta_isPrimary;
			Udm::BooleanAttr isPrimary() const { return Udm::BooleanAttr(impl, meta_isPrimary); }

			static ::Uml::Uml::AssociationRole meta_target;
			Udm::PointerAttr<::Uml::Uml::Class> target() const { return Udm::PointerAttr<::Uml::Uml::Class>(impl, meta_target); }

			static ::Uml::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr<::Uml::Uml::Association> parent() const { return Udm::ParentAttr<::Uml::Uml::Association>(impl, meta_parent); }

		};
		class UDM_DLL CompositionParentRole :  public GenericRole {
		public:
			static ::Uml::Uml::Class meta;

			CompositionParentRole() { }
			CompositionParentRole(Udm::ObjectImpl *impl) : GenericRole(impl) { }
			CompositionParentRole(const CompositionParentRole &master) : GenericRole(master) { }
			static CompositionParentRole Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static CompositionParentRole Create(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			CompositionParentRole CreateInstance(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			CompositionParentRole CreateDerived(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr<CompositionParentRole> Instances() { return Udm::InstantiatedAttr<::Uml::Uml::CompositionParentRole>(impl);}
			template <class Pred> Udm::InstantiatedAttr<CompositionParentRole, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<::Uml::Uml::CompositionParentRole, Pred>(impl);}

			Udm::DerivedAttr<::Uml::Uml::CompositionParentRole> Derived() { return Udm::DerivedAttr<::Uml::Uml::CompositionParentRole>(impl);}
			template <class Pred> Udm::DerivedAttr<::Uml::Uml::CompositionParentRole, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<::Uml::Uml::CompositionParentRole, Pred>(impl);}

			Udm::ArchetypeAttr<::Uml::Uml::CompositionParentRole> Archetype() { return Udm::ArchetypeAttr<::Uml::Uml::CompositionParentRole>(impl);}

			static ::Uml::Uml::AssociationRole meta_target;
			Udm::PointerAttr<::Uml::Uml::Class> target() const { return Udm::PointerAttr<::Uml::Uml::Class>(impl, meta_target); }

			static ::Uml::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr<::Uml::Uml::Composition> parent() const { return Udm::ParentAttr<::Uml::Uml::Composition>(impl, meta_parent); }

		};
		class UDM_DLL CompositionChildRole :  public GenericRole {
		public:
			static ::Uml::Uml::Class meta;

			CompositionChildRole() { }
			CompositionChildRole(Udm::ObjectImpl *impl) : GenericRole(impl) { }
			CompositionChildRole(const CompositionChildRole &master) : GenericRole(master) { }
			static CompositionChildRole Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static CompositionChildRole Create(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			CompositionChildRole CreateInstance(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			CompositionChildRole CreateDerived(const Udm::Object &parent, const ::Uml::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr<CompositionChildRole> Instances() { return Udm::InstantiatedAttr<::Uml::Uml::CompositionChildRole>(impl);}
			template <class Pred> Udm::InstantiatedAttr<CompositionChildRole, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<::Uml::Uml::CompositionChildRole, Pred>(impl);}

			Udm::DerivedAttr<::Uml::Uml::CompositionChildRole> Derived() { return Udm::DerivedAttr<::Uml::Uml::CompositionChildRole>(impl);}
			template <class Pred> Udm::DerivedAttr<::Uml::Uml::CompositionChildRole, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<::Uml::Uml::CompositionChildRole, Pred>(impl);}

			Udm::ArchetypeAttr<::Uml::Uml::CompositionChildRole> Archetype() { return Udm::ArchetypeAttr<::Uml::Uml::CompositionChildRole>(impl);}

			static ::Uml::Uml::Attribute meta_max;
			Udm::IntegerAttr max() const { return Udm::IntegerAttr(impl, meta_max); }

			static ::Uml::Uml::Attribute meta_min;
			Udm::IntegerAttr min() const { return Udm::IntegerAttr(impl, meta_min); }

			static ::Uml::Uml::AssociationRole meta_target;
			Udm::PointerAttr<::Uml::Uml::Class> target() const { return Udm::PointerAttr<::Uml::Uml::Class>(impl, meta_target); }

			static ::Uml::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr<::Uml::Uml::Composition> parent() const { return Udm::ParentAttr<::Uml::Uml::Composition>(impl, meta_parent); }

		};
	}
}

#endif //MOBIES_UML_H
