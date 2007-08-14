/*
 *	Copyright (c) Vanderbilt University, 2000-2001
 *	ALL RIGHTS RESERVED
 *
 *	Vanderbilt University disclaims all warranties with regard to this
 *	software, including all implied warranties of merchantability
 *	and fitness.  In no event shall Vanderbilt University be liable for
 *	any special, indirect or consequential damages or any damages
 *	whatsoever resulting from loss of use, data or profits, whether
 *	in an action of contract, negligence or other tortious action,
 *	arising out of or in connection with the use or performance of
 *	this software.
 */

/*
	-	11/10/04	-	endre

				- support for silent mode added.

	-  13/07/04	-	endre

				- isNavigable property was not saved correctly in the XML file.
				(if there is no role name, the role is considered not navigable)

	-	03/04/04	-	endre

				- an attempt to use the cross-link machinery for temporary links between the objects of the same datanetworks
				the rule as suggested by Adi: Associations that are among classes of the same package, but the connection itself
				is drawn outside the package are considered semi-cross associations, and will be instantiated in the cross-datanetwork 
				of the Udm project files.

				
	-	27/02/04	-	endre
				
				-	added the call GetPackage() for CClassBuilder and CCompositeClassBuilder 

	-	26/02/04	-	endre

				-	changed all CompositeClass->GetFolder() calls to GetParent()->GetParent() calls because 
					the parent of classes now are Models.
	-	24/02/04	-	endre

				-	changed the code to:
						- work with package models instead of package folders
						- ignore class diagram in the root folder
						- generate the version information in the output XML
	-	12/12/03	-	endre

					Bugfix: replaced the "_" delimiter characther with the 
					"_cross_ph_" delimiter string, to allow regular class-names 
					and diagram names to contain the "_" character


	-   12/02/03	-	endre

					bugfix: cross-link generation bug in situation of multiple inheritence

	-   11/28/03	-	endre
					
					  XSD support added

	-   11/118/03	- aditya
					added support for interpterer to work with UMT
					changed error messages to int_exceptions that are caught by 
					ComponentDll.cpp

	-	10/17/02	- Attribute specifier now is conformant with
					the UML Notation Guide standard 1.4

	-	06/17/02	-	endre

		  Added support for attribute arrays


	-	06/03/02	-	endre

		CCompositionBuilder::GetRoleID()	- had a bug which could not handle self-containment.
		Removed thsi functions and introduced two, GetParentRoleId(), and getChildrenRoleId(),
		which undoubtly code-doubling, but at least works;)

  */

#include "stdafx.h"

//stream in memory
#include <strstream>

#include "Lattrib.hpp"
#include "Pattrib.hpp"


#include "CardinalityObject.h"
#include "AttributeObject.h"
#include <afxdlgs.h>
#include <set>


//Component.h
#include "Component.h"
#include "int_exception.h"

//zip 
#include <zlib.h>
#include <contrib\minizip\zip.h>

//DTDs as resources
#include "Resource.h"

#define IDBASE	"id0000"

static int idcount = 1;

char* GetRelativeFilename(const char *currentDirectory,const char *absoluteFilename);

CComponent *CComponent::theInstance = 0;
#ifdef _DEBUG
#define DLL_NAME "UML2XMLD.dll"
#else
#define DLL_NAME "UML2XML.dll"
#endif



//////////////////////////////// CComponent //////////////////////////////////


CComponent::~CComponent()
{
	POSITION pos = compositeClasses.GetHeadPosition();
	while(pos)
		delete compositeClasses.GetNext(pos);
}

CString CComponent::GetID()
{
	CString id;
	id.Format("%s%d",IDBASE,idcount);
	idcount++;
	return id;
}

BOOL CALLBACK resenum(
  HMODULE hModule,   // module handle
  LPCTSTR lpszType,  // resource type
  LPTSTR lpszName,   // resource name
  long  lParam    // application-defined parameter
)
{
	
	AfxMessageBox(CString(lpszName) + CString(":") + CString(lpszType));
	return TRUE;
};


//void CComponent::Invoke(CBuilder &builder,CBuilderObjectList &selected, long param)
void CComponent::InvokeEx(CBuilder &builder,CBuilderObject *focus, CBuilderObjectList &selected, long param)
{	
	try
	{
		isUMT = false;
		theInstance = this;		// cannot use this in Initialize() functions!!!
		
		//open Udm Project dialog
		CBuilderFolder *root = builder.GetRootFolder();
		name = root->GetName();

		//getting the packages
		CPackageBuilderList *packages = &packageList;
		GatherPackageFolders(root, *packages);
		
		if(packages->GetCount() == 0)
		{	throw int_exception("Uml2Xml Error: There are no class diagrams in the project. No output will be generated");
		}

		if(packages->GetCount() == 1)
		{
			//only one diagram
			CPackageBuilder * package = packages->GetHead();

			name = package->GetName();
			
			GatherPackageSheets(package,sheets);
			POSITION pos = sheets.GetHeadPosition();
			while(pos)
				sheets.GetNext(pos)->Build(compositeClasses);
		
				
			BuildInheritance();
			CheckInheritance();

			BuildCompositions();
			BuildAssociations();

			std::strstream package_xml; 
			DumpXML(package_xml, package->GetVersion());
			
			
			CString filepath;

			if (param & GME_SILENT_MODE)
				filepath = name + "_udm.xml";
			else
				filepath = GetFilePath(builder, focus, "xml", "XML files (*.xml)|*.xml");

			if(filepath == "")
			{	throw int_exception("");
			}
			////////////////////////////////////////////////////
			FILE * f = fopen((LPCTSTR)(filepath),"w");
			if (!f)
			{	CString msg = "Uml2Xml Error: File " + filepath + " could not be opened!" ;
				throw int_exception((LPCTSTR)msg);
			}
			fwrite((void*)(package_xml.str()),sizeof(char), package_xml.pcount(), f);
			fclose(f);
			if(isUMT)
			{	
				CString sysCall = "call \"%UDM_PATH%\\bin\\Udm.exe\" \"" + filepath + "\"";
				if(system(LPCSTR(sysCall))!=0)
					throw int_exception("Uml2Xml Error: Unable to run command: "+ sysCall);
			}

			return;
		}

		
		CString filepath;
		
		if (param & GME_SILENT_MODE)
			filepath = name + "_udm.udm";
		else
			filepath = GetFilePath(builder, focus,"udm","Udm Project Files (*.udm)|*.udm");
		if(filepath == "")
		{	throw int_exception("");
			
		}
		////////////////////////////////////////////////////

		//zip initialization
		CString project_file = filepath;
		zipFile zip_pf = zipOpen(project_file, 0);
		if (zip_pf == NULL)
		{
			throw int_exception("Uml2Xml Error: File could not be opened for writing!");
		}

		//timestamp on ZIP-ed files
		time_t now;
		time(&now);

		struct tm *newtime = localtime(&now);
		zip_fileinfo zfi;
		zfi.tmz_date.tm_sec = newtime->tm_sec;
		zfi.tmz_date.tm_min = newtime->tm_min;
		zfi.tmz_date.tm_mday = newtime->tm_mday;
		zfi.tmz_date.tm_mon = newtime->tm_mon;
		zfi.tmz_date.tm_year = newtime->tm_year;
		zfi.dosDate = 0;
		zfi.internal_fa = 0;
		zfi.external_fa = 0;



		
		//map to store the generated XML for each package
		std::map<CString, std::strstream*> package_xmls;
		
		//generate XML for each package
		POSITION mPos = packages->GetHeadPosition();
		while (mPos)
		{
			CPackageBuilder * package = packages->GetNext(mPos);
			name = package->GetName();
			
			GatherPackageSheets(package,sheets);
			POSITION pos = sheets.GetHeadPosition();
			while(pos)
				sheets.GetNext(pos)->Build(compositeClasses);

			BuildInheritance();
			CheckInheritance();

			BuildCompositions();
			BuildIsoAssociations();
			
			std::strstream* package_xml = new std::strstream();
			DumpIsolatedXML(*package_xml,package->GetVersion());
			std::map<CString, std::strstream*>::value_type item(package->GetName() + CString(".xml"), package_xml);
			package_xmls.insert(item);


			compositeClasses.RemoveAll();
			compositions.RemoveAll();
			associations.RemoveAll();
			sheets.RemoveAll();
		};
		

		//generate the cross package associations

		name = root->GetName();
		GatherAllSheets(sheets);


		POSITION pos = sheets.GetHeadPosition();
		while(pos)
			sheets.GetNext(pos)->Build(compositeClasses);

		BuildInheritance();
		CheckInheritance();
		BuildCompositions();
		BuildAssociations();

		std::strstream cross_xml;

		//if (HasCrossAssociations())
		//{
			DumpCrossXML(cross_xml,"1.00");
		//}


		//Generate &output _project_.xml
		std::strstream project_xml;		//all the XML will be generated in the memory
		zipOpenNewFileInZip(zip_pf, "_project_.xml", &zfi, NULL,0, NULL, 0,  "UDM Project description. (XML)", 0, Z_DEFAULT_COMPRESSION);
		DumpProjectXML(root, project_xml, "1.00");
		zipWriteInFileInZip(zip_pf, (void*)project_xml.str(), (unsigned long)project_xml.pcount());
		zipCloseFileInZip(zip_pf);
		project_xml.clear();
		
		//output cross_xml
		if ((unsigned long)cross_xml.pcount() > 0)
		{
			zipOpenNewFileInZip(zip_pf, (LPCTSTR)(root->GetName() + CString(".xml")), &zfi, NULL,0, NULL, 0,  "Cross-package specification(XML)", 0, Z_DEFAULT_COMPRESSION);
			zipWriteInFileInZip(zip_pf, (void*)cross_xml.str(), (unsigned long)cross_xml.pcount());
			zipCloseFileInZip(zip_pf);
			cross_xml.clear();
		}


		//output instance_xmls
		for (std::map<CString, std::strstream*>::iterator i = package_xmls.begin(); i != package_xmls.end(); i++)
		{
			zipOpenNewFileInZip(zip_pf, (LPCTSTR)(i->first), &zfi, NULL,0, NULL, 0,  "Instance data network(XML)", 0, Z_DEFAULT_COMPRESSION);
			
			zipWriteInFileInZip(zip_pf, (void*)(i->second->str()), (unsigned long)(i->second->pcount()));
			zipCloseFileInZip(zip_pf);
			i->second->clear();
			delete i->second;		//they were created on the heap
		};



		

		HRSRC res;
		HGLOBAL resgl;
		HMODULE thisModule = GetModuleHandle(DLL_NAME);
		if (thisModule)
		{
			//EnumResourceNames(thisModule, "XSD", resenum, 0);
			//add Uml.xsd and UdmProject.xsd
			res = FindResource(thisModule,(const char *)XSD_UDMPROJECT,"XSD");
			if (res)
			{
				resgl = LoadResource(thisModule, res);
				if (resgl)
				{
					void * buff = LockResource(resgl);
					DWORD size = SizeofResource(thisModule, res);

					zipOpenNewFileInZip(zip_pf, "UdmProject.xsd", &zfi, NULL,0, NULL, 0,  "XSD", 0, Z_DEFAULT_COMPRESSION);
				
					zipWriteInFileInZip(zip_pf, buff, size);
					zipCloseFileInZip(zip_pf);
				}
			}
			res = FindResource(thisModule,(const char *)XSD_UML,"XSD");
			if (res)
			{
				resgl = LoadResource(thisModule, res);
				if (resgl)
				{
					void * buff = LockResource(resgl);
					DWORD size = SizeofResource(thisModule, res);

					zipOpenNewFileInZip(zip_pf, "Uml.xsd", &zfi, NULL,0, NULL, 0,  "XSD", 0, Z_DEFAULT_COMPRESSION);
				
					zipWriteInFileInZip(zip_pf, buff, size);
					zipCloseFileInZip(zip_pf);
				}
			}
		}
		//close ZIP file
		zipClose(zip_pf, "UDM Project file(regular zip) containing metainformation. Generated by the UML2XML interpreter.");

		if(isUMT)
		{	CString sysCall = "call \"%UDM_PATH%\\bin\\Udm.exe\" \"" + filepath + "\"";
			if(system(LPCSTR(sysCall))!=0)
				throw int_exception("Uml2Xml Error: Unable to run command: "+ sysCall);
		}
	}
	catch (int_exception &e)
	{
		if (param & GME_SILENT_MODE) return;

		std::string str  = e.what();
		//do we have stg to say?
		if (str.length())
			AfxMessageBox(e.what().c_str());
	};
}

