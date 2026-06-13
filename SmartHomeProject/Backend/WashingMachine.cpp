#include "WashingMachine.h"

WashingMachine::WashingMachine(const std::string &id,
                 const std::string &name,
                 const std::string &roomName)
    : Device(id, name, roomName, DEVICE_WASHING_MACHINE, 500.0)
{
    isWashing = 0;
    info.extraParam = isWashing;
}

void WashingMachine::updateParam(int value)
{
    isWashing = value;
    info.extraParam = isWashing;
}
