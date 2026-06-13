#ifndef RICE_COOKER_H
#define RICE_COOKER_H

#include "Device.h"

// Nồi cơm điện: không có tham số điều chỉnh, công suất cố định.
class RiceCooker : public Device
{
public:
    RiceCooker(
        std::string id,
        std::string name,
        std::string roomName,
        double power
    );

    void updateParam(int value) override;
};

#endif
