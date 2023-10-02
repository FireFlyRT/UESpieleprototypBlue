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
    fopen_s(&nnFile, "C:/Users/starw/OneDrive/Desktop/SAEProjects/UESpieleprototypBlueGIT/PythonInterface/PythonScripts/BasicDQN.py", "r");
    PyRun_SimpleFile(nnFile, "BasicDQN.py");
    
    if (Py_FinalizeEx() < 0 && nnFile != NULL) {
        fclose(nnFile);
        return 120;
    }
    return 0;
}