void CComponent::AddComposition(CCompositionBuilder *comp)
{
	compositions.AddTail(comp);
}

void CComponent::AddAssociation(CAssociationBase *ass)
{
	associations.AddTail(ass);
}
/*
int CComponent::GatherPackageFolders(CBuilderFolder*folder,CBuilderFolderList &packageFolders)
{
	int foldercount = 0;
	if(folder->GetKindName() == "RootFolder")
	{
		const CBuilderModelList *models =folder->GetRootModels();
		const CBuilderFolderList *subfolders = folder->GetSubFolders();
		if(subfolders)
		{
			POSITION pos = subfolders->GetHeadPosition();
			while(pos)
			{
				CBuilderFolder *subfolder = subfolders->GetNext(pos);
				foldercount += GatherPackageFolders(subfolder, packageFolders);
			}
		}
	
		POSITION pacPos = models->GetHeadPosition();
		While(pacPos)
		{
			CBuilderModel *model = models->GetNext(pacPos);
			if(model->GetKindName() == "Package")
			{
				packageFolders.AddTail(folder);
				foldercount = 1;
			}
		}
		return foldercount;
	}
	return foldercount;
}
*/
int CComponent::GatherPackageFolders(CBuilderFolder *folder,CPackageBuilderList &packages)
{
	int foldercount = 0;
	if(folder->GetKindName() == "RootFolder")
	{

		const CBuilderFolderList *subfolders = folder->GetSubFolders();
		if(subfolders)
		{
			POSITION pos = subfolders->GetHeadPosition();
			while(pos)
			{
				CBuilderFolder *subfolder = subfolders->GetNext(pos);
				foldercount += GatherPackageFolders(subfolder, packages);
			}
		}

		const CBuilderModelList *models = folder->GetRootModels();
		if(models)
		{	
			POSITION pos = models->GetHeadPosition();
			while(pos)
			{	
				CBuilderModel *model = models->GetNext(pos);
				if (model->IsKindOf(RUNTIME_CLASS(CPackageBuilder)))
				{
					packages.AddTail(BUILDER_CAST(CPackageBuilder, model));	
					foldercount = 1;
				}		
			}
		}
			
		return foldercount;
	}
	return foldercount;
}

void CComponent::GatherAllSheets(CClassDiagramList &sheets)
{
	POSITION pos = packageList.GetHeadPosition();
	while(pos)
	{	CPackageBuilder *package = packageList.GetNext(pos);
		GatherPackageSheets(package, sheets);
	}
	
}

void CComponent::GatherModelSheets(const CBuilderModelList *roots, CClassDiagramList &sheets)
{
	POSITION pos = roots->GetHeadPosition();
	while(pos) 
	{
		CBuilderModel *model = roots->GetNext(pos);
		if(model->GetKindName() == "ClassDiagram")
		{	CClassDiagramBuilder *sheet = dynamic_cast<CClassDiagramBuilder *>(model);
			if(!sheet) 
			{
				AfxMessageBox("Unexpected model kind found: " + sheet->GetName());
				continue;
			}
			sheets.AddTail(sheet);
			GatherModelSheets(sheet->GetModels(), sheets);
		}
		if(model->GetKindName() == "Namespace")
			GatherModelSheets(model->GetModels(), sheets);
	}
}

void CComponent::GatherPackageSheets(CPackageBuilder *folder, CClassDiagramList &sheets)
{
	GatherModelSheets(folder->GetModels(), sheets);
}

void CComponent::BuildInheritance()
{
	POSITION pos = compositeClasses.GetHeadPosition();
	while(pos)
		compositeClasses.GetNext(pos)->FindSubClasses();
}

bool CComponent::CheckInheritance()
{
	POSITION pos = compositeClasses.GetHeadPosition();
	while(pos) {
		CStringList trace;
		CCompositeClass *comp = compositeClasses.GetNext(pos);
		if(!comp->CheckInheritance(trace)) {
			ASSERT(!trace.IsEmpty());
			CString traceTxt;
			POSITION pos = trace.GetHeadPosition();
			while(pos)
				traceTxt += trace.GetNext(pos) + " -> ";
			traceTxt += trace.GetHead();
			AfxMessageBox("Loop detected in the inheritance hierarchy: \n" + traceTxt,MB_OK | MB_ICONSTOP);
			return false;
		}
	}
	return true;
}

void CComponent::BuildCompositions()
{
	POSITION pos = compositeClasses.GetHeadPosition();
	while(pos)
		compositeClasses.GetNext(pos)->BuildCompositions();
}

void CComponent::BuildIsoAssociations()
{
	POSITION pos = compositeClasses.GetHeadPosition();
	while(pos)
		compositeClasses.GetNext(pos)->BuildIsoAssociations();

}

void CComponent::BuildAssociations()
{
	POSITION pos = compositeClasses.GetHeadPosition();
	while(pos)
		compositeClasses.GetNext(pos)->BuildAssociations();
}

