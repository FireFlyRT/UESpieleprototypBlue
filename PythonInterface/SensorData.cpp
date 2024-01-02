#include "SensorData.h"

PyObject* SensorData::PySensorData_getClassCategory(PySensor* self, void* closure)
{
	return Py_NewRef(self->ClassCategory);
}

int SensorData::PySensorData_setClassCategory(PySensor* self, PyObject* value, void* closure)
{
	// Check if value is valid

	Py_SETREF(self->ClassCategory, Py_NewRef(value));
	// TODO (Major): Set the Value for C++ to use it
	return 0;
}

PyObject* SensorData::PySensorData_getTribeID(PySensor* self, void* closure)
{
	return Py_NewRef(self->TribeID);
}

int SensorData::PySensorData_setTribeID(PySensor* self, PyObject* value, void* closure)
{
	Py_SETREF(self->TribeID, Py_NewRef(value));
	return 0;
}

PyObject* SensorData::PySensorData_getLivePoints(PySensor* self, void* closure)
{
	return Py_NewRef(self->LivePoints);
}

int SensorData::PySensorData_setLivePoints(PySensor* self, PyObject* value, void* closure)
{
	Py_SETREF(self->LivePoints, Py_NewRef(value));
	return 0;
}

PyObject* SensorData::PySensorData_getStamina(PySensor* self, void* closure)
{
	return Py_NewRef(self->Stamina);
}

int SensorData::PySensorData_setStamina(PySensor* self, PyObject* value, void* closure)
{
	Py_SETREF(self->Stamina, Py_NewRef(value));
	return 0;
}

PyObject* SensorData::PySensorData_getStrength(PySensor* self, void* closure)
{
	return Py_NewRef(self->Strength);
}

int SensorData::PySensorData_setStrength(PySensor* self, PyObject* value, void* closure)
{
	Py_SETREF(self->Strength, Py_NewRef(value));
	return 0;
}

PyObject* SensorData::PySensorData_getAge(PySensor* self, void* closure)
{
	return Py_NewRef(self->Age);
}

int SensorData::PySensorData_setAge(PySensor* self, PyObject* value, void* closure)
{
	Py_SETREF(self->Age, Py_NewRef(value));
	return 0;
}

PyObject* SensorData::PySensorData_getHeight(PySensor* self, void* closure)
{
	return Py_NewRef(self->Height);
}

int SensorData::PySensorData_setHeight(PySensor* self, PyObject* value, void* closure)
{
	Py_SETREF(self->Height, Py_NewRef(value));
	return 0;
}

PyObject* SensorData::PySensorData_getHunger(PySensor* self, void* closure)
{
	return Py_NewRef(self->Hunger);
}

int SensorData::PySensorData_setHunger(PySensor* self, PyObject* value, void* closure)
{
	Py_SETREF(self->Hunger, Py_NewRef(value));
	return 0;
}

PyObject* SensorData::PySensorData_getThurst(PySensor* self, void* closure)
{
	return Py_NewRef(self->Thurst);
}

int SensorData::PySensorData_setThurst(PySensor* self, PyObject* value, void* closure)
{
	Py_SETREF(self->Thurst, Py_NewRef(value));
	return 0;
}

PyObject* SensorData::PySensorData_getPositionX(PySensor* self, void* closure)
{
	return Py_NewRef(self->PositionX);
}

int SensorData::PySensorData_setPositionX(PySensor* self, PyObject* value, void* closure)
{
	Py_SETREF(self->PositionX, Py_NewRef(value));
	return 0;
}

PyObject* SensorData::PySensorData_getPositionY(PySensor* self, void* closure)
{
	return Py_NewRef(self->PositionY);
}

int SensorData::PySensorData_setPositionY(PySensor* self, PyObject* value, void* closure)
{
	Py_SETREF(self->PositionY, Py_NewRef(value));
	return 0;
}

