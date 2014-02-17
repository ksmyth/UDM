def indent(indent_tabs=0):
	indent = ""
	for i in range(0,indent_tabs):
		indent += "\t";
	return indent

class UdmPython(object):
	@property
	def parent(self):
		return UdmPython(self.impl.parent)

	def __init__(self, impl):
		if isinstance(impl, UdmPython):
			#"copy constructor"... 
			self.__dict__['impl'] = impl.impl
			self.__dict__['id'] = impl.impl.id
			self.__dict__['indent'] = 0
		else:
			#construction from udm.Object
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
		#child_type could be either Udm.Object or UdmPython (or descendants)
		ret = []
		if isinstance(child_type, UdmPython):
			for child in self.impl.children(child_role, parent_role, child_type.impl):
				ret.append(UdmPython(child))
			return ret
		else:
			for child in self.impl.children(child_role, parent_role, child_type):
				ret.append(UdmPython(child))
			return ret

	def __eq__(self, other):
		return self.__dict__['impl'] == other.__dict__['impl']
	def __ne__(self, other):
		return self.__dict__['impl'] != other.__dict__['impl']
	def __repr__(self):
		return self.impl.__repr__()
	def setIndent(self,i):
		self.__dict__['indent'] = i

	def __str__(self):
		import udm	
		if self.impl == udm.null:
			 return self.impl.__str__()
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
				a_attr = ArrayAttr(self, attr)
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
	@property
	def array(self):
		attr_value=self.obj.get_attribute(self.attr.impl)
		return ArrayAttr.escaped_split(str(attr_value), ';')

	@array.setter
	def array(self, val):
		if type(val) != type([]):
			raise Exception("ArrayAttr.array.setter: expected array")
		new_arr = []
		for val_item in val:
			new_arr.append(str(val_item))#this will work for any type
		arr_str = ArrayAttr.escaped_combine(new_arr, ';')
        	self.obj.set_attribute(self.attr.impl, arr_str)

	@staticmethod
	def escaped_split(s, delim):
		ret = []
		current = []
		itr = iter(s)
		for ch in itr:
			if ch == '\\':
				try:
                			# skip the next character; it has been escaped!
                			#current.append('\\')
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
	@staticmethod
	def escaped_combine(s, delim):
		ret = ""
		first = True
		for s_i in s:
			if not first: ret += delim
			first = False
			itr = iter(s_i)
			for ch in itr:
				if ch == '\\' or ch == delim:
					ret += '\\'
				ret += ch
		return ret;


	def __init__(self, obj, attr):
		import Uml
		if attr.max==0 or attr.max == 1:
			raise ("Attribute is not an array")
		
		self.attr = attr
		self.obj = obj.impl
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
		attr_value=self.obj.get_attribute(self.attr.impl)
		str_array = ArrayAttr.escaped_split(str(attr_value), ';')
		if index > len(str_array):
			raise Exception("Index out of array boundaries")
		return str_array[index]

	def __setitem__(self, index, value):

		attr_value=self.obj.get_attribute(self.attr.impl)
		str_array = ArrayAttr.escaped_split(str(attr_value), ';')
		if index > len(str_array):
			raise Exception("Index out of array boundaries")
		str_array_new = []
		i=0;
		for str_array_i in str_array:
			if i == index:
				str_array_new.append(str(value))
			else:
				str_array_new.append(str_array_i)
			i=i+1
		arr_str = ArrayAttr.escaped_combine(str_array_new, ';')
        	self.obj.set_attribute(self.attr.impl, arr_str)


class StrArrayAttr(ArrayAttr):

	def __init__(self, obj, attr):
		import Uml
		if attr.type != "String":
			raise Exception("Attribute is not of type String")
		super(StrArrayAttr, self).__init__(obj, attr)


			
class IntArrayAttr(ArrayAttr):
	@property
	def array(self):
		str_array = super(IntArrayAttr, IntArrayAttr).array.fget(self)
		ret = []
		for str_i in str_array:
			ret.append(int(str_i))
		return ret

	def __init__(self, obj, attr):
		import Uml
		if attr.type != "Integer":
			raise ("Attribute is not of type Integer")
		super(StrArrayAttr, self).__init__(obj, attr)

	def __getitem__(self,index):
		return int(super(IntArrayAttr, self).__getitem__(index))


class RealArrayAttr(ArrayAttr):
	@property
	def array(self):
		str_array = super(IntArrayAttr, IntArrayAttr).array.fget(self)
		ret = []
		for str_i in str_array:
			ret.append(float(str_i))
		return ret

	def __init__(self, obj, attr):
		import Uml
		if attr.type != "Real":
			raise ("Attribute is not of type Real")
		super(StrArrayAttr, self).__init__(obj, attr)

	def __getitem__(self,index):
		return float(super(RealArrayAttr, self).__getitem__(index))



class BooleanArrayAttr(ArrayAttr):
	@property
	def array(self):
		str_array = super(IntArrayAttr, IntArrayAttr).array.fget(self)
		ret = []
		for str_i in str_array:
			ret.append(lower(str_i) == "true")
		return ret
	
	def __init__(self, obj, attr):
		import Uml
		if attr.type != "Boolean":
			raise ("Attribute is not of type Boolean")
		super(StrArrayAttr, self).__init__(obj, attr)

	def __getitem__(self,index):
		value = super(RealArrayAttr, self).__getitem__(index)
		return value.lower()=="true" 
			
		
def GetUmlAttributeByName(cl, name):
	import udm
	import Uml
	attrs = cl.getAttributeChildren()
	for attr in attrs:
		if attr.name == name:
			return attr
	return Uml.Attribute(udm.null)

def GetUmlClassByName(dgr, name):
	import udm
	import Uml
	classes = dgr.getClassChildren()
	for cl in classes:
		if cl.name == name:
			return cl
	return Uml.Class(udm.null)	
