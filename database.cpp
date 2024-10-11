#include "thu_vien_2048.h"

void database(const std::string &file_name){

    std::ifstream file(file_name);

    if (!file){
        std::ofstream file_new(file_name);
        file_new.close();
    }
    
}