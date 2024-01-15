#pragma once
#include "include/Python.h"

class PythonCommands
{
public:
	static PyObject* ImportModule(const char* moduleName);
	static PyObject* CreateVarFromCClass(PyObject* module, const char* pyObjName);
	static void SetVarFromClass(const char* classVarName, const char* varName, const char* value);
	static void SetVar(const char* varName, const char* value);
};

