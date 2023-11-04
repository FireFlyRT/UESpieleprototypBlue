#include "CrypticHelper.h"

bool CrypticHelper::DecryptValue(std::string value, SensorData* sensorData, StatData* statData, RewardData* rewardData)
{
    //SensorData
    sensorData->ClassCategory = std::stoi(value.substr(0, 1));
    sensorData->TribeID = std::stoi(value.substr(3, 5));
    sensorData->LivePoints = std::stoi(value.substr(7, 9));
    sensorData->Stamina = std::stoi(value.substr(11, 13));
    sensorData->Strength = std::stoi(value.substr(15, 17));
    sensorData->Age = std::stoi(value.substr(19, 21));
    sensorData->Height = std::stoi(value.substr(23, 25));
    sensorData->Hunger = std::stoi(value.substr(27, 29));
    sensorData->Thurst = std::stoi(value.substr(31, 33));
    int accidentalX = std::stoi(value.substr(35, 35));
    sensorData->PositionX = std::stoi(value.substr(37, 43));
    int accidentalY = std::stoi(value.substr(45, 45));
    sensorData->PositionY = std::stoi(value.substr(47, 53));
    int accidentalZ = std::stoi(value.substr(55, 55));
    sensorData->PositionZ = std::stoi(value.substr(57, 63));
    sensorData->Distance = std::stoi(value.substr(65, 70));
    // sensorData->Inventory = value.substr(0, 1);

    if (accidentalX == 0) sensorData->PositionX *= -1;
    if (accidentalY == 0) sensorData->PositionY *= -1;
    if (accidentalZ == 0) sensorData->PositionZ *= -1;

    // StatData
    statData->ClassCategory = std::stoi(value.substr(71, 72));
    statData->TribeID = std::stoi(value.substr(74, 76));
    statData->LivePoints = std::stoi(value.substr(78, 80));
    statData->Stamina = std::stoi(value.substr(82, 84));
    statData->Strength = std::stoi(value.substr(86, 88));
    statData->Age = std::stoi(value.substr(90, 92));
    statData->Height = std::stoi(value.substr(94, 96));
    statData->Hunger = std::stoi(value.substr(98, 100));
    statData->Thurst = std::stoi(value.substr(102, 104));
    int accidentalX = std::stoi(value.substr(106, 106));
    statData->PositionX = std::stoi(value.substr(108, 114));
    int accidentalY = std::stoi(value.substr(116, 116));
    statData->PositionY = std::stoi(value.substr(118, 124));
    int accidentalZ = std::stoi(value.substr(126, 126));
    statData->PositionZ = std::stoi(value.substr(128, 134));
    // sensorData->Inventory = value.substr(0, 1);

    if (accidentalX == 0) statData->PositionX *= -1;
    if (accidentalY == 0) statData->PositionY *= -1;
    if (accidentalZ == 0) statData->PositionZ *= -1;

    // RewardData
    int accidentalReward = std::stoi(value.substr(136, 136));
    rewardData->Reward = std::stoi(value.substr(138, 141));
    if (accidentalReward == 0) rewardData->Reward *= -1;

    return true;
}

std::string CrypticHelper::EncryptValue(NeuralNetworkData* data)
{
    return std::string();
}
