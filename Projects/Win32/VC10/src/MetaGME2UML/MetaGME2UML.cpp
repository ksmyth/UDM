/*
 *	Copyright (c) Vanderbilt University, 2003-2004
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
 *
 *  FILE NAME:	MetaGME2UML
 *	SYNOPSIS:	Class that converts a MetaGME metamodel to an equivalent UDM compatible UML class diagram
 *  AUTHOR:		Aditya Agrawal - aditya,agrawal@vanderbilt.edu
 *  CREATED:	03/19/03
 *  LAST UPDATE: 
 */

#include "stdafx.h"
//#include <afxdlgs.h> // For CFileDialog

#include "Mga.h"
#include "GME.h"

#include "MetaGME2UML.h"
#include "algorithm"
#include "cctype"
#include "UmlExt.h"

#include "Mga.h"

using namespace std;

bool AskUserForConstraint(long);

void MetaGME2UML::transformMetaGME2UmlGME()
{	
	cout << endl;
	// Phase 1
	//MESSAGE_OUT("Phase 1");
	cout << "Phase 1 - Setting up the sheets .... " << endl;
	Phase1_SetUpSheets();
	// Phase 2
	//MESSAGE_OUT("Phase 2");
	cout << "Phase 2 - Creating Implementation & Interface Inheritance .... " << endl;
	Phase2_CreateImplementationInterfaceInheritances();
	// Phase 3
	//MESSAGE_OUT("Phase 3");
	cout << "Phase 3 - Creating Classes .... " << endl;
	Phase3_CreateClasses();
	// Phase 4
	//MESSAGE_OUT("Phase 4");
	cout << "Phase 4 - Creating ClassCopy .... " << endl;
	Phase4_CreateReferences();
	// Phase 5
	//MESSAGE_OUT("Phase 5");
	cout << "Phase 5 - Creating Associations .... " << endl;
	Phase5_CreateConnections();
	// Phase 6
	//MESSAGE_OUT("Phase 6");
	cout << "Phase 6 - Creating and associating GME Object base .... " << endl;
	Phase6_CreateGMEObject();
	cout << "Done." << endl;
}

void MetaGME2UML::Phase1_SetUpSheets()
{	
	grf = MetaGME::RootFolder::Cast(metaGME.GetRootObject());
	InitializeSheets(grf,urf);

	//We check to see if new paradigm sheets need to go in a namespace or in the top level package
	if(topNamespace == Udm::null)
	{
		SetUpSheets(grf,urf,urf,urf);
	}
	else
	{
		SetUpSheets(grf,urf,topNamespace,urf);
	}
	
}

//Modified this to take two additional parameters:
//1. Where to create any new class diagrams
//2. Where to create any new namespaces

void MetaGME2UML::SetUpSheets(MetaGME::RootFolder grf, Udm::Object urf, Udm::Object cdParent, Udm::Object nsParent)
{
	//For each ParadigmSheet, we need to create a ClassDiagram; where we create this ClassDiagram depends
	//on whether the ParadigmSheet's RootFolder had a NS
	//Case 1: The ParadigmSheet's RootFolder has a NS
	//  -Create the ClassDiagram in the corresponding UML Namespace
	//Case 2: The ParadigmSheet's RootFolder doesn't have a NS
	//  -Create the ClassDiagram in the higher level NS, or possible directly in the top level package

	vector<MetaGME::SheetFolder> sfs = grf.SheetFolder_kind_children();
	for(vector<MetaGME::SheetFolder>::iterator i=sfs.begin(); i!=sfs.end();i++)
	{	MetaGME::SheetFolder sf = *i;
		vector<MetaGME::ParadigmSheet> pss = sf.ParadigmSheet_kind_children();
		for(vector<MetaGME::ParadigmSheet>::iterator j=pss.begin(); j!=pss.end();j++)
		{	MetaGME::ParadigmSheet ps = *j;
			//UmlGME::ClassDiagram cd = UmlGME::ClassDiagram::Create(urf);
			UmlGME::ClassDiagram cd = UmlGME::ClassDiagram::Create(cdParent);
			cd.name() = ps.name();
			cd.position() = ps.position();
			mapMetaGME2UmlGME_Paradigm[ps] = cd;
			SetupEquivalenceMaps(ps, cd);
		}
	}

	vector<MetaGME::ParadigmSheet> pss = grf.ParadigmSheet_kind_children();
	for(vector<MetaGME::ParadigmSheet>::iterator j=pss.begin(); j!=pss.end();j++)
	{	MetaGME::ParadigmSheet ps = *j;
		//UmlGME::ClassDiagram cd = UmlGME::ClassDiagram::Create(urf);
		UmlGME::ClassDiagram cd = UmlGME::ClassDiagram::Create(cdParent);
		cd.name() = ps.name();
		cd.position() = ps.position();
		mapMetaGME2UmlGME_Paradigm[ps] = cd;		
		SetupEquivalenceMaps(ps, cd);
	}

	//this code used to be at the top of this method, but it shouldn't matter when we recurse on the RootFolder children
	//let's do it here so that we have access to the higher level namespace, which we will need for creating the new
	//class diagrams
	vector<MetaGME::RootFolder> rfs = grf.RootFolder_kind_children();
	for(vector<MetaGME::RootFolder>::iterator ri=rfs.begin(); ri!=rfs.end();ri++)
	{
		MetaGME::RootFolder sf = *ri;
		string nsvalue = sf.Namespace();

		//Case 1: This RootFolder has a NS
		//  -Create a NS for it in nsParent and call SetUpSheets
		if(nsvalue != "")
		{
			UmlGME::Namespace currNamespace = UmlGME::Namespace::Create(nsParent);
			currNamespace.name() = nsvalue;
			SetUpSheets(sf, urf, currNamespace, currNamespace);
		}

		else
		{
			SetUpSheets(sf, urf, cdParent, nsParent);
		}

		//Case 2: This RootFolder does not have a NS
		//  -Call SetUpSheets with same parameters
		
		
	}
}

