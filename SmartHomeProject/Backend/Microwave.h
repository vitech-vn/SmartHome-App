#ifndef MICROWAVE_H
#define MICROWAVE_H

#include "Device.h"

// Lò vi sóng: không có tham số điều chỉnh, công suất cố định.
class Microwave : public Device
{
public:
    Microwave(
        std::string id,
        std::string name,
        std::string roomName,
        double power
    );

    void updateParam(int value) override;
};

#endif
