#define PY_SSIZE_T_CLEAN

#include "pylibs/Python.h"
#include "stddef.h"
#include "pylibs/structmember.h"


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

} CPySensData;

//static PyMemberDef PySensData_members[] =
//{
//	{"number", T_INT, offsetof(CPySensData, number), 0, "A Test Number"},
//	{NULL},
//};

#pragma region Member_get_set

static PyObject* PySensData_ClassCategory(CPySensData* self, PyObject* Py_UNUSED)
{
	if (self->ClassCategory == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "ClassCategory");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->ClassCategory);
}

static PyObject* PySensData_getClassCategory(CPySensData* self, void* closure)
{
	return Py_NewRef(self->ClassCategory);
}

static int PySensData_setClassCategory(CPySensData* self, PyObject* value, void* closure)
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

static PyObject* PySensData_TribeID(CPySensData* self, PyObject* Py_UNUSED)
{
	if (self->TribeID == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "TribeID");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->TribeID);
}

static PyObject* PySensData_getTribeID(CPySensData* self, void* closure)
{
	return Py_NewRef(self->TribeID);
}

static int PySensData_setTribeID(CPySensData* self, PyObject* value, void* closure)
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

static PyObject* PySensData_LivePoints(CPySensData* self, PyObject* Py_UNUSED)
{
	if (self->LivePoints == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "LivePoints");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->LivePoints);
}

static PyObject* PySensData_getLivePoints(CPySensData* self, void* closure)
{
	return Py_NewRef(self->LivePoints);
}

static int PySensData_setLivePoints(CPySensData* self, PyObject* value, void* closure)
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

static PyObject* PySensData_Stamina(CPySensData* self, PyObject* Py_UNUSED)
{
	if (self->Stamina == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "Stamina");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->Stamina);
}

static PyObject* PySensData_getStamina(CPySensData* self, void* closure)
{
	return Py_NewRef(self->Stamina);
}

static int PySensData_setStamina(CPySensData* self, PyObject* value, void* closure)
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

static PyObject* PySensData_Strength(CPySensData* self, PyObject* Py_UNUSED)
{
	if (self->Strength == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "Strength");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->Strength);
}

static PyObject* PySensData_getStrength(CPySensData* self, void* closure)
{
	return Py_NewRef(self->Strength);
}

static int PySensData_setStrength(CPySensData* self, PyObject* value, void* closure)
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

static PyObject* PySensData_Age(CPySensData* self, PyObject* Py_UNUSED)
{
	if (self->Age == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "Age");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->Age);
}

static PyObject* PySensData_getAge(CPySensData* self, void* closure)
{
	return Py_NewRef(self->Age);
}

static int PySensData_setAge(CPySensData* self, PyObject* value, void* closure)
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

static PyObject* PySensData_Height(CPySensData* self, PyObject* Py_UNUSED)
{
	if (self->Height == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "Height");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->Height);
}

static PyObject* PySensData_getHeight(CPySensData* self, void* closure)
{
	return Py_NewRef(self->Height);
}

static int PySensData_setHeight(CPySensData* self, PyObject* value, void* closure)
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

static PyObject* PySensData_Hunger(CPySensData* self, PyObject* Py_UNUSED)
{
	if (self->Hunger == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "Hunger");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->Hunger);
}

static PyObject* PySensData_getHunger(CPySensData* self, void* closure)
{
	return Py_NewRef(self->Hunger);
}

static int PySensData_setHunger(CPySensData* self, PyObject* value, void* closure)
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

static PyObject* PySensData_Thurst(CPySensData* self, PyObject* Py_UNUSED)
{
	if (self->Thurst == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "Thurst");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->Thurst);
}

static PyObject* PySensData_getThurst(CPySensData* self, void* closure)
{
	return Py_NewRef(self->Thurst);
}

static int PySensData_setThurst(CPySensData* self, PyObject* value, void* closure)
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

static PyObject* PySensData_PositionX(CPySensData* self, PyObject* Py_UNUSED)
{
	if (self->PositionX == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "PositionX");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->PositionX);
}

static PyObject* PySensData_getPositionX(CPySensData* self, void* closure)
{
	return Py_NewRef(self->PositionX);
}

static int PySensData_setPositionX(CPySensData* self, PyObject* value, void* closure)
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

static PyObject* PySensData_PositionY(CPySensData* self, PyObject* Py_UNUSED)
{
	if (self->PositionY == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "PositionY");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->PositionY);
}

static PyObject* PySensData_getPositionY(CPySensData* self, void* closure)
{
	return Py_NewRef(self->PositionY);
}

static int PySensData_setPositionY(CPySensData* self, PyObject* value, void* closure)
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

static PyObject* PySensData_PositionZ(CPySensData* self, PyObject* Py_UNUSED)
{
	if (self->PositionZ == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "PositionZ");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->PositionZ);
}

static PyObject* PySensData_getPositionZ(CPySensData* self, void* closure)
{
	return Py_NewRef(self->PositionZ);
}

static int PySensData_setPositionZ(CPySensData* self, PyObject* value, void* closure)
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

static PyObject* PySensData_Distance(CPySensData* self, PyObject* Py_UNUSED)
{
	if (self->Distance == NULL)
	{
		PyErr_SetString(PyExc_AttributeError, "Distance");
		return NULL;
	}

	return PyUnicode_FromFormat("%S", self->Distance);
}

