#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "../test_refports/RefPort.h"

#include "UdmBase.h"
#include "UdmStatic.h"
#include "Uml.h"

__declspec(dllexport) void init(void* data) {
	_CrtMemState* state = (_CrtMemState*) data;

	// Udm-60: this leaks the Udm objects
	Uml::Initialize();
	new double; // state needs to anchor to an allocation
	_CrtMemCheckpoint(state);
	RefPort::Initialize();
}