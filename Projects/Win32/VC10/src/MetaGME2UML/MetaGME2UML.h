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
#ifndef META_GME_TO_UML
#define META_GME_TO_UML

//#define GME_SILENT_MODE 128

#ifdef GME_INTERPRETER_USED
#include "stdafx.h"
#include <string>
#define MESSAGE_OUT(STR) if(param != GME_SILENT_MODE) AfxMessageBox(STR); else cout << STR << endl
#include "UdmConsole.h"
static void ConsoleMessage(const std::string& msg) {
	GMEConsole::Console::Out::WriteLine(msg);
}
#else
#include <string>
#include <iostream>
#define MESSAGE_OUT(STR) cout << STR << endl
static void ConsoleMessage(const std::string& msg) {
	std::cout << msg.c_str() << std::endl;
}
#endif

#include "iostream"
#include "Uml.h"
#include "UdmBase.h"
#include "MetaGME.h"
#include "UmlGME.h"

//#include "hash_map"
#include <map>
#include <iterator>

template<class Cont>
std::insert_iterator<Cont> set_inserter(Cont& s) { return std::inserter(s, s.begin()); }

struct stringicmp; 

/*struct udmhash
{	hash_map<Udm::Object, Udm::Object> h;
	size_t operator()(const Udm::Object __s) const { return h(__s.uniqueId()); }
};*/

/*struct udmhash
{	hash_map<size_t> h;
	size_t operator()(const Udm::Object __s) const { return h(__s.uniqueId()); }
};*/

// This version worked but probably didnt provide any optimization.
/*struct udmhash
{	size_t operator()(const Udm::Object __s) const { return __s.uniqueId(); }
};*/

typedef std::map<std::string, std::string, stringicmp> strmap;
//typedef hash_map<MetaGME::ContainedInPar, UmlGME::ClassBase, udmhash, equal_to<MetaGME::ContainedInPar> > map_CIP2CB;
typedef std::map<MetaGME::ContainedInPar, UmlGME::ClassBase> map_CIP2CB;
typedef std::map<MetaGME::ContainedInPar, MetaGME::ContainedInPar> map_CIP2CIP;
//typedef hash_map<MetaGME::ContainedInPar, MetaGME::ContainedInPar, udmhash, equal_to<MetaGME::ContainedInPar> > map_CIP2CIP;

class MetaGME2UML
{
public:
	MetaGME2UML(Udm::DataNetwork &MetaGMENet, Udm::SmartDataNetwork &UmlGMENet, Udm::Object URF, long params) : metaGME(MetaGMENet), umlGME(UmlGMENet), urf(URF), constraintHit(false), constraintCopy(false),param(params) {}
	void transformMetaGME2UmlGME();

protected:
	long param;

	Udm::DataNetwork &metaGME;
	Udm::SmartDataNetwork &umlGME;

	MetaGME::RootFolder grf;
	Udm::Object urf; //this is the top-level package that corresponds to the MetaGME RootFolder
	Udm::Object topNamespace; //this corresponds to the Namespace of the RootFolder
	
	map_CIP2CB mapMetaGME2UmlGME_Class;
	

	std::map< MetaGME::ParadigmSheet, UmlGME::ClassDiagram> mapMetaGME2UmlGME_Paradigm;

	std::map< UmlGME::ClassBase, std::pair< UmlGME::Class, UmlGME::Class> > mapUmlClass2ImplInheritBases;

	std::map<MetaGME::BaseFCO, std::set<MetaGME::BaseFCO>> m_SelfAndSupertypeMemo;
	std::set<MetaGME::BaseFCO> GetSelfAndSupertypes(const MetaGME::BaseFCO& fco);
	std::set<MetaGME::BaseFCO> GetContainersAndTheirSubtypes(const MetaGME::BaseFCO& fco);
	friend struct CanBeContainedInSameContainer;
	map_CIP2CB implMap, intfMap, reguMap;
	map_CIP2CIP equivMap;
	
	// For creating rootfolder
	UmlGME::ClassDiagram umlGMErootDiagram;
	UmlGME::Class umlGMErootFolder;
	int rfx,rfy;

	// For creating gme object
	UmlGME::ClassDiagram umlGMEObjectDiagram;
	UmlGME::Inheritance umlGMEObjectBaseInh;
	int gox,goy;

	// For creating interface & implementation inheritance
	UmlGME::ClassDiagram umlGMEimplinterfaceDiagram;
	int iox,ioy;
	void MakeIntImplDiagram();
	

	std::map<std::string, std::string> attmap, conmap, constrmap;

	std::map<UmlGME::Class, bool> maphasbaseimpl, maphasbaseintf;

	void Phase1_SetUpSheets();
		//void SetUpSheets(MetaGME::RootFolder grf, Udm::Object urf);  //need to know where to create CD and NS objects 4.06.07
		void MetaGME2UML::SetUpSheets(MetaGME::RootFolder grf, Udm::Object urf, Udm::Object cdParent, Udm::Object nsParent);
		void SetupEquivalenceMaps(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd);
			void AddEquivalence(MetaGME::ContainedInPar ms, MetaGME::ContainedInPar sl);

