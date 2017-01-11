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
 *  FILE NAME:	MetaGME2UML file 2, used because of heap overflow.
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
#include <UmlExt.h>
#include <cctype> // for isspace()

#include <iterator>
#include "UdmUtil.h"
#include "UdmGme.h"

using namespace std;

std::string ExName(const Udm::Object& o) { return UdmUtil::ExtractName(o); }

bool AskUserForConstraint(long);

void MetaGME2UML::Phase5_CreateConnections()
{	
	CreateConnections(grf,urf);
}

void MetaGME2UML::CreateConnections(MetaGME::RootFolder grf, Udm::Object urf)
{	
	vector<MetaGME::RootFolder> rfs = grf.RootFolder_kind_children();
	for(vector<MetaGME::RootFolder>::iterator ri=rfs.begin(); ri!=rfs.end();ri++)
	{	MetaGME::RootFolder sf = *ri;
		CreateConnections(sf, urf);
	}
	
	vector<MetaGME::SheetFolder> sfs = grf.SheetFolder_kind_children();
	for(vector<MetaGME::SheetFolder>::iterator i=sfs.begin(); i!=sfs.end();i++)
	{	MetaGME::SheetFolder sf = *i;
		vector<MetaGME::ParadigmSheet> pss = sf.ParadigmSheet_kind_children();
		for(vector<MetaGME::ParadigmSheet>::iterator j=pss.begin(); j!=pss.end();j++)
		{	MetaGME::ParadigmSheet ps = *j;
			UmlGME::ClassDiagram cd = mapMetaGME2UmlGME_Paradigm[ps];
			CreateConnections(ps,cd);
		}
	}
	
	vector<MetaGME::ParadigmSheet> pss = grf.ParadigmSheet_kind_children();
	for(vector<MetaGME::ParadigmSheet>::iterator j=pss.begin(); j!=pss.end();j++)
	{	MetaGME::ParadigmSheet ps = *j;
		UmlGME::ClassDiagram cd = mapMetaGME2UmlGME_Paradigm[ps];
		CreateConnections(ps,cd);
	}

}

void MetaGME2UML::CreateConnections(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd)
{	//string psName = ps.name();
	
	//MESSAGE_OUT("CreateCompositionAssociation");
	CreateCompositionAssociation(ps, cd);
	//MESSAGE_OUT("CreateFolderCompositionAssociation");
	CreateFolderCompositionAssociation(ps, cd);
	//MESSAGE_OUT("CreateReferToAssociation");
	CreateReferToAssociation(ps, cd);
	//MESSAGE_OUT("CreateSetMembershipAssociation");
	CreateSetMembershipAssociation(ps, cd);
	//MESSAGE_OUT("CreateAssociationClassAssociation");
	CreateAssociationClassAssociation(ps, cd);
	//MESSAGE_OUT("CreateInheritanceAssociation");
	CreateInheritanceAssociation(ps, cd);
	CreateRefportContainersAssociations(ps, cd);
	//CreateEquivalenceAssociation(ps, cd);
	//CreateFolderEquivalenceAssociation(ps, cd);
	//MESSAGE_OUT("CreateConstraints");
	CreateConstraints(ps, cd);	
}


// Transfering Composition association
void MetaGME2UML::CreateCompositionAssociation(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd)
{	vector<MetaGME::Containment> contains = ps.Containment_kind_children();
	for(vector<MetaGME::Containment>::iterator i = contains.begin(); i!=contains.end(); i++)
	{	MetaGME::Containment contain = *i;
		MetaGME::ContainedInPar child  = contain.srcContainment_end();
		MetaGME::ContainedInPar parent = contain.dstContainment_end();
		UmlGME::ClassBase cchild  = GetInterface(child);
		UmlGME::ClassBase cparent = GetImplementation(parent);
		UmlGME::Composition ccomp = UmlGME::Composition::Create(cd);
		ccomp.dstParent_end() = cparent;
		ccomp.srcChildren_end() = cchild;
		ccomp.ChildRole() = contain.Rolename();
		
		ccomp.Cardinality() = contain.Cardinality();
	}
}

// Transfering Folder Composition association
void MetaGME2UML::CreateFolderCompositionAssociation(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd)
{	vector<MetaGME::FolderContainment> contains = ps.FolderContainment_kind_children();
	for(vector<MetaGME::FolderContainment>::iterator i = contains.begin(); i!=contains.end(); i++)
	{	MetaGME::FolderContainment contain = *i;
		MetaGME::ContainedInPar child  = contain.dstFolderContainment_end();
		MetaGME::ContainedInPar parent = contain.srcFolderContainment_end();
		UmlGME::ClassBase cchild  = GetInterface(child);
		UmlGME::ClassBase cparent = GetImplementation(parent);
		UmlGME::Composition ccomp = UmlGME::Composition::Create(cd);
		ccomp.dstParent_end() = cparent;
		ccomp.srcChildren_end() = cchild;
		ccomp.Cardinality() = contain.Cardinality();
	}
}

// Transfering ReferTo association
void MetaGME2UML::CreateReferToAssociation(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd)
{	vector<MetaGME::Reference> contains = ps.Reference_kind_children();
	for(vector<MetaGME::Reference>::iterator i = contains.begin(); i!=contains.end(); i++)
	{	MetaGME::Reference contain = *i;
		vector<MetaGME::BaseReference> refandProxes;
		vector<MetaGME::ReferTo> refereds;
		refandProxes.push_back(contain);
		set<MetaGME::ReferenceProxy> refproxies = contain.src();
		for(set<MetaGME::ReferenceProxy>::iterator rpi=refproxies.begin(); rpi!=refproxies.end();rpi++)
			refandProxes.push_back(*rpi);
		for(vector<MetaGME::BaseReference>::iterator rapi=refandProxes.begin(); rapi!=refandProxes.end();rapi++)
		{	MetaGME::BaseReference rap = *rapi;
			set<MetaGME::ReferTo> refs = rap.dstReferTo();
			refereds.insert(refereds.end(),refs.begin(),refs.end());
		}
		if(refereds.size()<1)
		{	//Error
		//	string error = "Error: Reference:"+(string)contain.name()+ " in ParadigmSheet:" + (string)ps.name() + " Doesnt refer to any object";
		//	throw udm_exception(error);
			continue;
		}
	
		if(refereds.size()==1)
		{	MetaGME::ReferTo rt = *refereds.begin();
			MetaGME::BaseReference referer  = rt.srcReferTo_end();
			MetaGME::BaseFCO refereee = rt.dstReferTo_end();
			UmlGME::ClassBase crefer  = GetInterface(referer);
			UmlGME::ClassBase crefe   = GetInterface(refereee);
			CreateRefereredConnection(crefer, crefe, contain);
		}
		else
		{	// Multiple references, Creating a new sheet and new base class
			UmlGME::Class crefclass = GetRealInterface(contain);
			UmlGME::ClassDiagram ncd = UmlGME::ClassDiagram::Create(urf);
			ncd.name() = "zC_" + (string)contain.name() + "_Reference_2_Refered_Association";
			UmlGME::ClassCopy refp = UmlGME::ClassCopy::Create(ncd);
			refp.name() = contain.name();
			refp.position() = MakePosition(50,50,50,50);
			refp.ref() = crefclass;
			UmlGME::Class refereebase = UmlGME::Class::Create(ncd);
			refereebase.name() = (string)contain.name() + "_RefersTo_Base";
			refereebase.position() = MakePosition(250,50,250,50);
			refereebase.Stereotype() = "FCO";
			refereebase.IsAbstract() = true;
			CreateRefereredConnection(refp, refereebase, contain);
			UmlGME::Inheritance cinh = UmlGME::Inheritance::Create(ncd);
			cinh.position() = MakePosition(250,150,250,150);
			UmlGME::Base cbc = UmlGME::Base::Create(ncd);
			cbc.dstInheritance_end() = cinh;
			cbc.srcClassBase_end() = refereebase;
			int xa = 150, ya = 250;
			for(vector<MetaGME::ReferTo>::iterator rti=refereds.begin(); rti!=refereds.end(); rti++)
			{	MetaGME::ReferTo rt = *rti;
				MetaGME::BaseFCO refereee = rt.dstReferTo_end();
				UmlGME::ClassBase crefe = GetRealInterface(refereee);
				UmlGME::Class crefec;
				if((string)crefe.type().name() == "ClassCopy")
					crefec = UmlGME::ClassCopy::Cast(crefe).ref();
				else
					crefec = UmlGME::Class::Cast(crefe);
				UmlGME::ClassCopy obc = UmlGME::ClassCopy::Create(ncd);
				obc.name() = crefec.name();
				obc.ref() = crefec;
				obc.position() = MakePosition(xa,ya,xa,ya);
				xa += 200;
				UmlGME::Sub csub = UmlGME::Sub::Create(ncd);
				csub.srcInheritance_end() = cinh;
				csub.dstClassBase_end() = obc;
			}
		}
	}
}

