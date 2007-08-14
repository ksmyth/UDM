#ifndef MOBIES_UML_H
#define MOBIES_UML_H
// header file Uml.h generated from diagram Uml
// generated on Sun Aug 21 10:57:10 2005

#ifndef MOBIES_UDMBASE_H
#include "UdmBase.h"
#endif

#include "Uml_export.h"
namespace Uml {
	extern UDM_DLL Udm::UdmDiagram diagram;
	UDM_DLL void Initialize(const ::Uml::Diagram &dgr);
	UDM_DLL void Initialize();

		class UDM_DLL CompositionChildRole;
		class UDM_DLL Diagram;
		class UDM_DLL CompositionParentRole;
		class UDM_DLL AssociationRole;
		class UDM_DLL Association;
		class UDM_DLL TaggedValue;
		class UDM_DLL Composition;
		class UDM_DLL Namespace;
		class UDM_DLL Class;
		class UDM_DLL Constraint;
		class UDM_DLL GenericRole;
		class UDM_DLL Attribute;
		class UDM_DLL ConstraintDefinition;


		class UDM_DLL Diagram :  public Udm::Object {
		public:
			static ::Uml::Class meta;

			Diagram() { }
			Diagram(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) { }
			Diagram(const Diagram &master) : UDM_OBJECT(master) { }
			static Diagram Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static Diagram Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			Diagram CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			Diagram CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr< ::Uml::Diagram> Instances() { return Udm::InstantiatedAttr< ::Uml::Diagram>(impl);}
			template <class Pred> Udm::InstantiatedAttr< ::Uml::Diagram, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr< ::Uml::Diagram, Pred>(impl);}

