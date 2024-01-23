#include "PythonCommands.h"

PyObject* PythonCommands::ImportModule(const char* moduleName)
{
    PyObject* module = PyUnicode_FromString(moduleName);
    return PyImport_Import(module);
}

PyObject* PythonCommands::CreateVarFromCClass(PyObject* module, const char* pyObjName)
{
    return PyObject_GetAttrString(module, pyObjName);
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

void PythonCommands::CreateClass(std::string className, std::string varName, std::string** values, int count)
{
    std::string command = varName;
    command.append(" = ");
    command.append(className);
    command.append("(");

    for (int i = 0; i < count; i++)
    {
        command.append(values[i]->data());
        if (i != count - 1)
            command.append(", ");
    }

    command.append(")");
    PyRun_SimpleString(command.c_str());
}
