#include "thu_vien_2048.h"

void rand_number(int** bang, int size){

    // Random khởi tạo số 2 hay 4 cho trò chơi.
    // 2: 90%
    // 4: 10%
    int ti_le = 1 + rand() % 10;
    int so;

    // Khai báo mảng chứa các cặp toạ độ ô trống.
    std::pair<int, int>* o_trong = new std::pair<int, int>[size * size];

    if (ti_le == 1) so = 4;
    else so = 2;
    
    // Thêm các cặp toạ độ ô có giá trị bằng 0 vào mảng.
    int k = 0;

    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            if (bang[i][j] == 0){
                o_trong[k] = std::make_pair(i, j);
                ++k;
            }
        }
    }

    // Nếu không có ô trống thì trả về.
    if (k == 0){
        delete[] o_trong;
        return;
    }

    // Random một ô trống ngẫu nhiên.
    int o_random = rand() % k;

    // Gán giá trị ô đó bằng số khởi tạo ngẫu nhiên.
    bang[o_trong[o_random].first][o_trong[o_random].second] = so;

    delete[] o_trong;
}
