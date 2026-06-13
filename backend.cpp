#include "backend.h"

#include "Backend/AirConditioner.h"
#include "Backend/TV.h"
#include "Backend/Light.h"
#include "Backend/Fan.h"
#include "Backend/WaterHeater.h"
#include "Backend/Microwave.h"
#include "Backend/RiceCooker.h"
#include "Backend/Fridge.h"
#include "Backend/WashingMachine.h"

#include <QDateTime>

Backend::Backend(QObject *parent)
    : QObject(parent)
{
    m_summary.totalDevices = 0;
    m_summary.activeDevices = 0;
    m_summary.totalCurrentPower = 0.0;
    m_summary.totalEnergyUsed = 0.0;
    m_summary.totalCost = 0.0;
    m_summary.electricityPrice = DEFAULT_ELECTRICITY_PRICE;
    m_summary.warningDevices = 0;

    setupConnections();
    setupInitialDevices();

    // Demo: bật sẵn điều hòa và tivi để biểu đồ/cảnh báo có dữ liệu ngay.
    homeManager.slot_handleTurnOnDevice("R1_AC_01");
    homeManager.slot_handleTurnOnDevice("R1_TV_01");

    refreshDevices();
    refreshSummary();
    refreshChart();

    startSimulation();
}

QVariantList Backend::devices() const
{
    return m_devices;
}

QVariantList Backend::chartData() const
{
    return m_chartData;
}

QVariantList Backend::alerts() const
{
    return m_alerts;
}

int Backend::totalDevices() const
{
    return m_summary.totalDevices;
}

int Backend::activeDevices() const
{
    return m_summary.activeDevices;
}

int Backend::warningDevices() const
{
    return m_summary.warningDevices;
}

double Backend::totalCurrentPower() const
{
    return m_summary.totalCurrentPower;
}

double Backend::totalEnergyUsed() const
{
    return m_summary.totalEnergyUsed;
}

double Backend::totalCost() const
{
    return m_summary.totalCost;
}

double Backend::electricityPrice() const
{
    return m_summary.electricityPrice;
}

bool Backend::running() const
{
    return simulator.isRunning();
}

void Backend::startSimulation()
{
    if (!simulator.isRunning())
    {
        simulator.start();
        emit runningChanged();
    }
}

void Backend::stopSimulation()
{
    if (simulator.isRunning())
    {
        simulator.stop();
        emit runningChanged();
    }
}

void Backend::toggleSimulation()
{
    if (simulator.isRunning())
    {
        stopSimulation();
    }
    else
    {
        startSimulation();
    }
}

void Backend::turnOnDevice(const QString &id)
{
    homeManager.slot_handleTurnOnDevice(id.toStdString());
}

void Backend::turnOffDevice(const QString &id)
{
    homeManager.slot_handleTurnOffDevice(id.toStdString());
}

void Backend::toggleDevice(const QString &id)
{
    for (const QVariant &item : m_devices)
    {
        QVariantMap map = item.toMap();
        if (map.value("id").toString() == id)
        {
            if (map.value("isOn").toBool())
            {
                turnOffDevice(id);
            }
            else
            {
                turnOnDevice(id);
            }
            return;
        }
    }
}

void Backend::updateDeviceParam(const QString &id, int value)
{
    homeManager.slot_handleUpdateDeviceParam(id.toStdString(), value);
}

void Backend::clearAlerts()
{
    m_alerts.clear();
    emit alertsChanged();
}

void Backend::slot_updateDeviceList(const std::vector<DeviceInfo> &devices)
{
    m_devices.clear();

    for (const DeviceInfo &info : devices)
    {
        m_devices.append(deviceInfoToMap(info));
    }

    emit devicesChanged();
}

void Backend::slot_updateDeviceState(const DeviceInfo &device)
{
    bool found = false;

    for (int i = 0; i < m_devices.size(); i++)
    {
        QVariantMap map = m_devices[i].toMap();

        if (map.value("id").toString().toStdString() == device.id)
        {
            m_devices[i] = deviceInfoToMap(device);
            found = true;
            break;
        }
    }

    if (!found)
    {
        m_devices.append(deviceInfoToMap(device));
    }

    emit devicesChanged();
}

void Backend::slot_updateSummary(const HomeSummary &summary)
{
    m_summary = summary;
    emit summaryChanged();
}

void Backend::slot_updateEnergyChart(const std::vector<double> &hourlyData)
{
    m_chartData.clear();

    // UI hiển thị từ giờ cũ hơn sang giờ gần nhất.
    for (int i = static_cast<int>(hourlyData.size()) - 1; i >= 0; i--)
    {
        QVariantMap item;
        item["hour"] = QString("-%1h").arg(i);
        item["value"] = hourlyData[static_cast<size_t>(i)];
        m_chartData.append(item);
    }

    emit chartDataChanged();
}

