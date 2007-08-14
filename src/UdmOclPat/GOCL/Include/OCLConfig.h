//###############################################################################################################################################
//
//	Object Constraint Language Generic Manager
//	OCLConfig.h
//
//###############################################################################################################################################

#ifndef OCLConfig_h
#define OCLConfig_h

// Use OCL_USING_STL_NAMESPACE if you use std:: namespace

#ifdef OCL_USING_STL_NAMESPACE
	#define GOCL_STL_NS() std::
#else
	#define GOCL_STL_NS()
#endif

#pragma warning( disable : 4503 )
#pragma warning( disable : 4786 )
#pragma warning( disable : 4018 )
#pragma warning( disable : 4244 )

#endif // OCLConfig_h
