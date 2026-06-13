cmake_minimum_required(VERSION 3.16)

project(SmartHome VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appSmartHome
    main.cpp
    backend.h
    backend.cpp
    DataStructures.h

    Backend/Device.h
    Backend/Device.cpp
    Backend/Light.h
    Backend/Light.cpp
    Backend/Fan.h
    Backend/Fan.cpp
    Backend/AirConditioner.h
    Backend/AirConditioner.cpp
    Backend/TV.h
    Backend/TV.cpp
    Backend/Fridge.h
    Backend/Fridge.cpp
    Backend/WaterHeater.h
    Backend/WaterHeater.cpp
    Backend/WashingMachine.h
    Backend/WashingMachine.cpp
    Backend/Microwave.h
    Backend/Microwave.cpp
    Backend/RiceCooker.h
    Backend/RiceCooker.cpp
    Backend/Curtain.h
    Backend/Curtain.cpp
    Backend/EnergyTracker.h
    Backend/EnergyTracker.cpp
    Backend/AlertSystem.h
    Backend/AlertSystem.cpp
    Backend/SmartHomeManager.h
    Backend/SmartHomeManager.cpp

    Simulator/SimulationEngine.h
    Simulator/SimulationEngine.cpp
)

qt_add_qml_module(appSmartHome
    URI SmartHome
    VERSION 1.0
    QML_FILES
        Main.qml
)

target_include_directories(appSmartHome PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(appSmartHome PRIVATE Qt6::Quick)
