#ifndef ALERTSYSTEM_H
#define ALERTSYSTEM_H

#include "../DataStructures.h"
#include "Device.h"
#include <vector>

class AlertSystem
{
private:
    double overloadLimit;
    double deviceOverTimeLimit;

    AlertInfo createOverloadAlert(double currentPower) const;
    AlertInfo createForgottenDeviceAlert(const DeviceInfo &deviceInfo) const;

public:
    AlertSystem(double overloadLimit = MAX_HOUSE_POWER,
                double deviceOverTimeLimit = FORGOTTEN_TIME_LIMIT);

    bool checkOverload(double totalPower) const;
    std::vector<AlertInfo> checkDevicesOverTime(const std::vector<Device*> &devices) const;

    double getOverloadLimit() const;
    double getDeviceOverTimeLimit() const;

    void setOverloadLimit(double limit);
    void setDeviceOverTimeLimit(double limit);
};

#endif // ALERTSYSTEM_H
