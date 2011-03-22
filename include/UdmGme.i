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

%{
Udm::UdmDiagram UdmDiagram_Wrap(Uml::Diagram* umld);
namespace UdmGme {
class GmeDN_Wrapper {
   Uml::Diagram uml_diagram;
   Udm::UdmDiagram diagram;
   public:
   GmeDataNetwork dn;
   GmeDN_Wrapper(Uml::Diagram d, int pUnknownProject, bool customTransactions) : uml_diagram(d), diagram(UdmDiagram_Wrap(&uml_diagram)), dn(diagram) {
      dn.OpenExisting((LPUNKNOWN) pUnknownProject, Udm::CHANGES_LOST_DEFAULT, customTransactions);
   }
   GmeDataNetwork& _getDN() { return dn; }
};
}
%}
namespace UdmGme {
class GmeDN_Wrapper {
   Uml::Diagram uml_diagram;
   Udm::UdmDiagram diagram;
   GmeDataNetwork& dn;
   public:
   GmeDN_Wrapper(Uml::Diagram d, int pUnknownProject, bool customTransactions) : uml_diagram(d), diagram(UdmDiagram_Wrap(&uml_diagram)), dn(diagram) {
      dn.OpenExisting((LPUNKNOWN) pUnknownProject, Udm::CHANGES_LOST_DEFAULT, customTransactions);
   }
   GmeDataNetwork& _getDN() { return dn; }
};
  %extend GmeDN_Wrapper {
    %typemap(cscode) UdmGme::GmeDN_Wrapper %{
      public global::Udm.Native.UdmGme.GmeDataNetwork dn { get { return _getDN(); } }
    %}
  }
}