// Transfering SetMembership association
void MetaGME2UML::CreateSetMembershipAssociation(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd)
{	vector<MetaGME::Set> contains = ps.Set_kind_children();   //contains has all of the Sets 
	for(vector<MetaGME::Set>::iterator i = contains.begin(); i!=contains.end(); i++)
	{	MetaGME::Set contain = *i;  //contain is the current Set
		vector<MetaGME::BaseSet> setandProxes;  //has BaseSets and Sets
		vector<MetaGME::SetMembership> setmembers;
		setandProxes.push_back(contain);
		set<MetaGME::SetProxy> setproxies = contain.src();
		for(set<MetaGME::SetProxy>::iterator spi=setproxies.begin(); spi!=setproxies.end();spi++)
			setandProxes.push_back(*spi);
		for(vector<MetaGME::BaseSet>::iterator sapi=setandProxes.begin(); sapi!=setandProxes.end();sapi++)
		{	MetaGME::BaseSet sap = *sapi;
			set<MetaGME::SetMembership> members = sap.srcSetMembers();
			setmembers.insert(setmembers.end(),members.begin(),members.end());
		}
		//11-29-05: Commented out the following lines so that set inheritance can be dealt with properly
		/*
		if(setmembers.size()<1)
		{	//Error
			string error = "Error: Set:"+(string)contain.name()+ " in ParadigmSheet:" + (string)ps.name() + " Doesnt have any members defined";
			throw udm_exception(error);
		}*/
		if (setmembers.size() == 0)
		{
			// if empty, simply continue with next set
			continue;
		}
		if(setmembers.size()==1)
		{	MetaGME::SetMembership rt = *setmembers.begin();
			MetaGME::BaseSet setb   = rt.dstSets_end();
			MetaGME::BaseFCO member = rt.srcSetMembers_end();
			UmlGME::ClassBase cset   = GetInterface(setb);
			UmlGME::ClassBase cmember= GetInterface(member);
			CreateMembershipConnection(cset, cmember, contain);
		}
		else
		{	// Multiple references, Creating a new sheet and new base class
			UmlGME::Class crefclass= GetRealInterface(contain);
			UmlGME::ClassDiagram ncd = UmlGME::ClassDiagram::Create(urf);
			ncd.name() = "zC_" + (string)contain.name() + "_Set_2_Members";
			UmlGME::ClassCopy refp = UmlGME::ClassCopy::Create(ncd);
			refp.name() = contain.name();
			refp.position() = MakePosition(50,50,50,50);
			refp.ref() = crefclass;
			UmlGME::Class refereebase = UmlGME::Class::Create(ncd);
			refereebase.name() = (string)contain.name() + "_Members_Base";
			refereebase.position() = MakePosition(250,50,250,50);
			refereebase.Stereotype() = "FCO";
			refereebase.IsAbstract() = true;
			CreateMembershipConnection(refp, refereebase, contain);
			UmlGME::Inheritance cinh = UmlGME::Inheritance::Create(ncd);
			cinh.position() = MakePosition(250,150,250,150);
			UmlGME::Base cbc = UmlGME::Base::Create(ncd);
			cbc.dstInheritance_end() = cinh;
			cbc.srcClassBase_end() = refereebase;
			int xa = 150, ya = 250;
			for(vector<MetaGME::SetMembership>::iterator rti=setmembers.begin(); rti!=setmembers.end(); rti++)
			{	MetaGME::SetMembership rt = *rti;
				MetaGME::BaseFCO refereee = rt.srcSetMembers_end();
				UmlGME::ClassBase crefe = GetRealInterface(refereee);
				UmlGME::Class crefec;
				if((string)crefe.type().name() == "ClassCopy")
					crefec = UmlGME::ClassCopy::Cast(crefe).ref();
				else
					crefec = UmlGME::Class::Cast(crefe);
				UmlGME::ClassCopy obc = UmlGME::ClassCopy::Create(ncd);
				obc.name() = crefec.name();
				obc.ref() = crefec;
				obc.position() = MakePosition(xa,ya,xa,ya);
				xa += 200;
				UmlGME::Sub csub = UmlGME::Sub::Create(ncd);
				csub.srcInheritance_end() = cinh;
				csub.dstClassBase_end() = obc;
			}
		}
	}
}

// Transfering Association Class association
void MetaGME2UML::CreateAssociationClassAssociation(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd)
{	vector<MetaGME::Connector> connects = ps.Connector_kind_children();
	for(vector<MetaGME::Connector>::iterator i = connects.begin(); i!=connects.end(); i++)
	{	MetaGME::Connector contain = *i;
		set<MetaGME::SourceToConnector> srcs = contain.srcFCO();
		set<MetaGME::ConnectorToDestination> dsts = contain.dstFCO();
		if(srcs.size() == 0)
		{	//Error
			string error = "Error: Connector at "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " has 0 source-to-connector connections";
			throw udm_exception(error);
		}
		if(srcs.size() > 1)
		{	//Error
			string error = "Error: Connector at "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " has more than 1 source-to-connector connections";
			throw udm_exception(error);
		}
		if(dsts.size() == 0)
		{	//Error
			string error = "Error: Connector at "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " has 0 connector-to-destination connections";
			throw udm_exception(error);
		}
		if(dsts.size() > 1)
		{	//Error
			string error = "Error: Connector at "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " has more than 1 connector-to-destination connections";
			throw udm_exception(error);
		}
		MetaGME::SourceToConnector src = *(srcs.begin());
		MetaGME::ConnectorToDestination dst = *(dsts.begin());

		if(src==Udm::null || dst==Udm::null)
		{	//Error
			string error = "Error: Connector at "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " has atleast one connection missing";
			throw udm_exception(error);
		}

		set<MetaGME::AssociationClass> assocs = contain.srcConnection();
		set<MetaGME::AssociationClass> associs = contain.dstConnection();
		MetaGME::AssociationClass assoc, associ;


		if(assocs.size() + associs.size() == 0)
		{	//Error
			string error = "Error: Connector at "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " has no connection class";
			throw udm_exception(error);
		}
		if(assocs.size() + associs.size() > 1)
		{	//Error
			string error = "Error: Connector at "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " has more than one connection class";
			throw udm_exception(error);
		}
		
		MetaGME::AssociationClass_Members_Base assocb;
		
		if(assocs.size() == 1 )
		{	assoc  = *(assocs.begin());
			assocb = assoc.srcConnection_end();
		}
		else 
		{	associ = *(associs.begin());
			assocb = associ.dstConnection_end();
		}
		if((string)assocb.type().name() == "Connector")
		{	//Error
			string error = "Error: Connector at "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " is connected to another connector";
			throw udm_exception(error);
		}	
		
		MetaGME::BaseConnection connection;
		MetaGME::Connection realConnection;
		
		if((string)assocb.type().name()=="Connection")
		{	connection = MetaGME::BaseConnection::Cast(assocb);
			realConnection = MetaGME::Connection::Cast(assocb);
		}
		else if((string)assocb.type().name()=="ConnectionProxy")
		{	connection = MetaGME::BaseConnection::Cast(assocb);
			realConnection = MetaGME::Connection::Cast(MetaGME::ConnectionProxy::Cast(assocb).ref());
		}
							
		MetaGME::ContainedInPar srco = src.srcFCO_end();
		MetaGME::ContainedInPar dsto = dst.dstFCO_end();
		
		UmlGME::ClassBase csrco  = GetInterface(srco);
		UmlGME::ClassBase cdsto = GetInterface(dsto);
		UmlGME::ClassBase cassoco = GetInterface(connection);
		UmlGME::Class cassococ;
		if((string)cassoco.type().name() == "Class")
			cassococ = UmlGME::Class::Cast(cassoco);
		else
			cassococ = UmlGME::ClassCopy::Cast(cassoco).ref();
		string name = realConnection.name();
		
		UmlGME::Class csrcoc;
		if((string)csrco.type().name() == "Class")
			csrcoc = UmlGME::Class::Cast(csrco);
		else
			csrcoc= UmlGME::ClassCopy::Cast(csrco).ref();

		UmlGME::Class cdstoc;
		if((string)cdsto.type().name() == "Class")
			cdstoc = UmlGME::Class::Cast(cdsto);
		else
			cdstoc = UmlGME::ClassCopy::Cast(cdsto).ref();

		// Geting sname preference from registry
		strmap prefMap;
		ConverGeneralPreferenceToMap((string)realConnection.GeneralPreferences(),prefMap);
		
		string srvalue = GetValueForName("sName",prefMap);
		if(srvalue == "")
		{	srvalue = "src" + name;
			try
			{	realConnection.GeneralPreferences() = (string)realConnection.GeneralPreferences() + "\nsName = " + srvalue;
			}
			catch(udm_exception ce) 
			{	//Error
				string error = "Error: Connection:"+(string)connection.name()+ " in ParadigmSheet:" + (string)ps.name() + " is read only. The object may be part of a library. Please run this interpreter on the library mga file, refresh library in this file and then run the interpreter";
				throw udm_exception(error);
			}
		}
		
		// Geting dname preference from registry
		string drvalue = GetValueForName("dName",prefMap);
		if(drvalue == "")
		{	drvalue = "dst" + name;
			try
			{	realConnection.GeneralPreferences() = (string)realConnection.GeneralPreferences() + "\ndName = " + drvalue;
			}
			catch(udm_exception ce) 
			{	//Error
				string error = "Error: Connection:"+(string)connection.name()+ " in ParadigmSheet:" + (string)ps.name() + " is read only. The object may be part of a library. Please run this interpreter on the library mga file, refresh library in this file and then run the interpreter";
				throw udm_exception(error);
			}
		}
		
		if((string)src.srcRolename() == "" || (string)dst.dstRolename() == "")
		{	/* 
			// bidirectional association using association class with no attributes
			// Use this code if you want simple assoications for bidirectional GME connections without attribute
			set<MetaGME::HasAttribute> attrs = realConnection.srcAttributes();
			if(attrs.size() == 0)	
			{	UmlGME::Association cass = UmlGME::Association::Create(cd);
				cass.name() = cassococ.name();
				cass.srcAssociationClasses_end() = csrco;
				cass.dstAssociationClasses_end() = cdsto;
				cass.dstCardinality() = "0..*";
				cass.srcCardinality() = "0..*";
				cass.dstRolename() = drvalue;
				cass.srcRolename() = srvalue;
				cass = UmlGME::Association::Create(cd);
				cass.name() = cassococ.name();
				cass.srcAssociationClasses_end() = csrco;
				cass.dstAssociationClasses_end() = cdsto;
				cass.dstCardinality() = "0..*";
				cass.srcCardinality() = "0..*";
				cass.dstRolename() = srvalue;
				cass.srcRolename() = drvalue;
				//cassoco.DeleteObject(); delete the composition association first.
				
			}
			// bidirectional association using association class with attributes
			else
			{	*/
			
			// FIXME: don't need _Members_Base for bidirectional association to itself
				UmlGME::ClassDiagram ncd = UmlGME::ClassDiagram::Create(urf);
				ncd.name() = "zC_" + (string)cassococ.name() + "_Bidirectional_Association";
				UmlGME::ClassCopy assp = UmlGME::ClassCopy::Create(ncd);
				assp.name() = cassococ.name();
				assp.position() = MakePosition(50,50,50,50);
				assp.ref() = cassococ;
				
				UmlGME::Class assocbase = UmlGME::Class::Create(ncd);
				assocbase.name() = (string)cassococ.name() + "_Members_Base";
				assocbase.position() = MakePosition(250,50,250,50);
				assocbase.Stereotype() = "FCO";
				assocbase.IsAbstract() = true;
				
				UmlGME::Inheritance cinh = UmlGME::Inheritance::Create(ncd);
				cinh.position() = MakePosition(350,150,350,150);
				UmlGME::Base cbc = UmlGME::Base::Create(ncd);
				cbc.dstInheritance_end() = cinh;
				cbc.srcClassBase_end() = assocbase;

				UmlGME::Sub csub;

				UmlGME::ClassCopy csrcor = UmlGME::ClassCopy::Create(ncd);
				csrcor.name() = csrcoc.name();
				csrcor.ref() = csrcoc;
				csrcor.position() = MakePosition(200,250,200,250);
				csub = UmlGME::Sub::Create(ncd);
				csub.srcInheritance_end() = cinh;
				csub.dstClassBase_end() = csrcor;

				UmlGME::ClassCopy cdstor = UmlGME::ClassCopy::Create(ncd);
				cdstor.name() = cdstoc.name();
				cdstor.ref() = cdstoc;
				cdstor.position() = MakePosition(400,250,400,250);
				csub = UmlGME::Sub::Create(ncd);
				csub.srcInheritance_end() = cinh;
				csub.dstClassBase_end() = cdstor;

				UmlGME::Connector con = UmlGME::Connector::Create(ncd);
				con.position() = MakePosition(240,80,240,80);
				UmlGME::Src csrc = UmlGME::Src::Create(ncd);
				UmlGME::Dst cdst = UmlGME::Dst::Create(ncd);
				UmlGME::AssociationClass cassoc = UmlGME::AssociationClass::Create(ncd);
				csrc.dstConnector_end() = con;
				csrc.srcClassBase_end() = assocbase;
				cdst.dstClassBase_end() = assocbase;
				cdst.srcConnector_end() = con;
				cassoc.srcAssocConnector_end() = con;
				cassoc.dstAssocClassBase_end() = assp;
				
				csrc.srcRolename() = srvalue;
				cdst.dstRolename() = drvalue;

				csrc.Cardinality() = src.Cardinality();
				cdst.Cardinality() = dst.Cardinality();
				
			/*}*/
		}
		else // a uni directional association using association class
		{
			UmlGME::Connector con = UmlGME::Connector::Create(cd);
			con.position() = MakePosAttr(contain.position(), conmap);
			
			UmlGME::Src csrc = UmlGME::Src::Create(cd);
			csrc.dstConnector_end() = con;
			csrc.srcClassBase_end() = csrco;
			
			UmlGME::Dst cdst = UmlGME::Dst::Create(cd);
			cdst.dstClassBase_end() = cdsto;
			cdst.srcConnector_end() = con;
			
			UmlGME::AssociationClass cassoc = UmlGME::AssociationClass::Create(cd);
			cassoc.srcAssocConnector_end() = con;
			cassoc.dstAssocClassBase_end() = cassoco;
			
			csrc.srcRolename() = srvalue;
			cdst.dstRolename() = drvalue;

			csrc.Cardinality() = src.Cardinality();
			cdst.Cardinality() = dst.Cardinality();
		}
	}
}

