#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <string>

// 1. Quy ước ngưỡng cảnh báo cố định
const double MAX_HOUSE_POWER = 5000.0;    // Ngưỡng quá tải hệ thống: 5000 Watts
const double FORGOTTEN_TIME_LIMIT = 4.0;  // Ngưỡng quên tắt thiết bị: 4 giờ giả lập
const int MIN_AC_TEMP = 16;               // Nhiệt độ điều hòa tối thiểu
const int MAX_AC_TEMP = 30;               // Nhiệt độ điều hòa tối đa

// 2. Dữ liệu của TỪNG thiết bị hiển thị lên UI danh sách
struct DeviceInfo {
    std::string id;           // Định dạng: "R1_LIGHT_01", "R2_AC_01" (R1 = Phòng 1)
    std::string name;         // Tên hiển thị: "Đèn trần", "Điều hòa trung tâm"
    std::string roomName;     // Tên phòng: "Phòng khách", "Phòng ngủ"
    std::string type;         // Loại để UI bắt icon: "LIGHT", "FAN", "AC"
    bool isOn;                // Trạng thái: true (ON), false (OFF)
    double currentPower;      // Công suất tức thời (W)
    double totalConsumption;  // Điện năng tiêu thụ tích lũy (kWh)
    int extraParam;           // Giá trị bổ sung: Số quạt (1->3) hoặc Nhiệt độ AC (16->30)
};

// 3. Dữ liệu TỔNG QUAN toàn hệ thống đưa lên Dashboard chính
struct HomeSummary {
    double totalCurrentPower; // Tổng W hiện tại của tất cả thiết bị đang bật
    double totalEnergyUsed;   // Tổng kWh đã tiêu thụ từ đầu chương trình
    double totalCost;         // Tổng tiền điện tương ứng (VND)
    int totalDevices;         // Tổng số thiết bị trong nhà
    int activeDevices;        // Số thiết bị đang hoạt động
};

#endif
