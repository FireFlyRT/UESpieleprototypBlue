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
#include "PyEnvironment.h"
#include "filesystem"

static HANDLE _pipeHandle = INVALID_HANDLE_VALUE;

bool ClosePipeClient()
{
    CloseHandle(_pipeHandle);
    _pipeHandle = nullptr;
    delete(_pipeHandle);
    return true;
}

bool SendDataWithPipeClient(const wchar_t* data, std::string jsonPath)
{
    DWORD written;

    if (_pipeHandle != INVALID_HANDLE_VALUE)
    {
        if (WriteFile(_pipeHandle, data, sizeof(data), &written, NULL))
        {
            std::cout << "Data sended " << written << std::endl;
            return true;
        }
    }

    //std::cout << "Data send failed " << data << std::endl;
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
        std::cout << "Reading... " << std::endl;
        while(ReadFile(_pipeHandle, buffer, sizeof(buffer), &read, NULL) != FALSE);
        std::cout << "Data readed " << read << std::endl;
        std::ostringstream stream;
        stream << read;
        std::string result = stream.str();
        return result;
    }
    // DEBUG
    else 
    {
        std::cout << "Fallback Input!!!" << std::endl;
        std::string b = "00,000,100,050,030,024,189,043,042,1.0000000;0.3821341;1.0421621,010205,00,000,100,050,030,024,189,043,042,1.0000000;0.3821341;1.0421621,1.2458";
        return b;
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
    else if (/*!useBasicFile && */nnFile != nullptr)
    {
        PyRun_SimpleFile(nnFile, "RainbowDQN.py");
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
    //  - Send Output back to C++  (JSON)
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
    std::string program = "prog";
    int lastAction = 0;

    // Initialise Python Environment
    Py_Initialize();
    std::cout << "Initialized: " << Py_IsInitialized() << std::endl;
    PyRun_SimpleString("import platform");
    PyRun_SimpleString("print(platform.python_version())");

    // Add Folder Structure
    std::string projPath = GetProjectPath(argv);
    std::string jsonPath = projPath;
    jsonPath.append("/JSONData");
    if (!std::filesystem::exists(jsonPath.c_str()))
        std::filesystem::create_directories(jsonPath.c_str());

    // Run *DQN.py File
    RunPythonFile(argv, true);
    // Configure DQN for right usage


    // Connect to MainPipe
    bool isConnected = false;
    int connectionCount = 0;
    int jsonCount = 0;
    std::string villagerID;
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
            connectionCount++;
            if (connectionCount > 100)
                break;
            continue;
        }
        std::cout << "Connected to MainPipe" << std::endl;
    
        //while (ConnectNamedPipe(_pipeHandle, NULL) == FALSE);
        const size_t size = strlen("Empty") + 1;
        wchar_t* empty = new wchar_t[size];
        size_t s = mbstowcs(empty, "Empty", size);
        for (int i = 0; i < 100000; i++)
            SendDataWithPipeClient(empty);
        // Maybe with random unic uint ID
        // Or Connect to One VillagerPipe befor the next one
        //  - Save IDs in Queue/List
        //  - create InterfaceProgram and conntect to VPipe befor creating next one

    
        //Wait for new ID
        villagerID = ReceiveDataFromPipeServer();
        //if (villagerID == std::string())
        //std::string pyVillagerID = "'";
        //pyVillagerID.append("Villager");
        //pyVillagerID.append(villagerID);
        //pyVillagerID.append("'");
        std::string pyVillagerID = "'Villager001'"; // Fallback
        std::string newHandle = "\\\\.\\pipe\\";
        newHandle.append(villagerID);
        std::string** progValues = new std::string*[1]
        {
            new std::string(pyVillagerID),
        };
        PythonCommands::CreateClass("Program", program, progValues, 1);
    
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
    
    int connectionAttemps = 0;
    while (true)
    {
        if (ConnectNamedPipe(_pipeHandle, NULL) == FALSE)
        {
            connectionAttemps++;
            if (connectionAttemps > 100)
            {
                std::cout << "VillagerPipe Closed!" << std::endl;
                break;
            }
            continue;
        }

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
            // Save Objects for later use (Learning) TODO (No Prio)
            // ExperienceBuffer!

            // Create Data in Python
            std::string** statValues = new std::string*[12]
            {
                new std::string(std::to_string(statData->ClassCategory)),
                new std::string(std::to_string(statData->TribeID)),
                new std::string(std::to_string(statData->LivePoints)),
                new std::string(std::to_string(statData->Stamina)),
                new std::string(std::to_string(statData->Strength)),
                new std::string(std::to_string(statData->Age)),
                new std::string(std::to_string(statData->Height)),
                new std::string(std::to_string(statData->Hunger)),
                new std::string(std::to_string(statData->Thurst)),
                new std::string(std::to_string(statData->PositionX)),
                new std::string(std::to_string(statData->PositionY)),
                new std::string(std::to_string(statData->PositionZ)),
            };
            PythonCommands::CreateClass("StatData", "statData", statValues, 12);

            std::string** sensorValues = new std::string*[13]
            {
                new std::string(std::to_string(sensorData->ClassCategory)),
                new std::string(std::to_string(sensorData->TribeID)),
                new std::string(std::to_string(sensorData->LivePoints)),
                new std::string(std::to_string(sensorData->Stamina)),
                new std::string(std::to_string(sensorData->Strength)),
                new std::string(std::to_string(sensorData->Age)),
                new std::string(std::to_string(sensorData->Height)),
                new std::string(std::to_string(sensorData->Hunger)),
                new std::string(std::to_string(sensorData->Thurst)),
                new std::string(std::to_string(sensorData->PositionX)),
                new std::string(std::to_string(sensorData->PositionY)),
                new std::string(std::to_string(sensorData->PositionZ)),
                new std::string(std::to_string(sensorData->Distance)),
            };
            PythonCommands::CreateClass("SensorData", "sensorData", sensorValues, 13);

            std::string** rewardValues = new std::string*[1]
            {
                    new std::string(std::to_string(rewardData->Reward))
            };
            PythonCommands::CreateClass("RewardData", "rewardData", rewardValues, 1);

            // Init Environment in Python
            PyRun_SimpleString("prog.env.SetObservationSpace(sensorData.GetData(), statData.GetData())");
            PyRun_SimpleString("prog.LateInit()");

            // Build state in Python as new_state
            PyRun_SimpleString("new_state = statData.GetData()");

            // INFO: Program.agent.ExperienceStep(action, state, reward, isDone)
            command = program;
            command.append(".agent.ExperienceStep(");
            command.append(std::to_string(lastAction));
            command.append(", new_state, ");
            command.append(std::to_string(rewardData->Reward));
            command.append(", ");
            command.append("False"); // is_done | later from rewardData?
            command.append(")");
            PyRun_SimpleString(command.c_str());
            // INFO: Program.OnGetReward(reward)
            command = program;
            command.append(".OnGetReward(");
            command.append(std::to_string(rewardData->Reward));
            command.append(")");
            PyRun_SimpleString(command.c_str());

            // Insert Data in Neural Network

            // Step
            PyRun_SimpleString("prog.Step()");
            // Send Output back to C++ (JSON)

            // Create NeuralNetworkData out of the Output 
            NeuralNetworkData* nnData = new NeuralNetworkData();
            nnData->GetNeuralNetworkDataFromJSON(jsonPath, villagerID, std::to_string(jsonCount));
            lastAction = nnData->Action;
            jsonCount++;

            // Parse NeuralNetworkData with CrypticHelper  (Object to String)
            std::string nnValues = CrypticHelper::EncryptValue(nnData);
            // Send Parsed String to Unreal Application
            const size_t size = strlen(nnValues.c_str()) + 1;
            wchar_t* values = new wchar_t[size];
            mbstowcs(values, nnValues.c_str(), size);
            SendDataWithPipeClient(values);
            // Wait for new Sensor-/Reward-Data
        }
    }    
    
    return 0;
}