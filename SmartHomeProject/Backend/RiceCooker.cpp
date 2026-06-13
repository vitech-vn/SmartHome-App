#include "RiceCooker.h"

RiceCooker::RiceCooker(
    std::string id,
    std::string name,
    std::string roomName,
    double power
)
    : Device(id, name, roomName, DEVICE_RICE_COOKER, power)
{
    extraParam = 0;
}

void RiceCooker::updateParam(int value)
{
    // Thiết bị này không dùng tham số mở rộng.
    (void)value;
    extraParam = 0;
}