void MetaGME2UML::SetupEquivalenceMaps(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd)
{	
	// Transfering Equivalence association
	{	vector<MetaGME::Equivalence> connects = ps.Equivalence_kind_children();
		for(vector<MetaGME::Equivalence>::iterator i = connects.begin(); i!=connects.end(); i++)
		{	MetaGME::Equivalence contain = *i;
			set<MetaGME::EquivLeft> basecs = contain.dstFCO();
			if(basecs.size() == 0)
			{	//Error
				string error = "Error: Equivalence object "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " is not left connected to an FCO";
				throw udm_exception(error);
			}
			if(basecs.size() > 1)
			{	//Error
				string error = "Error: Equivalence object "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " is left connected to more than one FCO";
				throw udm_exception(error);
			}
			MetaGME::EquivLeft basec = *(basecs.begin());
			MetaGME::BaseFCO base = basec.dstFCO_end();
			
			set<MetaGME::EquivRight> derivedcs = contain.srcFCO();
			if(derivedcs.size() == 0)
			{	//Error
				string error = "Error: Equivalence object "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " is not right connected to an FCO";
				throw udm_exception(error);
			}
			if(derivedcs.size() > 1)
			{	//Error
				string error = "Error: Equivalence object "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " is right connected to more than one FCO";
				throw udm_exception(error);
			}
			MetaGME::EquivRight derivedc = *(derivedcs.begin());
			MetaGME::BaseFCO derived = derivedc.srcFCO_end();

			AddEquivalence(derived, base);
		}
	}

	// Transfering Folder Equivalence association
	{
		vector<MetaGME::SameFolder> connects = ps.SameFolder_kind_children();
		for(vector<MetaGME::SameFolder>::iterator i = connects.begin(); i!=connects.end(); i++)
		{	MetaGME::SameFolder contain = *i;
			set<MetaGME::SameFolderLeft> basecs = contain.dstFolder();
			if(basecs.size() == 0)
			{	//Error
				string error = "Error: SameFolder object "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " is not left connected to an Folder";
				throw udm_exception(error);
			}
			if(basecs.size() > 1)
			{	//Error
				string error = "Error: SameFolder object "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " is left connected to more than one Folder";
				throw udm_exception(error);
			}
			MetaGME::SameFolderLeft basec = *(basecs.begin());
			MetaGME::BaseFolder base = basec.dstFolder_end();
			
			set<MetaGME::SameFolderRight> derivedcs = contain.srcFolder();
			if(derivedcs.size() == 0)
			{	//Error
				string error = "Error: SameFolder object "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " is not right connected to an Folder";
				throw udm_exception(error);
			}
			if(derivedcs.size() > 1)
			{	//Error
				string error = "Error: SameFolder object "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " is right connected to more than one Folder";
				throw udm_exception(error);
			}
			MetaGME::SameFolderRight derivedc = *(derivedcs.begin());
			MetaGME::BaseFolder derived = derivedc.srcFolder_end();
			
			AddEquivalence(derived, base);
			
		}
	}
}

void MetaGME2UML::AddEquivalence(MetaGME::ContainedInPar ms, MetaGME::ContainedInPar sl)
{
	MetaGME::ContainedInPar master = GetRefMetaGMEObject(ms);
	MetaGME::ContainedInPar slave  = GetRefMetaGMEObject(sl);

	MetaGME::ContainedInPar newslave;

	//string sn = slave.name();
	//string mn = master.name();

	// for the case where the same object O is to the left of 2 equivalence relations;
	while(equivMap.find(slave) != equivMap.end())
	{	newslave = master;
		master = equivMap[slave];
		slave = newslave;
		//sn = slave.name();
		//mn = master.name();
	}
	if(equivMap.find(master) == equivMap.end())
	{	equivMap[slave] = master;
		// search for slave in Map value and replace with master
		vector<MetaGME::ContainedInPar> fcos;
		for(map_CIP2CIP::iterator emi=equivMap.begin(); emi!=equivMap.end(); emi++)
		{	if( (*emi).second == slave)
				fcos.push_back((*emi).first);
		}
		for(vector<MetaGME::ContainedInPar>::iterator fi = fcos.begin(); fi!=fcos.end(); fi++)
		{	equivMap[*fi] = master;
		}
	}
	else
	{	equivMap[slave] = equivMap[master];
	}
}

void MetaGME2UML::Phase2_CreateImplementationInterfaceInheritances()
{	
	CreateImplementationInterfaceInheritances(grf,urf);
		
}

void MetaGME2UML::CreateImplementationInterfaceInheritances(MetaGME::RootFolder grf, Udm::Object urf)
{	
	vector<MetaGME::RootFolder> rfs = grf.RootFolder_kind_children();
	for(vector<MetaGME::RootFolder>::iterator ri=rfs.begin(); ri!=rfs.end();ri++)
	{	MetaGME::RootFolder sf = *ri;
		CreateImplementationInterfaceInheritances(sf, urf);
	}
	
	vector<MetaGME::SheetFolder> sfs = grf.SheetFolder_kind_children();
	for(vector<MetaGME::SheetFolder>::iterator i=sfs.begin(); i!=sfs.end();i++)
	{	MetaGME::SheetFolder sf = *i;
		vector<MetaGME::ParadigmSheet> pss = sf.ParadigmSheet_kind_children();
		for(vector<MetaGME::ParadigmSheet>::iterator j=pss.begin(); j!=pss.end();j++)
		{	MetaGME::ParadigmSheet ps = *j;
			UmlGME::ClassDiagram cd = mapMetaGME2UmlGME_Paradigm[ps];
			CreateImplementationInterfaceInheritances(ps,cd);
		}
	}
	
	vector<MetaGME::ParadigmSheet> pss = grf.ParadigmSheet_kind_children();
	for(vector<MetaGME::ParadigmSheet>::iterator j=pss.begin(); j!=pss.end();j++)
	{	MetaGME::ParadigmSheet ps = *j;
		UmlGME::ClassDiagram cd = mapMetaGME2UmlGME_Paradigm[ps];
		CreateImplementationInterfaceInheritances(ps,cd);
	}

}

