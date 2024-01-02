#pragma once
#include "pylibs/Python.h"

class PythonCommands
{
public:
	static void ImportModule(const char* moduleName);
	static void CreateVarFromCClass(const char* varName, const char* className);
	static void SetVarFromClass(const char* classVarName, const char* varName, const char* value);
	static void SetVar(const char* varName, const char* value);
};

