#include <QApplication>
#include <QDebug>
#include <QTimer>

#include "Backend/SmartHomeManager.h"
#include "Backend/AirConditioner.h"
#include "Backend/TV.h"
#include "Backend/WaterHeater.h"
#include "Backend/Microwave.h"
#include "Backend/RiceCooker.h"
#include "Simulator/SimulationEngine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SmartHomeManager homeManager;
    SimulationEngine simulator;

    homeManager.addDevice(new AirConditioner("R1_AC_01", "Dieu hoa phong khach", "Phong khach"));
    homeManager.addDevice(new TV("R1_TV_01", "Tivi phong khach", "Phong khach"));

    QObject::connect(&simulator, &SimulationEngine::sig_timeTick,
                     &homeManager, &SmartHomeManager::slot_updateSimulation);

    QObject::connect(&homeManager, &SmartHomeManager::sig_summaryUpdated,
                     [](const HomeSummary &summary)
    {
        qDebug() << "Tong cong suat:" << summary.totalCurrentPower << "W"
                 << "| Tong dien:" << summary.totalEnergyUsed << "kWh"
                 << "| Tien dien:" << summary.totalCost << "VND"
                 << "| Dang bat:" << summary.activeDevices << "/" << summary.totalDevices
                 << "| Canh bao:" << summary.warningDevices;
    });

    QObject::connect(&homeManager, &SmartHomeManager::sig_energyHistoryReady,
                     [](const std::vector<double> &hourlyData)
    {
        if (!hourlyData.empty())
        {
            qDebug() << "Cap nhat bieu do, gio gan nhat:" << hourlyData[0] << "kWh";
        }
    });

    QObject::connect(&homeManager, &SmartHomeManager::sig_alertRaised,
                     [](const AlertInfo &alert)
    {
        qDebug() << "ALERT:" << QString::fromStdString(alert.title)
                 << "-" << QString::fromStdString(alert.message);
    });

    QObject::connect(&homeManager, &SmartHomeManager::sig_alertOverload,
                     [](double currentTotalPower, double maxThreshold)
    {
        qDebug() << "CANH BAO QUA TAI:" << currentTotalPower << "/" << maxThreshold << "W";
    });

    QObject::connect(&homeManager, &SmartHomeManager::sig_alertForgottenDevice,
                     [](const std::string &deviceName, double hoursRunning)
    {
        qDebug() << "CANH BAO QUEN TAT:"
                 << QString::fromStdString(deviceName)
                 << "- da chay" << hoursRunning << "gio";
    });

    homeManager.slot_handleTurnOnDevice("R1_AC_01");
    homeManager.slot_handleTurnOnDevice("R1_TV_01");

    simulator.start();

    // Run for about 11 real seconds = about 5 simulated hours
    QTimer::singleShot(11000, &app, &QApplication::quit);

    return app.exec();
}