void MetaGME2UML::CreateImplementationInterfaceInheritances(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd)
{	
	// Transfering Interface and Implementation Inheritance
	{	vector<MetaGME::InterfaceInheritance> connects = ps.InterfaceInheritance_kind_children();
		for(vector<MetaGME::InterfaceInheritance>::iterator i = connects.begin(); i!=connects.end(); i++)
		{	MetaGME::InterfaceInheritance contain = *i;
			set<MetaGME::BaseIntInheritance> basecs = contain.bintsrc();
			if(basecs.size() == 0)
			{	//Error
				string error = "Error: Interface inheritance object "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " is not connected to a base class";
				throw udm_exception(error);
			}
			if(basecs.size() > 1)
			{	//Error
				string error = "Error: Interface inheritance object "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " is not connected to more than one base class";
				throw udm_exception(error);
			}
			MetaGME::BaseIntInheritance basec = *(basecs.begin());
			set<MetaGME::DerivedIntInheritance> derivedcs = contain.dintdst();
			MetaGME::BaseFCO base = basec.bintsrc_end();
			
			base = MetaGME::BaseFCO::Cast(GetRefMetaGMEObject(base));

			//UmlGME::Class cbase = UmlGME::Class::Cast(mapMetaGME2UmlGME_Class[base]);

			for(set<MetaGME::DerivedIntInheritance>::iterator j=derivedcs.begin();j!=derivedcs.end();j++)
			{	MetaGME::DerivedIntInheritance derivedc = *j;
				MetaGME::BaseFCO derived = derivedc.dintdst_end();

				derived = MetaGME::BaseFCO::Cast(GetRefMetaGMEObject(derived));
				
				//UmlGME::Class cderived = UmlGME::Class::Cast(mapMetaGME2UmlGME_Class[derived]);
				MakeImplIntf(base, derived, false, true);

			}
		}
	}

	// Transfering Interface and Implementation Inheritance
	{	vector<MetaGME::ImplementationInheritance> connects = ps.ImplementationInheritance_kind_children();
		for(vector<MetaGME::ImplementationInheritance>::iterator i = connects.begin(); i!=connects.end(); i++)
		{	MetaGME::ImplementationInheritance contain = *i;
			set<MetaGME::BaseImpInheritance> basecs = contain.bimplsrc();
			if(basecs.size() == 0)
			{	//Error
				string error = "Error: Interface inheritance object "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " is not connected to a base class";
				throw udm_exception(error);
			}
			if(basecs.size() > 1)
			{	//Error
				string error = "Error: Interface inheritance object "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " is not connected to more than one base class";
				throw udm_exception(error);
			}
			MetaGME::BaseImpInheritance basec = *(basecs.begin());
			set<MetaGME::DerivedImpInheritance> derivedcs = contain.dimpldst();
			MetaGME::BaseFCO base = basec.bimplsrc_end();
			
			base = MetaGME::BaseFCO::Cast(GetRefMetaGMEObject(base));

			//UmlGME::Class cbase = UmlGME::Class::Cast(mapMetaGME2UmlGME_Class[base]);

			for(set<MetaGME::DerivedImpInheritance>::iterator j=derivedcs.begin();j!=derivedcs.end();j++)
			{	MetaGME::DerivedImpInheritance derivedc = *j;
				MetaGME::BaseFCO derived = derivedc.dimpldst_end();

				derived = MetaGME::BaseFCO::Cast(GetRefMetaGMEObject(derived));
				
				//UmlGME::Class cderived = UmlGME::Class::Cast(mapMetaGME2UmlGME_Class[derived]);
				MakeImplIntf(base, derived, true, false);

			}
		}
	}
}

MetaGME::ContainedInPar MetaGME2UML::GetRefMetaGMEObject(MetaGME::ContainedInPar base)
{	if(base == Udm::null )
	{	//Error
		string error = "Error: Function GetRefMetaGMEObject called with a null object";
		throw udm_exception(error);
	}
	
	Uml::Class basetype = base.type();

//	std::string typeName= basetype.name();
//	std::string name= MetaGME::BaseFCO::Cast( base).name();;

	if(!Udm::IsDerivedFrom(base.type(), MetaGME::ProxyBase::meta) && basetype != MetaGME::FolderProxy::meta)
		return base;

	Uml::Class nullClass( NULL);
	Udm::Object::AssociationInfo refinfo( nullClass);
//	Udm::Object::uniqueId_type uid= refinfo.clsAssociation.uniqueId();

	refinfo.strSrcRoleName = "src";
	refinfo.strDstRoleName = "ref";
	set<Udm::Object> objs = base.GetAdjacentUniqueObjects(MetaGME::ContainedInPar::meta, refinfo);
	if(objs.size() != 1)
	{	//Error
		string basename, sheetname;
		base.GetStrValue("name", basename); sheetname = MetaGME::ParadigmSheet::Cast(base.parent()).name();
		string error = "Error: Object "+ basename + " in ParadigmSheet:" + sheetname + " is a NULL reference";
		throw udm_exception(error);
	}
	return MetaGME::ContainedInPar::Cast(*objs.begin());
}

void MetaGME2UML::MakeIntImplDiagram()
{	if(!umlGMEimplinterfaceDiagram)
	{	umlGMEimplinterfaceDiagram = UmlGME::ClassDiagram::Create(urf);
		umlGMEimplinterfaceDiagram.name() = "zC_Interface_and_Implementation_Inheritance_diagram";
	}
}

template <class TYPE, class PROXY_TYPE>
TYPE getRefByProxy( const MetaGME::BaseFCO& proxy) {
	TYPE refByProxy;
	if ( proxy.type() == PROXY_TYPE::meta) {
		PROXY_TYPE typedProxy= PROXY_TYPE::Cast( proxy);
		refByProxy= typedProxy.ref();
	}
	return refByProxy;
}
MetaGME::BaseFCO RefByProxy( const MetaGME::BaseFCO& fco) {
		MetaGME::Atom ap= getRefByProxy< MetaGME::Atom, MetaGME::AtomProxy>( fco);
		MetaGME::Model mp= getRefByProxy< MetaGME::Model, MetaGME::ModelProxy>( fco);
		MetaGME::FCO fp= getRefByProxy< MetaGME::FCO, MetaGME::FCOProxy>( fco);
		MetaGME::Connection cp= getRefByProxy< MetaGME::Connection, MetaGME::ConnectionProxy>( fco);
		MetaGME::Reference rp= getRefByProxy< MetaGME::Reference, MetaGME::ReferenceProxy>( fco);
		MetaGME::Set sp= getRefByProxy< MetaGME::Set, MetaGME::SetProxy>( fco);
		//const MetaGME::BaseFCO& refByProxy= ( ap!=0) ? ap : ( mp!=0) ? mp : ( fp!=0) ? fp : ( cp!=0) ? cp : ( rp!=0) ? rp : (sp!=0) ? sp :fco;
		const MetaGME::BaseFCO& refByProxy= ( ap!=Udm::null) ? ap : ( mp!=Udm::null) ? mp : ( fp!=Udm::null) ? fp : ( cp!=Udm::null) ? cp : ( rp!=Udm::null) ? rp : (sp!=Udm::null) ? sp :fco;
		return refByProxy;
}

