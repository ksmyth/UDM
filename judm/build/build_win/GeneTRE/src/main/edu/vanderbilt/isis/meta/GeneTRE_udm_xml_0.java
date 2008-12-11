package edu.vanderbilt.isis.meta;



public class GeneTRE_udm_xml_0 {
	private static String str = new String();

	public static String getString()
	{
		if (str.length() == 0)
		{
			str +="<Diagram name=\"GeneTRE\" version=\"2.00\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"Uml.xsd\">\n";
			str +="	<Namespace name=\"genetre\">\n";
			str +="		<Association name=\"Association\" nonpersistent=\"false\">\n";
			str +="			<AssociationRole _id=\"id10\" max=\"-1\" min=\"0\" name=\"tf\" target=\"id7\" isPrimary=\"false\" isNavigable=\"true\"/>\n";
			str +="			<AssociationRole _id=\"id11\" max=\"-1\" min=\"0\" name=\"bindsTo\" target=\"ida\" isPrimary=\"false\" isNavigable=\"true\"/>\n";
			str +="		</Association>\n";
			str +="		<Association _id=\"id12\" name=\"TRE\" assocClass=\"id3\" nonpersistent=\"false\">\n";
			str +="			<AssociationRole _id=\"id13\" max=\"-1\" min=\"0\" name=\"gene\" target=\"idd\" isPrimary=\"false\" isNavigable=\"true\"/>\n";
			str +="			<AssociationRole _id=\"id14\" max=\"-1\" min=\"0\" name=\"site\" target=\"ida\" isPrimary=\"false\" isNavigable=\"true\"/>\n";
			str +="		</Association>\n";
			str +="		<Class _id=\"id3\" name=\"TRE\" childRoles=\"id4\" isAbstract=\"false\" association=\"id12\">\n";
			str +="			<Attribute max=\"1\" min=\"1\" name=\"regulation\" type=\"Integer\" ordered=\"false\" defvalue=\"0;\" registry=\"false\" visibility=\"public\" nonpersistent=\"false\"/>\n";
			str +="			<Attribute max=\"1\" min=\"1\" name=\"position\" type=\"Integer\" ordered=\"false\" registry=\"false\" visibility=\"public\" nonpersistent=\"false\"/>\n";
			str +="			<Attribute max=\"1\" min=\"1\" name=\"strand\" type=\"Boolean\" ordered=\"false\" registry=\"false\" visibility=\"public\" nonpersistent=\"false\"/>\n";
			str +="			<Attribute max=\"1\" min=\"1\" name=\"coreScore\" type=\"Real\" ordered=\"false\" registry=\"false\" visibility=\"public\" nonpersistent=\"false\"/>\n";
			str +="			<Attribute max=\"1\" min=\"1\" name=\"matrixScore\" type=\"Real\" ordered=\"false\" registry=\"false\" visibility=\"public\" nonpersistent=\"false\"/>\n";
			str +="		</Class>\n";
			str +="		<Class _id=\"id7\" name=\"TF\" childRoles=\"id8\" isAbstract=\"false\" associationRoles=\"id10\">\n";
			str +="			<Attribute max=\"1\" min=\"1\" name=\"name\" type=\"String\" ordered=\"false\" registry=\"false\" visibility=\"public\" nonpersistent=\"false\"/>\n";
			str +="		</Class>\n";
			str +="		<Class _id=\"ida\" name=\"PWM\" childRoles=\"idb\" isAbstract=\"false\" associationRoles=\"id11 id14\">\n";
			str +="			<Attribute max=\"1\" min=\"1\" name=\"name\" type=\"String\" ordered=\"false\" registry=\"false\" visibility=\"public\" nonpersistent=\"false\"/>\n";
			str +="		</Class>\n";
			str +="		<Class _id=\"idd\" name=\"Gene\" childRoles=\"ide\" isAbstract=\"false\" associationRoles=\"id13\">\n";
			str +="			<Attribute max=\"1\" min=\"1\" name=\"name\" type=\"String\" ordered=\"false\" registry=\"false\" visibility=\"public\" nonpersistent=\"false\"/>\n";
			str +="		</Class>\n";
			str +="		<Class _id=\"id5\" name=\"Container\" isAbstract=\"false\" parentRoles=\"id6 id9 idc idf\"/>\n";
			str +="		<Composition name=\"Composition\" nonpersistent=\"false\">\n";
			str +="			<CompositionChildRole _id=\"id4\" max=\"-1\" min=\"0\" target=\"id3\" isNavigable=\"true\"/>\n";
			str +="			<CompositionParentRole _id=\"id6\" target=\"id5\" isNavigable=\"true\"/>\n";
			str +="		</Composition>\n";
			str +="		<Composition name=\"Composition\" nonpersistent=\"false\">\n";
			str +="			<CompositionChildRole _id=\"id8\" max=\"-1\" min=\"0\" target=\"id7\" isNavigable=\"true\"/>\n";
			str +="			<CompositionParentRole _id=\"id9\" target=\"id5\" isNavigable=\"true\"/>\n";
			str +="		</Composition>\n";
			str +="		<Composition name=\"Composition\" nonpersistent=\"false\">\n";
			str +="			<CompositionChildRole _id=\"idb\" max=\"-1\" min=\"0\" target=\"ida\" isNavigable=\"true\"/>\n";
			str +="			<CompositionParentRole _id=\"idc\" target=\"id5\" isNavigable=\"true\"/>\n";
			str +="		</Composition>\n";
			str +="		<Composition name=\"Composition\" nonpersistent=\"false\">\n";
			str +="			<CompositionChildRole _id=\"ide\" max=\"-1\" min=\"0\" target=\"idd\" isNavigable=\"true\"/>\n";
			str +="			<CompositionParentRole _id=\"idf\" target=\"id5\" isNavigable=\"true\"/>\n";
			str +="		</Composition>\n";
			str +="	</Namespace>\n";
			str +="</Diagram>\n";
			str +="\n";
			str +="\n";
			str +="\n";
		}
		return str;
	}
}
