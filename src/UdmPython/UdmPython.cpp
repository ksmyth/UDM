
#include "UdmBase.h"
#include "Uml.h"
#include "UmlExt.h"
#include "UdmGme.h"
#include "UdmUtil.h"

#include "boost/python.hpp"
#include "boost/python/slice.hpp"
#include "boost/python/operators.hpp"

#undef min
#undef max

using namespace boost::python;
using namespace std;

void SDN_OpenExisting(Udm::SmartDataNetwork& self, const string &systemname, const string& metalocator) {
	self.OpenExisting(systemname, metalocator, Udm::CHANGES_LOST_DEFAULT);
}

void SDN_CreateNew(Udm::SmartDataNetwork& self, const string &systemname, const string& metalocator, const Udm::Object rootclass) {
	const Uml::Class& root = Uml::SafeTypeContainer::GetSafeType(Uml::Class::Cast(rootclass));
	self.CreateNew(systemname, metalocator, root, Udm::CHANGES_LOST_DEFAULT);
}

// Helper function so lifetimes are managed properly
Udm::SmartDataNetwork* SDN_NewHelper(Uml::Diagram* umldiag, Udm::UdmDiagram* udmdiag) {
	return new Udm::SmartDataNetwork(*udmdiag);
}

object SDN_NewHelper_ = make_function(SDN_NewHelper,	with_custodian_and_ward_postcall<1, 0,
														with_custodian_and_ward_postcall<2, 0,
														return_value_policy<manage_new_object> > >());

static void dummy(void) {}

object SDN_New(object class_, Udm::Object& udmodiagram) {
	Uml::Diagram* umldiag = new Uml::Diagram(Uml::Diagram::Cast(udmodiagram));
	Udm::UdmDiagram* udmdiag = new Udm::UdmDiagram();
	udmdiag->dgr = umldiag;
	udmdiag->init = &dummy;
	return SDN_NewHelper_(umldiag, udmdiag);
}

Udm::Object Uml_Diagram() {
	Uml::Initialize();
	return (Udm::Object) Uml::Class::meta.parent();
}

template<class colT>
boost::python::list toList(colT collection) {
	boost::python::list ret;
	colT::iterator it = collection.begin();
	for (; it != collection.end(); it++) {
		ret.append(object(*it));
	}
	return ret;
}

Uml::Attribute getAttribute(Udm::Object& self, std::string& name) {
	// Getting Attributes from meta
	::Uml::Class cls = self.type();
	set< ::Uml::Attribute> attrs = cls.attributes();	
	
	// Adding parent attributes
	set< ::Uml::Attribute> aattrs = ::Uml::AncestorAttributes(cls);
	attrs.insert(aattrs.begin(),aattrs.end());

	
	for(set< ::Uml::Attribute>::iterator attrsIt = attrs.begin(); attrsIt != attrs.end(); attrsIt++) {
		string strCurrAttrName = attrsIt->name();
		
		if (strCurrAttrName == name) {
			return *attrsIt;
		}
	}
	return Uml::Attribute();
}

object Object_attr(Udm::Object& self, str _name) {
	std::string name = extract<std::string>(_name);

	Uml::Attribute attr = getAttribute(self, name);
	if (!attr) {
		throw std::runtime_error(std::string("Unknown attribute '") + name + "' for class '" + static_cast<string>(self.type().name()) + "'");
	}
	if (static_cast<string>(attr.type()) == "Integer") {
		return object(self.getIntegerAttr(attr));
	}
	if (static_cast<string>(attr.type()) == "String" || static_cast<string>(attr.type()) == "Text") {
		return object(self.getStringAttr(attr));
	}
	if (static_cast<string>(attr.type()) == "Real") {
		return object(self.getRealAttr(attr));
	}
	if (static_cast<string>(attr.type()) == "Boolean") {
		return object(self.getBooleanAttr(attr));
	}
	throw std::runtime_error(std::string("Unsupported attribute type '") + static_cast<string>(attr.type()) + "' for class '" + static_cast<string>(self.type().name()) + "'");
}

