#include "thu_vien_2048.h"

void save_game(int** bang, int size, std::string username){
    std::ofstream save("saves", std::ios::app);

    save << username << '\n' << size << '\n';

    for (int i = 0; i < size; ++i){

        for (int j = 0; j < size; ++j)
            save << bang[i][j] << ' ';
        
        save << '\n';

    }

    save.close();
}