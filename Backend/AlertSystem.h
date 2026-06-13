#ifndef ALERTSYSTEM_H
#define ALERTSYSTEM_H

#include "../DataStructures.h"
#include "Device.h"

#include <map>
#include <set>
#include <string>
#include <vector>

class AlertSystem
{
private:
    double overloadLimit;
    double deviceOverTimeLimit;
    double reminderIntervalHours;

    std::set<std::string> activeAlertKeys;
    std::map<std::string, double> lastDeviceAlertHour;

    bool isAlertActive(const std::string &key) const;
    void markAlertActive(const std::string &key);
    void clearAlert(const std::string &key);

    bool shouldSendDeviceReminder(const std::string &key, double currentSessionHours);

    AlertInfo createOverloadAlert(double currentPower) const;
    AlertInfo createForgottenDeviceAlert(const DeviceInfo &deviceInfo) const;

public:
    AlertSystem(double overloadLimit = MAX_HOUSE_POWER,
                double deviceOverTimeLimit = FORGOTTEN_TIME_LIMIT,
                double reminderIntervalHours = 1.0);

    // Overload alert is sent once when overload starts, then reset after power returns to normal.
    std::vector<AlertInfo> checkOverload(double totalPower);

    // Device overtime alert is sent when the device first exceeds the limit,
    // then updated again after each reminderIntervalHours while the device remains on.
    std::vector<AlertInfo> checkDevicesOverTime(const std::vector<Device*> &devices);

    void clearDeviceAlerts(const std::string &deviceId);
    void reset();

    double getOverloadLimit() const;
    double getDeviceOverTimeLimit() const;
    double getReminderIntervalHours() const;

    void setOverloadLimit(double limit);
    void setDeviceOverTimeLimit(double limit);
    void setReminderIntervalHours(double intervalHours);
};

#endif // ALERTSYSTEM_H