// Transfering Inheritance association
void MetaGME2UML::CreateInheritanceAssociation(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd)
{	
	//return;
	vector<MetaGME::Inheritance> connects = ps.Inheritance_kind_children();
	for(vector<MetaGME::Inheritance>::iterator i = connects.begin(); i!=connects.end(); i++)
	{	MetaGME::Inheritance contain = *i;
		set<MetaGME::BaseInheritance> basecs = contain.bsrc();
		if(basecs.size() == 0)
		{	//Error
			string error = "Error: Inheritance object "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " is not connected to a base class";
			throw udm_exception(error);
		}
		if(basecs.size() > 1)
		{	//Error
			string error = "Error: Inheritance object "+(string)contain.position()+ " in ParadigmSheet:" + (string)ps.name() + " is connected to more than one base class";
			throw udm_exception(error);
		}
		MetaGME::BaseInheritance basec = *(basecs.begin());

		set<MetaGME::DerivedInheritance> derivedcs = contain.ddst();
		MetaGME::BaseFCO base = basec.bsrc_end();
		
		UmlGME::Inheritance cinh;
		UmlGME::ClassBase cbase, cderived;
		UmlGME::Sub csub;
		UmlGME::Base cbc;
		UmlGME::ClassBase cderivedimpl, cderivedintf;
		UmlGME::ClassBase cbaseimpl, cbaseintf;

		cbaseimpl = GetRealImplementation(base);
//		std::string name= base.name();
//		std::string implname= cbaseimpl.name();
		cbaseintf = GetRealInterface(base);
//		std::string intfname= cbaseintf.name();

		
		int flag = false;
		for(set<MetaGME::DerivedInheritance>::iterator j=derivedcs.begin();j!=derivedcs.end();j++)
		{	MetaGME::DerivedInheritance derivedc = *j;
			MetaGME::BaseFCO derived = derivedc.ddst_end();

			cderivedimpl = GetRealImplementation(derived);
			cderivedintf = GetRealInterface(derived);
			cderived = GetRegular(derived);
			if(cderivedimpl != cderivedintf)
			{
				if ( cbaseimpl!= mapMetaGME2UmlGME_Class[ base]) {	// see comments in GetRealImplementation()!
					UmlGME::Inheritance cinh = UmlGME::Inheritance::Create(umlGMEimplinterfaceDiagram);
			
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

				}

				if ( cbaseintf!= mapMetaGME2UmlGME_Class[ base]){
					UmlGME::Inheritance cinh = UmlGME::Inheritance::Create(umlGMEimplinterfaceDiagram);
			
					int bx=0, by=0, dx=0, dy=0;
					GetPosAttr((string)cbaseimpl.position(), "UML", bx, by);
					GetPosAttr((string)cderivedimpl.position(), "UML", dx, dy);

					cinh.position() = MakePosition(500, by + (dy-by)/2 , 500 , by + (dy-by)/2);
					UmlGME::Base cbc = UmlGME::Base::Create(umlGMEimplinterfaceDiagram);
					cbc.dstInheritance_end() = cinh;
					cbc.srcClassBase_end() = cbaseintf;

					UmlGME::Sub csub = UmlGME::Sub::Create(umlGMEimplinterfaceDiagram);
					csub.srcInheritance_end() = cinh;
					csub.dstClassBase_end() = cderivedintf;

				}
			}

			if(!flag)
			{	cbase = GetRegular(base);
				cinh = UmlGME::Inheritance::Create(cd);
				cinh.position() = MakePosAttr(contain.position(),attmap);
				cbc = UmlGME::Base::Create(cd);
				cbc.dstInheritance_end() = cinh;
				cbc.srcClassBase_end() = cbase;
				flag = true;
			}
			
			
			csub = UmlGME::Sub::Create(cd);
			csub.srcInheritance_end() = cinh;
			csub.dstClassBase_end() = cderived;
			// Make map for GME Object base
			UmlGME::Class cderivedclass;
			if((string)cderived.type().name() == "ClassCopy")
				cderivedclass = UmlGME::ClassCopy::Cast(cderived).ref();
			else
				cderivedclass = UmlGME::Class::Cast(cderived);
			maphasbaseimpl[cderivedclass] = true;
			maphasbaseintf[cderivedclass] = true;
		}
	}
}

// Transfering Equivalence association
void MetaGME2UML::CreateEquivalenceAssociation(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd)
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
		
		UmlGME::Inheritance cinh;
		UmlGME::ClassBase cbase, cderived;
		UmlGME::Sub csub;
		UmlGME::Base cbc;
		UmlGME::ClassBase cderivedimpl, cderivedintf;
		
		cderivedimpl = GetRealImplementation(derived);
		cderivedintf = GetRealInterface(derived);
		
		cbase = GetRegular(base);
		cinh = UmlGME::Inheritance::Create(cd);
		cinh.position() = MakePosAttr(contain.position(),attmap);
		cbc = UmlGME::Base::Create(cd);
		cbc.dstInheritance_end() = cinh;
		cbc.srcClassBase_end() = cbase;
		
		if((string)cbase.type().name() == "ClassCopy")
			UmlGME::Class::Cast(UmlGME::ClassCopy::Cast(cbase).ref()).IsAbstract() = true;
		else
			cbase.IsAbstract() = true;
		
		cderived = GetRegular(derived);
		csub = UmlGME::Sub::Create(cd);
		csub.srcInheritance_end() = cinh;
		csub.dstClassBase_end() = cderived;
		// Make map for GME Object base
		UmlGME::Class cderivedclass;
		if((string)cderived.type().name() == "ClassCopy")
			cderivedclass = UmlGME::ClassCopy::Cast(cderived).ref();
		else
			cderivedclass = UmlGME::Class::Cast(cderived);
		maphasbaseimpl[cderivedclass] = true;
		maphasbaseintf[cderivedclass] = true;
	
	}
}

// Transfering Folder Equivalence association
void MetaGME2UML::CreateFolderEquivalenceAssociation(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd)
{	vector<MetaGME::SameFolder> connects = ps.SameFolder_kind_children();
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
		
		UmlGME::Inheritance cinh;
		UmlGME::ClassBase cbase, cderived;
		UmlGME::Sub csub;
		UmlGME::Base cbc;
		UmlGME::ClassBase cderivedimpl, cderivedintf;
		
		cderivedimpl = GetRealImplementation(derived);
		cderivedintf = GetRealInterface(derived);
		
		cbase = GetRegular(base);
		cinh = UmlGME::Inheritance::Create(cd);
		cinh.position() = MakePosAttr(contain.position(),attmap);
		cbc = UmlGME::Base::Create(cd);
		cbc.dstInheritance_end() = cinh;
		cbc.srcClassBase_end() = cbase;
		
		if((string)cbase.type().name() == "ClassCopy")
			UmlGME::Class::Cast(UmlGME::ClassCopy::Cast(cbase).ref()).IsAbstract() = true;
		else
			cbase.IsAbstract() = true;
		
		cderived = GetRegular(derived);
		csub = UmlGME::Sub::Create(cd);
		csub.srcInheritance_end() = cinh;
		csub.dstClassBase_end() = cderived;
		// Make map for GME Object base
		UmlGME::Class cderivedclass;
		if((string)cderived.type().name() == "ClassCopy")
			cderivedclass = UmlGME::ClassCopy::Cast(cderived).ref();
		else
			cderivedclass = UmlGME::Class::Cast(cderived);
		maphasbaseimpl[cderivedclass] = true;
		maphasbaseintf[cderivedclass] = true;
	
	}
}