void MetaGME2UML::MakeImplIntf( const MetaGME::BaseFCO& b, const MetaGME::BaseFCO& d, bool impl, bool intf)
{	
	MakeIntImplDiagram();
	MetaGME::BaseFCO base= b;
	MetaGME::BaseFCO derived= d;
	if ( Uml::IsDerivedFrom( base.type(), MetaGME::ProxyBase::meta)) {
		base= RefByProxy( base);
	}
	if ( Uml::IsDerivedFrom( derived.type(), MetaGME::ProxyBase::meta)) {
		derived= RefByProxy( derived);
	}
	UmlGME::Class cbase, cderived;
	GetUMLCounterParts(base, derived, cbase, cderived);

	// Get Base impl and intf
	UmlGME::Class cbaseimpl, cbaseintf;
	UmlGME::Class cbaseref;

	map< UmlGME::ClassBase, pair< UmlGME::Class, UmlGME::Class> >::iterator bfi = mapUmlClass2ImplInheritBases.find(cbase);
//	if ( !Uml::IsDerivedFrom( base.type(), MetaGME::ProxyBase::meta)) 
	{
		if (bfi == mapUmlClass2ImplInheritBases.end()) {
			cbaseimpl = UmlGME::Class::Create(umlGMEimplinterfaceDiagram);
			cbaseimpl.name() = (string)cbase.name() + "ImplementationBase";
			cbaseimpl.position() = MakePosition(iox,ioy,iox,ioy); iox += 250;
			cbaseimpl.IsAbstract() = true;
			
			cbaseintf = UmlGME::Class::Create(umlGMEimplinterfaceDiagram);
			cbaseintf.name() = (string)cbase.name() + "InterfaceBase";
			cbaseintf.position() = MakePosition(iox,ioy,iox,ioy); iox -= 200; ioy += 150;
			cbaseintf.IsAbstract() = true;

			UmlGME::Inheritance cbimplinh = UmlGME::Inheritance::Create(umlGMEimplinterfaceDiagram);
			cbimplinh.position() = MakePosition(iox,ioy,iox,ioy); iox += 250;
			cbimplinh.name() = "";

			UmlGME::Inheritance cbintfinh = UmlGME::Inheritance::Create(umlGMEimplinterfaceDiagram);
			cbintfinh.position() = MakePosition(iox,ioy,iox,ioy); iox -= 175; ioy += 150;
			cbintfinh.name() = "";
			
			cbaseref = cbase;
			cbaseref.position() = MakePosition(iox,ioy,iox,ioy); iox -= 125; ioy += 150;

			UmlGME::Base cbc = UmlGME::Base::Create(umlGMEimplinterfaceDiagram);
			cbc.dstInheritance_end() = cbimplinh;
			cbc.srcClassBase_end() = cbaseimpl;

			UmlGME::Sub csub = UmlGME::Sub::Create(umlGMEimplinterfaceDiagram);
			csub.srcInheritance_end() = cbimplinh;
			csub.dstClassBase_end() = cbaseref;

			cbc = UmlGME::Base::Create(umlGMEimplinterfaceDiagram);
			cbc.dstInheritance_end() = cbintfinh;
			cbc.srcClassBase_end() = cbaseintf;

			csub = UmlGME::Sub::Create(umlGMEimplinterfaceDiagram);
			csub.srcInheritance_end() = cbintfinh;
			csub.dstClassBase_end() = cbaseref;
			
			pair<UmlGME::Class, UmlGME::Class> pr;
			pr.first = cbaseimpl; pr.second = cbaseintf;
			mapUmlClass2ImplInheritBases[cbase] = pr;
		}
		else
		{	cbaseimpl = (*bfi).second.first;
			cbaseintf = (*bfi).second.second;
		}
	}

	// Get Derived impl and intf
	UmlGME::Class cderivedimpl, cderivedintf;
	UmlGME::Class cderivedref;

	map< UmlGME::ClassBase, pair< UmlGME::Class, UmlGME::Class> >::iterator dfi = mapUmlClass2ImplInheritBases.end();
	if ( cderived) {
		dfi= mapUmlClass2ImplInheritBases.find(cderived);
	}
//	if ( !Uml::IsDerivedFrom( derived.type(), MetaGME::ProxyBase::meta))
	{
		if( dfi == mapUmlClass2ImplInheritBases.end()) {
			cderivedimpl = UmlGME::Class::Create(umlGMEimplinterfaceDiagram);
			cderivedimpl.name() = (string)cderived.name() + "ImplementationBase";
			cderivedimpl.position() = MakePosition(iox,ioy,iox,ioy); iox += 250;
			cderivedimpl.IsAbstract() = true;

			cderivedintf = UmlGME::Class::Create(umlGMEimplinterfaceDiagram);
			cderivedintf.name() = (string)cderived.name() + "InterfaceBase";
			cderivedintf.position() = MakePosition(iox,ioy,iox,ioy); iox -= 200; ioy +=150;
			cderivedintf.IsAbstract() = true;

			UmlGME::Inheritance cdimplinh = UmlGME::Inheritance::Create(umlGMEimplinterfaceDiagram);
			cdimplinh.position() = MakePosition(iox,ioy,iox,ioy); iox += 250;
			cdimplinh.name() = "";

			UmlGME::Inheritance cdintfinh = UmlGME::Inheritance::Create(umlGMEimplinterfaceDiagram);
			cdintfinh.position() = MakePosition(iox,ioy,iox,ioy); iox -= 175; ioy += 150;
			cdintfinh.name() = "";

			cderivedref = cderived;
			cderivedref.position() = MakePosition(iox,ioy,iox,ioy); iox -= 125; ioy +=150;

			UmlGME::Base cbc = UmlGME::Base::Create(umlGMEimplinterfaceDiagram);
			cbc.dstInheritance_end() = cdimplinh;
			cbc.srcClassBase_end() = cderivedimpl;

			UmlGME::Sub csub = UmlGME::Sub::Create(umlGMEimplinterfaceDiagram);
			csub.srcInheritance_end() = cdimplinh;
			csub.dstClassBase_end() = cderivedref;

			cbc = UmlGME::Base::Create(umlGMEimplinterfaceDiagram);
			cbc.dstInheritance_end() = cdintfinh;
			cbc.srcClassBase_end() = cderivedintf;

			csub = UmlGME::Sub::Create(umlGMEimplinterfaceDiagram);
			csub.srcInheritance_end() = cdintfinh;
			csub.dstClassBase_end() = cderivedref;
			
			pair<UmlGME::Class, UmlGME::Class> pr;
			pr.first = cderivedimpl; pr.second = cderivedintf;
			mapUmlClass2ImplInheritBases[cderived] = pr;
		}
		else
		{	cderivedimpl = (*dfi).second.first;
			cderivedintf = (*dfi).second.second;
		}
	}

	if(impl && intf && cderived)
	{
		maphasbaseimpl[cderived] = true;
		maphasbaseintf[cderived] = true;
		return;
	}
	if (impl && intf && !cderived) {
		return;
	}
	
	if(impl)
	{	UmlGME::Inheritance cinh = UmlGME::Inheritance::Create(umlGMEimplinterfaceDiagram);
		
		int bx=0, by=0, dx=0, dy=0;
		GetPosAttr((string)cbaseimpl.position(), "UML", bx, by);
		GetPosAttr((string)cderivedimpl.position(), "UML", dx, dy);

		cinh.position() = MakePosition(50, by + (dy-by)/2 , 50 , by + (dy-by)/2);
		UmlGME::Base cbc = UmlGME::Base::Create(umlGMEimplinterfaceDiagram);
		cbc.dstInheritance_end() = cinh;
		cbc.srcClassBase_end() = cbaseimpl;

		UmlGME::Sub csub = UmlGME::Sub::Create(umlGMEimplinterfaceDiagram);
		csub.srcInheritance_end() = cinh;
		csub.dstClassBase_end() = cderivedimpl;

		maphasbaseimpl[cderived] = true;
	}

	if(intf)
	{	UmlGME::Inheritance cinh = UmlGME::Inheritance::Create(umlGMEimplinterfaceDiagram);
		
		int bx=0, by=0, dx=0, dy=0;
		GetPosAttr((string)cbaseintf.position(), "UML", bx, by);
		GetPosAttr((string)cderivedintf.position(), "UML", dx, dy);

		cinh.position() = MakePosition(500, by + (dy-by)/2 , 500 , by + (dy-by)/2);
		UmlGME::Base cbc = UmlGME::Base::Create(umlGMEimplinterfaceDiagram);
		cbc.dstInheritance_end() = cinh;
		cbc.srcClassBase_end() = cbaseintf;

		UmlGME::Sub csub = UmlGME::Sub::Create(umlGMEimplinterfaceDiagram);
		csub.srcInheritance_end() = cinh;
		csub.dstClassBase_end() = cderivedintf;

		maphasbaseintf[cderived] = true;
	}
}


