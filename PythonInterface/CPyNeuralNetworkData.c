#pragma once
#define PY_SSIZE_T_CLEAN

#include "include/Python.h"
#include "stddef.h"
#include "include/structmember.h"


typedef struct
{
	PyObject_HEAD

	PyObject* Action;
	PyObject* MovementX;
	PyObject* MovementY;
	PyObject* RotationZ;

} CPyNNData;

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
		PyErr_SetString(PyExc_TypeError, "The last attribute value must be a string");
		return -1;
	}
	Py_SETREF(self->MovementX, Py_NewRef(value));
	return 0;
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
		PyErr_SetString(PyExc_TypeError, "The last attribute value must be a string");
		return -1;
	}
	Py_SETREF(self->MovementY, Py_NewRef(value));
	return 0;
}

static PyObject* PyNNData_getRotationX(CPyNNData* self, void* closure)
{
	return Py_NewRef(self->RotationZ);
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
	Py_SETREF(self->RotationZ, Py_NewRef(value));
	return 0;
}

static PyMethodDef PyNNData_methods[] =
{
	{NULL}
};

static PyGetSetDef PyNNData_getsetters[] =
{
	{"Action", (getter)PyNNData_getAction, (setter)PyNNData_setAction, "Action", NULL},
	{"MovementX", (getter)PyNNData_getMovementX, (setter)PyNNData_setMovementX, "MovementX", NULL},
	{"MovementY", (getter)PyNNData_getMovementY, (setter)PyNNData_setMovementY, "MovementY", NULL},
	{"RotationZ", (getter)PyNNData_getRotationX, (setter)PyNNData_setRotationX, "RotationZ", NULL},
	{NULL}
};

static void PyNNData_dealloc(CPyNNData* self)
{
	Py_XDECREF(self->Action);
	Py_XDECREF(self->MovementX);
	Py_XDECREF(self->MovementY);
	Py_XDECREF(self->RotationZ);
	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* PyNNData_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	CPyNNData* self;
	self = (CPyNNData*)type->tp_alloc(type, 0);
	if (self != NULL)
	{
		self->Action = PyLong_FromLong(0);
		if (self->Action == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->MovementX = PyFloat_FromDouble(0.0);
		if (self->MovementX == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->MovementY = PyFloat_FromDouble(0.0);
		if (self->MovementY == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->RotationZ = PyFloat_FromDouble(0.0);
		if (self->RotationZ == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
	}
	return (PyObject*)self;
}

static int PyNNData_init(CPyNNData* self, PyObject* args, PyObject* kwds)
{
	static char* kwlist[] = { (char*)"Action", (char*)"MovementX", (char*)"MovementY", (char*)"RotationZ", (char*)"RotationY", NULL};
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
		Py_XSETREF(self->RotationZ, Py_NewRef(rotationX));

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
	.tp_getset = PyNNData_getsetters,
	.tp_init = (initproc)PyNNData_init,
	.tp_new = PyNNData_new,
};
