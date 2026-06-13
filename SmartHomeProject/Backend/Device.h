#ifndef DEVICE_H
#define DEVICE_H

#include "../DataStructures.h"
#include <string>

class Device
{
protected:
    DeviceInfo info;
    double ratedPower;

public:
    Device(const std::string &id,
           const std::string &name,
           const std::string &roomName,
           const std::string &type,
           double ratedPower);

    virtual ~Device();

    virtual void turnOn();
    virtual void turnOff();

    // value = brightness, speed, temperature, volume, mode, ... depending on device type
    virtual void updateParam(int value);

    // Returns added energy in this tick, unit: kWh
    virtual double updateEnergy(double deltaHours);

    DeviceInfo getInfo() const;
    std::string getId() const;
    std::string getName() const;

    bool isDeviceOn() const;
    double getCurrentPower() const;
    double getTotalConsumption() const;
};

#endif // DEVICE_H
