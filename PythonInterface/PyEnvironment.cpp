#include "PyEnvironment.h"

#define PY_SSIZE_T_CLEAN

PyObject* PyEnvironment::PyEnvironment_nums(PyEnv* self, PyObject* args)
{
	if (!PyArg_ParseTuple(args, ":nums"))
	{
		return NULL;
	}
	return PyLong_FromLong(self->nums);
}

int PyEnvironment::GetNumargs()
{
	return Cnumargs;
}

PyObject* PyEnvironment::PyEnvironment_getNumargs(PyEnv* self, void* closure)
{
	return Py_NewRef(self->numargs);
}

int PyEnvironment::PyEnvironment_setNumargs(PyEnv* self, PyObject* value, void* closure)
{
	// Check if value is valid

	Py_SETREF(self->numargs, Py_NewRef(value));
	// TODO (Major): Set the Value for C++ to use it
	SetNumargs(self);
	return 0;
}

void PyEnvironment::SetNumargs(PyEnv* self)
{
	printf("Setting numargs!");
	Cnumargs = (int)PyFloat_AsDouble(self->numargs);
}

// GetSet dont need to be implemented by PyMethodDef
// For Costume Types add to .tp_getset
static PyGetSetDef PyEnvironment_getsetters[] =
{
	{
		"numargs", 
		(getter)PyEnvironment::PyEnvironment_getNumargs,
		(setter)PyEnvironment::PyEnvironment_setNumargs,
		"Variable numargs",
		NULL
	},
	{
		NULL // Sentinal
	}
};

static PyMethodDef PyEnvironmentMethods[] =
{
	{
		"nums", (PyCFunction)PyEnvironment::PyEnvironment_nums, METH_VARARGS,
		"Return the number of arguments received by the process."
	},
	{
		NULL, NULL, 0, NULL
	}
};

static PyModuleDef PyEnvironmentModule =
{
	PyModuleDef_HEAD_INIT, "PyEnvironment", NULL, -1, PyEnvironmentMethods,
	NULL, NULL, NULL, NULL
};

PyObject* PyEnvironment::PyInit_PyEnvironment()
{
	return PyModule_Create(&PyEnvironmentModule);
}
