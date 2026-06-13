#include "AlertSystem.h"
#include <sstream>
#include <iomanip>

AlertSystem::AlertSystem(double overloadLimit, double deviceOverTimeLimit)
{
    this->overloadLimit = overloadLimit;
    this->deviceOverTimeLimit = deviceOverTimeLimit;
}

bool AlertSystem::checkOverload(double totalPower) const
{
    return totalPower > overloadLimit;
}

std::vector<AlertInfo> AlertSystem::checkDevicesOverTime(const std::vector<Device*> &devices) const
{
    std::vector<AlertInfo> alerts;

    for (Device *device : devices)
    {
        if (device == nullptr)
        {
            continue;
        }

        DeviceInfo info = device->getInfo();

        if (info.isOn && info.currentSessionHours > deviceOverTimeLimit)
        {
            alerts.push_back(createForgottenDeviceAlert(info));
        }
    }

    return alerts;
}

double AlertSystem::getOverloadLimit() const
{
    return overloadLimit;
}

double AlertSystem::getDeviceOverTimeLimit() const
{
    return deviceOverTimeLimit;
}

void AlertSystem::setOverloadLimit(double limit)
{
    overloadLimit = limit;
}

void AlertSystem::setDeviceOverTimeLimit(double limit)
{
    deviceOverTimeLimit = limit;
}

AlertInfo AlertSystem::createOverloadAlert(double currentPower) const
{
    AlertInfo alert;

    alert.type = ALERT_OVERLOAD;
    alert.level = ALERT_LEVEL_CRITICAL;
    alert.title = "Canh bao qua tai cong suat";

    std::ostringstream oss;
    oss << "Tong cong suat hien tai la " << std::fixed << std::setprecision(0)
        << currentPower << " W, vuot gioi han " << overloadLimit << " W.";

    alert.message = oss.str();
    alert.deviceId = "";
    alert.deviceName = "";
    alert.timestamp = QDateTime::currentDateTime();
    alert.isCritical = true;

    return alert;
}

AlertInfo AlertSystem::createForgottenDeviceAlert(const DeviceInfo &deviceInfo) const
{
    AlertInfo alert;

    alert.type = ALERT_DEVICE_OVERTIME;
    alert.level = ALERT_LEVEL_WARNING;
    alert.title = "Canh bao quen tat thiet bi";

    std::ostringstream oss;
    oss << "Thiet bi " << deviceInfo.name << " da chay lien tuc "
        << std::fixed << std::setprecision(1) << deviceInfo.currentSessionHours
        << " gio mo phong.";

    alert.message = oss.str();
    alert.deviceId = deviceInfo.id;
    alert.deviceName = deviceInfo.name;
    alert.timestamp = QDateTime::currentDateTime();
    alert.isCritical = false;

    return alert;
}