object Object_set_attr(Udm::Object& self, str _name, object value) {
	std::string name = extract<std::string>(_name);

	Uml::Attribute attr = getAttribute(self, name);
	if (!attr) {
		throw std::runtime_error(std::string("Unknown attribute '") + name + "' for class '" + static_cast<string>(self.type().name()) + "'");
	}
	if (static_cast<string>(attr.type()) == "Integer") {
		self.setIntegerAttr(attr, extract<__int64>(value));
		return object();
	}
	if (static_cast<string>(attr.type()) == "String" || static_cast<string>(attr.type()) == "Text") {
		self.setStringAttr(attr, extract<std::string>(value));
		return object();
	}
	if (static_cast<string>(attr.type()) == "Real") {
		self.setRealAttr(attr, extract<double>(value));
		return object();
	}
	if (static_cast<string>(attr.type()) == "Boolean") {
		self.setBooleanAttr(attr, extract<bool>(value));
		return object();
	}
	throw std::runtime_error(std::string("Unsupported attribute type '") + static_cast<string>(attr.type()) + "' for class '" + static_cast<string>(self.type().name()) + "'");
}

object Object_children(Udm::Object& self, object child_role, object parent_role, object _child_type) {
	bool roles_none = true;
	Uml::Class child_type;
	if (_child_type != object()) {
		child_type = Uml::Class::Cast(extract<Udm::Object&>(_child_type));
	}
	Udm::Object::CompositionInfo comp_info;
	if (child_role != object()) {
		comp_info.strChildRoleName = extract<const char*>(child_role);
		roles_none = false;
	}
	if (parent_role != object()) {
		comp_info.strParentRoleName = extract<const char*>(parent_role);
		roles_none = false;
	}
	if (!roles_none) {
		// FIXME: might need to be a singleton if child_role is specified
		return toList(self.GetChildObjects(comp_info, child_type));
	} else if (child_type) {
		return toList(self.GetChildObjects(child_type));
	} else {
		return toList(self.GetChildObjects());
	}
}

Udm::Object Object_type(Udm::Object& self) {
	return Udm::Object(self.type());
}

void Object_set_adjacent_helper(Udm::Object& self, object _targets, object srcrolename, object dstrolename, object _associationClass, bool& /*out*/ foundApplicableAssociation) {
	// based on UdmTomi.cpp: Object::GetAdjacentObjects
	foundApplicableAssociation = false;
	boost::python::list ret;

	Uml::Class associationClass;
	if (_associationClass != object()) {
		associationClass = Uml::Class::Cast(extract<Udm::Object&>(_associationClass));
	}

	::Uml::Class srcClass = self.type();
	set<::Uml::Class> ancestorClasses = ::Uml::AncestorClasses(srcClass);
	set<::Uml::Class>::iterator ancestorClassesIt = ancestorClasses.begin();

	for(; ancestorClassesIt != ancestorClasses.end(); ancestorClassesIt++) {
		// Getting the association roles and iterating through them
		set<::Uml::AssociationRole> assocRoles = ancestorClassesIt->associationRoles();
		set<::Uml::AssociationRole>::iterator assocRolesIt = assocRoles.begin();
		for(; assocRolesIt != assocRoles.end(); assocRolesIt++) {
			::Uml::AssociationRole oRole = ::Uml::theOther(*assocRolesIt);
			// Checking role names
			if (srcrolename != object()) {
				if (static_cast<std::string>(assocRolesIt->name()) != 
					static_cast<const char*>(extract<const char*>(srcrolename))) {
					continue;
				}
			}
			if (dstrolename != object()) {
				if (static_cast<std::string>(oRole.name()) != 
					static_cast<const char*>(extract<const char*>(dstrolename))) {
					continue;
				}
			}

			// Check if there is an association class for this role
			::Uml::Association assoc = assocRolesIt->parent();
			::Uml::Class assoc_cls = assoc.assocClass();
			if (associationClass && !assoc_cls) {
				continue;
			}
			foundApplicableAssociation = true;

			using namespace Udm;
			std::vector<Udm::ObjectImpl*> targets_impl;
			extract<Udm::Object&> singleton(_targets);
			if (singleton.check()) {
				Udm::Object& o = static_cast<Udm::Object&>(singleton);
				if (o) {
					targets_impl.push_back(o.__impl());
				} else {
					// i.e. set_adjacent(Udm::null)
				}
			} else {
				// FIXME: should work with _targets.__iter__() instead
				int len_targets = boost::python::len(_targets);
				targets_impl.reserve(len_targets);
				for (int i = 0; i < len_targets; i++) {
					Udm::Object& o = extract<Udm::Object&>(_targets[i]);
					targets_impl.push_back(o.__impl());
					if (o.__impl()->__getdn()->uniqueId() != self.__impl()->__getdn()->uniqueId()) {
						throw std::exception("Cannot set_adjacent with a target from a different DataNetwork");
					}
				}
			}
			self.__impl()->setAssociation(oRole, targets_impl, (!assoc_cls ? Udm::TARGETFROMPEER : Udm::TARGETFROMCLASS));
			return;
		}
	}
}

