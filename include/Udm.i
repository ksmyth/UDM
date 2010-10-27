#define UDM_DLL
%module Udm

%include "UdmException.i"
%include "std_string.i"
%include "std_vector.i"
%include "csharp_std_set.i"

// Swig has poor support for generated code namespaces, so we need a "using Uml;"
%typemap(csimports) SWIGTYPE
%{
using System;
using System.Runtime.InteropServices;

using global::Udm.Native.Uml;
using Attribute = global::Udm.Native.Uml.Attribute;
%}

%pragma(csharp) moduleimports=%{
using System;
using System.Runtime.InteropServices;

using global::Udm.Native.Uml;
using Attribute = global::Udm.Native.Uml.Attribute;
%} 

CSHARP_NAMESPACE3(Udm, Udm.Native, BackendSemantics)
CSHARP_NAMESPACE3(Udm, Udm.Native, BaseVisitor)
CSHARP_NAMESPACE3(Udm, Udm.Native, BooleanArrAttrItem)
CSHARP_NAMESPACE3(Udm, Udm.Native, BooleanAttr)
CSHARP_NAMESPACE3(Udm, Udm.Native, BooleanAttrArr)
CSHARP_NAMESPACE3(Udm, Udm.Native, DataNetwork)
CSHARP_NAMESPACE3(Udm, Udm.Native, DataNetworkSpecifier)
CSHARP_NAMESPACE3(Udm, Udm.Native, DataNetworkSpecifier_vector)
CSHARP_NAMESPACE3(Udm, Udm.Native, DynamicMetaSpecifier)
CSHARP_NAMESPACE3(Udm, Udm.Native, IntegerArrAttrItem)
CSHARP_NAMESPACE3(Udm, Udm.Native, IntegerAttr)
CSHARP_NAMESPACE3(Udm, Udm.Native, IntegerAttrArr)
CSHARP_NAMESPACE3(Udm, Udm.Native, MetaDepository)
CSHARP_NAMESPACE3(Udm, Udm.Native, NullObject)
CSHARP_NAMESPACE3(Udm, Udm.Native, Object)
CSHARP_NAMESPACE3(Udm, Udm.Native, ObjectImpl)
CSHARP_NAMESPACE3(Udm, Udm.Native, std::set<Udm::Object>);
CSHARP_NAMESPACE3(Udm, Udm.Native, ParentAttr<Udm::Object>)
CSHARP_NAMESPACE3(Udm, Udm.Native, RealArrAttrItem)
CSHARP_NAMESPACE3(Udm, Udm.Native, RealAttr)
CSHARP_NAMESPACE3(Udm, Udm.Native, RealAttrArr)
CSHARP_NAMESPACE3(Udm, Udm.Native, SmartDataNetwork)
CSHARP_NAMESPACE3(Udm, Udm.Native, StaticDataNetworkSpecifier)
CSHARP_NAMESPACE3(Udm, Udm.Native, StaticUdmProject)
CSHARP_NAMESPACE3(Udm, Udm.Native, StringArrAttrItem)
CSHARP_NAMESPACE3(Udm, Udm.Native, StringAttr)
CSHARP_NAMESPACE3(Udm, Udm.Native, StringAttrArr)
CSHARP_NAMESPACE3(Udm, Udm.Native, TempBooleanArrAttrItem)
CSHARP_NAMESPACE3(Udm, Udm.Native, TempBooleanAttr)
CSHARP_NAMESPACE3(Udm, Udm.Native, TempBooleanAttrArr)
CSHARP_NAMESPACE3(Udm, Udm.Native, TempIntegerArrAttrItem)
CSHARP_NAMESPACE3(Udm, Udm.Native, TempIntegerAttr)
CSHARP_NAMESPACE3(Udm, Udm.Native, TempIntegerAttrArr)
CSHARP_NAMESPACE3(Udm, Udm.Native, TempRealArrAttrItem)
CSHARP_NAMESPACE3(Udm, Udm.Native, TempRealAttr)
CSHARP_NAMESPACE3(Udm, Udm.Native, TempRealAttrArr)
CSHARP_NAMESPACE3(Udm, Udm.Native, TempStringArrAttrItem)
CSHARP_NAMESPACE3(Udm, Udm.Native, TempStringAttr)
CSHARP_NAMESPACE3(Udm, Udm.Native, TempStringAttrArr)
CSHARP_NAMESPACE3(Udm, Udm.Native, UdmDiagram)
CSHARP_NAMESPACE3(Udm, Udm.Native, UdmProject)
CSHARP_NAMESPACE3(std, Udm.Native, vector<bool>)
CSHARP_NAMESPACE3(std, Udm.Native, vector<double>)
CSHARP_NAMESPACE3(std, Udm.Native, vector<std::string>)
CSHARP_NAMESPACE3(std, Udm.Native, vector<__Int64>)