// Create Constraints
void MetaGME2UML::CreateConstraints(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd)
{
	if(!constraintHit || (constraintHit && constraintCopy))
	{	vector<MetaGME::Constraint> consts = ps.Constraint_kind_children();
		for(vector<MetaGME::Constraint>::iterator i = consts.begin(); i!=consts.end(); i++)
		{	MetaGME::Constraint constr = *i;
			if(!constraintHit)
			{	constraintHit = true;
				if(AskUserForConstraint(param))
					constraintCopy = true;
				else
					constraintCopy = false;
			}
			if(!constraintCopy)
				break;
			UmlGME::Constraint cconst = UmlGME::Constraint::Create(cd);
			cconst.name() = constr.name();
			cconst.ConstraintEqn() = constr.ConstraintEqn();
			cconst.ConstraintDescription() = constr.ConstraintDescription();
			cconst.position() = constr.position();
			set<MetaGME::HasConstraint> hcs = constr.dstFCO();
			for(set<MetaGME::HasConstraint>::iterator j=hcs.begin(); j!=hcs.end(); j++)
			{
				MetaGME::HasConstraint hc = *j;
				MetaGME::ContainedInPar dst = hc.dstFCO_end();
				UmlGME::ClassBase cdst = GetInterface(dst);
				UmlGME::HasConstraint chc = UmlGME::HasConstraint::Create(cd);
				chc.srcConstraint_end() = cconst;
				chc.dstClassBase_end() = cdst;
			}
			
		}
	}
}

// this routine works incredibly, so that no human being would ever expect it
// it tries to find generated implbase Uml Class for 'cl', where 'cl' is Uml correspondent for 'mg'.
// Previously, mapUmlClass2ImplInheritBases has been initialized with pair< cl, cl> for each cl.
// It means, that even implbase of 'cl' does not exist, the routine still returns 'cl'!!!!!!!
UmlGME::Class MetaGME2UML::GetRealImplementation(MetaGME::ContainedInPar mg)
{	UmlGME::ClassBase cl = mapMetaGME2UmlGME_Class[mg];
//std::string name= cl.name();
if(mapUmlClass2ImplInheritBases.find(cl) != mapUmlClass2ImplInheritBases.end()) {
		return UmlGME::Class::Cast(mapUmlClass2ImplInheritBases[cl].first);
}
	return UmlGME::Class::Cast(cl);
}

UmlGME::ClassBase MetaGME2UML::GetImplementation(MetaGME::ContainedInPar mg)
{	if(implMap.find(mg)!=implMap.end())
		return implMap[mg];
	
	MetaGME::ParadigmSheet ps = MetaGME::ParadigmSheet::Cast(mg.parent());
	UmlGME::ClassDiagram cd = mapMetaGME2UmlGME_Paradigm[ps];
	UmlGME::ClassBase cl = mapMetaGME2UmlGME_Class[mg];
	UmlGME::Class impl = UmlGME::Class::Cast(mapUmlClass2ImplInheritBases[cl].first);
	UmlGME::ClassCopy implref = UmlGME::ClassCopy::Create(cd);
	
	implref.ref() = impl;
	implref.position() = MakePosAttr(mg.position(), attmap);
	implMap[mg] = implref;
	if(impl == cl)
	{	implref.name() = cl.name();
		intfMap[mg] = implref;
		reguMap[mg] = implref;
	}
	else
		implref.name() = (string) cl.name() + "ImplRef";
	return implref;
}

UmlGME::Class MetaGME2UML::GetRealInterface(const MetaGME::ContainedInPar& mg)
{	UmlGME::ClassBase cl = mapMetaGME2UmlGME_Class[mg];
	return UmlGME::Class::Cast(mapUmlClass2ImplInheritBases[cl].second);
}

UmlGME::ClassBase MetaGME2UML::GetInterface(MetaGME::ContainedInPar mg)
{	if(intfMap.find(mg)!=intfMap.end())
		return intfMap[mg];
	
	MetaGME::ParadigmSheet ps = MetaGME::ParadigmSheet::Cast(mg.parent());
	UmlGME::ClassDiagram cd = mapMetaGME2UmlGME_Paradigm[ps];
	UmlGME::ClassBase cl = mapMetaGME2UmlGME_Class[mg];
	UmlGME::Class intf = UmlGME::Class::Cast(mapUmlClass2ImplInheritBases[cl].second);
	
	UmlGME::ClassCopy intfref = UmlGME::ClassCopy::Create(cd);
	intfref.ref() = intf;
	intfref.position() = MakePosAttr(mg.position(), attmap);
	intfMap[mg] = intfref;
	if(intf == cl)
	{	intfref.name() = cl.name();
		implMap[mg] = intfref;
		reguMap[mg] = intfref;
	}
	else
		intfref.name() = (string) cl.name() + "IntfRef";

	return intfref;
}

UmlGME::ClassBase MetaGME2UML::GetRegular(MetaGME::ContainedInPar mg)
{	if(reguMap.find(mg)!=reguMap.end())
		return reguMap[mg];
	
	MetaGME::ParadigmSheet ps = MetaGME::ParadigmSheet::Cast(mg.parent());
	UmlGME::ClassDiagram cd = mapMetaGME2UmlGME_Paradigm[ps];
	UmlGME::ClassBase cl = mapMetaGME2UmlGME_Class[mg];
	UmlGME::Class regu = UmlGME::Class::Cast(cl);
	UmlGME::ClassCopy reguref = UmlGME::ClassCopy::Create(cd);
	reguref.name() = (string) cl.name();
	reguref.ref() = regu;
	reguref.position() = MakePosAttr(mg.position(), attmap);
	reguMap[mg] = reguref;
	if(regu == cl)
	{	reguref.name() = cl.name();
		implMap[mg] = reguref;
		intfMap[mg] = reguref;
	}
	return reguref;
}

void MetaGME2UML::CreateRefereredConnection(UmlGME::ClassBase crefer, UmlGME::ClassBase crefe, MetaGME::Reference reference)
{
	UmlGME::Association cref = UmlGME::Association::Create(crefer.parent());
	cref.srcAssociationClasses_end() = crefer;
	cref.dstAssociationClasses_end() = crefe;
	cref.dstCardinality() = "0..1";
	cref.srcCardinality() = "0..*";
	
	string name = reference.name();
	string value;
	strmap prefMap;
	ConverGeneralPreferenceToMap((string)reference.GeneralPreferences(),prefMap);

	value = GetValueForName("rName",prefMap);
	if(value == "")
	{	value = "ref";
		try
		{	reference.GeneralPreferences() = (string)reference.GeneralPreferences() + "\nrName = " + value;
		}
		catch(udm_exception ce) 
		{	//Error
			string error = "Error: Reference:"+(string)reference.name() + " is read only. The object may be part of a library. Please run this interpreter on the library mga file, refresh library in this file and then run the interpreter";
			throw udm_exception(error);
		}
	}
	cref.dstRolename() = value;
	
	value = GetValueForName("rrName",prefMap);
	if(value == "")
	{	value = "referedby" + name;
		try
		{	reference.GeneralPreferences() = (string)reference.GeneralPreferences() + "\nrrName = " + value;
		}
		catch(udm_exception ce) 
		{	//Error
			string error = "Error: Reference:"+(string)reference.name() + " is read only. The object may be part of a library. Please run this interpreter on the library mga file, refresh library in this file and then run the interpreter";
			throw udm_exception(error);

		}
	}
	cref.srcRolename() = value;
}
void MetaGME2UML::CreateMembershipConnection(UmlGME::ClassBase cset, UmlGME::ClassBase cmember, MetaGME::Set set)
{
	UmlGME::Association cms = UmlGME::Association::Create(cset.parent());
	cms.srcAssociationClasses_end() = cmember;
	cms.dstAssociationClasses_end() = cset;
	cms.dstCardinality() = "0..*";
	cms.srcCardinality() = "0..*";
	
	string name = set.name();
	string value;
	strmap prefMap;
	ConverGeneralPreferenceToMap((string)set.GeneralPreferences(),prefMap);
	
	value = GetValueForName("mName",prefMap);
	if(value == "")
	{	value = "members";
		try
		{	set.GeneralPreferences() = (string)set.GeneralPreferences() + "\nmName = " + value;
		}
		catch(udm_exception ce) 
		{	//Error
			string error = "Error: Set:"+(string)set.name() + " is read only. The object may be part of a library. Please run this interpreter on the library mga file, refresh library in this file and then run the interpreter";
			throw udm_exception(error);
		}
	}
	cms.srcRolename() = value;
// VIZA this code used to be commented out
	
	value = GetValueForName("sName",prefMap);
	if(value == "")
	{	value = "set" + name;
		try
		{	set.GeneralPreferences() = (string)set.GeneralPreferences() + "\nsName = " + value;
		}
		catch(udm_exception ce) 
		{	//Error
			MetaGME::ParadigmSheet ps = MetaGME::ParadigmSheet::Cast(set.parent());
			string error = "Error: Set:"+(string)set.name()+ " in ParadigmSheet:" + (string)ps.name() + " is read only. The object may be part of a library. Please run this interpreter on the library mga file, refresh library in this file and then run the interpreter";
			throw udm_exception(error);
		}
	}
	cms.dstRolename() = value;
	
// VIZA end
	//cms.dstRolename() = "";
}

template <class In, class Out, class Fn>
std::set<Out>& trans(const std::set<In>& input, std::set<Out>& output, const Fn f) {
	std::transform(input.begin(), input.end(), set_inserter(output), f);
	return output;
}

