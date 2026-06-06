# Hướng Dẫn Làm Việc Chung Trên GitHub

## Mục đích

Tài liệu này quy định quy trình làm việc chung của nhóm nhằm:

* Tránh xung đột mã nguồn (Merge Conflict)
* Theo dõi tiến độ dễ dàng
* Đảm bảo chất lượng code
* Hỗ trợ tích hợp hệ thống cuối kỳ

---

# 1. Quy Tắc Chung

## Không làm việc trực tiếp trên `main`

❌ Không được:

```bash
git push origin main
```

Mọi thay đổi phải được thực hiện trên branch riêng.

---

## Luôn Pull trước khi làm việc

Trước khi bắt đầu code:

```bash
git checkout main
git pull origin main
```

Sau đó mới tạo hoặc cập nhật branch cá nhân.

---

## Commit thường xuyên

Không dồn nhiều thay đổi vào một commit.

Ví dụ tốt:

```text
Add Fan class implementation
Fix AC temperature validation
Update dashboard chart
```

Ví dụ không nên:

```text
Update project
Fix bug
Code
```

---

# 2. Quy Ước Branch

## Branch chính

```text
main
```

Chỉ chứa mã nguồn ổn định.

---

## Branch cá nhân

Mỗi thành viên sử dụng một branch riêng:

```text
feature/member-a
feature/member-b
feature/member-c
feature/member-d
feature/member-e
```

Ví dụ:

```bash
git checkout -b feature/member-c
```

---

## Branch chức năng (khuyến khích)

Nếu thực hiện tính năng lớn:

```text
feature/device-system
feature/dashboard
feature/simulation-engine
feature/energy-report
```

---

# 3. Quy Trình Làm Việc

## Bước 1

Cập nhật mã nguồn mới nhất:

```bash
git checkout main
git pull origin main
```

---

## Bước 2

Chuyển sang branch cá nhân:

```bash
git checkout feature/member-a
```

---

## Bước 3

Code và commit:

```bash
git add .
git commit -m "Add Light class"
```

---

## Bước 4

Đẩy lên GitHub:

```bash
git push origin feature/member-a
```

---

## Bước 5

Tạo Pull Request (PR)

```text
feature/member-a
↓
main
```

Không merge trực tiếp.

---

## Bước 6

Leader review và merge.

---

# 4. Quy Ước Commit Message

## Thêm tính năng

```text
feat: add Light device
feat: implement energy tracking
```

---

## Sửa lỗi

```text
fix: correct AC temperature validation
fix: resolve dashboard refresh bug
```

---

## Cải tiến

```text
refactor: simplify Device inheritance
```

---

## Giao diện

```text
ui: add device control panel
ui: update dashboard layout
```

---

## Tài liệu

```text
docs: update interface contract
docs: add installation guide
```

---

# 5. Quy Tắc Merge

## Trước khi tạo Pull Request

Phải:

### Build thành công

```text
✔ Compile không lỗi
```

### Chạy thử thành công

```text
✔ Chức năng hoạt động đúng
```

### Không sửa file ngoài phạm vi phụ trách

Ví dụ:

* UI không sửa Device Logic
* Device Logic không sửa UI

---

## Không merge khi

```text
❌ Build lỗi
❌ Có conflict chưa xử lý
❌ Làm hỏng chức năng người khác
```

---

# 6. Xử Lý Conflict

Nếu Git báo conflict:

```bash
git pull origin main
```

Giải quyết xung đột thủ công.

Sau đó:

```bash
git add .
git commit -m "Resolve merge conflict"
git push
```

Nếu không chắc chắn:

* Không tự ý xóa code
* Trao đổi với người viết phần đó

---

# 7. Quy Định Theo Module

## Thành viên A

Được chỉnh sửa:

```text
Backend/
DataStructures.h
SmartHomeManager.*
```

---

## Thành viên B

Được chỉnh sửa:

```text
Backend/
Device.*
Light.*
Fan.*
AirConditioner.*
```

---

## Thành viên C

Được chỉnh sửa:

```text
Simulator/
SimulationEngine.*
```

---

## Thành viên D

Được chỉnh sửa:

```text
Frontend/
Dashboard
Charts
```

---

## Thành viên E

Được chỉnh sửa:

```text
Frontend/
Alerts
Reports
Energy Statistics
```

---

# 8. Checklist Trước Khi Push

* [ ] Code compile thành công
* [ ] Không có warning nghiêm trọng
* [ ] Đã test chức năng mới
* [ ] Commit message đúng quy ước
* [ ] Đã pull phiên bản mới nhất từ main
* [ ] Không chứa file tạm hoặc file build

---

# 9. File Không Được Commit

Thêm vào `.gitignore`

```gitignore
build/
*.pro.user
*.o
*.obj
*.exe
*.dll
*.user
```

---

# 10. Nguyên Tắc Cuối Cùng

1. Không push trực tiếp lên `main`.
2. Mỗi người làm việc trên branch riêng.
3. Tạo Pull Request cho mọi thay đổi.
4. Leader chịu trách nhiệm review và merge.
5. Mọi thay đổi liên quan đến `DataStructures.h` phải được cả nhóm thống nhất.

Tuân thủ đúng quy trình sẽ giúp giảm tối đa lỗi tích hợp và merge conflict trong giai đoạn hoàn thiện dự án.