// Get the UML counterparts
void MetaGME2UML::GetUMLCounterParts(MetaGME::BaseFCO base, MetaGME::BaseFCO derived, UmlGME::Class &cbase, UmlGME::Class &cderived)
{	MetaGME::BaseFCO ebase, ederived;
	if(mapMetaGME2UmlGME_Class.find(base) == mapMetaGME2UmlGME_Class.end())
	{	if(equivMap.find(base) != equivMap.end())	
		{	ebase = MetaGME::BaseFCO::Cast(equivMap[base]);
			if(mapMetaGME2UmlGME_Class.find(ebase) != mapMetaGME2UmlGME_Class.end())
			{	mapMetaGME2UmlGME_Class[base] = mapMetaGME2UmlGME_Class[ebase];
				//RecurseOnBases(base);
			}
			else {	
				if ( !Uml::IsDerivedFrom( base.type(), MetaGME::ProxyBase::meta)) {
					cbase = UmlGME::Class::Create(umlGMEimplinterfaceDiagram);
					cbase.name() = base.name();
					mapMetaGME2UmlGME_Class[base]  = cbase;
					mapMetaGME2UmlGME_Class[ebase] = cbase;
				}
				RecurseOnBases(ebase);
			}
			
		}
		else {	
			if ( !Uml::IsDerivedFrom( base.type(), MetaGME::ProxyBase::meta)) {
				cbase = UmlGME::Class::Create(umlGMEimplinterfaceDiagram);
				cbase.name() = base.name();
				mapMetaGME2UmlGME_Class[base] = cbase;
			}
			RecurseOnBases(base);
		}
		
	}
	else 
	{	cbase = UmlGME::Class::Cast(mapMetaGME2UmlGME_Class[base]);
	}

	if(mapMetaGME2UmlGME_Class.find(derived) == mapMetaGME2UmlGME_Class.end())
	{	
		if ( !Uml::IsDerivedFrom( derived.type(), MetaGME::ProxyBase::meta)) {
			cderived = UmlGME::Class::Create(umlGMEimplinterfaceDiagram);
			cderived.name() = derived.name();
			mapMetaGME2UmlGME_Class[derived] = cderived;
		}
	}
	else
	{	cderived = UmlGME::Class::Cast(mapMetaGME2UmlGME_Class[derived]);
	}
}
void MetaGME2UML::RecurseOnBases(const MetaGME::BaseFCO& base) {
	std::set< MetaGME::BaseFCO> visitedBases;
	RecurseOnBases( base, visitedBases);
}

template <class TYPE, class PROXY_TYPE>
void GetProxies(const MetaGME::BaseFCO& base, std::set<MetaGME::BaseFCO>& ret)
{
	if (base.type() == TYPE::meta)
	{
		std::set<PROXY_TYPE> proxies = TYPE::Cast(base).src();
		std::copy(proxies.begin(), proxies.end(), set_inserter(ret));
	}
}

set<MetaGME::BaseFCO> GetProxies(const MetaGME::BaseFCO& base)
{
	std::set<MetaGME::BaseFCO> ret;

	GetProxies<MetaGME::Atom, MetaGME::AtomProxy>(base, ret);
	GetProxies<MetaGME::Model, MetaGME::ModelProxy>(base, ret);
	GetProxies<MetaGME::FCO, MetaGME::FCOProxy>(base, ret);
	GetProxies<MetaGME::Connection, MetaGME::ConnectionProxy>(base, ret);
	GetProxies<MetaGME::Reference, MetaGME::ReferenceProxy>(base, ret);
	GetProxies<MetaGME::Set, MetaGME::SetProxy>(base, ret);

	return ret;
}


template <class TYPE, class PROXY_TYPE>
void MetaGME2UML::checkProxies( const MetaGME::BaseFCO& base, std::set< MetaGME::BaseFCO>& visitedBases) {
	if ( base.type() == TYPE::meta) {
		TYPE typedBase= TYPE::Cast( base);
		std::set< PROXY_TYPE> proxies= typedBase.src();
		for( std::set< PROXY_TYPE>::const_iterator it= proxies.begin(); it!= proxies.end(); ++it) {
			RecurseOnBases( *it, visitedBases);
//		std::for_each( proxies.begin(), proxies.end(), std::bind2nd( this->RecurseOnBases, visitedBases));
		}
	}
}

template <class TYPE, class PROXY_TYPE>
void MetaGME2UML::checkRefByProxies( const MetaGME::BaseFCO& proxy, std::set< MetaGME::BaseFCO>& visitedBases) {
	if ( proxy.type() == PROXY_TYPE::meta) {
		PROXY_TYPE typedProxy= PROXY_TYPE::Cast( proxy);
		TYPE refByProxy= typedProxy.ref();
		RecurseOnBases( refByProxy, visitedBases);
	}
}

