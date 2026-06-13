#include "Fridge.h"

Fridge::Fridge(
    std::string id,
    std::string name,
    std::string roomName,
    double power
)
    : Device(id, name, roomName, DEVICE_FRIDGE, power)
{
    extraParam = 0;
}

void Fridge::updateParam(int value)
{
    // Thiết bị này không dùng tham số mở rộng.
    (void)value;
    extraParam = 0;
}
