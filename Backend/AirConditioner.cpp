#include "AirConditioner.h"

AirConditioner::AirConditioner(const std::string &id,
                 const std::string &name,
                 const std::string &roomName)
    : Device(id, name, roomName, DEVICE_AC, 1200.0)
{
    temperature = 24;
    info.extraParam = temperature;
}

void AirConditioner::updateParam(int value)
{
    if (value < MIN_AC_TEMP) value = MIN_AC_TEMP;
    if (value > MAX_AC_TEMP) value = MAX_AC_TEMP;
    temperature = value;
    info.extraParam = temperature;
}