void MetaGME2UML::RecurseOnBases( const MetaGME::BaseFCO& base, std::set< MetaGME::BaseFCO>& visitedBases)
{	
	// for logging only
    std::string name= base.name();
	std::string type= Uml::Class::Cast( base.type()).name();
	// "base" has been visited yet?
	std::set< MetaGME::BaseFCO>::const_iterator findBase= visitedBases.find( base);
	if ( visitedBases.end() != findBase) {
		return; // found, so "base" have been checked previously
	} else {
		visitedBases.insert( base); // not found, insert "base"
	}
	// recurse on base
	{	set<MetaGME::DerivedInheritance> dihs = base.dsrc();
		for(set<MetaGME::DerivedInheritance>::iterator i=dihs.begin(); i!=dihs.end(); i++)
		{	MetaGME::DerivedInheritance dih = *i;
			MetaGME::Inheritance inh = dih.dsrc_end();
			set<MetaGME::BaseInheritance> bihs = inh.bsrc();
			for(set<MetaGME::BaseInheritance>::iterator i=bihs.begin(); i!=bihs.end(); i++)
			{	MetaGME::BaseInheritance bih = *i;
				MetaGME::BaseFCO basebase = bih.bsrc_end();
				MakeImplIntf(basebase, base, true, true);
			}

		}
		
	}
	// stuff have been added here for reference inheritance
	// 1. find all references that refer to "base"
	std::set< MetaGME::ReferTo> refs= base.srcReferTo();
	for ( std::set< MetaGME::ReferTo>::const_iterator it= refs.begin(); it!= refs.end(); ++it) {
		// check each reference whether it has a base 
		const MetaGME::ReferTo& currRef= *it;
		MetaGME::BaseReference baseRef= currRef.srcReferTo_end();
		RecurseOnBases( baseRef, visitedBases);	// recursive call
	}
	// 2. if "base" is a reference, figure out if the referred baseFCOs have any bases
	if ( base.type() == MetaGME::BaseReference::meta) {
		MetaGME::BaseReference baseRef= MetaGME::BaseReference::Cast( base);
		std::set< MetaGME::ReferTo> refs= baseRef.dstReferTo();
		for ( std::set< MetaGME::ReferTo>::const_iterator it= refs.begin(); it!= refs.end(); ++it) {
			// check each reference whether it has a base 
			const MetaGME::ReferTo& currRef= *it;
			MetaGME::BaseFCO currBase= currRef.dstReferTo_end();
			RecurseOnBases( currBase, visitedBases);	// recursive call
		}
	}
	// 3. find all proxys that refer to "base"
	checkProxies< MetaGME::Atom, MetaGME::AtomProxy>( base, visitedBases);
	checkProxies< MetaGME::Model, MetaGME::ModelProxy>( base, visitedBases);
	checkProxies< MetaGME::FCO, MetaGME::FCOProxy>( base, visitedBases);
	checkProxies< MetaGME::Connection, MetaGME::ConnectionProxy>( base, visitedBases);
	checkProxies< MetaGME::Reference, MetaGME::ReferenceProxy>( base, visitedBases);
	checkProxies< MetaGME::Set, MetaGME::SetProxy>( base, visitedBases);

	// 4. if base is a proxy, figure out if the referred baseFCOs have any bases
	checkRefByProxies< MetaGME::Atom, MetaGME::AtomProxy>( base, visitedBases);
	checkRefByProxies< MetaGME::Model, MetaGME::ModelProxy>( base, visitedBases);
	checkRefByProxies< MetaGME::FCO, MetaGME::FCOProxy>( base, visitedBases);
	checkRefByProxies< MetaGME::Connection, MetaGME::ConnectionProxy>( base, visitedBases);
	checkRefByProxies< MetaGME::Reference, MetaGME::ReferenceProxy>( base, visitedBases);
	checkRefByProxies< MetaGME::Set, MetaGME::SetProxy>( base, visitedBases);

	vector<MetaGME::ContainedInPar> fcos;
	for(map_CIP2CIP::iterator emi=equivMap.begin(); emi!=equivMap.end(); emi++)
	{	if( (*emi).second == base)
			fcos.push_back((*emi).first);
	}
	for(vector<MetaGME::ContainedInPar>::iterator fi = fcos.begin(); fi!=fcos.end(); fi++)
	{	RecurseOnBases(MetaGME::BaseFCO::Cast(*fi));
	}
}

void MetaGME2UML::Phase3_CreateClasses()
{	CreateClasses(grf,urf);
}

void MetaGME2UML::CreateClasses(MetaGME::RootFolder grf, Udm::Object urf)
{	
	vector<MetaGME::RootFolder> rfs = grf.RootFolder_kind_children();
	for(vector<MetaGME::RootFolder>::iterator ri=rfs.begin(); ri!=rfs.end();ri++)
	{	MetaGME::RootFolder sf = *ri;
		CreateClasses(sf, urf);
	}
	
	vector<MetaGME::SheetFolder> sfs = grf.SheetFolder_kind_children();
	for(vector<MetaGME::SheetFolder>::iterator i=sfs.begin(); i!=sfs.end();i++)
	{	MetaGME::SheetFolder sf = *i;
		vector<MetaGME::ParadigmSheet> pss = sf.ParadigmSheet_kind_children();
		for(vector<MetaGME::ParadigmSheet>::iterator j=pss.begin(); j!=pss.end();j++)
		{	MetaGME::ParadigmSheet ps = *j;
			UmlGME::ClassDiagram cd = mapMetaGME2UmlGME_Paradigm[ps];
			CreateClasses(ps,cd);
		}
	}
	
	vector<MetaGME::ParadigmSheet> pss = grf.ParadigmSheet_kind_children();
	for(vector<MetaGME::ParadigmSheet>::iterator j=pss.begin(); j!=pss.end();j++)
	{	MetaGME::ParadigmSheet ps = *j;
		UmlGME::ClassDiagram cd = mapMetaGME2UmlGME_Paradigm[ps];
		CreateClasses(ps,cd);
	}
}

// requires: fco is not a proxy
static bool InRootFolder(MetaGME::BaseFCO fco)
{
	std::set<MetaGME::BaseFCO> proxies = GetProxies(fco);
	for (std::set<MetaGME::BaseFCO>::iterator proxiesIt = proxies.begin(); proxiesIt != proxies.end(); proxiesIt++)
	{
		if (proxiesIt->InRootFolder())
			return true;
	}
	return false;
}

static bool BaseInRootFolder(MetaGME::ContainedInPar kind)
{
	if (kind.type() == MetaGME::Folder::meta)
	{
		return MetaGME::Folder::Cast(kind).InRootFolder();
	}
	if (Uml::IsDerivedFrom(kind.type(), MetaGME::BaseFCO::meta))
	{
		return InRootFolder(MetaGME::BaseFCO::Cast(kind));
	}
	return false;
}

