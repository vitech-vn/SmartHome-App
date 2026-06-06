# 🏡 Smart Home Energy Monitoring System (OOP C++ & Qt)

> **Đồ án môn học:** Lập trình hướng đối tượng (OOP)
> **Thời gian thực hiện:** 1 - 2 Tuần (Mô hình phát triển song song tốc độ cao)
> **Công nghệ sử dụng:** C++11, Qt Framework (Qt Quick/QML hoặc Qt Widgets), QtCharts, Multi-threading.

---

## 🏗️ 1. Kiến Trúc Hệ Thống & Hợp Đồng Giao Tiếp (Interface)

Để tối ưu hóa tốc độ và **tránh xung đột code (Merge Conflict)**, dự án được cô lập thành 3 phần: **Backend Core**, **Logic Thiết bị**, và **Frontend UI**. Các thành viên giao tiếp với nhau thông qua cơ chế **Signal & Slot** của Qt.

### 📡 Luồng Tín Hiệu Giữa UI và Backend

* **Từ UI -> Backend:** Khi người dùng tương tác (Bật/tắt, tăng giảm thông số), UI sẽ phát ra `Signal`. Lớp `SmartHomeManager` ở Backend sẽ nhận thông qua `Slot` và xử lý logic.
* **Từ Backend -> UI:** Sau khi tính toán điện năng hoặc phát hiện bất thường, Backend phát `Signal` kèm dữ liệu cấu trúc (`Struct`). UI nhận và cập nhật biểu đồ/hiện cảnh báo.

---

## 📊 2. Bảng Phân Công Nhiệm Vụ & Đóng Góp (Contribution Matrix)

| Thành viên | Vai trò | File phụ trách chính | Nhiệm vụ cốt lõi |
| :--- | :--- | :--- | :--- |
| **Thành viên A**<br>*(Leader)* | **Core Engine & Quản lý** | `SmartHomeManager.h/cpp`<br>`Room.h/cpp` | - Quản lý cấu trúc nhà/phòng (`std::vector<Device*>`).<br>- Xử lý luồng kích hoạt Bật/Tắt thiết bị.<br>- Hiện thực **Logic Cảnh báo Quá tải** (>5000W). |
| **Thành viên B** | **Logic Thiết bị (OOP)** | `Light.h/cpp`, `Fan.h/cpp`<br>`AirConditioner.h/cpp` | - Định nghĩa các lớp con kế thừa từ `Device`.<br>- Triển khai **Tính đa hình** cho hàm tính công suất thực tế.<br>- Viết logic **Cảnh báo quên tắt thiết bị** (>4h liên tục). |
| **Thành viên C** | **Simulator & Định lượng** | `SimulationEngine.h/cpp` | - Tạo `QTimer` mô phỏng: 1 giây thực = 30 phút giả lập.<br>- Viết thuật toán tính **Tiền điện lũy tiến 6 bậc EVN**.<br>- Trích xuất mảng dữ liệu tiêu thụ 24 giờ để vẽ biểu đồ. |
| **Thành viên D** | **Frontend UI & Biểu đồ** | `MainWindow.ui`<br>`CustomChart.h/cpp` (hoặc QML) | - Thiết kế giao diện Dashboard (Dark Mode phẳng, hiện đại).<br>- Sử dụng `QtCharts` (`QChartView`) để **vẽ biểu đồ tiêu thụ**.<br>- Thiết kế các Pop-up/Banner cảnh báo trực quan. |
| **Thành viên E** | **Git Master, QA & Report** | `TestSuites.cpp`<br>`BaoCao.docx`, `Slide.pptx` | - Khởi tạo, cấu hình Git Branches và giải quyết xung đột.<br>- Hiện thực **15+ Test Cases** (Kiểm thử biên, dữ liệu sai).<br>- Tổng hợp tài liệu báo cáo và làm Slide thuyết trình. |

---

## 📅 3. Lộ Trình Thực Hiện Chi Tiết (12 Ngày)

### ⏱️ Giai đoạn 1: Thiết lập & Code Song Song (Ngày 1 - Ngày 6)
* **Ngày 1:** Họp nhóm chốt cấu trúc dữ liệu chung (`DataStructures.h`). Thành viên E tạo Repo GitHub và chia 4 nhánh độc lập: `dev-core` (A), `dev-device` (B), `dev-sim` (C), `dev-ui` (D).
* **Ngày 2 - Ngày 5:** Các thành viên tập trung viết code trên file và nhánh được giao. Không can thiệp vào file của người khác. *Mẹo cho D: Dùng dữ liệu giả (Hardcode) để dựng và căn chỉnh giao diện trước.*
* **Ngày 6:** Đồng bộ hóa (Integration Day). Thành viên A và E phụ trách merge toàn bộ các nhánh vào nhánh `main`. Tiến hành kết nối Signal & Slot giữa UI và Core.

### 🔍 Giai đoạn 2: Kiểm Thử & Tối Ưu (Ngày 7 - Ngày 9)
* **Ngày 7:** Thành viên E chạy các kịch bản kiểm thử (Test Cases) trực tiếp trên phần mềm, log lỗi lên hệ thống.
* **Ngày 8 - Ngày 9:** Thành viên A, B, C tập trung sửa lỗi (Bug fixing). Thành viên D căn chỉnh lại hiệu ứng biểu đồ và pop-up cảnh báo cho mượt mà.

### 📝 Giai đoạn 3: Đóng Gói & Báo Cáo (Ngày 10 - Ngày 12)
* **Ngày 10 - 11:** Thành viên E hoàn thiện file báo cáo Word (thêm hình ảnh biểu đồ thực tế, sơ đồ lớp) và thiết kế Slide thuyết trình.
* **Ngày 12:** Cả nhóm chạy thử nghiệm (Demo) lần cuối, chuẩn bị sẵn sàng nội dung để bảo vệ đồ án.

---

## 🛠️ 4. Quy Định Sử Dụng Git & Nghiêm Cấm Xung Đột

Để dự án chạy mượt mà với tốc độ cao nhất, toàn bộ thành viên bắt buộc phải tuân thủ quy tắc Git sau:

1.  **KHÔNG** code trực tiếp trên nhánh `main`. Nhánh `main` chỉ dùng để chạy bản demo cuối cùng.
2.  Mọi tính năng mới phải được viết trên nhánh riêng của mình (`dev-xxx`).
3.  Trước khi đẩy code lên (Push), bắt buộc phải `git pull origin main` về nhánh của mình để kiểm tra xem có bị xung đột với code của người khác hay không.
4.  Khi gặp lỗi xung đột bộ nhớ hoặc xung đột code, liên hệ ngay với **Thành viên E (Git Master)** và **Thành viên A (Leader)** để cùng giải quyết, tuyệt đối không tự ý xóa code của thành viên khác.

---
*Chúc cả nhóm phối hợp tốt và đạt điểm tối đa trong kỳ đồ án này!*
