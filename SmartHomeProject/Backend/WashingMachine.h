#ifndef WASHING_MACHINE_H
#define WASHING_MACHINE_H

#include "Device.h"

// Máy giặt: không có tham số điều chỉnh, công suất cố định.
class WashingMachine : public Device
{
public:
    WashingMachine(
        std::string id,
        std::string name,
        std::string roomName,
        double power
    );

    void updateParam(int value) override;
};

#endif
