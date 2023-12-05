#include "PythonCommands.h"
#include <string>

void PythonCommands::ImportModule(const char* moduleName)
{
    std::string command = "import ";
    command.append(moduleName);
    PyRun_SimpleString(command.c_str());
}
