# Smart Home System

## Interface Contract v1.0

### Mục đích

Tài liệu này định nghĩa các chuẩn giao tiếp giữa các module trong hệ thống Smart Home, bao gồm:

* Cấu trúc thư mục dự án
* Kiểu dữ liệu dùng chung
* Danh mục thiết bị hỗ trợ
* Quy tắc Signals/Slots
* Cơ chế mô phỏng thời gian
* Quy định tích hợp hệ thống

Tất cả thành viên phải tuân thủ để đảm bảo các module có thể phát triển độc lập và tích hợp thành công.

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
│   ├── TV.h / TV.cpp
│   ├── Fridge.h / Fridge.cpp
│   ├── WaterHeater.h / WaterHeater.cpp
│   ├── WashingMachine.h / WashingMachine.cpp
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

### Yêu cầu

```pro
QT += charts
```

Không thay đổi cấu trúc thư mục nếu chưa thống nhất toàn nhóm.

---

# 2. Danh Mục Thiết Bị Hỗ Trợ

Hệ thống mô phỏng các thiết bị dân dụng phổ biến trong gia đình.

| Type            | Thiết bị        |
| --------------- | --------------- |
| LIGHT           | Đèn             |
| FAN             | Quạt            |
| AC              | Điều hòa        |
| TV              | Tivi            |
| FRIDGE          | Tủ lạnh         |
| WASHING_MACHINE | Máy giặt        |
| WATER_HEATER    | Bình nước nóng  |
| MICROWAVE       | Lò vi sóng      |
| RICE_COOKER     | Nồi cơm điện    |
| CURTAIN         | Rèm cửa tự động |

### Công suất tham khảo

| Thiết bị        | Công suất (W) |
| --------------- | ------------: |
| LIGHT           |            10 |
| FAN             |            70 |
| TV              |           120 |
| FRIDGE          |           150 |
| WASHING_MACHINE |           500 |
| RICE_COOKER     |           700 |
| MICROWAVE       |          1000 |
| AC              |          1200 |
| WATER_HEATER    |          2000 |

---

# 3. Dữ Liệu Dùng Chung

> File: `DataStructures.h`

Không được thay đổi tên Struct, tên biến hoặc kiểu dữ liệu nếu chưa có sự đồng thuận của nhóm.

## 3.1 Hằng Số Hệ Thống

```cpp
const double MAX_HOUSE_POWER = 5000.0;
const double FORGOTTEN_TIME_LIMIT = 4.0;

const int MIN_AC_TEMP = 16;
const int MAX_AC_TEMP = 30;
```

| Hằng số              | Mô tả                                             |
| -------------------- | ------------------------------------------------- |
| MAX_HOUSE_POWER      | Ngưỡng quá tải toàn hệ thống                      |
| FORGOTTEN_TIME_LIMIT | Thời gian thiết bị hoạt động liên tục để cảnh báo |
| MIN_AC_TEMP          | Nhiệt độ AC tối thiểu                             |
| MAX_AC_TEMP          | Nhiệt độ AC tối đa                                |

---

## 3.2 DeviceInfo

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

### Quy ước thuộc tính

| Thuộc tính       | Ý nghĩa                  |
| ---------------- | ------------------------ |
| id               | Mã định danh thiết bị    |
| name             | Tên hiển thị             |
| roomName         | Phòng chứa thiết bị      |
| type             | Loại thiết bị            |
| isOn             | Trạng thái hoạt động     |
| currentPower     | Công suất hiện tại (W)   |
| totalConsumption | Điện năng tích lũy (kWh) |
| extraParam       | Tham số mở rộng          |

### Quy ước extraParam

| Thiết bị      | Giá trị            |
| ------------- | ------------------ |
| LIGHT         | Độ sáng (0-100%)   |
| FAN           | Tốc độ (1-3)       |
| AC            | Nhiệt độ (16-30°C) |
| TV            | Âm lượng (0-100)   |
| CURTAIN       | Độ mở rèm (0-100%) |
| Thiết bị khác | 0                  |

---

## 3.3 HomeSummary

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

