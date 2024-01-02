#include "RewardData.h"


PyObject* RewardData::PyRewardData_getReward(PyReward* self, void* closure)
{
	return Py_NewRef(self->Reward);
}

int RewardData::PyRewardData_setReward(PyReward* self, PyObject* value, void* closure)
{
	// Check if value is valid

	Py_SETREF(self->Reward, Py_NewRef(value));
	// TODO (Major): Set the Value for C++ to use it
	return 0;
}

// GetSet dont need to be implemented by PyMethodDef
// For Costume Types add to .tp_getset
static PyGetSetDef PyRewardData_getsetters[] =
{
	{
		"Reward",
		(getter)RewardData::PyRewardData_getReward,
		(setter)RewardData::PyRewardData_setReward,
		"Variable Reward",
		NULL
	},
	{
		NULL // Sentinal
	}
};

static PyMethodDef PyRewardDataMethods[] =
{
	//{
	//	"nums", (PyCFunction)RewardData::PyRewardData_nums, METH_VARARGS,
	//	"Return the number of arguments received by the process."
	//},
	{
		NULL, NULL, 0, NULL
	}
};

static PyModuleDef PyRewardDataModule =
{
	PyModuleDef_HEAD_INIT, "PyRewardData", NULL, -1, PyRewardDataMethods,
	NULL, NULL, NULL, NULL
};

//PyObject* RewardData::PyInit_PyRewardData()
//{
//	return PyModule_Create(&PyRewardDataModule);
//}