void Backend::slot_receiveAlert(const AlertInfo &alert)
{
    QVariantMap newAlert = alertInfoToMap(alert);

    // Neu cung mot canh bao da ton tai, cap nhat noi dung/thoi gian thay vi them trung dong.
    // Vi du: thiet bi chay qua lau se cap nhat tu 4.5h -> 5.5h -> 6.5h...
    QString newType = newAlert.value("type").toString();
    QString newDeviceId = newAlert.value("deviceId").toString();

    for (int i = 0; i < m_alerts.size(); i++)
    {
        QVariantMap oldAlert = m_alerts[i].toMap();

        if (oldAlert.value("type").toString() == newType &&
            oldAlert.value("deviceId").toString() == newDeviceId)
        {
            m_alerts[i] = newAlert;
            emit alertsChanged();
            return;
        }
    }

    m_alerts.prepend(newAlert);

    while (m_alerts.size() > 10)
    {
        m_alerts.removeLast();
    }

    emit alertsChanged();
}

void Backend::setupConnections()
{
    connect(&simulator, &SimulationEngine::sig_timeTick,
            &homeManager, &SmartHomeManager::slot_updateSimulation);

    connect(&homeManager, &SmartHomeManager::sig_deviceListChanged,
            this, &Backend::slot_updateDeviceList);

    connect(&homeManager, &SmartHomeManager::sig_deviceStateChanged,
            this, &Backend::slot_updateDeviceState);

    connect(&homeManager, &SmartHomeManager::sig_summaryUpdated,
            this, &Backend::slot_updateSummary);

    connect(&homeManager, &SmartHomeManager::sig_energyHistoryReady,
            this, &Backend::slot_updateEnergyChart);

    // Chỉ dùng một luồng cảnh báo chính để UI không bị trùng/thừa thông báo.
    connect(&homeManager, &SmartHomeManager::sig_alertRaised,
            this, &Backend::slot_receiveAlert);
}

void Backend::setupInitialDevices()
{
    homeManager.addDevice(new AirConditioner("R1_AC_01", "Dieu hoa phong khach", "Phong khach"));
    homeManager.addDevice(new TV("R1_TV_01", "Tivi phong khach", "Phong khach"));
    homeManager.addDevice(new Light("R1_LIGHT_01", "Den phong khach", "Phong khach"));
    homeManager.addDevice(new Fan("R2_FAN_01", "Quat phong ngu", "Phong ngu"));
    homeManager.addDevice(new Fridge("K1_FRIDGE_01", "Tu lanh", "Bep"));
    homeManager.addDevice(new WaterHeater("B1_HEATER_01", "May nuoc nong", "Phong tam"));
    homeManager.addDevice(new Microwave("K1_MICRO_01", "Lo vi song", "Bep"));
    homeManager.addDevice(new RiceCooker("K1_RICE_01", "Noi com dien", "Bep"));
    homeManager.addDevice(new WashingMachine("Y1_WASH_01", "May giat", "San sau"));
}

void Backend::refreshDevices()
{
    slot_updateDeviceList(homeManager.getAllDevicesInfo());
}

void Backend::refreshSummary()
{
    slot_updateSummary(homeManager.getHomeSummary());
}

void Backend::refreshChart()
{
    slot_updateEnergyChart(homeManager.getEnergyHistory().hourlyConsumption);
}

QVariantMap Backend::deviceInfoToMap(const DeviceInfo &info) const
{
    QVariantMap map;

    map["id"] = QString::fromStdString(info.id);
    map["name"] = QString::fromStdString(info.name);
    map["roomName"] = QString::fromStdString(info.roomName);
    map["type"] = QString::fromStdString(info.type);
    map["isOn"] = info.isOn;
    map["currentPower"] = info.currentPower;
    map["totalConsumption"] = info.totalConsumption;
    map["extraParam"] = info.extraParam;
    map["runningHours"] = info.runningHours;
    map["currentSessionHours"] = info.currentSessionHours;

    return map;
}

QVariantMap Backend::alertInfoToMap(const AlertInfo &alert) const
{
    QVariantMap map;

    map["type"] = QString::fromStdString(alert.type);
    map["level"] = QString::fromStdString(alert.level);
    map["title"] = QString::fromStdString(alert.title);
    map["message"] = QString::fromStdString(alert.message);
    map["deviceId"] = QString::fromStdString(alert.deviceId);
    map["deviceName"] = QString::fromStdString(alert.deviceName);
    map["timestamp"] = alert.timestamp.toString("HH:mm:ss");
    map["isCritical"] = alert.isCritical;

    return map;
}