PyObject* SensorData::PySensorData_getPositionZ(PySensor* self, void* closure)
{
	return Py_NewRef(self->PositionZ);
}

int SensorData::PySensorData_setPositionZ(PySensor* self, PyObject* value, void* closure)
{
	Py_SETREF(self->PositionZ, Py_NewRef(value));
	return 0;
}

PyObject* SensorData::PySensorData_getDistance(PySensor* self, void* closure)
{
	return Py_NewRef(self->Distance);
}

int SensorData::PySensorData_setDistance(PySensor* self, PyObject* value, void* closure)
{
	Py_SETREF(self->Distance, Py_NewRef(value));
	return 0;
}

// GetSet dont need to be implemented by PyMethodDef
// For Costume Types add to .tp_getset
static PyGetSetDef PySensorData_getsetters[] =
{
	{
		"Reward",
		(getter)SensorData::PySensorData_getClassCategory,
		(setter)SensorData::PySensorData_setClassCategory,
		"Variable Reward",
		NULL
	},
	{
		"TribeID",
		(getter)SensorData::PySensorData_getTribeID,
		(setter)SensorData::PySensorData_setTribeID,
		"Variable TribeID",
		NULL
	},
	{
		"LivePoints",
		(getter)SensorData::PySensorData_getLivePoints,
		(setter)SensorData::PySensorData_setLivePoints,
		"Variable LivePoints",
		NULL
	},
	{
		"Stamina",
		(getter)SensorData::PySensorData_getStamina,
		(setter)SensorData::PySensorData_setStamina,
		"Variable Stamina",
		NULL
	},
	{
		"Strength",
		(getter)SensorData::PySensorData_getStrength,
		(setter)SensorData::PySensorData_setStrength,
		"Variable Strength",
		NULL
	},
	{
		"Age",
		(getter)SensorData::PySensorData_getAge,
		(setter)SensorData::PySensorData_setAge,
		"Variable Age",
		NULL
	},
	{
		"Height",
		(getter)SensorData::PySensorData_getHeight,
		(setter)SensorData::PySensorData_setHeight,
		"Variable Height",
		NULL
	},
	{
		"Hunger",
		(getter)SensorData::PySensorData_getHunger,
		(setter)SensorData::PySensorData_setHunger,
		"Variable Hunger",
		NULL
	},
	{
		"Thurst",
		(getter)SensorData::PySensorData_getThurst,
		(setter)SensorData::PySensorData_setThurst,
		"Variable Thurst",
		NULL
	},
	{
		"PositionX",
		(getter)SensorData::PySensorData_getPositionX,
		(setter)SensorData::PySensorData_setPositionX,
		"Variable PositionX",
		NULL
	},
	{
		"PositionY",
		(getter)SensorData::PySensorData_getPositionY,
		(setter)SensorData::PySensorData_setPositionY,
		"Variable PositionY",
		NULL
	},
	{
		"PositionZ",
		(getter)SensorData::PySensorData_getPositionZ,
		(setter)SensorData::PySensorData_setPositionZ,
		"Variable PositionZ",
		NULL
	},
	{
		"Distance",
		(getter)SensorData::PySensorData_getDistance,
		(setter)SensorData::PySensorData_setDistance,
		"Variable Distance",
		NULL
	},
	{
		NULL // Sentinal
	}
};

static PyMethodDef PySensorDataMethods[] =
{
	//{
	//	"nums", (PyCFunction)SensorData::PySensorData_nums, METH_VARARGS,
	//	"Return the number of arguments received by the process."
	//},
	{
		NULL, NULL, 0, NULL
	}
};

static PyModuleDef PySensorDataModule =
{
	PyModuleDef_HEAD_INIT, "PySensorData", NULL, -1, PySensorDataMethods,
	NULL, NULL, NULL, NULL
};
//
//PyObject* SensorData::PyInit_PySensorData()
//{
//	return PyModule_Create(&PySensorDataModule);
//}