#include "AirConditioner.h"

AirConditioner::AirConditioner(
    std::string id,
    std::string name,
    std::string roomName,
    double power
)
    : Device(id, name, roomName, DEVICE_AC, power)
{
    extraParam   = 24;                  // mặc định 24 độ
    currentPower = powerForTemp(24);
}

// 16 độ -> 100% công suất ; 30 độ -> 40% công suất (nội suy tuyến tính)
double AirConditioner::powerForTemp(int temp) const
{
    double t = (double)(MAX_AC_TEMP - temp)
             / (double)(MAX_AC_TEMP - MIN_AC_TEMP);
    double factor = 0.4 + 0.6 * t;
    return ratedPower * factor;
}

void AirConditioner::updateParam(int value)
{
    if (value < MIN_AC_TEMP) value = MIN_AC_TEMP;
    if (value > MAX_AC_TEMP) value = MAX_AC_TEMP;

    extraParam   = value;
    currentPower = powerForTemp(value);
}
