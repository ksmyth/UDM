

class UdmPython:
	def __init__(self, impl):
		self.impl = impl
		self.id = impl.id
		self.name = impl.name
	def is_lib_root(self):
		return self.impl.is_lib_root
	def is_lib_object(self):
		return self.impl.is_lib_object
	
	def __eq__(self, other):
		return self.impl == other.impl
	'''	
	def __str__(self):
		return self.impl.type.name+"(id="+str(self.id)+", name="+self.name+")"
	'''
	
	