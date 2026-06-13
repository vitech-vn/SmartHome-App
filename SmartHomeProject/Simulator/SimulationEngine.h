#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include <QObject>
#include <QTimer>

class SimulationEngine : public QObject
{
    Q_OBJECT

private:
    QTimer *timer;
    double currentTime;
    double tickStep;
    bool running;

public:
    explicit SimulationEngine(QObject *parent = nullptr);

    void start();
    void stop();
    void setTickStep(double step);

    double getCurrentTime() const;
    bool isRunning() const;

signals:
    void sig_timeTick(double deltaHours);

private slots:
    void onTimeout();
};

#endif // SIMULATIONENGINE_H
