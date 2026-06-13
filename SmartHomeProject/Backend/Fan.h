#ifndef FAN_H
#define FAN_H

#include "Device.h"

class Fan : public Device
{
private:
    int speed;

public:
    Fan(const std::string &id,
            const std::string &name,
            const std::string &roomName);

    void updateParam(int value) override;
};

#endif // FAN_H
