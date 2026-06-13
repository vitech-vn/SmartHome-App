#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include <QString>

#include <vector>

#include "DataStructures.h"
#include "Backend/SmartHomeManager.h"
#include "Simulator/SimulationEngine.h"

class Backend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList devices READ devices NOTIFY devicesChanged)
    Q_PROPERTY(QVariantList chartData READ chartData NOTIFY chartDataChanged)
    Q_PROPERTY(QVariantList alerts READ alerts NOTIFY alertsChanged)

    Q_PROPERTY(int totalDevices READ totalDevices NOTIFY summaryChanged)
    Q_PROPERTY(int activeDevices READ activeDevices NOTIFY summaryChanged)
    Q_PROPERTY(int warningDevices READ warningDevices NOTIFY summaryChanged)
    Q_PROPERTY(double totalCurrentPower READ totalCurrentPower NOTIFY summaryChanged)
    Q_PROPERTY(double totalEnergyUsed READ totalEnergyUsed NOTIFY summaryChanged)
    Q_PROPERTY(double totalCost READ totalCost NOTIFY summaryChanged)
    Q_PROPERTY(double electricityPrice READ electricityPrice NOTIFY summaryChanged)

    Q_PROPERTY(bool running READ running NOTIFY runningChanged)

public:
    explicit Backend(QObject *parent = nullptr);

    QVariantList devices() const;
    QVariantList chartData() const;
    QVariantList alerts() const;

    int totalDevices() const;
    int activeDevices() const;
    int warningDevices() const;
    double totalCurrentPower() const;
    double totalEnergyUsed() const;
    double totalCost() const;
    double electricityPrice() const;
    bool running() const;

    Q_INVOKABLE void startSimulation();
    Q_INVOKABLE void stopSimulation();
    Q_INVOKABLE void toggleSimulation();

    Q_INVOKABLE void turnOnDevice(const QString &id);
    Q_INVOKABLE void turnOffDevice(const QString &id);
    Q_INVOKABLE void toggleDevice(const QString &id);
    Q_INVOKABLE void updateDeviceParam(const QString &id, int value);
    Q_INVOKABLE void clearAlerts();

signals:
    void devicesChanged();
    void chartDataChanged();
    void alertsChanged();
    void summaryChanged();
    void runningChanged();

private slots:
    void slot_updateDeviceList(const std::vector<DeviceInfo> &devices);
    void slot_updateDeviceState(const DeviceInfo &device);
    void slot_updateSummary(const HomeSummary &summary);
    void slot_updateEnergyChart(const std::vector<double> &hourlyData);
    void slot_receiveAlert(const AlertInfo &alert);

private:
    SmartHomeManager homeManager;
    SimulationEngine simulator;

    QVariantList m_devices;
    QVariantList m_chartData;
    QVariantList m_alerts;
    HomeSummary m_summary;

    void setupConnections();
    void setupInitialDevices();
    void refreshDevices();
    void refreshSummary();
    void refreshChart();

    QVariantMap deviceInfoToMap(const DeviceInfo &info) const;
    QVariantMap alertInfoToMap(const AlertInfo &alert) const;
};

#endif // BACKEND_H
