#ifndef ENERGYTRACKER_H
#define ENERGYTRACKER_H

#include <vector>
#include "Device.h"

class EnergyTracker
{
private:
    double totalEnergy;      // kWh
    double totalCost;        // VND
    double electricityPrice; // VND/kWh

public:
    explicit EnergyTracker(double electricityPrice = DEFAULT_ELECTRICITY_PRICE);

    // Update all devices and return added energy in this tick, unit: kWh
    double update(const std::vector<Device*> &devices, double deltaHours);

    void reset();
    void setElectricityPrice(double price);

    double getTotalEnergy() const;
    double getTotalCost() const;
    double getElectricityPrice() const;
};

#endif // ENERGYTRACKER_H
