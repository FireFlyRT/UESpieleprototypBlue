#define PY_SSIZE_T_CLEAN

#include "pylibs/Python.h"
#include "stddef.h"
#include "pylibs/structmember.h"


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

static PyObject* PyEnv_ActionSpace(CPyEnv* self, PyObject* Py_UNUSED)
{
	if (self->ActionSpace == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "ActionSpace");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->ActionSpace);
}

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
	if (!PyUnicode_Check(value))
	{
		PyErr_SetString(PyExc_TypeError, "The las attribute value must be a string");
		return -1;
	}
	Py_SETREF(self->ActionSpace, Py_NewRef(value));
	return 0;
}

static PyMethodDef PyEnv_methods[] =
{
	{"ActionSpace", (PyCFunction)PyEnv_ActionSpace, METH_NOARGS, "Return the Action Space"},
	{NULL}
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
	.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	.tp_doc = PyDoc_STR("Environment"),
	.tp_methods = PyEnv_methods,
	.tp_members = PyEnv_members,
	.tp_getset = PyEnv_getsetters,
	.tp_init = (initproc)PyEnv_init,
	.tp_new = PyEnv_new,
};


