#include "EnergyTracker.h"

//Constructor
EnergyTracker::EnergyTracker()
{
    totalEnergy = 0;
    totalCost = 0;

    electricityPrice = 3000;

    history.hourlyConsumption.resize(
        24,
        0
    );
}

//Update
void EnergyTracker::update(
    const std::vector<DeviceInfo>& devices
)
{
    totalEnergy = 0;

    for(const DeviceInfo& d : devices)
    {
        totalEnergy +=
            d.totalConsumption;
    }

    totalCost =
        totalEnergy
        * electricityPrice;
}

//SetPrice
void EnergyTracker::setElectricityPrice(
    double price
)
{
    electricityPrice = price;
}

//Getters
double
EnergyTracker::getTotalEnergy() const
{
    return totalEnergy;
}

double
EnergyTracker::getTotalCost() const
{
    return totalCost;
}

double
EnergyTracker::getElectricityPrice() const
{
    return electricityPrice;
}

EnergyHistory
EnergyTracker::getHistory() const
{
    return history;
}

//Reset
void EnergyTracker::reset()
{
    totalEnergy = 0;
    totalCost = 0;

    history.hourlyConsumption.assign(
        24,
        0
    );
}

//
