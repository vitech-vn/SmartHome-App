#include "AlertSystem.h"

#include <iomanip>
#include <sstream>

AlertSystem::AlertSystem(double overloadLimit,
                         double deviceOverTimeLimit,
                         double reminderIntervalHours)
{
    this->overloadLimit = overloadLimit;
    this->deviceOverTimeLimit = deviceOverTimeLimit;
    this->reminderIntervalHours = reminderIntervalHours;
}

bool AlertSystem::isAlertActive(const std::string &key) const
{
    return activeAlertKeys.find(key) != activeAlertKeys.end();
}

void AlertSystem::markAlertActive(const std::string &key)
{
    activeAlertKeys.insert(key);
}

void AlertSystem::clearAlert(const std::string &key)
{
    activeAlertKeys.erase(key);
    lastDeviceAlertHour.erase(key);
}

bool AlertSystem::shouldSendDeviceReminder(const std::string &key, double currentSessionHours)
{
    auto it = lastDeviceAlertHour.find(key);

    if (it == lastDeviceAlertHour.end())
    {
        lastDeviceAlertHour[key] = currentSessionHours;
        return true;
    }

    if (currentSessionHours - it->second >= reminderIntervalHours)
    {
        lastDeviceAlertHour[key] = currentSessionHours;
        return true;
    }

    return false;
}

std::vector<AlertInfo> AlertSystem::checkOverload(double totalPower)
{
    std::vector<AlertInfo> alerts;
    const std::string key = "OVERLOAD";

    if (totalPower > overloadLimit)
    {
        if (!isAlertActive(key))
        {
            alerts.push_back(createOverloadAlert(totalPower));
            markAlertActive(key);
        }
    }
    else
    {
        clearAlert(key);
    }

    return alerts;
}

std::vector<AlertInfo> AlertSystem::checkDevicesOverTime(const std::vector<Device*> &devices)
{
    std::vector<AlertInfo> alerts;

    for (Device *device : devices)
    {
        if (device == nullptr)
        {
            continue;
        }

        DeviceInfo info = device->getInfo();
        std::string key = "FORGOTTEN_" + info.id;

        if (info.isOn && info.currentSessionHours > deviceOverTimeLimit)
        {
            markAlertActive(key);

            if (shouldSendDeviceReminder(key, info.currentSessionHours))
            {
                alerts.push_back(createForgottenDeviceAlert(info));
            }
        }
        else
        {
            clearAlert(key);
        }
    }

    return alerts;
}

void AlertSystem::clearDeviceAlerts(const std::string &deviceId)
{
    clearAlert("FORGOTTEN_" + deviceId);
}

void AlertSystem::reset()
{
    activeAlertKeys.clear();
    lastDeviceAlertHour.clear();
}

double AlertSystem::getOverloadLimit() const
{
    return overloadLimit;
}

double AlertSystem::getDeviceOverTimeLimit() const
{
    return deviceOverTimeLimit;
}

double AlertSystem::getReminderIntervalHours() const
{
    return reminderIntervalHours;
}

void AlertSystem::setOverloadLimit(double limit)
{
    overloadLimit = limit;
    clearAlert("OVERLOAD");
}

void AlertSystem::setDeviceOverTimeLimit(double limit)
{
    deviceOverTimeLimit = limit;
    reset();
}

void AlertSystem::setReminderIntervalHours(double intervalHours)
{
    if (intervalHours > 0.0)
    {
        reminderIntervalHours = intervalHours;
        reset();
    }
}

AlertInfo AlertSystem::createOverloadAlert(double currentPower) const
{
    AlertInfo alert;

    alert.type = ALERT_OVERLOAD;
    alert.level = ALERT_LEVEL_CRITICAL;
    alert.title = "Canh bao qua tai cong suat";

    std::ostringstream oss;
    oss << "Tong cong suat hien tai la " << std::fixed << std::setprecision(0)
        << currentPower << " W, vuot gioi han " << overloadLimit
        << " W. Hay tat bot thiet bi cong suat lon.";

    alert.message = oss.str();
    alert.deviceId = "";
    alert.deviceName = "Toan bo he thong";
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
    oss << "Thiet bi " << deviceInfo.name << " da hoat dong lien tuc "
        << std::fixed << std::setprecision(1) << deviceInfo.currentSessionHours
        << " gio mo phong. Hay kiem tra va tat neu khong can su dung.";

    alert.message = oss.str();
    alert.deviceId = deviceInfo.id;
    alert.deviceName = deviceInfo.name;
    alert.timestamp = QDateTime::currentDateTime();
    alert.isCritical = false;

    return alert;
}
