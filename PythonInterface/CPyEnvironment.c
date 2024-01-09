#pragma once
#define PY_SSIZE_T_CLEAN

#include "include/Python.h"
#include "stddef.h"
#include "include/structmember.h"

static PyObject* PyEnv_callback;

typedef struct
{
	PyObject_HEAD

	//int* action_space = new int[1, 128, 128];
	//int observation_space = 8;

	//Env Observation Space =
	//	 SensorData
	//	 Audio
	//	 Inventory
	//	 BrainStorage
	//	 Stats

	PyObject* ActionSpace;
	int number;

} CPyEnv;

static PyMemberDef PyEnv_members[] =
{
	{"number", T_INT, offsetof(CPyEnv, number), 0, "A Test Number"},
	{NULL},
};

static PyObject* PyEnv_getActionSpace(CPyEnv* self, void* closure)
{
	return Py_NewRef(self->ActionSpace);
}

static int PyEnv_setActionSpace(CPyEnv* self, PyObject* value, void* closure)
{
	if (value == NULL)
	{
		PyErr_SetString(PyExc_TypeError, "Cannot delete the last attribute");
		return -1;
	}
	if (!PyNumber_Check(value))
	{
		PyErr_SetString(PyExc_TypeError, "The las attribute value must be a number");
		return -1;
	}
	Py_SETREF(self->ActionSpace, Py_NewRef(value));
	return 0;
}

static PyObject* PyEnv_set_callback(PyObject* a, PyObject* args)
{
	//PyErr_SetString(PyExc_TypeError, "Called Set Callback");
	PyRun_SimpleString("print('Hello')");
	PyObject* result = NULL;
	PyObject* obj;

	if (PyArg_ParseTuple(args, "O:set_callback", &obj))
	{
		if (!PyCallable_Check(obj))
		{
			PyErr_SetString(PyExc_TypeError, "Parameter must be callable");
			return NULL;
		}
		Py_XINCREF(obj);
		Py_XDECREF(PyEnv_callback);
		PyEnv_callback = obj;
	
		Py_INCREF(result);
		result = obj;
		Py_XDECREF(obj);
	}
	return result;
}

static PyObject* PyEnv_set_call(PyObject* a, PyObject* args, PyObject* kwgs)
{
	return PyEnv_set_callback(a, args);
}

static PyMethodDef PyEnv_methods[] =
{
	{"set_callback", PyEnv_set_callback, METH_VARARGS, "Return the Result as PyObject*"},
	{NULL, NULL, 0, NULL}
};

static PyGetSetDef PyEnv_getsetters[] =
{
	{"ActionSpace", (getter)PyEnv_getActionSpace, (setter)PyEnv_setActionSpace, "Action Space", NULL},
	{NULL}
};

static void PyEnv_dealloc(CPyEnv* self)
{
	Py_XDECREF(self->ActionSpace);
	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* PyEnv_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	CPyEnv* self;
	self = (CPyEnv*)type->tp_alloc(type, 0);
	if (self != NULL)
	{
		// TODO: Actionspace as Array
		self->ActionSpace = PyLong_FromLong(0);
		if (self->ActionSpace == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->number = 0;
	}
	return (PyObject*)self;
}

static int PyEnv_init(CPyEnv* self, PyObject* args, PyObject* kwds)
{
	static char* kwlist[] = { (char*)"ActionSpace", (char*)"number", NULL };
	PyObject* actionSpace = NULL;

	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|00i", kwlist, &actionSpace, &self->number))
		return -1;

	if (actionSpace)
		Py_XSETREF(self->ActionSpace, Py_NewRef(actionSpace));

	return 0;
}

static PyTypeObject PyEnvObject =
{
	.ob_base = PyVarObject_HEAD_INIT(NULL, 0)
	.tp_name = "pyModule.CPyEnv",
	.tp_basicsize = sizeof(CPyEnv),
	.tp_itemsize = 0,
	.tp_dealloc = (destructor)PyEnv_dealloc,
	.tp_call = (ternaryfunc)PyEnv_set_call,
	.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	.tp_doc = PyDoc_STR("Environment"),
	.tp_methods = PyEnv_methods,
	.tp_members = PyEnv_members,
	.tp_getset = PyEnv_getsetters,
	.tp_init = (initproc)PyEnv_init,
	.tp_new = PyEnv_new,
};


