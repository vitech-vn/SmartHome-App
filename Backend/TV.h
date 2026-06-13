#ifndef TV_H
#define TV_H

#include "Device.h"

class TV : public Device
{
private:
    int volume;

public:
    TV(const std::string &id,
            const std::string &name,
            const std::string &roomName);

    void updateParam(int value) override;
};

#endif // TV_H
