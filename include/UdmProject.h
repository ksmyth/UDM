#ifndef MOBIES_UDMPROJECT_H
#define MOBIES_UDMPROJECT_H

// header file UdmProject.h generated from diagram UdmProject
// generated with Udm version 3.27 on Mon May 02 10:02:17 2011

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

namespace UdmProject {

	extern ::Uml::Diagram meta;
	class Datanetwork;
	class Project;

	void Initialize();

	extern Udm::UdmDiagram diagram;

	class Datanetwork : public Udm::Object {
	public:
		Datanetwork() {}
		Datanetwork(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) {}
		Datanetwork(const Datanetwork &master) : UDM_OBJECT(master) {}
		#ifdef UDM_RVALUE
		Datanetwork(Datanetwork &&master) : UDM_OBJECT(master) {}

		static Datanetwork Cast(Udm::Object &&a) { return __Cast(std::move(a), meta); }
		Datanetwork& operator=(Datanetwork &&a) { Udm::Object::operator =(std::move(a)); return *this; }
		#endif
		static Datanetwork Cast(const Udm::Object &a) { return __Cast(a, meta); }
		static Datanetwork Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }
		Datanetwork CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::InstantiatedAttr<Datanetwork> Instances() { return Udm::InstantiatedAttr<Datanetwork>(impl); }
		template <class Pred> Udm::InstantiatedAttr<Datanetwork, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<Datanetwork, Pred>(impl); }
		Datanetwork CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }
		Udm::DerivedAttr<Datanetwork> Derived() { return Udm::DerivedAttr<Datanetwork>(impl); }
		template <class Pred> Udm::DerivedAttr<Datanetwork, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<Datanetwork, Pred>(impl); }
		Udm::ArchetypeAttr<Datanetwork> Archetype() const { return Udm::ArchetypeAttr<Datanetwork>(impl); }
		Udm::StringAttr metaDgr() const { return Udm::StringAttr(impl, meta_metaDgr); }
		Udm::StringAttr systemname() const { return Udm::StringAttr(impl, meta_systemname); }
		Udm::StringAttr metalocator() const { return Udm::StringAttr(impl, meta_metalocator); }
		Udm::ParentAttr< ::UdmProject::Project> cross_associations_Project_parent() const { return Udm::ParentAttr< ::UdmProject::Project>(impl, meta_cross_associations_Project_parent); }
		Udm::ParentAttr< ::UdmProject::Project> instances_Project_parent() const { return Udm::ParentAttr< ::UdmProject::Project>(impl, meta_instances_Project_parent); }
		Udm::ParentAttr< ::UdmProject::Project> crosslinks_Project_parent() const { return Udm::ParentAttr< ::UdmProject::Project>(impl, meta_crosslinks_Project_parent); }
		Udm::ParentAttr< ::UdmProject::Project> parent() const { return Udm::ParentAttr< ::UdmProject::Project>(impl, Udm::NULLPARENTROLE); }

		static ::Uml::Class meta;
		static ::Uml::Attribute meta_metaDgr;
		static ::Uml::Attribute meta_systemname;
		static ::Uml::Attribute meta_metalocator;
		static ::Uml::CompositionParentRole meta_cross_associations_Project_parent;
		static ::Uml::CompositionParentRole meta_instances_Project_parent;
		static ::Uml::CompositionParentRole meta_crosslinks_Project_parent;

	};

	class Project : public Udm::Object {
	public:
		Project() {}
		Project(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) {}
		Project(const Project &master) : UDM_OBJECT(master) {}
		#ifdef UDM_RVALUE
		Project(Project &&master) : UDM_OBJECT(master) {}

		static Project Cast(Udm::Object &&a) { return __Cast(std::move(a), meta); }
		Project& operator=(Project &&a) { Udm::Object::operator =(std::move(a)); return *this; }
		#endif
		static Project Cast(const Udm::Object &a) { return __Cast(a, meta); }
		static Project Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }
		Project CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }
		Udm::InstantiatedAttr<Project> Instances() { return Udm::InstantiatedAttr<Project>(impl); }
		template <class Pred> Udm::InstantiatedAttr<Project, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr<Project, Pred>(impl); }
		Project CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }
		Udm::DerivedAttr<Project> Derived() { return Udm::DerivedAttr<Project>(impl); }
		template <class Pred> Udm::DerivedAttr<Project, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr<Project, Pred>(impl); }
		Udm::ArchetypeAttr<Project> Archetype() const { return Udm::ArchetypeAttr<Project>(impl); }
		Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }
		Udm::ChildAttr< ::UdmProject::Datanetwork> cross_associations() const { return Udm::ChildAttr< ::UdmProject::Datanetwork>(impl, meta_cross_associations); }
		Udm::ChildrenAttr< ::UdmProject::Datanetwork> instances() const { return Udm::ChildrenAttr< ::UdmProject::Datanetwork>(impl, meta_instances); }
		template <class Pred> Udm::ChildrenAttr< ::UdmProject::Datanetwork, Pred> instances_sorted(const Pred &) const { return Udm::ChildrenAttr< ::UdmProject::Datanetwork, Pred>(impl, meta_instances); }
		Udm::ChildAttr< ::UdmProject::Datanetwork> crosslinks() const { return Udm::ChildAttr< ::UdmProject::Datanetwork>(impl, meta_crosslinks); }
		Udm::ChildrenAttr< ::UdmProject::Datanetwork> Datanetwork_kind_children() const { return Udm::ChildrenAttr< ::UdmProject::Datanetwork>(impl, Udm::NULLCHILDROLE); }
		template <class Pred> Udm::ChildrenAttr< ::UdmProject::Datanetwork, Pred> Datanetwork_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::UdmProject::Datanetwork, Pred>(impl, Udm::NULLCHILDROLE); }
		Udm::ParentAttr<Udm::Object> parent() const { return Udm::ParentAttr<Udm::Object>(impl, Udm::NULLPARENTROLE); }

		static ::Uml::Class meta;
		static ::Uml::Attribute meta_name;
		static ::Uml::CompositionChildRole meta_cross_associations;
		static ::Uml::CompositionChildRole meta_instances;
		static ::Uml::CompositionChildRole meta_crosslinks;

	};

}

#endif // MOBIES_UDMPROJECT_H
