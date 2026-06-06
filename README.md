# 🏡 Smart Home Energy Monitoring System

> Hệ thống mô phỏng nhà thông minh (Smart Home) sử dụng **C++ và Qt Framework** nhằm quản lý thiết bị gia dụng, giám sát điện năng tiêu thụ, cảnh báo quá tải và trực quan hóa dữ liệu theo thời gian thực.

---

## 📋 Tổng Quan Dự Án

Smart Home Energy Monitoring System là ứng dụng mô phỏng một ngôi nhà thông minh với các chức năng:

* Quản lý thiết bị gia dụng trong nhà.
* Bật/Tắt và điều chỉnh trạng thái thiết bị từ giao diện.
* Theo dõi công suất tiêu thụ theo thời gian thực.
* Tính toán điện năng tiêu thụ và chi phí điện.
* Cảnh báo quá tải hệ thống.
* Cảnh báo thiết bị hoạt động quá lâu.
* Hiển thị thống kê và biểu đồ tiêu thụ điện.

Dự án được xây dựng theo mô hình **Object-Oriented Programming (OOP)** và kiến trúc phân tách rõ ràng giữa:

* Frontend (UI)
* Backend (Business Logic)
* Simulation Engine
* Data Contract

---

## 🎯 Mục Tiêu Học Thuật

Thông qua dự án, nhóm áp dụng các kiến thức:

* Class & Object
* Inheritance
* Polymorphism
* Encapsulation
* Abstraction
* Signals & Slots trong Qt
* Event-Driven Programming
* Modular Design
* Team Development với GitHub

---

## 🛠 Công Nghệ Sử Dụng

| Thành phần       | Công nghệ    |
| ---------------- | ------------ |
| Ngôn ngữ         | C++11        |
| Framework        | Qt 6 / Qt 5  |
| Giao diện        | Qt Widgets   |
| Biểu đồ          | Qt Charts    |
| Quản lý mã nguồn | Git & GitHub |
| IDE              | Qt Creator   |

---

## 🏠 Thiết Bị Được Mô Phỏng

Hệ thống hỗ trợ các thiết bị dân dụng phổ biến:

| Thiết bị        | Type            |
| --------------- | --------------- |
| Đèn             | LIGHT           |
| Quạt            | FAN             |
| Điều hòa        | AC              |
| Tivi            | TV              |
| Tủ lạnh         | FRIDGE          |
| Máy giặt        | WASHING_MACHINE |
| Bình nước nóng  | WATER_HEATER    |
| Lò vi sóng      | MICROWAVE       |
| Nồi cơm điện    | RICE_COOKER     |
| Rèm cửa tự động | CURTAIN         |

---

## 📂 Cấu Trúc Dự Án

```text
SmartHomeProject/
│
├── README.md
├── CONTRIBUTING.md
├── INTERFACE_CONTRACT.md
├── DataStructures.h
│
├── Backend/
│   ├── Device.*
│   ├── Light.*
│   ├── Fan.*
│   ├── AirConditioner.*
│   ├── TV.*
│   ├── Fridge.*
│   ├── WashingMachine.*
│   ├── WaterHeater.*
│   └── SmartHomeManager.*
│
├── Simulator/
│   └── SimulationEngine.*
│
└── Frontend/
    ├── MainWindow.*
    ├── MainWindow.ui
    └── CustomChart.*
```

---

## ⚙️ Chức Năng Chính

### Quản Lý Thiết Bị

* Bật/Tắt thiết bị.
* Điều chỉnh tham số thiết bị.
* Hiển thị trạng thái hoạt động.

### Giám Sát Điện Năng

* Công suất tức thời.
* Điện năng tiêu thụ tích lũy.
* Thống kê theo thời gian.

### Dashboard

* Tổng số thiết bị.
* Thiết bị đang hoạt động.
* Tổng điện năng tiêu thụ.
* Chi phí điện tạm tính.

### Cảnh Báo

* Quá tải công suất toàn nhà.
* Thiết bị hoạt động liên tục quá thời gian quy định.

### Biểu Đồ

* Lịch sử tiêu thụ điện.
* Thống kê 24 giờ gần nhất.

---

## ⏱ Quy Ước Mô Phỏng

```text
1 giây thực = 0.5 giờ mô phỏng
```

Simulation Engine phát tín hiệu định kỳ:

```cpp
emit sig_timeTick(0.5);
```

Từ đó hệ thống cập nhật:

* Điện năng tiêu thụ
* Thời gian hoạt động thiết bị
* Cảnh báo hệ thống
* Dữ liệu biểu đồ

---

## 👥 Phân Công Thành Viên

| Thành viên | Phụ trách                                         |
| ---------- | ------------------------------------------------- |
| Lâm Thị Huyền Vi | Kiến trúc hệ thống, SmartHomeManager, Integration |
| Phạm Thành Tân | Device Framework và các lớp thiết bị cơ bản       |
| Ninh Đức Thành | Thiết bị gia dụng mở rộng                         |
| Trần Duy Bảo | Simulation Engine, Energy Tracking                |
| Phạm Quốc Thịnh | UI, Dashboard, Charts, Alerts                     |

---

## 🔀 Quy Trình Làm Việc

* Không commit trực tiếp lên `main`.
* Mỗi thành viên làm việc trên branch riêng.
* Pull Request trước khi merge.
* Tuân thủ quy định trong `CONTRIBUTING.md`.
* Không tự ý thay đổi `DataStructures.h`.

---

## 📄 Tài Liệu Dự Án

| File                  | Mô tả                         |
| --------------------- | ----------------------------- |
| README.md             | Tổng quan dự án               |
| CONTRIBUTING.md       | Quy trình làm việc GitHub     |
| INTERFACE_CONTRACT.md | Hợp đồng dữ liệu và giao tiếp |
| DataStructures.h      | Cấu trúc dữ liệu dùng chung   |

---

## 📌 Ghi Chú

`DataStructures.h` được xem là hợp đồng dữ liệu trung tâm của toàn bộ hệ thống.

Mọi thay đổi liên quan đến:

* Struct
* Signal/Slot
* Quy ước dữ liệu

đều phải được thống nhất trước khi triển khai.
