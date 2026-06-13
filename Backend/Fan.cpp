#include "Fan.h"

Fan::Fan(const std::string &id,
                 const std::string &name,
                 const std::string &roomName)
    : Device(id, name, roomName, DEVICE_FAN, 70.0)
{
    speed = 1;
    info.extraParam = speed;
}

void Fan::updateParam(int value)
{
    if (value < 1) value = 1;
    if (value > 3) value = 3;
    speed = value;
    info.extraParam = speed;
}
