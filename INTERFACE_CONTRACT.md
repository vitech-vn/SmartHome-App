# 📐 Smart Home System - Interface Contract

## Mục đích

Tài liệu này định nghĩa các quy chuẩn chung về:

* Cấu trúc dự án
* Kiểu dữ liệu dùng chung
* Luồng giao tiếp giữa UI và Backend
* Quy tắc tích hợp hệ thống

Mọi thành viên phải tuân thủ để đảm bảo các module có thể phát triển độc lập và tích hợp ổn định.

---

# 1. Cấu Trúc Dự Án

```text
SmartHomeProject/
│
├── SmartHomeProject.pro
├── DataStructures.h
│
├── Backend/
│   ├── Device.h / Device.cpp
│   ├── Light.h / Light.cpp
│   ├── Fan.h / Fan.cpp
│   ├── AirConditioner.h / AirConditioner.cpp
│   └── SmartHomeManager.h / SmartHomeManager.cpp
│
├── Simulator/
│   └── SimulationEngine.h / SimulationEngine.cpp
│
└── Frontend/
    ├── MainWindow.h
    ├── MainWindow.cpp
    ├── MainWindow.ui
    └── CustomChart.h / CustomChart.cpp
```

### Quy định

* Toàn bộ nhóm sử dụng chung `DataStructures.h`.
* Không tự ý thay đổi cấu trúc thư mục.
* File `.pro` phải khai báo:

```pro
QT += charts
```

---

# 2. Dữ Liệu Dùng Chung

## 2.1 Hằng Số Hệ Thống

```cpp
const double MAX_HOUSE_POWER = 5000.0;
const double FORGOTTEN_TIME_LIMIT = 4.0;

const int MIN_AC_TEMP = 16;
const int MAX_AC_TEMP = 30;
```

| Hằng số              | Ý nghĩa                                            |
| -------------------- | -------------------------------------------------- |
| MAX_HOUSE_POWER      | Ngưỡng công suất tối đa toàn hệ thống              |
| FORGOTTEN_TIME_LIMIT | Thời gian hoạt động liên tục để kích hoạt cảnh báo |
| MIN_AC_TEMP          | Nhiệt độ điều hòa tối thiểu                        |
| MAX_AC_TEMP          | Nhiệt độ điều hòa tối đa                           |

---

## 2.2 Cấu Trúc Thiết Bị

```cpp
struct DeviceInfo
{
    std::string id;
    std::string name;
    std::string roomName;
    std::string type;

    bool isOn;

    double currentPower;
    double totalConsumption;

    int extraParam;
};
```

### Quy ước

| Thuộc tính       | Mô tả                                        |
| ---------------- | -------------------------------------------- |
| id               | Mã thiết bị (`R1_LIGHT_01`, `R2_AC_01`, ...) |
| name             | Tên hiển thị                                 |
| roomName         | Phòng chứa thiết bị                          |
| type             | `LIGHT`, `FAN`, `AC`                         |
| isOn             | Trạng thái hoạt động                         |
| currentPower     | Công suất tức thời (W)                       |
| totalConsumption | Điện năng tích lũy (kWh)                     |
| extraParam       | Tốc độ quạt hoặc nhiệt độ AC                 |

---

## 2.3 Cấu Trúc Dashboard

```cpp
struct HomeSummary
{
    double totalCurrentPower;
    double totalEnergyUsed;
    double totalCost;

    int totalDevices;
    int activeDevices;
};
```

### Thông tin hiển thị

* Công suất hiện tại toàn nhà
* Tổng điện năng tiêu thụ
* Chi phí điện tạm tính
* Số lượng thiết bị
* Số lượng thiết bị đang hoạt động

---

# 3. Giao Tiếp UI ↔ Backend

## 3.1 Điều Khiển Thiết Bị

### UI → Backend

