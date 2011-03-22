import sys
import os
import os.path
import unittest

sys.path.append(r"C:\Program Files\ISIS\Udm\bin")
if os.environ.has_key("UDM_PATH"):
    sys.path.append(os.path.join(os.environ["UDM_PATH"], "bin"))

sys.path.append(os.path.join(os.path.dirname(__file__), "../../bin/"))
import udm
# import udmd as udm

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
        test_meta = udm.map_uml_names(test_meta_dn.root)

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
        self.assertEquals(cmproleA1.adjacent(src_role="srcConnection"), [cmproleA2])
        self.assertEquals(cmproleA2.adjacent(dst_role="dstConnection"), [])
        self.assertEquals(cmproleA2.adjacent(src_role="srcConnection"), [])
        AtomA1 = filter(lambda x: x.name =="AtomA1", container.children())[0]
        self.assertEquals(AtomA1.boolattr, True)
        self.assertEquals(AtomA1.stringattr, "teststring")
        self.assertEquals(AtomA1.intattr, 42)
        AtomA1.intattr = 60
        self.assertEquals(AtomA1.intattr, 60)
        AtomA1.stringattr = "test123"
        self.assertEquals(AtomA1.stringattr, "test123")
        
        
        # trying to access nonexistant attribute raises an exception
        try:
            self.assertFalse(container.nonexistantattribute)
        except RuntimeError, e:
            # the error message should include the type's name and attribute name
            self.assertTrue(str(e).find("Container") != -1)
            self.assertTrue(str(e).find("nonexistantattribute") != -1)
        else:
            self.fail("Expected an exception")

        uml = udm.map_uml_names(udm.uml_diagram())
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

        #KMS: BUG: childRole_role_children should return a singleton, not a list
        self.assertEquals(test_meta.AtomA.childRoles[0].parent.childRole_role_children[0].target, test_meta.AtomA)

        dn.close_no_update()
        test_meta_dn.close_no_update()



if __name__ == '__main__':
    runner = unittest.TextTestRunner()
    runner.run(TestUdmPython("testudmpython"))