template<class C>
struct Copy_Set : public unary_function<std::set<C>, const std::set<C>& > {
	std::set<C>& dest;
	Copy_Set(std::set<C>& dest) : dest(dest) { }
	const std::set<C>& operator()(const std::set<C>& in) {
		std::copy(in.begin(), in.end(), set_inserter(dest));
		return in;
	}
};

template<class T>
std::set<T> flatten_set(const std::set<std::set<T> >& s) {
	std::set<T> ret;
	std::for_each(s.begin(), s.end(), Copy_Set<T>(ret));
	return ret;
}

template<typename UF>
struct _GetAllConnections {
	// i.e. UF::result_type should be a AClassAssocAttr
	typedef typename UF::result_type::connector Conn;
	const UF& F;
	_GetAllConnections(const UF& f) : F(f) { }
	std::set<Conn> operator()(const MetaGME::BaseFCO& fco)
	{
		std::set<std::set<Conn> > conns;
		MetaGME::BaseFCO base = RefByProxy(fco);
		conns.insert(F(base));
		if (base.type() == MetaGME::Atom::meta) {
			MetaGME::Atom atom = MetaGME::Atom::Cast(base);
			trans(std::set<MetaGME::AtomProxy>(atom.src()), conns, F);
		} else if (base.type() == MetaGME::FCO::meta) {
			MetaGME::FCO fco = MetaGME::FCO::Cast(base);
			trans(std::set<MetaGME::FCOProxy>(fco.src()), conns, F);
		} else if (base.type() == MetaGME::Model::meta) {
			MetaGME::Model model = MetaGME::Model::Cast(base);
			trans(std::set<MetaGME::ModelProxy>(model.src()), conns, F);
		} else if (base.type() == MetaGME::Set::meta) {
			MetaGME::Set set = MetaGME::Set::Cast(base);
			trans(std::set<MetaGME::SetProxy>(set.src()), conns, F);
		} else if (base.type() == MetaGME::Reference::meta) {
			MetaGME::Reference ref = MetaGME::Reference::Cast(base);
			trans(std::set<MetaGME::ReferenceProxy>(ref.src()), conns, F);
		} else if (base.type() == MetaGME::Connection::meta) {
			MetaGME::Connection ref = MetaGME::Connection::Cast(base);
			trans(std::set<MetaGME::ConnectionProxy>(ref.src()), conns, F);
		}
		return flatten_set(conns);
	}
};

template<class UF>
std::set<typename _GetAllConnections<UF>::Conn> GetAllConnections(const MetaGME::BaseFCO& fco, const UF& f) {
	_GetAllConnections<UF> gac(f);
	return gac(fco);
}

template<class UF>
_GetAllConnections<UF> GetAllConnectionsFunctor(const UF& f) {
	return _GetAllConnections<UF>(f);
}

void print_refport_attr_explanation(const MetaGME::Connection& connection, const std::set<MetaGME::Reference>& refport_containers, const std::string& assoc_rolename, const std::string& s_or_d)
{
	std::string refport_container_names;
	std::for_each(refport_containers.begin(), refport_containers.end(), [&](const MetaGME::Reference& ref){ 
		refport_container_names += string(ref.name()) + ", ";
	});
	refport_container_names = refport_container_names.substr(0, refport_container_names.size() - 2);
	string msg = "Connection <a href=\"mga:" + UdmGme::UdmId2GmeId(connection.uniqueId()) + "\">";
	msg += string(connection.name()) + "</a> may have " + (s_or_d == "s" ? "source" : "destination") +" refport parent";
	if (refport_containers.size() != 1)
		msg += "s";
	msg += " ";
	msg += refport_container_names + ". ";
	std::string gme_id = UdmGme::UdmId2GmeId(connection.uniqueId());
	msg += "<a href=\"javascript:"
		"gme.MgaProject.BeginTransactionInNewTerr(); "
		"conn = gme.MgaProject.GetObjectByID('" + gme_id + "');"
		"conn.SetAttributeByNameDisp('GeneralPreferences', conn.GetAttributeByNameDisp('GeneralPreferences') + '\\n' + '" + s_or_d + "RefParent=" + assoc_rolename + "_refport_parent');"
		"gme.MgaProject.CommitTransaction();"
		"gme.ShowFCO(conn, true);\">";
	msg += "Add \"" + s_or_d + "RefParent=" + assoc_rolename + "_refport_parent\" to the General Preferences attribute to generate refport container associations.";
	msg += "</a>";
	ConsoleMessage(msg);
}


void MetaGME2UML::CreateRefportContainersAssociations(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd)
{
	vector<MetaGME::Connection> connections = ps.Connection_kind_children();
	for (vector<MetaGME::Connection>::iterator i = connections.begin(); i != connections.end(); i++)
	{
		MetaGME::Connection connection = *i;
		std::set<MetaGME::BaseConnection> baseConnections;
		baseConnections.insert(connection);
		std::set<MetaGME::ConnectionProxy> connectionProxies = connection.src();
		std::copy(connectionProxies.begin(), connectionProxies.end(), set_inserter(baseConnections));

		std::set<std::set<MetaGME::AssociationClass> > aclasses;
		trans(baseConnections, aclasses, std::mem_fun_ref(&MetaGME::BaseConnection::srcConnection));
		trans(baseConnections, aclasses, std::mem_fun_ref(&MetaGME::BaseConnection::dstConnection));
		std::set<MetaGME::AssociationClass> aclasses_ = flatten_set(aclasses);
		for (std::set<MetaGME::AssociationClass>::iterator aclassesIt = aclasses_.begin(); 
				aclassesIt != aclasses_.end(); aclassesIt++) {
			MetaGME::AssociationClass aclass = *aclassesIt;
			MetaGME::Connector connector;
			if (Uml::IsDerivedFrom(((MetaGME::AssociationClass_Members_Base)aclass.dstConnection_end()).type(), MetaGME::BaseConnection::meta)) {
				connector = MetaGME::Connector::Cast(aclass.srcConnection_end());
			} else {
				connector = MetaGME::Connector::Cast(aclass.dstConnection_end());
			}
			std::set<MetaGME::ConnectorToDestination> ctodst = connector.dstFCO();
			if (ctodst.size() != 1)
			{
				throw udm_exception(string("Connection '") + string(connection.name()) + "' does not have exactly one destination");
			}
			std::set<MetaGME::SourceToConnector> srctoc = connector.srcFCO();
			if (srctoc.size() != 1)
			{
				throw udm_exception(string("Connection '") + string(connection.name()) + "' does not have exactly one source");
			}

			strmap prefMap;
			ConverGeneralPreferenceToMap((string)connection.GeneralPreferences(), prefMap);
		
			MetaGME::BaseFCO dstFco = ctodst.begin()->dstFCO_end();
			std::string dstrolename = GetValueForName("dRefParent",prefMap);
			string dst_assoc_rolename = GetValueForName("dName",prefMap);
			MetaGME::BaseFCO srcFco = srctoc.begin()->srcFCO_end();
			string srcrolename = GetValueForName("sRefParent",prefMap);
			string src_assoc_rolename = GetValueForName("sName",prefMap);

			if (dstFco) {
				std::string dstrrolename = GetValueForName("rdRefParent", prefMap);
				if (dstrrolename == "") {
					dstrrolename = dstrolename + "_rev";
				}
				std::set<MetaGME::Reference> refport_containers = GetRefportContainers(RefByProxy(dstFco), connection);
				if (ctodst.begin()->dstRolename() == "" && srctoc.begin()->srcRolename() == "") { // bidirectional connection
					std::set<MetaGME::Reference> src_refport_containers = GetRefportContainers(RefByProxy(srcFco), connection);
					std::copy(src_refport_containers.begin(), src_refport_containers.end(), set_inserter(refport_containers));
				}
				if (dstrolename != "")
					CreateRefportContainerAssociation(connection, dst_assoc_rolename, dstrolename, dstrrolename, refport_containers, cd);
				else if (refport_containers.size() > 0)
					print_refport_attr_explanation(connection, refport_containers, dst_assoc_rolename, "d");
			}

			if (srcFco)
			{
				std::string srcrrolename = GetValueForName("rsRefParent", prefMap);
				if (srcrrolename == "") {
					srcrrolename = srcrolename + "_rev";
				}
				std::set<MetaGME::Reference> refport_containers = GetRefportContainers(RefByProxy(srcFco), connection);
				if (ctodst.begin()->dstRolename() == "" && srctoc.begin()->srcRolename() == "") { // bidirectional connection
					std::set<MetaGME::Reference> dst_refport_containers = GetRefportContainers(RefByProxy(dstFco), connection);
					std::copy(dst_refport_containers.begin(), dst_refport_containers.end(), set_inserter(refport_containers));
				}
				if (srcrolename != "")
					CreateRefportContainerAssociation(connection, src_assoc_rolename, srcrolename, srcrrolename, refport_containers, cd);
				else if (refport_containers.size() > 0)
					print_refport_attr_explanation(connection, refport_containers, src_assoc_rolename, "s");
			}
		}
	}
}


std::set<MetaGME::BaseFCO> GetSelfAndSubtypes(const MetaGME::BaseFCO& fco)
{
	std::set<MetaGME::BaseFCO> basefcos_processed;
	std::deque<MetaGME::BaseFCO> basefcos_to_process;
	basefcos_to_process.push_back(fco);
	while (basefcos_to_process.size()) {
		MetaGME::BaseFCO base = basefcos_to_process.front();
		basefcos_to_process.pop_front();
		base = RefByProxy(base);
		if (basefcos_processed.find(base) != basefcos_processed.end())
			continue;
		basefcos_processed.insert(base);

		// Get all derived FCOs of base
		std::set<MetaGME::BaseInheritance> baseinhs = 
			GetAllConnections(base, std::mem_fun_ref(&MetaGME::BaseFCO::bdst));
		std::set<MetaGME::Inheritance> inheritances;
		trans(baseinhs, inheritances, std::mem_fun_ref(&MetaGME::BaseInheritance::bdst_end));
		std::set<std::set<MetaGME::DerivedInheritance> > derivedinhs;
		trans(inheritances, derivedinhs, std::mem_fun_ref(&MetaGME::Inheritance::ddst));
		std::set<MetaGME::DerivedInheritance> derivedinhs_ = flatten_set(derivedinhs);
		std::set<MetaGME::BaseFCO> derivedfcos;
		trans(derivedinhs_, derivedfcos, std::mem_fun_ref(&MetaGME::DerivedInheritance::ddst_end));
		std::copy(derivedfcos.begin(), derivedfcos.end(), std::back_inserter(basefcos_to_process));
	}
	return basefcos_processed;
}


