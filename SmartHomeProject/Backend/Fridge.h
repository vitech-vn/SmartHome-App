#ifndef FRIDGE_H
#define FRIDGE_H

#include "Device.h"

class Fridge : public Device
{
private:
    int coolingLevel;

public:
    Fridge(const std::string &id,
            const std::string &name,
            const std::string &roomName);

    void updateParam(int value) override;
};

#endif // FRIDGE_H
