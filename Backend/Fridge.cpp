#include "Fridge.h"

Fridge::Fridge(const std::string &id,
                 const std::string &name,
                 const std::string &roomName)
    : Device(id, name, roomName, DEVICE_FRIDGE, 150.0)
{
    coolingLevel = 3;
    info.extraParam = coolingLevel;
}

void Fridge::updateParam(int value)
{
    coolingLevel = value;
    info.extraParam = coolingLevel;
}