void CComponent::DumpProjectXML(CBuilderFolder *root, std::strstream& xml, const CString& version)
{

	idcount = 1;

	xml << "<?xml version=\"1.0\"?>"  << std::endl << std::endl;
	//XSD

	//xml << "<!DOCTYPE Project SYSTEM \"UdmProject.dtd\">" << std::endl << std::endl;
	//xml << "<Project name =\"" << (LPCTSTR)root->GetName() <<"\">" << std::endl << std::endl;
	/*xml << "<Project name =\"" << (LPCTSTR)root->GetName() << "\"" << std::endl <<
	"   xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << std::endl <<
	"   xsi:noNamespaceSchemaLocation=\"UdmProject.xsd\">" << std::endl << std::endl;
	*/
	xml << "<UdmProject:Project name =\"" << (LPCTSTR)root->GetName() << "\"" << std::endl <<
	"xmlns:UdmProject=\'http://www.isis.vanderbilt.edu/2004/schemas/UdmProject\' " << std::endl << 
	"xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << std::endl <<
	"xsi:schemaLocation=\'http://www.isis.vanderbilt.edu/2004/schemas/UdmProject UdmProject.xsd\'>" << std::endl << std::endl;

	//eo XSD

	xml << "   <!-- Generated by the UML2XML interpreter -->" << std::endl << std::endl;

	idcount = 1;
	

	//if (HasCrossAssociations())
	xml << "\t<UdmProject:Datanetwork _id=\"" << (LPCTSTR)GetID() << "\" systemname=\"" << (LPCTSTR)(root->GetName() + CString(".xml")) << "\" __child_as=\"cross_associations\" metaDgr=\"Uml\"/>" << std::endl;

	
	CPackageBuilderList *folders = &packageList;
	POSITION pos = folders->GetHeadPosition();
	while(pos)
	{
		CPackageBuilder * package = folders->GetNext(pos);
		xml << "\t<UdmProject:Datanetwork _id=\"" << (LPCTSTR)GetID() << "\" systemname=\"" << (LPCTSTR) (package->GetName() + CString(".xml")) << "\" __child_as=\"instances\" metaDgr=\"Uml\"/>" << std::endl;
	}

	xml << "</UdmProject:Project>" << std::endl;
};

void CComponent::DumpCrossXML(std::strstream & xml, const CString & version)
{

	//std::ofstream xml((LPCTSTR)filename);
	xml << "<?xml version=\"1.0\"?>" <<	std::endl << std::endl;
	//XSD
	//xml<< "<!DOCTYPE Diagram SYSTEM \"uml.dtd\">" << std::endl << std::endl;
	//xml << "<Diagram name =\"" << (LPCTSTR)name << "\">" << std::endl << std::endl;

	xml << "<Diagram name =\"" << (LPCTSTR)name << "\"" << std::endl <<
	"version=\"" << (LPCTSTR)version << "\"" << std::endl << 
	//"xmlns:Uml=\'http://www.isis.vanderbilt.edu/2004/schemas/Uml\' " << std::endl << 
	"xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << std::endl <<
	"xsi:noNamespaceSchemaLocation=\'Uml.xsd\'>" << std::endl << std::endl;

	//eo. XSD

	xml << "   <!-- Generated by the UML2XML interpreter -->" << std::endl << std::endl;
	std::set<std::string> namespaces;
	POSITION pos = sheets.GetHeadPosition();
	while (pos)
	{
		CClassDiagramBuilder * ccdb = sheets.GetNext(pos);
		CString ns = ccdb->GetNamespace();
		if (ns.GetLength())
			namespaces.insert((const char*)ns);
	};
	std::set<std::string>::iterator ns_i = namespaces.begin();
	if (ns_i != namespaces.end())
	{
		xml << "<Namespace name=\"" << (LPCTSTR) name << "\">" << std::endl ;
		while (ns_i != namespaces.end())
		{
			CString ns = ns_i->c_str();	
			DumpCrossAssociations(xml, ns);
			ns_i++;
		}
		DumpCrossClasses(xml);
		xml << "</Namespace>" << std::endl;
	}
	xml << "</Diagram>" << std::endl;
	//xml.close();

};



void CComponent::DumpIsolatedXML(std::strstream & xml, const CString & version)
{
	//std::ofstream xml((LPCTSTR)filename);
	xml << "<?xml version=\"1.0\"?>" <<	std::endl << std::endl;
	//XSD
	//xml << "<!DOCTYPE Diagram SYSTEM \"uml.dtd\">" << std::endl << std::endl;
	//xml << "<Diagram name =\"" << (LPCTSTR)name << "\">" << std::endl << std::endl;

	xml << "<Diagram name =\"" << (LPCTSTR)name << "\"" << std::endl <<
	"version=\"" << (LPCTSTR)version << "\"" << std::endl << 
	//"xmlns:Uml=\'http://www.isis.vanderbilt.edu/2004/schemas/Uml\' " << std::endl << 
	"xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << std::endl <<
	"xsi:noNamespaceSchemaLocation=\'Uml.xsd\'>" << std::endl << std::endl;


	//eo XSD

	xml << "   <!-- Generated by the UML2XML interpreter -->" << std::endl << std::endl;

	std::set<std::string> namespaces;
	POSITION pos = sheets.GetHeadPosition();
	while (pos)
	{
		CClassDiagramBuilder * ccdb = sheets.GetNext(pos);
		CString ns = ccdb->GetNamespace();
		if (ns.GetLength())
			namespaces.insert((const char*)ns);
	};

	DumpIsolatedAssociations(xml, "");
	DumpClasses(xml, "");
	DumpCompositions(xml, "");

	std::set<std::string>::iterator ns_i = namespaces.begin();
	while (ns_i != namespaces.end())
	{

		CString ns = ns_i->c_str();
		xml << "<Namespace name=\"" << (LPCTSTR) ns << "\">" << std::endl ;
		DumpIsolatedAssociations(xml, ns);
		DumpClasses(xml,ns);
		DumpCompositions(xml,ns);
		xml << "</Namespace>" << std::endl;
		ns_i++;
	}
	xml << "</Diagram>" << std::endl;
	//xml.close();
};

void CComponent::DumpXML(std::strstream & xml, const CString & version)
{
	xml << "<?xml version=\"1.0\"?>" <<	std::endl << std::endl;
	//XSD
	//xml << "<!DOCTYPE Diagram SYSTEM \"uml.dtd\">" << std::endl << std::endl;
	//xml << "<Diagram name =\"" << (LPCTSTR)name << "\">" << std::endl << std::endl;
	xml << "<Diagram name =\"" << (LPCTSTR)name << "\"" << std::endl <<
	"version=\"" << (LPCTSTR)version << "\"" << std::endl << 
	//"xmlns:Uml=\'http://www.isis.vanderbilt.edu/2004/schemas/Uml\' " << std::endl << 
	"xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << std::endl <<
	"xsi:noNamespaceSchemaLocation=\'Uml.xsd\'>" << std::endl << std::endl;

	//eo XSD
	xml << "   <!-- Generated by the UML2XML interpreter -->" << std::endl << std::endl;

	std::set<std::string> namespaces;
	
	POSITION pos = sheets.GetHeadPosition();

	while (pos)
	{
		CClassDiagramBuilder * ccdb = sheets.GetNext(pos);
		const CString &ns = ccdb->GetNamespace();
		if (ns && ns.GetLength())
			namespaces.insert((const char*)ns);
	};

	DumpAssociations(xml, "");
	DumpClasses(xml, "");
	DumpCompositions(xml, "");

	std::set<std::string>::iterator ns_i = namespaces.begin();
	while (ns_i != namespaces.end())
	{

		CString ns = ns_i->c_str();

		xml << "<Namespace name=\"" << (LPCTSTR) ns << "\">" << std::endl ;
		
		DumpAssociations(xml, ns);
		DumpClasses(xml, ns);
		DumpCompositions(xml,ns);
		ns_i++;

		xml << "</Namespace>" << std::endl;

	};


	xml << "</Diagram>" << std::endl;
	//xml.close();

}

