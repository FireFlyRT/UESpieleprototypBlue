#pragma once
#include "pylibs/Python.h"

class PyEnvironment : public PyObject
{
public:
	PyObject_HEAD;
	PyEnvironment();
	const char* tp_name;
};


