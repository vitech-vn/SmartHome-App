#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <string>
#include <vector>
#include <QDateTime>

// =========================
// System constants
// =========================
const double MAX_HOUSE_POWER = 5000.0;          // W
const double FORGOTTEN_TIME_LIMIT = 4.0;        // simulated hours
const double DEFAULT_ELECTRICITY_PRICE = 3000.0; // VND/kWh

const int MIN_AC_TEMP = 16;
const int MAX_AC_TEMP = 30;

// =========================
// Device type constants
// =========================
const std::string DEVICE_LIGHT = "LIGHT";
const std::string DEVICE_FAN = "FAN";
const std::string DEVICE_AC = "AC";
const std::string DEVICE_TV = "TV";
const std::string DEVICE_FRIDGE = "FRIDGE";
const std::string DEVICE_WASHING_MACHINE = "WASHING_MACHINE";
const std::string DEVICE_WATER_HEATER = "WATER_HEATER";
const std::string DEVICE_MICROWAVE = "MICROWAVE";
const std::string DEVICE_RICE_COOKER = "RICE_COOKER";
const std::string DEVICE_CURTAIN = "CURTAIN";

// =========================
// Alert constants
// =========================
const std::string ALERT_OVERLOAD = "OVERLOAD";
const std::string ALERT_DEVICE_OVERTIME = "DEVICE_OVERTIME";
const std::string ALERT_DEVICE_ERROR = "DEVICE_ERROR";

const std::string ALERT_LEVEL_INFO = "INFO";
const std::string ALERT_LEVEL_WARNING = "WARNING";
const std::string ALERT_LEVEL_CRITICAL = "CRITICAL";

// =========================
// Shared structs
// =========================
struct DeviceInfo
{
    std::string id;
    std::string name;
    std::string roomName;
    std::string type;

    bool isOn;

    double currentPower;        // W
    double ratedPower;          // W
    double totalConsumption;    // kWh

    int extraParam;             // brightness, speed, temperature, volume, ...

    double runningHours;        // total simulated hours
    double currentSessionHours; // continuous simulated hours since turn-on
};

struct HomeSummary
{
    int totalDevices;
    int activeDevices;

    double totalCurrentPower; // W
    double totalEnergyUsed;   // kWh
    double totalCost;         // VND
    double electricityPrice;  // VND/kWh

    int warningDevices;
};

struct EnergyHistory
{
    // index 0 = latest simulated hour
    std::vector<double> hourlyConsumption;
};

struct AlertInfo
{
    std::string type;
    std::string level;
    std::string title;
    std::string message;
    std::string deviceId;
    std::string deviceName;
    QDateTime timestamp;
    bool isCritical;
};

#endif // DATASTRUCTURES_H
