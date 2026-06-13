#ifndef DEVICE_H
#define DEVICE_H


#include <string>

#include "../Data/DataStructures.h"


class Device
{


protected:


    std::string id;


    std::string name;


    std::string roomName;


    std::string type;



    bool isOn;



    double currentPower;


    double totalConsumption;


    int extraParam;


    double runningHours;


    double currentSessionHours;



public:


    Device(
        std::string id,
        std::string name,
        std::string roomName,
        std::string type,
        double power
    );


    virtual ~Device();



    // bật thiết bị

    virtual void turnOn();



    // tắt thiết bị

    virtual void turnOff();



    // cập nhật điện năng

    virtual void updateEnergy(
        double deltaHours
    );



    // thay đổi tham số

    virtual void updateParam(
        int value
    );



    // trả dữ liệu cho UI

    virtual DeviceInfo getInfo() const;



    std::string getId() const;



    bool getStatus() const;



};



#endif
