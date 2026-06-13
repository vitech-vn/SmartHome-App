#ifndef AIRCONDITIONER_H
#define AIRCONDITIONER_H

#include "Device.h"

class AirConditioner : public Device
{
private:
    int temperature;

public:
    AirConditioner(const std::string &id,
            const std::string &name,
            const std::string &roomName);

    void updateParam(int value) override;
};

#endif // AIRCONDITIONER_H