void MetaGME2UML::CreateClasses(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd)
{	vector<MetaGME::ContainedInPar> cips = ps.ContainedInPar_kind_children();
	for(vector<MetaGME::ContainedInPar>::iterator i=cips.begin(); i!=cips.end();i++)
	{	MetaGME::ContainedInPar cip = *i;
		
		Uml::Class cipType = cip.type();
		string type = cipType.name();
		if(Udm::IsDerivedFrom(cipType, MetaGME::ProxyBase::meta) || type == "FolderProxy")
			continue;
		
		if(equivMap.find(cip)!= equivMap.end())
		{	continue;
		}
		
		int setmaps = false;

		UmlGME::Class cl, impl, intf;
		if(mapMetaGME2UmlGME_Class.find(cip)!=mapMetaGME2UmlGME_Class.end())
		{	cl = UmlGME::Class::Cast(mapMetaGME2UmlGME_Class[cip]);
			impl = mapUmlClass2ImplInheritBases[cl].first;
			intf = mapUmlClass2ImplInheritBases[cl].second;
		}
		else
		{	cl = UmlGME::Class::Create(cd);
			impl = cl; intf = cl;
			pair<UmlGME::Class, UmlGME::Class> pr;
			pr.first = impl; pr.second = intf;
			mapUmlClass2ImplInheritBases[cl] = pr;
			implMap[cip] = cl;
			intfMap[cip] = cl;
			reguMap[cip] = cl;
			setmaps = true;
			cl.position() = MakePosAttr(cip.position(), attmap);
			mapMetaGME2UmlGME_Class[cip] = cl;
		}


		vector<MetaGME::ContainedInPar> fcos;
		for(map_CIP2CIP::iterator emi=equivMap.begin(); emi!=equivMap.end(); emi++)
		{	if( (*emi).second == cip)
				fcos.push_back((*emi).first);
		}

		if(type == "Folder")
		{	MetaGME::Folder mo = MetaGME::Folder::Cast(cip);
			cl.name() = mo.name();
			cl.Stereotype() = "Folder";
			impl.Stereotype() = "Folder";
			intf.Stereotype() = "Folder";
			cl.IsAbstract() = false;
			cl.Attributes() = "name : String[0..1]\n";
			bool inRootFolder = mo.InRootFolder();
			inRootFolder |= std::any_of(fcos.begin(), fcos.end(), BaseInRootFolder);
			if (inRootFolder)
				CreateRootFolderAssociation(intf);
		}
		else // either Model, Atom, FCO, Set, Reference, Connection
		{	MetaGME::BaseFCO mo = MetaGME::BaseFCO::Cast(cip);
			cl.name() = mo.name();
			cl.IsAbstract() = mo.IsAbstract();
			cl.Stereotype() = type;
			impl.Stereotype() = type;
			intf.Stereotype() = type;

			bool inRootFolder = mo.InRootFolder();
			inRootFolder |= InRootFolder(mo);
			inRootFolder |= std::any_of(fcos.begin(), fcos.end(), BaseInRootFolder);

			if (inRootFolder)
				CreateRootFolderAssociation(intf);
			AddAttribute(mo,impl);
		}

		for(vector<MetaGME::ContainedInPar>::iterator fi = fcos.begin(); fi!=fcos.end(); fi++)
		{	MetaGME::ContainedInPar slave = *fi;
			mapMetaGME2UmlGME_Class[slave] = cl;
			if(setmaps && MetaGME::ParadigmSheet::Cast(slave.parent()) == MetaGME::ParadigmSheet::Cast(cip.parent()) )
			{	implMap[slave] = implMap[cip];
				intfMap[slave] = intfMap[cip];
				reguMap[slave] = reguMap[cip];
			}
			if(Udm::IsDerivedFrom(slave.type(), MetaGME::BaseFCO::meta))
			{	AddAttribute(MetaGME::BaseFCO::Cast(slave),impl);
			}
		}
	}
}

void MetaGME2UML::Phase4_CreateReferences()
{	
	CreateReferences(grf,urf);
		
}

void MetaGME2UML::CreateReferences(MetaGME::RootFolder grf, Udm::Object urf)
{	
	vector<MetaGME::RootFolder> rfs = grf.RootFolder_kind_children();
	for(vector<MetaGME::RootFolder>::iterator ri=rfs.begin(); ri!=rfs.end();ri++)
	{	MetaGME::RootFolder sf = *ri;
		CreateReferences(sf, urf);
	}
	
	vector<MetaGME::SheetFolder> sfs = grf.SheetFolder_kind_children();
	for(vector<MetaGME::SheetFolder>::iterator i=sfs.begin(); i!=sfs.end();i++)
	{	MetaGME::SheetFolder sf = *i;
		vector<MetaGME::ParadigmSheet> pss = sf.ParadigmSheet_kind_children();
		for(vector<MetaGME::ParadigmSheet>::iterator j=pss.begin(); j!=pss.end();j++)
		{	MetaGME::ParadigmSheet ps = *j;
			UmlGME::ClassDiagram cd = mapMetaGME2UmlGME_Paradigm[ps];
			CreateReferences(ps,cd);
		}
	}
	
	vector<MetaGME::ParadigmSheet> pss = grf.ParadigmSheet_kind_children();
	for(vector<MetaGME::ParadigmSheet>::iterator j=pss.begin(); j!=pss.end();j++)
	{	MetaGME::ParadigmSheet ps = *j;
		UmlGME::ClassDiagram cd = mapMetaGME2UmlGME_Paradigm[ps];
		CreateReferences(ps,cd);
	}

}

