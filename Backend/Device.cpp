#include "Device.h"

Device::Device(const std::string &id,
               const std::string &name,
               const std::string &roomName,
               const std::string &type,
               double ratedPower)
{
    this->ratedPower = ratedPower;

    info.id = id;
    info.name = name;
    info.roomName = roomName;
    info.type = type;

    info.isOn = false;
    info.currentPower = 0.0;
    info.totalConsumption = 0.0;
    info.extraParam = 0;
    info.runningHours = 0.0;
    info.currentSessionHours = 0.0;
}

Device::~Device()
{
}

void Device::turnOn()
{
    info.isOn = true;
    info.currentPower = ratedPower;
}

void Device::turnOff()
{
    info.isOn = false;
    info.currentPower = 0.0;
    info.currentSessionHours = 0.0;
}

void Device::updateParam(int value)
{
    info.extraParam = value;
}

double Device::updateEnergy(double deltaHours)
{
    if (!info.isOn)
    {
        return 0.0;
    }

    double addedKWh = (info.currentPower * deltaHours) / 1000.0;

    info.totalConsumption += addedKWh;
    info.runningHours += deltaHours;
    info.currentSessionHours += deltaHours;

    return addedKWh;
}

DeviceInfo Device::getInfo() const
{
    return info;
}

std::string Device::getId() const
{
    return info.id;
}

std::string Device::getName() const
{
    return info.name;
}

bool Device::isDeviceOn() const
{
    return info.isOn;
}

double Device::getCurrentPower() const
{
    return info.currentPower;
}

double Device::getTotalConsumption() const
{
    return info.totalConsumption;
}
