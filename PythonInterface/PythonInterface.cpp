// Exe is in ..\UESpieleprototypBlue\x64\Release\PythonInterface.exe
#define PY_SSIZE_T_CLEAN

#include <iostream>
#include <stdio.h>
#include <future>
#include <array>
#include "pylibs/Python.h"
#include "PyEnvironment.h"



int TaskTest(char* argv[])
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

    // Initialise PyObject in Python
    PyEnvironment* pyEnv = new PyEnvironment();
    PyObject_Init(pyEnv, pyEnv->ob_type);
    //PyRun_SimpleString("pyEnv = PyEnvironment()"); // Der Typ ist hier NICHT in Python definiert
    PyRun_SimpleString("print(pyEnv)");                // Warum ist pyEnv nicht definiert?

    // Init Basic File
    fopen_s(&nnFile, pyPath.c_str(), "r");
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
    PyRun_SimpleString("program = Program()");
    PyRun_SimpleString("program.Start()");

    if (Py_FinalizeEx() < 0 && nnFile != NULL) {
        fclose(nnFile);
        return 120;
    }
}

int main(int argc, char* argv[])
{
    std::array<std::future<int>*, 2> threads = std::array<std::future<int>*, 2>();

    for (int i = 0; i < 2; i++)
    {
        std::future<int> thread = std::async(std::launch::async, TaskTest, argv);
        threads[i] = &thread;
    }
    
    bool threadsActive = true; 

    while (threadsActive)
    {
        for (int i = 0; i < threads.size(); i++)
        {
            if (threads[i]->get() == 1)
            {
                threads[i] = nullptr;
            }
        }
        for (int i = 0; i < threads.size(); i++)
        {
            if (threads[i] != nullptr)
            {
                break;
            }
            else if (i == threads.size())
            {
                threadsActive = false;
            }
        }
    }
    
    return 0;
}