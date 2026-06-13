#include "SmartHomeManager.h"

SmartHomeManager::SmartHomeManager(QObject *parent)
    : QObject(parent),
      energyTracker(DEFAULT_ELECTRICITY_PRICE),
      alertSystem(MAX_HOUSE_POWER, FORGOTTEN_TIME_LIMIT)
{
    energyHistory.hourlyConsumption = std::vector<double>(24, 0.0);
    currentHourConsumption = 0.0;
    hourCounter = 0.0;
}

SmartHomeManager::~SmartHomeManager()
{
    for (Device *device : devices)
    {
        delete device;
    }

    devices.clear();
}

void SmartHomeManager::addDevice(Device *device)
{
    if (device == nullptr)
    {
        return;
    }

    devices.push_back(device);

    emit sig_deviceStateChanged(device->getInfo());
    emit sig_deviceListChanged(getAllDevicesInfo());
    emit sig_summaryUpdated(buildHomeSummary());
    emit sig_energyHistoryReady(energyHistory.hourlyConsumption);
}

std::vector<DeviceInfo> SmartHomeManager::getAllDevicesInfo() const
{
    std::vector<DeviceInfo> result;

    for (Device *device : devices)
    {
        if (device != nullptr)
        {
            result.push_back(device->getInfo());
        }
    }

    return result;
}

HomeSummary SmartHomeManager::getHomeSummary() const
{
    return buildHomeSummary();
}

EnergyHistory SmartHomeManager::getEnergyHistory() const
{
    return energyHistory;
}

Device* SmartHomeManager::findDeviceById(const std::string &id)
{
    for (Device *device : devices)
    {
        if (device != nullptr && device->getId() == id)
        {
            return device;
        }
    }

    return nullptr;
}

void SmartHomeManager::slot_handleTurnOnDevice(const std::string &id)
{
    Device *device = findDeviceById(id);

    if (device == nullptr)
    {
        return;
    }

    device->turnOn();

    emit sig_deviceStateChanged(device->getInfo());
    emit sig_deviceListChanged(getAllDevicesInfo());

    HomeSummary summary = buildHomeSummary();

    if (alertSystem.checkOverload(summary.totalCurrentPower))
    {
        AlertInfo alert;
        alert.type = ALERT_OVERLOAD;
        alert.level = ALERT_LEVEL_CRITICAL;
        alert.title = "Canh bao qua tai cong suat";
        alert.message = "Tong cong suat hien tai vuot nguong cho phep.";
        alert.deviceId = "";
        alert.deviceName = "";
        alert.timestamp = QDateTime::currentDateTime();
        alert.isCritical = true;

        emit sig_alertRaised(alert);
        emit sig_alertOverload(summary.totalCurrentPower, alertSystem.getOverloadLimit());
    }

    emit sig_summaryUpdated(summary);
}

void SmartHomeManager::slot_handleTurnOffDevice(const std::string &id)
{
    Device *device = findDeviceById(id);

    if (device == nullptr)
    {
        return;
    }

    device->turnOff();

    emit sig_deviceStateChanged(device->getInfo());
    emit sig_deviceListChanged(getAllDevicesInfo());
    emit sig_summaryUpdated(buildHomeSummary());
}

void SmartHomeManager::slot_handleUpdateDeviceParam(const std::string &id, int value)
{
    Device *device = findDeviceById(id);

    if (device == nullptr)
    {
        return;
    }

    device->updateParam(value);

    emit sig_deviceStateChanged(device->getInfo());
    emit sig_deviceListChanged(getAllDevicesInfo());
    emit sig_summaryUpdated(buildHomeSummary());
}

void SmartHomeManager::slot_updateSimulation(double deltaHours)
{
    double addedEnergyThisTick = energyTracker.update(devices, deltaHours);

    for (Device *device : devices)
    {
        if (device != nullptr)
        {
            emit sig_deviceStateChanged(device->getInfo());
        }
    }

    currentHourConsumption += addedEnergyThisTick;
    hourCounter += deltaHours;

    if (hourCounter >= 1.0)
    {
        energyHistory.hourlyConsumption.insert(
            energyHistory.hourlyConsumption.begin(),
            currentHourConsumption
        );

        if (energyHistory.hourlyConsumption.size() > 24)
        {
            energyHistory.hourlyConsumption.pop_back();
        }

        currentHourConsumption = 0.0;
        hourCounter = 0.0;

        emit sig_energyHistoryReady(energyHistory.hourlyConsumption);
    }

    HomeSummary summary = buildHomeSummary();

    if (alertSystem.checkOverload(summary.totalCurrentPower))
    {
        AlertInfo alert;
        alert.type = ALERT_OVERLOAD;
        alert.level = ALERT_LEVEL_CRITICAL;
        alert.title = "Canh bao qua tai cong suat";
        alert.message = "Tong cong suat hien tai vuot nguong cho phep.";
        alert.deviceId = "";
        alert.deviceName = "";
        alert.timestamp = QDateTime::currentDateTime();
        alert.isCritical = true;

        emit sig_alertRaised(alert);
        emit sig_alertOverload(summary.totalCurrentPower, alertSystem.getOverloadLimit());
    }

    std::vector<AlertInfo> overtimeAlerts = alertSystem.checkDevicesOverTime(devices);

    for (const AlertInfo &alert : overtimeAlerts)
    {
        Device *device = findDeviceById(alert.deviceId);
        double hoursRunning = 0.0;

        if (device != nullptr)
        {
            hoursRunning = device->getInfo().currentSessionHours;
        }

        emit sig_alertRaised(alert);
        emit sig_alertForgottenDevice(alert.deviceName, hoursRunning);
    }

    emit sig_summaryUpdated(summary);
}

HomeSummary SmartHomeManager::buildHomeSummary() const
{
    HomeSummary summary;

    summary.totalDevices = static_cast<int>(devices.size());
    summary.activeDevices = 0;
    summary.totalCurrentPower = 0.0;
    summary.totalEnergyUsed = energyTracker.getTotalEnergy();
    summary.totalCost = energyTracker.getTotalCost();
    summary.electricityPrice = energyTracker.getElectricityPrice();
    summary.warningDevices = 0;

    for (Device *device : devices)
    {
        if (device == nullptr)
        {
            continue;
        }

        DeviceInfo info = device->getInfo();

        summary.totalCurrentPower += info.currentPower;

        if (info.isOn)
        {
            summary.activeDevices++;
        }

        if (info.isOn && info.currentSessionHours > alertSystem.getDeviceOverTimeLimit())
        {
            summary.warningDevices++;
        }
    }

    return summary;
}
