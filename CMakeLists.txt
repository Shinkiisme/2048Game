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
