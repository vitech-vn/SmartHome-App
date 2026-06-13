#include "Curtain.h"

Curtain::Curtain(const std::string &id,
                 const std::string &name,
                 const std::string &roomName)
    : Device(id, name, roomName, DEVICE_CURTAIN, 5.0)
{
    position = 0;
    info.extraParam = position;
}

void Curtain::updateParam(int value)
{
    if (value < 0) value = 0;
    if (value > 100) value = 100;
    position = value;
    info.extraParam = position;
}
