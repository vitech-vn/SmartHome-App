#ifndef AIR_CONDITIONER_H
#define AIR_CONDITIONER_H

#include "Device.h"

// Điều hòa: extraParam = nhiệt độ (MIN_AC_TEMP - MAX_AC_TEMP)
// Nhiệt độ càng thấp -> công suất càng cao.
class AirConditioner : public Device
{
public:
    AirConditioner(
        std::string id,
        std::string name,
        std::string roomName,
        double power
    );

    void updateParam(int value) override;

private:
    double powerForTemp(int temp) const;
};

#endif
