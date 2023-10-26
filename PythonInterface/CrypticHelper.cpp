#include "CrypticHelper.h"

SensorData* CrypticHelper::DecryptValue(std::string value)
{
    SensorData* data = new SensorData();

    data->ClassCategory = std::stoi(value.substr(0, 1));
    data->TribeID = std::stoi(value.substr(3, 5));
    data->LivePoints = std::stoi(value.substr(7, 9));
    data->Stamina = std::stoi(value.substr(11, 13));
    data->Strength = std::stoi(value.substr(15, 17));
    data->Age = std::stoi(value.substr(19, 21));
    data->Height = std::stoi(value.substr(23, 25));
    data->Hunger = std::stoi(value.substr(27, 29));
    data->Thurst = std::stoi(value.substr(31, 33));
    int accidentalX = std::stoi(value.substr(35, 35));
    data->PositionX = std::stoi(value.substr(37, 43));
    int accidentalY = std::stoi(value.substr(45, 45));
    data->PositionY = std::stoi(value.substr(47, 53));
    int accidentalZ = std::stoi(value.substr(55, 55));
    data->PositionZ = std::stoi(value.substr(57, 63));
    data->Distance = std::stoi(value.substr(65, 70));
    // data->Inventory = value.substr(0, 1);

    if (accidentalX == 0) data->PositionX *= -1;
    if (accidentalY == 0) data->PositionY *= -1;
    if (accidentalZ == 0) data->PositionZ *= -1;

    return data;
}

std::string CrypticHelper::EncryptValue(NeuralNetworkData* data)
{
    return std::string();
}
