#include "PyEnvironment.h"
#include <string> 
#include <stddef.h>
#include "structmember.h"

#define PY_SSIZE_T_CLEAN

static PyMemberDef PyEnv_members[] =
{
	{"number", T_INT, offsetof(PyEnv, number), 0, "A Test Number"},
	{NULL},
};

static PyMethodDef PyEnv_methods[] =
{
	{"ActionSpace", (PyCFunction)PyEnvironment::PyEnv_ActionSpace, METH_NOARGS, "Return the Action Space"},
	{NULL}
};

static PyGetSetDef PyEnv_getsetters[] =
{
	{"ActionSpace", (getter)PyEnvironment::PyEnv_getActionSpace, (setter)PyEnvironment::PyEnv_setActionSpace, "Action Space", NULL},
	{NULL}
};

static PyTypeObject PyEnvObject =
{
	.ob_base = PyVarObject_HEAD_INIT(NULL, 0)
	.tp_name = "pyModule.PyEnv",
	.tp_basicsize = sizeof(PyEnv),
	.tp_itemsize = 0,
	.tp_dealloc = (destructor)PyEnvironment::PyEnv_dealloc,
	.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	.tp_doc = PyDoc_STR("Environment"),
	.tp_methods = PyEnv_methods,
	.tp_members = PyEnv_members,
	.tp_getset = PyEnv_getsetters,
	.tp_init = (initproc)PyEnvironment::PyEnv_init,
	.tp_new = PyEnvironment::PyEnv_new,
};

static PyModuleDef PyModule =
{
	.m_base = PyModuleDef_HEAD_INIT,
	.m_name = "pyModule",
	.m_doc = "Py Module for C++",
	.m_size = -1,
};

PyMODINIT_FUNC PyInit_PyEnv() 
{
	PyObject* obj;
	if (PyType_Ready(&PyEnvObject) < 0) 
		return NULL;

	obj = PyModule_Create(&PyModule);
	if (obj == NULL)
		return NULL;

	Py_INCREF(&PyEnvObject);
	if (PyModule_AddObject(obj, "PyEnv", (PyObject*)&PyEnvObject) < 0)
	{
		Py_DECREF(&PyEnvObject);
		Py_DECREF(obj);
		return NULL;
	}

	return obj;
}

void PyEnvironment::PyEnv_dealloc(PyEnv* self)
{
	Py_XDECREF(self->ActionSpace);
	Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject* PyEnvironment::PyEnv_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	PyEnv* self;
	self = (PyEnv*)type->tp_alloc(type, 0);
	if (self != NULL)
	{
		// TODO: Actionspace as Array
		self->ActionSpace = PyUnicode_FromString("");
		if (self->ActionSpace == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->number = 0;
	}
	return (PyObject*)self;
}

int PyEnvironment::PyEnv_init(PyEnv* self, PyObject* args, PyObject* kwds)
{
	static char* kwlist[] = { (char*)"ActionSpace", (char*)"number", NULL };
	PyObject* actionSpace = NULL;

	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|00i", kwlist, &actionSpace, &self->number))
		return -1;

	if (actionSpace)
		Py_XSETREF(self->ActionSpace, Py_NewRef(actionSpace));

	return 0;
}

PyObject* PyEnvironment::PyEnv_ActionSpace(PyEnv* self, PyObject* Py_UNUSED)
{
	if (self->ActionSpace == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "ActionSpace");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->ActionSpace);
}

PyObject* PyEnvironment::PyEnv_getActionSpace(PyEnv* self, void* closure)
{
	return Py_NewRef(self->ActionSpace);
}

int PyEnvironment::PyEnv_setActionSpace(PyEnv* self, PyObject* value, void* closure)
{
	if (value == NULL)
	{
		PyErr_SetString(PyExc_TypeError, "Cannot delete the last attribute");
		return -1;
	}
	if (!PyUnicode_Check(value))
	{
		PyErr_SetString(PyExc_TypeError, "The las attribute value must be a string");
		return -1;
	}
	Py_SETREF(self->ActionSpace, Py_NewRef(value));
	return 0;
}