void CComponent::DumpCrossClasses(std::strstream &xml)
{
	std::strstream compositions; //this stream will contain the compositions
	std::strstream cont_class;	//this stream will contain the container class definition

	CString cont_class_id = GetID();//id for the container class

	//cont_class << "<Class _id=\"" << (LPCTSTR)cont_class_id << "\" name=\"_gen_cont\" isAbstract=\"false\" parentRoles = \"";  
	cont_class << "<Class _id=\"" << (LPCTSTR)cont_class_id << "\" name=\"_gen_cont\" isAbstract=\"false\"";  

	
	bool prole_added = false;
	POSITION pos = compositeClasses.GetHeadPosition();
	while(pos)
	{
		CString childrole_id = GetID();
		CString parentrole_id = GetID();
		
		CCompositeClass * ccl = compositeClasses.GetNext(pos);

		CString comp_id = childrole_id;
		if (ccl->DumpCrossXML(xml, comp_id))//comp_id will be overwritten with the ID of the class
		{
			compositions << "<Composition>" << std::endl;;
		
			compositions << "\t<CompositionChildRole _id=\"" << (LPCTSTR)childrole_id << "\" target=\"" << (LPCTSTR)comp_id << "\" min=\"0\" max=\"-1\"/>" << std::endl;
			compositions << "\t<CompositionParentRole _id=\"" << (LPCTSTR)parentrole_id << "\" target=\"" << (LPCTSTR)cont_class_id << "\"/>" << std::endl;
			compositions << "</Composition>" << std::endl;;	

			if (!prole_added)
			{
				cont_class << " parentRoles = \"";  
				prole_added = true;
			}
			cont_class << (LPCTSTR) parentrole_id << " ";
		}
	}

	if (prole_added)
		cont_class << "\"/>" << std::endl;
	else
		cont_class << "/>" << std::endl;


	char * tmp;
	tmp = new char[cont_class.pcount() + 1];
	strncpy(tmp, cont_class.str(), cont_class.pcount());
	*(tmp + cont_class.pcount()) = '\0';
	xml << std::string(tmp);
	delete [] tmp;
	tmp = new char[compositions.pcount() + 1];
	strncpy(tmp, compositions.str(), compositions.pcount());
	*(tmp + compositions.pcount()) = '\0';
	xml << std::string(tmp);
	delete [] tmp;
	

	

};
void CComponent::DumpClasses(std::strstream &xml, const CString& ns)
{
	POSITION pos = compositeClasses.GetHeadPosition();
	while(pos)
		compositeClasses.GetNext(pos)->DumpXML(xml,ns);
}



void CComponent::DumpCrossAssociations(std::strstream &xml, const CString& ns)
{
	
	POSITION pos = associations.GetHeadPosition();
	while(pos)
	{
		CAssociationBase * ass = associations.GetNext(pos);
		if (ass->IsCrossPackage())
			ass->DumpXML(xml, ns);		
	}
};

bool CComponent::HasCrossAssociations()
{
	POSITION pos = associations.GetHeadPosition();
	while(pos) 
		if (associations.GetNext(pos)->IsCrossPackage()) return true;
	return false;
};

void CComponent::DumpIsolatedAssociations(std::strstream &xml, const CString &ns)
{
	POSITION pos = associations.GetHeadPosition();
	int i = associations.GetCount();
	while(pos)
	{
		CAssociationBase * ass = associations.GetNext(pos);
		if (!ass->IsCrossPackage())
			ass->DumpXML(xml, ns);
	}


};

void CComponent::DumpAssociations(std::strstream &xml, const CString &ns)
{
	POSITION pos = associations.GetHeadPosition();
	while(pos)
		associations.GetNext(pos)->DumpXML(xml, ns);
}

void CComponent::DumpCompositions(std::strstream &xml, const CString& ns)
{
	POSITION pos = compositions.GetHeadPosition();
	while(pos)
		compositions.GetNext(pos)->DumpXML(xml,ns);
}

///////////////////////////// CPackage /////////////////////////////////

IMPLEMENT_CUSTOMMODEL(CPackageBuilder, CBuilderModel, "Package")
CString CPackageBuilder::GetVersion() const
{
	CString ret;
	GetAttribute("version", ret);
	return ret;
};

///////////////////////////// CClassDiagram /////////////////////////////////

IMPLEMENT_CUSTOMMODEL(CClassDiagramBuilder, CBuilderModel, "ClassDiagram")

CString CClassDiagramBuilder::GetNamespace() const
{
	const CBuilderModel *parent = this->GetParent();
	if (!parent)
		return "";
	if (parent->GetKindName() == "Namespace") {
		return parent->GetName();
	}
	if (parent->IsKindOf(RUNTIME_CLASS(CClassDiagramBuilder)))
		return BUILDER_CAST(CClassDiagramBuilder, parent)->GetNamespace();
	return "";
};

void CClassDiagramBuilder::Build(CCompositeClassList &compositeClasses)
{
	const CBuilderAtomList *classes = GetAtoms("Class");
	POSITION pos = classes->GetHeadPosition();
	while(pos) {
		CClassBuilder *cls = dynamic_cast<CClassBuilder *>(classes->GetNext(pos));
		ASSERT(cls);
		CBuilderObjectList copies;
		cls->GetReferencedBy(copies);

		CCompositeClass *comp = new CCompositeClass(cls,copies);
		compositeClasses.AddTail(comp);
	}
}

CPackageBuilder * CClassDiagramBuilder::GetPackage()
{
    CPackageBuilder * package;
	const CBuilderModel * parent = GetParent();
	while (parent && parent->GetKindName() != "Package")
		parent = parent->GetParent();
	package = BUILDER_CAST(CPackageBuilder, parent);
	ASSERT(package);
	return package;

};

////////////////////////////// CCompositeClass ////////////////////////////////

CCompositeClass::CCompositeClass(CClassBuilder *c,CBuilderObjectList &copies) : cls(c), association(0), flag(false)
{
	cls->composite = this;
	parts.AddHead(cls);
	POSITION pos = copies.GetHeadPosition();
	while(pos) 
	{	CBuilderObject *cpy = copies.GetNext(pos);
		if(cpy->GetKindName() != "ClassCopy")
			continue;
		CClassCopyBuilder *copy = dynamic_cast<CClassCopyBuilder *>(cpy);
		copy->composite = this;
		ASSERT(copy);
		parts.AddTail(copy);
	}
	id = CComponent::GetID();
}

CString CCompositeClass::GetName()
{
	return cls ? cls->GetName() : "";
}

void CCompositeClass::FindSubClasses(CBuilderObjectList &triangles)
{
	POSITION pos = triangles.GetHeadPosition();
	while(pos) {
		CBuilderObject *triangle = triangles.GetNext(pos);
		CBuilderObjectList subs;
		triangle->GetOutConnectedObjects("Sub",subs);
		RegisterSubClasses(subs);
	}
}

void CCompositeClass::FindSubClasses()
{
	POSITION pos = parts.GetHeadPosition();
	while(pos) {
		CClassBase *part = parts.GetNext(pos);
		CBuilderObjectList triangles;
		part->builder->GetOutConnectedObjects("Base",triangles);
		FindSubClasses(triangles);
	}
}

void CCompositeClass::RegisterSubClasses(CBuilderObjectList &subs)
{
	POSITION pos = subs.GetHeadPosition();
	while(pos) {
		CBuilderObject *obj = subs.GetNext(pos);
		CClassBase *subClass = dynamic_cast<CClassBase *>(obj);
		if(subClass == 0)
			AfxMessageBox("Unexpected subclass " + obj->GetName() + " of " + GetName(),MB_OK | MB_ICONSTOP);
		else {
			subClass->composite->AddBaseClass(this);
			AddSubClass(subClass->composite);
		}
	}
}

void CCompositeClass::AddSubClass(CCompositeClass *sub)
{
	if(!subClasses.Find(sub))
		subClasses.AddTail(sub);
}

void CCompositeClass::AddBaseClass(CCompositeClass *base)
{
	if(!baseClasses.Find(base))
		baseClasses.AddTail(base);
}

bool CCompositeClass::CheckInheritance(CStringList &trace)
{
	if(flag) {
		flag = false;
		return false;
	}
	flag = true;
	trace.AddTail(GetName());

	POSITION pos = subClasses.GetHeadPosition();
	while(pos) {
		if(!subClasses.GetNext(pos)->CheckInheritance(trace)) {
			flag = false;
			return false;
		}
	}

	trace.RemoveTail();
	flag = false;
	return true;
}

void CCompositeClass::DumpInheritance()
{
	POSITION pos = baseClasses.GetHeadPosition();
	while(pos)
		AfxMessageBox("Base class of " + GetName() + " is " + baseClasses.GetNext(pos)->GetName());
}

void CCompositeClass::BuildCompositions()
{
	POSITION pos = parts.GetHeadPosition();
	while(pos) {
		CClassBase *part = parts.GetNext(pos);
		const CBuilderConnectionList *conns= part->builder->GetInConnections("Composition");

		CString name = GetName();

		if(conns) {
			POSITION cpos = conns->GetHeadPosition();
			while(cpos) {
				CBuilderConnection *conn = conns->GetNext(cpos);
				CCompositionBuilder *composition = dynamic_cast<CCompositionBuilder *>(conn);
				ASSERT(composition);
				composition->parent.cls = this;
				CClassBase *src = dynamic_cast<CClassBase *>(composition->GetSource());
				ASSERT(src);
				composition->child.cls = src->composite;
				if(!FindEquivalentComposition(composition)) {
					parentCompositions.AddTail(composition);
					composition->child.cls->childCompositions.AddTail(composition);
					CComponent::theInstance->AddComposition(composition);
				}
			}
		}
	}
}

CCompositionBuilder *CCompositeClass::FindEquivalentComposition(CCompositionBuilder *composition)
{
	POSITION pos = parentCompositions.GetHeadPosition();
	while(pos) {
		CCompositionBuilder *candidate = parentCompositions.GetNext(pos);
		if(candidate->child.cls == composition->child.cls &&
				candidate->child.name == composition->child.name)
			return candidate;
	}
	return 0;
};

