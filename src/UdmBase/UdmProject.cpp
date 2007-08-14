// cpp source file UdmProject.cpp generated from diagram UdmProject
// generated on Fri Sep 23 15:53:40 2005

#include "UdmProject.h"
#include "UmlExt.h"

namespace UdmProject {

	::Uml::Diagram umldiagram;

		::Uml::Class Project::meta;
		::Uml::Class Datanetwork::meta;
		::Uml::Attribute Project::meta_name;
		::Uml::Attribute Datanetwork::meta_metaDgr;
		::Uml::Attribute Datanetwork::meta_systemname;
		::Uml::Attribute Datanetwork::meta_metalocator;
		::Uml::CompositionParentRole Datanetwork::meta_cross_associations_Project_parent;
		::Uml::CompositionParentRole Datanetwork::meta_crosslinks_Project_parent;
		::Uml::CompositionParentRole Datanetwork::meta_instances_Project_parent;
		::Uml::CompositionChildRole Project::meta_cross_associations;
		::Uml::CompositionChildRole Project::meta_crosslinks;
		::Uml::CompositionChildRole Project::meta_instances;
	 void InitializeDgr()
	{
			Project::meta = ::Uml::CreateClass();
			Datanetwork::meta = ::Uml::CreateClass();
			Project::meta_name = ::Uml::CreateAttribute();
			Datanetwork::meta_metaDgr = ::Uml::CreateAttribute();
			Datanetwork::meta_systemname = ::Uml::CreateAttribute();
			Datanetwork::meta_metalocator = ::Uml::CreateAttribute();
			Datanetwork::meta_cross_associations_Project_parent = ::Uml::CreateCompositionParentRole();
			Datanetwork::meta_crosslinks_Project_parent = ::Uml::CreateCompositionParentRole();
			Datanetwork::meta_instances_Project_parent = ::Uml::CreateCompositionParentRole();
			Project::meta_cross_associations = ::Uml::CreateCompositionChildRole();
			Project::meta_crosslinks = ::Uml::CreateCompositionChildRole();
			Project::meta_instances = ::Uml::CreateCompositionChildRole();
		
			::Uml::InitClass(Project::meta, umldiagram, "Project", false);
			::Uml::InitClass(Datanetwork::meta, umldiagram, "Datanetwork", false);
		
			::Uml::InitAttribute(Project::meta_name, Project::meta, "name", "String", false, false, 1, 1, false, "public");
			::Uml::InitAttribute(Datanetwork::meta_metaDgr, Datanetwork::meta, "metaDgr", "String", false, false, 1, 1, false, "public");
			::Uml::InitAttribute(Datanetwork::meta_systemname, Datanetwork::meta, "systemname", "String", false, false, 1, 1, false, "public");
			::Uml::InitAttribute(Datanetwork::meta_metalocator, Datanetwork::meta, "metalocator", "String", false, false, 0, 1, false, "public");
		
			{
				::Uml::Composition comp = ::Uml::CreateComposition();
				::Uml::InitComposition(comp , umldiagram, "");
			
				::Uml::InitCompositionParentRole(Datanetwork::meta_cross_associations_Project_parent, comp, "cross_associations_Project_parent", true, Project::meta);
				::Uml::InitCompositionChildRole(Project::meta_cross_associations, comp, "cross_associations", true, 0, 1, Datanetwork::meta);
			}
			{
				::Uml::Composition comp = ::Uml::CreateComposition();
				::Uml::InitComposition(comp , umldiagram, "");
			
				::Uml::InitCompositionParentRole(Datanetwork::meta_crosslinks_Project_parent, comp, "crosslinks_Project_parent", true, Project::meta);
				::Uml::InitCompositionChildRole(Project::meta_crosslinks, comp, "crosslinks", true, 0, 1, Datanetwork::meta);
			}
			{
				::Uml::Composition comp = ::Uml::CreateComposition();
				::Uml::InitComposition(comp , umldiagram, "");
			
				::Uml::InitCompositionParentRole(Datanetwork::meta_instances_Project_parent, comp, "instances_Project_parent", true, Project::meta);
				::Uml::InitCompositionChildRole(Project::meta_instances, comp, "instances", true, 0, -1, Datanetwork::meta);
			}
		
	}
	 void Initialize()
	{
		static bool first = true;
		if(!first) return;
		first = false;
		::Uml::Initialize();

		ASSERT( umldiagram == Udm::null );
		umldiagram = ::Uml::CreateDiagram();

		InitializeDgr();

		::Uml::InitDiagram(umldiagram, "UdmProject", "1.00");
	}
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
