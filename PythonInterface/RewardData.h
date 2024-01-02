#pragma once
#include "pylibs/Python.h"

typedef struct
{
	PyObject_HEAD;
	PyObject* Reward;

} PyReward;

class RewardData
{
public:
	int Reward;

public:
	//static PyObject* PyInit_PyRewardData();
	static PyObject* PyRewardData_getReward(PyReward* self, void* closure);
	static int PyRewardData_setReward(PyReward* self, PyObject* value, void* closure);
};

