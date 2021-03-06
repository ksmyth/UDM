#ifndef Uml_xsd_H
#define Uml_xsd_H
#include <string>
#pragma warning( disable : 4010)

namespace Uml_xsd
{
const std::string& getString()
{
	static std::string str;
	if (str.empty())
	{
		str +="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		str +="<?udm interface=\"Uml\" version=\"2.04\"?>\n";
		str +="<xsd:schema xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"\n";
		str +=" elementFormDefault=\"qualified\" \n";
		str +=">\n";
//		str +="<!-- generated on Thu Nov 05 17:19:40 2015 -->\n";
		str +="\n";
		str +="\n";
		str +="	<xsd:complexType name=\"CompositionChildRoleType\">\n";
		str +="		<xsd:attribute name=\"max\" type=\"xsd:long\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"min\" type=\"xsd:long\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"isNavigable\" type=\"xsd:boolean\" default=\"true\"/>\n";
		str +="		<xsd:attribute name=\"name\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"target\" type=\"xsd:IDREF\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
		str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
		str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
		str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
		str +="	</xsd:complexType>\n";
		str +="\n";
		str +="	<xsd:complexType name=\"GenericRoleType\">\n";
		str +="		<xsd:attribute name=\"isNavigable\" type=\"xsd:boolean\" default=\"true\"/>\n";
		str +="		<xsd:attribute name=\"name\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
		str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
		str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
		str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
		str +="	</xsd:complexType>\n";
		str +="\n";
		str +="	<xsd:complexType name=\"CompositionParentRoleType\">\n";
		str +="		<xsd:attribute name=\"isNavigable\" type=\"xsd:boolean\" default=\"true\"/>\n";
		str +="		<xsd:attribute name=\"name\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"target\" type=\"xsd:IDREF\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
		str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
		str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
		str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
		str +="	</xsd:complexType>\n";
		str +="\n";
		str +="	<xsd:complexType name=\"AssociationRoleType\">\n";
		str +="		<xsd:attribute name=\"isNavigable\" type=\"xsd:boolean\" default=\"true\"/>\n";
		str +="		<xsd:attribute name=\"name\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"max\" type=\"xsd:long\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"min\" type=\"xsd:long\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"isPrimary\" type=\"xsd:boolean\" default=\"false\"/>\n";
		str +="		<xsd:attribute name=\"rp_helper_user\" type=\"xsd:IDREF\"/>\n";
		str +="		<xsd:attribute name=\"rp_helper\" type=\"xsd:IDREF\"/>\n";
		str +="		<xsd:attribute name=\"target\" type=\"xsd:IDREF\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
		str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
		str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
		str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
		str +="	</xsd:complexType>\n";
		str +="\n";
		str +="	<xsd:complexType name=\"ClassType\">\n";
		str +="		<xsd:sequence>\n";
		str +="			<xsd:element name=\"Attribute\" type=\"AttributeType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
		str +="			<xsd:element name=\"Constraint\" type=\"ConstraintType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
		str +="			<xsd:element name=\"ConstraintDefinition\" type=\"ConstraintDefinitionType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
		str +="			<xsd:element name=\"TaggedValue\" type=\"TaggedValueType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
		str +="		</xsd:sequence>\n";
		str +="		<xsd:attribute name=\"isAbstract\" type=\"xsd:boolean\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"stereotype\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"name\" type=\"xsd:string\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"from\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"childRoles\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"parentRoles\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"associationRoles\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"association\" type=\"xsd:IDREF\"/>\n";
		str +="		<xsd:attribute name=\"subTypes\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"baseTypes\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
		str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
		str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
		str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
		str +="	</xsd:complexType>\n";
		str +="\n";
		str +="	<xsd:complexType name=\"DiagramType\">\n";
		str +="		<xsd:sequence>\n";
		str +="			<xsd:element name=\"Association\" type=\"AssociationType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
		str +="			<xsd:element name=\"Class\" type=\"ClassType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
		str +="			<xsd:element name=\"Composition\" type=\"CompositionType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
		str +="			<xsd:element name=\"Namespace\" type=\"NamespaceType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
		str +="			<xsd:element name=\"Diagram\" type=\"DiagramType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
		str +="		</xsd:sequence>\n";
		str +="		<xsd:attribute name=\"version\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"name\" type=\"xsd:string\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
		str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
		str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
		str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
		str +="		<xsd:attribute name=\"_libname\" type=\"xsd:string\"/>\n";
		str +="	</xsd:complexType>\n";
		str +="\n";
		str +="	<xsd:complexType name=\"AssociationType\">\n";
		str +="		<xsd:sequence>\n";
		str +="			<xsd:element name=\"AssociationRole\" type=\"AssociationRoleType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
		str +="			<xsd:element name=\"TaggedValue\" type=\"TaggedValueType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
		str +="		</xsd:sequence>\n";
		str +="		<xsd:attribute name=\"nonpersistent\" type=\"xsd:boolean\" default=\"false\"/>\n";
		str +="		<xsd:attribute name=\"name\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"assocClass\" type=\"xsd:IDREF\"/>\n";
		str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
		str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
		str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
		str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
		str +="	</xsd:complexType>\n";
		str +="\n";
		str +="	<xsd:complexType name=\"CompositionType\">\n";
		str +="		<xsd:sequence>\n";
		str +="			<xsd:element name=\"CompositionChildRole\" type=\"CompositionChildRoleType\"/>\n";
		str +="			<xsd:element name=\"CompositionParentRole\" type=\"CompositionParentRoleType\"/>\n";
		str +="		</xsd:sequence>\n";
		str +="		<xsd:attribute name=\"nonpersistent\" type=\"xsd:boolean\" default=\"false\"/>\n";
		str +="		<xsd:attribute name=\"name\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
		str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
		str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
		str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
		str +="	</xsd:complexType>\n";
		str +="\n";
		str +="	<xsd:complexType name=\"NamespaceType\">\n";
		str +="		<xsd:sequence>\n";
		str +="			<xsd:element name=\"Association\" type=\"AssociationType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
		str +="			<xsd:element name=\"Class\" type=\"ClassType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
		str +="			<xsd:element name=\"Composition\" type=\"CompositionType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
		str +="			<xsd:element name=\"Namespace\" type=\"NamespaceType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n";
		str +="		</xsd:sequence>\n";
		str +="		<xsd:attribute name=\"name\" type=\"xsd:string\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
		str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
		str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
		str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
		str +="	</xsd:complexType>\n";
		str +="\n";
		str +="	<xsd:complexType name=\"TaggedValueType\">\n";
		str +="		<xsd:attribute name=\"value\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"name\" type=\"xsd:string\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
		str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
		str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
		str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
		str +="	</xsd:complexType>\n";
		str +="\n";
		str +="	<xsd:complexType name=\"ConstraintDefinitionType\">\n";
		str +="		<xsd:attribute name=\"stereotype\" type=\"xsd:string\" default=\"method\"/>\n";
		str +="		<xsd:attribute name=\"name\" type=\"xsd:string\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"parameterList\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"expression\" type=\"xsd:string\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"returnType\" type=\"xsd:string\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
		str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
		str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
		str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
		str +="	</xsd:complexType>\n";
		str +="\n";
		str +="	<xsd:complexType name=\"AttributeType\">\n";
		str +="		<xsd:attribute name=\"name\" type=\"xsd:string\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"type\" type=\"xsd:string\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"defvalue\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"min\" type=\"xsd:long\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"max\" type=\"xsd:long\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"visibility\" type=\"xsd:string\" default=\"public\"/>\n";
		str +="		<xsd:attribute name=\"ordered\" type=\"xsd:boolean\" default=\"false\"/>\n";
		str +="		<xsd:attribute name=\"nonpersistent\" type=\"xsd:boolean\" default=\"false\"/>\n";
		str +="		<xsd:attribute name=\"registry\" type=\"xsd:boolean\" default=\"false\"/>\n";
		str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
		str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
		str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
		str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
		str +="	</xsd:complexType>\n";
		str +="\n";
		str +="	<xsd:complexType name=\"ConstraintType\">\n";
		str +="		<xsd:attribute name=\"description\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"name\" type=\"xsd:string\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"expression\" type=\"xsd:string\" use=\"required\"/>\n";
		str +="		<xsd:attribute name=\"_id\" type=\"xsd:ID\"/>\n";
		str +="		<xsd:attribute name=\"_archetype\" type=\"xsd:IDREF\"/>\n";
		str +="		<xsd:attribute name=\"_derived\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_instances\" type=\"xsd:IDREFS\"/>\n";
		str +="		<xsd:attribute name=\"_desynched_atts\" type=\"xsd:string\"/>\n";
		str +="		<xsd:attribute name=\"_real_archetype\" type=\"xsd:boolean\"/>\n";
		str +="		<xsd:attribute name=\"_subtype\" type=\"xsd:boolean\"/>\n";
		str +="	</xsd:complexType>\n";
		str +="\n";
		str +=" <xsd:element name=\"Diagram\" type=\"DiagramType\"/>\n";
		str +="\n";
		str +="</xsd:schema>\n";
		str +="\n";
	}
		return str;
}
} //namespace
#endif
