#include "thu_vien_2048.h"

bool win_check(int** bang, int size, bool afterWin){
    if (afterWin) return false;

    for (int i = 0; i < size; ++i)
        
        for (int j = 0; j < size; ++j)

            if (bang[i][j] == 2048) return true;

    return false;
}

bool lose_check(int** bang, int size){

    for (int i = 0; i < size; ++i)

        for (int j = 0; j < size; ++j){

            if (i < size - 1 && bang[i][j] == bang[i + 1][j]) return false;

            if (j < size - 1 && bang[i][j] == bang[i][j + 1]) return false;

        }
    
    return true;
}