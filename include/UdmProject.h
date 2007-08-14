#ifndef MOBIES_UDMPROJECT_H
#define MOBIES_UDMPROJECT_H
// header file UdmProject.h generated from diagram UdmProject
// generated on Mon Jul 02 21:02:22 2007

#ifndef MOBIES_UDMBASE_H
#include "UdmBase.h"
#endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif
namespace UdmProject {
	extern  Udm::UdmDiagram diagram;
	 void Initialize(const ::Uml::Diagram &dgr);
	 void Initialize();

		class  Project;
		class  Datanetwork;


		 void CreateMetaObjs();
		 void InitCrossNSInheritence();
		 void InitCrossNSCompositions();
		 void InitCrossNSAssociations();
		class  Project :  public Udm::Object {
		public:
			static ::Uml::Class meta;

			Project() { }
			Project(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) { }
			Project(const Project &master) : UDM_OBJECT(master) { }
			static Project Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static Project Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			Project CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			Project CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr< ::UdmProject::Project> Instances() { return Udm::InstantiatedAttr< ::UdmProject::Project>(impl);}
			template <class Pred> Udm::InstantiatedAttr< ::UdmProject::Project, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr< ::UdmProject::Project, Pred>(impl);}

			Udm::DerivedAttr< ::UdmProject::Project> Derived() { return Udm::DerivedAttr< ::UdmProject::Project>(impl);}
			template <class Pred> Udm::DerivedAttr< ::UdmProject::Project, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr< ::UdmProject::Project, Pred>(impl);}

			Udm::ArchetypeAttr< ::UdmProject::Project> Archetype() const { return Udm::ArchetypeAttr< ::UdmProject::Project>(impl);}

			static ::Uml::Attribute meta_name;
			Udm::StringAttr name() const { return Udm::StringAttr(impl, meta_name); }

			static ::Uml::CompositionChildRole meta_instances;
			Udm::ChildrenAttr< ::UdmProject::Datanetwork> instances() const { return Udm::ChildrenAttr< ::UdmProject::Datanetwork>(impl, meta_instances); }
			template <class Pred> Udm::ChildrenAttr< ::UdmProject::Datanetwork, Pred> instances_sorted(const Pred &) const { return Udm::ChildrenAttr< ::UdmProject::Datanetwork, Pred>(impl, meta_instances); }

			static ::Uml::CompositionChildRole meta_crosslinks;
			Udm::ChildAttr< ::UdmProject::Datanetwork> crosslinks() const { return Udm::ChildAttr< ::UdmProject::Datanetwork>(impl, meta_crosslinks); }

			static ::Uml::CompositionChildRole meta_cross_associations;
			Udm::ChildAttr< ::UdmProject::Datanetwork> cross_associations() const { return Udm::ChildAttr< ::UdmProject::Datanetwork>(impl, meta_cross_associations); }

			Udm::ChildrenAttr< ::UdmProject::Datanetwork> Datanetwork_kind_children() const { return Udm::ChildrenAttr< ::UdmProject::Datanetwork>(impl, Udm::NULLCHILDROLE); }
			template<class Pred> Udm::ChildrenAttr< ::UdmProject::Datanetwork, Pred> Datanetwork_kind_children_sorted(const Pred &) const { return Udm::ChildrenAttr< ::UdmProject::Datanetwork, Pred>(impl, Udm::NULLCHILDROLE); }

			Udm::ParentAttr<Udm::Object> parent() const { return Udm::ParentAttr<Udm::Object>(impl, Udm::NULLPARENTROLE); }
		};

		class  Datanetwork :  public Udm::Object {
		public:
			static ::Uml::Class meta;

			Datanetwork() { }
			Datanetwork(Udm::ObjectImpl *impl) : UDM_OBJECT(impl) { }
			Datanetwork(const Datanetwork &master) : UDM_OBJECT(master) { }
			static Datanetwork Cast(const Udm::Object &a) { return __Cast(a, meta); }

			static Datanetwork Create(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role); }

			Datanetwork CreateInstance(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl); }

			Datanetwork CreateDerived(const Udm::Object &parent, const ::Uml::CompositionChildRole &role = Udm::NULLCHILDROLE) { return __Create(meta, parent, role, impl, true); }

			Udm::InstantiatedAttr< ::UdmProject::Datanetwork> Instances() { return Udm::InstantiatedAttr< ::UdmProject::Datanetwork>(impl);}
			template <class Pred> Udm::InstantiatedAttr< ::UdmProject::Datanetwork, Pred> Instances_sorted(const Pred &) { return Udm::InstantiatedAttr< ::UdmProject::Datanetwork, Pred>(impl);}

			Udm::DerivedAttr< ::UdmProject::Datanetwork> Derived() { return Udm::DerivedAttr< ::UdmProject::Datanetwork>(impl);}
			template <class Pred> Udm::DerivedAttr< ::UdmProject::Datanetwork, Pred> Derived_sorted(const Pred &) { return Udm::DerivedAttr< ::UdmProject::Datanetwork, Pred>(impl);}

			Udm::ArchetypeAttr< ::UdmProject::Datanetwork> Archetype() const { return Udm::ArchetypeAttr< ::UdmProject::Datanetwork>(impl);}

			static ::Uml::Attribute meta_metaDgr;
			Udm::StringAttr metaDgr() const { return Udm::StringAttr(impl, meta_metaDgr); }

			static ::Uml::Attribute meta_systemname;
			Udm::StringAttr systemname() const { return Udm::StringAttr(impl, meta_systemname); }

			static ::Uml::Attribute meta_metalocator;
			Udm::StringAttr metalocator() const { return Udm::StringAttr(impl, meta_metalocator); }

			static ::Uml::CompositionParentRole meta_instances_Project_parent;
			Udm::ParentAttr< ::UdmProject::Project> instances_Project_parent() const { return Udm::ParentAttr< ::UdmProject::Project>(impl, meta_instances_Project_parent); }

			static ::Uml::CompositionParentRole meta_crosslinks_Project_parent;
			Udm::ParentAttr< ::UdmProject::Project> crosslinks_Project_parent() const { return Udm::ParentAttr< ::UdmProject::Project>(impl, meta_crosslinks_Project_parent); }

			static ::Uml::CompositionParentRole meta_cross_associations_Project_parent;
			Udm::ParentAttr< ::UdmProject::Project> cross_associations_Project_parent() const { return Udm::ParentAttr< ::UdmProject::Project>(impl, meta_cross_associations_Project_parent); }

			Udm::ParentAttr< ::UdmProject::Project> parent() const { return Udm::ParentAttr< ::UdmProject::Project>(impl, Udm::NULLPARENTROLE); }
		};



}

#endif //MOBIES_UDMPROJECT_H
