# 📐 Quy Ước Cấu Trúc Dữ Liệu & Giao Tiếp (Interface Contract)

> **Mục đích:** File này định nghĩa các quy chuẩn chung về cấu trúc thư mục, kiểu dữ liệu, và luồng tín hiệu (Signals/Slots) giữa Frontend (UI) và Backend (Logic). Tất cả thành viên bắt buộc phải tuân thủ để code độc lập không bị xung đột.

---

# 📁 1. Quy Định Cấu Trúc Thư Mục Dự Án (Qt Creator)

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
---

# 📐 2. Đặc Tả Dữ Liệu Dùng Chung (DataStructures.h)

> File này do **Thành viên A (Leader)** khởi tạo đầu tiên.  
> **Nghiêm cấm** mọi thành viên tự ý chỉnh sửa kiểu dữ liệu hoặc đổi tên biến.

---

## 2.1. Các Hằng Số Hệ Thống & Ngưỡng Cảnh Báo

```cpp
#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <string>

// Ngưỡng cấu hình hệ thống
const double MAX_HOUSE_POWER = 5000.0;    // Ngưỡng quá tải toàn nhà (Watts)
const double FORGOTTEN_TIME_LIMIT = 4.0;  // Thiết bị bật liên tục quá 4 giờ giả lập sẽ cảnh báo
const int MIN_AC_TEMP = 16;               // Nhiệt độ AC tối thiểu
const int MAX_AC_TEMP = 30;               // Nhiệt độ AC tối đa
```

---

## 2.2. Các Cấu Trúc Dữ Liệu Giao Tiếp (Structs)

```cpp
// 1. Gói dữ liệu của TỪNG thiết bị gửi lên UI hiển thị
struct DeviceInfo {
    std::string id;           // Định dạng: "R1_LIGHT_01", "R2_AC_01"
                              // (R1: Phòng 1, R2: Phòng 2)

    std::string name;         // Tên hiển thị:
                              // "Đèn trần", "Điều hòa Panasonic"

    std::string roomName;     // Tên phòng:
                              // "Phòng khách", "Phòng ngủ Master"

    std::string type;         // Phân loại để UI map Icon:
                              // "LIGHT", "FAN", "AC"

    bool isOn;                // Trạng thái hoạt động
                              // true = ON, false = OFF

    double currentPower;      // Công suất tiêu thụ tức thời hiện tại (W)

    double totalConsumption;  // Điện năng tiêu thụ tích lũy tổng (kWh)

    int extraParam;           // Thông số phụ:
                              // - Tốc độ quạt (1 → 3)
                              // - Nhiệt độ AC (16 → 30)
                              // - Đèn mặc định = 0
};

// 2. Gói dữ liệu TỔNG QUAN để hiển thị trên Dashboard chính
struct HomeSummary {
    double totalCurrentPower; // Tổng công suất tức thời toàn nhà (W)

    double totalEnergyUsed;   // Tổng số điện năng tiêu thụ (kWh)

    double totalCost;         // Tổng tiền điện tạm tính lũy tiến theo EVN (VND)

    int totalDevices;         // Tổng số lượng thiết bị có trong hệ thống

    int activeDevices;        // Số lượng thiết bị hiện đang bật
                              // (isOn == true)
};

#endif // DATA_STRUCTURES_H
```

---

# 📡 3. Quy Ước Luồng Tín Hiệu (Qt Signals & Slots)

Lớp **SmartHomeManager** đóng vai trò trung tâm điều phối dữ liệu.

Sự kết nối giữa **UI (Thành viên D)** và **Logic/Core (Thành viên A, B, C)** được thực hiện qua các đầu hàm sau.

---

## 3.1. Luồng Điều Khiển Thiết Bị Từ Xa (Từ UI tác động vào Core)

Khi người dùng tương tác trên màn hình, **Thành viên D (UI)** phát ra các **Signal** tương ứng.

**Thành viên A (Core)** viết hàm **Slot** để nhận và xử lý.

| Signal từ UI | Slot xử lý Backend | Mô tả |
|-------------|-------------------|--------|
| `void requestTurnOn(std::string deviceId);` | `void slot_handleTurnOnDevice(std::string deviceId);` | Gửi yêu cầu bật thiết bị theo ID |
| `void requestTurnOff(std::string deviceId);` | `void slot_handleTurnOffDevice(std::string deviceId);` | Gửi yêu cầu tắt thiết bị theo ID |
| `void requestParamChange(std::string id, int val);` | `void slot_handleUpdateDeviceParam(std::string id, int val);` | Thay đổi tốc độ quạt hoặc nhiệt độ AC |

---

## 3.2. Luồng Trả Kết Quả Cập Nhật (Từ Core phản hồi ra UI)

