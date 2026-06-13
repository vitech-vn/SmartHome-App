#ifndef LIGHT_H
#define LIGHT_H

#include "Device.h"

class Light : public Device
{
private:
    int brightness;

public:
    Light(const std::string &id,
            const std::string &name,
            const std::string &roomName);

    void updateParam(int value) override;
};

#endif // LIGHT_H
