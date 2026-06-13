PHAN DA GHEP THEM
- DataStructures.h: bo sung DeviceInfo, HomeSummary, EnergyHistory, AlertInfo va cac hang so canh bao.
- Backend/AlertSystem.h, AlertSystem.cpp: tach rieng he thong canh bao qua tai va quen tat thiet bi.
- Backend/EnergyTracker.h, EnergyTracker.cpp: tach rieng tinh dien nang va chi phi.
- Backend/SmartHomeManager.h, SmartHomeManager.cpp: goi EnergyTracker + AlertSystem, phat signal canh bao.
- Simulator/SimulationEngine.h, SimulationEngine.cpp: dung QTimer phat sig_timeTick(0.5) moi 1 giay.
- main.cpp: file test bang Application Output, chua phai main UI cuoi cung.

CACH TEST
1. Mo SmartHomeProject.pro bang Qt Creator.
2. Build -> Run qmake.
3. Build -> Clean Project.
4. Build -> Rebuild Project.
5. Run.

KET QUA MONG MUON
- Tong cong suat AC + TV = 1320W.
- Moi tick tang 0.66 kWh.
- Sau khoang 10 tick tong dien = 6.6 kWh.
- Sau hon 4 gio mo phong hien canh bao quen tat.

LUU Y
- File main.cpp hien tai chi de test Simulation Engine, Energy Tracking va AlertSystem.
- Khi ghep UI, thay cac connect qDebug bang slot cua MainWindow.
