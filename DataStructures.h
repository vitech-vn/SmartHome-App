```cpp
#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <string>
#include <vector>

//
// ======================================================
// SMART HOME SYSTEM - SHARED DATA CONTRACT
// ======================================================
// File dùng chung cho toàn bộ hệ thống.
// Không tự ý thay đổi tên Struct, tên biến hoặc kiểu dữ liệu
// nếu chưa được cả nhóm thống nhất.
// ======================================================
//

//
// 1. CẤU HÌNH HỆ THỐNG
//

// Ngưỡng công suất tối đa toàn hệ thống (W)
const double MAX_HOUSE_POWER = 5000.0;

// Thiết bị hoạt động liên tục quá ngưỡng này sẽ cảnh báo (giờ giả lập)
const double FORGOTTEN_TIME_LIMIT = 4.0;

// Giới hạn nhiệt độ điều hòa
const int MIN_AC_TEMP = 16;
const int MAX_AC_TEMP = 30;

//
// 2. DANH SÁCH LOẠI THIẾT BỊ CHUẨN
//
// UI và Backend phải sử dụng đúng các giá trị này.
//

const std::string DEVICE_LIGHT            = "LIGHT";
const std::string DEVICE_FAN              = "FAN";
const std::string DEVICE_AC               = "AC";
const std::string DEVICE_TV               = "TV";
const std::string DEVICE_FRIDGE           = "FRIDGE";
const std::string DEVICE_WASHING_MACHINE  = "WASHING_MACHINE";
const std::string DEVICE_WATER_HEATER     = "WATER_HEATER";
const std::string DEVICE_MICROWAVE        = "MICROWAVE";
const std::string DEVICE_RICE_COOKER      = "RICE_COOKER";
const std::string DEVICE_CURTAIN          = "CURTAIN";

//
// 3. DEVICE INFO
//
// Dữ liệu của một thiết bị gửi từ Backend -> UI
//

struct DeviceInfo
{
    // =============================
    // Thông tin định danh
    // =============================

    std::string id;
    // Ví dụ:
    // R1_LIGHT_01
    // R2_AC_01
    // R3_TV_01

    std::string name;
    // Ví dụ:
    // "Đèn phòng khách"
    // "Điều hòa Panasonic"

    std::string roomName;
    // Ví dụ:
    // "Phòng khách"
    // "Phòng ngủ"

    std::string type;
    // Giá trị lấy từ:
    // DEVICE_LIGHT
    // DEVICE_FAN
    // DEVICE_AC
    // ...

    // =============================
    // Trạng thái hoạt động
    // =============================

    bool isOn;

    // =============================
    // Điện năng
    // =============================

    double currentPower;
    // Công suất tức thời (W)

    double totalConsumption;
    // Điện năng tiêu thụ tích lũy (kWh)

    // =============================
    // Tham số mở rộng
    // =============================
    //
    // LIGHT           : độ sáng (0-100)
    // FAN             : tốc độ (1-3)
    // AC              : nhiệt độ (16-30)
    // TV              : âm lượng (0-100)
    // CURTAIN         : độ mở (0-100)
    // Các thiết bị khác: 0
    //

    int extraParam;

    // =============================
    // Thống kê hoạt động
    // =============================

    double runningHours;
    // Tổng số giờ đã hoạt động
    // (giờ mô phỏng)

    double currentSessionHours;
    // Thời gian chạy liên tục từ lần bật gần nhất
    // Dùng cho cảnh báo quên tắt
};

//
// 4. DASHBOARD SUMMARY
//
// Dữ liệu tổng quan toàn hệ thống
//

struct HomeSummary
{
    double totalCurrentPower;
    // Tổng công suất tức thời toàn nhà (W)

    double totalEnergyUsed;
    // Tổng điện năng tiêu thụ (kWh)

    double totalCost;
    // Tổng tiền điện (VND)

    int totalDevices;
    // Tổng số thiết bị

    int activeDevices;
    // Số thiết bị đang bật

    int warningDevices;
    // Số thiết bị đang nằm trong trạng thái cảnh báo
};

//
// 5. DỮ LIỆU LỊCH SỬ TIÊU THỤ
//
// Dùng cho Qt Charts
//

struct EnergyHistory
{
    std::vector<double> hourlyConsumption;

    // 24 phần tử
    // index 0  -> giờ gần nhất
    // index 23 -> 24 giờ trước
};

//
// 6. THÔNG TIN CẢNH BÁO
//

struct AlertInfo
{
    std::string title;
    std::string message;

    std::string deviceId;
    std::string deviceName;

    bool isCritical;
};

#endif // DATA_STRUCTURES_H
```