// Only part of ErrHand.h in Udm.i:
using namespace std;

// Some strings aren't marked const
// %apply const std::string& { Udm::string& };
%apply const std::string& { std::string& };
%apply const std::string& { string& };
%apply const std::string& { const string& };
%apply std::string { string };
%apply std::string { const string };

%pragma(csharp) imclassimports=%{

using System;
using System.Runtime.InteropServices;

public class UdmException : System.ApplicationException {
  public UdmException(string message) 
    : base(message) {
  }
}
%}

// These are not dllexport'ed
%ignore Uml::theOther1;
%ignore Udm::UdmProject::GetRealObject;
%ignore Udm::UdmProject::GetPlaceHolder;
%ignore Udm::NullObject::e;

// Defined in Uml.i
%ignore Uml::IsDerivedFrom;

// TODO: support these
%ignore Udm::DynamicMetaSpecifier::metalocator;
%ignore Udm::udmvariant::strval;

%{
#include "UdmBase.h"
#include "UdmUtil.h"
typedef Udm::Object::AssociationInfo AssociationInfo;
typedef Udm::Object::CompositionInfo CompositionInfo;
namespace Udm {
typedef Udm::DataNetwork::backendtabt DataNetwork_backendtabt;
udm_exception NullObject::e("Object handle is null");
}
#include "Uml.h"
%}

%rename(Equals) Udm::ArrAttrItem::operator==;
%rename(Set) Udm::TempStringAttr::operator=;
%rename(Get) Udm::TempStringAttr::operator string;
%rename(Get) Udm::TempStringAttrArr::operator [];
// TempStringAttrArr::operator vector<string> ?
%rename(Set) Udm::TempIntegerAttr::operator=;
%rename(Get) Udm::TempIntegerAttr::operator __int64;
%rename(Get) Udm::TempIntegerAttrArr::operator [];
%rename(AsVector) Udm::TempIntegerAttrArr::operator vector<__int64> const;
%rename(Set) Udm::TempRealAttr::operator =;
%rename(Get) Udm::TempRealAttr::operator double;
%rename(Get) Udm::TempRealAttrArr::operator [];
%rename(AsVector) Udm::TempRealAttrArr::operator vector<double>() const;
%rename(Set) Udm::TempBooleanAttr::operator =;
%rename(Get) Udm::TempBooleanAttr::operator bool;
%rename(Get) Udm::TempBooleanAttrArr::operator [];
%rename(AsVector) Udm::TempBooleanAttrArr::operator vector<bool>() const;
%rename(Set) Udm::StringAttr::operator=;
%rename(Get) Udm::StringAttr::operator string;
%rename(Get) Udm::StringAttrArr::operator [];
%rename(AsVector) Udm::StringAttrArr::operator vector<string>() const ;
%rename(Set) Udm::IntegerAttr::operator=;
%rename(Get) Udm::IntegerAttr::operator __int64;
%rename(Get) Udm::IntegerAttrArr::operator [];
%rename(Set) Udm::RealAttr::operator =;
%rename(Get) Udm::RealAttr::operator double;
%rename(Get) Udm::RealAttrArr::operator [];
%rename(AsVector) Udm::RealAttrArr::operator vector<bool>() const;
%rename(Set) Udm::BooleanAttr::operator =;
%rename(Get) Udm::BooleanAttr::operator bool;
%rename(Get) Udm::BooleanAttrArr::operator [];

%rename(Equals) Udm::Object::operator==;
%rename(IsNull) Udm::Object::operator bool;

%rename(AsSet) Udm::AssocAttr::operator set<CLASS,Pred >() const;
%rename(AsSet) Udm::AClassCrossAssocAttr::operator set<CLASS,Pred >() const;
%rename(AsSet) Udm::AClassAssocAttr::operator set<CLASS,Pred >() const;
%rename(AsSet) Udm::ChildrenAttr::operator set<CLASS,Pred >() const;
%rename(AsSet) Udm::DerivedAttr::operator set<CLASS,Pred >() const;
%rename(AsSet) Udm::InstantiatedAttr::operator set<CLASS,Pred >() const;
%rename(AsSet) Udm::CrossAssocAttr::operator set<CLASS,Pred >() const;