Sau khi Backend xử lý xong logic, thay đổi trạng thái thiết bị hoặc tính xong lượng điện tăng thêm, Thành viên A & C sẽ phát Signal để Thành viên D (UI) nhận và cập nhật giao diện.

```cpp
// Khai báo trong lớp SmartHomeManager ở mục signals:

// 1. Phát ra khi 1 thiết bị thay đổi trạng thái
// (Ví dụ: đổi màu nút bấm, đổi icon bật/tắt)
void sig_deviceStateChanged(const DeviceInfo& updatedDevice);

// 2. Phát ra định kỳ để UI cập nhật Dashboard
// (kWh, VND, số thiết bị đang bật)
void sig_summaryUpdated(const HomeSummary& summary);

// 3. Phát ra mảng dữ liệu lịch sử tiêu thụ
// 24 giờ gần nhất để QtCharts vẽ biểu đồ
void sig_energyHistoryReady(
    const std::vector<double>& hourlyData
);
```

---

## 3.3. Luồng Phát Tín Hiệu Cảnh Báo Hệ Thống

Khi Backend tính toán và phát hiện bất thường, lập tức phát ra các tín hiệu sau.

Thành viên D (UI) thiết kế sẵn hàm nhận để hiển thị **Pop-up cảnh báo màu đỏ nhấp nháy**.

```cpp
// Khai báo trong lớp SmartHomeManager ở mục signals:

// 1. Cảnh báo khi tổng công suất vượt quá 5000W
void sig_alertOverload(
    double currentTotalPower,
    double maxThreshold
);

// 2. Cảnh báo khi một thiết bị công suất lớn
// chạy liên tục quá 4 giờ giả lập
void sig_alertForgottenDevice(
    const std::string& deviceName,
    double hoursRunning
);
```

---

# ⏱️ 4. Quy Ước Engine Mô Phỏng Thời Gian (SimulationEngine)

Để thống nhất về tốc độ dòng chảy của thời gian giả lập, **Thành viên C** cấu hình `QTimer` theo quy ước sau:

## Tỷ lệ quy đổi

```text
1 giây thời gian thực tế
=
0.5 giờ (30 phút) thời gian giả lập
```

## Cơ chế kích hoạt

Cứ mỗi **1 giây thực**, lớp `SimulationEngine` sẽ phát tín hiệu:

```cpp
emit sig_timeTick(0.5);
```

Ý nghĩa:

```text
Hệ thống đã trôi qua 0.5 giờ giả lập
```

### Xử lý phía Backend

Thành viên A nhận giá trị `0.5`, duyệt qua danh sách thiết bị.

Đối với các thiết bị có:

```cpp
isOn == true
```

thì cộng dồn điện năng tiêu thụ theo công thức:

\[
\Delta A = P_{current} \times 0.5 \; (Wh)
\]

Trong đó:

- `Pcurrent`: Công suất hiện tại của thiết bị (W)
- `0.5`: Thời gian giả lập đã trôi qua (giờ)
- `ΔA`: Điện năng tiêu thụ tăng thêm (Wh)

---

# 🚨 5. Nguyên Tắc "Bất Khả Xâm Phạm"

## 5.1. Không sửa code chéo

### Thành viên D (UI)

Không được:

- Tự ý sửa biến logic
- Tự tính điện năng tiêu thụ
- Tự tính tiền điện

### Thành viên A, B, C (Core)

Không được:

- Can thiệp vào thuộc tính hiển thị đồ họa Qt
- Chỉnh sửa giao diện UI

---

## 5.2. Ghép nối bằng QObject::connect

Việc kết nối toàn bộ hệ thống được thực hiện tập trung tại:

```text
main.cpp
```

vào ngày tích hợp cuối cùng.

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

## 5.3. Xử lý Giá Trị Biên

Mọi dữ liệu do UI gửi xuống nếu vượt quá khoảng cho phép:

```cpp
MIN_AC_TEMP → MAX_AC_TEMP
```

Backend sẽ tự động đưa về giá trị hợp lệ gần nhất.

Ví dụ:

| Giá trị nhận từ UI | Giá trị Backend sử dụng |
|-------------------|------------------------|
| 10 | 16 |
| 15 | 16 |
| 25 | 25 |
| 35 | 30 |
| 40 | 30 |

**Lưu ý:** UI không cần viết code kiểm tra hay chặn dữ liệu đầu vào phức tạp.

---

# 📌 Tóm Tắt Trách Nhiệm

| Thành viên | Trách nhiệm chính |
|------------|------------------|
| A (Leader) | Core Logic, Device Manager, Signals/Slots |
| B | Thiết bị thông minh và hành vi thiết bị |
| C | Simulation Engine, tính điện năng, lịch sử tiêu thụ |
| D | UI, Dashboard, QtCharts, Popup cảnh báo |