void CCompositeClass::BuildIsoAssociations()
{
	POSITION pos = parts.GetHeadPosition();
	while(pos) 
	{
		CClassBase *part = parts.GetNext(pos);
		CBuilderObjectList connectors;

//		AfxMessageBox(CString("Part name:") + part->GetComposite()->GetName());
		part->builder->GetOutConnectedObjects("Src",connectors);
/*		char tmp[30];
		CClassBuilder * ccbl = dynamic_cast<CClassBuilder *>(part);
		if (ccbl) AfxMessageBox("ccbl is a CClassBuilder.");
*/		
		CClassCopyBuilder * cccbl = dynamic_cast<CClassCopyBuilder *>(part);
//		if (cccbl) AfxMessageBox("cccbl is a CClassCopyBuilder.");
		//if (cccbl && (cccbl->GetFolder() != cls->GetFolder()))
		//if (cccbl && (cccbl->GetParent()->GetParent() != cls->GetParent()->GetParent() ))
		if (cccbl && (cccbl->GetPackage() != cls->GetPackage() ))
		{
//			it is a cross-package link ...
//			AfxMessageBox("....in different folder!");
			continue; 
		}
//		sprintf(tmp,"%d", connectors.GetCount());
//		AfxMessageBox(CString("number of connectors:") + tmp);
		POSITION cpos = connectors.GetHeadPosition();
		while(cpos) 
		{
			CAssociationBuilder *connector = dynamic_cast<CAssociationBuilder *>(connectors.GetNext(cpos));
			CBuilderObjectList dstList;
			connector->GetOutConnectedObjects("Dst",dstList);
			if(dstList.IsEmpty())
				AfxMessageBox("Partially specified association for class " + GetName());
			else if(dstList.GetCount() > 1)
				AfxMessageBox("Overspecified association for class " + GetName());
			else 
			{
				CClassBase *dst = dynamic_cast<CClassBase *>(dstList.GetHead());

				ASSERT(dst);
				if (dst->composite) RegisterAssociation(connector,dst->composite);
			}
		}
		const CBuilderConnectionList *directs = part->builder->GetOutConnections("Association");
		if(directs) {
			cpos = directs->GetHeadPosition();
			while(cpos) {
				CDirectAssociationBuilder *direct = dynamic_cast<CDirectAssociationBuilder *>(directs->GetNext(cpos));
				ASSERT(direct);
				CClassBase *dst = dynamic_cast<CClassBase *>(direct->GetDestination());
				ASSERT(dst);
				if (dst->composite) RegisterAssociation(direct,dst->composite);
			}
		}
	}

};

void CCompositeClass::BuildAssociations()
{
	POSITION pos = parts.GetHeadPosition();
	while(pos) 
	{
		CClassBase *part = parts.GetNext(pos);
		CBuilderObjectList connectors;
		part->builder->GetOutConnectedObjects("Src",connectors);
		POSITION cpos = connectors.GetHeadPosition();
		while(cpos) 
		{
			CAssociationBuilder *connector = dynamic_cast<CAssociationBuilder *>(connectors.GetNext(cpos));
			CBuilderObjectList dstList;
			connector->GetOutConnectedObjects("Dst",dstList);
			if(dstList.IsEmpty())
				AfxMessageBox("Partially specified association for class " + GetName());
			else if(dstList.GetCount() > 1)
				AfxMessageBox("Overspecified association for class " + GetName());
			else 
			{
				CClassBase *dst = dynamic_cast<CClassBase *>(dstList.GetHead());

				ASSERT(dst);
				if (dst->composite) RegisterAssociation(connector,dst->composite);
			}
		}
		const CBuilderConnectionList *directs = part->builder->GetOutConnections("Association");
		if(directs) {
			cpos = directs->GetHeadPosition();
			while(cpos) {
				CDirectAssociationBuilder *direct = dynamic_cast<CDirectAssociationBuilder *>(directs->GetNext(cpos));
				ASSERT(direct);
				CClassBase *dst = dynamic_cast<CClassBase *>(direct->GetDestination());
				ASSERT(dst);
				if (dst->composite) RegisterAssociation(direct,dst->composite);
			}
		}
	}
}

void CCompositeClass::RegisterAssociation(CAssociationBase *assoc,CCompositeClass *dst)
{
	assoc->SetSourceAndDestination(this,dst);
	assoc->SetRolesAndCardinalities();
	POSITION pos = srcAssociations.GetHeadPosition();
	while(pos) {
		CAssociationBase *ass = srcAssociations.GetNext(pos);
		if(assoc->IsEquivalent(ass))
			return;
	}
	srcAssociations.AddTail(assoc);
	dst->dstAssociations.AddTail(assoc);
	CComponent::theInstance->AddAssociation(assoc);
}

bool CCompositeClass::IsAbstract()
{
	POSITION pos = parts.GetHeadPosition();
	while(pos) {
		CBuilderObject *part = parts.GetNext(pos)->builder;
		bool abstract;
		part->GetAttribute("IsAbstract",abstract);
		if(abstract)
			return true;
	}
	return false;
}
bool CCompositeClass::IsCrossClass()
{
	bool cross_package = false;

	cross_package = association && (association->IsCrossPackage());

	POSITION pos = dstAssociations.GetHeadPosition();

	while (!cross_package && pos)
		cross_package = dstAssociations.GetNext(pos)->IsCrossPackage();

	pos = srcAssociations.GetHeadPosition();
	while (!cross_package && pos)
		cross_package = srcAssociations.GetNext(pos)->IsCrossPackage();


	pos = baseClasses.GetHeadPosition();
	while (!cross_package && pos)
		cross_package = baseClasses.GetNext(pos)->IsCrossClass();

	return cross_package;


};

bool CCompositeClass::DumpCrossXML(std::strstream &xml, CString& role_id)
{
	/*
	bool cross_package = false;

	cross_package = association && (association->IsCrossPackage());

	POSITION pos = dstAssociations.GetHeadPosition();

	while (!cross_package && pos)
		cross_package = dstAssociations.GetNext(pos)->IsCrossPackage();

	pos = srcAssociations.GetHeadPosition();
	while (!cross_package && pos)
		cross_package = srcAssociations.GetNext(pos)->IsCrossPackage();
*/
	bool cross_package = IsCrossClass();

	if(!cross_package) return false;

	bool has_base = false;

	if (!baseClasses.IsEmpty())
	{
		//we only care about baseclasses when this class actually inherits a cross-package association
		//so we simply check if any of the baseclasses is part of a cross-package association
		POSITION bc_pos = baseClasses.GetHeadPosition();
		while (!has_base && bc_pos)
		{
			CCompositeClass * cccl = baseClasses.GetNext(bc_pos);
			has_base = cccl->IsCrossClass();
		};
	}

	//bool has_base = !baseClasses.IsEmpty();

	CString PHname = "__udm_ph_";
	PHname += GetName();
	PHname += "_from_";
	//PHname += cls->GetFolder()->GetName();
	//PHname += cls->GetParent()->GetParent()->GetName();
	PHname += cls->GetPackage()->GetName();
	CString cls_ns = cls->GetClassDiagram()->GetNamespace();

	//CString class_ph_name = GetName() + CString("_cross_ph_") + cls->GetFolder()->GetName();
	//CString class_ph_name = GetName() + CString("_cross_ph_") + cls->GetParent()->GetParent()->GetName();
	//CString class_ph_name = GetName() + CString("_cross_ph_") + cls->GetPackage()->GetName();
	//CString class_ph_name = GetName() + CString("_cross_ph_") + cls->GetPackage()->GetName() + CString("_cross_ns_") + cls->GetClassDiagram()->GetNamespace();
	CString class_ph_name = GetName() + CString("_cross_ph_") + cls_ns;
	//--//CString class_ph_name = GetName();

	// if it's a derived class, no composition is generated - it uses the base's composition */
	if (has_base)
		xml << "<Class _id=\"" << (LPCTSTR) id << "\" name= \"" << (LPCTSTR)class_ph_name << "\" " << " isAbstract= \"false\" " ;
	else
		xml << "<Class _id=\"" << (LPCTSTR) id << "\" name= \"" << (LPCTSTR)class_ph_name << "\" " << " isAbstract= \"false\" childRoles=\"" << (LPCTSTR)role_id << "\"" ;

	if(association && association->IsCrossPackage())
		xml << " association = \"" << (LPCTSTR) association->GetID() << "\"";

	if(has_base) {
		xml << " baseTypes= \"";
		POSITION pos = baseClasses.GetHeadPosition();
		/*
			Multiple inheritence bug: Only base-classes which are CrossClasses (or inherited from cross-classes)
			should be listed here, because for the other ones no placeholders classes are generated.

			Although we sure that at least one such class will exist once has_base is true ...
		*/
		while(pos)
		{
			CCompositeClass * cccl = baseClasses.GetNext(pos);
			if (cccl->IsCrossClass())
				xml << " " << (LPCTSTR) cccl->id;
		}
		xml << "\" ";
	}
	if(!subClasses.IsEmpty()) {
		xml << " subTypes= \"";
		POSITION pos = subClasses.GetHeadPosition();
		while(pos)
			xml << " " << (LPCTSTR) subClasses.GetNext(pos)->id;
		xml << "\" ";
	}


	if(!srcAssociations.IsEmpty() || !dstAssociations.IsEmpty()) 
	{
		POSITION pos;
		pos = srcAssociations.GetHeadPosition();
		bool ar_needed = false;
		while (pos && !ar_needed)
		{
			ar_needed = srcAssociations.GetNext(pos)->IsCrossPackage();
		}

		pos = dstAssociations.GetHeadPosition();
		while (pos && !ar_needed)
			ar_needed = dstAssociations.GetNext(pos)->IsCrossPackage();


		if (ar_needed)
		{
			xml << " associationRoles= \"";
			
			
			pos = srcAssociations.GetHeadPosition();
			while(pos)
			{
				CAssociationBase * cab =srcAssociations.GetNext(pos);
				if (cab->IsCrossPackage())
					xml << " " << (LPCTSTR) cab->GetSrcRoleID(this);
			}
			pos = dstAssociations.GetHeadPosition();
			while(pos)
			{
				CAssociationBase * cab =dstAssociations.GetNext(pos);
				if (cab->IsCrossPackage())
					xml << " " << (LPCTSTR) cab->GetDstRoleID(this);
			}
			xml << "\" ";
		}
	}

	//xml << " from=\"" << (LPCTSTR)cls->GetFolder()->GetName() <<"\" >" << std::endl;
	//xml << " from=\"" << (LPCTSTR)cls->GetParent()->GetParent()->GetName() <<"\" >" << std::endl;
	xml << " from=\"" << (LPCTSTR)(cls->GetPackage()->GetName());
	if (cls_ns.GetLength())
		xml << ":" << (LPCTSTR)cls_ns;
	xml << "\" >" << std::endl;
	
	if (!has_base)
	{
		//the base class already has these attributes defined
		xml << "\t<Attribute name=\"rem_sysname\" type=\"String\" min=\"1\" max=\"1\" />" << std::endl;
		xml << "\t<Attribute name=\"rem_id\" type=\"Integer\" min=\"1\" max=\"1\"/>" << std::endl;
	}
	xml << "</Class>" << std::endl;

	role_id = id;	//the caller needs this

	return !has_base;	//if it has a base class, it's not necesary to generate another containment

}