| Signal                       | Slot                                   | Chức năng        |
| ---------------------------- | -------------------------------------- | ---------------- |
| `requestTurnOn(id)`          | `slot_handleTurnOnDevice(id)`          | Bật thiết bị     |
| `requestTurnOff(id)`         | `slot_handleTurnOffDevice(id)`         | Tắt thiết bị     |
| `requestParamChange(id,val)` | `slot_handleUpdateDeviceParam(id,val)` | Cập nhật tham số |

---

## 3.2 Cập Nhật Giao Diện

### Backend → UI

```cpp
void sig_deviceStateChanged(
    const DeviceInfo& updatedDevice
);

void sig_summaryUpdated(
    const HomeSummary& summary
);

void sig_energyHistoryReady(
    const std::vector<double>& hourlyData
);
```

| Signal                 | Mục đích                     |
| ---------------------- | ---------------------------- |
| sig_deviceStateChanged | Cập nhật trạng thái thiết bị |
| sig_summaryUpdated     | Cập nhật Dashboard           |
| sig_energyHistoryReady | Cập nhật biểu đồ tiêu thụ    |

---

## 3.3 Cảnh Báo Hệ Thống

```cpp
void sig_alertOverload(
    double currentTotalPower,
    double maxThreshold
);

void sig_alertForgottenDevice(
    const std::string& deviceName,
    double hoursRunning
);
```

### Điều kiện kích hoạt

#### Quá tải hệ thống

```text
totalCurrentPower > MAX_HOUSE_POWER
```

#### Thiết bị bị quên tắt

```text
runningTime > FORGOTTEN_TIME_LIMIT
```

UI chịu trách nhiệm hiển thị Popup cảnh báo.

---

# 4. Engine Mô Phỏng Thời Gian

## Tỷ lệ thời gian

```text
1 giây thực = 0.5 giờ mô phỏng
```

## Tick hệ thống

```cpp
emit sig_timeTick(0.5);
```

Phát tín hiệu sau mỗi 1 giây thực.

---

## Cập Nhật Điện Năng

Đối với thiết bị đang hoạt động:

```cpp
isOn == true
```

Điện năng tăng thêm:

ΔA = P × Δt

Trong đó:

* P: Công suất hiện tại (W)
* Δt = 0.5 giờ
* ΔA: Điện năng tiêu thụ tăng thêm (Wh)

---

# 5. Quy Tắc Tích Hợp

## Không Can Thiệp Chéo

### Frontend

Không được:

* Thay đổi trạng thái logic thiết bị
* Tính toán điện năng
* Tính toán chi phí

### Backend

Không được:

* Can thiệp giao diện Qt
* Chỉnh sửa thành phần hiển thị

---

## Kết Nối Module

Mọi kết nối Signal/Slot được thực hiện tập trung tại:

```text
main.cpp
```

Ví dụ:

```cpp
QObject::connect(
    &uiWindow,
    &MainWindow::requestTurnOn,
    &homeManager,
    &SmartHomeManager::slot_handleTurnOnDevice
);
```

---

## Xử Lý Giá Trị Biên

Backend chịu trách nhiệm kiểm tra dữ liệu đầu vào.

Ví dụ đối với nhiệt độ điều hòa:

| Giá trị nhận | Giá trị sử dụng |
| ------------ | --------------- |
| < 16         | 16              |
| 16–30        | Giữ nguyên      |
| > 30         | 30              |

UI không cần xử lý giới hạn dữ liệu.

---

# 6. Phân Công Thành Viên

| Thành viên | Phạm vi phụ trách                         |
| ---------- | ----------------------------------------- |
| A (Leader) | Core Logic, SmartHomeManager, Integration |
| B          | Device Models (Light, Fan, AC)            |
| C          | Simulation Engine, Energy Tracking        |
| D          | UI, Dashboard, Charts, Alerts             |

---

## Quy Tắc Cuối Cùng

**DataStructures.h là hợp đồng dữ liệu của toàn dự án.**

Không thay đổi:

* Tên struct
* Tên biến
* Kiểu dữ liệu
* Tên signal/slot

trừ khi có sự thống nhất của toàn nhóm.