	// added later to take care of GME's Implementaiton and Interface inheritanece.
	void Phase2_CreateImplementationInterfaceInheritances();
		void CreateImplementationInterfaceInheritances(MetaGME::RootFolder grf, Udm::Object urf);
		void CreateImplementationInterfaceInheritances(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd);
			void MakeImplIntf(const MetaGME::BaseFCO& base, const MetaGME::BaseFCO& derived, bool impl, bool intf);
			void GetUMLCounterParts(MetaGME::BaseFCO base, MetaGME::BaseFCO derived, UmlGME::Class &cbase, UmlGME::Class &cderived);
			void RecurseOnBases(const MetaGME::BaseFCO& base);

		void RecurseOnBases(const MetaGME::BaseFCO& base, std::set< MetaGME::BaseFCO>&visitedBases);
protected:
		template <class TYPE, class PROXY_TYPE>
		void checkProxies( const MetaGME::BaseFCO& base, std::set< MetaGME::BaseFCO>& visitedBases);
		template <class TYPE, class PROXY_TYPE>
		void checkRefByProxies( const MetaGME::BaseFCO& proxy, std::set< MetaGME::BaseFCO>& visitedBases);
	void Phase3_CreateClasses();
		void CreateClasses(MetaGME::RootFolder grf, Udm::Object urf);
		void CreateClasses(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd);
			void CreateRootFolderAssociation(UmlGME::Class cl);

	void Phase4_CreateReferences();
		void CreateReferences(MetaGME::RootFolder grf, Udm::Object urf);
		void CreateReferences(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd);

	void Phase5_CreateConnections();
	void CreateConnections(MetaGME::RootFolder grf, Udm::Object urf);
	void CreateConnections(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd);
	void CreateCompositionAssociation(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd);
	void CreateFolderCompositionAssociation(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd);
	void CreateReferToAssociation(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd);
	void CreateSetMembershipAssociation(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd);
	void CreateAssociationClassAssociation(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd);
	void CreateInheritanceAssociation(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd);

	void CreateRefportContainersAssociations(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd);
	std::set<MetaGME::Reference> GetRefportContainers(MetaGME::BaseFCO& connend, const MetaGME::Connection& connection);
	void CreateRefportContainerAssociation(const MetaGME::Connection& connection, const std::string& assoc_rolename, const std::string& rolename, const std::string& rrolename, const std::set<MetaGME::Reference>& refport_containers, UmlGME::ClassDiagram& cd);
	void CreateRefportConnection(const UmlGME::ClassBase& connection, const UmlGME::ClassBase& refport_container, const std::string& rolename, const std::string& rrolename);

	void CreateEquivalenceAssociation(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd);
	void CreateFolderEquivalenceAssociation(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd);
	void CreateConstraints(MetaGME::ParadigmSheet ps, UmlGME::ClassDiagram cd);
			
	void CreateRefereredConnection(UmlGME::ClassBase crefer, UmlGME::ClassBase crefe, MetaGME::Reference reference);
	void CreateMembershipConnection(UmlGME::ClassBase crefer, UmlGME::ClassBase crefe, MetaGME::Set set);

	void Phase6_CreateGMEObject();
		void CreateGMEBaseAssociation(UmlGME::Class cl);
	
	// Helper functions
	UmlGME::Class GetRealInterface(const MetaGME::ContainedInPar& mg);
	UmlGME::Class GetRealImplementation(MetaGME::ContainedInPar mg);
	UmlGME::ClassBase GetInterface(MetaGME::ContainedInPar mg);
	UmlGME::ClassBase GetImplementation(MetaGME::ContainedInPar mg);
	UmlGME::ClassBase GetRegular(MetaGME::ContainedInPar mg);

	MetaGME::ContainedInPar GetRefMetaGMEObject(MetaGME::ContainedInPar base);

	void InitializeSheets(MetaGME::RootFolder grf, Udm::Object urf);
	std::string ConvertPosition(std::string pos);
	std::string MakePosition(int ux, int uy, int cx, int cy);
	std::string MakePosition(int ux, int uy);
	void ConverGeneralPreferenceToMap(std::string pref, strmap &prefmap);
	std::string GetValueForName(std::string name, strmap &prefmap);
	void AddAttribute(MetaGME::ContainedInPar fco, UmlGME::Class cl);
	
	std::string _ConvertPositionAttribute(std::string pos, char* mapingstr);
	
	void GetPosAttr(std::string spos, std::map<std::string, std::string> &atmap);
	std::string MakePosAttr(std::string spos, std::map<std::string, std::string> posmap);

	bool GetPosAttr(std::string spos, std::string aspect, int &x, int &y);

	// Asking about constrints
	bool constraintHit;
	bool constraintCopy;
	
};

struct stringicmp 
{
  bool operator()(const std::string& first, const std::string& second) const;
};

// From website http://www.thecodezone.com/diary/archives/000057.html
class StringTokenizer : public std::vector<std::string>
{
	public:
		StringTokenizer(const std::string &rStr, const std::string &rDelimiters = " ,\n");

};

MetaGME::BaseFCO RefByProxy( const MetaGME::BaseFCO& fco);

#endif