void CCompositeClass::DumpXML(std::strstream &xml, const CString& ns)
{
	if (ns.Compare ( BUILDER_CAST(CClassDiagramBuilder,cls->builder->GetParent())->GetNamespace())) return;

	xml << "<Class _id=\"" << (LPCTSTR) id << "\" name= \"" << (LPCTSTR)GetName() << "\" ";
	if(!cls->stereotype.IsEmpty())
		xml << "stereotype= \"" << (LPCTSTR)  cls->stereotype << "\" ";
	xml << "isAbstract= \"" << (IsAbstract() ? "true" : "false") << "\" ";
	if(!baseClasses.IsEmpty()) {
		xml << "baseTypes= \"";
		POSITION pos = baseClasses.GetHeadPosition();
		while(pos)
			xml << " " << (LPCTSTR) baseClasses.GetNext(pos)->id;
		xml << "\" ";
	}
	if(!subClasses.IsEmpty()) {
		xml << "subTypes= \"";
		POSITION pos = subClasses.GetHeadPosition();
		while(pos)
			xml << " " << (LPCTSTR) subClasses.GetNext(pos)->id;
		xml << "\" ";
	}

	if(!srcAssociations.IsEmpty() || !dstAssociations.IsEmpty()) 
	{
		POSITION pos = srcAssociations.GetHeadPosition();
		bool are_assocs = false;
		while (pos && !are_assocs)
		{
			CAssociationBase * cab = srcAssociations.GetNext(pos);
			if (!(cab->IsCrossPackage())) are_assocs = true;
		}

		pos = dstAssociations.GetHeadPosition();
		while (pos && !are_assocs)
		{
			CAssociationBase * cab = dstAssociations.GetNext(pos);
			if (!(cab->IsCrossPackage())) are_assocs = true;
		}


	
		if (are_assocs)
		{
			xml << "associationRoles= \"";
			pos = srcAssociations.GetHeadPosition();
			while(pos)
			{
				CAssociationBase * cab = srcAssociations.GetNext(pos);
				if (!(cab->IsCrossPackage()))
					xml << " " << (LPCTSTR) cab->GetSrcRoleID(this);
			}
		

			pos = dstAssociations.GetHeadPosition();
			while(pos)
			{
				CAssociationBase * cab = dstAssociations.GetNext(pos);
				if (!(cab->IsCrossPackage()))
					xml << " " << (LPCTSTR) cab->GetDstRoleID(this);
			}
			xml << "\" ";
		}
	}
	if(!parentCompositions.IsEmpty()) {
		xml << "parentRoles= \"";
		POSITION pos = parentCompositions.GetHeadPosition();
		while(pos)
			xml << " " << (LPCTSTR) parentCompositions.GetNext(pos)->GetParentRoleID();
		xml << "\" ";
	}
	if(!childCompositions.IsEmpty()) {
		xml << "childRoles= \"";
		POSITION pos = childCompositions.GetHeadPosition();
		while(pos)
			xml << " " << (LPCTSTR) childCompositions.GetNext(pos)->GetChildRoleID();
		xml << "\" ";
	}
	if(association)
		xml << " association = \"" << (LPCTSTR) association->GetID() << "\"";

	xml << ">" << std::endl;

	ASSERT(cls);

	//Dump out the attributes
	std::vector<AttributeObject>::iterator aoi = cls->attributes.begin();
	while (aoi != cls->attributes.end())
		*aoi++ >> xml;


	//Dump the constraints, if any
	const CBuilderConnectionList *  constraints = cls->GetInConnections("HasConstraint");

	POSITION mPos = constraints->GetHeadPosition();
	while (mPos)
		//this line should not fail. The paradigm allows only constraint source
		//for HasConstraint type connection
		*BUILDER_CAST(CConstraintBuilder, constraints->GetNext(mPos)->GetSource()) >> xml;

	//Dump the constraintDefinitions, if any
	const CBuilderConnectionList *  constraintdefs = cls->GetInConnections("HasDefinition");
	POSITION cdPos = constraintdefs->GetHeadPosition();
	while (cdPos)
		//this line should not fail. The paradigm allows only constraint source
		//for HasConstraint type connection
		*BUILDER_CAST(CConstraintDefinitionBuilder, constraintdefs->GetNext(cdPos)->GetSource()) >> xml;

	//End of the class definition
	xml << "</Class>" << std::endl;
}

////////////////////////////////// CRole //////////////////////////////////////

////////////////////////////////// CRole //////////////////////////////////////

CRole::CRole() : cls(0), minc(1), maxc(1)
{
	id = CComponent::GetID();
}

void CRole::ParseCardinality()
{
	//Invoke ANTLR to parse the cardinality string
	try
	{
		CardinalityObject c_obj((LPCTSTR)cardinality);
		minc = c_obj.getmin();
		maxc = c_obj.getmax();

	}
	catch(const CardinalityObjectException &e)
	{
		AfxMessageBox(CString("Parser error occured while parsing cardinality string: ") + e.what());
	}

};
/////////////////////////////// CClassBuilder /////////////////////////////////

IMPLEMENT_CUSTOMATOM(CClassBuilder, CBuilderAtom, "Class")

void CClassBuilder::Initialize()
{
	CBuilderAtom::Initialize();
	builder = this;
	GetAttribute("Stereotype",stereotype);
	GetUMLAttributes();

}

void CClassBuilder::GetConstraints()
{

};

void CClassBuilder::GetConstraintDefinitions()
{

};

CPackageBuilder * CClassBuilder::GetPackage()
{
    CPackageBuilder * package;
	const CBuilderModel * parent = GetParent();
	while (parent && parent->GetKindName() != "Package")
		parent = parent->GetParent();
	package = BUILDER_CAST(CPackageBuilder, parent);
	ASSERT(package);
	return package;

};

CClassDiagramBuilder * CClassBuilder::GetClassDiagram()
{
	CClassDiagramBuilder * cd = BUILDER_CAST(CClassDiagramBuilder, GetParent());
	ASSERT(cd);
	return cd;
};



