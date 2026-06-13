#ifndef ENERGY_TRACKER_H
#define ENERGY_TRACKER_H

#include <vector>

#include "../Data/DataStructures.h"

class EnergyTracker
{
private:

    double totalEnergy;
    double totalCost;

    double electricityPrice;

    EnergyHistory history;

public:

    EnergyTracker();

    //--------------------------------
    // cập nhật dữ liệu
    //--------------------------------

    void update(
        const std::vector<DeviceInfo>& devices
    );

    //--------------------------------
    // reset
    //--------------------------------

    void reset();

    //--------------------------------
    // getters
    //--------------------------------

    double getTotalEnergy() const;

    double getTotalCost() const;

    double getElectricityPrice() const;

    EnergyHistory getHistory() const;

    //--------------------------------
    // cấu hình
    //--------------------------------

    void setElectricityPrice(
        double price
    );
};

#endif
