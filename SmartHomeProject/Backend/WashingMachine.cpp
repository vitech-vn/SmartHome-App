#include "WashingMachine.h"

WashingMachine::WashingMachine(
    std::string id,
    std::string name,
    std::string roomName,
    double power
)
    : Device(id, name, roomName, DEVICE_WASHING_MACHINE, power)
{
    extraParam = 0;
}

void WashingMachine::updateParam(int value)
{
    // Thiết bị này không dùng tham số mở rộng.
    (void)value;
    extraParam = 0;
}
