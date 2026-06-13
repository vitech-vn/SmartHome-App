#include "Fan.h"

Fan::Fan(
    std::string id,
    std::string name,
    std::string roomName,
    double power
)
    : Device(id, name, roomName, DEVICE_FAN, power)
{
    extraParam   = 1;
    currentPower = ratedPower * (1.0 / 3.0);
}

void Fan::updateParam(int value)
{
    if (value < 1) value = 1;
    if (value > 3) value = 3;

    extraParam   = value;
    currentPower = ratedPower * (value / 3.0);
}
