#include "TV.h"

TV::TV(const std::string &id,
                 const std::string &name,
                 const std::string &roomName)
    : Device(id, name, roomName, DEVICE_TV, 120.0)
{
    volume = 30;
    info.extraParam = volume;
}

void TV::updateParam(int value)
{
    if (value < 0) value = 0;
    if (value > 100) value = 100;
    volume = value;
    info.extraParam = volume;
}
