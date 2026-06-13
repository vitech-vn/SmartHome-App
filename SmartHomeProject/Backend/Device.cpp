#include "Device.h"



Device::Device(
    std::string id,
    std::string name,
    std::string roomName,
    std::string type,
    double power

)

{

this->id=id;

this->name=name;

this->roomName=roomName;

this->type=type;


currentPower=power;

ratedPower=power;


isOn=false;


totalConsumption=0;


extraParam=0;


runningHours=0;


currentSessionHours=0;


}



Device::~Device()
{

}



void Device::turnOn()

{

isOn=true;

}



void Device::turnOff()

{

isOn=false;

currentSessionHours=0;

}



void Device::updateEnergy(double deltaHours)

{


if(isOn)

{

    double kwh =
    currentPower * deltaHours /1000.0;



    totalConsumption += kwh;


    runningHours += deltaHours;


    currentSessionHours += deltaHours;

}


}



void Device::updateParam(int value)

{

extraParam=value;

}



DeviceInfo Device::getInfo() const

{

DeviceInfo info;


info.id=id;

info.name=name;

info.roomName=roomName;

info.type=type;


info.isOn=isOn;


info.currentPower=currentPower;


info.totalConsumption=
totalConsumption;


info.extraParam=
extraParam;


info.runningHours=
runningHours;


info.currentSessionHours=
currentSessionHours;



return info;

}



std::string Device::getId() const

{

return id;

}



bool Device::getStatus() const

{

return isOn;

}
