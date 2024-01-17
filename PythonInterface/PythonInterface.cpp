// Exe is in ..\UESpieleprototypBlue\x64\Release\PythonInterface.exe
#pragma once
#define PY_SSIZE_T_CLEAN

#include <iostream>
#include <stdio.h>
#include <future>
#include <array>
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <sstream>
#include "CrypticHelper.h"
#include "PythonCommands.h"
#include "CPyEnvironment.c"
#include "filesystem"

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


std::string GetProjectPath(char* argv[])
{
    char path[255] = "";
    char* _ = _fullpath(path, argv[0], sizeof(path));
    std::string basePath = path;
    std::string pyPath = basePath.substr(0, basePath.find_last_of("6") - 1); // Get Path before x64
    return pyPath;
}

int RunPythonFile(char* argv[], bool useBasicFile = false)
{
    FILE* nnFile = nullptr;
    std::string pyPath = GetProjectPath(argv); // Get Path before x64
    pyPath += "PythonScripts\\BasicDQN.py"; // And add Path to Py-File
    fopen_s(&nnFile, pyPath.c_str(), "r");

    if (/*useBasicFile && */nnFile != nullptr)
    {
        // Init Basic File
        PyRun_SimpleFile(nnFile, "BasicDQN.py");
        fclose(nnFile);
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
    //std::cout << "Initialize Python Interface!\n"; 
    //
    //// C++ Values for Python
    //const char* pyModule = "pyModule";
    //const char* pyEnv = "CPyEnv";
    //const char* pyRewData = "CPyRew";
    //const char* pyNNData = "CPyNNData";
    //const char* pySensData = "CPySensData";
    //const char* pyStatData = "CPyStatData";
    //
    // Initialise Python Environment
    Py_Initialize();
    std::cout << "Initialized: " << Py_IsInitialized() << std::endl;
    PyRun_SimpleString("import platform");
    PyRun_SimpleString("print(platform.python_version())");
    //PyObject* module = PythonCommands::ImportModule(pyModule);

    // Add Folder Structure
    std::string projPath = GetProjectPath(argv);
    std::string jsonPath = projPath;
    jsonPath.append("/JSONData");
    if (!std::filesystem::exists(jsonPath.c_str()))
        std::filesystem::create_directories(jsonPath.c_str());

    //// Run *DQN.py File
    RunPythonFile(argv, true);
    //// Configure DQN for right usage

    // Connect to MainPipe
    //bool isConnected = false;
    //while (!isConnected)
    //{
    //    _pipeHandle = CreateFile(
    //        TEXT("\\\\.\\pipe\\MainPipe"),
    //        GENERIC_READ | GENERIC_WRITE,
    //        0,
    //        NULL,
    //        OPEN_EXISTING,
    //        0,
    //        NULL);
    //
    //    if (_pipeHandle == INVALID_HANDLE_VALUE)
    //    {
    //        std::cout << "MainPipe Invalid!!!" << std::endl;
    //        ClosePipeClient();
    //        continue;
    //    }
    //
    //    if (ConnectNamedPipe(_pipeHandle, NULL) != FALSE)
    //    {
    //        SendDataWithPipeClient("Empty"); 
    //        // Maybe with random unic uint ID
    //        // Or Connect to One VillagerPipe befor the next one
    //        //  - Save IDs in Queue/List
    //        //  - create InterfaceProgram and conntect to VPipe befor creating next one
    //    }
    //
    //    std::cout << "Connected to MainPipe" << std::endl;
    //
    //    //Wait for new ID
    //    std::string villagerID = ReceiveDataFromPipeServer();
    //    std::string newHandle = "\\\\.\\pipe\\";
    //    newHandle.append(villagerID);
    //
    //    std::cout << "New Handle Address: " << newHandle << std::endl;
    //
    //    // On ID Received:
    //    // Connect to VillagerPipe using the ID
    //    _pipeHandle = CreateFile(
    //        (LPCWSTR)newHandle.c_str(),
    //        GENERIC_READ | GENERIC_WRITE,
    //        0,
    //        NULL,
    //        OPEN_EXISTING,
    //        0,
    //        NULL);
    //
    //    if (_pipeHandle == INVALID_HANDLE_VALUE)
    //    {
    //        std::cout << "VillagerPipe Invalid!!!" << std::endl;
    //        ClosePipeClient();
    //        continue;
    //    }
    //    else
    //    {
    //        isConnected = true;
    //    }
    //}
    
    //while (true)
    //{
        //if (ConnectNamedPipe(_pipeHandle, NULL) == FALSE)
        //{
        //    std::cout << "VillagerPipe Closed!" << std::endl;
        //    break;
        //}

        // Wait for Sensor-/Reward-Data
        std::string sArData = ReceiveDataFromPipeServer();
    
        // On Data Received:
        // Parse Data with CrypticHelper (String to Objects)
        SensorData* sensorData = new SensorData();
        StatData* statData = new StatData();
        RewardData* rewardData = new RewardData();
        if (CrypticHelper::DecryptValue(sArData, sensorData, statData, rewardData))
        {
            std::string command = std::string();
            // Save Objects for later use (Learning) TODO
            // Create Data in Python

            

            // Init Environment
            

            // Insert Data in Neural Network

            // Send Output back to C++

            // Create NeuralNetworkData out of the Output 
            NeuralNetworkData* nnData = new NeuralNetworkData();
            nnData->GetNeuralNetworkDataFromJSON(jsonPath, "2189712", "2");
            std::cout << nnData->MovementX << std::endl;
        
            // Parse NeuralNetworkData with CrypticHelper  (Object to String)
            std::string nnValues = CrypticHelper::EncryptValue(nnData);
            // Send Parsed String to Unreal Application
            SendDataWithPipeClient(nnValues.c_str());
            // Wait for new Sensor-/Reward-Data
    /*    }
    }    */
    
    return 0;
}