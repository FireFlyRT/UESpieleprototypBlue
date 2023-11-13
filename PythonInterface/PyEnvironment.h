#pragma once
#include "pylibs/Python.h"

struct PyEnvironment
{
public:
	PyObject_HEAD;

	int* action_space = new int[1, 128, 128];
	int observation_space = 8;
};
