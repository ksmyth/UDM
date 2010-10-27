from Cheetah.Template import Template

import sys
import os
import os.path
sys.path.append(os.path.join(os.environ['UDM_PATH'], "bin"))
import udm
import common


if __name__ == "__main__":
    from optparse import OptionParser
    parser = OptionParser(usage="usage: %prog [options] input-uml.xml")
    parser.add_option("-o", "--output", dest="output")
    parser.add_option("--impl_namespace", dest="impl_namespace")
    (options, args) = parser.parse_args()
    if len(args) != 1:
        print parser.print_help()
        sys.exit()
    if options.output:
        output = open(options.output, "w")
        # TODO: close this
    else:
        output = sys.stdout
    if options.impl_namespace:
        common.impl_namespace = options.impl_namespace + "."
    
    uml = udm.map_uml_names(udm.uml_diagram())
    dn = udm.SmartDataNetwork(udm.uml_diagram())
    dn.open(args[0], "")

    classes = []
    classes.extend(dn.root.children(child_type=uml.Class))
    import collections
    q = collections.deque()
    q.extend(dn.root.children(child_type=uml.Namespace))
    while q:
        namespace = q.pop()
        q.extend(namespace.children(child_type=uml.Namespace))
        classes.extend(namespace.children(child_type=uml.Class))
    
    for child in classes:
        searchList = {'c': child, 'namespace': common.get_path(child.parent), 'uml': uml, 'diagram_name': dn.root.name}
        t = Template(file="Interface.tmpl", searchList=[searchList])
        output.write(str(t))

        searchList = {'c': child, 'namespace': common.impl_namespace + common.get_path(child.parent), 'uml': uml, 'diagram_name': dn.root.name}
        t = Template(file="Implementation.tmpl", searchList=[searchList])
        output.write(str(t))

    searchList = {'root': dn.root}
    t = Template(file="Initialize.tmpl", searchList=[searchList])
    output.write(str(t))

    t = Template(file="Base.tmpl", searchList=[{ 'diagram_name': dn.root.name }])
    output.write(str(t))
