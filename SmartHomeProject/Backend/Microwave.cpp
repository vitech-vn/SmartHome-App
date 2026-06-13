#include "Microwave.h"

Microwave::Microwave(const std::string &id,
                 const std::string &name,
                 const std::string &roomName)
    : Device(id, name, roomName, DEVICE_MICROWAVE, 1000.0)
{
    timerSeconds = 0;
    info.extraParam = timerSeconds;
}

void Microwave::updateParam(int value)
{
    timerSeconds = value;
    info.extraParam = timerSeconds;
}
