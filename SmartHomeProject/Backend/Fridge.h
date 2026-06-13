#ifndef FRIDGE_H
#define FRIDGE_H

#include "Device.h"

// Tủ lạnh: không có tham số điều chỉnh, công suất cố định.
class Fridge : public Device
{
public:
    Fridge(
        std::string id,
        std::string name,
        std::string roomName,
        double power
    );

    void updateParam(int value) override;
};

#endif
