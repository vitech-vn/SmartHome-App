#include "SmartHomeManager.h"

SmartHomeManager::SmartHomeManager()
{

}

SmartHomeManager::~SmartHomeManager()
{
    for(Device* d : devices)
    {
        delete d;
    }
}

// Add Device
void SmartHomeManager::addDevice(
    Device* device
)
{
    devices.push_back(device);
}

// Get Device
Device*
SmartHomeManager::getDevice(
    const std::string& id
)
{
    for(Device* d : devices)
    {
        if(d->getId() == id)
            return d;
    }

    return nullptr;
}

//Get All Devices Info
std::vector<DeviceInfo>
SmartHomeManager::getAllDevicesInfo() const
{
    std::vector<DeviceInfo> result;

    for(Device* d : devices)
    {
        result.push_back(
            d->getInfo()
        );
    }

    return result;
}

//Turn On Device
bool
SmartHomeManager::turnOnDevice(
    const std::string& id
)
{
    Device* d = getDevice(id);

    if(d == nullptr)
        return false;

    d->turnOn();

    return true;
}

//Turn Off Device
bool
SmartHomeManager::turnOffDevice(
    const std::string& id
)
{
    Device* d = getDevice(id);

    if(d == nullptr)
        return false;

    d->turnOff();

    return true;
}

//Update Param
bool
SmartHomeManager::updateDeviceParam(
    const std::string& id,
    int value
)
{
    Device* d = getDevice(id);

    if(d == nullptr)
        return false;

    d->updateParam(value);

    return true;
}

//Simulation Tick
void
SmartHomeManager::updateAll(
    double deltaHours
)
{
    for(Device* d : devices)
    {
        d->updateEnergy(
            deltaHours
        );
    }
}

//GetHomeSummary
HomeSummary
SmartHomeManager::getHomeSummary() const
{
    HomeSummary s;

    s.totalCurrentPower = 0;
    s.totalEnergyUsed = 0;
    s.totalCost = 0;

    s.totalDevices = devices.size();
    s.activeDevices = 0;
    s.warningDevices = 0;

    for(Device* d : devices)
    {
        DeviceInfo info =
            d->getInfo();

        if(info.isOn)
        {
            s.activeDevices++;
            s.totalCurrentPower +=
                info.currentPower;
        }

        s.totalEnergyUsed +=
            info.totalConsumption;

        if(info.currentSessionHours >
           FORGOTTEN_TIME_LIMIT)
        {
            s.warningDevices++;
        }
    }

    //------------------------------------------------
    // Ví dụ:
    // 3000 VND/kWh
    //------------------------------------------------

    s.totalCost =
        s.totalEnergyUsed
        * 3000;

    return s;
}
