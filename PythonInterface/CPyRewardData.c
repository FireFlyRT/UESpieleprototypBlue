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

	PyObject* Reward;

} CPyRew;

//static PyMemberDef PyRew_members[] =
//{
//	{"number", T_INT, offsetof(CPyRew, number), 0, "A Test Number"},
//	{NULL},
//};

static PyObject* PyRew_ActionSpace(CPyRew* self, PyObject* Py_UNUSED)
{
	if (self->Reward == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "Reward");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->Reward);
}

static PyObject* PyRew_getActionSpace(CPyRew* self, void* closure)
{
	return Py_NewRef(self->Reward);
}

static int PyRew_setActionSpace(CPyRew* self, PyObject* value, void* closure)
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
	Py_SETREF(self->Reward, Py_NewRef(value));
	return 0;
}

static PyMethodDef PyRew_methods[] =
{
	{"Reward", (PyCFunction)PyRew_ActionSpace, METH_NOARGS, "Return the Reward"},
	{NULL}
};

static PyGetSetDef PyRew_getsetters[] =
{
	{"Reward", (getter)PyRew_getActionSpace, (setter)PyRew_setActionSpace, "Reward", NULL},
	{NULL}
};

static void PyRew_dealloc(CPyRew* self)
{
	Py_XDECREF(self->Reward);
	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* PyRew_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	CPyRew* self;
	self = (CPyRew*)type->tp_alloc(type, 0);
	if (self != NULL)
	{
		// TODO: Actionspace as Array
		self->Reward = PyUnicode_FromString("");
		if (self->Reward == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
	}
	return (PyObject*)self;
}

static int PyRew_init(CPyRew* self, PyObject* args, PyObject* kwds)
{
	static char* kwlist[] = { (char*)"Reward", NULL };
	PyObject* reward = NULL;

	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|00i", kwlist, &reward))
		return -1;

	if (reward)
		Py_XSETREF(self->Reward, Py_NewRef(reward));

	return 0;
}

static PyTypeObject PyRewObject =
{
	.ob_base = PyVarObject_HEAD_INIT(NULL, 0)
	.tp_name = "pyModule.CPyRew",
	.tp_basicsize = sizeof(CPyRew),
	.tp_itemsize = 0,
	.tp_dealloc = (destructor)PyRew_dealloc,
	.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	.tp_doc = PyDoc_STR("Reward"),
	.tp_methods = PyRew_methods,
	//.tp_members = PyRew_members,
	.tp_getset = PyRew_getsetters,
	.tp_init = (initproc)PyRew_init,
	.tp_new = PyRew_new,
};