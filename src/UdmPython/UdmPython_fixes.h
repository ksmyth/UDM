#pragma once

#include "boost/python.hpp"

#if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 10

#include <exception>

static FILE * _Py_fopen(char *path, char *mode) {
	PyObject *obj = Py_BuildValue("s", path);
	FILE *file = _Py_fopen_obj(obj, mode);

	Py_DECREF(obj);
	return file;
}


#endif
