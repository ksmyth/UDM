
%include "UdmException.i"
%import "Udm.i"
%import "Uml.i"
%include "std_vector.i"
%include "csharp_std_set.i"

%pragma(csharp) imclassimports=%{

using System;
using System.Runtime.InteropServices;

using UdmException = global::Udm.Native.UdmException;
using Attribute = global::Udm.Native.Uml.Attribute;
%}


%typemap(csimports) SWIGTYPE
%{
using System;
using System.Runtime.InteropServices;

using global::Udm.Native;
%}


%{
#include <algorithm>
%}

%define %udm_class(Namespace, Class)
  %template(Class ## _ArchetypeAttr) Udm::ArchetypeAttr<Namespace::Class>;
  %template(Class ## _AssocAttr) Udm::AssocAttr<Namespace::Class>;
  %template(Class ## _AssocEndAttr) Udm::AssocEndAttr<Namespace::Class>;
  %template(Class ## _CrossAssocAttr) Udm::CrossAssocAttr<Namespace::Class>;
  %template(Class ## _ChildAttr) Udm::ChildAttr<Namespace::Class>;
  %template(Class ## _ChildrenAttr) Udm::ChildrenAttr<Namespace::Class>;
  %template(Class ## _DerivedAttr) Udm::DerivedAttr<Namespace::Class>;
  %template(Class ## _InstantiatedAttr) Udm::InstantiatedAttr<Namespace::Class>;
  %template(Class ## _ParentAttr) Udm::ParentAttr<Namespace::Class>;
  %template(Class ## _PointerAttr) Udm::PointerAttr<Namespace::Class>;

  %template(Class ## _vector) std::vector<Namespace::Class>;
  %template(Class ## _set) std::set<Namespace::Class>;
  // TODO: any standard extensions?
  //%extend Class {
%enddef

