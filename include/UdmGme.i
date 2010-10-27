%module UdmGme

%include "UdmCli.i"

CSHARP_NAMESPACE3(UdmGme, Udm.Native.UdmGme, GmeDataNetwork)

%ignore UdmGme::GmeDataNetwork::semantics;
%ignore UdmGme::GmeDataNetwork::meta_role_filter_cache;
%ignore UdmGme::GmeDataNetwork::amapInitialize;
%ignore UdmGme::GmeDataNetwork::amap;
%ignore UdmGme::GmeDataNetwork::priv;
%ignore UdmGme::GmeDataNetwork::CountWriteOps;
%ignore UdmGme::GmeDataNetwork::meta_class_cache;
%ignore UdmGme::DummyFL;
%ignore UdmGme::Dummy_For_Linker;

%{
#include "UdmGme.h"
%}

%include "UdmGme.h"
