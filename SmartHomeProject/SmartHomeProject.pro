QT += core gui widgets
CONFIG += c++17
TEMPLATE = app
TARGET = SmartHomeProject

SOURCES += \
    main.cpp \
    Backend/Device.cpp \
    Backend/Light.cpp \
    Backend/Fan.cpp \
    Backend/AirConditioner.cpp \
    Backend/TV.cpp \
    Backend/Fridge.cpp \
    Backend/WaterHeater.cpp \
    Backend/WashingMachine.cpp \
    Backend/Microwave.cpp \
    Backend/RiceCooker.cpp \
    Backend/Curtain.cpp \
    Backend/EnergyTracker.cpp \
    Backend/AlertSystem.cpp \
    Backend/SmartHomeManager.cpp \
    Simulator/SimulationEngine.cpp

HEADERS += \
    DataStructures.h \
    Backend/Device.h \
    Backend/Light.h \
    Backend/Fan.h \
    Backend/AirConditioner.h \
    Backend/TV.h \
    Backend/Fridge.h \
    Backend/WaterHeater.h \
    Backend/WashingMachine.h \
    Backend/Microwave.h \
    Backend/RiceCooker.h \
    Backend/Curtain.h \
    Backend/EnergyTracker.h \
    Backend/AlertSystem.h \
    Backend/SmartHomeManager.h \
    Simulator/SimulationEngine.h
