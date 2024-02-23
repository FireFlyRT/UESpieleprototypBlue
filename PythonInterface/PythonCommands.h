#pragma once
#include "include/Python.h"
#include "string"

class PythonCommands
{
public:
	static PyObject* ImportModule(const char* moduleName);
	static PyObject* CreateVarFromCClass(PyObject* module, const char* pyObjName);
	static void SetVarFromClass(const char* classVarName, const char* varName, const char* value);
	static void SetVar(const char* varName, const char* value);
	static void CreateClass(std::string className, std::string varName, std::string** values = nullptr, int count = 0);
};

