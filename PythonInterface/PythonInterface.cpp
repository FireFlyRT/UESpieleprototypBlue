// Exe is in ..\UESpieleprototypBlue\x64\Release\PythonInterface.exe
#define PY_SSIZE_T_CLEAN

#include <iostream>
#include <stdio.h>
#include "pylibs/Python.h"

int main(int argc, char* argv[])
{
    std::cout << "Initialize Python Interface!\n";

    Py_Initialize();
    std::cout << "Initialized: " << Py_IsInitialized() << std::endl;
    
    PyRun_SimpleString("print('From Python: Hello World!')");

    FILE* nnFile;
    char path[255] = "";
    _fullpath(path, argv[0], sizeof(path));
    std::string basePath = path;
    std::string pyPath = basePath.substr(0, basePath.find_last_of("6") - 1);
    pyPath += "PythonInterface\\PythonScripts\\BasicDQN.py";

    fopen_s(&nnFile, pyPath.c_str(), "r");
    PyRun_SimpleFile(nnFile, "BasicDQN.py");

    PyRun_SimpleString("program.Start()");
    
    if (Py_FinalizeEx() < 0 && nnFile != NULL) {
        fclose(nnFile);
        return 120;
    }
    return 0;
}