#ifndef SMARTHOMEMANAGER_H
#define SMARTHOMEMANAGER_H

#include <QObject>
#include <vector>
#include <string>

#include "../DataStructures.h"
#include "Device.h"
#include "EnergyTracker.h"
#include "AlertSystem.h"

class SmartHomeManager : public QObject
{
    Q_OBJECT

private:
    std::vector<Device*> devices;

    EnergyTracker energyTracker;
    AlertSystem alertSystem;
    EnergyHistory energyHistory;

    double currentHourConsumption;
    double hourCounter;

    Device* findDeviceById(const std::string &id);
    HomeSummary buildHomeSummary() const;

public:
    explicit SmartHomeManager(QObject *parent = nullptr);
    ~SmartHomeManager();

    void addDevice(Device *device);
    std::vector<DeviceInfo> getAllDevicesInfo() const;
    HomeSummary getHomeSummary() const;
    EnergyHistory getEnergyHistory() const;

signals:
    void sig_deviceStateChanged(const DeviceInfo &updatedDevice);
    void sig_deviceListChanged(const std::vector<DeviceInfo> &devices);
    void sig_summaryUpdated(const HomeSummary &summary);
    void sig_energyHistoryReady(const std::vector<double> &hourlyData);

    // Alert signals: keep both detailed AlertInfo and simple signals for UI compatibility
    void sig_alertRaised(const AlertInfo &alert);
    void sig_alertOverload(double currentTotalPower, double maxThreshold);
    void sig_alertForgottenDevice(const std::string &deviceName, double hoursRunning);

public slots:
    void slot_handleTurnOnDevice(const std::string &id);
    void slot_handleTurnOffDevice(const std::string &id);
    void slot_handleUpdateDeviceParam(const std::string &id, int value);

    void slot_updateSimulation(double deltaHours);
};

#endif // SMARTHOMEMANAGER_H
