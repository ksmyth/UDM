// UdmApp.h: interface for the CUdmApp class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

// Udm includes
#include "UdmBase.h"
#include "Uml.h"
#include "UmlExt.h"

#ifdef _USE_DOM
	#include "UdmDOM.h"
#endif

#include "UdmGme.h"
#include "UdmStatic.h"


class CUdmApp  
{

public:
	static std::string mgaDir;
	
	static int Initialize();
	static void UdmMain(Udm::DataNetwork* p_backend,Udm::Object currentObject, std::set<Udm::Object> selectedObjects, long param);
	
};

