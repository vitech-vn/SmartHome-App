#ifndef SMART_HOME_MANAGER_H
#define SMART_HOME_MANAGER_H

#include <vector>
#include <string>

#include "Device.h"
#include "DataStructures.h"
#include "EnergyTracker.h"

class SmartHomeManager
{
private:

    std::vector<Device*> devices;
    EnergyTracker energyTracker;

public:

    SmartHomeManager();

    ~SmartHomeManager();

    //-----------------------------------
    // Device Management
    //-----------------------------------

    void addDevice(Device* device);

    Device* getDevice(
        const std::string& id
    );

    std::vector<DeviceInfo>
    getAllDevicesInfo() const;

    //-----------------------------------
    // Device Control
    //-----------------------------------

    bool turnOnDevice(
        const std::string& id
    );

    bool turnOffDevice(
        const std::string& id
    );

    bool updateDeviceParam(
        const std::string& id,
        int value
    );

    //-----------------------------------
    // Simulation
    //-----------------------------------

    void updateAll(
        double deltaHours
    );

    //-----------------------------------
    // Dashboard
    //-----------------------------------

    HomeSummary
    getHomeSummary() const;

};

#endif
