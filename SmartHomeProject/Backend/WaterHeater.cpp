#include "WaterHeater.h"

WaterHeater::WaterHeater(const std::string &id,
                 const std::string &name,
                 const std::string &roomName)
    : Device(id, name, roomName, DEVICE_WATER_HEATER, 2000.0)
{
    temperature = 40;
    info.extraParam = temperature;
}

void WaterHeater::updateParam(int value)
{
    temperature = value;
    info.extraParam = temperature;
}
