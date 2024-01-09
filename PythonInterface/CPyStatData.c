#pragma once
#define PY_SSIZE_T_CLEAN

#include "include/Python.h"
#include "stddef.h"
#include "include/structmember.h"


typedef struct
{
	PyObject_HEAD

	PyObject* ClassCategory;
	PyObject* TribeID;
	PyObject* LivePoints;
	PyObject* Stamina;
	PyObject* Strength;
	PyObject* Age;
	PyObject* Height;
	PyObject* Hunger;
	PyObject* Thurst;
	PyObject* PositionX;
	PyObject* PositionY;
	PyObject* PositionZ;
	PyObject* Distance;

} CPyStatData;

//static PyMemberDef PyStatData_members[] =
//{
//	{"number", T_INT, offsetof(CPyStatData, number), 0, "A Test Number"},
//	{NULL},
//};

#pragma region Member_get_set

static PyObject* PyStatData_ClassCategory(CPyStatData* self, PyObject* Py_UNUSED)
{
	if (self->ClassCategory == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "ClassCategory");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->ClassCategory);
}

static PyObject* PyStatData_getClassCategory(CPyStatData* self, void* closure)
{
	return Py_NewRef(self->ClassCategory);
}

static int PyStatData_setClassCategory(CPyStatData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->ClassCategory, Py_NewRef(value));
	return 0;
}

static PyObject* PyStatData_TribeID(CPyStatData* self, PyObject* Py_UNUSED)
{
	if (self->TribeID == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "TribeID");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->TribeID);
}

static PyObject* PyStatData_getTribeID(CPyStatData* self, void* closure)
{
	return Py_NewRef(self->TribeID);
}

static int PyStatData_setTribeID(CPyStatData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->TribeID, Py_NewRef(value));
	return 0;
}

static PyObject* PyStatData_LivePoints(CPyStatData* self, PyObject* Py_UNUSED)
{
	if (self->LivePoints == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "LivePoints");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->LivePoints);
}

static PyObject* PyStatData_getLivePoints(CPyStatData* self, void* closure)
{
	return Py_NewRef(self->LivePoints);
}

static int PyStatData_setLivePoints(CPyStatData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->LivePoints, Py_NewRef(value));
	return 0;
}

static PyObject* PyStatData_Stamina(CPyStatData* self, PyObject* Py_UNUSED)
{
	if (self->Stamina == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "Stamina");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->Stamina);
}

static PyObject* PyStatData_getStamina(CPyStatData* self, void* closure)
{
	return Py_NewRef(self->Stamina);
}

static int PyStatData_setStamina(CPyStatData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->Stamina, Py_NewRef(value));
	return 0;
}

static PyObject* PyStatData_Strength(CPyStatData* self, PyObject* Py_UNUSED)
{
	if (self->Strength == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "Strength");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->Strength);
}

static PyObject* PyStatData_getStrength(CPyStatData* self, void* closure)
{
	return Py_NewRef(self->Strength);
}

static int PyStatData_setStrength(CPyStatData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->Strength, Py_NewRef(value));
	return 0;
}

static PyObject* PyStatData_Age(CPyStatData* self, PyObject* Py_UNUSED)
{
	if (self->Age == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "Age");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->Age);
}

static PyObject* PyStatData_getAge(CPyStatData* self, void* closure)
{
	return Py_NewRef(self->Age);
}

static int PyStatData_setAge(CPyStatData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->Age, Py_NewRef(value));
	return 0;
}

static PyObject* PyStatData_Height(CPyStatData* self, PyObject* Py_UNUSED)
{
	if (self->Height == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "Height");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->Height);
}

static PyObject* PyStatData_getHeight(CPyStatData* self, void* closure)
{
	return Py_NewRef(self->Height);
}

static int PyStatData_setHeight(CPyStatData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->Height, Py_NewRef(value));
	return 0;
}

static PyObject* PyStatData_Hunger(CPyStatData* self, PyObject* Py_UNUSED)
{
	if (self->Hunger == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "Hunger");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->Hunger);
}

static PyObject* PyStatData_getHunger(CPyStatData* self, void* closure)
{
	return Py_NewRef(self->Hunger);
}

static int PyStatData_setHunger(CPyStatData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->Hunger, Py_NewRef(value));
	return 0;
}

static PyObject* PyStatData_Thurst(CPyStatData* self, PyObject* Py_UNUSED)
{
	if (self->Thurst == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "Thurst");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->Thurst);
}

static PyObject* PyStatData_getThurst(CPyStatData* self, void* closure)
{
	return Py_NewRef(self->Thurst);
}

