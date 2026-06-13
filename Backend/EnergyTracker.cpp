#include "EnergyTracker.h"

EnergyTracker::EnergyTracker(double electricityPrice)
{
    this->electricityPrice = electricityPrice;
    totalEnergy = 0.0;
    totalCost = 0.0;
}

double EnergyTracker::update(const std::vector<Device*> &devices, double deltaHours)
{
    double addedEnergyThisTick = 0.0;

    for (Device *device : devices)
    {
        if (device != nullptr)
        {
            addedEnergyThisTick += device->updateEnergy(deltaHours);
        }
    }

    totalEnergy += addedEnergyThisTick;
    totalCost = totalEnergy * electricityPrice;

    return addedEnergyThisTick;
}

void EnergyTracker::reset()
{
    totalEnergy = 0.0;
    totalCost = 0.0;
}

void EnergyTracker::setElectricityPrice(double price)
{
    electricityPrice = price;
    totalCost = totalEnergy * electricityPrice;
}

double EnergyTracker::getTotalEnergy() const
{
    return totalEnergy;
}

double EnergyTracker::getTotalCost() const
{
    return totalCost;
}

double EnergyTracker::getElectricityPrice() const
{
    return electricityPrice;
}
