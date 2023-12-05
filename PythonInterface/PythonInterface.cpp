// Exe is in ..\UESpieleprototypBlue\x64\Release\PythonInterface.exe
#define PY_SSIZE_T_CLEAN

#include <iostream>
#include <stdio.h>
#include <future>
#include <array>
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <sstream>
#include "pylibs/Python.h"
#include "PyEnvironment.h"
#include "CrypticHelper.h"
#include "SensorData.h"
#include "PythonCommands.h"

HANDLE _pipeHandle;

bool ClosePipeClient()
{
    return CloseHandle(_pipeHandle);
}

bool SendDataWithPipeClient(const char* data)
{
    DWORD written;

    if (_pipeHandle != INVALID_HANDLE_VALUE)
    {
        while (WriteFile(_pipeHandle, data, sizeof(data), &written, NULL) != FALSE);

        std::cout << "Data sended " << written << std::endl;
        return true;
    }

    return false;
}

bool StartPipeClient()
{
    return true;
}

std::string ReceiveDataFromPipeServer()
{
    DWORD read;
    char buffer[1028];

    if (_pipeHandle != INVALID_HANDLE_VALUE)
    {
        while(ReadFile(_pipeHandle, buffer, sizeof(buffer), &read, NULL) != FALSE);
        std::cout << "Data readed " << read << std::endl;
        std::ostringstream stream;
        stream << read;
        std::string result = stream.str();
        return result;
    }

    return NULL;
}

int RunPythonFile(char* argv[], bool basicFile = false)
{
    FILE* nnFile = nullptr;
    char path[255] = "";
    char* _ = _fullpath(path, argv[0], sizeof(path));
    std::string basePath = path;
    std::string pyPath = basePath.substr(0, basePath.find_last_of("6") - 1); // Get Path before x64
    pyPath += "PythonInterface\\PythonScripts\\BasicDQN.py"; // And add Path to Py-File

    if (basicFile && nnFile != nullptr)
    {
        // Init Basic File
        fopen_s(&nnFile, pyPath.c_str(), "r");
        PyRun_SimpleFile(nnFile, "BasicDQN.py");
        fclose(nnFile);
    }

    if (Py_FinalizeEx() < 0 && nnFile != nullptr) {
        return 120;
    }

    return 0;
}

