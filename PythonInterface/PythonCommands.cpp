#include "PythonCommands.h"
#include <string>
#include "CPyEnvironment.c"

void PythonCommands::ImportModule(const char* moduleName)
{
    std::string command = "import ";
    command.append(moduleName);
    PyRun_SimpleString(command.c_str());
}

PyObject* PythonCommands::CreateVarFromCClass(PyObject* pyObj, const char* varName, const char* className)
{
    std::string command = varName;
    command.append(" = pyModule.");
    command.append(className);
    command.append("()");
    PyRun_SimpleString(command.c_str());
    return PyObject_Init(pyObj, &PyEnvObject);
}

void PythonCommands::SetVarFromClass(const char* classVarName, const char* varName, const char* value)
{
    std::string command = classVarName;
    command.append(".");
    command.append(varName);
    command.append(" = ");
    command.append(value);
    PyRun_SimpleString(command.c_str());
}

void PythonCommands::SetVar(const char* varName, const char* value)
{
    std::string command = varName;
    command.append(" = ");
    command.append(value);
    PyRun_SimpleString(command.c_str());
}
