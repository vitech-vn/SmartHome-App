# 🏡 Smart Home Energy Monitoring System (OOP C++ & Qt)

> **Đồ án môn học:** Lập trình hướng đối tượng (OOP)
> **Thời gian thực hiện:** 1 - 2 Tuần (Mô hình phát triển song song tốc độ cao)
> **Công nghệ sử dụng:** C++11, Qt Framework (Qt Quick/QML hoặc Qt Widgets), QtCharts, Multi-threading.

---

## 🏗️ 1. Quy Chuẩn Thiết Kế & Hợp Đồng Giao Tiếp

Để đảm bảo các thành viên có thể **lập trình độc lập 100% cùng một lúc** mà không cần đợi nhau, nhóm đã thống nhất cấu trúc thư mục, kiểu dữ liệu chung và luồng truyền tín hiệu giữa UI và Logic tại file quy ước riêng.

👉 **Vui lòng đọc kỹ trước khi code:** [Tài liệu Hợp đồng Giao tiếp Interface (INTERFACE_CONTRACT.md)](./INTERFACE_CONTRACT.md)

---

## 📊 2. Bảng Phân Công Nhiệm Vụ (Contribution Matrix)

| Thành viên | Vai trò | File phụ trách chính | Nhiệm vụ cốt lõi |
| :--- | :--- | :--- | :--- |
| **Thành viên A**<br>*(Leader)* | **Core Engine & Quản lý** | `SmartHomeManager.h/cpp`<br>`Room.h/cpp` | - Quản lý cấu trúc nhà/phòng (`std::vector<Device*>`).<br>- Xử lý luồng kích hoạt Bật/Tắt thiết bị.<br>- Hiện thực **Logic Cảnh báo Quá tải** (>5000W). |
| **Thành viên B** | **Logic Thiết bị (OOP)** | `Light.h/cpp`, `Fan.h/cpp`<br>`AirConditioner.h/cpp` | - Định nghĩa các lớp con kế thừa từ `Device`.<br>- Triển khai **Tính đa hình** cho hàm tính công suất thực tế.<br>- Viết logic **Cảnh báo quên tắt thiết bị** (>4h liên tục). |
| **Thành viên C** | **Simulator & Định lượng** | `SimulationEngine.h/cpp` | - Tạo `QTimer` mô phỏng: 1 giây thực = 30 phút giả lập.<br>- Viết thuật toán tính **Tiền điện lũy tiến 6 bậc EVN**.<br>- Trích xuất mảng dữ liệu tiêu thụ 24 giờ để vẽ biểu đồ. |
| **Thành viên D** | **Frontend UI & Biểu đồ** | `MainWindow.ui`<br>`CustomChart.h/cpp` | - Thiết kế giao diện Dashboard (Dark Mode phẳng, hiện đại).<br>- Sử dụng `QtCharts` để **vẽ biểu đồ xu hướng tiêu thụ**.<br>- Thiết kế các Pop-up/Banner cảnh báo trực quan. |
| **Thành viên E** | **Git Master, QA & Report** | `TestSuites.cpp`<br>`BaoCao.docx`, `Slide.pptx` | - Khởi tạo, cấu hình Git Branches và giải quyết xung đột.<br>- Hiện thực **15+ Test Cases** (Kiểm thử biên, dữ liệu sai).<br>- Tổng hợp tài liệu báo cáo và làm Slide thuyết trình. |

---

## 📅 3. Lộ Trình Thực Hiện Chi Tiết (12 Ngày)

* **Ngày 1:** Họp nhóm, thống nhất [INTERFACE_CONTRACT.md](./INTERFACE_CONTRACT.md). Thành viên E tạo repo GitHub, chia nhánh: `dev-core` (A), `dev-device` (B), `dev-sim` (C), `dev-ui` (D).
* **Ngày 2 - Ngày 5:** Code song song trên nhánh riêng biệt.
* **Ngày 6 (Integration Day):** Merge toàn bộ code vào nhánh `main` và kết nối Signal & Slot.
* **Ngày 7 - Ngày 9:** Chạy các kịch bản kiểm thử (Test Cases), sửa lỗi (Bug fixing) và tối ưu hóa biểu đồ.
* **Ngày 10 - Ngày 12:** Đóng gói phần mềm, hoàn thiện file báo cáo Word và Slide thuyết trình.

---

## 🛠️ 4. Quy Định Sử Dụng Git

1. **KHÔNG** code trực tiếp trên nhánh `main`. Nhánh `main` chỉ dùng để lưu bản chạy thử cuối cùng của cả nhóm.
2. Mọi tính năng mới bắt buộc phải viết trên nhánh cá nhân (`dev-xxx`).
3. Trước khi đẩy code lên (Push), bắt buộc phải chạy `git pull origin main` về nhánh của mình để kiểm tra lỗi xung đột code.
4. Mọi vấn đề về xung đột mã nguồn liên hệ ngay **Thành viên E (Git Master)** để xử lý.