void CClassBuilder::GetUMLAttributes()
{
	CString str_attributes;

	GetAttribute("Attributes",str_attributes);
	str_attributes.Trim();
	char buf[4096];
	char *string = buf;
	strcpy(string,(LPCSTR)str_attributes);
	const char * endbuf = buf + strlen(buf);
	char seps[16];
	sprintf(seps,"%c\n",13);
	char *token;

	token = strtok(string,seps);
	while(token)
	{

		try
		{
			//antlr will do the parsing
			AttributeObject curr_atto(token);
			attributes.push_back(curr_atto);
		}

		//catch any parsing exceptions
		catch (AttributeObjectException &e)
		{
			AfxMessageBox(CString("Attribute Object Exception: ") + e.what());
		}

		//step to the next token
		string = token + strlen(token) + 1;

		//(if there is one)
		if (string > endbuf) string = 0;

		//get the next token
		token = strtok(string,seps);
	}
}

///////////////////////////// CClassCopyBuilder ///////////////////////////////

IMPLEMENT_CUSTOMATOMREF(CClassCopyBuilder, CBuilderAtomReference, "ClassCopy")

void CClassCopyBuilder::Initialize()
{
	CBuilderAtomReference::Initialize();
	builder = this;
}

CPackageBuilder * CClassCopyBuilder::GetPackage()
{
    CPackageBuilder * package;
	const CBuilderModel * parent = GetParent();
	while (parent && parent->GetKindName() != "Package")
		parent = parent->GetParent();
	package = BUILDER_CAST(CPackageBuilder, parent);
	ASSERT(package);
	return package;

};


///////////////////////////// CCompositionBuilder ///////////////////////////////

IMPLEMENT_CUSTOMCONNECTION(CCompositionBuilder, CBuilderConnection, "Composition")

void CCompositionBuilder::Initialize()
{
	CBuilderConnection::Initialize();
	GetAttribute("ChildRole",child.name);
	GetAttribute("ParentRole",parent.name);
	GetAttribute("Cardinality",child.cardinality);
	child.ParseCardinality();
}

CString CCompositionBuilder::GetParentRoleID()
{
	return parent.id;
};

CString CCompositionBuilder::GetChildRoleID()
{
	return child.id;

};

/*
	//-- removed, unable to handle self-contained objects,
	//	06/03/02
CString CCompositionBuilder::GetRoleID(CCompositeClass *cls)
{
	if(parent.cls == cls)
		return parent.id;
	if(child.cls == cls)
		return child.id;
	ASSERT(false);
	return "-1";
}*/

void CCompositionBuilder::DumpXML(std::strstream &xml, const CString& ns)
{
	if (ns.Compare(BUILDER_CAST(CClassDiagramBuilder, GetParent())->GetNamespace())) return;

	CString childName = child.name;
	CString parentName = parent.name;
	CString nm = GetName();
	if(nm == "Composition")
		nm.Empty();

	xml << "<Composition";
	if(!nm.IsEmpty())
		xml << " name= \"" << (LPCTSTR) nm << "\"";
	xml << ">" << std::endl;


	xml << "   <CompositionChildRole _id= \"" << (LPCTSTR) child.id << "\"";
	if(!child.name.IsEmpty())
		xml << " name= \"" << (LPCTSTR) child.name << "\"";
	xml << " min= \"" << child.minc << "\" max= \"" << child.maxc << "\" target= \"" << (LPCTSTR) child.cls->GetID() << "\"/>" << std::endl;

	xml << "   <CompositionParentRole _id= \"" << (LPCTSTR) parent.id << "\"";
	if(!parent.name.IsEmpty())
		xml << " name= \"" << (LPCTSTR) parent.name << "\"";
	xml << " target= \"" << (LPCTSTR) parent.cls->GetID() << "\"/>" << std::endl;




	xml << "</Composition>" << std::endl;
}

//////////////////////////////// CAssociationBase /////////////////////////////////

CAssociationBase::CAssociationBase() : associationClass(0)
{
	id = CComponent::GetID();
}
bool CAssociationBase::IsCrossPackage()
{

	if (dest.cls->cls->GetPackage() != source.cls->cls->GetPackage()) return true;

	//at this time dest and source for sure are in the same package

	//return associationClass ? (associationClass->cls->GetPackage() != source.cls->cls->GetPackage()) : false;
	if (associationClass  && (associationClass->cls->GetPackage() != source.cls->cls->GetPackage()) ) return true;
	//at this time dest and source and assoc class are in the same package.
	//or there is no assoc, and dest and source are in the same package



	const CPackageBuilder * owner_package;
	if (associationClass)
	{
		//there is an assoc class,
		//so this is really  a CAssociationBuilder
		const CAssociationBuilder * cab =  (CAssociationBuilder *)this;
		owner_package = BUILDER_CAST(CClassDiagramBuilder, cab->GetParent())->GetPackage();
		
	}
	else
	{
		//there isn't an association  class
		//so this is a CDirectConnectionBuilder
		const CDirectAssociationBuilder * cdab =(CDirectAssociationBuilder *) this;
		owner_package = BUILDER_CAST(CClassDiagramBuilder, cdab->GetParent())->GetPackage();

		
	}

	ASSERT(owner_package);
	//we have the package where the connection was drawn.
	//if the connection was drawn in a different package, but the peers are in the same package,
	//the user meant to use the cross link machinery to create temporary links between the objects 
	//of the same datanetwork


	//source and dest  (and assoc class, if there is one) are in the same packagefor sure
	//no need to re-check them, just one.
	if (owner_package != source.cls->cls->GetPackage()) return true;
		



	return false;

};
bool CAssociationBase::IsEquivalent(CAssociationBase *ass)
{
	//if(source.cls != ass->source.cls || dest.cls != ass->dest.cls || association != ass->association)
	if(source.cls != ass->source.cls || dest.cls != ass->dest.cls || association.Compare(ass->association))
		return false;
	//if(source.name != ass->source.name || dest.name != ass->dest.name)
	if(source.name.Compare(ass->source.name ) || dest.name.Compare(ass->dest.name))
		return false;
	if(associationClass && ass->associationClass && associationClass != ass->associationClass)
		AfxMessageBox("Conflicting association classes: "
		+ associationClass->GetName() + " and " + ass->associationClass->GetName());
	return true;
}

CString CAssociationBase::GetSrcRoleID(CCompositeClass *cls)
{
	if(source.cls == cls)
		return source.id;
	ASSERT(false);
	return "-1";
}

CString CAssociationBase::GetDstRoleID(CCompositeClass *cls)
{
	if(dest.cls == cls)
		return dest.id;
	ASSERT(false);
	return "-1";
}

void CAssociationBase::DumpXML(std::strstream &xml, const CString& ns)
{
	if (ns.Compare(BUILDER_CAST(CClassDiagramBuilder, parent_classdgr)->GetNamespace())) return;

	CString srcName = source.name;
	bool src_isnavig = true;
	bool dst_isnavig = true;

	if(srcName.IsEmpty())
	{
		srcName = source.cls->GetName();
		src_isnavig = false;
	}
	CString dstName = dest.name;
	if(dstName.IsEmpty())
	{
		dstName = dest.cls->GetName();
		dst_isnavig = false;
	}
	CString nm = association;
	if(nm == "Association")
		nm.Empty();

	xml << "<Association _id=\"" << (LPCTSTR) id << "\"";
	if(!nm.IsEmpty())
		xml << " name= \"" << (LPCTSTR) nm << "\"";
	if(associationClass)
		xml << " assocClass = \"" << (LPCTSTR) associationClass->GetID() << "\"";
	xml << ">" << std::endl;

	xml << "   <AssociationRole _id= \"" << (LPCTSTR) source.id << "\" name= \"" << (LPCTSTR) srcName;
	xml << "\" min= \"" << source.minc << "\" max= \"" << source.maxc << "\" target= \"" << (LPCTSTR) source.cls->GetID() << "\"" << " isNavigable=\"" << (src_isnavig ? "true" : "false" ) << "\" />" << std::endl;
	xml << "   <AssociationRole _id= \"" << (LPCTSTR) dest.id << "\" name= \"" << (LPCTSTR) dstName;
	xml << "\" min= \"" << dest.minc << "\" max= \"" << dest.maxc << "\" target= \"" << (LPCTSTR) dest.cls->GetID() << "\"" << " isNavigable=\"" << (dst_isnavig ? "true" : "false") << "\" />" << std::endl;
	xml << "</Association>" << std::endl;
}

///////////////////////////// CDirectAssociationBuilder ///////////////////////////////

IMPLEMENT_CUSTOMCONNECTION(CDirectAssociationBuilder, CBuilderConnection, "Association")

void CDirectAssociationBuilder::Initialize()
{
	CBuilderConnection::Initialize();
	parent_classdgr = GetParent();

}

void CDirectAssociationBuilder::SetSourceAndDestination(CCompositeClass *s,CCompositeClass *d)
{
	source.cls = s;
	dest.cls = d;
	associationClass = 0;
	association = name;
}

