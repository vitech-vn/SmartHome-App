#include "Light.h"

Light::Light(
    std::string id,
    std::string name,
    std::string roomName,
    double power
)
    : Device(id, name, roomName, DEVICE_LIGHT, power)
{
    extraParam   = 100;          // mặc định sáng 100%
    currentPower = ratedPower;   // 100% -> đủ công suất
}

void Light::updateParam(int value)
{
    if (value < 0)   value = 0;
    if (value > 100) value = 100;

    extraParam   = value;
    currentPower = ratedPower * (value / 100.0);
}
