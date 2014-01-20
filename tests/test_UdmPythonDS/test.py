import sys
sys.path.append('/Users/endre/trunk/lib')
import udm          # C++ UdmPhyton module
import UdmPython    # python wrapper
import Uml          # generated UML classes
import LampDiagram  # generated Domain Specific API



pdn = udm.SmartDataNetwork(udm.uml_diagram())
pdn.open(r"../../samples/LampDiagram_udm.xml","")
LampDiagram.initialize(udm.map_uml_names(pdn.root), udm.map_uml_names(udm.uml_diagram()))


dn = udm.SmartDataNetwork(pdn.root)
dn.open(r"Lamp.mem","")

rf =LampDiagram.RootFolder(dn.root)
l_children = rf.getLampChildren()
lamp_1 = l_children[0]

print lamp_1.ModelName
lamp_1.ModelName = "test_python"
print lamp_1.ModelName
print lamp_1.meta.name


dn.close_no_update()
pdn.close_no_update()
