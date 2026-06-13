#ifndef WATERHEATER_H
#define WATERHEATER_H

#include "Device.h"

class WaterHeater : public Device
{
private:
    int temperature;

public:
    WaterHeater(const std::string &id,
            const std::string &name,
            const std::string &roomName);

    void updateParam(int value) override;
};

#endif // WATERHEATER_H
