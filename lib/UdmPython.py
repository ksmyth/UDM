def indent(indent_tabs=0):
	indent = ""
	for i in range(0,indent_tabs):
		indent += "\t";
	return indent

class UdmPython:
	def __init__(self, impl):
		self.__dict__['impl'] = impl
		self.__dict__['id'] = impl.id
		self.__dict__['indent'] = 0

	def is_lib_root(self):
		return self.impl.is_lib_root
	def is_lib_object(self):
		return self.impl.is_lib_object

	def _type(self):
		import Uml
		return Uml.Class.cast(self.impl.type)

	def children(self,child_role=None, parent_role=None, child_type=None):
		ret = []
		for child in self.impl.children(child_role, parent_role, child_type):
			ret.append(UdmPython(child))
		return ret

	def __impl(self):
		return self.__dict__['impl']
	def __eq__(self, other):
		return self.__dict__['impl'] == other.__dict__['impl']
	def __ne__(self, other):
		return self.__dict__['impl'] != other.__dict__['impl']
	def __repr__(self):
		return self.impl.__repr__()
	def setIndent(self,i):
		self.__dict__['indent'] = i

	def __str__(self):
		import Uml
		line = str()
		cl = Uml.Class(self.impl.type)
		indent_tabs = self.__dict__['indent']
		line = indent(indent_tabs) + "--------------------------------------------------------------------" + "\n"
		line += indent(indent_tabs) + "Object's type:"  + cl.name + "\n"
		line += indent(indent_tabs) + self.impl.__repr__() + "\n"
		attrs= cl.getAttributeChildren()
		for attr in attrs:
			attr_value = self.impl.get_attribute(attr.impl)
			if attr.max == 1 or attr.max == 0:
				if attr.type == "Integer":
					line +=  indent(indent_tabs) + "attribute name: " + attr.name + ", value: %d " % (attr_value) +"\n"
				elif attr.type == "Real":
					line += indent(indent_tabs) + "attribute name: " + attr.name + ", value: %f " % (attr_value) + "\n"
				elif attr.type == "Boolean":
					boolstr = "true" if attr_value else "false"
					line += indent(indent_tabs) + "attribute name: " + attr.name + ", value:" + boolstr + "\n"
                		elif attr.type == "String":
					line += indent(indent_tabs) + "attribute name: " + attr.name + ", value:" + attr_value + "\n"
            		else:
				a_attr = ArrayAttr(self.impl, attr)
				a_attr.setIndent(indent_tabs)
				line += a_attr.__str__() + "\n"
		return line

	def __getattr__(self, name):
		return self.impl.__getattr__(name)
	def __setattr__(self, name, value):
		self.impl.__setattr__(name, value)
	def __nonzero__(self):
		return self.impl.__nonzero__();

class ArrayAttr(object):


	@staticmethod
	def escaped_split(s, delim):
		ret = []
		current = []
		itr = iter(s)
		for ch in itr:
			if ch == '\\':
				try:
                			# skip the next character; it has been escaped!
                			current.append('\\')
                			current.append(itr.next())
            			except StopIteration:
                			pass
        		elif ch == delim:
            			# split! (add current to the list and reset it)
            			ret.append(''.join(current))
            			current = []
        		else:
            			current.append(ch)
    		ret.append(''.join(current))
    		return ret

	def __init__(self, obj, attr):
		import Uml
		if attr.max==0 or attr.max == 1:
			raise ("Attribute is not an array")
		
		self.attr = attr
		self.obj = obj
		self.indent = 0

	def setIndent(self,i):
		self.indent = i

	def __str__(self):
		import Uml
		lines = indent(self.indent) + "Array attribute name: " + self.attr.name + ", type:" + self.attr.type
		lines += "\n"
		attr_value=self.obj.get_attribute(self.attr.impl)
		str_array = ArrayAttr.escaped_split(str(attr_value), ';')
		i=0
		for str_i in str_array:
			lines += indent(self.indent) + self.attr.name + "[" + str(i) + "] =" + str_i
			lines +="\n"
			i = i + 1
		return lines

	def __getitem__(self,index):
		attr_value=obj.get_attribute(attr.impl)
		str_array = ArrayAttr.escaped_split(str(attr_value), ';')
		return self.str_array[index]

class StrArrayAttr(ArrayAttr):

	def __init__(self, obj, attr):
		import Uml
		if attr.type != "String":
			raise Exception("Attribute is not of type String")
		super(StrArrayAttr, self).__init__(obj, attr)


			
class IntArrayAttr(ArrayAttr):

	def __init__(self, obj, attr):
		import Uml
		if attr.type != "Integer":
			raise ("Attribute is not of type Integer")
		super(StrArrayAttr, self).__init__(obj, attr)

	def __getitem__(self,index):
		return int(super(IntArrayAttr, self).__getitem__[index])

class RealArrayAttr(ArrayAttr):

	def __init__(self, obj, attr):
		import Uml
		if attr.type != "Real":
			raise ("Attribute is not of type Real")
		super(StrArrayAttr, self).__init__(obj, attr)

	def __getitem__(self,index):
		return int(super(RealArrayAttr, self).__getitem__[index])

class BooleanArrayAttr(ArrayAttr):

	def __init__(self, obj, attr):
		import Uml
		if attr.type != "Boolean":
			raise ("Attribute is not of type Boolean")
		super(StrArrayAttr, self).__init__(obj, attr)

	def __getitem__(self,index):
		value = super(RealArrayAttr, self).__getitem__[index]
		return value.lower()=="true" 
			
		
