#include "RiceCooker.h"

RiceCooker::RiceCooker(const std::string &id,
                 const std::string &name,
                 const std::string &roomName)
    : Device(id, name, roomName, DEVICE_RICE_COOKER, 700.0)
{
    mode = 0;
    info.extraParam = mode;
}

void RiceCooker::updateParam(int value)
{
    mode = value;
    info.extraParam = mode;
}
