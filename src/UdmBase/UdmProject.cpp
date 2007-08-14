// cpp(meta datanetwork format) source file UdmProject.cpp generated from diagram UdmProject
// generated on Sun Jan 16 21:02:46 2005

#include "UdmProject.h"
#include "UmlExt.h"

#include "UdmStatic.h"

namespace UdmProject {

	::Uml::Uml::Diagram umldiagram;

	namespace UdmProject {

		::Uml::Uml::Namespace meta;
		::Uml::Uml::Class Datanetwork::meta;
		::Uml::Uml::Class Project::meta;
		::Uml::Uml::Attribute Datanetwork::meta_metaDgr;
		::Uml::Uml::Attribute Datanetwork::meta_systemname;
		::Uml::Uml::Attribute Datanetwork::meta_metalocator;
		::Uml::Uml::Attribute Project::meta_name;
		::Uml::Uml::CompositionParentRole Datanetwork::meta_cross_associations_Project_parent;
		::Uml::Uml::CompositionParentRole Datanetwork::meta_crosslinks_Project_parent;
		::Uml::Uml::CompositionParentRole Datanetwork::meta_instances_Project_parent;
		::Uml::Uml::CompositionChildRole Project::meta_cross_associations;
		::Uml::Uml::CompositionChildRole Project::meta_crosslinks;
		::Uml::Uml::CompositionChildRole Project::meta_instances;
		void Creates()
		{
			Datanetwork::meta = ::Uml::Uml::Class::Create(meta);
			Project::meta = ::Uml::Uml::Class::Create(meta);
			Datanetwork::meta_metaDgr = ::Uml::Uml::Attribute::Create(Datanetwork::meta);
			Datanetwork::meta_systemname = ::Uml::Uml::Attribute::Create(Datanetwork::meta);
			Datanetwork::meta_metalocator = ::Uml::Uml::Attribute::Create(Datanetwork::meta);
			Project::meta_name = ::Uml::Uml::Attribute::Create(Project::meta);
		}
		void InitClassesAttributes()
		{
			Datanetwork::meta.name() = "Datanetwork";
			Datanetwork::meta.isAbstract() = false;
			Project::meta.name() = "Project";
			Project::meta.isAbstract() = false;
			
			Datanetwork::meta_metaDgr.name() = "metaDgr";
			Datanetwork::meta_metaDgr.type() = "String";
			Datanetwork::meta_metaDgr.min() = 1;
			Datanetwork::meta_metaDgr.max() = 1;
			Datanetwork::meta_metaDgr.nonpersistent() = false;
			Datanetwork::meta_metaDgr.registry() = false;
			Datanetwork::meta_metaDgr.ordered() = false;
			Datanetwork::meta_metaDgr.visibility() = "public";
			Datanetwork::meta_metaDgr.defvalue() = vector<string>();
			Datanetwork::meta_systemname.name() = "systemname";
			Datanetwork::meta_systemname.type() = "String";
			Datanetwork::meta_systemname.min() = 1;
			Datanetwork::meta_systemname.max() = 1;
			Datanetwork::meta_systemname.nonpersistent() = false;
			Datanetwork::meta_systemname.registry() = false;
			Datanetwork::meta_systemname.ordered() = false;
			Datanetwork::meta_systemname.visibility() = "public";
			Datanetwork::meta_systemname.defvalue() = vector<string>();
			Datanetwork::meta_metalocator.name() = "metalocator";
			Datanetwork::meta_metalocator.type() = "String";
			Datanetwork::meta_metalocator.min() = 0;
			Datanetwork::meta_metalocator.max() = 1;
			Datanetwork::meta_metalocator.nonpersistent() = false;
			Datanetwork::meta_metalocator.registry() = false;
			Datanetwork::meta_metalocator.ordered() = false;
			Datanetwork::meta_metalocator.visibility() = "public";
			Datanetwork::meta_metalocator.defvalue() = vector<string>();
			Project::meta_name.name() = "name";
			Project::meta_name.type() = "String";
			Project::meta_name.min() = 1;
			Project::meta_name.max() = 1;
			Project::meta_name.nonpersistent() = false;
			Project::meta_name.registry() = false;
			Project::meta_name.ordered() = false;
			Project::meta_name.visibility() = "public";
			Project::meta_name.defvalue() = vector<string>();
			
		}
		void InitComposition0()
		{
			::Uml::Uml::Composition comp = ::Uml::Uml::Composition::Create(meta);
			comp.nonpersistent() =false;
			Datanetwork::meta_cross_associations_Project_parent = ::Uml::Uml::CompositionParentRole::Create(comp);
			Datanetwork::meta_cross_associations_Project_parent.name() = "cross_associations_Project_parent";
			Datanetwork::meta_cross_associations_Project_parent.isNavigable() = true;
			Datanetwork::meta_cross_associations_Project_parent.target() = Project::meta;
			Project::meta_cross_associations = ::Uml::Uml::CompositionChildRole::Create(comp);
			Project::meta_cross_associations.name() = "cross_associations";
			Project::meta_cross_associations.min() = 0;
			Project::meta_cross_associations.max() = 1;
			Project::meta_cross_associations.isNavigable() = true;
			Project::meta_cross_associations.target() = Datanetwork::meta;
		}
		void InitComposition1()
		{
			::Uml::Uml::Composition comp = ::Uml::Uml::Composition::Create(meta);
			comp.nonpersistent() =false;
			Datanetwork::meta_crosslinks_Project_parent = ::Uml::Uml::CompositionParentRole::Create(comp);
			Datanetwork::meta_crosslinks_Project_parent.name() = "crosslinks_Project_parent";
			Datanetwork::meta_crosslinks_Project_parent.isNavigable() = true;
			Datanetwork::meta_crosslinks_Project_parent.target() = Project::meta;
			Project::meta_crosslinks = ::Uml::Uml::CompositionChildRole::Create(comp);
			Project::meta_crosslinks.name() = "crosslinks";
			Project::meta_crosslinks.min() = 0;
			Project::meta_crosslinks.max() = 1;
			Project::meta_crosslinks.isNavigable() = true;
			Project::meta_crosslinks.target() = Datanetwork::meta;
		}
		void InitComposition2()
		{
			::Uml::Uml::Composition comp = ::Uml::Uml::Composition::Create(meta);
			comp.nonpersistent() =false;
			Datanetwork::meta_instances_Project_parent = ::Uml::Uml::CompositionParentRole::Create(comp);
			Datanetwork::meta_instances_Project_parent.name() = "instances_Project_parent";
			Datanetwork::meta_instances_Project_parent.isNavigable() = true;
			Datanetwork::meta_instances_Project_parent.target() = Project::meta;
			Project::meta_instances = ::Uml::Uml::CompositionChildRole::Create(comp);
			Project::meta_instances.name() = "instances";
			Project::meta_instances.min() = 0;
			Project::meta_instances.max() = -1;
			Project::meta_instances.isNavigable() = true;
			Project::meta_instances.target() = Datanetwork::meta;
		}
		 void Initialize()
		{
			Creates();
			InitClassesAttributes();
			InitComposition0();
			InitComposition1();
			InitComposition2();
			
		}
		 void Initialize(const ::Uml::Uml::Namespace & ns)
		{
			Uml::SetClass(Datanetwork::meta, ns, "Datanetwork");
			Uml::SetAttribute(Datanetwork::meta_metaDgr,Datanetwork::meta, "metaDgr");
			Uml::SetAttribute(Datanetwork::meta_systemname,Datanetwork::meta, "systemname");
			Uml::SetAttribute(Datanetwork::meta_metalocator,Datanetwork::meta, "metalocator");
			Uml::SetClass(Project::meta, ns, "Project");
			Uml::SetAttribute(Project::meta_name,Project::meta, "name");
			//composition child roles 
			Uml::SetParentRole(Datanetwork::meta_cross_associations_Project_parent,Datanetwork::meta,Project::meta, "cross_associations", "");
			Uml::SetParentRole(Datanetwork::meta_crosslinks_Project_parent,Datanetwork::meta,Project::meta, "crosslinks", "");
			Uml::SetParentRole(Datanetwork::meta_instances_Project_parent,Datanetwork::meta,Project::meta, "instances", "");
			// composition parentroles 
			Uml::SetChildRole(Project::meta_cross_associations,Project::meta,Datanetwork::meta, "", "cross_associations");
			Uml::SetChildRole(Project::meta_crosslinks,Project::meta,Datanetwork::meta, "", "crosslinks");
			Uml::SetChildRole(Project::meta_instances,Project::meta,Datanetwork::meta, "", "instances");
			// Association roles 


			
		}
	}
	void Initialize()
	{
		static bool first = true;
		if(!first) return;
		first = false;
		::Uml::Initialize();

		ASSERT( umldiagram == Udm::null );
		UdmStatic::StaticDataNetwork * meta_dn = new UdmStatic::StaticDataNetwork(::Uml::diagram);
		meta_dn->CreateNew("UdmProject.mem", "", ::Uml::Uml::Diagram::meta, Udm::CHANGES_LOST_DEFAULT);
		umldiagram = ::Uml::Uml::Diagram::Cast(meta_dn->GetRootObject());
		umldiagram.name() ="UdmProject";
		umldiagram.version() ="1.00";
		
		UdmProject::meta = ::Uml::Uml::Namespace::Create(umldiagram);
		UdmProject::meta.name() = "UdmProject";
		UdmProject::Initialize();
	};
	void Initialize(const ::Uml::Uml::Diagram &dgr)
	{
		umldiagram = dgr;
		::Uml::SetNamespace(UdmProject::meta, dgr, "UdmProject");
		UdmProject::Initialize(UdmProject::meta);
	};
	Udm::UdmDiagram diagram = { &umldiagram, Initialize };
	static struct _regClass
	{
		_regClass()
		{
			Udm::MetaDepository::StoreDiagram("UdmProject", diagram);
		};
		~_regClass()
		{
			Udm::MetaDepository::RemoveDiagram("UdmProject");
		};
	} __regUnUsed;

}
// END UdmProject.cpp
