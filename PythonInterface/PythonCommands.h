#pragma once
#include "include/Python.h"

class PythonCommands
{
public:
	static void ImportModule(const char* moduleName);
	static PyObject* CreateVarFromCClass(PyObject* pyObj, const char* varName, const char* className);
	static void SetVarFromClass(const char* classVarName, const char* varName, const char* value);
	static void SetVar(const char* varName, const char* value);
};

