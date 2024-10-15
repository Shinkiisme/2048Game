#include "thu_vien_2048.h"

// Hàm load lại bản lưu cũ mà người chơi đã lưu.
int** load_save(std::string username, int &size){

    // Đọc dữ liệu từ thư mục Saves, file trùng với tên người chơi cũ.
    std::ifstream file_save("Saves/" + username);
    std::string reading;

    // Nếu không mở được file (không có bản lưu) thì trả về nullptr.
    if (!file_save.is_open()) return nullptr;

    // Đọc dữ liệu từ file lưu và gán cho các biến hiện hành để chơi tiếp.
    std::getline(file_save, reading);
    std::istringstream(reading) >> size;

    int** bang = new int*[size];

    for (int i = 0; i < size; ++i)
        bang[i] = new int[size];

    for (int i = 0; i < size; ++i){
        std::getline(file_save, reading);
        std::istringstream load(reading);

        for (int j = 0; j < size; ++j)
            load >> bang[i][j]; 
            
    }
            
    file_save.close();

    return bang;

}