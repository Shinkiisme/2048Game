#include "thu_vien_2048.h"

int** load_save(std::string username, int &size){

    database("saves");

    std::ifstream file_save("saves");
    std::string reading;

    while(std::getline(file_save, reading)){
        if (reading.empty()) continue;

        if (reading == username){
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
    }

    file_save.close();

    return nullptr;

}