void Object_set_adjacent(Udm::Object& self, object _targets, object srcrolename, object dstrolename, object _associationClass) {
	bool foundApplicableAssociation;
	Object_set_adjacent_helper(self, _targets, srcrolename, dstrolename, _associationClass, foundApplicableAssociation);
	if (!foundApplicableAssociation) {
		Uml::Class associationClass;
		if (_associationClass != object()) {
			associationClass = Uml::Class::Cast(extract<Udm::Object&>(_associationClass));
		}
		if (!foundApplicableAssociation && (srcrolename != object() && dstrolename != object() && !associationClass)) {
			std::string errorMessage = "Object of type '";
			errorMessage += static_cast<string>(self.type().name());
			errorMessage += "' has no association defined";
			if (srcrolename != object()) {
				errorMessage += " with src_role '";
				errorMessage += static_cast<std::string>(extract<std::string>(srcrolename));
				errorMessage += "'";
			}
			if (dstrolename != object()) {
				errorMessage += " with dst_role '";
				errorMessage += static_cast<std::string>(extract<std::string>(dstrolename));
				errorMessage += "'";
			}
			if (associationClass) {
				errorMessage += " with assocation_class '";
				errorMessage += static_cast<string>(associationClass.name());
				errorMessage += "'";
			}
			throw std::runtime_error(errorMessage);
		}
	}
}

object Object_adjacent_helper(Udm::Object& self, object srcrolename, object dstrolename, object _associationClass, bool& /*out*/ foundApplicableAssociation) {
	// based on UdmTomi.cpp: Object::GetAdjacentObjects
	foundApplicableAssociation = false;
	boost::python::list ret;

	Uml::Class associationClass;
	if (_associationClass != object()) {
		associationClass = Uml::Class::Cast(extract<Udm::Object&>(_associationClass));
	}

	::Uml::Class srcClass = self.type();
	set<::Uml::Class> ancestorClasses = ::Uml::AncestorClasses(srcClass);
	set<::Uml::Class>::iterator ancestorClassesIt = ancestorClasses.begin();

