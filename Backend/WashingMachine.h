#ifndef WASHINGMACHINE_H
#define WASHINGMACHINE_H

#include "Device.h"

class WashingMachine : public Device
{
private:
    int isWashing;

public:
    WashingMachine(const std::string &id,
            const std::string &name,
            const std::string &roomName);

    void updateParam(int value) override;
};

#endif // WASHINGMACHINE_H
