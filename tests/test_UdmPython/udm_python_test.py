import sys
import os.path
import unittest

sys.path.append(r"C:\Program Files\ISIS\Udm\bin")
sys.path.append(os.path.join(os.path.dirname(__file__), "../../bin/"))
# copy udm.pyd to C:\Program Files\ISIS\Udm\bin
import udm

def map_class_names(diagram):
    class_meta = filter(lambda class_: class_.name == "Class", udm.uml_diagram().children())[0]
    class ClassMap(object):
        def __init__(self, d):
            self.__dict__.update(d)
    # TODO: Namespaces
    return ClassMap(map(lambda class_: (class_.name, class_), diagram.children(child_type=class_meta)))

def get_names(col):
	names = map(lambda x: x.name, col)
	names.sort()
	return names


class TestUdmPython(unittest.TestCase):
	def __init__(self, test):
		unittest.TestCase.__init__(self, test)

	def testudmpython(self):
		# need to open meta DN since it isn't compiled in
		test_meta_dn= udm.SmartDataNetwork(udm.uml_diagram())
		test_meta_dn.open(r"UdmPythonTestMeta.xml", "")
		self.assertEquals(test_meta_dn.root.name, "UdmPythonTestMeta")
		test_meta = map_class_names(test_meta_dn.root)

		dn = udm.SmartDataNetwork(test_meta_dn.root)
		dn.open(r"UdmPythonTestModel.mga", "")

		container = dn.root.children()[0]
		self.assertTrue(container)
		# get children by type
		self.assertEquals(get_names(container.children(child_type=test_meta.AtomB)), [ "cmproleA1", "cmproleA2", "cmproleB1" ]) # also accepts child_role, parent_role
		# get children by child's composition role
		self.assertEquals(get_names(container.cmproleA_role_children), [ "cmproleA1", "cmproleA2" ])
		self.assertEquals(container.children(child_role="cmproleA"), container.cmproleA_role_children)
		self.assertEquals(get_names(container.cmproleB_role_children), [ "cmproleB1"] )
		self.assertEquals(container.type, test_meta.Container)
		cmproleA1 = filter(lambda x: x.name =="cmproleA1", container.children())[0]
		cmproleA2 = filter(lambda x: x.name =="cmproleA2", container.children())[0]
		self.assertEquals(cmproleA1.dstConnection, [cmproleA2])
		self.assertEquals(cmproleA1.adjacent(dst_role="dstConnection"), [cmproleA2])
		self.assertEquals(cmproleA1.adjacent(src_role="srcConnection"), [])
		
		# trying to access nonexistant attribute raises an exception
		try:
			self.assertFalse(container.nonexistantattribute)
		except RuntimeError, e:
			self.assertTrue(str(e).find("Container") != -1)
			self.assertTrue(str(e).find("nonexistantattribute") != -1)
		else:
			self.fail("Expected an exception")

		uml = map_class_names(udm.uml_diagram())
		for o in udm.uml_diagram().children():
			if get_names(o.children(child_type=uml.CompositionChildRole)) == ['namespaces'] and get_names(o.children(child_type=uml.CompositionParentRole)) == ['parent']:
				break
		else:
			self.fail()
		namespaces = o.children(child_type=uml.CompositionChildRole)[0] # i.e. CompositionChildRole in Composition Diagram<>---Namespace
		self.assertEquals(namespaces.min, 0)
		self.assertEquals(namespaces.max, -1)
		self.assertTrue(namespaces.isNavigable)
		self.assertEquals(namespaces.target, uml.Namespace)
		self.assertEquals(namespaces.adjacent(dst_role="target"), uml.Namespace)
		self.assertEquals(namespaces.adjacent(dst_role="target", src_role="childRoles"), uml.Namespace)
		# if we don't specify dst_role, adjacent() returns a list
		self.assertEquals(namespaces.adjacent(), [uml.Namespace])
		self.assertEquals(namespaces.adjacent(src_role="childRoles"), [uml.Namespace])

		self.assertEquals(get_names(test_meta_dn.root.children()[0].adjacent(dst_role="subTypes")), []) # also accepts dst_role, association_class
		self.assertTrue(test_meta_dn.root.children()[0].name)
		self.assertTrue(test_meta_dn.root.children()[0].stereotype)
		self.assertEqual(test_meta.AtomA.name, "AtomA")
		self.assertEquals(test_meta.AtomA, test_meta.AtomA)
		self.assertNotEqual(test_meta.AtomA, test_meta.AtomB)
		self.assertNotEqual(test_meta_dn.root, udm.uml_diagram())
		self.assertNotEqual(test_meta_dn, udm.uml_diagram()) # disparate types
		self.assertNotEqual(udm.uml_diagram(), test_meta_dn) # disparate types
		self.assertTrue(test_meta.AtomA.__hash__() > 0)
		self.assertTrue(test_meta.AtomA)


		dn.close_no_update()
		test_meta_dn.close_no_update()



if __name__ == '__main__':
	runner = unittest.TextTestRunner()
	runner.run(TestUdmPython("testudmpython"))
