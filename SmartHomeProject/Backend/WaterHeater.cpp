#include "WaterHeater.h"

WaterHeater::WaterHeater(
    std::string id,
    std::string name,
    std::string roomName,
    double power
)
    : Device(id, name, roomName, DEVICE_WATER_HEATER, power)
{
    extraParam = 0;
}

void WaterHeater::updateParam(int value)
{
    // Thiết bị này không dùng tham số mở rộng.
    (void)value;
    extraParam = 0;
}
