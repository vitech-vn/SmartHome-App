#ifndef FAN_H
#define FAN_H

#include "Device.h"

// Quạt: extraParam = tốc độ (1 - 3)
// Công suất scale theo cấp tốc độ.
class Fan : public Device
{
public:
    Fan(
        std::string id,
        std::string name,
        std::string roomName,
        double power
    );

    void updateParam(int value) override;
};

#endif
