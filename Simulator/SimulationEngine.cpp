#include "SimulationEngine.h"

SimulationEngine::SimulationEngine(QObject *parent)
    : QObject(parent)
{
    timer = new QTimer(this);
    currentTime = 0.0;
    tickStep = 0.5; // 1 real second = 0.5 simulated hour
    running = false;

    connect(timer, &QTimer::timeout,
            this, &SimulationEngine::onTimeout);
}

void SimulationEngine::start()
{
    running = true;
    timer->start(1000);
}

void SimulationEngine::stop()
{
    running = false;
    timer->stop();
}

void SimulationEngine::setTickStep(double step)
{
    tickStep = step;
}

double SimulationEngine::getCurrentTime() const
{
    return currentTime;
}

bool SimulationEngine::isRunning() const
{
    return running;
}

void SimulationEngine::onTimeout()
{
    currentTime += tickStep;
    emit sig_timeTick(tickStep);
}