	for(; ancestorClassesIt != ancestorClasses.end(); ancestorClassesIt++) {
		::Uml::Association association = static_cast<::Uml::Association>(ancestorClassesIt->association());
		if (association && dstrolename != object()) {
			std::set<::Uml::AssociationRole> roles = association.AssociationRole_kind_children();
			for (auto roleIt = roles.begin(); roleIt != roles.end(); roleIt++) {
				::Uml::AssociationRole role = *roleIt;
				if (static_cast<std::string>(role.name()) == 
						static_cast<const char*>(extract<const char*>(dstrolename))) {
					using namespace Udm;
					vector<ObjectImpl*> dstPeers = self.__impl()->getAssociation(role, Udm::TARGETFROMCLASS);
					vector<ObjectImpl*>::iterator dstPeersIt = dstPeers.begin();
					foundApplicableAssociation = true;
					return object(Udm::Object(*dstPeersIt));
				}
			}
		}
		// Getting the association roles and iterating through them
		set<::Uml::AssociationRole> assocRoles = ancestorClassesIt->associationRoles();
		set<::Uml::AssociationRole>::iterator assocRolesIt = assocRoles.begin();
		for(; assocRolesIt != assocRoles.end(); assocRolesIt++) {
			::Uml::AssociationRole oRole = ::Uml::theOther(*assocRolesIt);
			// Checking role names
			if (srcrolename != object()) {
				if (static_cast<std::string>(assocRolesIt->name()) != 
					static_cast<const char*>(extract<const char*>(srcrolename))) {
					continue;
				}
			}
			if (dstrolename != object()) {
				if (static_cast<std::string>(oRole.name()) != 
					static_cast<const char*>(extract<const char*>(dstrolename))) {
					continue;
				}
			}

			// Check if there is an association class for this role
			::Uml::Association assoc = assocRolesIt->parent();
			::Uml::Class assoc_cls = assoc.assocClass();
			if (associationClass && !assoc_cls) {
				continue;
			}
			foundApplicableAssociation = true;

			using namespace Udm;
			// simple association
			if (!assoc_cls) {
				vector<ObjectImpl*> dstPeers = self.__impl()->getAssociation(oRole, Udm::TARGETFROMPEER);
				vector<ObjectImpl*>::iterator dstPeersIt = dstPeers.begin();

				for (; dstPeersIt != dstPeers.end(); dstPeersIt++) {
					Udm::Object dstObject(*dstPeersIt);

					// return a singleton (like CompositionChildRole::target())
					if (dstrolename != object() && oRole.max() == 1) {
						return object(dstObject);
					}

					ret.append(object(dstObject));
				}
				if (dstrolename != object() && oRole.max() == 1) {
					// FIXME: is this right?
					return object(Udm::null);
				}
				continue;
			}

			// Check all association with classes
			vector<ObjectImpl*> assocs = self.__impl()->getAssociation(oRole, Udm::CLASSFROMTARGET);

			for(vector<ObjectImpl*>::iterator p_currAssoc = assocs.begin(); p_currAssoc != assocs.end(); p_currAssoc++)
			{
				Udm::Object assocCls_obj(*p_currAssoc);
				::Uml::Class clsAssociation = assocCls_obj.type();

				// Checking association class type
				if (associationClass && associationClass != clsAssociation && !::Uml::IsDerivedFrom(clsAssociation, associationClass))
					continue;

				// Get and test the peers
				vector<ObjectImpl*> dstPeers = assocCls_obj.__impl()->getAssociation(oRole, Udm::TARGETFROMCLASS);
				vector<ObjectImpl*>::iterator dstPeersIt = dstPeers.begin();
				for (; dstPeersIt != dstPeers.end(); dstPeersIt++) {
					Udm::Object dstObject(*dstPeersIt);
						
					// return a singleton (like CompositionChildRole::target())
					if (dstrolename != object() && oRole.max() == 1) {
						return object(dstObject);
					}

					ret.append(object(dstObject));
				}
				if (dstrolename != object() && oRole.max() == 1) {
					// FIXME: is this right?
					return object(Udm::null);
				}

			}
		}
	}
	return ret;
}

object Object_adjacent(Udm::Object& self, object srcrolename, object dstrolename, object _associationClass) {
	bool foundApplicableAssociation;
	object ret = Object_adjacent_helper(self, srcrolename, dstrolename, _associationClass, foundApplicableAssociation);