std::set<MetaGME::BaseFCO> MetaGME2UML::GetSelfAndSupertypes(const MetaGME::BaseFCO& fco)
{
	auto memo = m_SelfAndSupertypeMemo.find(fco);
	if (memo != m_SelfAndSupertypeMemo.end())
	{
		return memo->second;
	}

	std::set<MetaGME::BaseFCO> basefcos_processed;
	std::deque<MetaGME::BaseFCO> basefcos_to_process;
	basefcos_to_process.push_back(fco);
	while (basefcos_to_process.size()) {
		MetaGME::BaseFCO base = basefcos_to_process.front();
		basefcos_to_process.pop_front();
		base = RefByProxy(base);
		if (basefcos_processed.find(base) != basefcos_processed.end())
			continue;
		basefcos_processed.insert(base);

		// Get all supertype FCOs of base
		std::set<MetaGME::DerivedInheritance> dinhs = 
			GetAllConnections(base, std::mem_fun_ref(&MetaGME::BaseFCO::dsrc));
		std::set<MetaGME::Inheritance> inheritances;
		trans(dinhs, inheritances, std::mem_fun_ref(&MetaGME::DerivedInheritance::dsrc_end));
		std::set<std::set<MetaGME::BaseInheritance> > binhs;
		trans(inheritances, binhs, std::mem_fun_ref(&MetaGME::Inheritance::bsrc));
		std::set<MetaGME::BaseInheritance> binhs_ = flatten_set(binhs);
		std::set<MetaGME::BaseFCO> superfcos;
		trans(binhs_, superfcos, std::mem_fun_ref(&MetaGME::BaseInheritance::bsrc_end));
		std::copy(superfcos.begin(), superfcos.end(), std::back_inserter(basefcos_to_process));
	}
	m_SelfAndSupertypeMemo.emplace(std::pair<MetaGME::BaseFCO, std::set<MetaGME::BaseFCO> >(fco, basefcos_processed));
	return basefcos_processed;
}

struct IsDerivedFrom : public unary_function<Udm::Object, bool>
{
	const Uml::Class& class_;
	IsDerivedFrom(const Uml::Class& class_) : class_(class_) { }
	bool operator()(const Udm::Object& o) const {
		return Uml::IsDerivedFrom(o.type(), class_);
	}
};

std::set<MetaGME::BaseFCO> MetaGME2UML::GetContainersAndTheirSubtypes(const MetaGME::BaseFCO& fco) {
	std::set<std::set<MetaGME::Containment>> superContainments;
	trans(GetSelfAndSupertypes(fco), superContainments, GetAllConnectionsFunctor(std::mem_fun_ref(&MetaGME::BaseFCO::dstContainment)));
	std::set<MetaGME::Containment> containments = flatten_set(superContainments);
	std::set<MetaGME::BaseModel> containers;
	trans(containments, containers, std::mem_fun_ref(&MetaGME::Containment::dstContainment_end));
	std::set<std::set<MetaGME::BaseFCO> > containers_and_supertypes;
	trans(containers, containers_and_supertypes, std::ptr_fun(&GetSelfAndSubtypes));
	return flatten_set(containers_and_supertypes);
}

struct CanBeContainedInSameContainer : public std::unary_function<const MetaGME::BaseFCO, bool> {
	const MetaGME::BaseFCO& fco1;
	MetaGME2UML& metaGME2UML;
	CanBeContainedInSameContainer(const MetaGME::BaseFCO& fco1, MetaGME2UML& metaGME2UML) : fco1(fco1), metaGME2UML(metaGME2UML) { }
	
	bool operator ()(const MetaGME::BaseFCO& fco2) const {
		std::set<MetaGME::BaseFCO> fco1_containers = metaGME2UML.GetContainersAndTheirSubtypes(fco1);
		std::set<MetaGME::BaseFCO> fco2_containers = metaGME2UML.GetContainersAndTheirSubtypes(fco2);

		std::set<MetaGME::BaseFCO> common_container_subtypes;
		std::set_intersection(fco1_containers.begin(), fco1_containers.end(),
			fco2_containers.begin(), fco2_containers.end(),
			set_inserter(common_container_subtypes));
		return common_container_subtypes.size() != 0;
	}
};

std::set<MetaGME::Reference> MetaGME2UML::GetRefportContainers(MetaGME::BaseFCO& connend, const MetaGME::Connection& connection)
{
	std::set<MetaGME::BaseFCO> subtypes;
	std::set<MetaGME::BaseFCO> subtypes_ = GetSelfAndSubtypes(connend);
	std::set<std::set<MetaGME::BaseFCO>> subtypesSupers_;

	auto self = this;
	trans(subtypes_, subtypesSupers_, [&self](const MetaGME::BaseFCO& fco) -> std::set<MetaGME::BaseFCO> { return self->GetSelfAndSupertypes(fco); });
	std::set<MetaGME::BaseFCO> subtypesSupers = flatten_set(subtypesSupers_);
	std::copy(subtypesSupers.begin(), subtypesSupers.end(), set_inserter(subtypes_));
	// connections cannot be ports
	std::remove_copy_if(subtypes_.begin(), subtypes_.end(), set_inserter(subtypes), IsDerivedFrom(MetaGME::Connection::meta));
#ifdef _DEBUG
	std::vector<std::string> subtypes_str;
	std::transform(subtypes.begin(), subtypes.end(), std::back_inserter(subtypes_str), std::ptr_fun(ExName));
	std::vector<std::string> subtypesSupers_str;
	std::transform(subtypesSupers.begin(), subtypesSupers.end(), std::back_inserter(subtypesSupers_str), std::ptr_fun(ExName));
#endif

	// now compute port_containers: models that can contain a subtype as a port
	std::set<MetaGME::Model> port_containers;
	{
	std::set<std::set<MetaGME::Containment> > containments;
	trans(subtypes, containments, GetAllConnectionsFunctor(std::mem_fun_ref(&MetaGME::FCOBase::dstContainment)));
	std::set<MetaGME::Containment> containments_ = flatten_set(containments);
	std::set<MetaGME::Containment> port_containments;
	std::remove_copy_if(containments_.begin(), containments_.end(), set_inserter(port_containments), std::not1(std::mem_fun_ref(&MetaGME::Containment::IsPort)));

	std::set<MetaGME::BaseModel> base_port_containers;
	trans(port_containments, base_port_containers, std::mem_fun_ref(&MetaGME::Containment::dstContainment_end));
	std::set<MetaGME::BaseFCO> base_port_containers_;
	trans(base_port_containers, base_port_containers_, std::ptr_fun(&RefByProxy));
	std::set<std::set<MetaGME::BaseFCO> > base_port_containers_and_subtypes;
	trans(base_port_containers_, base_port_containers_and_subtypes, std::ptr_fun(&GetSelfAndSubtypes));

	MetaGME::Model (*Model_cast)(const Udm::Object&) = &MetaGME::Model::Cast;
	trans(flatten_set(base_port_containers_and_subtypes), port_containers, std::ptr_fun(Model_cast));
	}
#ifdef _DEBUG
	std::vector<std::string> port_containers_str;
	std::transform(port_containers.begin(), port_containers.end(), std::back_inserter(port_containers_str), std::ptr_fun(ExName));
#endif

	// Now compute refport_containers: the references that refer to port_containers
	std::set<MetaGME::Reference> refport_containers;
	{
	std::set<std::set<MetaGME::ModelProxy> > port_containers_refs;
	trans(port_containers, port_containers_refs, std::mem_fun_ref(&MetaGME::Model::src));
	std::set<MetaGME::ModelProxy> port_container_refs_ = flatten_set(port_containers_refs);
	std::set<MetaGME::BaseModel> port_container_refs_base;
	std::copy(port_container_refs_.begin(), port_container_refs_.end(), set_inserter(port_container_refs_base));
	std::copy(port_containers.begin(), port_containers.end(), set_inserter(port_container_refs_base));

	std::set<std::set<MetaGME::BaseFCO> > port_container_supertypes_;
	auto self = this;
	trans(port_container_refs_base, port_container_supertypes_, [&self](const MetaGME::BaseModel& fco) -> std::set<MetaGME::BaseFCO> { return self->GetSelfAndSupertypes(fco); });
	std::set<MetaGME::BaseFCO> port_container_supertypes = flatten_set(port_container_supertypes_);
#ifdef _DEBUG
	std::vector<std::string> port_container_supertypes_str;
	std::transform(port_container_supertypes.begin(), port_container_supertypes.end(), std::back_inserter(port_container_supertypes_str), std::ptr_fun(ExName));
#endif

	std::set<std::set<MetaGME::ReferTo> > port_container_refs_refertos;
	trans(port_container_supertypes, port_container_refs_refertos, GetAllConnectionsFunctor(std::mem_fun_ref(&MetaGME::BaseModel::srcReferTo)));
	std::set<MetaGME::ReferTo> port_container_refs_refertos_ = flatten_set(port_container_refs_refertos);
	std::set<MetaGME::BaseReference> baserefport_containers;
	trans(port_container_refs_refertos_, baserefport_containers, std::mem_fun_ref(&MetaGME::ReferTo::srcReferTo_end));
	std::set<MetaGME::BaseFCO> baserefport_containers_;
	trans(baserefport_containers, baserefport_containers_, std::ptr_fun(&RefByProxy));
#ifdef _DEBUG
	std::vector<std::string> baserefport_containers_str;
	std::transform(baserefport_containers.begin(), baserefport_containers.end(), std::back_inserter(baserefport_containers_str), std::ptr_fun(ExName));
#endif
	// references in refport_containers can only be refports if contained by something that can also contain the connection
	// FIXME: a descendant of the other end of the connection must also be contained
	for (std::set<MetaGME::BaseFCO>::iterator baserefport_containerIt = baserefport_containers_.begin(); baserefport_containerIt != baserefport_containers_.end();)
	{
		std::set<MetaGME::BaseFCO> subtypes = GetSelfAndSubtypes(*baserefport_containerIt);
		if (std::any_of(subtypes.begin(), subtypes.end(), CanBeContainedInSameContainer(connection, *this)))
			baserefport_containerIt++;
		else
			baserefport_containers_.erase(baserefport_containerIt++);
	}

	MetaGME::Reference (*Reference_cast)(const Udm::Object&) = &MetaGME::Reference::Cast;
	trans(baserefport_containers_, refport_containers, std::ptr_fun(Reference_cast));
	// FIXME: filter out subtypes of refport_containers
	}

	return refport_containers;
}