%rename(AsVector) Udm::ChildrenAttr::operator vector<CLASS >() const;

%rename(DeRef) Udm::ArrAttrItem::operator CLASS() const;
%rename(DeRef) Udm::CrossPointerAttr::operator CLASS() const;
%rename(DeRef) Udm::PointerAttr::operator CLASS() const;
%rename(DeRef) Udm::CrossAssocEndAttr::operator CLASS() const;
%rename(DeRef) Udm::AssocEndAttr::operator CLASS() const;
%rename(DeRef) Udm::AClassCrossPointerAttr::operator CLASS() const;
%rename(DeRef) Udm::AClassPointerAttr::operator CLASS() const;
%rename(DeRef) Udm::ChildAttr::operator CLASS() const;
%rename(DeRef) Udm::ParentAttr::operator CLASS() const;
%rename(DeRef) Udm::ArchetypeAttr::operator CLASS() const;

%rename(Set) *::operator =;
%rename(RemoveMember) *::operator -=;
%rename(AddMember) *::operator +=;

// Don't get confused with System.Object
%rename(UdmObject) Udm::Object;

%include "UdmBase.h"

//TODO: do we need these?
//%template(BoolArrAttrItem) Udm::ArrAttrItem<bool>;
//%template(StringArrAttrItem) Udm::ArrAttrItem<string>;
//%template(StringAdditiveArrAttrItem) Udm::AdditiveArrAttrItem< string >;
//%template(DoubleArrAttrItem) Udm::ArrAttrItem<double>;
//%template(DoubleAdditiveArrAttrItem) Udm::AdditiveArrAttrItem< double >;
//%template(IntArrAttrItem) Udm::ArrAttrItem<__int64>;
//%template(IntAdditiveArrAttrItem) Udm::AdditiveArrAttrItem< __int64 >;

namespace Udm {
  %extend ChildrenAttr {
    %typemap(csinterfaces) Udm::ChildrenAttr "IDisposable, System.Collections.Generic.IEnumerable<$typemap(cstype, CLASS)>";
	%typemap(cscode) Udm::ChildrenAttr <CLASS, Pred > %{
      public System.Collections.Generic.IEnumerator<$typemap(cstype, CLASS)> GetEnumerator()
      {
        return AsVector().GetEnumerator();
      }
      System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
      {
        return AsVector().GetEnumerator();
      }
    %}
  };
  
  %extend StringAttr {
    %typemap(cscode) Udm::StringAttr %{
      public override String ToString()
      {
        return Get();
      }
    %}
  }
}
// TODO: IEnumerable for the following:
// CrossAssocAttr
// AssocAttr
// AClassCrossAssocAttr
// AClassAssocAttr
// DerivedAttr
// InstantiatedAttr


%template(ObjectParentAttr) Udm::ParentAttr<Udm::Object>;
%template(Object_set) std::set<Udm::Object>;
%template(ObjectImpl_vector) std::vector<Udm::ObjectImpl*>;
%template(DataNetworkSpecifier_vector) std::vector<Udm::DataNetworkSpecifier>;
%template(StaticDataNetworkSpecifier_vector) std::vector<Udm::StaticDataNetworkSpecifier>;
%template(bool_vector) std::vector<bool>;
%template(double_vector) std::vector<double>;
%template(string_vector) std::vector<std::string>;
%template(Int64_Vector) std::vector<long long>;

%include "UdmUtil.h"

%{
static void udmdiagram_dummy() {}
Udm::UdmDiagram UdmDiagram_Wrap(Uml::Diagram* umld) {
	Udm::UdmDiagram ret;
	ret.dgr = umld;
	ret.init = udmdiagram_dummy;
	return ret;
}
class SDN_Wrapper {
   Uml::Diagram uml_diagram;
   Udm::UdmDiagram diagram;
   public:
   Udm::SmartDataNetwork dn;
   SDN_Wrapper(Uml::Diagram d) : uml_diagram(d), diagram(UdmDiagram_Wrap(&uml_diagram)), dn(diagram) { }
};
%}

class SDN_Wrapper {
   Uml::Diagram uml_diagram;
   Udm::UdmDiagram diagram;
   public:
   Udm::SmartDataNetwork dn;
   SDN_Wrapper(Uml::Diagram d) : uml_diagram(d), diagram(UdmDiagram_Wrap(&uml_diagram)), dn(diagram) { }
};


%import "Uml.i"