	Uml::Class associationClass;
	if (_associationClass != object()) {
		associationClass = Uml::Class::Cast(extract<Udm::Object&>(_associationClass));
	}
	if (!foundApplicableAssociation && (srcrolename != object() && dstrolename != object() && !associationClass)) {
		std::string errorMessage = "Object of type '";
		errorMessage += static_cast<string>(self.type().name());
		errorMessage += "' has no association defined";
		if (srcrolename != object()) {
			errorMessage += " with src_role '";
			errorMessage += static_cast<std::string>(extract<std::string>(srcrolename));
			errorMessage += "'";
		}
		if (dstrolename != object()) {
			errorMessage += " with dst_role '";
			errorMessage += static_cast<std::string>(extract<std::string>(dstrolename));
			errorMessage += "'";
		}
		if (associationClass) {
			errorMessage += " with assocation_class '";
			errorMessage += static_cast<string>(associationClass.name());
			errorMessage += "'";
		}
		throw std::runtime_error(errorMessage);
	}
	return ret;
}

object Object___setattr__(object& self, str _name, object value) {
	bool foundApplicableAssociation;
	Object_set_adjacent_helper(extract<Udm::Object&>(self), value, object(), _name, object(), foundApplicableAssociation);
	if (foundApplicableAssociation) {
		return object();
	}

	object(self).attr("set_attr")(_name, value);
	return object();
}

object Object___getattr__(object& self, str _name) {
	str _role_children = "_role_children";
	if (_name.endswith(_role_children)) {
		return object(self).attr("children")(static_cast<string>(extract<string>(_name[slice(0,-14)])));
	}
	str _kind_children = "_kind_children";
	if (_name.endswith(_kind_children)) {
		// TODO: need to look up the meta class
		//return object(self).attr("children")(object(), object(), xxx));
	}
	bool foundApplicableAssociation;
	object adjacents = Object_adjacent_helper(extract<Udm::Object&>(self), object(), _name, object(), foundApplicableAssociation);
	if (foundApplicableAssociation) {
		return adjacents;
	}

	return object(self).attr("attr")(_name);
}

void Object_SetParent(Udm::Object& self, Udm::Object& parent) {
	// TODO: roles
	Udm::ParentAttr<Udm::Object> parentAttr(self.__impl(), Udm::NULLPARENTROLE);
	parentAttr = parent;
}

object Object_derived(Udm::Object& self) {
	return toList(self.derived());
}

object Object_instances(Udm::Object& self) {
	return toList(self.instances());
}

std::string Object_getLibraryName(Udm::Object& self) {
	std::string ret;
	self.getLibraryName(ret);
	return ret;
}

void CopyObjectHierarchy_(Udm::Object src, Udm::Object dst) {
	UdmUtil::copy_assoc_map map;
	UdmUtil::CopyObjectHierarchy(src.__impl(), dst.__impl(), dst.__impl()->__getdn(), map);
}

namespace {
	class Object_access : Udm::Object {
	public:
		static Udm::ObjectImpl* Create(const ::Uml::Class& meta, const Udm::Object& parent,
			const ::Uml::CompositionChildRole& role,
			const Udm::ObjectImpl* archetype = &Udm::_null,
			const bool subtype = false) {
				// FIXME: does this leak?
				return __Create(meta, parent, role, archetype, subtype);
		}
	};
}

Udm::Object Object_create(Udm::Object& meta, Udm::Object& parent /*,Udm::Object& role, Udm::Object& archetype, bool is_subtype*/) {
	return Object_access::Create(Uml::Class::Cast(meta), parent, Udm::NULLCHILDROLE);
}

extern "C" {
__declspec(dllexport) PyObject* __cdecl Object_Convert(Udm::Object udmObject) {
	object o(udmObject);
	PyObject* ret = o.ptr();
	Py_INCREF(ret);
	return ret;
}
}

