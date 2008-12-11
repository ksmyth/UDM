package edu.vanderbilt.isis.meta;



public class TimeSeries_udm_xml_0 {
	private static String str = new String();

	public static String getString()
	{
		if (str.length() == 0)
		{
			str +="<Diagram name=\"TimeSeries\" version=\"1.00\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"Uml.xsd\">\n";
			str +="	<Association name=\"Association\" nonpersistent=\"false\">\n";
			str +="		<AssociationRole _id=\"id11\" max=\"-1\" min=\"0\" name=\"src_tp\" target=\"id4\" isPrimary=\"false\" isNavigable=\"true\"/>\n";
			str +="		<AssociationRole _id=\"id12\" max=\"-1\" min=\"0\" name=\"dst_dv\" target=\"ide\" isPrimary=\"false\" isNavigable=\"true\"/>\n";
			str +="	</Association>\n";
			str +="	<Association name=\"Association\" nonpersistent=\"false\">\n";
			str +="		<AssociationRole _id=\"id13\" max=\"-1\" min=\"0\" name=\"src\" target=\"id4\" isPrimary=\"false\" isNavigable=\"true\"/>\n";
			str +="		<AssociationRole _id=\"id14\" max=\"-1\" min=\"0\" name=\"dst\" target=\"id8\" isPrimary=\"false\" isNavigable=\"true\"/>\n";
			str +="	</Association>\n";
			str +="	<Class _id=\"id3\" name=\"string_data\" baseTypes=\"id4\" isAbstract=\"false\">\n";
			str +="		<Attribute max=\"1\" min=\"1\" name=\"value\" type=\"String\" ordered=\"false\" registry=\"false\" visibility=\"public\" nonpersistent=\"false\"/>\n";
			str +="	</Class>\n";
			str +="	<Class _id=\"id5\" name=\"integer_data\" baseTypes=\"id4\" isAbstract=\"false\">\n";
			str +="		<Attribute max=\"1\" min=\"1\" name=\"value\" type=\"Integer\" ordered=\"false\" registry=\"false\" visibility=\"public\" nonpersistent=\"false\"/>\n";
			str +="	</Class>\n";
			str +="	<Class _id=\"id6\" name=\"real_data\" baseTypes=\"id4\" isAbstract=\"false\">\n";
			str +="		<Attribute max=\"1\" min=\"1\" name=\"value\" type=\"Real\" ordered=\"false\" registry=\"false\" visibility=\"public\" nonpersistent=\"false\"/>\n";
			str +="	</Class>\n";
			str +="	<Class _id=\"id7\" name=\"boolean_data\" baseTypes=\"id4\" isAbstract=\"false\">\n";
			str +="		<Attribute max=\"1\" min=\"1\" name=\"value\" type=\"Boolean\" ordered=\"false\" registry=\"false\" visibility=\"public\" nonpersistent=\"false\"/>\n";
			str +="	</Class>\n";
			str +="	<Class _id=\"id8\" name=\"data_label\" childRoles=\"id9\" isAbstract=\"false\" associationRoles=\"id14\">\n";
			str +="		<Attribute max=\"1\" min=\"0\" name=\"name\" type=\"String\" ordered=\"false\" registry=\"false\" visibility=\"public\" nonpersistent=\"false\"/>\n";
			str +="	</Class>\n";
			str +="	<Class _id=\"id4\" name=\"data_value\" subTypes=\"id3 id5 id6 id7\" childRoles=\"idc\" isAbstract=\"true\" associationRoles=\"id11 id13\"/>\n";
			str +="	<Class _id=\"ida\" name=\"Container\" isAbstract=\"false\" parentRoles=\"idb idd id10\"/>\n";
			str +="	<Class _id=\"ide\" name=\"time_point\" childRoles=\"idf\" isAbstract=\"false\" associationRoles=\"id12\">\n";
			str +="		<Attribute max=\"1\" min=\"1\" name=\"at\" type=\"Real\" ordered=\"false\" registry=\"false\" visibility=\"public\" nonpersistent=\"false\"/>\n";
			str +="	</Class>\n";
			str +="	<Composition name=\"Composition\" nonpersistent=\"false\">\n";
			str +="		<CompositionChildRole _id=\"id9\" max=\"-1\" min=\"0\" target=\"id8\" isNavigable=\"true\"/>\n";
			str +="		<CompositionParentRole _id=\"idb\" target=\"ida\" isNavigable=\"true\"/>\n";
			str +="	</Composition>\n";
			str +="	<Composition name=\"Composition\" nonpersistent=\"false\">\n";
			str +="		<CompositionChildRole _id=\"idc\" max=\"-1\" min=\"0\" target=\"id4\" isNavigable=\"true\"/>\n";
			str +="		<CompositionParentRole _id=\"idd\" target=\"ida\" isNavigable=\"true\"/>\n";
			str +="	</Composition>\n";
			str +="	<Composition name=\"Composition\" nonpersistent=\"false\">\n";
			str +="		<CompositionChildRole _id=\"idf\" max=\"-1\" min=\"0\" target=\"ide\" isNavigable=\"true\"/>\n";
			str +="		<CompositionParentRole _id=\"id10\" target=\"ida\" isNavigable=\"true\"/>\n";
			str +="	</Composition>\n";
			str +="</Diagram>\n";
			str +="\n";
			str +="\n";
			str +="\n";
		}
		return str;
	}
}