static int PyStatData_setThurst(CPyStatData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->Thurst, Py_NewRef(value));
	return 0;
}

static PyObject* PyStatData_PositionX(CPyStatData* self, PyObject* Py_UNUSED)
{
	if (self->PositionX == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "PositionX");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->PositionX);
}

static PyObject* PyStatData_getPositionX(CPyStatData* self, void* closure)
{
	return Py_NewRef(self->PositionX);
}

static int PyStatData_setPositionX(CPyStatData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->PositionX, Py_NewRef(value));
	return 0;
}

static PyObject* PyStatData_PositionY(CPyStatData* self, PyObject* Py_UNUSED)
{
	if (self->PositionY == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "PositionY");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->PositionY);
}

static PyObject* PyStatData_getPositionY(CPyStatData* self, void* closure)
{
	return Py_NewRef(self->PositionY);
}

static int PyStatData_setPositionY(CPyStatData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->PositionY, Py_NewRef(value));
	return 0;
}

static PyObject* PyStatData_PositionZ(CPyStatData* self, PyObject* Py_UNUSED)
{
	if (self->PositionZ == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "PositionZ");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->PositionZ);
}

static PyObject* PyStatData_getPositionZ(CPyStatData* self, void* closure)
{
	return Py_NewRef(self->PositionZ);
}

static int PyStatData_setPositionZ(CPyStatData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->PositionZ, Py_NewRef(value));
	return 0;
}

#pragma endregion



static PyMethodDef PyStatData_methods[] =
{
	{"ClassCategory", (PyCFunction)PyStatData_ClassCategory, METH_NOARGS, "Return the ClassCategory"},
	{"TribeID", (PyCFunction)PyStatData_TribeID, METH_NOARGS, "Return the TribeID"},
	{"LivePoints", (PyCFunction)PyStatData_LivePoints, METH_NOARGS, "Return the LivePoints"},
	{"Stamina", (PyCFunction)PyStatData_Stamina, METH_NOARGS, "Return the Stamina"},
	{"Strength", (PyCFunction)PyStatData_Strength, METH_NOARGS, "Return the Strength"},
	{"Age", (PyCFunction)PyStatData_Age, METH_NOARGS, "Return the Age"},
	{"Height", (PyCFunction)PyStatData_Height, METH_NOARGS, "Return the Height"},
	{"Hunger", (PyCFunction)PyStatData_Hunger, METH_NOARGS, "Return the Hunger"},
	{"Thurst", (PyCFunction)PyStatData_Thurst, METH_NOARGS, "Return the Thurst"},
	{"PositionX", (PyCFunction)PyStatData_PositionX, METH_NOARGS, "Return the PositionX"},
	{"PositionY", (PyCFunction)PyStatData_PositionY, METH_NOARGS, "Return the PositionY"},
	{"PositionZ", (PyCFunction)PyStatData_PositionZ, METH_NOARGS, "Return the PositionZ"},
	{NULL}
};

static PyGetSetDef PyStatData_getsetters[] =
{
	{"ClassCategory", (getter)PyStatData_getClassCategory, (setter)PyStatData_setClassCategory, "ClassCategory", NULL},
	{"TribeID", (getter)PyStatData_getTribeID, (setter)PyStatData_setTribeID, "TribeID", NULL},
	{"LivePoints", (getter)PyStatData_getLivePoints, (setter)PyStatData_setLivePoints, "LivePoints", NULL},
	{"Stamina", (getter)PyStatData_getStamina, (setter)PyStatData_setStamina, "Stamina", NULL},
	{"Strength", (getter)PyStatData_getStrength, (setter)PyStatData_setStrength, "Strength", NULL},
	{"Age", (getter)PyStatData_getAge, (setter)PyStatData_setAge, "Age", NULL},
	{"Height", (getter)PyStatData_getHeight, (setter)PyStatData_setHeight, "Height", NULL},
	{"Hunger", (getter)PyStatData_getHunger, (setter)PyStatData_setHunger, "Hunger", NULL},
	{"Thurst", (getter)PyStatData_getThurst, (setter)PyStatData_setThurst, "Thurst", NULL},
	{"PositionX", (getter)PyStatData_getPositionX, (setter)PyStatData_setPositionX, "PositionX", NULL},
	{"PositionY", (getter)PyStatData_getPositionY, (setter)PyStatData_setPositionY, "PositionY", NULL},
	{"PositionZ", (getter)PyStatData_getPositionZ, (setter)PyStatData_setPositionZ, "PositionZ", NULL},
	{NULL}
};

