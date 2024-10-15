#include "thu_vien_2048.h"

// Hàm kiểm tra thoả mãn điều kiện thắng.
bool win_check(int** bang, int size, bool afterWin){
    
    // Nếu đang trong chế độ chơi tiếp sau khi thắng.
    // Bỏ qua kiểm tra thắng.
    if (afterWin) return false;

    for (int i = 0; i < size; ++i)
        
        for (int j = 0; j < size; ++j)

            if (bang[i][j] == 2048) return true;

    return false;
}

// Hàm kiểm tra thoả mãn điều kiện thua.
bool lose_check(int** bang, int size){

    // Duyệt qua các ô, nếu vẫn còn có thể gộp thì chưa thoả điều kiện thua.
    for (int i = 0; i < size; ++i)

        for (int j = 0; j < size; ++j){

            if (i < size - 1 && bang[i][j] == bang[i + 1][j]) return false;

            if (j < size - 1 && bang[i][j] == bang[i][j + 1]) return false;

        }
    
    return true;
}