void MetaGME2UML::CreateReferences(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd)
{	
	vector<MetaGME::ContainedInPar> cips = ps.ContainedInPar_kind_children();
//	int sz= cips.size();
	for(vector<MetaGME::ContainedInPar>::iterator i=cips.begin(); i!=cips.end();i++)
	{	MetaGME::ContainedInPar cip = *i;
	std::string cipname= cip.name();
		Uml::Class cipType = cip.type();
//		string type = cipType.name();
		if(!Udm::IsDerivedFrom(cipType, MetaGME::ProxyBase::meta) && ( cipType != MetaGME::FolderProxy::meta))
			continue;
		
		MetaGME::ContainedInPar cipO = GetRefMetaGMEObject(cip);
		if(mapMetaGME2UmlGME_Class.find(cipO)!=mapMetaGME2UmlGME_Class.end())
		{	mapMetaGME2UmlGME_Class[cip] = mapMetaGME2UmlGME_Class[cipO];
			
			MetaGME::ContainedInPar cipb = cip;
			UmlGME::Class rcl = UmlGME::Class::Cast(mapMetaGME2UmlGME_Class[cipO]);
			if(cipb == Udm::null || rcl == Udm::null)
				MESSAGE_OUT("NULL || NULL");
			AddAttribute(cipb,rcl);
			//continue;
		}
		continue;
		
		// code below this is not executed as of now
		/*
		UmlGME::ClassCopy cl = UmlGME::ClassCopy::Create(cd);
		implMap[cip] = cl;
		intfMap[cip] = cl;
		reguMap[cip] = cl;

		if(type == "ModelProxy")
		{	MetaGME::ModelProxy mo = MetaGME::ModelProxy::Cast(cip);
			cl.name() = mo.name();
			cl.position() = MakePosAttr(mo.position(), attmap);
			MetaGME::Model m = mo.ref();
			map_CIP2CB::iterator mf = mapMetaGME2UmlGME_Class.find(m);
			if(mf==mapMetaGME2UmlGME_Class.end())
			{	//Error
				string error = "Error: ModelProxy:" + (string)mo.name() + " in ParadigmSheet:" + (string)ps.name() + " refers to NULL";
				throw udm_exception(error);
			}
			UmlGME::Class cls = UmlGME::Class::Cast(mf->second);
			cl.ref() = cls;
			AddAttribute(mo,cls);
			mapMetaGME2UmlGME_Class[mo] = cl;
		}
		else if(type == "AtomProxy")
		{	MetaGME::AtomProxy mo = MetaGME::AtomProxy::Cast(cip);
			cl.name() = mo.name();
			cl.position() = MakePosAttr(mo.position(), attmap);
			MetaGME::Atom m = MetaGME::Atom::Cast(mo.ref());
			map_CIP2CB::iterator mf = mapMetaGME2UmlGME_Class.find(m);
			if(mf==mapMetaGME2UmlGME_Class.end())
			{	//Error
				string error = "Error: AtomProxy:" + (string)mo.name() + " in ParadigmSheet:" + (string)ps.name() + " refers to NULL";
				throw udm_exception(error);
			}
			UmlGME::Class cls = UmlGME::Class::Cast(mf->second);
			cl.ref() = cls;
			AddAttribute(mo,cls);
			mapMetaGME2UmlGME_Class[mo] = cl;
		}
		else if(type == "FolderProxy")
		{	MetaGME::FolderProxy mo = MetaGME::FolderProxy::Cast(cip);
			cl.name() = mo.name();
			cl.position() = MakePosAttr(mo.position(), attmap);
			MetaGME::Folder m = MetaGME::Folder::Cast(mo.ref());
			map_CIP2CB::iterator mf = mapMetaGME2UmlGME_Class.find(m);
			if(mf==mapMetaGME2UmlGME_Class.end())
			{	//Error
				string error = "Error: FolderProxy:" + (string)mo.name() + " in ParadigmSheet:" + (string)ps.name() + " refers to NULL";
				throw udm_exception(error);
			}
			UmlGME::Class cls = UmlGME::Class::Cast(mf->second);
			cl.ref() = cls;
			mapMetaGME2UmlGME_Class[mo] = cl;
		}
		else if(type == "FCOProxy")
		{	MetaGME::FCOProxy mo = MetaGME::FCOProxy::Cast(cip);
			cl.name() = mo.name();
			cl.position() = MakePosAttr(mo.position(), attmap);
			MetaGME::FCO m = MetaGME::FCO::Cast(mo.ref());
			map_CIP2CB::iterator mf = mapMetaGME2UmlGME_Class.find(m);
			if(mf==mapMetaGME2UmlGME_Class.end())
			{	//Error
				string error = "Error: FCOProxy:" + (string)mo.name() + " in ParadigmSheet:" + (string)ps.name() + " refers to NULL";
				throw udm_exception(error);
			}
			UmlGME::Class cls = UmlGME::Class::Cast(mf->second);
			cl.ref() = cls;
			AddAttribute(mo,cls);
			mapMetaGME2UmlGME_Class[mo] = cl;
		}
		else if(type == "SetProxy")
		{	MetaGME::SetProxy mo = MetaGME::SetProxy::Cast(cip);
			cl.name() = mo.name();
			cl.position() = MakePosAttr(mo.position(), attmap);
			MetaGME::Set m = MetaGME::Set::Cast(mo.ref());
			map_CIP2CB::iterator mf = mapMetaGME2UmlGME_Class.find(m);
			if(mf==mapMetaGME2UmlGME_Class.end())
			{	//Error
				string error = "Error: SetProxy:" + (string)mo.name() + " in ParadigmSheet:" + (string)ps.name() + " refers to NULL";
				throw udm_exception(error);
			}
			UmlGME::Class cls = UmlGME::Class::Cast(mf->second);
			cl.ref() = cls;
			AddAttribute(mo,cls);
			mapMetaGME2UmlGME_Class[mo] = cl;
		}
		else if(type == "ReferenceProxy")
		{	MetaGME::ReferenceProxy mo = MetaGME::ReferenceProxy::Cast(cip);
			cl.name() = mo.name();
			cl.position() = MakePosAttr(mo.position(), attmap);
			MetaGME::Reference m = MetaGME::Reference::Cast(mo.ref());
			map_CIP2CB::iterator mf = mapMetaGME2UmlGME_Class.find(m);
			if(mf==mapMetaGME2UmlGME_Class.end())
			{	//Error
				string error = "Error: ReferenceProxy:" + (string)mo.name() + " in ParadigmSheet:" + (string)ps.name() + " refers to NULL";
				throw udm_exception(error);
			}
			UmlGME::Class cls = UmlGME::Class::Cast(mf->second);
			cl.ref() = cls;
			AddAttribute(mo,cls);
			mapMetaGME2UmlGME_Class[mo] = cl;
		}
		else if(type == "ConnectionProxy")
		{	UmlGME::ClassCopy cl = UmlGME::ClassCopy::Create(cd);
			MetaGME::ConnectionProxy mo = MetaGME::ConnectionProxy::Cast(cip);
			cl.name() = mo.name();
			cl.position() = MakePosAttr(mo.position(), attmap);
			MetaGME::Connection m = MetaGME::Connection::Cast(mo.ref());
			map_CIP2CB::iterator mf = mapMetaGME2UmlGME_Class.find(m);
			if(mf==mapMetaGME2UmlGME_Class.end())
			{	//Error
				string error = "Error: ConnectionProxy:" + (string)mo.name() + " in ParadigmSheet:" + (string)ps.name() + " refers to NULL";
				throw udm_exception(error);
			}
			UmlGME::Class cls = UmlGME::Class::Cast(mf->second);
			cl.ref() = cls;
			AddAttribute(mo,cls);
			mapMetaGME2UmlGME_Class[mo] = cl;
		}
		*/
		
	}
}