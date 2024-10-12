#include "thu_vien_2048.h"

int** load_save(std::string username, int &size){

    std::ifstream file_save("Saves/" + username);
    std::string reading;

    if (!file_save.is_open()) return nullptr;

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