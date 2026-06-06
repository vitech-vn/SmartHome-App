# 📐 Quy Ước Cấu Trúc Dữ Liệu & Giao Tiếp (Interface Contract)

> **Mục đích:** File này định nghĩa các quy chuẩn chung về cấu trúc thư mục, kiểu dữ liệu, và luồng tín hiệu (Signals/Slots) giữa Frontend (UI) và Backend (Logic). Tất cả thành viên bắt buộc phải tuân thủ để code độc lập không bị xung đột.

---

## 📁 1. Quy Định Cấu Trúc Thư Mục Dự Án (Qt Creator)

Mọi người tạo file đúng vị trí quy định để tránh lỗi đường dẫn khi `#include`:

```text
SmartHomeProject/
│
├── SmartHomeProject.pro   <-- File cấu hình tổng (Thêm dòng: QT += charts)
├── DataStructures.h       <-- Định nghĩa Struct dùng chung (Cả team dùng)
│
├── Backend/               <-- Nơi làm việc của A và B
│   ├── Device.h / Device.cpp
│   ├── Light.h / Light.cpp
│   ├── Fan.h / Fan.cpp
│   ├── AirConditioner.h / AirConditioner.cpp
│   └── SmartHomeManager.h / SmartHomeManager.cpp
│
├── Simulator/             <-- Nơi làm việc của C
│   └── SimulationEngine.h / SimulationEngine.cpp
│
└── Frontend/              <-- Nơi làm việc của D
    ├── MainWindow.h / MainWindow.cpp / MainWindow.ui
    └── CustomChart.h / CustomChart.cpp