int main(int argc, char* argv[])
{    
    // TODO (Major): Workflow from PyInterface (multiline)
    // On Start:
    //  - Initialise all C++ Modules for Python
    //  - Initialise Python Environment
    //  - Run *DQN.py File
    //  - Configure DQN for right usage
    // 
    //  - Connect to MainPipe
    //  - Wait for new ID
    // 
    // On ID Received:
    //  - Connect to VillagerPipe using the ID
    //  - Wait for Sensor-/Reward-Data
    // 
    // On Data Received:
    //  - Parse Data with CrypticHelper (String to Objects)
    //  - Save Objects for later use (Learning)
    //  - Create Data in Python
    //  - Insert Data in Neural Network
    //  - Send Output back to C++  (HOW?!?!?!?)
    //  - Create NeuralNetworkData out of the Output 
    //  - Parse NeuralNetworkData with CrypticHelper  (Object to String)
    //  - Send Parsed String to Unreal Application
    //  - Wait for new Sensor-/Reward-Data
    // 
    // On Learning enabled:
    //  - Get saved Environments and Rewards
    //  - Input every Tuple of it
    //  - Update after each Tuple
    //  
    //  - When learning finished
    //  - Save DQN
    //  - Send wake message to Unreal
    // 
    // On Death:
    //  - Save the DQN for comparison?
    //  - Compare the DQN with best dead DQN?
    //  - if best: Save DQN as best, delete other OR delete DQN (Score?)?
    //  - Disconnect NamedPipe
    //  - Finalise Python
    //  - Close Interface Application
    //

    // On Start:
    std::cout << "Initialize Python Interface!\n"; 

    // Initialise C++ Modules in Python
    const char* pyEnvModule = "PyEnvironment";
    const char* pyRewModule = "RewardData";
    const char* pySensModule = "SensorData";
    const char* pyStatModule = "StatData";
    const char* pyNNModule = "NeuralNetworkData";
    PyImport_AppendInittab(pyEnvModule, &PyEnvironment::PyInit_PyEnvironment);
    PyImport_AppendInittab(pyRewModule, &RewardData::PyInit_PyRewardData);
    PyImport_AppendInittab(pySensModule, &SensorData::PyInit_PySensorData);
    PyImport_AppendInittab(pyStatModule, &StatData::PyInit_PyStatData);
    PyImport_AppendInittab(pyNNModule, &NeuralNetworkData::PyInit_PyNeuralNetworkData);

    // Initialise Python Environment
    Py_Initialize();
    std::cout << "Initialized: " << Py_IsInitialized() << std::endl;

    // Run *DQN.py File
    RunPythonFile(argv, true);
    // Configure DQN for right usage
    PythonCommands::ImportModule(pyEnvModule);
    PythonCommands::ImportModule(pyRewModule);
    PythonCommands::ImportModule(pySensModule);
    PythonCommands::ImportModule(pyStatModule);
    PythonCommands::ImportModule(pyNNModule);
    PyRun_SimpleString("print('From Python: Hello World!')"); 

    // Connect to MainPipe
    bool isConnected = false;
    while (!isConnected)
    {
        _pipeHandle = CreateFile(
            TEXT("\\\\.\\pipe\\MainPipe"),
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);

        if (_pipeHandle == INVALID_HANDLE_VALUE)
        {
            std::cout << "MainPipe Invalid!!!" << std::endl;
            ClosePipeClient();
            continue;
        }

        if (ConnectNamedPipe(_pipeHandle, NULL) != FALSE)
        {
            SendDataWithPipeClient("Empty"); 
            // Maybe with random unic uint ID
            // Or Connect to One VillagerPipe befor the next one
            //  - Save IDs in Queue/List
            //  - create InterfaceProgram and conntect to VPipe befor creating next one
        }

        std::cout << "Connected to MainPipe" << std::endl;

        //Wait for new ID
        std::string villagerID = ReceiveDataFromPipeServer();
        std::string newHandle = "\\\\.\\pipe\\";
        newHandle.append(villagerID);

        std::cout << "New Handle Address: " << newHandle << std::endl;

        // On ID Received:
        // Connect to VillagerPipe using the ID
        _pipeHandle = CreateFile(
            (LPCWSTR)newHandle.c_str(),
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);

        if (_pipeHandle == INVALID_HANDLE_VALUE)
        {
            std::cout << "VillagerPipe Invalid!!!" << std::endl;
            ClosePipeClient();
            continue;
        }
        else
        {
            isConnected = true;
        }
    }
    
    while (true)
    {
        // Wait for Sensor-/Reward-Data
        std::string sArData = ReceiveDataFromPipeServer();
    
        // On Data Received:
        // Parse Data with CrypticHelper (String to Objects)
        SensorData* sensorData = new SensorData();
        StatData* statData = new StatData();
        RewardData* rewardData = new RewardData();
        if (CrypticHelper::DecryptValue(sArData, sensorData, statData, rewardData))
        {
            // Save Objects for later use (Learning)
            // Create Data in Python
            // Insert Data in Neural Network
            // TODO (Major): Send Output back to C++  (HOW?!?!?!?)
            std::string command = "PyEnvironment.numargs = ";
            command.append(std::to_string(12));
            PyRun_SimpleString(command.c_str());
            PyRun_SimpleString("print(PyEnvironment.numargs)");
            
            std::cout << "From C++: " << PyEnvironment::GetNumargs() << std::endl;
            std::string output;
            // TODO (Major): Create NeuralNetworkData out of the Output 
            NeuralNetworkData* nnData = new NeuralNetworkData();
            // Parse NeuralNetworkData with CrypticHelper  (Object to String)
            std::string nnValues = CrypticHelper::EncryptValue(nnData);
            // Send Parsed String to Unreal Application
            SendDataWithPipeClient(nnValues.c_str());
            // Wait for new Sensor-/Reward-Data
        }
    }    
    
    return 0;
}