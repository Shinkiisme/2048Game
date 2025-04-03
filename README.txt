## 2048 Game Project ##
  24120121 - FIT HCMUS
------------------------
				Giải nén 24120121.zip

1. Hướng dẫn Build: NẾU ĐÃ CÀI ĐẶT MÔI TRƯỜNG UCRT64 THÌ CÓ THỂ BỎ QUA 5 BƯỚC ĐẦU
	Bước 1: Tải MSYS2
		+ Truy cập trang chủ MSYS2: https://www.msys2.org/.

		+ Tải bản cài đặt mới nhất.

	Bước 2: Cài đặt MSYS2
		+ Chạy file cài đặt vừa tải về.

		+ Chọn thư mục cài đặt (ví dụ: C:\msys64).

		+ Hoàn tất cài đặt và khởi động MSYS2.

	Bước 3: Cập nhật hệ thống
		+ Mở MSYS2 MSYS (không phải UCRT64/MINGW64).

		+ Chạy lệnh sau để cập nhật các gói cơ bản:
			pacman -Syu

		+ Nếu có thông báo đóng cửa sổ, hãy đóng và mở lại MSYS2, sau đó chạy lại lệnh:
			pacman -Su

	Bước 4: Cài đặt môi trường UCRT64
		+ Mở MSYS2 UCRT64 từ menu Start.

		+ Cài đặt các công cụ cần thiết:
			pacman -S mingw-w64-ucrt-x86_64-toolchain

		+ Nhập all (nhấn Enter) để cài đặt tất cả các gói trong nhóm.

	Bước 5: Thiết lập biến môi trường (PATH)
		+ Mở Control Panel → System and Security → System → Advanced system settings.

		+ Chọn Environment Variables.

		+ Trong phần System variables, tìm biến Path và chọn Edit.

		+ Thêm đường dẫn đến thư mục ucrt64/bin (ví dụ: C:\msys64\ucrt64\bin).

		+ Nhấn OK để lưu thay đổi.
	
	Bước 6: Cài đặt SFML qua MSYS2 UCRT64:
			pacman -S mingw-w64-ucrt-x86_64-sfml
	
	Bước 7: Cài đặt CMake qua MSYS2 UCRT64:
			pacman -S mingw-w64-ucrt-x86_64-cmake
	
	Bước 8: Build dự án:
			+ Vào VSCode -> File -> Open Folder -> 24120121

			+ Terminal -> New Terminal

			+ Tạo thư mục build:
				mkdir build
				cd build

			+ Chạy CMake:
				cmake .. -G "MinGW Makefiles"
			
			+ Build dự án:
				cmake --build .

	File thực thi 2048Game.exe sẽ nằm trong thư mục bin/

*** MỘT SỐ LƯU Ý ***
+ Chạy chương trình bằng cách:
	- Vào thư mục 24120121
	- bin -> 2048Game.exe

+ Nếu vào VSCode hiển thị danh sách chọn Kit để build dự án thì chọn GCC 14.2.0 x86_64-w64-mingw32 (ucrt64)

+ Nội dung file CMakeLists.txt nếu có bị mất:
	cmake_minimum_required(VERSION 3.10)
	project(2048Game)

	set(CMAKE_CXX_STANDARD 17)

	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

	# Tìm SFML từ hệ thống (MSYS2)
	find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

	# Danh sách file source
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

+ Có thể thay đổi font chữ và nhân vật bằng cách thay thế font chữ (24120121->assets->Font) hoặc nhân vật (24120121->assets->Texture)

------------------------

2. Bản tự đánh giá:
	- Có chức năng undo/redo không
	- Có chức năng lưu game
	- Có lưu game bằng file nhị phân
	- Có sử dụng con trỏ thuần để cài đặt
	- Có sử dụng kĩ thuật chia file (.h và .cpp)
	- Tự đánh giá mức độ hoàn thành: 100%

------------------------

3. Link video demo build và gameplay: https://youtu.be/KJQTyD58ENg


	