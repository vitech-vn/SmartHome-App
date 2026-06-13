#ifndef WATER_HEATER_H
#define WATER_HEATER_H

#include "Device.h"

// Bình nước nóng: không có tham số điều chỉnh, công suất cố định.
class WaterHeater : public Device
{
public:
    WaterHeater(
        std::string id,
        std::string name,
        std::string roomName,
        double power
    );

    void updateParam(int value) override;
};

#endif
