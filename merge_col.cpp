#include "thu_vien_2048.h"

void merge_col(int** bang, int size, char button){

    for (int i = 0; i < size; ++i){


        if (button == 'w' || button == 'W'){
            
            int chi_so = 0;

            for (int j = 0; j < size; ++j)
                if (bang [j][i] != 0) std::swap(bang[chi_so++][i], bang[j][i]);

            for (int j = 0; j < size - 1; ++j){
                if (bang[j][i] == bang[j + 1][i]){
                    bang[j][i] *= 2;
                    bang[j + 1][i] = 0;
                }
            }   

            chi_so = 0;

            for (int j = 0; j < size; ++j)
                if (bang [j][i] != 0) std::swap(bang[chi_so++][i], bang[j][i]);
        }

        else{
            
            int chi_so = size - 1;

            for (int j = size - 1; j >= 0; --j)
                if (bang [j][i] != 0) std::swap(bang[chi_so--][i], bang[j][i]);

            for (int j = size - 1; j > 0; --j){
                if (bang[j][i] == bang[j - 1][i]){
                    bang[j][i] *= 2;
                    bang[j - 1][i] = 0;
                }
            }   

            chi_so = size - 1;

            for (int j = size - 1; j >= 0; --j)
                if (bang [j][i] != 0) std::swap(bang[chi_so--][i], bang[j][i]);
        }
    }
}