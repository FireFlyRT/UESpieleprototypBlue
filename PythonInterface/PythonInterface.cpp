// Exe is in ..\UESpieleprototypBlue\x64\Release\PythonInterface.exe
#define PY_SSIZE_T_CLEAN

#include <iostream>
#include <stdio.h>
#include "pylibs/Python.h"
#include "PyEnvironment.h"

typedef struct {
    PyObject_HEAD
} BlaObject;

static PyTypeObject BlaType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "OB",
    .tp_doc = PyDoc_STR("Custom objects"),
    .tp_basicsize = sizeof(PyTypeObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
};

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
    std::string pyPath = basePath.substr(0, basePath.find_last_of("6") - 1); // Get Path before x64
    pyPath += "PythonInterface\\PythonScripts\\BasicDQN.py"; // And add Path to Py-File


    PyEnvironment* pyEnv = new PyEnvironment();
    PyObject_Init(pyEnv, pyEnv->ob_type);

    fopen_s(&nnFile, pyPath.c_str(), "r");
    // Init Basic File
    PyRun_SimpleFile(nnFile, "BasicDQN.py");

    

    /*
    * Env Observation Space =
    *   SensorData
    *   Audio
    *   Inventory
    *   BrainStorage
    *   Stats
    * 
    * Daten von Unreal 1 - "named Pipe" -> n PythonInterface 1 - PyObject -> 1 Python
    * Python - PyObject? -> PythonInterface - "named Pipe" -> Unreal
    */

    // Start with Env
    PyRun_SimpleString("program.Start()");
    
    if (Py_FinalizeEx() < 0 && nnFile != NULL) {
        fclose(nnFile);
        return 120;
    }
    return 0;
}