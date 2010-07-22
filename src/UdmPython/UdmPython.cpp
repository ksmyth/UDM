
#include "UdmBase.h"
#include "Uml.h"
#include "UmlExt.h"
#include "UdmGme.h"

#include "boost/python.hpp"
#include "boost/python/slice.hpp"
#include "boost/python/operators.hpp"

#undef min
#undef max

using namespace boost::python;

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

object Object_attr(Udm::Object& self, str _name) {
	std::string name = extract<std::string>(_name);
	__int64 intValue;
	if (self.GetIntValue(name, intValue)) {
		return object(intValue);
	}
	std::string stringValue;
	if (self.GetStrValue(name, stringValue)) {
		return object(stringValue);
	}
	double doubleValue;
	if (self.GetRealValue(name, doubleValue)) {
		return object(doubleValue);
	}
	bool boolValue;
	if (self.GetBoolValue(name, boolValue)) {
		return object(boolValue);
	}

	throw std::runtime_error(std::string("Unknown attribute '") + name + "' for class '" + static_cast<string>(self.type().name()) + "'");
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

object Object_adjacent_orig(Udm::Object& self, object srcrolename, object dstrolename, object _associationClass) {
	Uml::Class associationClass;
	if (_associationClass != object()) {
		associationClass = Uml::Class::Cast(extract<Udm::Object&>(_associationClass));
	}

	Udm::Object::AssociationInfo ascType(associationClass);
	// KMS: is ascType str(Dst,Src)RoleName backwards?
	if (srcrolename != object()) {
		ascType.strDstRoleName = extract<std::string>(srcrolename);
	}
	if (dstrolename != object()) {
		ascType.strSrcRoleName = extract<std::string>(dstrolename);
	}

	Uml::Class dstType;

	// TODO: shouldn't be a list if cardinality is 0..1
	return toList(self.GetAdjacentObjects(dstType, ascType));
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

object Object_getattr(object& self, str _name) {
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

BOOST_PYTHON_MODULE(udm)
{
	class_<Udm::Object>("Object")
		.add_property("type", Object_type)
		.add_property("id", &Udm::Object::uniqueId)
		.add_property("parent", &Udm::Object::GetParent, &Object_SetParent)
		.def("_children", Object_children)
		.def("_adjacent", Object_adjacent)
		.def("attr", &Object_attr)
		.def("__getattr__", &Object_getattr)
		.def(self == self)
		.def(self != self)
		.def("__hash__", &Udm::Object::uniqueId)

		.add_property("has_real_archetype", &Udm::Object::hasRealArchetype)
		.add_property("is_instance", &Udm::Object::isSubtype)
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

	class_<Uml::Diagram>("_UmlDiagram")
		;

	class_<Udm::UdmDiagram>("_UdmDiagram")
		;

	def("uml_diagram", Uml_Diagram);

	class_<Udm::SmartDataNetwork>("SmartDataNetwork", no_init) //, init<const Udm::UdmDiagram &>())
		.def("__new__", SDN_New, with_custodian_and_ward_postcall<2, 0>())
		.staticmethod("__new__")
		.def("open", SDN_OpenExisting)
		.def("create", SDN_CreateNew)
		.def("close_with_update", &Udm::SmartDataNetwork::CloseWithUpdate)
		.def("close_no_update", &Udm::SmartDataNetwork::CloseNoUpdate)
		.add_property("root", &Udm::SmartDataNetwork::GetRootObject)
	;
	scope().attr("SmartDataNetwork").attr("__init__") = eval("lambda self, *args: None");

	//def("UdmId2GmeId", UdmGme::UdmId2GmeId);
	//Udm::Object::uniqueId_type (*GmeId2UdmId)(const char* gmeId) = &UdmGme::GmeId2UdmId;
	//def("GmeId2UdmId", GmeId2UdmId);
	//UDM_DLL Udm::Object::uniqueId_type GmeId2UdmId(const char* gmeId);

}
