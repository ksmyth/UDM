// BackendDump.h: interface for the CBackendDump class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BACKENDDUMP_H__6CEB1988_9475_4427_909E_05FAE8D15482__INCLUDED_)
#define AFX_BACKENDDUMP_H__6CEB1988_9475_4427_909E_05FAE8D15482__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>


#include "Uml.h"

#include "UmlExt.h"

/* Paradigm-independent Udm Backend Dump class							*/
/* Send any compliments to Tihamer Levendovszky tihamer@valon.aut.bm.hu */

class CBackendDump  
{

ostream* dump;
public:
	CBackendDump(){dump=&cout;};
	CBackendDump(ostream*);
	virtual ~CBackendDump();


// Call this to dump a backend
void Dump(Udm::SmartDataNetwork *sdnBackend);

// Paradigm-independent dump functions
void ExtractAttributes(Udm::Object ob, int nDepthLevel=0);
string ExtractName(Udm::Object ob);
void DumpClasses(::Uml::Diagram dgr);
void DumpCompositions(::Uml::Diagram dgr);
void DumpCompositions(const set< ::Uml::Composition> &metacomps);
void DumpAssociations(::Uml::Diagram dgr);
void DumpAssociations(const set< ::Uml::Association> &metaas);

void ExtractLinks(Udm::Object ob);
void VisitObjects(Udm::Object ob, int nDepthLevel=0);
void VisitLinks(Udm::Object ob);


};

#endif // !defined(AFX_BACKENDDUMP_H__6CEB1988_9475_4427_909E_05FAE8D15482__INCLUDED_)
