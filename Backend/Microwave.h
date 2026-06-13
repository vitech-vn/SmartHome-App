#ifndef MICROWAVE_H
#define MICROWAVE_H

#include "Device.h"

class Microwave : public Device
{
private:
    int timerSeconds;

public:
    Microwave(const std::string &id,
            const std::string &name,
            const std::string &roomName);

    void updateParam(int value) override;
};

#endif // MICROWAVE_H