static void PyStatData_dealloc(CPyStatData* self)
{
	Py_XDECREF(self->ClassCategory);
	Py_XDECREF(self->TribeID);
	Py_XDECREF(self->LivePoints);
	Py_XDECREF(self->Stamina);
	Py_XDECREF(self->Strength);
	Py_XDECREF(self->Age);
	Py_XDECREF(self->Height);
	Py_XDECREF(self->Hunger);
	Py_XDECREF(self->Thurst);
	Py_XDECREF(self->PositionX);
	Py_XDECREF(self->PositionY);
	Py_XDECREF(self->PositionZ);
	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* PyStatData_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	CPyStatData* self;
	self = (CPyStatData*)type->tp_alloc(type, 0);
	if (self != NULL)
	{
		self->ClassCategory = PyUnicode_FromString("");
		if (self->ClassCategory == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->TribeID = PyUnicode_FromString("");
		if (self->TribeID == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->LivePoints = PyUnicode_FromString("");
		if (self->LivePoints == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->Stamina = PyUnicode_FromString("");
		if (self->Stamina == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->Strength = PyUnicode_FromString("");
		if (self->Strength == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->Age = PyUnicode_FromString("");
		if (self->Age == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->Height = PyUnicode_FromString("");
		if (self->Height == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->Hunger = PyUnicode_FromString("");
		if (self->Hunger == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->Thurst = PyUnicode_FromString("");
		if (self->Thurst == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->PositionX = PyUnicode_FromString("");
		if (self->PositionX == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->PositionY = PyUnicode_FromString("");
		if (self->PositionY == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
		self->PositionZ = PyUnicode_FromString("");
		if (self->PositionZ == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
	}
	return (PyObject*)self;
}

static int PyStatData_init(CPyStatData* self, PyObject* args, PyObject* kwds)
{
	static char* kwlist[] = { (char*)"ClassCategory", (char*)"TribeID", (char*)"LivePoints", 
		(char*)"Stamina", (char*)"Strength", (char*)"Age", (char*)"Height", (char*)"Hunger", 
		(char*)"Thurst", (char*)"PositionX", (char*)"PositionY", (char*)"PositionZ", NULL };
	PyObject* classCategory = NULL;
	PyObject* tribeID = NULL;
	PyObject* livePoints = NULL;
	PyObject* stamina = NULL;
	PyObject* strength = NULL;
	PyObject* age = NULL;
	PyObject* height = NULL;
	PyObject* hunger = NULL;
	PyObject* thurst = NULL;
	PyObject* positionX = NULL;
	PyObject* positionY = NULL;
	PyObject* positionZ = NULL;

	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|00i", kwlist,
		&classCategory, &tribeID, &livePoints, &stamina, &strength, &age,
		&height, &hunger, &thurst, &positionX, &positionY, &positionZ))
		return -1;

	if (classCategory)
		Py_XSETREF(self->ClassCategory, Py_NewRef(classCategory));
	if (tribeID)
		Py_XSETREF(self->TribeID, Py_NewRef(tribeID));
	if (livePoints)
		Py_XSETREF(self->LivePoints, Py_NewRef(livePoints));
	if (stamina)
		Py_XSETREF(self->Stamina, Py_NewRef(stamina));
	if (strength)
		Py_XSETREF(self->Strength, Py_NewRef(strength));
	if (age)
		Py_XSETREF(self->Age, Py_NewRef(age));
	if (height)
		Py_XSETREF(self->Height, Py_NewRef(height));
	if (hunger)
		Py_XSETREF(self->Hunger, Py_NewRef(hunger));
	if (thurst)
		Py_XSETREF(self->Thurst, Py_NewRef(thurst));
	if (positionX)
		Py_XSETREF(self->PositionX, Py_NewRef(positionX));
	if (positionY)
		Py_XSETREF(self->PositionY, Py_NewRef(positionY));
	if (positionZ)
		Py_XSETREF(self->PositionZ, Py_NewRef(positionZ));

	return 0;
}

static PyTypeObject PyStatDataObject =
{
	.ob_base = PyVarObject_HEAD_INIT(NULL, 0)
	.tp_name = "pyModule.CPyStatData",
	.tp_basicsize = sizeof(CPyStatData),
	.tp_itemsize = 0,
	.tp_dealloc = (destructor)PyStatData_dealloc,
	.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	.tp_doc = PyDoc_STR("Stats"),
	.tp_methods = PyStatData_methods,
	//.tp_members = PyStatData_members,
	.tp_getset = PyStatData_getsetters,
	.tp_init = (initproc)PyStatData_init,
	.tp_new = PyStatData_new,
};
