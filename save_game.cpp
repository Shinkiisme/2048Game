#include "thu_vien_2048.h"

void save_game(int** bang, int size, std::string username){

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

    if (!std::filesystem::exists("Saves")) std::filesystem::create_directory("Saves");
    
    
    std::ofstream save("Saves/" + username);

    save << size << '\n';

    for (int i = 0; i < size; ++i){

        for (int j = 0; j < size; ++j)
            save << bang[i][j] << ' ';
         
        save << '\n';
    }

    save.close();

}