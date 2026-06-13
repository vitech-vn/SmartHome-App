#ifndef LIGHT_H
#define LIGHT_H

#include "Device.h"

// Đèn: extraParam = độ sáng (0 - 100)
// Công suất tiêu thụ tỉ lệ thuận với độ sáng.
class Light : public Device
{
public:
    Light(
        std::string id,
        std::string name,
        std::string roomName,
        double power
    );

    void updateParam(int value) override;
};

#endif