#ifdef _DEBUG
BOOST_PYTHON_MODULE(udmd)
#else
BOOST_PYTHON_MODULE(udm)
#endif
{
	class_<Udm::Object>("Object")
		.add_property("type", Object_type)
		.add_property("id", &Udm::Object::uniqueId)
		.add_property("parent", &Udm::Object::GetParent, &Object_SetParent)
		.def("create", Object_create)
		.def("delete", &Udm::Object::DeleteObject)
		.def("_children", Object_children)
		.def("_adjacent", Object_adjacent)
		.def("attr", &Object_attr)
		.def("set_attr", &Object_set_attr)
		.def("__getattr__", &Object___getattr__)
		.def("__setattr__", &Object___setattr__)
		// FIXME: these should use object's DataNetwork id too
		.def(self == self)
		.def(self != self)
		.def("__hash__", &Udm::Object::uniqueId)
		.def("_set_adjacent", &Object_set_adjacent)

		.add_property("has_real_archetype", &Udm::Object::hasRealArchetype)
		.add_property("is_instance", &Udm::Object::isInstance)
		.add_property("is_subtype", &Udm::Object::isSubtype)
		.add_property("archetype", &Udm::Object::archetype)
		.add_property("derived", &Object_derived)
		.add_property("instances", &Object_instances)

		.add_property("is_lib_object", &Udm::Object::isLibObject)
		.add_property("is_lib_root", &Udm::Object::isLibRoot)
		.add_property("library_name", &Object_getLibraryName)
		;
	scope().attr("Object").attr("adjacent") = eval("lambda self, src_role=None, dst_role=None, association_class=None: self._adjacent(src_role, dst_role, association_class)");
	scope().attr("Object").attr("children") = eval("lambda self, child_role=None, parent_role=None, child_type=None: self._children(child_role, parent_role, child_type)");
	scope().attr("Object").attr("set_adjacent") = eval("lambda self, targets, src_role=None, dst_role=None, association_class=None: self._set_adjacent(targets, src_role, dst_role, association_class)");
	scope().attr("Object").attr("__repr__") = eval("lambda self: \"udm.null\" if self.id==0 else (\"<udm.Object id\" + str(self.id) + \">\")");

	scope().attr("null") = Udm::null;

	class_<Uml::Diagram>("_UmlDiagram")
		;

	class_<Udm::UdmDiagram>("_UdmDiagram")
		;

	def("uml_diagram", Uml_Diagram);

	def("CopyObjectHierarchy", &CopyObjectHierarchy_);


	class_<Udm::SmartDataNetwork>("SmartDataNetwork", no_init) //, init<const Udm::UdmDiagram &>())
		.def("__new__", SDN_New, with_custodian_and_ward_postcall<2, 0>())
		.staticmethod("__new__")
		.def("open", SDN_OpenExisting)
		.def("create", SDN_CreateNew)
		.def("close_with_update", &Udm::SmartDataNetwork::CloseWithUpdate)
		.def("close_no_update", &Udm::SmartDataNetwork::CloseNoUpdate)
		.def("save_as", &Udm::SmartDataNetwork::SaveAs)
		.add_property("root", &Udm::SmartDataNetwork::GetRootObject)
	;
	scope().attr("SmartDataNetwork").attr("__init__") = eval("lambda self, *args: None");
	exec(
"def map_uml_names(diagram):\n"
"    class_meta = filter(lambda class_: class_.name == 'Class', udm.uml_diagram().children())[0]\n"
"    namespace_meta = filter(lambda class_: class_.name == 'Namespace', udm.uml_diagram().children())[0]\n"
"    class ClassMap(object):\n"
"        def __init__(self, d):\n"
"            self.__dict__.update(d)\n"
"    def map_classes(container):\n"
"        ret = map(lambda class_: (class_.name, class_), container.children(child_type=class_meta))\n"
"        ret.extend(map(lambda namespace: (namespace.name, map_classes(namespace)), container.children(child_type=namespace_meta)))\n"
"        return ClassMap(ret)\n"
"    return map_classes(diagram)\n",
		import("__main__").attr("__dict__"), scope().attr("__dict__"));

	def("UdmId2GmeId", UdmGme::UdmId2GmeId);
	Udm::Object::uniqueId_type (*GmeId2UdmId)(const char* gmeId) = &UdmGme::GmeId2UdmId;
	def("GmeId2UdmId", GmeId2UdmId);

}