			Udm::DerivedAttr< ::Uml::Diagram> Derived() { return Udm::DerivedAttr< ::Uml::Diagram>(impl);}
			template <class Pred> Udm::DerivedAttr< ::Uml::Diagram, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr< ::Uml::Diagram, Pred>(impl);}

			Udm::ArchetypeAttr< ::Uml::Diagram> Archetype() { return Udm::ArchetypeAttr< ::Uml::Diagram>(impl);}

			static ::Uml::Attribute meta_version;
			Udm::StringAttr version() const { return Udm::StringAttr(impl, meta_version); }

			static ::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::CompositionChildRole meta_associations;
			Udm::ChildrenAttr< ::Uml::Association> associations() const { return Udm::ChildrenAttr< ::Uml::Association>(impl, meta_associations); }
			template <class Pred> Udm::ChildrenAttr< ::Uml::Association, Pred> associations_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Association, Pred>(impl, meta_associations); }

			static ::Uml::CompositionChildRole meta_classes;
			Udm::ChildrenAttr< ::Uml::Class> classes() const { return Udm::ChildrenAttr< ::Uml::Class>(impl, meta_classes); }
			template <class Pred> Udm::ChildrenAttr< ::Uml::Class, Pred> classes_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Class, Pred>(impl, meta_classes); }

			static ::Uml::CompositionChildRole meta_compositions;
			Udm::ChildrenAttr< ::Uml::Composition> compositions() const { return Udm::ChildrenAttr< ::Uml::Composition>(impl, meta_compositions); }
			template <class Pred> Udm::ChildrenAttr< ::Uml::Composition, Pred> compositions_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Composition, Pred>(impl, meta_compositions); }

			static ::Uml::CompositionChildRole meta_namespaces;
			Udm::ChildrenAttr< ::Uml::Namespace> namespaces() const { return Udm::ChildrenAttr< ::Uml::Namespace>(impl, meta_namespaces); }
			template <class Pred> Udm::ChildrenAttr< ::Uml::Namespace, Pred> namespaces_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Namespace, Pred>(impl, meta_namespaces); }

			Udm::ChildrenAttr< ::Uml::Association> Association_kind_children() const { return Udm::ChildrenAttr< ::Uml::Association>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::Uml::Association, Pred> Association_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Association, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr< ::Uml::Composition> Composition_kind_children() const { return Udm::ChildrenAttr< ::Uml::Composition>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::Uml::Composition, Pred> Composition_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Composition, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr< ::Uml::Namespace> Namespace_kind_children() const { return Udm::ChildrenAttr< ::Uml::Namespace>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::Uml::Namespace, Pred> Namespace_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Namespace, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr< ::Uml::Class> Class_kind_children() const { return Udm::ChildrenAttr< ::Uml::Class>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::Uml::Class, Pred> Class_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Class, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ParentAttr<Udm::Object> parent() const { return Udm::ParentAttr<Udm::Object>(impl, Udm::NULLPARENTROLE); }
		};

		class UDM_DLL Association :  public Udm::Object {
		public:
			static ::Uml::Class meta;

			Association() { }
			Association(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) { }
			Association(const Association &master) : UDM_OBJECT(master) { }
			static Association Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static Association Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			Association CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			Association CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr< ::Uml::Association> Instances() { return Udm::InstantiatedAttr< ::Uml::Association>(impl);}
			template <class Pred> Udm::InstantiatedAttr< ::Uml::Association, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr< ::Uml::Association, Pred>(impl);}

			Udm::DerivedAttr< ::Uml::Association> Derived() { return Udm::DerivedAttr< ::Uml::Association>(impl);}
			template <class Pred> Udm::DerivedAttr< ::Uml::Association, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr< ::Uml::Association, Pred>(impl);}

			Udm::ArchetypeAttr< ::Uml::Association> Archetype() { return Udm::ArchetypeAttr< ::Uml::Association>(impl);}

			static ::Uml::Attribute meta_nonpersistent;
			Udm::BooleanAttr nonpersistent() const { return Udm::BooleanAttr(impl, meta_nonpersistent); }

			static ::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::AssociationRole meta_assocClass;
			Udm::PointerAttr< ::Uml::Class> assocClass() const { return Udm::PointerAttr< ::Uml::Class>(impl, meta_assocClass); }

			static ::Uml::CompositionChildRole meta_tagValues;
			Udm::ChildrenAttr< ::Uml::TaggedValue> tagValues() const { return Udm::ChildrenAttr< ::Uml::TaggedValue>(impl, meta_tagValues); }
			template <class Pred> Udm::ChildrenAttr< ::Uml::TaggedValue, Pred> tagValues_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::TaggedValue, Pred>(impl, meta_tagValues); }

			static ::Uml::CompositionChildRole meta_roles;
			Udm::ChildrenAttr< ::Uml::AssociationRole> roles() const { return Udm::ChildrenAttr< ::Uml::AssociationRole>(impl, meta_roles); }
			template <class Pred> Udm::ChildrenAttr< ::Uml::AssociationRole, Pred> roles_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::AssociationRole, Pred>(impl, meta_roles); }

			Udm::ChildrenAttr< ::Uml::AssociationRole> AssociationRole_kind_children() const { return Udm::ChildrenAttr< ::Uml::AssociationRole>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::Uml::AssociationRole, Pred> AssociationRole_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::AssociationRole, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr< ::Uml::TaggedValue> TaggedValue_kind_children() const { return Udm::ChildrenAttr< ::Uml::TaggedValue>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::Uml::TaggedValue, Pred> TaggedValue_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::TaggedValue, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr< ::Uml::GenericRole> GenericRole_kind_children() const { return Udm::ChildrenAttr< ::Uml::GenericRole>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::Uml::GenericRole, Pred> GenericRole_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::GenericRole, Pred>(impl, Udm::NULLCHILDROLE); }

			static ::Uml::CompositionParentRole meta_parent_ns;
			Udm::ParentAttr< ::Uml::Namespace> parent_ns() const { return Udm::ParentAttr< ::Uml::Namespace>(impl, meta_parent_ns); }

			static ::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr< ::Uml::Diagram> parent() const { return Udm::ParentAttr< ::Uml::Diagram>(impl, meta_parent); }

		};

		class UDM_DLL TaggedValue :  public Udm::Object {
		public:
			static ::Uml::Class meta;

			TaggedValue() { }
			TaggedValue(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) { }
			TaggedValue(const TaggedValue &master) : UDM_OBJECT(master) { }
			static TaggedValue Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static TaggedValue Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			TaggedValue CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			TaggedValue CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr< ::Uml::TaggedValue> Instances() { return Udm::InstantiatedAttr< ::Uml::TaggedValue>(impl);}
			template <class Pred> Udm::InstantiatedAttr< ::Uml::TaggedValue, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr< ::Uml::TaggedValue, Pred>(impl);}

			Udm::DerivedAttr< ::Uml::TaggedValue> Derived() { return Udm::DerivedAttr< ::Uml::TaggedValue>(impl);}
			template <class Pred> Udm::DerivedAttr< ::Uml::TaggedValue, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr< ::Uml::TaggedValue, Pred>(impl);}

			Udm::ArchetypeAttr< ::Uml::TaggedValue> Archetype() { return Udm::ArchetypeAttr< ::Uml::TaggedValue>(impl);}

			static ::Uml::Attribute meta_value;
			Udm::StringAttr value() const { return Udm::StringAttr(impl, meta_value); }

			static ::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::CompositionParentRole meta_classParent;
			Udm::ParentAttr< ::Uml::Class> classParent() const { return Udm::ParentAttr< ::Uml::Class>(impl, meta_classParent); }

			static ::Uml::CompositionParentRole meta_assocParent;
			Udm::ParentAttr< ::Uml::Association> assocParent() const { return Udm::ParentAttr< ::Uml::Association>(impl, meta_assocParent); }

			Udm::ParentAttr<Udm::Object> parent() const { return Udm::ParentAttr<Udm::Object>(impl, Udm::NULLPARENTROLE); }
		};

		class UDM_DLL Composition :  public Udm::Object {
		public:
			static ::Uml::Class meta;

			Composition() { }
			Composition(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) { }
			Composition(const Composition &master) : UDM_OBJECT(master) { }
			static Composition Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static Composition Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			Composition CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			Composition CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr< ::Uml::Composition> Instances() { return Udm::InstantiatedAttr< ::Uml::Composition>(impl);}
			template <class Pred> Udm::InstantiatedAttr< ::Uml::Composition, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr< ::Uml::Composition, Pred>(impl);}

			Udm::DerivedAttr< ::Uml::Composition> Derived() { return Udm::DerivedAttr< ::Uml::Composition>(impl);}
			template <class Pred> Udm::DerivedAttr< ::Uml::Composition, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr< ::Uml::Composition, Pred>(impl);}

			Udm::ArchetypeAttr< ::Uml::Composition> Archetype() { return Udm::ArchetypeAttr< ::Uml::Composition>(impl);}

			static ::Uml::Attribute meta_nonpersistent;
			Udm::BooleanAttr nonpersistent() const { return Udm::BooleanAttr(impl, meta_nonpersistent); }

			static ::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::CompositionChildRole meta_childRole;
			Udm::ChildAttr< ::Uml::CompositionChildRole> childRole() const { return Udm::ChildAttr< ::Uml::CompositionChildRole>(impl, meta_childRole); }

			static ::Uml::CompositionChildRole meta_parentRole;
			Udm::ChildAttr< ::Uml::CompositionParentRole> parentRole() const { return Udm::ChildAttr< ::Uml::CompositionParentRole>(impl, meta_parentRole); }

			Udm::ChildrenAttr< ::Uml::CompositionChildRole> CompositionChildRole_kind_children() const { return Udm::ChildrenAttr< ::Uml::CompositionChildRole>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::Uml::CompositionChildRole, Pred> CompositionChildRole_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::CompositionChildRole, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr< ::Uml::CompositionParentRole> CompositionParentRole_kind_children() const { return Udm::ChildrenAttr< ::Uml::CompositionParentRole>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::Uml::CompositionParentRole, Pred> CompositionParentRole_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::CompositionParentRole, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr< ::Uml::GenericRole> GenericRole_kind_children() const { return Udm::ChildrenAttr< ::Uml::GenericRole>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::Uml::GenericRole, Pred> GenericRole_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::GenericRole, Pred>(impl, Udm::NULLCHILDROLE); }

			static ::Uml::CompositionParentRole meta_parent_ns;
			Udm::ParentAttr< ::Uml::Namespace> parent_ns() const { return Udm::ParentAttr< ::Uml::Namespace>(impl, meta_parent_ns); }

			static ::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr< ::Uml::Diagram> parent() const { return Udm::ParentAttr< ::Uml::Diagram>(impl, meta_parent); }

		};

		class UDM_DLL Namespace :  public Udm::Object {
		public:
			static ::Uml::Class meta;

			Namespace() { }
			Namespace(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) { }
			Namespace(const Namespace &master) : UDM_OBJECT(master) { }
			static Namespace Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static Namespace Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			Namespace CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			Namespace CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr< ::Uml::Namespace> Instances() { return Udm::InstantiatedAttr< ::Uml::Namespace>(impl);}
			template <class Pred> Udm::InstantiatedAttr< ::Uml::Namespace, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr< ::Uml::Namespace, Pred>(impl);}

			Udm::DerivedAttr< ::Uml::Namespace> Derived() { return Udm::DerivedAttr< ::Uml::Namespace>(impl);}
			template <class Pred> Udm::DerivedAttr< ::Uml::Namespace, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr< ::Uml::Namespace, Pred>(impl);}

			Udm::ArchetypeAttr< ::Uml::Namespace> Archetype() { return Udm::ArchetypeAttr< ::Uml::Namespace>(impl);}

			static ::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::CompositionChildRole meta_compositions;
			Udm::ChildrenAttr< ::Uml::Composition> compositions() const { return Udm::ChildrenAttr< ::Uml::Composition>(impl, meta_compositions); }
			template <class Pred> Udm::ChildrenAttr< ::Uml::Composition, Pred> compositions_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Composition, Pred>(impl, meta_compositions); }

			static ::Uml::CompositionChildRole meta_classes;
			Udm::ChildrenAttr< ::Uml::Class> classes() const { return Udm::ChildrenAttr< ::Uml::Class>(impl, meta_classes); }
			template <class Pred> Udm::ChildrenAttr< ::Uml::Class, Pred> classes_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Class, Pred>(impl, meta_classes); }

			static ::Uml::CompositionChildRole meta_associations;
			Udm::ChildrenAttr< ::Uml::Association> associations() const { return Udm::ChildrenAttr< ::Uml::Association>(impl, meta_associations); }
			template <class Pred> Udm::ChildrenAttr< ::Uml::Association, Pred> associations_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Association, Pred>(impl, meta_associations); }

			Udm::ChildrenAttr< ::Uml::Association> Association_kind_children() const { return Udm::ChildrenAttr< ::Uml::Association>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::Uml::Association, Pred> Association_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Association, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr< ::Uml::Composition> Composition_kind_children() const { return Udm::ChildrenAttr< ::Uml::Composition>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::Uml::Composition, Pred> Composition_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Composition, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr< ::Uml::Class> Class_kind_children() const { return Udm::ChildrenAttr< ::Uml::Class>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::Uml::Class, Pred> Class_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Class, Pred>(impl, Udm::NULLCHILDROLE); }

			static ::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr< ::Uml::Diagram> parent() const { return Udm::ParentAttr< ::Uml::Diagram>(impl, meta_parent); }

		};

		class UDM_DLL Class :  public Udm::Object {
		public:
			static ::Uml::Class meta;

			Class() { }
			Class(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) { }
			Class(const Class &master) : UDM_OBJECT(master) { }
			static Class Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static Class Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			Class CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			Class CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr< ::Uml::Class> Instances() { return Udm::InstantiatedAttr< ::Uml::Class>(impl);}
			template <class Pred> Udm::InstantiatedAttr< ::Uml::Class, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr< ::Uml::Class, Pred>(impl);}

			Udm::DerivedAttr< ::Uml::Class> Derived() { return Udm::DerivedAttr< ::Uml::Class>(impl);}
			template <class Pred> Udm::DerivedAttr< ::Uml::Class, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr< ::Uml::Class, Pred>(impl);}

			Udm::ArchetypeAttr< ::Uml::Class> Archetype() { return Udm::ArchetypeAttr< ::Uml::Class>(impl);}

			static ::Uml::Attribute meta_isAbstract;
			Udm::BooleanAttr isAbstract() const { return Udm::BooleanAttr(impl, meta_isAbstract); }

			static ::Uml::Attribute meta_stereotype;
			Udm::StringAttr stereotype() const { return Udm::StringAttr(impl, meta_stereotype); }

			static ::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::Attribute meta_from;
			Udm::StringAttr from() const { return Udm::StringAttr(impl, meta_from); }

			static ::Uml::AssociationRole meta_childRoles;
			Udm::AssocAttr< ::Uml::CompositionChildRole> childRoles() const { return Udm::AssocAttr< ::Uml::CompositionChildRole>(impl, meta_childRoles); }
			template <class Pred> Udm::AssocAttr< ::Uml::CompositionChildRole, Pred > childRoles_sorted(const Pred &) const { return Udm::AssocAttr< ::Uml::CompositionChildRole, Pred>(impl, meta_childRoles); }

			static ::Uml::AssociationRole meta_parentRoles;
			Udm::AssocAttr< ::Uml::CompositionParentRole> parentRoles() const { return Udm::AssocAttr< ::Uml::CompositionParentRole>(impl, meta_parentRoles); }
			template <class Pred> Udm::AssocAttr< ::Uml::CompositionParentRole, Pred > parentRoles_sorted(const Pred &) const { return Udm::AssocAttr< ::Uml::CompositionParentRole, Pred>(impl, meta_parentRoles); }

			static ::Uml::AssociationRole meta_associationRoles;
			Udm::AssocAttr< ::Uml::AssociationRole> associationRoles() const { return Udm::AssocAttr< ::Uml::AssociationRole>(impl, meta_associationRoles); }
			template <class Pred> Udm::AssocAttr< ::Uml::AssociationRole, Pred > associationRoles_sorted(const Pred &) const { return Udm::AssocAttr< ::Uml::AssociationRole, Pred>(impl, meta_associationRoles); }

			static ::Uml::AssociationRole meta_association;
			Udm::PointerAttr< ::Uml::Association> association() const { return Udm::PointerAttr< ::Uml::Association>(impl, meta_association); }

			static ::Uml::AssociationRole meta_baseTypes;
			Udm::AssocAttr< ::Uml::Class> baseTypes() const { return Udm::AssocAttr< ::Uml::Class>(impl, meta_baseTypes); }
			template <class Pred> Udm::AssocAttr< ::Uml::Class, Pred > baseTypes_sorted(const Pred &) const { return Udm::AssocAttr< ::Uml::Class, Pred>(impl, meta_baseTypes); }

			static ::Uml::AssociationRole meta_subTypes;
			Udm::AssocAttr< ::Uml::Class> subTypes() const { return Udm::AssocAttr< ::Uml::Class>(impl, meta_subTypes); }
			template <class Pred> Udm::AssocAttr< ::Uml::Class, Pred > subTypes_sorted(const Pred &) const { return Udm::AssocAttr< ::Uml::Class, Pred>(impl, meta_subTypes); }

			static ::Uml::CompositionChildRole meta_attributes;
			Udm::ChildrenAttr< ::Uml::Attribute> attributes() const { return Udm::ChildrenAttr< ::Uml::Attribute>(impl, meta_attributes); }
			template <class Pred> Udm::ChildrenAttr< ::Uml::Attribute, Pred> attributes_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Attribute, Pred>(impl, meta_attributes); }

			static ::Uml::CompositionChildRole meta_definitions;
			Udm::ChildrenAttr< ::Uml::ConstraintDefinition> definitions() const { return Udm::ChildrenAttr< ::Uml::ConstraintDefinition>(impl, meta_definitions); }
			template <class Pred> Udm::ChildrenAttr< ::Uml::ConstraintDefinition, Pred> definitions_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::ConstraintDefinition, Pred>(impl, meta_definitions); }

			static ::Uml::CompositionChildRole meta_constraints;
			Udm::ChildrenAttr< ::Uml::Constraint> constraints() const { return Udm::ChildrenAttr< ::Uml::Constraint>(impl, meta_constraints); }
			template <class Pred> Udm::ChildrenAttr< ::Uml::Constraint, Pred> constraints_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Constraint, Pred>(impl, meta_constraints); }

			static ::Uml::CompositionChildRole meta_tagValues;
			Udm::ChildrenAttr< ::Uml::TaggedValue> tagValues() const { return Udm::ChildrenAttr< ::Uml::TaggedValue>(impl, meta_tagValues); }
			template <class Pred> Udm::ChildrenAttr< ::Uml::TaggedValue, Pred> tagValues_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::TaggedValue, Pred>(impl, meta_tagValues); }

			Udm::ChildrenAttr< ::Uml::TaggedValue> TaggedValue_kind_children() const { return Udm::ChildrenAttr< ::Uml::TaggedValue>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::Uml::TaggedValue, Pred> TaggedValue_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::TaggedValue, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr< ::Uml::Constraint> Constraint_kind_children() const { return Udm::ChildrenAttr< ::Uml::Constraint>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::Uml::Constraint, Pred> Constraint_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Constraint, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr< ::Uml::Attribute> Attribute_kind_children() const { return Udm::ChildrenAttr< ::Uml::Attribute>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::Uml::Attribute, Pred> Attribute_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::Attribute, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ChildrenAttr< ::Uml::ConstraintDefinition> ConstraintDefinition_kind_children() const { return Udm::ChildrenAttr< ::Uml::ConstraintDefinition>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::Uml::ConstraintDefinition, Pred> ConstraintDefinition_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::Uml::ConstraintDefinition, Pred>(impl, Udm::NULLCHILDROLE); }

			static ::Uml::CompositionParentRole meta_parent_ns;
			Udm::ParentAttr< ::Uml::Namespace> parent_ns() const { return Udm::ParentAttr< ::Uml::Namespace>(impl, meta_parent_ns); }

			static ::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr< ::Uml::Diagram> parent() const { return Udm::ParentAttr< ::Uml::Diagram>(impl, meta_parent); }

		};

		class UDM_DLL Constraint :  public Udm::Object {
		public:
			static ::Uml::Class meta;

			Constraint() { }
			Constraint(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) { }
			Constraint(const Constraint &master) : UDM_OBJECT(master) { }
			static Constraint Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static Constraint Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			Constraint CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			Constraint CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr< ::Uml::Constraint> Instances() { return Udm::InstantiatedAttr< ::Uml::Constraint>(impl);}
			template <class Pred> Udm::InstantiatedAttr< ::Uml::Constraint, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr< ::Uml::Constraint, Pred>(impl);}

			Udm::DerivedAttr< ::Uml::Constraint> Derived() { return Udm::DerivedAttr< ::Uml::Constraint>(impl);}
			template <class Pred> Udm::DerivedAttr< ::Uml::Constraint, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr< ::Uml::Constraint, Pred>(impl);}

			Udm::ArchetypeAttr< ::Uml::Constraint> Archetype() { return Udm::ArchetypeAttr< ::Uml::Constraint>(impl);}

			static ::Uml::Attribute meta_description;
			Udm::StringAttr description() const { return Udm::StringAttr(impl, meta_description); }

			static ::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::Attribute meta_expression;
			Udm::StringAttr expression() const { return Udm::StringAttr(impl, meta_expression); }

			static ::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr< ::Uml::Class> parent() const { return Udm::ParentAttr< ::Uml::Class>(impl, meta_parent); }

		};

		class UDM_DLL GenericRole :  public Udm::Object {
		public:
			static ::Uml::Class meta;

			GenericRole() { }
			GenericRole(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) { }
			GenericRole(const GenericRole &master) : UDM_OBJECT(master) { }
			static GenericRole Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static GenericRole Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			GenericRole CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			GenericRole CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr< ::Uml::GenericRole> Instances() { return Udm::InstantiatedAttr< ::Uml::GenericRole>(impl);}
			template <class Pred> Udm::InstantiatedAttr< ::Uml::GenericRole, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr< ::Uml::GenericRole, Pred>(impl);}

			Udm::DerivedAttr< ::Uml::GenericRole> Derived() { return Udm::DerivedAttr< ::Uml::GenericRole>(impl);}
			template <class Pred> Udm::DerivedAttr< ::Uml::GenericRole, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr< ::Uml::GenericRole, Pred>(impl);}

			Udm::ArchetypeAttr< ::Uml::GenericRole> Archetype() { return Udm::ArchetypeAttr< ::Uml::GenericRole>(impl);}

			static ::Uml::Attribute meta_isNavigable;
			Udm::BooleanAttr isNavigable() const { return Udm::BooleanAttr(impl, meta_isNavigable); }

			static ::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			Udm::ParentAttr<Udm::Object> parent() const { return Udm::ParentAttr<Udm::Object>(impl, Udm::NULLPARENTROLE); }
		};

		class UDM_DLL CompositionChildRole :  public ::Uml::GenericRole {
		public:
			static ::Uml::Class meta;

			CompositionChildRole() { }
			CompositionChildRole(Udm::ObjectImpl *impl) : ::Uml::GenericRole(impl) { }
			CompositionChildRole(const CompositionChildRole &master) : ::Uml::GenericRole(master) { }
			static CompositionChildRole Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static CompositionChildRole Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			CompositionChildRole CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			CompositionChildRole CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr< ::Uml::CompositionChildRole> Instances() { return Udm::InstantiatedAttr< ::Uml::CompositionChildRole>(impl);}
			template <class Pred> Udm::InstantiatedAttr< ::Uml::CompositionChildRole, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr< ::Uml::CompositionChildRole, Pred>(impl);}

			Udm::DerivedAttr< ::Uml::CompositionChildRole> Derived() { return Udm::DerivedAttr< ::Uml::CompositionChildRole>(impl);}
			template <class Pred> Udm::DerivedAttr< ::Uml::CompositionChildRole, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr< ::Uml::CompositionChildRole, Pred>(impl);}

			Udm::ArchetypeAttr< ::Uml::CompositionChildRole> Archetype() { return Udm::ArchetypeAttr< ::Uml::CompositionChildRole>(impl);}

			static ::Uml::Attribute meta_max;
			Udm::IntegerAttr max() const { return Udm::IntegerAttr(impl, meta_max); }

			static ::Uml::Attribute meta_min;
			Udm::IntegerAttr min() const { return Udm::IntegerAttr(impl, meta_min); }

			static ::Uml::AssociationRole meta_target;
			Udm::PointerAttr< ::Uml::Class> target() const { return Udm::PointerAttr< ::Uml::Class>(impl, meta_target); }

			static ::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr< ::Uml::Composition> parent() const { return Udm::ParentAttr< ::Uml::Composition>(impl, meta_parent); }

		};

		class UDM_DLL CompositionParentRole :  public ::Uml::GenericRole {
		public:
			static ::Uml::Class meta;

			CompositionParentRole() { }
			CompositionParentRole(Udm::ObjectImpl *impl) : ::Uml::GenericRole(impl) { }
			CompositionParentRole(const CompositionParentRole &master) : ::Uml::GenericRole(master) { }
			static CompositionParentRole Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static CompositionParentRole Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			CompositionParentRole CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			CompositionParentRole CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr< ::Uml::CompositionParentRole> Instances() { return Udm::InstantiatedAttr< ::Uml::CompositionParentRole>(impl);}
			template <class Pred> Udm::InstantiatedAttr< ::Uml::CompositionParentRole, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr< ::Uml::CompositionParentRole, Pred>(impl);}

			Udm::DerivedAttr< ::Uml::CompositionParentRole> Derived() { return Udm::DerivedAttr< ::Uml::CompositionParentRole>(impl);}
			template <class Pred> Udm::DerivedAttr< ::Uml::CompositionParentRole, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr< ::Uml::CompositionParentRole, Pred>(impl);}

			Udm::ArchetypeAttr< ::Uml::CompositionParentRole> Archetype() { return Udm::ArchetypeAttr< ::Uml::CompositionParentRole>(impl);}

			static ::Uml::AssociationRole meta_target;
			Udm::PointerAttr< ::Uml::Class> target() const { return Udm::PointerAttr< ::Uml::Class>(impl, meta_target); }

			static ::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr< ::Uml::Composition> parent() const { return Udm::ParentAttr< ::Uml::Composition>(impl, meta_parent); }

		};

		class UDM_DLL AssociationRole :  public ::Uml::GenericRole {
		public:
			static ::Uml::Class meta;

			AssociationRole() { }
			AssociationRole(Udm::ObjectImpl *impl) : ::Uml::GenericRole(impl) { }
			AssociationRole(const AssociationRole &master) : ::Uml::GenericRole(master) { }
			static AssociationRole Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static AssociationRole Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			AssociationRole CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			AssociationRole CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr< ::Uml::AssociationRole> Instances() { return Udm::InstantiatedAttr< ::Uml::AssociationRole>(impl);}
			template <class Pred> Udm::InstantiatedAttr< ::Uml::AssociationRole, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr< ::Uml::AssociationRole, Pred>(impl);}

			Udm::DerivedAttr< ::Uml::AssociationRole> Derived() { return Udm::DerivedAttr< ::Uml::AssociationRole>(impl);}
			template <class Pred> Udm::DerivedAttr< ::Uml::AssociationRole, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr< ::Uml::AssociationRole, Pred>(impl);}

			Udm::ArchetypeAttr< ::Uml::AssociationRole> Archetype() { return Udm::ArchetypeAttr< ::Uml::AssociationRole>(impl);}

			static ::Uml::Attribute meta_max;
			Udm::IntegerAttr max() const { return Udm::IntegerAttr(impl, meta_max); }

			static ::Uml::Attribute meta_min;
			Udm::IntegerAttr min() const { return Udm::IntegerAttr(impl, meta_min); }

			static ::Uml::Attribute meta_isPrimary;
			Udm::BooleanAttr isPrimary() const { return Udm::BooleanAttr(impl, meta_isPrimary); }

			static ::Uml::AssociationRole meta_target;
			Udm::PointerAttr< ::Uml::Class> target() const { return Udm::PointerAttr< ::Uml::Class>(impl, meta_target); }

			static ::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr< ::Uml::Association> parent() const { return Udm::ParentAttr< ::Uml::Association>(impl, meta_parent); }

		};

		class UDM_DLL Attribute :  public Udm::Object {
		public:
			static ::Uml::Class meta;

			Attribute() { }
			Attribute(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) { }
			Attribute(const Attribute &master) : UDM_OBJECT(master) { }
			static Attribute Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static Attribute Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			Attribute CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			Attribute CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr< ::Uml::Attribute> Instances() { return Udm::InstantiatedAttr< ::Uml::Attribute>(impl);}
			template <class Pred> Udm::InstantiatedAttr< ::Uml::Attribute, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr< ::Uml::Attribute, Pred>(impl);}

			Udm::DerivedAttr< ::Uml::Attribute> Derived() { return Udm::DerivedAttr< ::Uml::Attribute>(impl);}
			template <class Pred> Udm::DerivedAttr< ::Uml::Attribute, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr< ::Uml::Attribute, Pred>(impl);}

			Udm::ArchetypeAttr< ::Uml::Attribute> Archetype() { return Udm::ArchetypeAttr< ::Uml::Attribute>(impl);}

			static ::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::Attribute meta_type;
			Udm::StringAttr type() const { return Udm::StringAttr(impl, meta_type); }

			static ::Uml::Attribute meta_defvalue;
			Udm::StringAttrArr defvalue() const { return Udm::StringAttrArr(impl, meta_defvalue); }

			static ::Uml::Attribute meta_min;
			Udm::IntegerAttr min() const { return Udm::IntegerAttr(impl, meta_min); }

			static ::Uml::Attribute meta_max;
			Udm::IntegerAttr max() const { return Udm::IntegerAttr(impl, meta_max); }

			static ::Uml::Attribute meta_visibility;
			Udm::StringAttr visibility() const { return Udm::StringAttr(impl, meta_visibility); }

			static ::Uml::Attribute meta_ordered;
			Udm::BooleanAttr ordered() const { return Udm::BooleanAttr(impl, meta_ordered); }

			static ::Uml::Attribute meta_nonpersistent;
			Udm::BooleanAttr nonpersistent() const { return Udm::BooleanAttr(impl, meta_nonpersistent); }

			static ::Uml::Attribute meta_registry;
			Udm::BooleanAttr registry() const { return Udm::BooleanAttr(impl, meta_registry); }

			static ::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr< ::Uml::Class> parent() const { return Udm::ParentAttr< ::Uml::Class>(impl, meta_parent); }

		};

		class UDM_DLL ConstraintDefinition :  public Udm::Object {
		public:
			static ::Uml::Class meta;

			ConstraintDefinition() { }
			ConstraintDefinition(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) { }
			ConstraintDefinition(const ConstraintDefinition &master) : UDM_OBJECT(master) { }
			static ConstraintDefinition Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static ConstraintDefinition Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			ConstraintDefinition CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			ConstraintDefinition CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr< ::Uml::ConstraintDefinition> Instances() { return Udm::InstantiatedAttr< ::Uml::ConstraintDefinition>(impl);}
			template <class Pred> Udm::InstantiatedAttr< ::Uml::ConstraintDefinition, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr< ::Uml::ConstraintDefinition, Pred>(impl);}

			Udm::DerivedAttr< ::Uml::ConstraintDefinition> Derived() { return Udm::DerivedAttr< ::Uml::ConstraintDefinition>(impl);}
			template <class Pred> Udm::DerivedAttr< ::Uml::ConstraintDefinition, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr< ::Uml::ConstraintDefinition, Pred>(impl);}

			Udm::ArchetypeAttr< ::Uml::ConstraintDefinition> Archetype() { return Udm::ArchetypeAttr< ::Uml::ConstraintDefinition>(impl);}

			static ::Uml::Attribute meta_stereotype;
			Udm::StringAttr stereotype() const { return Udm::StringAttr(impl, meta_stereotype); }

			static ::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::Attribute meta_parameterList;
			Udm::StringAttr parameterList() const { return Udm::StringAttr(impl, meta_parameterList); }

			static ::Uml::Attribute meta_expression;
			Udm::StringAttr expression() const { return Udm::StringAttr(impl, meta_expression); }

			static ::Uml::Attribute meta_returnType;
			Udm::StringAttr returnType() const { return Udm::StringAttr(impl, meta_returnType); }

			static ::Uml::CompositionParentRole meta_parent;
			Udm::ParentAttr< ::Uml::Class> parent() const { return Udm::ParentAttr< ::Uml::Class>(impl, meta_parent); }

		};



}

#endif //MOBIES_UML_H
