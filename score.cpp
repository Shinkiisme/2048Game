#include "thu_vien_2048.h"
// Hàm tính điểm trên toàn bộ vùng chơi.
int score(int** bang, int size){
    int point = 0;

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            point += bang[i][j];

    std::cout << "Diem cua ban: " << point << '\n';

    return point;
}