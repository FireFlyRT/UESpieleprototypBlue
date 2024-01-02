#define PY_SSIZE_T_CLEAN

#include "pylibs/Python.h"
#include "stddef.h"
#include "pylibs/structmember.h"


typedef struct
{
	PyObject_HEAD

	PyObject* Action;
	PyObject* MovementX;
	PyObject* MovementY;
	PyObject* RotationX;
	PyObject* RotationY;

} CPyNNData;

//static PyMemberDef PyNNData_members[] =
//{
//	{"number", T_INT, offsetof(CPyNNData, number), 0, "A Test Number"},
//	{NULL},
//};

static PyObject* PyNNData_Action(CPyNNData* self, PyObject* Py_UNUSED)
{
	if (self->Action == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "Action");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->Action);
}

static PyObject* PyNNData_getAction(CPyNNData* self, void* closure)
{
	return Py_NewRef(self->Action);
}

static int PyNNData_setAction(CPyNNData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->Action, Py_NewRef(value));
	return 0;
}

static PyObject* PyNNData_MovementX(CPyNNData* self, PyObject* Py_UNUSED)
{
	if (self->MovementX == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "MovementX");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->MovementX);
}

static PyObject* PyNNData_getMovementX(CPyNNData* self, void* closure)
{
	return Py_NewRef(self->MovementX);
}

static int PyNNData_setMovementX(CPyNNData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->MovementX, Py_NewRef(value));
	return 0;
}

static PyObject* PyNNData_MovementY(CPyNNData* self, PyObject* Py_UNUSED)
{
	if (self->MovementY == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "MovementY");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->MovementY);
}

static PyObject* PyNNData_getMovementY(CPyNNData* self, void* closure)
{
	return Py_NewRef(self->MovementY);
}

static int PyNNData_setMovementY(CPyNNData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->MovementY, Py_NewRef(value));
	return 0;
}

static PyObject* PyNNData_RotationX(CPyNNData* self, PyObject* Py_UNUSED)
{
	if (self->RotationX == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "RotationX");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->RotationX);
}

static PyObject* PyNNData_getRotationX(CPyNNData* self, void* closure)
{
	return Py_NewRef(self->RotationX);
}

static int PyNNData_setRotationX(CPyNNData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->RotationX, Py_NewRef(value));
	return 0;
}

static PyObject* PyNNData_RotationY(CPyNNData* self, PyObject* Py_UNUSED)
{
	if (self->RotationY == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "RotationY");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->RotationY);
}

static PyObject* PyNNData_getRotationY(CPyNNData* self, void* closure)
{
	return Py_NewRef(self->RotationY);
}

static int PyNNData_setRotationY(CPyNNData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->RotationY, Py_NewRef(value));
	return 0;
}

static PyMethodDef PyNNData_methods[] =
{
	{"Action", (PyCFunction)PyNNData_Action, METH_NOARGS, "Return the Action"},
	{"MovementX", (PyCFunction)PyNNData_MovementX, METH_NOARGS, "Return the MovementX"},
	{"MovementY", (PyCFunction)PyNNData_MovementY, METH_NOARGS, "Return the MovementY"},
	{"RotationX", (PyCFunction)PyNNData_RotationX, METH_NOARGS, "Return the RotationX"},
	{"RotationY", (PyCFunction)PyNNData_RotationY, METH_NOARGS, "Return the RotationY"},
	{NULL}
};

static PyGetSetDef PyNNData_getsetters[] =
{
	{"Action", (getter)PyNNData_getAction, (setter)PyNNData_setAction, "Action", NULL},
	{"MovementX", (getter)PyNNData_getMovementX, (setter)PyNNData_setMovementX, "MovementX", NULL},
	{"MovementY", (getter)PyNNData_getMovementY, (setter)PyNNData_setMovementY, "MovementY", NULL},
	{"RotationX", (getter)PyNNData_getRotationX, (setter)PyNNData_setRotationX, "RotationX", NULL},
	{"RotationY", (getter)PyNNData_getRotationY, (setter)PyNNData_setRotationY, "RotationY", NULL},
	{NULL}
};

static void PyNNData_dealloc(CPyNNData* self)
{
	Py_XDECREF(self->Action);
	Py_XDECREF(self->MovementX);
	Py_XDECREF(self->MovementY);
	Py_XDECREF(self->RotationX);
	Py_XDECREF(self->RotationY);
	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* PyNNData_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	CPyNNData* self;
	self = (CPyNNData*)type->tp_alloc(type, 0);
	if (self != NULL)
	{
		self->Action = PyUnicode_FromString("");
		if (self->Action == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->MovementX = PyUnicode_FromString("");
		if (self->MovementX == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->MovementY = PyUnicode_FromString("");
		if (self->MovementY == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->RotationX = PyUnicode_FromString("");
		if (self->RotationX == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->RotationY = PyUnicode_FromString("");
		if (self->RotationY == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
	}
	return (PyObject*)self;
}

static int PyNNData_init(CPyNNData* self, PyObject* args, PyObject* kwds)
{
	static char* kwlist[] = { (char*)"Action", (char*)"MovementX", (char*)"MovementY", (char*)"RotationX", (char*)"RotationY", NULL};
	PyObject* action = NULL;
	PyObject* movementX = NULL;
	PyObject* movementY = NULL;
	PyObject* rotationX = NULL;
	PyObject* rotationY = NULL;

	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|00i", kwlist, &action, &movementX, &movementY, &rotationX, &rotationY))
		return -1;

	if (action)
		Py_XSETREF(self->Action, Py_NewRef(action));
	if (movementX)
		Py_XSETREF(self->MovementX, Py_NewRef(movementX));
	if (movementY)
		Py_XSETREF(self->MovementY, Py_NewRef(movementY));
	if (rotationX)
		Py_XSETREF(self->RotationX, Py_NewRef(rotationX));
	if (rotationY)
		Py_XSETREF(self->RotationY, Py_NewRef(rotationY));

	return 0;
}

static PyTypeObject PyNNDataObject =
{
	.ob_base = PyVarObject_HEAD_INIT(NULL, 0)
	.tp_name = "pyModule.CPyNNData",
	.tp_basicsize = sizeof(CPyNNData),
	.tp_itemsize = 0,
	.tp_dealloc = (destructor)PyNNData_dealloc,
	.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	.tp_doc = PyDoc_STR("Neural Network"),
	.tp_methods = PyNNData_methods,
	//.tp_members = PyNNData_members,
	.tp_getset = PyNNData_getsetters,
	.tp_init = (initproc)PyNNData_init,
	.tp_new = PyNNData_new,
};
