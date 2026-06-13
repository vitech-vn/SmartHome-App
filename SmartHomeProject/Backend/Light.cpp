#include "Light.h"

Light::Light(const std::string &id,
                 const std::string &name,
                 const std::string &roomName)
    : Device(id, name, roomName, DEVICE_LIGHT, 10.0)
{
    brightness = 100;
    info.extraParam = brightness;
}

void Light::updateParam(int value)
{
    if (value < 0) value = 0;
    if (value > 100) value = 100;
    brightness = value;
    info.extraParam = brightness;
}