void MetaGME2UML::CreateRefportContainerAssociation(const MetaGME::Connection& connection, const std::string& assoc_rolename, const std::string& rolename, const std::string& rrolename, const std::set<MetaGME::Reference>& refport_containers, UmlGME::ClassDiagram& cd)
{
	if(refport_containers.size() == 0)
	{
		return;
	}
	// If there are more than one refport_container (or if the association class and references are in different namespaces),
	// then we need to create a ClassDiagram to contain the abstract base class (or references to the classes)
	if (refport_containers.size() == 1)
	{	
		MetaGME::Reference ref = *refport_containers.begin();
		UmlGME::ClassBase cconnectionclass = GetInterface(connection);
		UmlGME::ClassBase cref = GetInterface(ref);
		if (Udm::Object(cconnectionclass.parent()) == Udm::Object(cref.parent()))
		{
			CreateRefportConnection(cconnectionclass, cref, rolename, rrolename);
			return;
		}
	}
	UmlGME::Class cconnectionclass = GetRealInterface(connection);
	UmlGME::ClassDiagram classdiagram = UmlGME::ClassDiagram::Create(urf);
	classdiagram.name() = "zC_" + (string)cconnectionclass.name() + "_" + assoc_rolename + "_RefportContainer_Association";
	UmlGME::ClassCopy refp = UmlGME::ClassCopy::Create(classdiagram);
	refp.name() = cconnectionclass.name();
	refp.position() = MakePosition(50,50,50,50);
	refp.ref() = cconnectionclass;

	if (refport_containers.size() == 1)
	{	
		MetaGME::Reference ref = *refport_containers.begin();
		UmlGME::ClassBase cconnectionclass = GetInterface(connection);
		UmlGME::ClassBase cref = GetInterface(ref);
		UmlGME::Class cref_class;
		if (cref.type() == UmlGME::Class::meta) {
			cref_class = UmlGME::Class::Cast(cref);
		} else {
			cref_class = UmlGME::ClassCopy::Cast(cref).ref();
		}
		UmlGME::ClassCopy refport_container = UmlGME::ClassCopy::Create(classdiagram);
		refport_container.name() = (string)cref_class.name();
		refport_container.position() = MakePosition(350,50,350,50);
		refport_container.ref() = cref_class;
		CreateRefportConnection(refp, refport_container, rolename, rrolename);
		return;
	}

	UmlGME::Class refport_container = UmlGME::Class::Create(classdiagram);
	refport_container.name() = (string)cconnectionclass.name() + "_" + assoc_rolename + "_RPContainer_Base";
	refport_container.position() = MakePosition(350,50,350,50);
	refport_container.Stereotype() = "FCO";
	refport_container.IsAbstract() = true;
	CreateRefportConnection(refp, refport_container, rolename, rrolename);

	UmlGME::Inheritance cinh = UmlGME::Inheritance::Create(classdiagram);
	cinh.position() = MakePosition(250,150,250,150);
	UmlGME::Base base = UmlGME::Base::Create(classdiagram);
	base.dstInheritance_end() = cinh;
	base.srcClassBase_end() = refport_container;
	int xa = 150, ya = 250;
	for (std::set<MetaGME::Reference>::const_iterator refport_container_it = refport_containers.begin();
		refport_container_it != refport_containers.end(); refport_container_it++)
	{
		const MetaGME::Reference ref = *refport_container_it;
		UmlGME::ClassBase cref = GetRealInterface(ref);
		UmlGME::Class crefc;
		if (cref.type().type() == UmlGME::ClassCopy::meta)
			crefc = UmlGME::ClassCopy::Cast(cref).ref();
		else
			crefc = UmlGME::Class::Cast(cref);
		UmlGME::ClassCopy obc = UmlGME::ClassCopy::Create(classdiagram);
		obc.name() = crefc.name();
		obc.ref() = crefc;
		obc.position() = MakePosition(xa,ya,xa,ya);
		xa += 200;
		UmlGME::Sub csub = UmlGME::Sub::Create(classdiagram);
		csub.srcInheritance_end() = cinh;
		csub.dstClassBase_end() = obc;
	}
}

void MetaGME2UML::CreateRefportConnection(const UmlGME::ClassBase& connection, const UmlGME::ClassBase& refport_container, const std::string& rolename, const std::string& rrolename)
{
	UmlGME::Association cref = UmlGME::Association::Create(connection.parent());

	cref.srcAssociationClasses_end() = connection;
	cref.dstAssociationClasses_end() = refport_container;
	cref.dstCardinality() = "0..1";
	cref.srcCardinality() = "0..*";
	cref.dstRolename() = rolename;
	cref.srcRolename() = rrolename;
}


void MetaGME2UML::Phase6_CreateGMEObject()
{
	for(map_CIP2CB::iterator i=mapMetaGME2UmlGME_Class.begin();i!=mapMetaGME2UmlGME_Class.end();i++)
	{	
		pair<MetaGME::ContainedInPar, UmlGME::ClassBase> p = *i;
		MetaGME::ContainedInPar mg = p.first;
		UmlGME::ClassBase cb = p.second;
		UmlGME::Class cln = GetRealImplementation(mg);
		UmlGME::Class cle = GetRealInterface(mg);
		if(cb == Udm::null)
			continue;
		if((string)cb.type().name() == "Class")
		{	UmlGME::Class cl =  UmlGME::Class::Cast(cb);
			if(maphasbaseimpl.find(cl)== maphasbaseimpl.end() && maphasbaseintf.find(cl)== maphasbaseintf.end())
			{	maphasbaseimpl[cl] = true; maphasbaseintf[cl] = true;
				if(cln == cle)
				{	CreateGMEBaseAssociation(cl);
				}
				else
				{	CreateGMEBaseAssociation(cln);
					CreateGMEBaseAssociation(cle);
				}
			}
			else if(maphasbaseimpl.find(cl)== maphasbaseimpl.end() )
			{	maphasbaseimpl[cl] = true;
				CreateGMEBaseAssociation(cln);
			}
			else if(maphasbaseintf.find(cl)== maphasbaseintf.end() )
			{	maphasbaseintf[cl] = true;
				CreateGMEBaseAssociation(cle);
			}

		}
	}

}


void MetaGME2UML::InitializeSheets(MetaGME::RootFolder grf, Udm::Object urf)
{	
	//We need to check here and see if the MetaGME project's RootFolder contains a Namespace
	//1. If it doesn't, then proceed as before
	//2. If it does, then create a Namespace element in the UML package, and place these objects in there:
	//  -zC_GMEInheritanceSheet
	//  -zC_RootFolderCompositionSheet

	string rootFolderNS = grf.Namespace();
	UmlGME::Namespace topLevelNS;

	if(rootFolderNS == "")  //If NS is empty, create in top level package
	{
		umlGMEObjectDiagram = UmlGME::ClassDiagram::Create(urf);
		umlGMErootDiagram = UmlGME::ClassDiagram::Create(urf);
		topNamespace = Udm::null;
	}

	else  //otherwise make a new namespace and return it to the caller
	{
		topLevelNS = UmlGME::Namespace::Create(urf);
		topLevelNS.name() = rootFolderNS;

		umlGMEObjectDiagram = UmlGME::ClassDiagram::Create(topLevelNS);
		/* Daniel, 5-15-07: The RootFolder isn't in a Namespace, so create the umlGMErootDiagram in the urf instead of the topLevelNS */
		umlGMErootDiagram = UmlGME::ClassDiagram::Create(urf);
		topNamespace = topLevelNS;
	}

	// Initializing Gme Object Sheet
	umlGMEObjectDiagram.name() = "zC_GMEInheritanceSheet";
	UmlGME::Class umlGMEObjectBase = UmlGME::Class::Create(umlGMEObjectDiagram);
	umlGMEObjectBase.name() = "MgaObject";
	umlGMEObjectBase.position() = "UML(350,5);Constraints(350,5);";
	umlGMEObjectBase.IsAbstract() = true;
	umlGMEObjectBase.Attributes() = "name : String[0..1] \nposition : String[0..1]\n";
	umlGMEObjectBaseInh = UmlGME::Inheritance::Create(umlGMEObjectDiagram);
	umlGMEObjectBaseInh.position() = "UML(350,100);Constraints(350,100);";
	UmlGME::Base cbc = UmlGME::Base::Create(umlGMEObjectDiagram);
	cbc.dstInheritance_end() = umlGMEObjectBaseInh;
	cbc.srcClassBase_end() = umlGMEObjectBase;	

	// Initializing Gme Root Folder Sheet
	umlGMErootDiagram.name() = "zC_RootFolderCompositionSheet";
	umlGMErootFolder = UmlGME::Class::Create(umlGMErootDiagram);
	umlGMErootFolder.name() = "RootFolder";
	umlGMErootFolder.Stereotype() = "Folder";
	umlGMErootFolder.Attributes() = "name : String[0..1]\n";
	umlGMErootFolder.position() = "UML(350,5);Constraints(350,5);";
	
	// Adding a self composition to enable accessing Libraries
	UmlGME::Composition rfcomp = UmlGME::Composition::Create(umlGMErootDiagram);
	rfcomp.Cardinality() = "0..*";
	rfcomp.srcChildren_end() = umlGMErootFolder;
	rfcomp.dstParent_end() = umlGMErootFolder;

	rfx=0; rfy = 200; gox=0; goy = 200;

	iox=100 ; ioy = 200;

	attmap["ClassDiagram"] = "UML";
	attmap["Constraints"]  = "Constraints";

	conmap["ClassDiagram"] = "UML";

	constrmap["Constraints"] = "Constraints";

	// Create Root Folder Association
	//CreateGMEBaseAssociation(umlGMErootFolder);


	
}
void MetaGME2UML::CreateRootFolderAssociation(UmlGME::Class cl)
{	
	UmlGME::ClassCopy cpy = UmlGME::ClassCopy::Create(umlGMErootDiagram);
	cpy.name() = cl.name();
	cpy.ref() = cl;
	cpy.position() = MakePosition(rfx,rfy,rfx,rfy);
	rfx = (rfx+150)%1200;
	rfy += (rfx==0)? 100:0;
	UmlGME::Composition comp = UmlGME::Composition::Create(umlGMErootDiagram);
	comp.srcChildren_end() = cpy;
	comp.dstParent_end() = umlGMErootFolder;
}

