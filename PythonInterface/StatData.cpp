#include "StatData.h"

PyObject* StatData::PyStatData_getClassCategory(PyStat* self, void* closure)
{
	return Py_NewRef(self->ClassCategory);
}

int StatData::PyStatData_setClassCategory(PyStat* self, PyObject* value, void* closure)
{
	// Check if value is valid

	Py_SETREF(self->ClassCategory, Py_NewRef(value));
	// TODO (Major): Set the Value for C++ to use it
	return 0;
}

PyObject* StatData::PyStatData_getTribeID(PyStat* self, void* closure)
{
	return Py_NewRef(self->TribeID);
}

int StatData::PyStatData_setTribeID(PyStat* self, PyObject* value, void* closure)
{
	Py_SETREF(self->TribeID, Py_NewRef(value));
	return 0;
}

PyObject* StatData::PyStatData_getLivePoints(PyStat* self, void* closure)
{
	return Py_NewRef(self->LivePoints);
}

int StatData::PyStatData_setLivePoints(PyStat* self, PyObject* value, void* closure)
{
	Py_SETREF(self->LivePoints, Py_NewRef(value));
	return 0;
}

PyObject* StatData::PyStatData_getStamina(PyStat* self, void* closure)
{
	return Py_NewRef(self->Stamina);
}

int StatData::PyStatData_setStamina(PyStat* self, PyObject* value, void* closure)
{
	Py_SETREF(self->Stamina, Py_NewRef(value));
	return 0;
}

PyObject* StatData::PyStatData_getStrength(PyStat* self, void* closure)
{
	return Py_NewRef(self->Strength);
}

int StatData::PyStatData_setStrength(PyStat* self, PyObject* value, void* closure)
{
	Py_SETREF(self->Strength, Py_NewRef(value));
	return 0;
}

PyObject* StatData::PyStatData_getAge(PyStat* self, void* closure)
{
	return Py_NewRef(self->Age);
}

int StatData::PyStatData_setAge(PyStat* self, PyObject* value, void* closure)
{
	Py_SETREF(self->Age, Py_NewRef(value));
	return 0;
}

PyObject* StatData::PyStatData_getHeight(PyStat* self, void* closure)
{
	return Py_NewRef(self->Height);
}

int StatData::PyStatData_setHeight(PyStat* self, PyObject* value, void* closure)
{
	Py_SETREF(self->Height, Py_NewRef(value));
	return 0;
}

PyObject* StatData::PyStatData_getHunger(PyStat* self, void* closure)
{
	return Py_NewRef(self->Hunger);
}

int StatData::PyStatData_setHunger(PyStat* self, PyObject* value, void* closure)
{
	Py_SETREF(self->Hunger, Py_NewRef(value));
	return 0;
}

PyObject* StatData::PyStatData_getThurst(PyStat* self, void* closure)
{
	return Py_NewRef(self->Thurst);
}

int StatData::PyStatData_setThurst(PyStat* self, PyObject* value, void* closure)
{
	Py_SETREF(self->Thurst, Py_NewRef(value));
	return 0;
}

PyObject* StatData::PyStatData_getPositionX(PyStat* self, void* closure)
{
	return Py_NewRef(self->PositionX);
}

int StatData::PyStatData_setPositionX(PyStat* self, PyObject* value, void* closure)
{
	Py_SETREF(self->PositionX, Py_NewRef(value));
	return 0;
}

PyObject* StatData::PyStatData_getPositionY(PyStat* self, void* closure)
{
	return Py_NewRef(self->PositionY);
}

int StatData::PyStatData_setPositionY(PyStat* self, PyObject* value, void* closure)
{
	Py_SETREF(self->PositionY, Py_NewRef(value));
	return 0;
}

PyObject* StatData::PyStatData_getPositionZ(PyStat* self, void* closure)
{
	return Py_NewRef(self->PositionZ);
}

int StatData::PyStatData_setPositionZ(PyStat* self, PyObject* value, void* closure)
{
	Py_SETREF(self->PositionZ, Py_NewRef(value));
	return 0;
}

// GetSet dont need to be implemented by PyMethodDef
// For Costume Types add to .tp_getset
static PyGetSetDef PyStatData_getsetters[] =
{
	{
		"Reward",
		(getter)StatData::PyStatData_getClassCategory,
		(setter)StatData::PyStatData_setClassCategory,
		"Variable Reward",
		NULL
	},
	{
		"TribeID",
		(getter)StatData::PyStatData_getTribeID,
		(setter)StatData::PyStatData_setTribeID,
		"Variable TribeID",
		NULL
	},
	{
		"LivePoints",
		(getter)StatData::PyStatData_getLivePoints,
		(setter)StatData::PyStatData_setLivePoints,
		"Variable LivePoints",
		NULL
	},
	{
		"Stamina",
		(getter)StatData::PyStatData_getStamina,
		(setter)StatData::PyStatData_setStamina,
		"Variable Stamina",
		NULL
	},
	{
		"Strength",
		(getter)StatData::PyStatData_getStrength,
		(setter)StatData::PyStatData_setStrength,
		"Variable Strength",
		NULL
	},
	{
		"Age",
		(getter)StatData::PyStatData_getAge,
		(setter)StatData::PyStatData_setAge,
		"Variable Age",
		NULL
	},
	{
		"Height",
		(getter)StatData::PyStatData_getHeight,
		(setter)StatData::PyStatData_setHeight,
		"Variable Height",
		NULL
	},
	{
		"Hunger",
		(getter)StatData::PyStatData_getHunger,
		(setter)StatData::PyStatData_setHunger,
		"Variable Hunger",
		NULL
	},
	{
		"Thurst",
		(getter)StatData::PyStatData_getThurst,
		(setter)StatData::PyStatData_setThurst,
		"Variable Thurst",
		NULL
	},
	{
		"PositionX",
		(getter)StatData::PyStatData_getPositionX,
		(setter)StatData::PyStatData_setPositionX,
		"Variable PositionX",
		NULL
	},
	{
		"PositionY",
		(getter)StatData::PyStatData_getPositionY,
		(setter)StatData::PyStatData_setPositionY,
		"Variable PositionY",
		NULL
	},
	{
		"PositionZ",
		(getter)StatData::PyStatData_getPositionZ,
		(setter)StatData::PyStatData_setPositionZ,
		"Variable PositionZ",
		NULL
	},
	{
		NULL // Sentinal
	}
};

static PyMethodDef PyStatDataMethods[] =
{
	//{
	//	"nums", (PyCFunction)StatData::PyStatData_nums, METH_VARARGS,
	//	"Return the number of arguments received by the process."
	//},
	{
		NULL, NULL, 0, NULL
	}
};

static PyModuleDef PyStatDataModule =
{
	PyModuleDef_HEAD_INIT, "PyStatData", NULL, -1, PyStatDataMethods,
	NULL, NULL, NULL, NULL
};

//PyObject* StatData::PyInit_PyStatData()
//{
//	return PyModule_Create(&PyStatDataModule);
//}
