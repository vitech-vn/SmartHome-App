#ifndef CURTAIN_H
#define CURTAIN_H

#include "Device.h"

class Curtain : public Device
{
private:
    int position;

public:
    Curtain(const std::string &id,
            const std::string &name,
            const std::string &roomName);

    void updateParam(int value) override;
};

#endif // CURTAIN_H