Dashboard hiển thị:

* Tổng công suất tức thời
* Tổng điện năng tiêu thụ
* Chi phí điện tạm tính
* Tổng số thiết bị
* Số thiết bị đang hoạt động

---

# 4. Giao Tiếp Hệ Thống

## 4.1 UI → Backend

| Signal                     | Slot                                 | Chức năng        |
| -------------------------- | ------------------------------------ | ---------------- |
| requestTurnOn(id)          | slot_handleTurnOnDevice(id)          | Bật thiết bị     |
| requestTurnOff(id)         | slot_handleTurnOffDevice(id)         | Tắt thiết bị     |
| requestParamChange(id,val) | slot_handleUpdateDeviceParam(id,val) | Cập nhật tham số |

---

## 4.2 Backend → UI

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

| Signal                 | Mục đích                       |
| ---------------------- | ------------------------------ |
| sig_deviceStateChanged | Cập nhật trạng thái thiết bị   |
| sig_summaryUpdated     | Cập nhật Dashboard             |
| sig_energyHistoryReady | Cập nhật biểu đồ tiêu thụ điện |

---

## 4.3 Cảnh Báo Hệ Thống

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

#### Quá tải

```text
totalCurrentPower > MAX_HOUSE_POWER
```

#### Thiết bị bị quên tắt

```text
runningTime > FORGOTTEN_TIME_LIMIT
```

UI chịu trách nhiệm hiển thị Popup hoặc Notification.

---

# 5. Simulation Engine

## Quy Ước Thời Gian

```text
1 giây thực = 0.5 giờ mô phỏng
```

Mỗi giây thực:

```cpp
emit sig_timeTick(0.5);
```

---

## Cập Nhật Điện Năng

Đối với thiết bị đang bật:

```cpp
isOn == true
```

Điện năng tăng thêm:

```text
ΔA = P × Δt
```

Trong đó:

```text
P  : Công suất hiện tại (W)
Δt : 0.5 giờ
ΔA : Điện năng tăng thêm (Wh)
```

---

# 6. Quy Tắc Tích Hợp

## Phân Tách Trách Nhiệm

### Frontend

Chịu trách nhiệm:

* Giao diện người dùng
* Dashboard
* Biểu đồ
* Popup cảnh báo

Không được:

* Tính điện năng
* Tính tiền điện
* Thay đổi logic thiết bị

---

### Backend

Chịu trách nhiệm:

* Quản lý thiết bị
* Tính toán điện năng
* Tính chi phí điện
* Kiểm tra cảnh báo

Không được:

* Can thiệp thành phần hiển thị UI

---

## Kết Nối Module

Toàn bộ kết nối Signal/Slot thực hiện tập trung tại:

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

## Kiểm Tra Giá Trị Biên

Backend chịu trách nhiệm kiểm tra dữ liệu đầu vào.

Ví dụ:

| Input | Giá trị sử dụng |
| ----- | --------------- |
| < 16  | 16              |
| 16-30 | Giữ nguyên      |
| > 30  | 30              |

UI không cần xử lý giới hạn dữ liệu.

---

# 7. Phân Công Thành Viên

| Thành viên | Phạm vi phụ trách |
|------------|-------------------|
| A (Leader) | SmartHomeManager, kiến trúc hệ thống, tích hợp module |
| B | Device Framework (`Device`, `Light`, `Fan`, `AC`) |
| C | Thiết bị gia dụng nâng cao (`TV`, `Fridge`, `WashingMachine`, `WaterHeater`, ...) |
| D | Simulation Engine, Energy Tracking, lịch sử tiêu thụ |
| E | Frontend (Qt UI), Dashboard, Charts, Alerts |

---

# 8. Quy Định Cuối

`DataStructures.h` được xem là hợp đồng dữ liệu của toàn hệ thống.

Không được tự ý thay đổi:

* Tên Struct
* Tên biến
* Kiểu dữ liệu
* Tên Signal
* Tên Slot

Mọi thay đổi phải được thống nhất bởi toàn nhóm trước khi triển khai.
