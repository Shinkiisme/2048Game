#include "thu_vien_2048.h"


// Hàm lưu lại trạng thái trò chơi nếu người chơi muốn lưu để lần sau chơi tiếp.
void save_game(int** bang, int size, std::string username){

    // Lưu tên người chơi vào cơ sở dữ liệu.
    std::ifstream file("players");
    std::string reading;
    bool name_found = false;

    while(std::getline(file, reading)){
        if (reading == username){
            name_found = true;
            break;
        }
    }

    if (!name_found){
            std::ofstream file_add("players", std::ios::app);

            file_add << username << '\n';

            file_add.close();
    
    }

    file.close();

    // Nếu chưa có thư mục Saves thì tạo mới.
    if (!std::filesystem::exists("Saves")) std::filesystem::create_directory("Saves");
    
    // Lưu bảng chơi của người chơi vào file tên người chơi.
    std::ofstream save("Saves/" + username);

    save << size << '\n';

    for (int i = 0; i < size; ++i){

        for (int j = 0; j < size; ++j)
            save << bang[i][j] << ' ';
         
        save << '\n';
    }

    save.close();

}