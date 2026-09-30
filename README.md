# 🎮 2048 Game Project

**MSSV:** `24120121`  
**Trường:** FIT - HCMUS

---

## 1. Hướng dẫn Build

Trước tiên, giải nén file:

```text
24120121.zip
```

> **Lưu ý:** Nếu máy đã cài đặt và thiết lập môi trường **MSYS2 UCRT64** thì có thể bỏ qua **Bước 1 → Bước 5**.

### Bước 1: Tải MSYS2

- Truy cập trang chủ MSYS2:  
  https://www.msys2.org/
- Tải phiên bản cài đặt mới nhất.

### Bước 2: Cài đặt MSYS2

- Chạy file cài đặt vừa tải.
- Chọn thư mục cài đặt, ví dụ:

```text
C:\msys64
```

- Hoàn tất cài đặt.
- Khởi động **MSYS2**.

### Bước 3: Cập nhật hệ thống

Mở **MSYS2 MSYS**.

> Không mở UCRT64 hoặc MINGW64 ở bước này.

Chạy:

```bash
pacman -Syu
```

Nếu hệ thống yêu cầu đóng cửa sổ terminal:

1. Đóng MSYS2.
2. Mở lại **MSYS2 MSYS**.
3. Chạy:

```bash
pacman -Su
```

### Bước 4: Cài đặt môi trường UCRT64

Mở **MSYS2 UCRT64** từ Start Menu.

Cài đặt toolchain:

```bash
pacman -S mingw-w64-ucrt-x86_64-toolchain
```

Khi được hỏi lựa chọn package:

```text
Enter a selection (default=all):
```

Nhấn **Enter** để cài đặt tất cả.

### Bước 5: Thiết lập biến môi trường PATH

Mở:

```text
Control Panel
→ System and Security
→ System
→ Advanced system settings
→ Environment Variables
```

Trong phần **System variables**:

1. Chọn biến `Path`.
2. Chọn **Edit**.
3. Thêm đường dẫn:

```text
C:\msys64\ucrt64\bin
```

4. Nhấn **OK** để lưu.

### Bước 6: Cài đặt SFML

Mở **MSYS2 UCRT64** và chạy:

```bash
pacman -S mingw-w64-ucrt-x86_64-sfml
```

### Bước 7: Cài đặt CMake

Trong **MSYS2 UCRT64**, chạy:

```bash
pacman -S mingw-w64-ucrt-x86_64-cmake
```

### Bước 8: Build dự án

Mở project bằng VS Code:

```text
VS Code
→ File
→ Open Folder
→ 24120121
```

Sau đó mở terminal:

```text
Terminal
→ New Terminal
```

Tạo thư mục `build`:

```bash
mkdir build
cd build
```

Chạy CMake:

```bash
cmake .. -G "MinGW Makefiles"
```

Build project:

```bash
cmake --build .
```

Sau khi build thành công, file thực thi:

```text
2048Game.exe
```

sẽ nằm trong:

```text
bin/
```

---

## 2. Chạy chương trình

Vào thư mục project:

```text
24120121/
```

Sau đó mở:

```text
bin/
└── 2048Game.exe
```

Hoặc chạy trực tiếp file:

```text
24120121/bin/2048Game.exe
```

---

## 3. Một số lưu ý

### Chọn Compiler Kit trong VS Code

Nếu VS Code hiển thị danh sách **Kit** để build project, chọn:

```text
GCC 14.2.0 x86_64-w64-mingw32 (ucrt64)
```

---

### Nội dung `CMakeLists.txt`

Trong trường hợp file `CMakeLists.txt` bị mất hoặc cần tạo lại:

```cmake
cmake_minimum_required(VERSION 3.10)

project(2048Game)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Tìm SFML từ hệ thống MSYS2
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Danh sách source files
set(SOURCE_FILES
    src/Game.cpp
    src/Data.cpp
    src/Controls.cpp
    src/GameLogic.cpp
    src/FreeMemory.cpp
    src/Graphics.cpp
    src/main.cpp
    src/NewGame.cpp
    src/UndoRedo.cpp
)

# Tạo executable
add_executable(2048Game ${SOURCE_FILES})

# Liên kết thư viện SFML
target_link_libraries(2048Game PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
)

# Thêm thư mục include
target_include_directories(2048Game PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${SFML_INCLUDE_DIR}
)
```

---

### Thay đổi font chữ

Có thể thay đổi font của game bằng cách thay thế file font trong:

```text
24120121/
└── assets/
    └── Font/
```

### Thay đổi nhân vật / texture

Có thể thay đổi hình ảnh nhân vật bằng cách thay thế các file trong:

```text
24120121/
└── assets/
    └── Texture/
```

---

## 4. Cấu trúc project

```text
24120121/
├── assets/
│   ├── Font/
│   └── Texture/
│
├── include/
│
├── src/
│   ├── Game.cpp
│   ├── Data.cpp
│   ├── Controls.cpp
│   ├── GameLogic.cpp
│   ├── FreeMemory.cpp
│   ├── Graphics.cpp
│   ├── main.cpp
│   ├── NewGame.cpp
│   └── UndoRedo.cpp
│
├── bin/
│   └── 2048Game.exe
│
├── build/
│
└── CMakeLists.txt
```

---

## 5. Bản tự đánh giá

Project đã hoàn thành các yêu cầu sau:

- [x] Có chức năng **Undo / Redo**
- [x] Có chức năng **lưu game**
- [x] Lưu game bằng **file nhị phân**
- [x] Có sử dụng **con trỏ thuần**
- [x] Có sử dụng kỹ thuật **chia file `.h` và `.cpp`**

**Tự đánh giá mức độ hoàn thành:** `100%`

---

## 6. Video Demo

Video hướng dẫn build và demo gameplay:

https://youtu.be/KJQTyD58ENg

---

## Thông tin project

| Nội dung | Thông tin |
|---|---|
| Project | 2048 Game |
| MSSV | 24120121 |
| Ngôn ngữ | C++ |
| Chuẩn C++ | C++17 |
| Thư viện đồ họa | SFML |
| Build system | CMake |
| Compiler | GCC / MinGW UCRT64 |
| Môi trường | MSYS2 UCRT64 |
| Mức độ hoàn thành | 100% |
