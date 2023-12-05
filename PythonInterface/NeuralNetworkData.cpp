#include "NeuralNetworkData.h"

PyObject* NeuralNetworkData::PyNeuralNetworkData_getAction(PyNN* self, void* closure)
{
	return Py_NewRef(self->Action);
}

int NeuralNetworkData::PyNeuralNetworkData_setAction(PyNN* self, PyObject* value, void* closure)
{
	Py_SETREF(self->Action, Py_NewRef(value));
	return 0;
}

PyObject* NeuralNetworkData::PyNeuralNetworkData_getMovementX(PyNN* self, void* closure)
{
	return Py_NewRef(self->MovementX);
}

int NeuralNetworkData::PyNeuralNetworkData_setMovementX(PyNN* self, PyObject* value, void* closure)
{
	Py_SETREF(self->MovementX, Py_NewRef(value));
	return 0;
}

PyObject* NeuralNetworkData::PyNeuralNetworkData_getMovementY(PyNN* self, void* closure)
{
	return Py_NewRef(self->MovementY);
}

int NeuralNetworkData::PyNeuralNetworkData_setMovementY(PyNN* self, PyObject* value, void* closure)
{
	Py_SETREF(self->MovementY, Py_NewRef(value));
	return 0;
}

PyObject* NeuralNetworkData::PyNeuralNetworkData_getRotationX(PyNN* self, void* closure)
{
	return Py_NewRef(self->RotationX);
}

int NeuralNetworkData::PyNeuralNetworkData_setRotationX(PyNN* self, PyObject* value, void* closure)
{
	Py_SETREF(self->RotationX, Py_NewRef(value));
	return 0;
}

PyObject* NeuralNetworkData::PyNeuralNetworkData_getRotationY(PyNN* self, void* closure)
{
	return Py_NewRef(self->RotationY);
}

int NeuralNetworkData::PyNeuralNetworkData_setRotationY(PyNN* self, PyObject* value, void* closure)
{
	Py_SETREF(self->RotationY, Py_NewRef(value));
	return 0;
}

// GetSet dont need to be implemented by PyMethodDef
// For Costume Types add to .tp_getset
static PyGetSetDef PyNeuralNetworkData_getsetters[] =
{
	{
		"Action",
		(getter)NeuralNetworkData::PyNeuralNetworkData_getAction,
		(setter)NeuralNetworkData::PyNeuralNetworkData_setAction,
		"Variable Action",
		NULL
	},
	{
		"MovementX",
		(getter)NeuralNetworkData::PyNeuralNetworkData_getMovementX,
		(setter)NeuralNetworkData::PyNeuralNetworkData_setMovementX,
		"Variable MovementX",
		NULL
	},
	{
		"MovementY",
		(getter)NeuralNetworkData::PyNeuralNetworkData_getMovementY,
		(setter)NeuralNetworkData::PyNeuralNetworkData_setMovementY,
		"Variable MovementY",
		NULL
	},
	{
		"RotationX",
		(getter)NeuralNetworkData::PyNeuralNetworkData_getRotationX,
		(setter)NeuralNetworkData::PyNeuralNetworkData_setRotationX,
		"Variable RotationX",
		NULL
	},
	{
		"RotationY",
		(getter)NeuralNetworkData::PyNeuralNetworkData_getRotationY,
		(setter)NeuralNetworkData::PyNeuralNetworkData_setRotationY,
		"Variable RotationY",
		NULL
	},
	{
		NULL // Sentinal
	}
};

static PyMethodDef PyNeuralNetworkDataMethods[] =
{
	//{
	//	"nums", (PyCFunction)NeuralNetworkData::PyNeuralNetworkData_nums, METH_VARARGS,
	//	"Return the number of arguments received by the process."
	//},
	{
		NULL, NULL, 0, NULL
	}
};

static PyModuleDef PyNeuralNetworkDataModule =
{
	PyModuleDef_HEAD_INIT, "PyNeuralNetworkData", NULL, -1, PyNeuralNetworkDataMethods,
	NULL, NULL, NULL, NULL
};

PyObject* NeuralNetworkData::PyInit_PyNeuralNetworkData()
{
	return PyModule_Create(&PyNeuralNetworkDataModule);
}