void CDirectAssociationBuilder::SetRolesAndCardinalities()
{
	GetAttribute("srcRolename",source.name);
	GetAttribute("srcCardinality",source.cardinality);
	source.ParseCardinality();
	GetAttribute("dstRolename",dest.name);
	GetAttribute("dstCardinality",dest.cardinality);
	dest.ParseCardinality();
}

/////////////////////////////// CAssociationBuilder ///////////////////////////////

IMPLEMENT_CUSTOMATOM(CAssociationBuilder, CBuilderAtom, "Connector")

void CAssociationBuilder::Initialize()
{
	CBuilderAtom::Initialize();
	parent_classdgr = GetParent();
}

void CAssociationBuilder::SetSourceAndDestination(CCompositeClass *s,CCompositeClass *d)
{
	source.cls = s;
	dest.cls = d;
	CBuilderObjectList assClasses;
	GetOutConnectedObjects("AssociationClass",assClasses);
	GetInConnectedObjects("AssociationClass",assClasses);
	if(assClasses.GetCount() > 1)
		AfxMessageBox("Multiple association classes defined for association!");
	else if(!assClasses.IsEmpty()) {
		CClassBase *cls = dynamic_cast<CClassBase *>(assClasses.GetHead());
		ASSERT(cls);
		associationClass = cls->GetComposite();
		associationClass->SetAssociation(this);
		association = associationClass->GetName();
	}
}

void CAssociationBuilder::SetRolesAndCardinalities()
{
	const CBuilderConnectionList *srcs = GetInConnections("Src");
	if(srcs == 0 || srcs->GetCount() != 1)
		AfxMessageBox("Invalid source specification for association " + association);
	else {
		CBuilderObject *obj = srcs->GetHead();
		obj->GetAttribute("Cardinality",source.cardinality);
		source.ParseCardinality();
		obj->GetAttribute("srcRolename",source.name);
	}
	const CBuilderConnectionList *dsts = GetOutConnections("Dst");
	if(dsts == 0 || dsts->GetCount() != 1)
		AfxMessageBox("Invalid destination specification for association " + association);
	else {
		CBuilderObject *obj = dsts->GetHead();
		obj->GetAttribute("Cardinality",dest.cardinality);
		dest.ParseCardinality();
		obj->GetAttribute("dstRolename",dest.name);
	}
}

//////////////////////////////CConstraintBuilder//////////////////////////////

IMPLEMENT_CUSTOMATOM(CConstraintBuilder, CBuilderAtom, "Constraint")

void CConstraintBuilder::Initialize()
{
	CBuilderAtom::Initialize();
	GetAttribute("ConstraintDescription", desc);
	GetAttribute("ConstraintEqn", expr);
	expr.Replace( "&" , "&amp;" );
	expr.Replace( "\n" , "\\n" );
	expr.Replace( "\r" , "\\r" );
	expr.Replace( "\"" , "\\&quot;" );
	expr.Replace( "<" , "&lt;" );
	expr.Replace( ">" , "&gt;" );
};

std::strstream& CConstraintBuilder::operator >>(std::strstream& out)
{
	out << "   <Constraint name=\"" << (LPCTSTR)GetName() << "\" description=\""
	<< (LPCTSTR)desc << "\" expression=\"" << (LPCTSTR)expr << "\"/>" <<std::endl;
	return out;
};

//////////////////////////////CConstraintDefinitionBuilder//////////////////////////////

IMPLEMENT_CUSTOMATOM(CConstraintDefinitionBuilder, CBuilderAtom, "ConstraintDefinition")

void CConstraintDefinitionBuilder::Initialize()
{
	CBuilderAtom::Initialize();

	GetAttribute( "DefinitionEqn", expr );
	expr.Replace( "&" , "&amp;" );
	expr.Replace( "\n" , "\\n" );
	expr.Replace( "\r" , "\\r" );
	expr.Replace( "\"" , "\\&quot;" );
	expr.Replace( "<" , "&lt;" );
	expr.Replace( ">" , "&gt;" );
	
	CString sStereo;
	GetAttribute( "DefinitionStereo", sStereo );
	stereo = sStereo == "method";

	GetAttribute( "DefinitionRetType", retType );

	GetAttribute( "DefinitionParamList", paramList );
	paramList.Replace( ",", ";" );
};

std::strstream& CConstraintDefinitionBuilder::operator >>(std::strstream& out)
{
	out << "   <ConstraintDefinition name=\"" << (LPCTSTR)GetName() << "\" "
		<< "expression=\"" << (LPCTSTR)expr << "\" "
		<< "stereotype=\"" << ( ( stereo ) ? "method" : "attribute" )<< "\" "
		<< "returnType=\"" << (LPCTSTR)retType << "\" "
		<< "parameterList=\"" << (LPCTSTR)paramList << "\" "
		<< "/>" << std::endl;
	return out;
};


/////////////////////////////////////////////////////////////////////////////////////
// Writing back information to config
/////////////////////////////////////////////////////////////////////////////////////
CString CComponent::GetFilePath(CBuilder &builder, CBuilderObject *focus, char *FILE_EXT, char *UDM_FILTER)
{	CBuilderFolder *root = builder.GetRootFolder();
	IMgaProject *proj = builder.GetProject();
	CComPtr<IMgaMetaProject> mproj;
	COMVERIFY( proj->get_RootMeta(&mproj));
	CBstr pn;
	COMVERIFY( mproj->get_Name(pn) );
	CString paradigmName = pn;
	if(paradigmName  == "UMLModelTransformer")
	{	isUMT = true;
		CBuilderFolder *root = builder.GetRootFolder();
		const CBuilderFolderList *subfolders = root->GetSubFolders();
		CBuilderModel *theCfg;
		if(focus != NULL && focus->GetKindName() == "Configuration")
			theCfg = BUILDER_CAST(CBuilderModel, focus);
		else
		{	POSITION spos = subfolders->GetHeadPosition();
			CBuilderModelList configs;
			while(spos)
			{
				CBuilderFolder *subfolder = subfolders->GetNext(spos);
				if(subfolder->GetKindName() != "Configurations")
					continue;
				
				const CBuilderModelList *cfgs = subfolder->GetRootModels();
				POSITION cmpos = cfgs->GetHeadPosition();
				while(cmpos)
				{
					CBuilderModel *curr_model = cfgs->GetNext(cmpos);
					if ( curr_model->GetKindName() == "Configuration")
						configs.AddTail( curr_model);
				}
			}
			if(configs.GetCount() == 0)
			{	throw int_exception("Uml2Xml Error: No Configuration model found. Use UMT Master Interpreter.");
			}
			else if(configs.GetCount() > 1)
			{	throw int_exception("Uml2Xml Error: More than one Configuration model found. Either Start interpretation from one or delete the others.");
			}
			else
			{	theCfg = configs.GetHead();
			}
		}	

		CBuilderAtom *theMetaIcon;
		const CBuilderAtomList *mis = theCfg->GetAtoms("MetaInformation");
		if(!mis || mis->GetCount() == 0)
			theMetaIcon = theCfg->CreateNewAtom("MetaInformation");
		else
			theMetaIcon = mis->GetHead();
		CString cfgFileName;
		CString cfgDirName;
		theCfg->GetAttribute("ConfigFile",cfgFileName);
		if(cfgFileName == "" || cfgFileName.GetLength() <3 || cfgFileName.GetAt(1) != ':')
		{	throw int_exception("Uml2Xml Error: Config file name is not absolute. Run UMT Master interpreter.");
		}
		
		int p = cfgFileName.ReverseFind('\\');
		cfgDirName = cfgFileName.Left(p+1);
		
		CString transFileName;
		theMetaIcon->GetAttribute("UdmProjectFile",transFileName);
		if(transFileName == "")
		{	throw int_exception("Uml2Xml Error: Udm file is blank. Run UMT Master interpreter.");
		}
		
		CString transFilePath = cfgDirName + transFileName;
		CString transDirName;
		
		p = transFilePath.ReverseFind('\\');
		transDirName = transFilePath.Left(p+1);

		if(CreateDirectory((LPCSTR)transDirName, NULL)==0)
		{	int le = GetLastError();
			if(le != 183)
			{	LPVOID lpMsgBuf;
				FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
								NULL, le, 0, (LPTSTR) &lpMsgBuf, 0, NULL );
				CString msg = "Uml2Xml Error: Unable to create directory " + transDirName + "\n";
				msg += (LPCSTR)lpMsgBuf;
				throw int_exception((LPCSTR)msg);
			}
		}
		SetCurrentDirectory((LPCSTR)transDirName);
		return transFilePath;
	}
	else
	{	//static char UDM_FILTER[] = "XML files (*.xml)|*.xml";
		CFileDialog cfdlg(false, FILE_EXT, root->GetName(), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, UDM_FILTER);	
		cfdlg.m_ofn.lpstrTitle = "UDM Meta File Location";
		if (cfdlg.DoModal() != IDOK) 
		{	throw int_exception("");
		}
		return cfdlg.GetPathName();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
