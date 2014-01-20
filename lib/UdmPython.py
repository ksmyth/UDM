
class UdmPython:
	def __init__(self, impl):
		self.__dict__['impl'] = impl
		self.__dict__['id'] = impl.id
		#self.name = impl.name
	def is_lib_root(self):
		return self.impl.is_lib_root
	def is_lib_object(self):
		return self.impl.is_lib_object
	
	def __eq__(self, other):
		return self.impl == other.impl
#	def __str__(self):
#		return self.impl.type.name+"(id="+str(self.id)+", name="+self.name+")"
	def __repr__(self):
		return self.impl.__repr__()
	def __getattr__(self, name):
		return self.impl.__getattr__(name)
	def __setattr__(self, name, value):
		self.impl.__setattr__(name, value)

	
	