static PyObject* PySensData_getDistance(CPySensData* self, void* closure)
{
	return Py_NewRef(self->PositionZ);
}

static int PySensData_setDistance(CPySensData* self, PyObject* value, void* closure)
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
	Py_SETREF(self->Distance, Py_NewRef(value));
	return 0;
}

#pragma endregion



static PyMethodDef PySensData_methods[] =
{
	{"ClassCategory", (PyCFunction)PySensData_ClassCategory, METH_NOARGS, "Return the ClassCategory"},
	{"TribeID", (PyCFunction)PySensData_TribeID, METH_NOARGS, "Return the TribeID"},
	{"LivePoints", (PyCFunction)PySensData_LivePoints, METH_NOARGS, "Return the LivePoints"},
	{"Stamina", (PyCFunction)PySensData_Stamina, METH_NOARGS, "Return the Stamina"},
	{"Strength", (PyCFunction)PySensData_Strength, METH_NOARGS, "Return the Strength"},
	{"Age", (PyCFunction)PySensData_Age, METH_NOARGS, "Return the Age"},
	{"Height", (PyCFunction)PySensData_Height, METH_NOARGS, "Return the Height"},
	{"Hunger", (PyCFunction)PySensData_Hunger, METH_NOARGS, "Return the Hunger"},
	{"Thurst", (PyCFunction)PySensData_Thurst, METH_NOARGS, "Return the Thurst"},
	{"PositionX", (PyCFunction)PySensData_PositionX, METH_NOARGS, "Return the PositionX"},
	{"PositionY", (PyCFunction)PySensData_PositionY, METH_NOARGS, "Return the PositionY"},
	{"PositionZ", (PyCFunction)PySensData_PositionZ, METH_NOARGS, "Return the PositionZ"},
	{"Distance", (PyCFunction)PySensData_Distance, METH_NOARGS, "Return the Distance"},
	{NULL}
};

static PyGetSetDef PySensData_getsetters[] =
{
	{"ClassCategory", (getter)PySensData_getClassCategory, (setter)PySensData_setClassCategory, "ClassCategory", NULL},
	{"TribeID", (getter)PySensData_getTribeID, (setter)PySensData_setTribeID, "TribeID", NULL},
	{"LivePoints", (getter)PySensData_getLivePoints, (setter)PySensData_setLivePoints, "LivePoints", NULL},
	{"Stamina", (getter)PySensData_getStamina, (setter)PySensData_setStamina, "Stamina", NULL},
	{"Strength", (getter)PySensData_getStrength, (setter)PySensData_setStrength, "Strength", NULL},
	{"Age", (getter)PySensData_getAge, (setter)PySensData_setAge, "Age", NULL},
	{"Height", (getter)PySensData_getHeight, (setter)PySensData_setHeight, "Height", NULL},
	{"Hunger", (getter)PySensData_getHunger, (setter)PySensData_setHunger, "Hunger", NULL},
	{"Thurst", (getter)PySensData_getThurst, (setter)PySensData_setThurst, "Thurst", NULL},
	{"PositionX", (getter)PySensData_getPositionX, (setter)PySensData_setPositionX, "PositionX", NULL},
	{"PositionY", (getter)PySensData_getPositionY, (setter)PySensData_setPositionY, "PositionY", NULL},
	{"PositionZ", (getter)PySensData_getPositionZ, (setter)PySensData_setPositionZ, "PositionZ", NULL},
	{"Distance", (getter)PySensData_getDistance, (setter)PySensData_setDistance, "Distance", NULL},
	{NULL}
};

static void PySensData_dealloc(CPySensData* self)
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
	Py_XDECREF(self->Distance);
	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* PySensData_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	CPySensData* self;
	self = (CPySensData*)type->tp_alloc(type, 0);
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
		self->Distance = PyUnicode_FromString("");
		if (self->Distance == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
	}
	return (PyObject*)self;
}

static int PySensData_init(CPySensData* self, PyObject* args, PyObject* kwds)
{
	static char* kwlist[] = { (char*)"ClassCategory", (char*)"TribeID", (char*)"LivePoints",
		(char*)"Stamina", (char*)"Strength", (char*)"Age", (char*)"Height", (char*)"Hunger",
		(char*)"Thurst", (char*)"PositionX", (char*)"PositionY", (char*)"PositionZ", (char*)"Distance", NULL };
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
	PyObject* distance = NULL;

	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|00i", kwlist, 
		&classCategory, &tribeID, &livePoints, &stamina, &strength, &age, 
		&height, &hunger, &thurst, &positionX, &positionY, &positionZ, &distance))
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
	if (distance)
		Py_XSETREF(self->Distance, Py_NewRef(distance));

	return 0;
}

static PyTypeObject PySensDataObject =
{
	.ob_base = PyVarObject_HEAD_INIT(NULL, 0)
	.tp_name = "pyModule.CPySensData",
	.tp_basicsize = sizeof(CPySensData),
	.tp_itemsize = 0,
	.tp_dealloc = (destructor)PySensData_dealloc,
	.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	.tp_doc = PyDoc_STR("Sensor"),
	.tp_methods = PySensData_methods,
	//.tp_members = PySensData_members,
	.tp_getset = PySensData_getsetters,
	.tp_init = (initproc)PySensData_init,
	.tp_new = PySensData_new,
};
