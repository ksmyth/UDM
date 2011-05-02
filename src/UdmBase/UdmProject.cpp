// cpp (meta datanetwork format) source file UdmProject.cpp
// generated from diagram UdmProject
// generated on Mon May 02 10:02:17 2011

#include "UdmProject.h"
#include <UmlExt.h>
#include <UdmStatic.h>

#include <UdmDom.h>
#include "UdmProject_xsd.h"
using namespace std;

namespace UdmProject {

	::Uml::Class Datanetwork::meta;
	::Uml::Attribute Datanetwork::meta_metaDgr;
	::Uml::Attribute Datanetwork::meta_systemname;
	::Uml::Attribute Datanetwork::meta_metalocator;
	::Uml::CompositionParentRole Datanetwork::meta_cross_associations_Project_parent;
	::Uml::CompositionParentRole Datanetwork::meta_instances_Project_parent;
	::Uml::CompositionParentRole Datanetwork::meta_crosslinks_Project_parent;

	::Uml::Class Project::meta;
	::Uml::Attribute Project::meta_name;
	::Uml::CompositionChildRole Project::meta_cross_associations;
	::Uml::CompositionChildRole Project::meta_instances;
	::Uml::CompositionChildRole Project::meta_crosslinks;

	::Uml::Diagram meta;

	void CreateMeta() {
		// classes, with attributes, constraints and constraint definitions
		Datanetwork::meta = ::Uml::CreateClass();
		Datanetwork::meta_metaDgr = ::Uml::CreateAttribute();
		Datanetwork::meta_systemname = ::Uml::CreateAttribute();
		Datanetwork::meta_metalocator = ::Uml::CreateAttribute();

		Project::meta = ::Uml::CreateClass();
		Project::meta_name = ::Uml::CreateAttribute();

		Datanetwork::meta_cross_associations_Project_parent = ::Uml::CreateCompositionParentRole();
		Project::meta_cross_associations = ::Uml::CreateCompositionChildRole();
		Datanetwork::meta_instances_Project_parent = ::Uml::CreateCompositionParentRole();
		Project::meta_instances = ::Uml::CreateCompositionChildRole();
		Datanetwork::meta_crosslinks_Project_parent = ::Uml::CreateCompositionParentRole();
		Project::meta_crosslinks = ::Uml::CreateCompositionChildRole();

	}

	void InitMeta() {
		// classes, with attributes, constraints and constraint definitions
		::Uml::InitClass(Datanetwork::meta, meta, "Datanetwork", false, NULL, NULL);
		::Uml::InitAttribute(Datanetwork::meta_metaDgr, Datanetwork::meta, "metaDgr", "String", false, false, 1, 1, false, "public", vector<string>());
		::Uml::InitAttribute(Datanetwork::meta_systemname, Datanetwork::meta, "systemname", "String", false, false, 1, 1, false, "public", vector<string>());
		::Uml::InitAttribute(Datanetwork::meta_metalocator, Datanetwork::meta, "metalocator", "String", false, false, 0, 1, false, "public", vector<string>());

		::Uml::InitClass(Project::meta, meta, "Project", false, NULL, NULL);
		::Uml::InitAttribute(Project::meta_name, Project::meta, "name", "String", false, false, 1, 1, false, "public", vector<string>());

	}

	void InitMetaLinks() {
		// compositions
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(Datanetwork::meta_cross_associations_Project_parent, comp, "cross_associations_Project_parent", true, Project::meta);
			::Uml::InitCompositionChildRole(Project::meta_cross_associations, comp, "cross_associations", true, 0, 1, Datanetwork::meta);

		}
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(Datanetwork::meta_instances_Project_parent, comp, "instances_Project_parent", true, Project::meta);
			::Uml::InitCompositionChildRole(Project::meta_instances, comp, "instances", true, 0, -1, Datanetwork::meta);

		}
		{
			::Uml::Composition comp = ::Uml::CreateComposition();
			::Uml::InitComposition(comp, meta, "Composition");
			::Uml::InitCompositionParentRole(Datanetwork::meta_crosslinks_Project_parent, comp, "crosslinks_Project_parent", true, Project::meta);
			::Uml::InitCompositionChildRole(Project::meta_crosslinks, comp, "crosslinks", true, 0, 1, Datanetwork::meta);

		}

	}

	void _SetXsdStorage()
	{
		UdmDom::str_xsd_storage::StoreXsd("UdmProject.xsd", UdmProject_xsd::getString());
	}

	void Initialize()
	{
		static bool first = true;
		if (!first) return;
		first = false;
		::Uml::Initialize();

	
		UDM_ASSERT( meta == Udm::null );

		meta = ::Uml::CreateDiagram();


		CreateMeta();
		InitMeta();
		InitMetaLinks();

		::Uml::InitDiagram(meta, "UdmProject", "1.00");


		_SetXsdStorage();

	}


	Udm::UdmDiagram diagram = { &meta, Initialize };
	static struct _regClass
	{
		_regClass()
		{
			Udm::MetaDepository::StoreDiagram("UdmProject", diagram);
		}
		~_regClass()
		{
			Udm::MetaDepository::RemoveDiagram("UdmProject");
		}
	} __regUnUsed;

}

