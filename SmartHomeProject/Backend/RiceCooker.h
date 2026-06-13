#ifndef RICECOOKER_H
#define RICECOOKER_H

#include "Device.h"

class RiceCooker : public Device
{
private:
    int mode;

public:
    RiceCooker(const std::string &id,
            const std::string &name,
            const std::string &roomName);

    void updateParam(int value) override;
};

#endif // RICECOOKER_H
