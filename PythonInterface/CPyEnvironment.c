#pragma once
#define PY_SSIZE_T_CLEAN

#include "include/Python.h"
#include "stddef.h"
#include "include/structmember.h"

static PyObject* PyEnv_callback = NULL;

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
	/*PyEnv_callback = PyLong_FromLong(30l);
	Py_XINCREF(PyEnv_callback);*/
	return Py_NewRef(self->ActionSpace);
}

static int PyEnv_setActionSpace(CPyEnv* self, PyObject* value, void* closure)
{
	/*PyEnv_callback = PyLong_FromLong(32l);
	Py_XINCREF(PyEnv_callback);*/
	if (value == NULL)
	{
		PyErr_SetString(PyExc_TypeError, "Cannot delete the last attribute");
		return -1;
	}
	if (!PyNumber_Check(value))
	{
		PyErr_SetString(PyExc_TypeError, "The last attribute value must be a number");
		return -1;
	}
	Py_SETREF(self->ActionSpace, Py_NewRef(value));
	return 0;
}

// Diese Funktion soll aufgerufen werden, es passiert aber nichts
static PyObject* PyEnv_set_callback(PyObject* a, PyObject* args)
{
	PyRun_SimpleString("print('HALLLLLOOOOOOO!!!!!!!!!')");
	Py_SETREF(PyEnv_callback, Py_NewRef(PyLong_FromLong(41l))); // Setzen von PyEnv_callback Variable passiert nicht
	Py_XINCREF(PyEnv_callback);
	/*PyEnv_callback = PyLong_FromLong(32l);					// Auch nicht damit
	Py_XINCREF(PyEnv_callback);*/
	PyObject* result = PyLong_FromLong(40l);					// Result wird auch nicht gesetzt
	Py_XINCREF(result);
	//PyObject* obj;
	a = PyLong_FromLong(96l);									// a wird auch nicht gesetzt
	Py_INCREF(a);												
																// und der return ist auch nullptr
	//if (PyArg_ParseTuple(args, "O:set_callback", &obj))
	//{
	//	if (!PyCallable_Check(obj))
	//	{
	//		PyErr_SetString(PyExc_TypeError, "Parameter must be callable");
	//		return PyLong_FromLong(9999);
	//	}
	//	Py_XINCREF(obj);
	//	//Py_XDECREF(PyEnv_callback);
	//	//PyEnv_callback = obj;

	//	Py_INCREF(result);
	//	result = PyLong_FromLong(10);
	//	Py_XDECREF(obj);
	//}

	//result = PyLong_FromLong(10);

	return a;
}

static PyObject* PyEnv_set_call(PyObject* a, PyObject* args, PyObject* kwgs)
{
	PyEnv_callback = PyLong_FromLong(50l);
	Py_XINCREF(PyEnv_callback);
	return PyEnv_set_callback(a, args);
}

// Methode wird hier mit dem selben Namen registriert, wie sie in Python ist
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
	PyEnv_callback = PyLong_FromLong(11l);			// Auch das setzten in anderen Methoden, 
	Py_XINCREF(PyEnv_callback);  					// die automatisch aufgerufen werden funktioniert nicht
	CPyEnv* self;
	self = (CPyEnv*)type->tp_alloc(type, 0);
	if (self != NULL)
	{
		// TODO: Actionspace as Array
		self->ActionSpace = PyLong_FromLong(12l);
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
	/*PyEnv_callback = PyLong_FromLong(21);
	Py_XINCREF(PyEnv_callback);*/
	static char* kwlist[] = { (char*)"ActionSpace", (char*)"number", NULL };
	PyObject* actionSpace = NULL;

	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|00i", kwlist, &actionSpace, &self->number))
		return -1;

	if (actionSpace)
		Py_XSETREF(self->ActionSpace, Py_NewRef(PyLong_FromLong(24l)));
		self->ActionSpace = PyLong_FromLong(22l);

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
