#include "Microwave.h"

Microwave::Microwave(
    std::string id,
    std::string name,
    std::string roomName,
    double power
)
    : Device(id, name, roomName, DEVICE_MICROWAVE, power)
{
    extraParam = 0;
}

void Microwave::updateParam(int value)
{
    // Thiết bị này không dùng tham số mở rộng.
    (void)value;
    extraParam = 0;
}