void MetaGME2UML::CreateGMEBaseAssociation(UmlGME::Class cl)
{	
	if((string)cl.Stereotype() == "Folder")
		return;
	UmlGME::ClassCopy cpy = UmlGME::ClassCopy::Create(umlGMEObjectDiagram);
	cpy.name() = cl.name();
	cpy.ref() = cl;
	cpy.position() = MakePosition(gox,goy,gox,goy);
	gox = (gox+150)%1200;
	goy += (gox==0)? 100:0;
	UmlGME::Sub comp = UmlGME::Sub::Create(umlGMEObjectDiagram);
	comp.srcInheritance_end() = umlGMEObjectBaseInh;
	comp.dstClassBase_end() = cpy;
}

string MetaGME2UML::ConvertPosition(string pos)
{	
	int ax,ay,cox,coy,vx,vy,cx,cy;
	//cout << "Position " << pos << endl;
	if(sscanf_s(pos.c_str(),"Attributes(%d,%d);Constraints(%d,%d);Visualization(%d,%d);ClassDiagram(%d,%d);",&ax,&ay,&cox,&coy,&vx,&vy,&cx,&cy)==8)
		return MakePosition(cx,cy,cox,coy);
	
	sscanf_s(pos.c_str(),"Visualization(%d,%d);ClassDiagram(%d,%d);",&vx,&vy,&cx,&cy);
	return MakePosition(cx,cy);
}

string MetaGME2UML::MakePosAttr(string spos, map<string, string> posmap)
{	map<string, string > pmap;
	GetPosAttr(spos, pmap);
	string out;
	for(map<string, string>::iterator i=posmap.begin(); i!=posmap.end();i++)
	{	string val = i->first;
		map<string, string>::iterator mi = pmap.find(val);
		if(mi==pmap.end())
			continue;
		out += (string)i->second + "(" + (mi->second) + ");";
	}
	//cout << "PositionGME: " << spos << endl;
	//cout << "PositionUML: " << out << endl;
	return out;
}

void MetaGME2UML::GetPosAttr(string spos, map<string, string> &atmap)
{	StringTokenizer stok(spos, ";() ");
	StringTokenizer::iterator i,j;
	for(i=stok.begin();i!=stok.end();i++)
	{	j=i;
		i++;
		if(i!=stok.end())
		{	atmap[*j] = *i;
		}
	}
}

bool MetaGME2UML::GetPosAttr(string spos, string aspect, int &x, int &y)
{	map<string, string > pmap;
	GetPosAttr(spos, pmap);
	if( pmap.find(aspect) == pmap.end())
		return false;
	
	string pos = pmap[aspect];
	int tx, ty;
	if(sscanf_s(pos.c_str(),"%d,%d", &tx, &ty) != 2)
		return false;

	x= tx, y=ty;
	return true;
}

string MetaGME2UML::MakePosition(int ux, int uy, int cx, int cy)
{	char position[555];
	sprintf_s(position,"UML(%d,%d);Constraints(%d,%d);",ux,uy,cx,cy);
	return position;
}

string MetaGME2UML::MakePosition(int ux, int uy)
{	char position[555];
	sprintf_s(position,"UML(%d,%d);",ux,uy);
	return position;
}

void MetaGME2UML::ConverGeneralPreferenceToMap(string pref, strmap &prefmap)
{	StringTokenizer lines(pref, "\n");
	for(StringTokenizer::iterator i=lines.begin();i!=lines.end();i++)
	{	string line = *i;
		
		StringTokenizer words(line, "=");
		if(words.size()!=2)
			continue;
		
		StringTokenizer::iterator j = words.begin();
		string key = *j; ++j;
		string value = *j;

		unsigned int ks, ke, vs, ve;
		for(ks=0;ks<key.length();++ks)
		{	if(key[ks] != ' ')
				break;
		}
		for(ke=key.length()-1;ke>=0;--ke)
		{	if(key[ke] != ' ')
				break;
		}
				
		for(vs=0;vs<value.length();++vs)
		{	if(value[vs] != ' ')
				break;
		}
		for(ve=value.length()-1;ve>=0;--ve)
		{	if(value[ve] != ' ')
				break;
		}
		
		string rkey = key.substr(ks,ke+1-ks);
		string rvalue = value.substr(vs,ve+1-vs);
		
		prefmap[rkey] = rvalue;
		
	}
}

string MetaGME2UML::GetValueForName(string name, strmap &prefmap)
{	strmap::iterator mi = prefmap.find(name);
	if(mi==prefmap.end())
		return string();
	else
		return mi->second;
}

void trim( std::string& toTrim)
{
	if ( toTrim.empty())
		return;
	std::string::iterator i;
	for( i= toTrim.begin(); isspace( *i); ++i) {}
	toTrim.erase( toTrim.begin(), i);
	std::string::reverse_iterator ri;
	for( ri= toTrim.rbegin(); isspace( *ri); ++ri) {}
	toTrim.erase( ri.base(), toTrim.rbegin().base());
}

void MetaGME2UML::AddAttribute(MetaGME::ContainedInPar fco, UmlGME::Class cl)
{
	set<MetaGME::HasAttribute> attrs;
	if ( Uml::IsDerivedFrom( fco.type(), MetaGME::BaseFCO::meta)) {
		attrs= (MetaGME::BaseFCO::Cast( fco)).srcAttributes();
	}
	for(set<MetaGME::HasAttribute>::iterator i = attrs.begin(); i!=attrs.end(); i++)
	{	string attrstr;
		MetaGME::HasAttribute attrc = *i;
		MetaGME::Attribute attr = attrc.srcAttributes_end();
		if((string)attr.type().name() == "FieldAttribute")
		{	MetaGME::FieldAttribute fa = MetaGME::FieldAttribute::Cast(attr);
			string fd = fa.FieldDefault(); 
						
			string type;
			string dataType = fa.DataType();
			if(dataType == "String" || dataType == "string")
			{	type = "String"; if(fd!="") fd = "\"" +fd+ "\"";
			}
			else if(dataType == "Integer" || dataType == "integer")
			{	type = "Integer";
			}
			else if(dataType == "Double" || dataType == "double")
			{	type = "Real";
			}
			else
			{	//Error
				string error = "Error: Feild Attribute:"+(string)attr.name()+ " of object:" + (string)fco.name() + " is of unrecognizable type";
				throw udm_exception(error);
			}
			attrstr = "\n" + (string)fa.name() + ":"+ type;
			
			if(fd != "")
				attrstr += "="+fd;
			cl.Attributes() = (string)cl.Attributes() + attrstr;
		}
		else if((string)attr.type().name() == "EnumAttribute")
		{	MetaGME::EnumAttribute fa = MetaGME::EnumAttribute::Cast(attr);
			attrstr = "\n" + (string)fa.name() + ":String";
			string fd = fa.DefaultItem(); 
			if(fd != "") {
/*				string mitems= fa.MenuItems();
				string::size_type findDefaultItem= mitems.find( fd);
				if ( string::npos != findDefaultItem) {
					// found, check if 'fd' is a display label, in which case we need the real label...
					string::size_type endOfDefaultItem= findDefaultItem+ fd.length();
					if ( endOfDefaultItem < mitems.length()) {
						while ( isspace( mitems.at( endOfDefaultItem))) {	// skip white-space chars
							++endOfDefaultItem;
						}
						if ( mitems.at( endOfDefaultItem)== ',') {
							// 'fd' is a display label. parse expr: 'display label, real label\n'
							++endOfDefaultItem; // skip comma char
							string::size_type findEndOfLine= mitems.find( "\n", endOfDefaultItem);
							string realLabel= mitems.substr( endOfDefaultItem, findEndOfLine- endOfDefaultItem);
							trim( realLabel);
							fd= realLabel;
						}
					}
				}
	*/
				attrstr += "=\"" +fd + "\""; 
			}

			cl.Attributes() = (string)cl.Attributes() + attrstr;
		}
		else
		{	MetaGME::BooleanAttribute fa = MetaGME::BooleanAttribute::Cast(attr);
			attrstr = "\n" + (string)fa.name() + ":Boolean";
			bool fd = fa.BooleanDefault(); 
			attrstr += (fd)?"=true":"=false";
			cl.Attributes() = (string)cl.Attributes() + attrstr;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This is the function that implements stringicmp for the map
bool stringicmp::operator()(const string& first, const string& second) const 
{
	string firsti = first;
	string secondi = second;
	transform(firsti.begin(),firsti.end(), firsti.begin(), tolower);
	transform(secondi.begin(),secondi.end(), secondi.begin(), tolower);
	return(firsti < secondi);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// from website http://www.thecodezone.com/diary/archives/000057.html
StringTokenizer::StringTokenizer(const string &rStr, const string &rDelimiters)
{
	string::size_type lastPos(rStr.find_first_not_of(rDelimiters, 0));
	string::size_type pos(rStr.find_first_of(rDelimiters, lastPos));
	while (string::npos != pos || string::npos != lastPos)
	{
		push_back(rStr.substr(lastPos, pos - lastPos));
		lastPos = rStr.find_first_not_of(rDelimiters, pos);
		pos = rStr.find_first_of(rDelimiters, lastPos);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


